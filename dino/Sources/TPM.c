/*!
 * @file TPM.c
 * @brief Este modulo contem interface dos TPMx.
 * @author Wu Shin Ting
 * @date 01/03/2022
 */

#include "MKL25Z4.h"
#include "TPM.h"
#include "GPIO_switches.h"

static TPM_MemMapPtr TPM[] = TPM_BASE_PTRS;
static PORT_MemMapPtr PORT[] = PORT_BASE_PTRS;

void TPM_initPTB0EPWM(uint16_t periodo, uint8_t ps, uint8_t percentagem, booleano_type mode) {
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORT_PCR_REG(PORT[1], 0) |= (PORT_PCR_ISF_MASK | PORT_PCR_MUX(0x3));
	TPM_init(1, periodo, ps);
	TPM_initChEPWM(1, 0, percentagem, mode);
}


void TPM_initH5Pin12EPWM (uint16_t periodo, uint8_t ps, uint8_t percentagem, booleano_type mode) {
	
	TPM_init (2, periodo, ps);
	
	/*!
	 * Configura a funcao dos pinos em TPM
	 */
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK; 			///< \li \l habilita clock de PORTE                           	
	PORT_PCR_REG(PORT[4],22) |= (PORT_PCR_ISF_MASK |			///< \li \l PTE22 em TPM2_CH0 (H5, pino 2)
				  PORT_PCR_MUX(0x3) );       
	PORT_PCR_REG(PORT[4],23) |= (PORT_PCR_ISF_MASK |			///< \li \l PTE23 em TPM2_CH1 (H5, pino 1)
				  PORT_PCR_MUX(0x3) );      

	/*!
	 * Configura os canais para gerarem EPWM (edge-aligned PWM): 0b1010 (High) ou 0b10X1 (Low) 
	 * Configura o valor de match inicial
	 */
	TPM_initChEPWM (2, 0, percentagem, mode);
	TPM_initChEPWM (2, 1, percentagem, mode);

}

void TPM_atualizaDutyCycleH5Pin2 (uint8_t percentagem)
{
	TPM_CnV_REG(TPM[2],0) = TPM_CnV_VAL(percentagem*0.01*(TPM2_MOD+1));
}

void TPM_atualizaDutyCycleH5Pin1 (uint8_t percentagem)
{

	TPM_CnV_REG(TPM[2],1) = TPM_CnV_VAL(percentagem*0.01*(TPM[2]->MOD+1));
}

void TPM_atualizaDutyCycleEPWM (uint8_t x, uint8_t n, uint8_t percentagem){
	TPM_CnV_REG(TPM[x], n) = TPM_CnV_VAL(percentagem*0.01*(TPM[x]->MOD+1));
}

uint16_t TPM_leChValor(uint8_t x, uint8_t n) {
	return TPM_CnV_REG(TPM[x], n);
}

uint16_t TPM_leMOD(uint8_t x) {
	return TPM[x]->MOD;
}

void TPM_chaveiaChModoNivel(uint8_t x, uint8_t n, uint8_t MbaEba) {
	TPM_CnSC_REG(TPM[x], n) &= ~(0xffff << 2);
	TPM_CnSC_REG(TPM[x], n) |= (MbaEba << 2); 
}

void TPM_init (uint8_t x, uint16_t periodo, uint8_t ps) {
	
	SIM_SCGC6 |= GPIO_PIN(24+x); 	///< \li \l habilita clock de TPMx                           	

	/**
	 * Fonte de CLK de TPM: TPMSRC=SIM_SOPT2[25:24]=01 (MCGFLLCLK|MCGPLLCLK/2)
	 * PLLFLLSEL=SIM_SOPT2[16]=0 (MCGFLLCLK) 
	 */
	SIM_SOPT2 |= SIM_SOPT2_TPMSRC(0b01);     ///< \li \l seleciona fonte de clock TPM
	SIM_SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;  	

	TPM[x]->SC &= ~TPM_SC_CMOD(0x3);		///< desabilita contador

	TPM[x]->SC &= ~(TPM_SC_TOIE_MASK |		///< \li \l desabilita interrupcao "overflow"
				TPM_SC_CPWMS_MASK); 	///< \li \l modo de contagem crescente

	TPM[x]->MOD &= TPM_MOD_MOD(periodo);    	///< \li \l seta contagem maxima
	
	TPM[x]->SC &= ~TPM_SC_PS(0b111);       ///< \li \l seta prescaler 
	TPM[x]->SC |= TPM_SC_PS(ps);         	

	TPM[x]->CNT |= TPM_CNT_COUNT(0x0)  ;   ///< \li \l reseta a contagem com base em LPTPM
	
	TPM[x]->SC |= TPM_SC_CMOD(0x1);		///< \li \l habilita contador 
}

void TPM_initChEPWM (uint8_t x, uint8_t n, uint8_t percentagem, booleano_type mode) {
	/*!
	 * Configura os canais para gerarem EPWM (edge-aligned PWM): 0b1010 (High) ou 0b10X1 (Low) 
	 */
	TPM_CnSC_REG(TPM[x],n) &= ~(TPM_CnSC_MSB_MASK |  // MSB=TPMx_CnSC[5]=0
			TPM_CnSC_MSA_MASK |         // MSA=TPMx_CnSC[4]=0
			TPM_CnSC_ELSB_MASK |        // ELSB=TPMx_CnSC[3]=0
			TPM_CnSC_ELSA_MASK );       // ELSA=TPMx_CnSC[2]=0

	if (mode == ON) { //High-true
		TPM_CnSC_REG(TPM[x],n) |= (TPM_CnSC_MSB_MASK |       // MSB=TPMx_CnSC[5]=1
				TPM_CnSC_ELSB_MASK );     		// ELSB=TPMx_CnSC[3]=1
	} else if (mode == OFF) { //Low-true
		TPM_CnSC_REG(TPM[x],n) |= (TPM_CnSC_MSB_MASK |       // MSB=TPMx_CnSC[5]=1
				TPM_CnSC_ELSA_MASK );     		// ELSB=TPMx_CnSC[2]=1
	}
	
	/*!
	 * Configura o valor de match inicial
	 */
	TPM_CnV_REG(TPM[x],n) = TPM_CnV_VAL(percentagem*0.01*(TPM[x]->MOD+1)); // TPMx_CnV	
}

void TPM_atualizaPolaridadeEPWM (uint8_t x, uint8_t n, booleano_type mode)
{
	TPM_CnSC_REG(TPM[x],n) &= ~(TPM_CnSC_MSB_MASK |      ///< desabilita canal TPM2_CH1
			TPM_CnSC_MSA_MASK |         
			TPM_CnSC_ELSB_MASK |        
			TPM_CnSC_ELSA_MASK );       

	if (mode == ON) 						///< reabilita o canal no modo HIGH
		TPM_CnSC_REG(TPM[x],n) |= (TPM_CnSC_MSB_MASK |      
				TPM_CnSC_ELSB_MASK );     
	else if (mode == OFF) 					///< reabilita o canal no modo LOW
		TPM_CnSC_REG(TPM[x],n) |= (TPM_CnSC_MSB_MASK |       
				TPM_CnSC_ELSA_MASK );     		
}

/*!
 * @file main.c
 * @brief Este projeto demonstra o uso de TPMx para gerar sinais PWM
 * @author Arthur Cantarela
 * @author Leandro Ponsano
 */

#include "timers.h"
#include "TPM.h"
#include "util.h"
#include "ISR.h"
#include "GPIO_latch_lcd.h"
#include "GPIO_switches.h"
#include "derivative.h"
#include "dino.h"
#include "cactus.h"
#include "game.h"
#include "ADC.h"

/*!
 * @var config
 * @brief Inicializar os parametros de configuracao do modulo ADC0
 * @note Ver secao 28.4.4.5 (pagina 487) do manual 
 * https://www.dca.fee.unicamp.br/cursos/EA871/references/ARM/KL25P80M48SF0RM.pdf
 */
ADCConfig config = {
		.sc1_diff=0,      		///< conversao unipolar (0) ou diferencial (1)
		.cfg1_adlpc=0,			///< potencia normal
		.cfg1_adiv=0b10,		///< 10485760/2621440 = 4
		.cfg1_adlsmp=1, 		///< tempo de amostragem longo
		.cfg1_mode=0b11,		///< Resolucao de 16 bits
		.cfg1_adiclk=0b01,		///< Bus clock/2
		.cfg2_muxsel=0, 		///< canal A (0)
		.cfg2_adacken=0,		///< desabilitar a saida de sinal de clock assincrono
		.cfg2_adhsc=0,			///< velocidade normal de conversao
		.cfg2_adlsts=0b11, 		///< 2 ciclos ADCK extra
		.sc2_adtrg=0,			///< trigger por software
		.sc2_acfe=0, 		    ///< desabilitar funcao de comparacao em igualdade
		.sc2_acfgt=0,			///< desabilitar funcao de comparacao em desigualdade
		.sc2_acren=0,			///< desabilitar comparacao de uma faixa
		.sc2_dmaen=0, 			///< habilitar de DMA
		.sc2_refsel=0b00,		///< tensoes de referencia VREFH e VREFL
		.sc3_adco=0,			///< amostragem unica
		.sc3_avge=1, 			///< habilitar media de amostras por hardware
		.sc3_avgs=0b00 			///< 4 amostras
};


int main(void)
{
	GPIO_ativaConLatchLCD ();
	GPIO_initLCD ();
	GPIO_initSwitches ();
	GPIO_habilitaSwitchesInterrupt (3);
	SIM_setaOUTDIV4 (0b001);
	SysTick_init (5242880/4);
	RTClpo_init ();
	
	PIT_initSemAtivacaoTimer0(968000); 	
	ADC0_init(&config);		
	ADC0_connectPTB1ToChannel ();
	ADC0_initADHWT(0b100);     
	TPM_initPTB0EPWM (65535, 0b101, 0, 1);
	uint16_t amostra;
	uint8_t progressByte;
	ADC0_selChannel (0b01001); 				//!< /li /l selecionar o canal do header H7
	ADC0_ativaIRQ(2);
	PIT_ativaIRQ(1);
	PIT_ativaTimer0();
	
	initCactus();
	initDino();
	initGame();
		
	amostra = 0;
	for(;;) {
		renderCactus ();
		renderDino ();
		renderGameLevel();
		renderGameScore();
		renderGameState();
			
		amostra = ISR_LeValorAmostrado ();
		if(amostra < 0x4000) {
			setGameLevel(EASY);
		} else if(amostra < 0xC000) {
			setGameLevel(MEDIUM);
		} else {
			setGameLevel(HARD);
		}
		progressByte = ISR_LeByteProgresso();
		GPIO_escreveByteLatch(progressByte, 10);
	}
	return 0;
}

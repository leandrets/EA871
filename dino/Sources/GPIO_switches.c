/**
 * @file GPIO_switches.h
 * @brief Programas relacionados com as botoeiras
 * @author Arthur Cantarela
 * @author Leandro Ponsano Corimbaba
 */

//Para uso das macros dos registradores de KL25Z4
#include "derivative.h"
#include "GPIO_switches.h"
#include "util.h"

void GPIO_amostraSwitchesISF (uint32_t *valor)
{
	*valor = (PORTA_ISFR & 0x1030);
}

void GPIO_initSwitches () {
    // Habilita o clock do modulo PORTA (SIM_SCGC5 mapeado em 0x40048038)
    SIM_SCGC5 |= (1<<9);

    // Funcao GPIO (PORTA_PCR4 mapeado em 0x40049010)
    PORTA_PCR4 &= ~(0b111 << 8);
    PORTA_PCR4 |=  (0b001 << 8);
    // Funcao GPIO (PORTA_PCR5 mapeado em 0x40049014)
    PORTA_PCR5 &= ~(0b111 << 8);
    PORTA_PCR5 |=  (0b001 << 8);
    // Funcao GPIO (PORTA_PCR12 mapeado em 0x40049030)
    PORTA_PCR12 &= ~(0b111 << 8);
    PORTA_PCR12 |=  (0b001 << 8);

    // Sentido do sinal: entrada (GPIOA_PDDR mapeado em 0x400ff014)
    GPIOA_PDDR &= ~(1<< 4);
    GPIOA_PDDR &= ~(1<< 5);
    GPIOA_PDDR &= ~(1<<12);
}

void GPIO_habilitaSwitchesInterrupt (uint8_t priority) {
	//regiatrador NVIC_ISER mapeado em 0xe000e100u
	/** habilita interrupcoes */
	NVIC_ISER |= (1 << 30);
	//registrador NVIC_ICPR mapeado em 0xe000e280u (pg. 283)
	NVIC_ICPR |= (1 << 30);
	//registrador NVIC_IPR7 mapeado em 0xe000e410u (pg. 283)
	/** define prioridade */
	NVIC_IPR7 &= ~(0b11 << 22);
	NVIC_IPR7 |= (priority << 22);

	// Configurar IRQC (PORTA_PCR4 mapeado em 0x40049010) e limpar flag (w1c)
	PORTA_PCR4 &= ~(0b1111 << 16);
	PORTA_PCR5 &= ~(0b1111 << 16);
	PORTA_PCR12 &= ~(0b1111 << 16);
	/** interrompe nas borda de subida e descida */
	PORTA_PCR4 |= ((ISF_DETECTED << 24) | (IRQC_FALLING_EDGE << 16));
	PORTA_PCR5 |= ((ISF_DETECTED << 24) | (IRQC_FALLING_EDGE << 16));
	PORTA_PCR12 |= ((ISF_DETECTED << 24) | (IRQC_FALLING_EDGE << 16));
}

void GPIO_desativaSwitchesInterrupt ()
{
	NVIC_ICER |= (1 << 30);
}

void GPIO_reativaSwitchesInterrupt ()
{
	NVIC_ISER |= (1 << 30);
}

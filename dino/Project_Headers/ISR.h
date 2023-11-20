/*
 * ISR.h
 *
 *  Created on: Oct 23, 2022
 *      Author: ea871
 */

#ifndef ISR_H_
#define ISR_H_

/** Switches helpers */
#define NMI_SWITCH 0x0010
#define IRQA5_SWITCH 0x0020
#define IRQA12_SWITCH 0x1000
#define BOTH_IRQA_SWITCHES 0x1020

/**
 * @brief Le 2 valores amostrados
 * @param[out] amostras 2 amostras
 */
uint16_t ISR_LeValorAmostrado ();

uint16_t ISR_LePontuacao();

uint8_t ISR_LeByteProgresso();

/**
 * @brief Converte codigo binario em um valor de tensao
 * @param[in] valor: codigo binario amostrado
 * @param[out] mV: resultado da conversao em ponto flutuante
 */
void codigo2tensao (uint16_t valor, float *mV);

void SysTick_Handler (void);

void PORTA_IRQHandler(void);

void ADC0_IRQHandler(void);

void PIT_IRQHandler(void);

#endif /* ISR_H_ */


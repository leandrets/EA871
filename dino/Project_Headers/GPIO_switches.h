/**
 * @file GPIO_switches.h
 * @brief Programas relacionados com as botoeiras
 * @author Arthur Cantarela
 * @author Leandro Ponsano Corimbaba
 */

#ifndef GPIO_SWITCHES_H_
#define GPIO_SWITCHES_H_

//Para uso dos tipos de dados uint*_t
#include "stdint.h"

#define ISF_DETECTED 1 /** Interrupt Status Flag */
/** Interrupt configuration */
#define IRQC_RISING_EDGE 0b1001  
#define IRQC_FALLING_EDGE 0b1010  
#define IRQC_EITHER_EDGE 0b1011 

/**
 * @brief amostra as chaves NMI, IRQA5 e IRQA12
 * @param[out] valor de 13 bits, onde 4, 5 e 12 indicam estado das chavas (ativo baixo),
 * deslocados de 4 bits para direita
 */
void GPIO_amostraSwitchesISF (uint32_t *valor);

/**
 * @brief inicializa as botoeira NMI, IRQA5 e IRQA12
 */
void GPIO_initSwitches ();

/**
 * @brief habilita a interrupcao das botoeiras NMI, IRQA5 e IRQA12
 * @param[in] priority nivel de prioridade do atendimento da interrupcao
 */
void GPIO_habilitaSwitchesInterrupt (uint8_t priority);

/**
 * @brief desabita a interrupcao das botoeiras 
*/
void GPIO_desativaSwitchesInterrupt ();

/**
 * @brief reabilita a interrupcao das botoeiras
*/
void GPIO_reativaSwitchesInterrupt ();

#endif /* GPIO_SWITCHES_H_  */

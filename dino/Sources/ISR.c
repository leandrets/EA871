/*!
 * @file ISR.c
 * @brief Este modulo contem as rotinas de servico para tratamento de interrupcoes.
 * @author Wu Shin Ting
 * @date 03/03/2022
 */

#include "derivative.h"
#include "GPIO_switches.h"
#include "GPIO_latch_lcd.h"
#include "timers.h"
#include "TPM.h"
#include "ISR.h"
#include "dino.h"
#include "cactus.h"
#include "game.h"
#include "stdint.h"
#include <stdlib.h>

/*!
 * Declarar variaveis GLOBAIS de controle
 */
static uint16_t valor;		///< valor convertido do sensor LM61
static uint8_t counter = 0, level_timer = 5;
static uint8_t byte = 0;

void SysTick_Handler (void)
{	
	Game game = getGame ();
	Cactus cactus = getCactus ();
	Dino dino = getDino ();
	counter += 3;
	uint8_t cactus_position;
	if (counter > level_timer)
	{
		if(cactus.x > 0xf) {
			cactus_position = 0xf;
			if(rand() < RAND_MAX / 6) {
				setCactusPosition(cactus_position);
			}
		} else {
			cactus_position = cactus.x - 1;
			setCactusPosition(cactus_position);
		}
		counter = 0;
	}
	cactus = getCactus ();
	if(cactus.x == 1 || cactus.x == 2) {
		if(cactus.h > dino.y) {
			setGameState(GAMEOVER);
			dinoKill ();
			SysTick_desativaInterrupt ();
		}
	}
	if (dino.state == JUMPING || dino.state == JUMPED)
	{
		dinoMoveY ();
	}
	switch (game.level) {
		case EASY:
			level_timer = 6;
			if (game.score == 65535) {
				setGameTurns(game.turns + 1);
				cleanGameScore();
			}
			setGameScore (game.score + 1);
			break;
		case MEDIUM:
			level_timer = 3;
			if (game.score > 65530) {
				setGameTurns(game.turns + 1);
				cleanGameScore();
			}
			setGameScore (game.score + 5);
			break;
		case HARD:
			level_timer = 0;
			if (game.score > 65525) {
				setGameTurns(game.turns + 1);
				cleanGameScore();
			}
			setGameScore (game.score + 10);
	}
	float percentagem = (float)game.score/65535.0;
	setGameProgress(percentagem);
	byte = ((1 << (game.turns)) - 1) | (game.progress << game.turns);
}

void PORTA_IRQHandler(void) {
	uint32_t valor;
	GPIO_amostraSwitchesISF(&valor);
	Dino dino = getDino();
	Game game = getGame();
	
	switch(game.state) {
		case RESETED:
			if (valor == IRQA5_SWITCH) {
				setGameState(RUNNING);
				SysTick_ativaInterrupt ();
			}
			break;
		case GAMEOVER:
			if (valor == IRQA5_SWITCH) {
				setGameState(RESETED);
				initCactus();
				initDino();
				setGameScore(0);
				setGameTurns(0);
				setGameProgress(0);
				cleanGameScore();
			}
			break;
		case RUNNING:
			if (valor == IRQA12_SWITCH) {
				if(dino.state == GROUND) {
					dinoJumpingBegin ();
				} else if(dino.state == JUMPING) {
					dinoJumpingEnd ();
				}
			}
			else if (valor == IRQA5_SWITCH) {
				setGameState(PAUSED);
				SysTick_desativaInterrupt ();
			}
			break;
		case PAUSED:
			if (valor == IRQA5_SWITCH) {
				setGameState(RUNNING);
				SysTick_ativaInterrupt ();
			}
			break;
	}
	PORTA_ISFR |= 0x1030;
}


void ADC0_IRQHandler(void) {
	if( ADC0_SC1A & ADC_SC1_COCO_MASK) {
		valor = ADC0_RA;					//!< \li \l guardar o valor amostrado
	}
}


void PIT_IRQHandler(void) {	
	GPIOE_PSOR = GPIO_PIN(21);			//!< trigger software enviado para ADC0		
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;     //!< \li \l w1c (limpa pendencias)
}

uint16_t ISR_LeValorAmostrado () {
	return valor;
}

uint8_t ISR_LeByteProgresso() {
	return byte;
}

/*
 * @file game.c
 */

#include "game.h"
#include "GPIO_latch_lcd.h"
#include "util.h"

static Game game;

void initGame (void)
{
	game.state = RESETED;
	game.level = EASY;
	game.score = 0;
	game.turns = 0;
	game.progress = 0;
}

Game getGame (void)
{
	return game;
}

void setGameState (game_state_type state)
{
	game.state = state;
}

void setGameLevel (game_level_type level)
{
	game.level = level;
}

void setGameScore (uint16_t score)
{
	game.score = score;
}

void setGameTurns (uint8_t turns) {
	game.turns = turns;
}

void setGameProgress (float percentagem) {
	uint8_t availableBits = 8 - game.turns;
	uint8_t litBits = (uint8_t)(percentagem * availableBits);
	game.progress = (1 << (litBits+1)) - 1;
}

void renderGameLevel (void)
{
	static game_level_type level = -1;
	static uint8_t lvl1[] = { 0x15, 0x15, 0x1A, 0x00, 0x04, 0x0C, 0x04, 0x0E };
	static uint8_t lvl2[] = { 0x15, 0x15, 0x1A, 0x00, 0x0E, 0x02, 0x0C, 0x0E };
	static uint8_t lvl3[] = { 0x15, 0x15, 0x1A, 0x00, 0x0E, 0x06, 0x02, 0x0E };
	static uint8_t lvlString[] = { LEVEL_CHAR, 0x00 }; 
	if(level != game.level) {
		switch (game.level) {
			case EASY:
				GPIO_escreveBitmapLCD (LEVEL_CHAR, lvl1);
				break;
			case MEDIUM:
				GPIO_escreveBitmapLCD (LEVEL_CHAR, lvl2);
				break;
			case HARD:
				GPIO_escreveBitmapLCD (LEVEL_CHAR, lvl3);
		}
		GPIO_escreveStringLCD (LEVEL_BASE_ADDR, lvlString);
	}
}

void renderGameState (void)
{
	static game_state_type game_state = -1;
	if(game_state != game.state) {
		game_state = game.state;
		switch(game_state) {
			case RESETED:
				GPIO_escreveStringLCD(STATE_BASE_ADDR, (uint8_t*) "  START  ");
				break;
			case GAMEOVER:
				GPIO_escreveStringLCD(STATE_BASE_ADDR, (uint8_t*) "GAME OVER");
				break;
			case PAUSED:
				GPIO_escreveStringLCD(STATE_BASE_ADDR, (uint8_t*) "  PAUSED ");
				break;
			default:
				GPIO_escreveStringLCD(STATE_BASE_ADDR, (uint8_t*) "         ");
				break;
		}
	}
}

void renderGameScore (void)
{
	static uint16_t game_score = -1;
	static game_state_type game_state = -1;
	static char scoreStr[] = "    ";
	uint8_t base_addr;
	if(game_score != game.score || game_state != game.state || game_state == GAMEOVER) {
		game_score = game.score;
		game_state = game.state;
		base_addr = UPPER_SCORE_BASE_ADDR;
		if(game.state == GAMEOVER) {
			GPIO_escreveStringLCD(base_addr, (uint8_t*)"    ");
			base_addr = LOWER_SCORE_BASE_ADDR;
		}
		itoa((int32_t)game_score, scoreStr, 10);
		GPIO_escreveStringLCD(base_addr, (uint8_t*)scoreStr);
	}
}

void cleanGameScore(void) {
	GPIO_escreveStringLCD(UPPER_SCORE_BASE_ADDR, (uint8_t*) "     ");
}

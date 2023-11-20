/*
 * @file game.h
 * @author Arthur Cantarela
 * @author Leandro Ponsano
 */

#ifndef GAME_H_
#define GAME_H_

#include "derivative.h"

typedef enum game_state_tag { RESETED, RUNNING, PAUSED, GAMEOVER } game_state_type;

typedef enum game_level_tag {EASY, MEDIUM, HARD} game_level_type;

#define LEVEL_BASE_ADDR 0x00
#define LEVEL_CHAR 0x05

#define STATE_BASE_ADDR 0x02
#define UPPER_SCORE_BASE_ADDR 0x0b
#define LOWER_SCORE_BASE_ADDR 0x46

typedef struct Game {
	game_state_type state;
	game_level_type level;
	uint16_t score;
	uint8_t turns;
	uint8_t progress;
} Game;

void initGame (void);

Game getGame (void);

void setGameState (game_state_type state);

void setGameLevel (game_level_type level);

void setGameScore (uint16_t score);

void setGameTurns (uint8_t turns);

void setGameProgress (float percentagem);

void renderGameLevel (void);

void renderGameState (void);

void renderGameScore (void);

void cleanGameScore(void);

#endif /* GAME_H_ */

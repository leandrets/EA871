/*
 * @file dino.h
 * @author Arthur Cantarela 135017
 * @author Leandro Ponsano
 */

#ifndef DINO_H_
#define DINO_H_

#include "derivative.h"

typedef enum dino_state_tag { GROUND, JUMPING, JUMPED, DEAD } dino_state_type;

typedef struct Dino {
	int8_t y;
	int8_t vy;
	uint8_t jump_counter;
	dino_state_type state;
} Dino;

void initDino (void);

Dino getDino (void);

void dinoJump (void);

void dinoMoveY (void);

void dinoOverJump (void);

void dinoKill (void);

void renderDino (void);

void dinoJumpingBegin (void);

void dinoJumpingEnd (void);

#define DINO_BASE_ADDR 0x01
#define DINO_UPPER_CHAR 0x01
#define DINO_LOWER_CHAR 0x02
#define DINO_HEIGHT 6

#endif /* DINO_H_ */

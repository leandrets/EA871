/*
 * @file cactus.h
 */

#ifndef CACTUS_H_
#define CACTUS_H_

#include "derivative.h"

typedef struct Cactus {
	uint8_t x;
	uint8_t h;
	uint8_t bitmap[8];
} Cactus;

#define CACTUS_BASE_ADDR 0x40
#define CACTUS_CHAR 0x04

void initCactus (void);

Cactus getCactus (void);

void setCactusPosition (uint8_t x);

void renderCactus (void);

#endif /* CACTUS_H_ */

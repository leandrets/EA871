/*
 * @file dino.c
 * @author Arthur Cantarela
 * @author Leandro Ponsano
 */

#include "dino.h"
#include "cactus.h"
#include "game.h"
#include "GPIO_latch_lcd.h"
#include "GPIO_switches.h"

static uint8_t dino_bitmap[6] = { 0x07, 0x07, 0x06, 0x0F, 0x1E, 0x0A };
static Dino dino;

Dino getDino (void)
{
	return dino;
}

void initDino (void) {
	dino.y = 0;
	dino.vy = 0;
	dino.jump_counter = 0;
	dino.state = GROUND;
}

void renderDino (void) {
	uint8_t i;
	static uint8_t y = -1;
	static game_state_type game_state = -1;
	uint8_t upper_bitmap[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	uint8_t lower_bitmap[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	static uint8_t upper_string[2] = { DINO_UPPER_CHAR, 0x00 };
	static uint8_t lower_string[2] = { DINO_LOWER_CHAR, 0x00 };
	Cactus cactus = getCactus ();
	Game game = getGame ();
	
	if(dino.y != y || cactus.x <= 1 || game_state != game.state) {
		y = dino.y;
		game_state = game.state;
		for(i = 0; i < 16; i++) {
			if(i >= y && i < y+6) {
				if(i < 8) {
					lower_bitmap[7-i] = dino_bitmap[5-(i-y)];
				} else {
					upper_bitmap[15-i] = dino_bitmap[5-(i-y)];
				}
			}
			if(cactus.x == 1) {
				lower_bitmap[7-i] |= cactus.bitmap[7-i];
			}
		}
		GPIO_escreveBitmapLCD (DINO_UPPER_CHAR, upper_bitmap);
		GPIO_escreveBitmapLCD (DINO_LOWER_CHAR, lower_bitmap);
		GPIO_escreveStringLCD (DINO_BASE_ADDR, upper_string);
		GPIO_escreveStringLCD (DINO_BASE_ADDR+0x40, lower_string);
	}
}

void dinoJumpingBegin (void)
{
	if(dino.state != GROUND) return;
	dino.state = JUMPING;
	dino.vy = 4;
	PORTA_PCR12 |= IRQC_RISING_EDGE << 16;
}

void dinoJumpingEnd (void)
{
	PORTA_PCR12 |= IRQC_FALLING_EDGE << 16;
	if(dino.state != JUMPING) return;
	dino.state = JUMPED;
}

void dinoMoveY (void)
{
	if(dino.state != JUMPING && dino.state != JUMPED) return;
	if(dino.state == JUMPING) {
		if(dino.vy > 0) {
			if(dino.jump_counter < 6) dino.jump_counter += 2;
		} else {
			dino.state = JUMPED;
		}
	}
	if(dino.y == 0 && dino.vy < 0) {
		dino.state = GROUND;
		dino.vy = 0;
		dino.jump_counter = 0;
	} else if(dino.vy == 0) {
		if(dino.jump_counter) {
			dino.jump_counter--;
		} else {
			dino.vy--;
		}
	} else {
		dino.y += dino.vy--;
		if(dino.y > 10) dino.y = 10;
		else if(dino.y < 0) dino.y = 0;
	}
}

void dinoKill (void)
{
	dinoJumpingEnd();
	dino.state = DEAD;
}

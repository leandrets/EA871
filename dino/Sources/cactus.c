/*
 * @file cactus.c
 */

#include "cactus.h"
#include "GPIO_latch_lcd.h"
static Cactus cactus;

void initCactus (void)
{
	uint8_t i;
	uint8_t bitmap[] = { 0x00, 0x04, 0x14, 0x14, 0x15, 0x0D, 0x06, 0x04 };  
	cactus.x = 0x0f;
	cactus.h = 7;
	for (i = 0; i < 8; i++) {
		cactus.bitmap[i] = bitmap[i];
	}
	GPIO_escreveBitmapLCD (CACTUS_CHAR, cactus.bitmap);
}

Cactus getCactus (void)
{
	return cactus;
}

void setCactusPosition (uint8_t x)
{
	cactus.x = x;
}

void renderCactus (void)
{
	uint8_t cactus_line[17];
	uint8_t i;
	static uint8_t x = -1;
	if(cactus.x != x) {
		x = cactus.x;
		for(i = 0; i < 16; i++) {
			if (i == x) {
				cactus_line[i] = CACTUS_CHAR;
			} else {
				cactus_line[i] = ' ';
			}
		}
		cactus_line[1] = cactus_line[i] = 0;
		GPIO_escreveStringLCD (CACTUS_BASE_ADDR, cactus_line);
		GPIO_escreveStringLCD (CACTUS_BASE_ADDR+2, cactus_line+2);
	}
}



/*!
 * @file util.c
 * @brief Este modulo contem as funcoes de uso frequente
 * @author Wu Shin Ting
 * @date 17/09/2022
 */

#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "util.h"

void delay_10us (uint32_t multiplos)
{
	__asm__ (
			"mov  r3, #0\n\t"
			"iteracao:\n\t"

			"mov	r2, #26\n\t"
			"laco:\n\t"
			"add		r3, #0\n\t"
			"sub		r3, #0\n\t"
			"add		r3, #0\n\t"
			"sub		r3, #0\n\t"
			"add		r3, #0\n\t"
			"sub 		r2, #1\n\t"

			"bne 	laco\n\t"

			"sub	%0, #1\n\t"
			"bne	iteracao\n\t"

			:
			: "r" (multiplos)			 //multiplos recebe o codigo %0
			: "r2","r3" //os registradores usados no escopo __asm__
			  );
}

char *itoa (int32_t n, char *string, uint8_t b)
{
	char sinal;
	unsigned short i, j, a;
	unsigned int m;
	
	if (n == 0) {
		///< Tratamento do caso especial
		string[0] = '0';
		string[1] = '\0';
		return string;
	}
	
	if (n < 0) sinal = 1;
	else sinal = 0;
	
	/*!
	 * Converter para codigos ASCII, digito por digito, de menos 
	 * significativo para o mais
	 */ 
	i = 0;
	m = abs(n);
	
	while (m != 0) {
		a = m%b;
		string[i+sinal] = (a>9)?(a-10)+'A' : a+'0';
		i++;
		m = m/b;
	}
	string[i+sinal] = '\0';			///< Incluir terminador
	
	///< Reverter a sequencia
	j = strlen(string)-1;
	i = sinal;
			
	while (j > i) {
		char tmp = string[i];
		string[i] = string[j];
		string[j] = tmp;
		i++;
		j--;
	}
	
	///< Adicionar o sinal negativo caso necessario
	if (sinal) string[0] = '-';
	
	return string;
}

char *ftoa(float v, char *string) {
	int32_t truncado;
	float deslocado = (v * 100);
	truncado = (int32_t)deslocado;
	float resto = v * 100. - truncado;
	if (resto > 0.5) {
		truncado++;
	}
	if (truncado >= 100) {
		truncado = 100;
	}
	char inteiro[4];
	char frac[3];
	itoa(truncado/100, inteiro, 10);
	itoa(truncado%100, frac, 10);
	switch(strlen(inteiro)) {
		case 1:
			strcpy(string, "  ");
			break;
		case 2:
			strcpy(string, " ");
			break;
		case 3:
			strcpy(string, "");
			break;
	}
	strcat(string, inteiro);
	strcat(string, ".");
	switch(strlen(frac)) {
		case 1:
			strcat(string, "0");
			break;
	}
	strcat(string, frac);
	return string;
}

char *ttoa (uint32_t seconds, char *string)
{
	uint32_t dd, hh, mm, ss;

	s2dhms (seconds, &dd, &hh, &mm, &ss);
	
	string[2] = string[5] = ':';    // inserir os espacadores
	string[8] = '\0';				// terminador

	if (hh > 23) {
		//!< horario invalido: FF:FF:FF
		string[0] = string[1] = string[3] = string[4] = string[6] = string[7] = 'F';
	}
	
	string[0] = (hh < 10)? '0': (hh/10)+'0';
	string[1] = hh%10+'0';
	
	string[3] = (mm < 10)? '0': (mm/10)+'0';
	string[4] = mm%10+'0';
	
	string[6] = (ss < 10)? '0': (ss/10)+'0';
	string[7] = ss%10+'0';	
	
	return string;
}

void s2dhms (uint32_t segundos, uint32_t *DD, uint32_t *HH, uint32_t *MM, uint32_t *SS)
{
	*DD = segundos/86400;

	uint32_t sec = segundos%86400;
	
	*SS = sec%60;
	
	*MM = (sec/60)%60;
	
	*HH = sec/3600;
	
}

void dhms2s (uint8_t DD, uint8_t HH, uint8_t MM, uint8_t SS, uint32_t *segundos)
{
	*segundos = DD*86400+HH*3600+MM*60+SS;
}


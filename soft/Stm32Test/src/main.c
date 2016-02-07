/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f30x.h"

void delay(int time) {
	int i;
	for (i = 0; i < time * 4000; i++) {
	}
}

int main(void) {
	GPIO_InitTypeDef gpio; // obiekt gpio z konfiguracja portow GPIO

	RCC_AHBPeriphClockCmd(
			RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN
					| RCC_AHBENR_GPIODEN, ENABLE); // uruchomienie zegara modulu GPIO

	GPIO_StructInit(&gpio); // domyslna konfiguracja
	gpio.GPIO_Pin = GPIO_Pin_5; // konfigurujemy pin 5
	gpio.GPIO_Mode = GPIO_Mode_OUT; // jako wyjscie
	GPIO_Init(GPIOA, &gpio); // inicjalizacja modulu GPIOA

	while (1) {
		GPIO_SetBits(GPIOA, GPIO_Pin_5); // zapalenie diody
		delay(100);
		GPIO_ResetBits(GPIOA, GPIO_Pin_5); // zgaszenie diody
		delay(400);
	}
}

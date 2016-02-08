/**
 ******************************************************************************
 * @file    outputs.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-08
 * @brief   Basic outputs
 ******************************************************************************
 */

#include "outputs.h"
#include "config.h"
#include <stdbool.h>

GPIO_TypeDef * const ledGpios[LED_NUMBER] = LED_GPIOS;
uint16_t const ledPins[LED_NUMBER] = LED_PINS;
BitAction const ledActiveStates[LED_NUMBER] = LED_ACTIVE_STATES;

uint8_t outputsInit(void) {
	GPIO_InitTypeDef gpio;
	uint_fast8_t i;

	// LED pins - low speed outputs
	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	for (i = 0; i < LED_NUMBER; i++) {

		gpio.GPIO_Pin = ledPins[i];
		GPIO_Init(ledGpios[i], &gpio);
	}

	return 0;
}

uint8_t ledCmd(uint8_t led, FunctionalState state) {
	BitAction bitState;
	bitState = !((bool) ledActiveStates[led] ^ (bool) state); // negate if active low
	if (led < LED_NUMBER) {
		GPIO_WriteBit(ledGpios[led], ledPins[led], bitState);
		return 0;
	} else {
		return 1;
	}
}

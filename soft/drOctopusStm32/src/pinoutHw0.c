/**
 ******************************************************************************
 * @file    pinoutHW0.c
 * @author  piotr@nicecircuits.com
 * @date    2016-lut-07
 * @brief
 ******************************************************************************
 */

#include "pinoutHw0.h"

uint8_t portInit(void) {
	// initialize all GPIO clocks (power consumption is not important)
	RCC_AHBPeriphClockCmd(
			RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN
					| RCC_AHBENR_GPIODEN | RCC_AHBENR_GPIOFEN, ENABLE);
	return 0;
}

uint8_t debugClockEnable(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN, ENABLE);
	return 0;
}

uint8_t debugGpioAfSetup(void){
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource2, GPIO_AF_7);
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource3, GPIO_AF_7);
	return 0;
}

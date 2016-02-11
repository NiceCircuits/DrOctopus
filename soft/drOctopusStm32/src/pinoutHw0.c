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
	// enable debug USART and DMA peripheral clock
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_USART2EN, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBENR_DMA1EN, ENABLE);
	// initialize USART pins alternative functions
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource2, GPIO_AF_7);
	GPIO_PinAFConfig(DEBUG_GPIO, GPIO_PinSource3, GPIO_AF_7);
	// enable PWM timer peripheral clock
	RCC_APB1PeriphClockCmd(RCC_APB1ENR_TIM3EN, ENABLE);
	// initialize PWM pins alternative functions
	GPIO_PinAFConfig(PWM_GPIO, GPIO_PinSource6, GPIO_AF_2);
	GPIO_PinAFConfig(PWM_GPIO, GPIO_PinSource7, GPIO_AF_2);
	GPIO_PinAFConfig(PWM_GPIO, GPIO_PinSource8, GPIO_AF_2);
	GPIO_PinAFConfig(PWM_GPIO, GPIO_PinSource9, GPIO_AF_2);
	return 0;
}

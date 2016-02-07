/**
 ******************************************************************************
 * @file    debug.c
 * @author  piotr@nicecircuits.com
 * @date    2016-02-07
 * @brief
 ******************************************************************************
 */

#include "debug.h"
#include "config.h"

uint8_t debugInit(void) {
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;

	// TX pin - alternative low speed output
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = DEBUG_TX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(DEBUG_GPIO, &gpio);

	// RX pin - input
	gpio.GPIO_Pin = DEBUG_RX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(DEBUG_GPIO, &gpio);

	// Setup alternate functions of GPIO
	debugGpioAfSetup();

	debugClockEnable();
	USART_StructInit(&uart);
	uart.USART_BaudRate = DEBUG_BUADRATE;
	USART_Init(DEBUG_USART, &uart);
	USART_Cmd(DEBUG_USART, ENABLE);

	return 0;
}

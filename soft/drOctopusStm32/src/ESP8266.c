/**
 ******************************************************************************
 * @file    ESP8266.c
 * @author  piotr@nicecircuits.com
 * @date    2016-03-01
 * @brief
 ******************************************************************************
 */

#include "esp8266.h"
#include "config.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// ---------- Private variables. ----------
/// ESP8266 Tx USART DMA buffer.
static char espUsartTxBuffer[ESP_TX_BUFFER_SIZE] = "";
/// ESP8266 Rx USART DMA buffer.
static char espUsartRxBuffer[ESP_RX_BUFFER_SIZE] = "";
/// ESP8266 transmit start flag. Set to one after starting first debug print.
static bool espTxStartFlag = 0;

// ---------- Public functions. ----------
uint_fast8_t espInit(void) {
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	DMA_InitTypeDef dma;

	// TX pin - alternative low speed output
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = ESP_TX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(ESP_GPIO, &gpio);

	// RX pin - input
	gpio.GPIO_Pin = ESP_RX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(ESP_GPIO, &gpio);

	// Alternate function registers of GPIO are set up in portInit() function

	// Setup USART
	// Peripheral clock is enabled in portInit() function
	USART_StructInit(&uart);
	uart.USART_BaudRate = ESP_BUADRATE;
	USART_Init(ESP_USART, &uart);
	USART_Cmd(ESP_USART, ENABLE);
	USART_DMACmd(ESP_USART, USART_DMAReq_Tx, ENABLE);

	// Setup DMA
	// Clock enabled in debugClockEnable() function
	DMA_Cmd(ESP_TX_DMA, DISABLE);
	DMA_StructInit(&dma);
	dma.DMA_DIR = DMA_DIR_PeripheralDST;
	dma.DMA_M2M = DMA_M2M_Disable;
	dma.DMA_MemoryBaseAddr = (uint32_t) espUsartTxBuffer;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_Mode = DMA_Mode_Normal;
	dma.DMA_PeripheralBaseAddr = (uint32_t) &ESP_USART->TDR;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_Priority = DMA_Priority_Medium;
	dma.DMA_BufferSize = 1;
	DMA_Init(ESP_TX_DMA, &dma);
	return 0;
}

uint_fast8_t espPrintf(const char* format, ...) {
	size_t len;
	va_list arglist;
	while (espTxStartFlag && DMA_GetFlagStatus(ESP_DMA_TX_TC_FLAG) == 0) {
		// Wait until previous transfer complete (if any has started).
	}
	espTxStartFlag = 1; // Indicate, that transfer has started.
	// pass variable argument list to vsnprintf function to format
	// formatted string will be available in espUsartTxBuffer
	va_start(arglist, format);
	len = vsnprintf(espUsartTxBuffer, ESP_TX_BUFFER_SIZE - 2, format, arglist);
	va_end(arglist);
	// setup DMA transfer
	DMA_Cmd(ESP_TX_DMA, DISABLE);
	DMA_SetCurrDataCounter(ESP_TX_DMA, len);
	DMA_ClearFlag(ESP_DMA_TX_TC_FLAG);
	DMA_Cmd(ESP_TX_DMA, ENABLE);
	return 0;
}

#if TEST_MODE == TEST_MODE_ESP

int main(void) {
	defaultInit();
	for (;;) {
		// Finished, do nothing.
	}
}
#endif // TEST_MODE == TEST_MODE_ESP

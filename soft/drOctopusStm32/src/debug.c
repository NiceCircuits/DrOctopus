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
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/// Max number of debug sources available.
#define DEBUG_SOURCES_MAX_NUMBER (20)
/// Maximum length of debug source name string.
#define DEBUG_SOURCE_NAME_MAX_LENGTH (20)
/// Debug USART DMA buffer.
static char debugUsartBuffer[DEBUG_BUFFER_SIZE] = "UART buffer empty";
/// Array of debug sources names.
static const char* debugSourcesNames[DEBUG_SOURCES_MAX_NUMBER];
/// Array of enable state of debug sources
static FunctionalState debugSourcesEnabled[DEBUG_SOURCES_MAX_NUMBER];
/// Number of configured debug sources
static debugSource_t debugSourcesNumber = 0;

uint8_t debugInit(void) {
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	DMA_InitTypeDef dma;

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

	// Alternate function registers of GPIO are set up in portInit() function

	// Setup USART
	// Peripheral clock is enabled in portInit() function
	USART_StructInit(&uart);
	uart.USART_BaudRate = DEBUG_BUADRATE;
	USART_Init(DEBUG_USART, &uart);
	USART_Cmd(DEBUG_USART, ENABLE);
	USART_DMACmd(DEBUG_USART, USART_DMAReq_Tx, ENABLE);

	// Setup DMA
	// Clock enabled in debugClockEnable() function
	DMA_Cmd(DEBUG_DMA, DISABLE);
	DMA_StructInit(&dma);
	dma.DMA_DIR = DMA_DIR_PeripheralDST;
	dma.DMA_M2M = DMA_M2M_Disable;
	dma.DMA_MemoryBaseAddr = (uint32_t) debugUsartBuffer;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_Mode = DMA_Mode_Normal;
	dma.DMA_PeripheralBaseAddr = (uint32_t) &DEBUG_USART->TDR;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_Priority = DMA_Priority_Low;
	dma.DMA_BufferSize = 1;
	DMA_Init(DEBUG_DMA, &dma);
	return 0;
}

uint8_t debugPrintln(debugSource_t source, const char* format, ...) {
	size_t len;
	va_list arglist;
	if ((source < 0) || (source >= debugSourcesNumber)) {
		// no such source configured
		return -1;
	} else if (debugSourcesEnabled[source] == DISABLE) {
		// source disabled, do not print anything
		return 0;
	} else {
		// insert source name into USART DMA buffer
		len = strlcpy(debugUsartBuffer, debugSourcesNames[source],
		DEBUG_SOURCE_NAME_MAX_LENGTH);
		if (len >= DEBUG_SOURCE_NAME_MAX_LENGTH) {
			len = DEBUG_SOURCE_NAME_MAX_LENGTH - 1;
		}
		debugUsartBuffer[len] = ':';
		len++;
		debugUsartBuffer[len] = ' ';
		len++;
		// pass variable argument list to vsnprintf function to format
		// formatted string will be available in debugBuffer
		va_start(arglist, format);
		len = len
				+ vsnprintf(debugUsartBuffer + len, DEBUG_BUFFER_SIZE - len - 2,
						format, arglist);
		va_end(arglist);
		// add new line
		debugUsartBuffer[len] = '\r';
		len++;
		debugUsartBuffer[len] = '\n';
		len++;
		// setup DMA transfer
		DMA_Cmd(DEBUG_DMA, DISABLE);
		DMA_SetCurrDataCounter(DEBUG_DMA, len);
		DMA_Cmd(DEBUG_DMA, ENABLE);
		return 0;
	}
}

debugSource_t debugNewSource(const char* name) {
	if (debugSourcesNumber >= DEBUG_SOURCES_MAX_NUMBER) {
		// no more sources available
		return -1;
	} else {
		debugSourcesNames[debugSourcesNumber] = name;
		debugSourcesEnabled[debugSourcesNumber] = DISABLE;
		debugSourcesNumber++;
		return debugSourcesNumber - 1;
	}
}

uint8_t debugSourceEnable(debugSource_t source, FunctionalState enabled) {
	if ((source < 0) || (source >= debugSourcesNumber)) {
		// no such source configured
		return 1;
	} else if (!IS_FUNCTIONAL_STATE(enabled)) {
		// invalid value
		return 2;
	} else {
		debugSourcesEnabled[source] = enabled;
		return 0;
	}
}

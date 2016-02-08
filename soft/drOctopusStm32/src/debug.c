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

char debugBuffer[DEBUG_BUFFER_SIZE] = "DMA buffer empty";

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

	// Setup alternate functions of GPIO
	debugGpioAfSetup();

	// Setup USART
	debugClockEnable();
	USART_StructInit(&uart);
	uart.USART_BaudRate = DEBUG_BUADRATE;
	USART_Init(DEBUG_USART, &uart);
	USART_Cmd(DEBUG_USART, ENABLE);
	USART_DMACmd(DEBUG_USART, USART_DMAReq_Tx, ENABLE);

	// Setup DMA
	// Clock enabled in debugClockEnable() function
	DMA_StructInit(&dma);
	dma.DMA_DIR = DMA_DIR_PeripheralDST;
	dma.DMA_M2M = DMA_M2M_Disable;
	dma.DMA_MemoryBaseAddr = (uint32_t) debugBuffer;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_Mode = DMA_Mode_Normal;
	dma.DMA_PeripheralBaseAddr = (uint32_t) &DEBUG_USART->TDR;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_Priority = DMA_Priority_Low;
	dma.DMA_BufferSize = 16;
	DMA_Init(DEBUG_DMA, &dma);

	DMA_Cmd(DEBUG_DMA, ENABLE);

	return 0;
}

/**
 ******************************************************************************
 * @file    espStream.cpp
 * @author  piotr@nicecircuits.com
 * @date    2016-03-21
 * @brief
 ******************************************************************************
 */

#include "espStream.h"

uint_fast8_t espStream_t::print(const char* format, ...) {
	size_t len;
	va_list arglist;
	while (txStartFlag && DMA_GetFlagStatus(ESP_DMA_TX_TC_FLAG) == 0) {
		// Wait until previous transfer complete (if any has started).
	}
	txStartFlag = 1; // Indicate, that transfer has started.
	// pass variable argument list to vsnprintf function to format
	// formatted string will be available in espUsartTxBuffer
	va_start(arglist, format);
	len = vsnprintf(txBuffer, ESP_TX_BUFFER_SIZE - 2, format, arglist);
	va_end(arglist);
	// setup DMA transfer
	DMA_Cmd(ESP_TX_DMA, DISABLE);
	DMA_SetCurrDataCounter(ESP_TX_DMA, (uint16_t) len);
	DMA_ClearFlag(ESP_DMA_TX_TC_FLAG);
	DMA_Cmd(ESP_TX_DMA, ENABLE);
	return len;
}

size_t espStream_t::write(uint8_t byte) {
	while (txStartFlag && DMA_GetFlagStatus(ESP_DMA_TX_TC_FLAG) == 0) {
		// Wait until previous transfer complete (if any has started).
	}
	txStartFlag = 1; // Indicate, that transfer has started.
	txBuffer[0] = byte;
	// setup DMA transfer
	DMA_Cmd(ESP_TX_DMA, DISABLE);
	DMA_SetCurrDataCounter(ESP_TX_DMA, 1);
	DMA_ClearFlag(ESP_DMA_TX_TC_FLAG);
	DMA_Cmd(ESP_TX_DMA, ENABLE);
	return 1;
}

int espStream_t::available() {
	return this->rxBuffer.count;
}

char espStream_t::read() {
	char data = 0;
	this->rxBuffer.pop(&data);
	return data;
}

uint_fast8_t espStream_t::init() {
	GPIO_InitTypeDef gpio;
	USART_InitTypeDef uart;
	DMA_InitTypeDef dma;
	NVIC_InitTypeDef nvic;

	// BOOT and ENABLE pins
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_PuPd = GPIO_PuPd_NOPULL;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_Pin = ESP_BOOT_PIN;
	GPIO_Init(ESP_BOOT_GPIO, &gpio);
	bootPinCmd(Bit_SET); // Disable bootloader.

	gpio.GPIO_Pin = ESP_EN_PIN;
	GPIO_Init(ESP_EN_GPIO, &gpio);
	enablePinCmd(Bit_RESET); // Reset chip.

	// TX pin - alternative low speed output
	GPIO_StructInit(&gpio);
	gpio.GPIO_Pin = ESP_TX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(ESP_GPIO, &gpio);

	// RX pin - input
	gpio.GPIO_Pin = ESP_RX_PIN;
	gpio.GPIO_Mode = GPIO_Mode_AF;
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
	dma.DMA_MemoryBaseAddr = (uint32_t) txBuffer;
	dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma.DMA_Mode = DMA_Mode_Normal;
	dma.DMA_PeripheralBaseAddr = (uint32_t) &ESP_USART->TDR;
	dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	dma.DMA_Priority = DMA_Priority_Medium;
	dma.DMA_BufferSize = 1;
	DMA_Init(ESP_TX_DMA, &dma);

	// Init USART Receive data register not empty interrupt.
	nvic.NVIC_IRQChannel = (ESP_IRQ);
	nvic.NVIC_IRQChannelPriority = 0;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	USART_ITConfig(ESP_USART, USART_IT_RXNE, ENABLE);

	delayMs(10);
	enablePinCmd(Bit_SET); // Enable chip.
	return 0;
}

uint_fast8_t espStream_t::pushRxData(char data) {
	return this->rxBuffer.push(data);
	delayMs(10);
	enablePinCmd(Bit_SET); // Enable chip.
}

void espStream_t::enterProgrammingMode() {
	GPIO_InitTypeDef gpio;
	BitAction rx, tx;
	enablePinCmd(Bit_RESET); // Reset chip.
	bootPinCmd(Bit_RESET); // Enable bootloader.
	// Configure GPIO.
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Pin = ESP_TX_PIN;
	GPIO_Init(ESP_GPIO, &gpio);
	gpio.GPIO_Pin = DEBUG_TX_PIN;
	GPIO_Init(DEBUG_GPIO, &gpio);

	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_Pin = ESP_RX_PIN;
	GPIO_Init(ESP_GPIO, &gpio);
	gpio.GPIO_Pin = DEBUG_RX_PIN;
	GPIO_Init(DEBUG_GPIO, &gpio);

	delayMs(100);
	enablePinCmd(Bit_SET); // Enable chip.
	// Transfer data from debug USART to ESP USART and back.
	for (;;) {
#if defined(HW_VERSION) && HW_VERSION == HW_VERSION1
		GPIO_WriteBit(ESP_GPIO, ESP_TX_PIN,
				(BitAction) (((DEBUG_GPIO->IDR) & DEBUG_RX_PIN) != 0));
		GPIO_WriteBit(DEBUG_GPIO, DEBUG_TX_PIN,
				(BitAction) (((ESP_GPIO->IDR) & ESP_RX_PIN) != 0));
#else // #if defined(HW_VERSION) && HW_VERSION == HW_VERSION1
#error "HW version not supported or not set!"
#endif // #if defined(HW_VERSION) && HW_VERSION == HW_VERSION1
	}
	for (;;) {
		tx = (BitAction) GPIO_ReadInputDataBit(DEBUG_GPIO, DEBUG_RX_PIN);
		rx = (BitAction) GPIO_ReadInputDataBit(ESP_GPIO, ESP_RX_PIN);
		GPIO_WriteBit(ESP_GPIO, ESP_TX_PIN, tx);
		GPIO_WriteBit(DEBUG_GPIO, DEBUG_TX_PIN, rx);
	}
}

void espStream_t::enablePinCmd(BitAction state) {
	GPIO_WriteBit(ESP_EN_GPIO, ESP_EN_PIN, state);
}

void espStream_t::bootPinCmd(BitAction state) {
	GPIO_WriteBit(ESP_BOOT_GPIO, ESP_BOOT_PIN, state);
}

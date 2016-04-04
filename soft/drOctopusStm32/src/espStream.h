/**
 ******************************************************************************
 * @file    espStream.h
 * @author  piotr@nicecircuits.com
 * @date    2016-03-21
 * @brief
 ******************************************************************************
 */
#ifndef ESPSTREAM_H_
#define ESPSTREAM_H_

#include <cstdint>
#include <cstdarg>
#include <cstdio>
#include <cstdbool>
#include "ELClient.h"
#include "espUsartRxBuffer.h"
extern "C" {
#include "config.h"
#include "delay.h"
#include "outputs.h"
}

class espStream_t: public ELStream {
public:
	size_t print(const char* format, ...);
	size_t write(uint8_t);
	int available();
	char read();
	uint_fast8_t init();
	uint_fast8_t pushRxData(char data);
	/**
	 * Enter ESP8266 programming mode. It creates connection from debug USART to
	 * ESP USART and enables ESP bootloader.
	 */
	void enterProgrammingMode();
	~espStream_t(){
	}
private:
	bool txStartFlag = 0;
	/// ESP8266 Rx USART DMA buffer.
	espUsartRxBuffer_t rxBuffer;
	/// ESP8266 Tx USART DMA buffer.
	char txBuffer[ESP_TX_BUFFER_SIZE] = "";
	void enablePinCmd(BitAction state);
	void bootPinCmd(BitAction state);
};

#endif /* ESPSTREAM_H_ */

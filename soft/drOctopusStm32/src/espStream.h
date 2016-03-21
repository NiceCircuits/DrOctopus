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
}

class espStream_t: public ELStream {
public:
	size_t print(const char* format, ...);
	size_t write(uint8_t);
	int available();
	int read();
	uint_fast8_t init();
private:
	bool txStartFlag=0;
	/// ESP8266 Rx USART DMA buffer.
	espUsartRxBuffer_t rxBuffer;
	/// ESP8266 Tx USART DMA buffer.
	char txBuffer[ESP_TX_BUFFER_SIZE] = "";
};


#endif /* ESPSTREAM_H_ */

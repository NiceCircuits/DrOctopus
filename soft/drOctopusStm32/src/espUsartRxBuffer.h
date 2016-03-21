/**
  ******************************************************************************
  * @file    espUsartRxBuffer.h
  * @author  piotr@nicecircuits.com
  * @date    2016-03-21
  * @brief   
  ******************************************************************************
*/
#ifndef ESPUSARTRXBUFFER_H_
#define ESPUSARTRXBUFFER_H_

extern "C" {
#include "config.h"
}

class espUsartRxBuffer_t{
public:
	char buffer[ESP_RX_BUFFER_SIZE];
	uint_fast16_t head = 0;
	uint_fast16_t tail = 0;
	uint_fast16_t count = 0;
	uint_fast8_t push(char data);
	uint_fast8_t pop(char *data);
};

#endif /* ESPUSARTRXBUFFER_H_ */

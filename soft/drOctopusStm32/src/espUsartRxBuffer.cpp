/**
 ******************************************************************************
 * @file    espUsartRxBuffer.cpp
 * @author  piotr@nicecircuits.com
 * @date    2016-03-21
 * @brief
 ******************************************************************************
 */

#include "espUsartRxBuffer.h"

uint_fast8_t espUsartRxBuffer_t::push(char data) {
	// If cicular buffer is full
	if (this->count >= ESP_RX_BUFFER_SIZE) {
		return 1;  // return an error
	}
	uint16_t next = this->head;
	this->buffer[next] = data;
	next++;
	if (next >= ESP_RX_BUFFER_SIZE) {
		next = 0;
	}
	this->head = next;
	this->count++;
	//updateDebugPin();
	return 0;
}

uint_fast8_t espUsartRxBuffer_t::pop(char *data) {
	// if the head isn't ahead of the tail, we don't have any characters
	if (this->count == 0) {
		return 1;  // quit with an error
	}
	uint8_t next = this->tail;
	*data = this->buffer[next];
	next++;
	if (next >= ESP_RX_BUFFER_SIZE) {
		next = 0;
	}
	this->tail = next;
	this->count--;
	//updateDebugPin();
	return 0;
}

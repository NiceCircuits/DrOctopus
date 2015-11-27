/*
 * commandBuffer.cpp
 *
 *  Created on: 2015-11-26
 *      Author: Piotr Nowicki
 */

#include "commandBuffer.h"
#include "debug.h"

#define COMMAND_BUFFER_LENGTH (8)

typedef struct {
	command_t buffer[COMMAND_BUFFER_LENGTH];
	uint8_t head;
	uint8_t tail;
} commandBuffer_t;

commandBuffer_t commandBuffer;

int commandBufferPush(command_t* data) {
	uint8_t next = commandBuffer.head + 1;
	if (next >= COMMAND_BUFFER_LENGTH)
		next = 0;

	debugPrintln(data->timestamp);
	// Cicular buffer is full
	if (next == commandBuffer.tail) {
		debugPin((COMMAND_BUFFER_LENGTH - 1) * 256 / COMMAND_BUFFER_LENGTH);
		return -1;  // quit with an error
	}

	memcpy(&commandBuffer.buffer[commandBuffer.head], data, sizeof(command_t));
	commandBuffer.head = next;
	debugPin(next * (256 / COMMAND_BUFFER_LENGTH));
	return 0;
}

int commandBufferPop(command_t* data) {
	// if the head isn't ahead of the tail, we don't have any characters
	if (commandBuffer.head == commandBuffer.tail) {
		debugPin(0);
		return -1;  // quit with an error
	}

	memcpy(data, &commandBuffer.buffer[commandBuffer.tail], sizeof(command_t));

	int next = commandBuffer.tail + 1;
	if (next >= COMMAND_BUFFER_LENGTH) {
		next = 0;
	}

	commandBuffer.tail = next;

	return 0;
}

void commandBufferInit() {
	commandBuffer.head = 0;
	commandBuffer.tail = 0;
}


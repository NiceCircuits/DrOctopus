/*
 * commandBuffer.cpp
 *
 *  Created on: 2015-11-26
 *      Author: Piotr Nowicki
 */

#include "commandBuffer.h"
#include "debug.h"

#define COMMAND_BUFFER_LENGTH (16)

typedef struct {
	command_t buffer[COMMAND_BUFFER_LENGTH];
	uint8_t head = 0;
	uint8_t tail = 0;
	uint8_t count = 0;
} commandBuffer_t;

commandBuffer_t commandBuffer;

void updateDebugPin() {
	debugPin(constrain(commandBuffer.count * (256 / COMMAND_BUFFER_LENGTH), 0, 255));
}

int8_t commandBufferPush(command_t* data) {
	debugPrint("push: ");
	debugPrintln(data->timestamp);
	// If cicular buffer is full
	if (commandBuffer.count >= COMMAND_BUFFER_LENGTH) {
		return -1;  // quit with an error
	}
	uint8_t next = commandBuffer.head;
	memcpy(&commandBuffer.buffer[next], data, sizeof(command_t));
	next++;
	if (next >= COMMAND_BUFFER_LENGTH) {
		next = 0;
	}
	commandBuffer.head = next;
	commandBuffer.count++;
	updateDebugPin();
	return 0;
}

int8_t commandBufferPop(command_t* data) {
	// if the head isn't ahead of the tail, we don't have any characters
	if (commandBuffer.count == 0) {
		return -1;  // quit with an error
	}
	uint8_t next = commandBuffer.tail;
	memcpy(data, &commandBuffer.buffer[next], sizeof(command_t));
	next++;
	if (next >= COMMAND_BUFFER_LENGTH) {
		next = 0;
	}
	commandBuffer.tail = next;
	commandBuffer.count--;
	updateDebugPin();
	return 0;
}

void commandBufferInit() {
}


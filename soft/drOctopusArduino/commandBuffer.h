/*
 * commandBuffer.h
 *
 *  Created on: 2015-11-26
 *      Author: Piotr Nowicki
 */

#ifndef COMMANDBUFFER_H_
#define COMMANDBUFFER_H_

#include "servos.h"
#include <Arduino.h>

typedef struct {
	uint32_t timestamp; // time for command to be executed
	int16_t servoPos[N_SERVOS]; // positions of servos to achieve at the timestamp
} command_t;

int commandBufferPush(command_t* data);

int commandBufferPop(command_t* data);

void commandBufferInit();

#endif /* COMMANDBUFFER_H_ */

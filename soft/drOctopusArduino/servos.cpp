/*
 * servos.cpp
 *
 *  Created on: 2015-11-24
 *      Author: Piotr Nowicki
 */
#include <Servo.h>
#include "servos.h"
#include "commandBuffer.h"
#include "time.h"

Servo servo[N_SERVOS];
static command_t lastCommand;

void servosInit() {
	servo[0].attach(7);
	servo[1].attach(8);
	servo[2].attach(9);
	servo[3].attach(10);
	for (uint8_t i = 0; i < N_SERVOS; i++) {
		servo[i].writeMicroseconds(1500);  // set servo to mid-point
		lastCommand.servoPos[i] = 0;
	}
	lastCommand.timestamp = 0;
	pinMode(A3,OUTPUT);
}

void servosLoop() {
	uint32_t now = timeGet();
	if (now >= lastCommand.timestamp) {
		if (commandBufferPop(&lastCommand) >= 0) {
			for (uint8_t i = 0; i < N_SERVOS; i++) {
				servo[i].writeMicroseconds(lastCommand.servoPos[i] + 1500);
			}
			static bool click;
			digitalWrite(A3,click);
			click=!click;
		}
	}
}


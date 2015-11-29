/*
 * time.cpp
 *
 *  Created on: 2015-11-28
 *      Author: Piotr Nowicki
 */

#include <Arduino.h>

static int32_t timeCorrection = 0; // signed

uint32_t timeGet() {
	return (uint32_t) ((int32_t) millis() + timeCorrection);
}

void setTime(uint32_t newTime) {
	timeCorrection = newTime - millis();
}

/*
 * debug.cpp
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#include "debug.h"

#if DEBUG_ENABLE
#define DEBUG_PIN (5F)
void debugPin(uint8_t value) {
	debugPrint("debugPin: ");
	debugPrintln(value);
	analogWrite(DEBUG_PIN, value);
}
#else
#define DEBUG_PIN (-1)
void debugPin(uint8_t value) {}
#endif

#if DEBUG_ENABLE==DEBUG_SOFT_SERIAL
SoftwareSerial debugPort(-1, A3); // RX, TX
void debugInit() {
	debugPort.begin(57600);
	pinMode(DEBUG_PIN,OUTPUT);
}
#elif DEBUG_ENABLE==DEBUG_HARD_SERIAL
void debugInit() {
	Serial.begin(57600);
	pinMode(DEBUG_PIN, OUTPUT);
}
#else // DEBUG_ENABLE
void debugInit() {
}
#endif //DEBUG_ENABLE


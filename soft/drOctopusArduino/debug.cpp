/*
 * debug.cpp
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#include "debug.h"
#include <Arduino.h>

#if DEBUG_ENABLE
SoftwareSerial debugPort(A2, A3); // RX, TX
void debugInit(){
	debugPort.begin(115200);
}
#else // DEBUG_ENABLE
void debugInit(){
}
#endif //DEBUG_ENABLE


/*
 * debug.cpp
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#include "debug.h"
#include <Arduino.h>

#if DEBUG_ENABLE==DEBUG_SOFT_SERIAL
SoftwareSerial debugPort(-1, A3); // RX, TX
void debugInit(){
	debugPort.begin(57600);
}
#elif DEBUG_ENABLE==DEBUG_HARD_SERIAL
void debugInit(){
	// port initilized in wifiInit
}
#else // DEBUG_ENABLE
void debugInit(){
}
#endif //DEBUG_ENABLE


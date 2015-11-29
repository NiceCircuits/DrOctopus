/*
 * debug.h
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <Arduino.h>

// debug port selection
// no debug
#define DEBUG_DISABLED 0
// use dedicated software defined serial port (interferes with servos)
#define DEBUG_SOFT_SERIAL 1
// use existing hardware serial port (the same as ESP module)
#define DEBUG_HARD_SERIAL 2
// select one of options
#ifndef DEBUG_ENABLE
#define DEBUG_ENABLE DEBUG_DISABLED
#define DEBUG_PIN_ENABLE 1
#endif

#if DEBUG_ENABLE==DEBUG_SOFT_SERIAL
#include <SoftwareSerial.h>
extern SoftwareSerial debugPort;

#define debugPrint(n) do{debugPort.print(n);}while(0)
#define debugPrintln(n) do{debugPort.println(n);}while(0)
#elif DEBUG_ENABLE==DEBUG_HARD_SERIAL
#define debugPrint(n) do{Serial.print(n);}while(0)
#define debugPrintln(n) do{Serial.println(n);}while(0)
#else // DEBUG_ENABLE==DEBUG_DISABLED
#define debugPrint(n) do{}while(0)
#define debugPrintln(n) do{}while(0)
#endif //DEBUG_ENABLE

void debugInit();

void debugPin(uint8_t value);

#endif /* DEBUG_H_ */

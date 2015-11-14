/*
 * debug.h
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <SoftwareSerial.h>

#define DEBUG_ENABLE 1

#if DEBUG_ENABLE
extern SoftwareSerial debugPort;

#define debugPrint(n) do{debugPort.print(n);}while(0)
#define debugPrintln(n) do{debugPort.println(n);}while(0)

#else // DEBUG_ENABLE
#define debugPrint(n) do{}while(0)
#define debugPrintln(n) do{}while(0)
#endif //DEBUG_ENABLE

void debugInit();

#endif /* DEBUG_H_ */

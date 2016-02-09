/**
  ******************************************************************************
  * @file    debug.h
  * @author  piotr@nicecircuits.com
  * @date    2016-02-07
  * @brief   
  ******************************************************************************
*/
#ifndef DEBUG_H_
#define DEBUG_H_

#include <inttypes.h>

typedef int8_t debugSource_t;

uint8_t debugInit(void);

/**
 * Print to debug UART. Uses printf format and variable list of arguments.
 * Can be enabled or disabled.
 * @param source debug source identifier.
 * @param format printf-like format string.
 * @return
 */
uint8_t debugPrint(debugSource_t source, const char* format, ...);

#endif /* DEBUG_H_ */

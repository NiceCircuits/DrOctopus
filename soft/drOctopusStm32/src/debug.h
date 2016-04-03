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
#include "config.h"
#include <stdbool.h>

typedef int8_t debugSource_t;

/**
 * Initialize debug UART
 * @return 0 if OK
 */
uint_fast8_t debugInit(void);

/**
 * Print new line to debug UART. Uses printf format and variable list of
 * arguments.
 *
 * @param source debug source identifier.
 * @param format printf-like format string.
 * @return 0 if OK
 */
uint_fast8_t debugPrintln(debugSource_t source, const char* format, ...);

/**
 * Prints raw string to debug UART (no prefix and newline). Uses printf format
 * and variable list of arguments.
 * @param source debug source identifier.
 * @param format printf-like format string.
 * @return 0 if OK
 */
uint_fast8_t debugPrintRaw(debugSource_t source, const char* format, ...);

/**
 * Add new debug source. It can be than used with debugPrint, enabled and
 * disabled. Disabled initially.
 * @param name name of new source, used as prefix for debug print.
 * @return new source identifier (equal or greater than zero). Negative number
 * if error.
 */
debugSource_t debugNewSource(const char* name);

/**
 * Enable/disable debug source.
 * @param source identifier of source.
 * @param enabled new enabled state.
 * @return 0 if OK
 */
uint_fast8_t debugSourceEnable(debugSource_t source, FunctionalState enabled) ;
#endif /* DEBUG_H_ */

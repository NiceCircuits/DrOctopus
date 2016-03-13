/**
 ******************************************************************************
 * @file    ESP8266.h
 * @author  piotr@nicecircuits.com
 * @date    2016-03-01
 * @brief
 ******************************************************************************
 */
#ifndef ESP8266_H_
#define ESP8266_H_

#include <inttypes.h>

/**
 * Initialize ESP8266 module.
 * @return 0 if OK.
 */
uint_fast8_t espInit(void);

/**
 * Print to ESP8266.
 * @param format printf-like format string.
 * @return
 */
uint_fast8_t espPrintf(const char* format, ...);

#endif /* ESP8266_H_ */

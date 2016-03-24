/**
 ******************************************************************************
 * @file    oled.h
 * @author  piotr@nicecircuits.com
 * @date    2016-02-22
 * @brief   OLED display library.
 ******************************************************************************
 */
#ifndef OLED_H_
#define OLED_H_

#include "u8g.h"
#include "config.h"
#include <stdint.h>

// Initialize OLED display.
uint_fast8_t oledInit(void);

#endif /* OLED_H_ */

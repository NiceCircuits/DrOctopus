/*
 * oled.h
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#ifndef OLED_H_
#define OLED_H_

void oledInit(void);

void oledLoop(void);

void oledCls();

void oledPrintLine(const char *str, int line);

#endif /* OLED_H_ */

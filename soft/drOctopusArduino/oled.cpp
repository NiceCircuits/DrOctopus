/*
 * oled.cpp
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#include <Arduino.h>
#include <Wire.h>
#include <U8glib.h>
#include "oled.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_DEV_0);	// I2C

#define OLED_LINES 4
#define OLED_MAX_LINE 24
char oledText[OLED_LINES][OLED_MAX_LINE + 1];

void oledInit(void) {
	// u8g.setRot180();
	oledCls();
	for (uint8_t i = 0; i < OLED_LINES; i++) {
		memset(oledText[i], '\0', OLED_MAX_LINE + 1);
	}
}

void oledLoop(void) {
	u8g.firstPage();
	do {
		for (int i = 0; i < OLED_LINES; i++) {
			int L = strlen(oledText[i]);
			if (L < 15) {
				u8g.setFont(u8g_font_9x15); // 2959 bytes
//			} else if (L < 17) {
//				u8g.setFont(u8g_font_8x13); // 2152 bytes
			} else if (L < 19) {
				u8g.setFont(u8g_font_7x13); // 2157 bytes
//			} else if (L < 22) {
//				u8g.setFont(u8g_font_6x13); // 2160 bytes
			} else {
				u8g.setFont(u8g_font_5x8); // 1693 bytes
			}
			u8g.drawStr(0, 15 + 16 * i, oledText[i]);
		}
	} while (u8g.nextPage());
}

void oledCls() {
	for (int i = 0; i < OLED_LINES; i++) {
		oledText[i][0] = '\0';
	}
}

void oledPrintLine(const char *str, int line) {
	strncpy(oledText[line], str, OLED_MAX_LINE);
}


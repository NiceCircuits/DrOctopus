/*
 * debug.cpp
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#include "debug.h"

#if DEBUG_PIN_ENABLE
#define DEBUG_PIN (5)
void debugPin(uint8_t value) {
	debugPrint("debugPin: ");
	debugPrintln(value);
	analogWrite(DEBUG_PIN, value);
}
#else
#define DEBUG_PIN (-1)
void debugPin(uint8_t value) {}
#endif

#if DEBUG_ENABLE==DEBUG_SOFT_SERIAL
SoftwareSerial debugPort(-1, A3); // RX, TX
void debugInit() {
	debugPort.begin(57600);
	pinMode(DEBUG_PIN,OUTPUT);
}
#elif DEBUG_ENABLE==DEBUG_HARD_SERIAL
void debugInit() {
	Serial.begin(57600);
	pinMode(DEBUG_PIN, OUTPUT);
}
#elif DEBUG_ENABLE==DEBUG_HARD_SPI
SPISettings spiSettings(2000000, MSBFIRST, SPI_MODE0);
const uint8_t SSpin = A2;
void debugInit() {
	// CS pin must be output to use SPI as Master!
	SPI.begin();
	digitalWrite(SSpin,HIGH);
	pinMode(SSpin,OUTPUT);
}

void spiPrint(const char* str) {
	char* str1 = (char*) str;
	SPI.beginTransaction(spiSettings);
	digitalWrite(SSpin,LOW);
	while (1) {
		unsigned char c = *str++;
		if (c == 0) break;
		SPI.transfer(c);
	}
	SPI.endTransaction();
	digitalWrite(SSpin,HIGH);
}

void spiPrint(const __FlashStringHelper *str) {
	PGM_P p = reinterpret_cast<PGM_P>(str);
	size_t n = 0;
	SPI.beginTransaction(spiSettings);
	digitalWrite(SSpin,LOW);
	while (1) {
		unsigned char c = pgm_read_byte(p++);
		if (c == 0) break;
		SPI.transfer(c);
	}
	digitalWrite(SSpin,HIGH);
	SPI.endTransaction();
}

void spiPrint(int num){
	char str[11];
	itoa(num,str,10);
	spiPrint(str);
}

#else // DEBUG_ENABLE
void debugInit() {
	pinMode(DEBUG_PIN,OUTPUT);
}
#endif //DEBUG_ENABLE


/**
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */
#include <espduino.h>
#include <mqtt.h>
#include "wifi.h"
#include "debug.h"
#include "oled.h"
#include "servos.h"
#include "commandBuffer.h"
#include "time.h"
#include <avr/pgmspace.h>

boolean wifiConnectedLast = false;

void setup() {
	pinMode(A2, OUTPUT);
	debugInit();
	commandBufferInit();
	oledInit();
	debugPrintln(F("start"));
	oledPrintLine("Connecting...", 0);
	oledLoop(); // push data to OLED
	wifiInit();
	debugPrintln(F("started"));
	servosInit();
	// TODO:delete
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
}

void loop() {
	// TODO:delete
	digitalWrite(A0, HIGH);
	servosLoop();
	// TODO:delete
	digitalWrite(A1, HIGH);
	wifiLoop();
	// TODO:delete
	digitalWrite(A0, LOW);
	if (wifiConnected && !wifiConnectedLast) {
		oledCls();
		oledPrintLine(wifiSsid, 0);
		oledPrintLine(wifiIp, 1);
		oledPrintLine(armIdStr, 2);
		oledLoop();
	} else if (!wifiConnected && wifiConnectedLast) {
		oledCls();
		oledPrintLine("Conn. failed!", 0);
		oledLoop();
	}
	wifiConnectedLast = wifiConnected;
	// TODO:delete
	uint32_t t;
	t = timeGet();
	char temp[20];
	static uint32_t tLast = 0;
	if ((t >= (tLast + 1000)) || (t <= (tLast - 1000))) {
		tLast = t;
		itoa(t / 1000, temp, 10);
		oledPrintLine(temp, 3);
		oledLoop();
	}
	// TODO:delete
	digitalWrite(A1, LOW);
}


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

boolean wifiConnectedLast = true;

void setup() {
	pinMode(A2, OUTPUT);
	debugInit();
	commandBufferInit();
	oledInit();
	debugPrintln("start");
	oledPrintLine("Connecting...", 0);
	oledLoop(); // push data to OLED
	wifiInit();
	debugPrintln("started");
	servosInit();
}

void loop() {
	servosLoop();
	wifiLoop();
	static uint32_t tLast=0;
	if (wifiConnected && !wifiConnectedLast) {
		char str[23] = "WiFi:";
		oledCls();
		strncat(str, wifiSsid, 22 - 5);
		oledPrintLine(str, 0);
		oledPrintLine(wifiIp, 1);
		oledLoop();
	} else if (!wifiConnected && wifiConnectedLast) {
		oledCls();
		oledPrintLine("Conn. failed!", 0);
		oledLoop();
	}
	wifiConnectedLast = wifiConnected;
	uint32_t t;
	t=timeGet();
	char temp[20];
	if(t>=(tLast+1000))
	{
		tLast=t;
		itoa(t/1000,temp,10);
		oledPrintLine(temp,2);
		oledLoop();
	}
}


/**
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */
#include <espduino.h>
#include <mqtt.h>
#include "wifi.h"
#include "debug.h"
#include "oled.h"

void setup() {
	debugInit();
	oledInit();
	debugPrintln("start");
	oledPrintLine("Connecting...", 0);
	oledLoop(); // push data to OLED
	wifiInit();
	debugPrintln("started");
}

void loop() {
	oledLoop();
	wifiLoop();
	if (wifiConnected) {
		char str[23] = "WiFi:";
		oledCls();
		strncat(str, wifiSsid, 22 - 5);
		oledPrintLine(str, 0);
		oledPrintLine(wifiIp, 1);
	} else {
		oledCls();
		oledPrintLine("Conn. failed!", 0);
	}
}

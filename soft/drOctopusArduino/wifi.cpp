/*
 * wifi.c
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */
#include "wifi.h"
#include "debug.h"
#include <espduino.h>
#include <mqtt.h>

ESP esp(&Serial, &Serial, 4);
MQTT mqtt(&esp);
boolean wifiConnected = false;
char wifiIp[16], wifiSsid[16];

void wifiCb(void* response) {
	uint32_t status;
	RESPONSE res(response);

	if (res.getArgc() == 1) {
		res.popArgs((uint8_t*) &status, 4);
		if (status == STATION_GOT_IP) {
			debugPrintln("Wifi connected");
			//mqtt.connect("yourserver.com", 1883, false); // not needed - esp-link connects automatically
			wifiConnected = true;
			//or mqtt.connect("host", 1883); /*without security ssl*/
		} else {
			wifiConnected = false;
			mqtt.disconnect();
		}

	}
}

void mqttConnected(void* response) {
	debugPrintln("MQTT connected");
	mqtt.subscribe("/drOctopus/#"); //or mqtt.subscribe("topic"); /*with qos = 0*/
	mqtt.subscribe("/esp-link/#"); // subscribe status messages
	//mqtt.publish("/drOctopus/test/arduSend", "data0");

}
void mqttDisconnected(void* response) {
	debugPrintln("MQTT disconnected");
}
void mqttData(void* response) {
	RESPONSE res(response);

	debugPrint("Received: topic=");
	String topic = res.popString();
	debugPrintln(topic);

	debugPrint("\tdata=");
	String data = res.popString();
	debugPrintln(data);

}
void mqttPublished(void* response) {

}

void wifiInit() {
	Serial.begin(115200);
	esp.enable();
	delay(500);
	esp.reset();

	// wait for connection and search SSID and IP in debug log
	Serial.setTimeout(1000);
	const String ssidString = "Wifi connected to ssid ";
	const String ipString = "Wifi got ip:";
	const String endString = "Turning OFF uart log";
	String temp;
	int found = 0, location, start, stop;
	for (int i = 0; i < 120; i++) {
		String espString = Serial.readStringUntil('\r');
		if (found == 0) {
			// search for Wifi SSID information
			location = espString.indexOf(ssidString);
			if (location >= 0) {
				start = location + ssidString.length();
				stop = espString.indexOf(",", start);
				strncpy(wifiSsid, espString.substring(start, stop).c_str(), 15);
				debugPrint(ssidString);
				debugPrintln(wifiSsid);
				found = 1;
			}
		} else if (found == 1) {
			// search for Wifi IP information
			location = espString.indexOf(ipString);
			if (location >= 0) {
				start = location + ipString.length();
				stop = espString.indexOf(',', start);
				strncpy(wifiIp, espString.substring(start, stop).c_str(), 15);
				debugPrint(ipString);
				debugPrintln(wifiIp);
				found = 2;
			}
		} else if (found == 2) {
			// search for end of esp debug log
			location = espString.indexOf(endString);
			if (location >= 0) {
				break;
			}
		}
	}
	while (!esp.ready())
		;

	//debugPrintln("setup mqtt client");
	if (!mqtt.begin("", "", "", 120, 1)) {
		debugPrintln("MQTT Fail");
		while (1)
			;
	}

	//mqtt.lwt("/lwt", "offline", 0, 0); //or mqtt.lwt("/lwt", "offline");

	/*setup mqtt events */
	mqtt.connectedCb.attach(&mqttConnected);
	mqtt.disconnectedCb.attach(&mqttDisconnected);
	mqtt.publishedCb.attach(&mqttPublished);
	mqtt.dataCb.attach(&mqttData);

	/*setup wifi*/
	esp.wifiCb.attach(&wifiCb);
	esp.wifiConnect("", "");
}

void wifiLoop() {
	esp.process();
}

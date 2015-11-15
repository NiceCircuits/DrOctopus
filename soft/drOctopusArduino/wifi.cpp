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
boolean wifiConnected = false, mqttConnected = false;
char wifiIp[16], wifiSsid[16];

void mqttSubscribe() {
	mqtt.subscribe("/drOctopus/#"); //or mqtt.subscribe("topic"); /*with qos = 0*/
	mqtt.subscribe("/esp-link/#"); // subscribe status messages
}

void wifiCb(void* response) {
	uint32_t status;
	RESPONSE res(response);

	if (res.getArgc() == 1) {
		res.popArgs((uint8_t*) &status, 4);
		if (status == STATION_GOT_IP) {
			debugPrintln("Wifi connected");
			mqtt.connect("zzzz", 1883, false); // not needed - esp-link connects automatically
			wifiConnected = true;
			//or mqtt.connect("host", 1883); /*without security ssl*/
		} else {
			wifiConnected = false;
			mqtt.disconnect();
		}

	}
}

void mqttConnectedCb(void* response) {
	debugPrintln("MQTT connected");
	mqttSubscribe();
	//mqtt.publish("/drOctopus/test/arduSend", "data0");
	mqttConnected = true;
}

void mqttDisconnectedCb(void* response) {
	debugPrintln("MQTT disconnected");
	mqttConnected = false;
}

void mqttDataCb(void* response) {
	RESPONSE res(response);
	char buf[21];

	debugPrint("Received: topic=");
	res.popArgs((uint8_t*) buf, 20);
	debugPrintln(buf);

	debugPrint("\tdata=");
	res.popArgs((uint8_t*) buf, 20);
	debugPrintln(buf);
}

void mqttPublishedCb(void* response) {

}

void wifiInit() {
	Serial.begin(57600);
	esp.enable();
	delay(500);
	esp.reset();

	/*setup mqtt events */
	mqtt.connectedCb.attach(&mqttConnectedCb);
	mqtt.disconnectedCb.attach(&mqttDisconnectedCb);
	mqtt.publishedCb.attach(&mqttPublishedCb);
	mqtt.dataCb.attach(&mqttDataCb);

	/*setup wifi*/
	esp.wifiCb.attach(&wifiCb);
	// wait for connection and search SSID and IP in debug log
	Serial.setTimeout(1000);
	const char* ssidString = "Wifi connected to ssid ";
	const char* ipString = "Wifi got ip:";
	const char* endString = "Turning OFF uart log";
	int found = 0;
	char* start, stop;
	for (int i = 0; i < 120; i++) {
		char espString[80];
		Serial.readBytesUntil('\n', espString, 60);
		if (found == 0) {
			// search for Wifi SSID information
			start = strstr(espString, ssidString);
			if (start != NULL) {
				start += strlen(ssidString);
				*strchr(start, ',') = '\0';
				debugPrint(ssidString);
				debugPrintln(start);
				strncpy(wifiSsid, start, 15);
				found = 1;
			}
		} else if (found == 1) {
			// search for Wifi IP information
			start = strstr(espString, ipString);
			if (start != NULL) {
				start += strlen(ipString);
				*strchr(start, ',') = '\0';
				debugPrint(ipString);
				debugPrintln(start);
				strncpy(wifiIp, start, 15);
				found = 2;
			}
		} else if (found == 2) {
			// search for end of esp debug log
			start = strstr(espString, endString);
			if (start != NULL) {
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

	esp.wifiConnect("", "");
	mqttSubscribe();
}

void wifiLoop() {
	esp.process();
}

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
#include <EEPROM.h>
#include "commandBuffer.h"

ESP esp(&Serial, &Serial, 4);
MQTT mqtt(&esp);
boolean wifiConnected = false, mqttConnected = false;
char wifiIp[16], wifiSsid[16];
uint8_t wifiId; // last byte of IP
uint8_t armId; // id of arm, from 1 to 99, stored on EEPROM
// address where ID is stored in EEPROM
#define ARM_ID_EE_ADDRESS (13)

const char mqttTopicCommon[] = "/drOctopus/common/#";
const char mqttTopicSync[] = "/drOctopus/common/sync";
char mqttTopicArm[] = "/drOctopus/arm/\0\0\0"; // "\0\0\0" will be replaced with arm number
char mqttTopicConfig[] = "/drOctopus/conf/\0\0\0"; // "\0\0\0" will be replaced with arm wifi ID

void mqttSubscribe() {
	mqtt.subscribe(mqttTopicCommon);
	mqtt.subscribe(mqttTopicArm);
	mqtt.subscribe(mqttTopicConfig);
}

void wifiCb(void* response) {
	uint32_t status;
	RESPONSE res(response);

	if (res.getArgc() == 1) {
		res.popArgs((uint8_t*) &status, 4);
		if (status == STATION_GOT_IP) {
			debugPrintln("Wifi connected");
			mqtt.connect("", 1883, false); // not needed - esp-link connects automatically
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
	mqttConnected = true;
}

void mqttDisconnectedCb(void* response) {
	debugPrintln("MQTT disconnected");
	mqttConnected = false;
}

void mqttDataCb(void* response) {
	RESPONSE res(response);
	char buf[31];
	boolean commandFlag = false;

	debugPrint("Received: topic=");
	memset(buf, 0, 31);
	res.popArgs((uint8_t*) buf, 30);
	debugPrintln(buf);
	if (strcmp(buf, mqttTopicArm) == 0) {
		commandFlag = true;
	}
	debugPrint("\tdata=");
	memset(buf, 0, 31);
	res.popArgs((uint8_t*) buf, 30);
	debugPrintln(buf);
	if (commandFlag) {
		command_t c;
		memcpy(&c, buf, sizeof(command_t));
		commandBufferPush(&c);
	}
}

void mqttPublishedCb(void* response) {

}

void wifiInit() {
	char strBuffer[80];
	// read arm ID from EEPROM
	armId = EEPROM.read(ARM_ID_EE_ADDRESS);
	debugPrint("Arm ID: ");
	itoa(armId, strBuffer, 10);
	debugPrintln(strBuffer);
	strncat(mqttTopicArm, strBuffer, 3);

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
	char *start, *temp;
	for (int i = 0; i < 120; i++) {
		Serial.readBytesUntil('\n', strBuffer, 60);
		if (found == 0) {
			// search for Wifi SSID information
			start = strstr(strBuffer, ssidString);
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
			start = strstr(strBuffer, ipString);
			if (start != NULL) {
				start += strlen(ipString);
				*strchr(start, ',') = '\0';
				debugPrint(ipString);
				debugPrintln(start);
				strncpy(wifiIp, start, 15);
				// find last dot and read last byte of IP
				temp = strrchr(wifiIp, '.');
				wifiId = atoi(temp);
				found = 2;
			}
		} else if (found == 2) {
			// search for end of esp debug log
			start = strstr(strBuffer, endString);
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

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
#include "time.h"
#include <avr/pgmspace.h>

ESP esp(&Serial, &Serial, 4);
MQTT mqtt(&esp);
boolean wifiConnected = false, mqttConnected = false;
char wifiIp[16], wifiSsid[16], armIdStr[4];
uint8_t wifiId; // last byte of IP
uint8_t armId; // id of arm, from 1 to 99, stored on EEPROM
// address where ID is stored in EEPROM
#define ARM_ID_EE_ADDRESS (13)

const char mqttTopicCommon[] PROGMEM = "/drOctopus/common/#";
const char mqttTopicSync[] PROGMEM = "/drOctopus/common/sync";
const char mqttTopicArm[] PROGMEM = "/drOctopus/arm/"; // arm number will be appended
const char mqttTopicConfig[] PROGMEM = "/drOctopus/conf/"; // wifi ID will be appended

typedef enum {
	mqttCommandNone = 0, mqttCommandPosition = 1, mqttCommandSync = 2
} mqttCommand_t;

void mqttSubscribe() {
	char strBuffer[sizeof(mqttTopicSync) + 6];
	strncpy_P(strBuffer, mqttTopicCommon, sizeof(strBuffer) - 1);
	mqtt.subscribe(mqttTopicCommon);
	strncpy_P(strBuffer, mqttTopicArm, sizeof(strBuffer) - 1);
	itoa(armId, strBuffer + sizeof(mqttTopicArm) - 1, 10);
	mqtt.subscribe(strBuffer);
	strncpy_P(strBuffer, mqttTopicConfig, sizeof(strBuffer) - 1);
	itoa(wifiId, strBuffer + sizeof(mqttTopicConfig) - 1, 10);
	mqtt.subscribe(strBuffer);
	//TODO: check all below
}

void wifiCb(void* response) {
	uint32_t status;
	RESPONSE res(response);

	if (res.getArgc() == 1) {
		res.popArgs((uint8_t*) &status, 4);
		if (status == STATION_GOT_IP) {
			debugPrintln(F("Wifi connected"));
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
	debugPrintln(F("MQTT connected"));
	mqttSubscribe();
	mqttConnected = true;
}

void mqttDisconnectedCb(void* response) {
	debugPrintln(F("MQTT disconnected"));
	mqttConnected = false;
}

void mqttDataCb(void* response) {
	RESPONSE res(response);
	char buf[31];
	mqttCommand_t commandType = mqttCommandNone;

	debugPrint(F("Received: topic="));
	memset(buf, 0, 31);
	res.popArgs((uint8_t*) buf, 30);
	debugPrintln(buf);
	if (strncmp_P(mqttTopicArm, buf, sizeof(mqttTopicArm) - 1) == 0) {
		commandType = mqttCommandPosition;
	} else if (strcmp(buf, mqttTopicSync) == 0) {
		commandType = mqttCommandSync;
	}

	debugPrint(F("\tdata="));
	memset(buf, 0, 31);
	res.popArgs((uint8_t*) buf, 30);
	debugPrintln(buf);
	if (commandType == mqttCommandPosition) {
		command_t c;
		memcpy(&c, buf, sizeof(command_t));
		commandBufferPush(&c);
	} else if (commandType == mqttCommandSync) {
		uint32_t newTime;
		memcpy(&newTime, buf, sizeof(command_t));
		setTime(newTime);
	}
}

void mqttPublishedCb(void* response) {

}

void wifiInit() {
	char strBuffer[80];
	// read arm ID from EEPROM
	armId = EEPROM.read(ARM_ID_EE_ADDRESS);
	debugPrint(F("Arm ID: "));
	debugPrintln(armId);
	itoa(armId, armIdStr, 10);

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
	static const char ssidString[] PROGMEM = "Wifi connected to ssid ";
	static const char ipString[] PROGMEM = "Wifi got ip:";
	static const char endString[] PROGMEM = "Turning OFF uart log";
	int found = 0;
	char *start, *temp;
	for (int i = 0; i < 120; i++) {
		Serial.readBytesUntil('\n', strBuffer, 60);
		if (found == 0) {
			// search for Wifi SSID information
			start = strstr_P(strBuffer, ssidString);
			if (start != NULL) {
				start += sizeof(ssidString)-1;
				*strchr(start, ',') = '\0';
				debugPrint(FS(ssidString));
				debugPrintln(start);
				strncpy(wifiSsid, start, 15);
				found = 1;
			}
		} else if (found == 1) {
			// search for Wifi IP information
			start = strstr_P(strBuffer, ipString);
			if (start != NULL) {
				start += sizeof(ipString)-1;
				*strchr(start, ',') = '\0';
				debugPrint(FS(ipString));
				debugPrintln(start);
				strncpy(wifiIp, start, 15);
				// find last dot and read last byte of IP
				temp = strrchr(wifiIp, '.');
				wifiId = atoi(temp+1);
				found = 2;
			}
		} else if (found == 2) {
			// search for end of esp debug log
			start = strstr_P(strBuffer, endString);
			if (start != NULL) {
				break;
			}
		}
	}
	while (!esp.ready())
		;

//debugPrintln("setup mqtt client");
	if (!mqtt.begin("", "", "", 120, 1)) {
		debugPrintln(F("MQTT Fail"));
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

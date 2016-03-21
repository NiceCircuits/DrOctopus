/**
 ******************************************************************************
 * @file    ESP8266.c
 * @author  piotr@nicecircuits.com
 * @date    2016-03-01
 * @brief
 ******************************************************************************
 */
extern "C" {
#include "config.h"
#include "delay.h"
#include "debug.h"
}
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "ELClient.h"
#include "ELClientMqtt.h"
#include "espStream.h"

// ---------- Private variables. ----------
/// esp-link client stream object
espStream_t espStream;
/// esp-link client object
ELClient espELClient(&espStream, &espStream, getTime);
/// esp-link MQTT client object
ELClientMqtt espELClientMqtt(&espELClient);
/// Debug source variable.
debugSource_t espDebugSource;
/// Wifi connected flag
bool wifiConnected = false;

// ---------- Private functions declarations. ----------
void wifiCb(void *response);
void dataCb(void *response);

// ---------- Public functions. ----------
extern "C" uint_fast8_t espInit(void) {
	// Create and enable debug source for ESP
	espDebugSource = debugNewSource("ESP");
	debugSourceEnable(espDebugSource, ENABLE);

	// Initialize ESP and MQTT.
	espStream.init();
	espELClient.wifiCb.attach(wifiCb);
	espELClientMqtt.dataCb.attach(dataCb);
	debugPrintln(espDebugSource, "Init OK.");
	bool ok;
	do {
		ok = espELClient.Sync(); // sync up with esp-link, blocks for up to 2 seconds
		if (!ok)
			debugPrintln(espDebugSource, "EL-Client sync failed!");
	} while (!ok);
	//TODO: error handling
	debugPrintln(espDebugSource, "EL-Client synced!");
	espELClientMqtt.setup();
	debugPrintln(espDebugSource, "EL-MQTT ready");
	return 0;
}

extern "C" void ESP_IRQHandler() {
	uint8_t data;
	if (USART_GetITStatus(ESP_USART, USART_IT_RXNE) == SET) {
		data = USART_ReceiveData(ESP_USART);
		espStream.pushRxData(data);
	}
}

// ---------- Private functions. ----------
// Callback made from esp-link to notify of wifi status changes
// Here we print something out and set a global flag
void wifiCb(void *response) {
	ELClientResponse *res = (ELClientResponse*) response;
	if (res->argc() == 1) {
		uint8_t status;
		res->popArg(&status, 1);

		if (status == STATION_GOT_IP) {
			debugPrintln(espDebugSource, "WIFI connected");
			wifiConnected = true;
		} else {
			debugPrintln(espDebugSource, "WIFI not ready: $u", status);
			wifiConnected = false;
		}
	}
}

void dataCb(void *response) {
	ELClientResponse *res = (ELClientResponse*) response;
	void* topic;
	void* message;
	res->popArgPtr(&topic);
	res->popArgPtr(&message);
	debugPrintln(espDebugSource, "MQTT received: %s, %s", (char*) topic,
			(char*) message);
}

#if TEST_MODE == TEST_MODE_ESP
int main(void) {
	uint8_t i = 0;
	defaultInit();
	espInit();
	if (0) {
		// USART loopback.
		for (;;) {
			if (espStream.available()) {
				espStream.write(espStream.read());
			}
		}
	}
	if (0) {
		// Print test
		for (;;) {
			//espStream.print("ESP test %c\r\n", i);
			i++;
			//delayMs(1000);
		}
	}
	if (1) {
		// MQTT test. Example MQTT settings (set via ESP WiFi):
		// Host: broker.hivemq.com
		// Port: 1883
		// Can be tested using http://www.hivemq.com/demos/websocket-client/
		// This test publishes "esplink_test" message every 1s
		// and subscribes "esp_test_resp" messages from server
		// Received messages are sent to debug port
		espELClientMqtt.subscribe("esp_test_resp");
		for (;;) {
			espELClient.Process();
			if (wifiConnected) {
				// Request /utc/now from the previously set-up server
				espELClientMqtt.publish("esplink_test", "xyz", 0);
				delayMs(1000);
			}
		}
	}
}
#endif // TEST_MODE == TEST_MODE_ESP

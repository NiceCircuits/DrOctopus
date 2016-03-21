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

// ---------- Public functions. ----------
extern "C" uint_fast8_t espInit(void) {
	espStream.init();
	return 0;
}

#if TEST_MODE == TEST_MODE_ESP
int main(void) {
	uint8_t i = 0;
	defaultInit();
	espInit();
	for (;;) {
		espStream.print("ESP test %u\r\n", i);
		i++;
		delayMs(1000);
	}
}
#endif // TEST_MODE == TEST_MODE_ESP

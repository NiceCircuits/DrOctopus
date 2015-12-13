/*
 * wifi.h
 *
 *  Created on: 2015-11-12
 *      Author: Piotr Nowicki
 */

#ifndef WIFI_H_
#define WIFI_H_

#include <Arduino.h>

void wifiInit(void);
void wifiLoop(void);

extern boolean wifiConnected;
extern char wifiIp[], wifiSsid[], armIdStr[];
extern uint8_t armId;
//TODO: delete:
//extern const PROGMEM char mqttTopicArm[];

#endif /* WIFI_H_ */

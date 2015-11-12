/**
 */
#include <espduino.h>
#include <mqtt.h>
#include "wifi.h"
#include "debug.h"

void setup() {
  debugPort.begin(115200);
  debugPort.println("ARDUINO: start");
  wifiInit();
  debugPort.println("ARDUINO: system started");
}

void loop() {
  wifiLoop();
  if(wifiConnected) {

  }
}

/**
 * \file
 *       ESP8266 MQTT Bridge example
 * \author
 *       Tuan PM <tuanpm@live.com>
 */
#include <SoftwareSerial.h>
#include <espduino.h>
#include <mqtt.h>

SoftwareSerial debugPort(A2, A3); // RX, TX
ESP esp(&Serial, &Serial, 4);
MQTT mqtt(&esp);
boolean wifiConnected = false;

void wifiCb(void* response)
{
  uint32_t status;
  RESPONSE res(response);

  if(res.getArgc() == 1) {
    res.popArgs((uint8_t*)&status, 4);
    if(status == STATION_GOT_IP) {
      debugPort.println("Wifi connected");
      //mqtt.connect("yourserver.com", 1883, false); // not needed - esp-link connects automatically
      wifiConnected = true;
      //or mqtt.connect("host", 1883); /*without security ssl*/
    } else {
      wifiConnected = false;
      mqtt.disconnect();
    }

  }
}

void mqttConnected(void* response)
{
  debugPort.println("MQTT connected");
  mqtt.subscribe("/drOctopus/test/#"); //or mqtt.subscribe("topic"); /*with qos = 0*/
  mqtt.subscribe("/esp-link/#"); // subscribe status messages
  //mqtt.publish("/drOctopus/test/arduSend", "data0");

}
void mqttDisconnected(void* response)
{

}
void mqttData(void* response)
{
  RESPONSE res(response);

  debugPort.print("Received: topic=");
  String topic = res.popString();
  debugPort.println(topic);

  debugPort.print("data=");
  String data = res.popString();
  debugPort.println(data);

}
void mqttPublished(void* response)
{

}
void setup() {
  Serial.begin(115200);
  debugPort.begin(115200);
  debugPort.println("ARDUINO: start");
  esp.enable();
  debugPort.println("ARDUINO: esp enable");
  delay(500);
  debugPort.println("ARDUINO: esp reset");
  esp.reset();
  // wait for
//  Serial.setTimeout(1000);
//  for (int i=0;i<200;i++)
//  {
//	  String str = Serial.readStringUntil('\r');
//	  debugPort.print(str);
//  }
//  delay(10000);
  debugPort.println("ARDUINO: esp wait");
  while(!esp.ready());

  debugPort.println("ARDUINO: setup mqtt client");
  if(!mqtt.begin("DVES_duino", "admin", "Isb_C4OGD4c3", 120, 1)) {
    debugPort.println("ARDUINO: fail to setup mqtt");
    while(1);
  }


  debugPort.println("ARDUINO: setup mqtt lwt");
  mqtt.lwt("/lwt", "offline", 0, 0); //or mqtt.lwt("/lwt", "offline");

/*setup mqtt events */
  mqtt.connectedCb.attach(&mqttConnected);
  mqtt.disconnectedCb.attach(&mqttDisconnected);
  mqtt.publishedCb.attach(&mqttPublished);
  mqtt.dataCb.attach(&mqttData);


  /*setup wifi*/
  debugPort.println("ARDUINO: setup wifi");
  esp.wifiCb.attach(&wifiCb);

  //esp.wifiConnect("DVES_HOME","wifipassword"); // not needed - esp-link connects automatically


  debugPort.println("ARDUINO: system started");
}

void loop() {
  esp.process();
  if(wifiConnected) {

  }
}

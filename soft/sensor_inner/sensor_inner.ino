

#include <Wire.h>
#include "LSM303.h"
#include "NewPing.h"

LSM303 compass;
char report[80];

#define TRIGGER_PIN  A4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     A3  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 256 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  compass.init();
  compass.enableDefault();
}

void loop()
{
  compass.read();

  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  uS = (uS / US_ROUNDTRIP_CM); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  snprintf(report, sizeof(report), "%d,%d,%d,%d,%d,%d,%d",
    compass.a.x, compass.a.y, compass.a.z,
    compass.m.x, compass.m.y, compass.m.z, uS);
  Serial.println(report);

  delay(300);
}




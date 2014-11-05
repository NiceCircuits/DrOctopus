

#include "dht11.h"
#include <Wire.h>
#include "LPS331.h"
#include "BH1750.h"

dht11 DHT11;
LPS331 ps;
BH1750 lightMeter;

#define DHT11PIN 7

char report[80];

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  lightMeter.begin();
  if (!ps.init())
  {
    Serial.println("Failed to autodetect pressure sensor!");
    while (1);
  }

  ps.enableDefault();
}

void loop()
{
  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float temperature = ps.readTemperatureC();

  int chk = DHT11.read(DHT11PIN);

  snprintf(report, sizeof(report), "%d,%d,%d,%d",
    (int)DHT11.humidity, (int)DHT11.temperature, (int)pressure, lightMeter.readLightLevel());
    Serial.println(report);
  delay(300);
}


// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double dewPoint(double celsius, double humidity)
{
	// (1) Saturation Vapor Pressure = ESGG(T)
	double RATIO = 373.15 / (273.15 + celsius);
	double RHS = -7.90298 * (RATIO - 1);
	RHS += 5.02808 * log10(RATIO);
	RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
	RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
	RHS += log10(1013.246);

        // factor -3 is to adjust units - Vapor Pressure SVP * humidity
	double VP = pow(10, RHS - 3) * humidity;

        // (2) DEWPOINT = F(Vapor Pressure)
	double T = log(VP/0.61078);   // temp var
	return (241.88 * T) / (17.558 - T);
}



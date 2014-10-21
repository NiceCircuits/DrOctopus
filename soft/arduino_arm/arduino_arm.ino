/*
 Arm driver firmware
 Board - Arduino Pro Mini with ATmega328, 5V, 16MHz
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//
const int nrfCePin = A0;
const int nrfCsPin = A2;
const int servo1Pin = 2;
const int servo2Pin = 3;
const int servo3Pin = 4;
const int servo4Pin = 5;
const int extruderMotorPin = 6;
const int heaterPin = 9;

// Set up nRF24L01 radio on SPI bus plus pins 9 & 10 
RF24 radio(nrfCePin,nrfCsPin);

//
// Topology
//

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0F1LL;

char txt[100];
const char ctxt[]="test12345678901234567890\r\n";
int len = 10;

int led=2;

void setup(void)
{
  digitalWrite(led,0);
  pinMode(led, OUTPUT);
  Serial.begin(57600);
  printf_begin();
  Serial.write("receiver\n\r");
  radio.begin();
  radio.setAutoAck(true);
  radio.setRetries(15,15);  
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  radio.printDetails();
}

void loop(void)
{
  if ( radio.available() )
  {
    bool done = false;
    while (!done)
    {
      done = radio.read(txt, len);
      Serial.write(txt);
      digitalWrite(led,1);
      delay(15);
      digitalWrite(led,0);
    }
  }
}


#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
RF24 radio(9,10);
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t startPipe = 0xDEADBEEF00LL;

const char txt[]="12345\r\n";
int len;

void setup(void)
{
  len=strlen(txt);
  Serial.begin(57600);
  printf_begin();
  Serial.write("hub\n\r");
  radio.begin();
  radio.setAutoAck(true);
  radio.setRetries(15,15);  
  radio.setPayloadSize(8);
  radio.openWritingPipe(startPipe+1);
  radio.printDetails();
}

void loop(void)
{
  while(1)
  {
    radio.write(txt, len);
    Serial.write(".");
    delay(10);
  }
}

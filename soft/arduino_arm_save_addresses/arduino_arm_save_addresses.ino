/*
 * EEPROM Write
 *
 * Stores values read from analog input 0 into the EEPROM.
 * These values will stay in the EEPROM when the board is
 * turned off and may be retrieved later by another sketch.
 */

#include <EEPROM.h>

// the current address in the EEPROM (i.e. which byte
// we're going to write to next)
int addr = 10;

void setup()
{
  digitalWrite(13, LOW);
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, LOW);
  EEPROM.write(addr, 1);
  delay(100);
  
  digitalWrite(13, HIGH);
  while(1)
  {
  }
}

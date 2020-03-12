#include "_HC05.h"

SoftwareSerial BTserial(9, 10);

void testBT()
{
  if (BTserial.available())
  {
    byte x = BTserial.read();
    Serial.write(x);
  }

  if (Serial.available())
  {
    byte y = Serial.read();
    BTserial.write(y);
  }
}
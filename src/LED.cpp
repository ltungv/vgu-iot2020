#include "LED.hpp"

#include <Arduino.h>

void LED::blink(int digitalPin,
                int millisOnDuration,
                int millisOffDuration,
                int times)
{
  while (times--)
  {
    digitalWrite(digitalPin, HIGH);
    delay(millisOnDuration);
    digitalWrite(digitalPin, LOW);
    delay(millisOffDuration);
  }
}

//
//
//

#include "Led.h"

Grove_LED_Bar bar(9, 8, 0);  // Clock pin, Data pin, Orientation

void LedClass::init(int pin)
{
  this->pin = pin;
  bar.begin();
}

void LedClass::turnOn(int value)
{
  if (value == 1) bar.setBits(0x001);
  if (value == 2) bar.setBits(0x003);
  if (value == 3) bar.setBits(0x007);
  if (value == 4) bar.setBits(0x00F);
  if (value == 5) bar.setBits(0x01F);
  if (value == 6) bar.setBits(0x03F);
  if (value == 7) bar.setBits(0x07F);
  if (value == 8) bar.setBits(0x0FF);
  if (value == 9) bar.setBits(0x1FF);
  if (value == 10) bar.setBits(0x3FF);
  Serial.println("LED IS ON");
}

void LedClass::turnOff()
{
  bar.setBits(0x000);
  Serial.println("LED IS OFF");
}

float LedClass::getValue(String value) {
  return 0;
}

void LedClass::setValue(int value) {
  if (value == 0) {
    turnOff();
  }
  else {
    turnOn(value);
  }
}

LedClass Led;


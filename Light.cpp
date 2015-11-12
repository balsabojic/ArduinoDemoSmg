//
//
//

#include "Light.h"

void LightClass::init(uint8_t pin)
{
  this->pin = pin;
}

float LightClass::getValue(String value) {
  int sensorValue = analogRead(0);
  float sensor = (float)(sensorValue) / 8;
  return sensor;
}

void LightClass::setValue(int value) {
}

LightClass Light;


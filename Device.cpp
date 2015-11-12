//
//
//

#include "Device.h"

void DeviceClass::init(int pin)
{
  this->pin = pin;
  pinMode(pin, OUTPUT);
  digitalWrite(this->pin, HIGH);
}

void DeviceClass::turnOn()
{
  digitalWrite(this->pin, LOW);
  Serial.println("RELAY IS ON");
}

void DeviceClass::turnOff()
{
  digitalWrite(this->pin, HIGH);
  Serial.println("RELAY IS OFF");
}

float DeviceClass::getValue(String value) {
  return 0;
}

void DeviceClass::setValue(int value) {
  if (value == 1) {
    turnOn();
  }
  else if (value == 0) {
    turnOff();
  }
}

DeviceClass Device;


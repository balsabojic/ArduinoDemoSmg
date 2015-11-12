// Light.h

#ifndef _LIGHT_h
#define _LIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Sensor.h"

class LightClass : SensorClass
{
  protected:
    uint8_t pin;
  public:
    void init(uint8_t pin);
    float getValue(String value);
    void setValue(int value);
};

extern LightClass Light;

#endif


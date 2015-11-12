// Device.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Sensor.h"
#include <Grove_LED_Bar.h>

class LedClass : SensorClass
{
  protected:
    int pin;
  public:
    void init(int pin);
    void turnOn(int value);
    void turnOff();
    float getValue(String value);
    void setValue(int value);
};

extern LedClass Led;

#endif


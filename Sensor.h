// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class SensorClass
{
  public:
    virtual float getValue(String value);
    virtual void setValue(int value);
};


#endif


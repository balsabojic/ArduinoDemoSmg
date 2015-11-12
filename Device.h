// Device.h

#ifndef _DEVICE_h
#define _DEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Sensor.h"

class DeviceClass : SensorClass
{
  protected:
    int pin;
  public:
    void init(int pin);
    void turnOn();
    void turnOff();
    float getValue(String value);
    void setValue(int value);
};

extern DeviceClass Device;

#endif


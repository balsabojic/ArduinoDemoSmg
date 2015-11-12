#ifndef SENSORDATA_H__
#define SENSORDATA_H__

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Device.h"
#include "Sensor.h"

class SensorData {
  public:
    String name;
    int code;
    int treshold;
    uint8_t pin;
    SensorClass *dev;
    float oldValue;
};

#endif

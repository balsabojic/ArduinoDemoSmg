#include "Sensor.h"
#include "Device.h"
#include "Light.h"
#include "Led.h"
#include <SPI.h>
#include <Ethernet2.h> // Used for Ethernet
#include <Grove_LED_Bar.h>
#include "NetworkConnection.h";


void setup() {
  Serial.begin(9600);

  NetworkConnection.init();
}

void loop()
{
  NetworkConnection.run();
}

// NetworkConnection.h

#ifndef _NETWORKCONNECTION_h
#define _NETWORKCONNECTION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"

#else
#include "WProgram.h"
#endif

#include <SPI.h>
#include "LinkedList.h"
#include "SensorData.h"
#include <Ethernet2.h> // Used for Ethernet

static enum {
  IDLE, RECV_DATA, SEND_DATA
} state;

class NetworkConnectionClass
{
  private:
    void getConfigData();
    void sendData(String name, String value);
    void checkForUpdate();
    uint8_t getIntValue(String pin);
  protected:
    EthernetClient client;
    LinkedList<SensorData*>* sensorData;
  public:
    void init();
    void run();
};

extern NetworkConnectionClass NetworkConnection;

#endif


#include "NetworkConnection.h"
#include "Device.h"
#include "Light.h"
#include "Led.h"

// SMG Arduino address
byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x32 };
IPAddress ip(192, 168, 21, 235);
EthernetServer server(82);

unsigned long previousMillis = 0; // last time update
long interval = 5; // interval at which to do something (milliseconds)

void NetworkConnectionClass::init()
{
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();

  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());

  sensorData = new LinkedList<SensorData*>();
  state = RECV_DATA;
}

void NetworkConnectionClass::getConfigData()
{
  String name = "";
  String value = "";
  boolean isValue = false;
  char character;
  SensorData *data;
  while (client.available() > 0) {
    character = client.read();
    if (character == '{') {
      data = new SensorData();
      name = "";
      value = "";
      isValue = false;
      continue;
    }
    if (character == ',' || character == '}') {
      if (name.equals("name")) {
        data->name = value;
      }
      else if (name.equals("code")) {
        data->code = value.toInt();
      }
      else if (name.equals("threshold")) {
        data->treshold = value.toInt();
      }
      else if (name.equals("pin")) {
        data->pin = getIntValue(value);
      }
      name = "";
      value = "";
      isValue = false;
      if (character == '}') {
        data->oldValue = 0;
        sensorData->insert(data);
      }
      continue;
    }
    if (character == ':') {
      isValue = true;
      continue;
    }
    if (!isValue) {
      name.concat(character);
    }
    else {
      value.concat(character);
    }
  }
}

uint8_t NetworkConnectionClass::getIntValue(String pin) {
  uint8_t pin_uint = 0;

  if (pin.equals("A0")) {
    pin_uint = A0;
  }
  else if (pin.equals("A1")) {
    pin_uint = A1;
  }
  else if (pin.equals("A2")) {
    pin_uint = A2;
  }
  else if (pin.equals("A3")) {
    pin_uint = A3;
  }
  else if (pin.equals("A4")) {
    pin_uint = A4;
  }
  else if (pin.equals("A5")) {
    pin_uint = A5;
  }
  else if (pin.equals("A6")) {
    pin_uint = A6;
  }
  else if (pin.equals("A7")) {
    pin_uint = A7;
  }
  else {
    pin_uint = pin.toInt();
  }
  return pin_uint;
}

void NetworkConnectionClass::sendData(String name, String value)
{
  String str1 = name + "=" + value;
  client.println(str1);
}

void NetworkConnectionClass::checkForUpdate()
{
  String name = "";
  String value = "";
  boolean isValue = false;

  while (client.available() > 0) {
    char character = client.read();
    if (character == '=') {
      isValue = true;
    }
    else {
      if (isValue) {
        value.concat(character);
      }
      else {
        name.concat(character);
      }  
    }
  }

  for (LinkedList<SensorData*>::Iterator it = sensorData->begin(); it != sensorData->end(); it++) {
    if (name.equals((*it)->name)) {
      Serial.println(name);
      if (value[0] == '1' && value[1] == '0') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(10);
        }
      }
      else if (value[0] == '1') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(1);
        }
      }
      else if (value[0] == '0') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(0);
        }
      }
      else if (value[0] == '3') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(3);
        }
      }
      else if (value[0] == '4') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(4);
        }
      }
      else if (value[0] == '5') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(5);
        }
      }
      else if (value[0] == '6') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(6);
        }
      }
      else if (value[0] == '7') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(7);
        }
      }
      else if (value[0] == '8') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(8);
        }
      }
      else if (value[0] == '9') {
        if ((*it)->dev != NULL) {
          (*it)->dev->setValue(9);
        }
      }
    }
  }
}

void NetworkConnectionClass::run()
{
  client = server.available();
  while (client.connected()) {
    switch (state) {
      case IDLE:
        state = SEND_DATA;
        return;
      case RECV_DATA:
        getConfigData();
        for (LinkedList<SensorData*>::Iterator it = sensorData->begin(); it != sensorData->end(); it++) {
          if ((*it)->code == 12) {
            LightClass *temp = new LightClass();
            temp->init((*it)->pin);
            (*it)->dev = (SensorClass*)temp;
          }
          else if ((*it)->code == 0) {
            LedClass *d1 = new LedClass();
            d1->init((*it)->pin);
            (*it)->dev = (SensorClass*)d1;
          }
          else if ((*it)->code == 3) {
            Serial.println("Relay created");
            DeviceClass *d4 = new DeviceClass();
            d4->init((*it)->pin);
            (*it)->dev = (SensorClass*)d4;
          }
          else if ((*it)->code == 4) {
            Serial.println("Relay created");
            DeviceClass *d5 = new DeviceClass();
            d5->init((*it)->pin);
            (*it)->dev = (SensorClass*)d5;
          }
        }
        state = SEND_DATA;
        break;
      case SEND_DATA:
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis > interval) {
          previousMillis = currentMillis;

          for (LinkedList<SensorData*>::Iterator it = sensorData->begin(); it != sensorData->end(); it++) {
            // Check just sensors, not devices. Devices have code 0.
            if ((*it)->code == 12) {
              float dataValue;
              if ((*it)->code == 12) {
                dataValue = (*it)->dev->getValue("");
              }
              float newValueMax = (*it)->oldValue + (*it)->treshold;
              float newValueMin = (*it)->oldValue - (*it)->treshold;
              // Check if the sensor has exceeded threshold, send data and update oldValue of sensor
              //if (dataValue <= newValueMin || dataValue >= newValueMax) {
              sendData((*it)->name, String((int)dataValue));
              (*it)->oldValue = dataValue;
              //Serial.println((*it)->name);
              //Serial.println(dataValue);
              //}
            }
          }
        }

        checkForUpdate();

        state = SEND_DATA;
        break;
    }
  }
}
NetworkConnectionClass NetworkConnection;


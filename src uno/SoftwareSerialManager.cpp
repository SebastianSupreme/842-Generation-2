#include "SoftwareSerialManager.h"

SoftwareSerial softwareserial(2, 3);

void SoftwareSerialManager::connect(int baud)
{
  softwareserial.begin(baud);
}

void SoftwareSerialManager::disconnect()
{
  softwareserial.end();
}

void SoftwareSerialManager::write(String data)
{
  softwareserial.println(data);
  softwareserial.flush();
}

String SoftwareSerialManager::read()
{
  String data = softwareserial.readString();
  return data;
}

bool SoftwareSerialManager::isAvailable()
{
  if (softwareserial.available() > 0)
  {
    return true;
  }
  return false;
}

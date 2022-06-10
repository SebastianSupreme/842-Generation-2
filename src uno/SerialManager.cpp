#include "SerialManager.h"

SuperSerial ss;

void SerialManager::connect(int baud)
{
  Serial.begin(baud);
}

void SerialManager::disconnect()
{
  Serial.end();
}

void SerialManager::write(String data)
{
  Serial.println(data);
}

String SerialManager::read()
{
  return Serial.readString();
}

void SerialManager::sendStringToJavaPC(String s)
{
  ss.write(s);
}

void SerialManager::sendIntToJavaPC(int i)
{
  ss.write(i);
}

String SerialManager::receiveStringFromJavaPC()
{
  return ss.readString();
}

int SerialManager::receiveIntFromJavaPC()
{
  return ss.readInt();
}

bool SerialManager::isAvailable()
{
  if (Serial.available() > 0)
  {
    return true;
  }
  return false;
}

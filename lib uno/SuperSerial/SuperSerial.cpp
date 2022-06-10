/*
SuperSerial.cpp - Library for serial communication with java "Serial" library
Created by Sebastian Köller
*/

#include <Arduino.h>
#include "SuperSerial.h"

SuperSerial::SuperSerial()
{
}

void SuperSerial::write(String s)
{
  String s2 = "@" + s + "#";
  Serial.println(s2);
  Serial.flush();
}

void SuperSerial::write(int i)
{
  String s = "@" + String(i) + "#";
  Serial.println(s);
  Serial.flush();
}

void SuperSerial::write(float f)
{
  String s = "@" + String(f) + "#";
  Serial.println(s);
  Serial.flush();
}

void SuperSerial::write(double d)
{
  String s = "@" + String(d) + "#";
  Serial.println(s);
  Serial.flush();
}

String SuperSerial::readString()
{
  String receivedDataString = "";

  receivedDataString += Serial.readString();
  receivedDataString.replace("null", "");
  receivedDataString.replace("\n", "");
  receivedDataString.replace("\r", "");
  if (receivedDataString.indexOf("@") > -1 && receivedDataString.indexOf("#") > receivedDataString.indexOf("@"))
  {
    receivedDataString = receivedDataString.substring(1, receivedDataString.indexOf("#"));
  }
  Serial.flush();
  return receivedDataString;
}

int SuperSerial::readInt()
{
  int receivedInt = -1;
  receivedInt = Serial.read();
  Serial.flush();
  return receivedInt;
}

float SuperSerial::readFloat()
{
  String receivedDataString = "";
  float receivedFloat = -1.0;

  receivedDataString += Serial.readString();
  receivedDataString.replace("null", "");
  receivedDataString.replace("\n", "");
  receivedDataString.replace("\r", "");
  if (receivedDataString.indexOf("@") > -1 && receivedDataString.indexOf("#") > receivedDataString.indexOf("@"))
  {
    receivedDataString = receivedDataString.substring(1, receivedDataString.indexOf("#"));
    receivedFloat = receivedDataString.toFloat();
  }
  Serial.flush();
  return receivedFloat;
}

double SuperSerial::readDouble()
{
  String receivedDataString = "";
  double receivedDouble = -1.0;

  receivedDataString += Serial.readString();
  receivedDataString.replace("null", "");
  receivedDataString.replace("\n", "");
  receivedDataString.replace("\r", "");
  if (receivedDataString.indexOf("@") > -1 && receivedDataString.indexOf("#") > receivedDataString.indexOf("@"))
  {
    receivedDataString = receivedDataString.substring(1, receivedDataString.indexOf("#"));
    receivedDouble = receivedDataString.toDouble();
  }
  Serial.flush();
  return receivedDouble;
}

/*
SuperSerial.h - Library for serial communication with java "Serial" library
Created by Sebastian Köller
*/

#ifndef SuperSerial_h
#define SuperSerial_h

#include "Arduino.h"

class SuperSerial
{

public:
    SuperSerial();
    void write(String s);
    void write(int i);
    void write(float f);
    void write(double d);

    String readString();
    int readInt();
    float readFloat();
    double readDouble();
};

#endif

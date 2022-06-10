#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

class SoftwareSerialManager
{

public:
    static void connect(int baud);

    static void write(String data);

    static String read();

    static bool isAvailable();
};
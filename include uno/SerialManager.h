#pragma once

#include "Arduino.h"
#include <SuperSerial.h>

class SerialManager
{

public:
    static void connect(int baud);

    static void disconnect();

    static void write(String data);

    static String read();

    static void sendStringToJavaPC(String s);

    static void sendIntToJavaPC(int i);

    static String receiveStringFromJavaPC();

    static int receiveIntFromJavaPC();

    static bool isAvailable();
};

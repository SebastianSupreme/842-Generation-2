#pragma once

#include "Arduino.h"
#include "BluetoothManager.h"
#include "SecurityManager.h"

extern bool passwordCorrect;
extern String defaultPasswort;

class SecurityManager
{

public:
    static void Sicherheitsanalyse();

    static String Encrypt(String input);

    static String Decrypt(String input);
};

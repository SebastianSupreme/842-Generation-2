#pragma once

#include <SoftwareSerial.h>
#include "DataManager.h"
#include "EingabeAnalyseUndVerarbeitung.h"

class BluetoothManager
{

public:
    static void setupBluetooth();

    static bool passwordEingabe();

    static void processInput();

    static void updateAusgabe();

    static void updateEingabe();

    static void write(String data);
};

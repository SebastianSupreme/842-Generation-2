#pragma once

#include <Arduino.h>
#include "SecurityManager.h"
#include "DataManager.h"
#include "Rechnen.h"
#include "SerialManager.h"
#include "SoftwareSerialManager.h"

extern String StringEingabe, Antwort, lastAntwort;
extern bool binaerwandlung, wirdGerechnet;
extern int Random, analogLevi, digitalLevi;
extern String randMini, randMaxi;

extern bool scanFor(String target);
extern void softReset();

class EingabeAnalyseUndVerarbeitung
{

public:
    static void AnalyseUndVerarbeitung();

    static void reset();

    static void newDigitalSA(String name, String text);

    static void newAnalogSA(String name, String text);
};

//Projekt 842 Generation 2
//Die künstliche Intelligenz und Assistentin 842 wurde von Sebastian Köller entwickelt.

#include <Arduino.h>
#include "Gehirn.h"
#include "SoftwareSerialManager.h"
#include "EingabeAnalyseUndVerarbeitung.h"

void setup()
{

    SoftwareSerialManager::connect(9600);
}

void loop()
{

    if (SoftwareSerialManager::isAvailable())
    {
        eingabe = SoftwareSerialManager::read();
        EingabeAnalyseUndVerarbeitung::AnalyseUndVerarbeitung();
    }
}
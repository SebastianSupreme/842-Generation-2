#pragma once

#include "Arduino.h"
#include "EingabeAnalyseUndVerarbeitung.h"

static double ergebnis, zahl1, zahl2;
static String rechenOperator = "";

class Rechnen
{

public:
    static String Berechnen(String StringEingabe, String mathAns);
};

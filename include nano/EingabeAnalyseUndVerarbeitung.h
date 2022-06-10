#pragma once

#include <Arduino.h>

extern String eingabe, ausgabe;

extern bool scanFor(String target);

class EingabeAnalyseUndVerarbeitung
{

public:
    static void AnalyseUndVerarbeitung();
};
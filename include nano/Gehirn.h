#pragma once

#include "Arduino.h"

extern String bildcode;

class Gehirn
{

public:
    static String Verarbeitung();
};

//Neuronen:

//Erste Stufe
char ObenLinks();

char ObenRechts();

char UntenLinks();

char UntenRechts();

//Zweite Stufe
char Top();

char Bottom();

char Left();

char Right();

char Slash();

char BackSlash();

//Dritte Stufe

char Full();

char Waagerecht();

char Senkrecht();

char Diagonal();

char EckeOL();

char EckeOR();

char EckeUL();

char EckeUR();

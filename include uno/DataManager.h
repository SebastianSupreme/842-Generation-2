#pragma once

#include "Arduino.h"
#include <EEPROM.h>

extern String notiz;
extern String mathAns;

class EEPROMFile
{

public:
  int start, finish;

  EEPROMFile(int Pstart, int Pfinish)
  {
    start = Pstart;
    finish = Pfinish;
  }
};

//Files
extern EEPROMFile notizFile;
extern EEPROMFile matheFile;
extern EEPROMFile bildFile;
extern EEPROMFile securityFile;
extern EEPROMFile systemFile;
extern EEPROMFile SAFiles[10];
extern EEPROMFile softResetFile;

class DataManager
{

public:
  static void write(EEPROMFile file, String data);

  static String read(EEPROMFile file);

  static void clearFile(EEPROMFile file);

  static void clearEEPROM();

  static boolean isEmpty(EEPROMFile file);
};

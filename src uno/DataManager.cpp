#include "DataManager.h"

String notiz = "";
String mathAns = "";

//Files
EEPROMFile notizFile(0, 99);
EEPROMFile matheFile(100, 149);
EEPROMFile bildFile(150, 199);
EEPROMFile securityFile(200, 249);
EEPROMFile SAFiles[10] = {EEPROMFile(250, 269), EEPROMFile(270, 289), EEPROMFile(290, 309), EEPROMFile(310, 329), EEPROMFile(330, 349),
                          EEPROMFile(350, 369), EEPROMFile(370, 389), EEPROMFile(390, 409), EEPROMFile(410, 429), EEPROMFile(430, 449)};
EEPROMFile softResetFile(450, 469);
EEPROMFile systemFile(900, 999);

void DataManager::write(EEPROMFile file, String data)
{

  int start = file.start;
  int finish = file.finish;
  char chars[100];
  byte bytes[100];
  data.toCharArray(chars, sizeof(chars));
  for (int i = start; i < finish; i++)
  {
    int j = i - start;
    bytes[j] = (byte)chars[j];
    EEPROM.update(i, bytes[j]);
  }
}

String DataManager::read(EEPROMFile file)
{

  String s = "";
  int start = file.start;
  int finish = file.finish;
  byte bytes[100];
  char chars[100];
  for (int i = start; i < finish; i++)
  {
    int j = i - start;
    bytes[j] = EEPROM.read(i);
    chars[j] = (char)bytes[j];
  }
  s = String(chars);
  return s;
}

void DataManager::clearFile(EEPROMFile file)
{
  int start = file.start;
  int finish = file.finish;
  for (int i = start; i < finish; i++)
  {
    EEPROM.update(i, 0);
  }
}

void DataManager::clearEEPROM()
{

  for (int i = 0; i < EEPROM.length(); i++)
  {
    EEPROM.update(i, 0);
  }
}

boolean DataManager::isEmpty(EEPROMFile file)
{
  int start = file.start;
  int finish = file.finish;
  int gesamtwert = 0;
  for (int i = start; i < finish; i++)
  {
    gesamtwert += EEPROM.read(i);
  }
  if (gesamtwert == 0)
  {
    return true;
  }
  return false;
}

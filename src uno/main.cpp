//Projekt 842 Generation 2
//Die künstliche Intelligenz und Assistentin 842 wurde von Sebastian Köller entwickelt.

#include <Arduino.h>
#include "EingabeAnalyseUndVerarbeitung.h"
#include "SoftwareSerialManager.h"
#include "DataManager.h"
#include "BluetoothManager.h"
#include "SecurityManager.h"

void setup()
{

  BluetoothManager::setupBluetooth();

  if (DataManager::isEmpty(systemFile) == true && DataManager::isEmpty(softResetFile) == true)
  {
    if (DataManager::isEmpty(securityFile) == true)
    {
      Antwort = F("Gib bitte das Standardpasswort ein.");
      BluetoothManager::updateAusgabe();
    }
    else
    {
      Antwort = F("Gib bitte das Passwort ein.");
      BluetoothManager::updateAusgabe();
    }
  }
  if (DataManager::isEmpty(systemFile) == false)
  {
    StringEingabe = DataManager::read(systemFile);
    EingabeAnalyseUndVerarbeitung::AnalyseUndVerarbeitung();
    DataManager::clearFile(systemFile);
    if (scanFor("analysiere bild neu"))
    {
      StringEingabe = "";
      BluetoothManager::updateAusgabe();
      softReset();
    }
  }
  if (DataManager::isEmpty(softResetFile) == false)
  {
    DataManager::clearFile(softResetFile);
    passwordCorrect = true;
  }
}

void loop()
{

  if (passwordCorrect == true)
  {

    BluetoothManager::processInput();
    BluetoothManager::updateAusgabe();
  }
  else
  {
    if (BluetoothManager::passwordEingabe())
    {
      SecurityManager::Sicherheitsanalyse();
      BluetoothManager::updateAusgabe();
    }
  }
}
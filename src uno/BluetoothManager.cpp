#include "BluetoothManager.h"

SoftwareSerial btss(4, 5);

void BluetoothManager::setupBluetooth()
{
  btss.begin(9600);
}

bool BluetoothManager::passwordEingabe()
{
  if (btss.available() > 0)
  {
    StringEingabe = btss.readString();
    return true;
  }
  return false;
}

void BluetoothManager::processInput()
{
  if (btss.available() > 0)
  {
    StringEingabe = btss.readString();
    EingabeAnalyseUndVerarbeitung::AnalyseUndVerarbeitung();
  }
}

void BluetoothManager::updateAusgabe()
{
  if (Antwort != lastAntwort)
  {
    btss.println(Antwort);
    btss.flush();
    lastAntwort = Antwort;
  }
}

void BluetoothManager::updateEingabe(){
   if (btss.available() > 0)
  {
    StringEingabe = btss.readString();
  }
}

void BluetoothManager::write(String data)
{
  btss.println(data);
  btss.flush();
}

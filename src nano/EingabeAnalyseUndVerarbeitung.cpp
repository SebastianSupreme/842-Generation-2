#include "EingabeAnalyseUndVerarbeitung.h"
#include "Gehirn.h"
#include "Rechnen.h"
#include "SoftwareSerialManager.h"

String eingabe = "", ausgabe = "";

bool scanFor(String target)
{
  if (eingabe.indexOf(target) >= 0)
  {
    return true;
  }
  return false;
}

void EingabeAnalyseUndVerarbeitung::AnalyseUndVerarbeitung()
{

  //Analysiere Bild
  if (scanFor("Gehirn"))
  {
    bildcode = eingabe.substring(eingabe.indexOf(" ") + 1, eingabe.length());
    SoftwareSerialManager::write(Gehirn::Verarbeitung());
    delay(1500);
    return;
  }

  //Rechnen
  if (scanFor("Rechnen"))
  {

    String zwischenString = eingabe.substring(eingabe.indexOf(" ") + 1, eingabe.length());
    String mathAnswer = zwischenString.substring(0, zwischenString.indexOf(" "));
    String rechnung = zwischenString.substring(zwischenString.indexOf(" ") + 1, zwischenString.length());

    SoftwareSerialManager::write(Rechnen::Berechnen(rechnung, mathAnswer));
    delay(1500);
    return;
  }
}
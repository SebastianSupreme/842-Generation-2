#include "Rechnen.h"

void Rechnen::IntZuByteUmwandeln()
{

  String s = StringEingabe;
  int eingabe = s.toInt();
  String b = "";
  if (eingabe <= 255 && eingabe >= 0)
  {
    for (byte i = 0; i < 8; i++)
    {

      if (eingabe % 2 == 1)
      {
        b = '1' + b;
      }
      if (eingabe % 2 == 0)
      {
        b = '0' + b;
      }
      eingabe /= 2;
    }

    Antwort = b;
  }
  else
  {
    if (eingabe < 0)
    {
      Antwort = "Fehler! Die Zahl ist zu klein.";
    }
    if (eingabe > 255)
    {
      Antwort = "Fehler! Die Zahl ist zu groß.";
    }
  }
}

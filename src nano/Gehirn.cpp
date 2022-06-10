#include "Gehirn.h"

String bildcode = "";

String Gehirn::Verarbeitung()
{

  String antwort;

  if (Full() == 1)
  {
    antwort = F("Das Bild ist komplett weiß.");
  }
  else if (Full() == 0)
  {
    antwort = F("Das Bild ist komplett schwarz.");
  }
  else if (Waagerecht() == 1)
  {
    antwort = F("Das Bild ist weiß-schwarz waagerecht gestreift.");
  }
  else if (Waagerecht() == 0)
  {
    antwort = F("Das Bild ist schwarz-weiß waagerecht gestreift.");
  }
  else if (Senkrecht() == 1)
  {
    antwort = F("Das Bild ist weiß-schwarz senkrecht gestreift.");
  }
  else if (Senkrecht() == 0)
  {
    antwort = F("Das Bild ist schwarz-weiß senkrecht gestreift.");
  }
  else if (Diagonal() == 1)
  {
    antwort = F("Das Bild ist schwarz-weiß-weiß-schwarz kariert.");
  }
  else if (Diagonal() == 0)
  {
    antwort = F("Das Bild ist weiß-schwarz-schwarz-weiß kariert.");
  }
  else if (EckeOL() == 1)
  {
    antwort = F("Das Bild hat unten-rechts eine schwarze Ecke.");
  }
  else if (EckeOL() == 0)
  {
    antwort = F("Das Bild hat unten-rechts eine weiße Ecke.");
  }
  else if (EckeOR() == 1)
  {
    antwort = F("Das Bild hat unten-linkseine schwarze Ecke.");
  }
  else if (EckeOR() == 0)
  {
    antwort = F("Das Bild hat unten-links eine weiße Ecke.");
  }
  else if (EckeUL() == 1)
  {
    antwort = F("Das Bild hat oben-rechts eine schwarze Ecke.");
  }
  else if (EckeUL() == 0)
  {
    antwort = F("Das Bild hat oben-rechts eine weiße Ecke.");
  }
  else if (EckeUR() == 1)
  {
    antwort = F("Das Bild hat oben-links eine schwarze Ecke.");
  }
  else if (EckeUR() == 0)
  {
    antwort = F("Das Bild hat oben-links eine weiße Ecke.");
  }

  return antwort;
}

//Neuronen:

//Erste Stufe

char ObenLinks()
{
  if (bildcode.substring(0, 3) == "255")
  {
    return 1;
  }
  if (bildcode.substring(0, 3) == "000")
  {
    return 0;
  }
  return 'x';
}

char ObenRechts()
{
  if (bildcode.substring(3, 6) == "255")
  {
    return 1;
  }
  if (bildcode.substring(3, 6) == "000")
  {
    return 0;
  }
  return 'x';
}

char UntenLinks()
{
  if (bildcode.substring(6, 9) == "255")
  {
    return 1;
  }
  if (bildcode.substring(6, 9) == "000")
  {
    return 0;
  }
  return 'x';
}

char UntenRechts()
{
  if (bildcode.substring(9, 12) == "255")
  {
    return 1;
  }
  if (bildcode.substring(9, 12) == "000")
  {
    return 0;
  }
  return 'x';
}

//Zweite Stufe
char Top()
{

  if (ObenLinks() == 1 && ObenRechts() == 1)
  {
    return 1;
  }
  else if (ObenLinks() == 0 && ObenRechts() == 0)
  {
    return 0;
  }
  return 'x';
}

char Bottom()
{

  if (UntenLinks() == 1 && UntenRechts() == 1)
  {
    return 1;
  }
  else if (UntenLinks() == 0 && UntenRechts() == 0)
  {
    return 0;
  }
  return 'x';
}

char Left()
{

  if (ObenLinks() == 1 && UntenLinks() == 1)
  {
    return 1;
  }
  else if (ObenLinks() == 0 && UntenLinks() == 0)
  {
    return 0;
  }
  return 'x';
}

char Right()
{

  if (ObenRechts() == 1 && UntenRechts() == 1)
  {
    return 1;
  }
  else if (ObenRechts() == 0 && UntenRechts() == 0)
  {
    return 0;
  }
  return 'x';
}

char Slash()
{

  if (UntenLinks() == 1 && ObenRechts() == 1)
  {
    return 1;
  }
  else if (UntenLinks() == 0 && ObenRechts() == 0)
  {
    return 0;
  }
  return 'x';
}

char BackSlash()
{

  if (ObenLinks() == 1 && UntenRechts() == 1)
  {
    return 1;
  }
  else if (ObenLinks() == 0 && UntenRechts() == 0)
  {
    return 0;
  }
  return 'x';
}

//Dritte Stufe

char Full()
{

  if (Top() == 1 && Bottom() == 1 && Left() == 1 && Right() == 1 && Slash() == 1 && BackSlash() == 1)
  {
    return 1;
  }
  else if (Top() == 0 && Bottom() == 0 && Left() == 0 && Right() == 0 && Slash() == 0 && BackSlash() == 0)
  {
    return 0;
  }
  return 'x';
}

char Waagerecht()
{

  if (Top() == 1 && Bottom() == 0)
  {
    return 1;
  }
  else if (Top() == 0 && Bottom() == 1)
  {
    return 0;
  }
  return 'x';
}

char Senkrecht()
{

  if (Left() == 1 && Right() == 0)
  {
    return 1;
  }
  else if (Left() == 0 && Right() == 1)
  {
    return 0;
  }
  return 'x';
}

char Diagonal()
{

  if (Slash() == 1 && BackSlash() == 0)
  {
    return 1;
  }
  else if (Slash() == 0 && BackSlash() == 1)
  {
    return 0;
  }
  return 'x';
}

char EckeOL()
{

  if (Left() == 1 && Top() == 1 && UntenRechts() == 0)
  {
    return 1;
  }
  else if (Left() == 0 && Top() == 0 && UntenRechts() == 1)
  {
    return 0;
  }
  return 'x';
}

char EckeOR()
{

  if (Right() == 1 && Top() == 1 && UntenLinks() == 0)
  {
    return 1;
  }
  else if (Right() == 0 && Top() == 0 && UntenLinks() == 1)
  {
    return 0;
  }
  return 'x';
}

char EckeUL()
{

  if (Left() == 1 && Bottom() == 1 && ObenRechts() == 0)
  {
    return 1;
  }
  else if (Left() == 0 && Bottom() == 0 && ObenRechts() == 1)
  {
    return 0;
  }
  return 'x';
}

char EckeUR()
{

  if (Right() == 1 && Bottom() == 1 && ObenLinks() == 0)
  {
    return 1;
  }
  else if (Right() == 0 && Bottom() == 0 && ObenLinks() == 1)
  {
    return 0;
  }
  return 'x';
}

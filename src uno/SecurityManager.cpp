#include "SecurityManager.h"

bool passwordCorrect = false;
String defaultPasswort = "geh dahin";

void SecurityManager::Sicherheitsanalyse()
{
  if (Antwort == F("Gib bitte das Standardpasswort ein."))
  {
    if (StringEingabe == defaultPasswort)
    {
      passwordCorrect = true;
      Antwort = "Hallo.";
    }
  }
  else if (Antwort == F("Gib bitte das Passwort ein."))
  {
    if (StringEingabe == SecurityManager::Decrypt(DataManager::read(securityFile)))
    {
      passwordCorrect = true;
      Antwort = "Hallo.";
    }
  }
}

String SecurityManager::Encrypt(String input)
{

  input = String(input) + " ";
  String output = "";
  char ca[input.length()];
  byte ba[input.length()];
  input.toCharArray(ca, sizeof(ca));

  for (byte i = 0; i < input.length(); i++)
  {
    ba[i] = (byte)ca[i];
    ba[i] -= 10;
    ba[i] *= 2;
    ba[i] += 5;
    ca[i] = (char)ba[i];
    output += ca[i];
  }
  return output;
}

String SecurityManager::Decrypt(String input)
{

  String output = "";
  char ca[input.length()];
  byte ba[input.length()];
  input.toCharArray(ca, sizeof(ca));

  for (byte i = 0; i < input.length(); i++)
  {
    ba[i] = (byte)ca[i];
    ba[i] -= 5;
    ba[i] /= 2;
    ba[i] += 10;
    ca[i] = (char)ba[i];
    output += ca[i];
  }
  output = output.substring(0, output.length() - 1);
  return output;
}

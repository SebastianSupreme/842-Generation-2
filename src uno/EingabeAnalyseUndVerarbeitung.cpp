#include "EingabeAnalyseUndVerarbeitung.h"

String StringEingabe = "", Antwort = "Hallo.", lastAntwort = "Hallo.", randMini = "", randMaxi = "";
bool binaerwandlung = false, wirdGerechnet = false;
byte zwischenWert = 0;
int Random = 0, analogLevi, digitalLevi;

bool scanFor(String target)
{
  if (StringEingabe.indexOf(target) >= 0)
  {
    return true;
  }
  return false;
}

void softReset()
{
  DataManager::write(softResetFile, "softReset");
  EingabeAnalyseUndVerarbeitung::reset();
}

void EingabeAnalyseUndVerarbeitung::AnalyseUndVerarbeitung()
{

  //System:

  //Für wiederholendes Rechnen
  if (scanFor("newCalc"))
  {
    StringEingabe = "";
    wirdGerechnet = true;
    return;
  }

  if (Antwort == F("Schreibe deine Notiz in das Textfeld."))
  {
    notiz = StringEingabe;
    DataManager::write(notizFile, notiz);
    Antwort = F("Notiz gespeichert.");
    return;
  }

  if (Antwort == F("Gib bitte ein, was ich über Bluetooth senden soll."))
  {
    Antwort = "Gesendet.";
    BluetoothManager::updateAusgabe();
    delay(1000);
    BluetoothManager::write(StringEingabe);
    return;
  }

  if (Antwort == F("Gib bitte ein, was ich über die serielle Schnittstelle an ein Java-Programm senden soll."))
  {
    SerialManager::connect(9600);
    SerialManager::sendStringToJavaPC(StringEingabe);
    SerialManager::disconnect();
    Antwort = "Gesendet.";
    BluetoothManager::updateAusgabe();
    softReset();
    return;
  }
  else if (Antwort == F("Gib bitte ein, was ich über die serielle Schnittstelle senden soll."))
  {
    SerialManager::connect(9600);
    SerialManager::write(StringEingabe);
    SerialManager::disconnect();
    Antwort = "Gesendet.";
    BluetoothManager::updateAusgabe();
    softReset();
    return;
  }

  //Befehle:

  //Informationstechnik:

  //ok
  if (scanFor(F("ok")) || scanFor(F("fertig")) || scanFor(F("okay")) || scanFor(F("beenden")))
  {
    if (binaerwandlung == true)
    {
      binaerwandlung = false;
    }
    if (wirdGerechnet == true)
    {
      wirdGerechnet = false;
    }
    Antwort = "";
    return;
  }

  //lösche alles
  if (scanFor(F("lösch")) || scanFor(F("entfern")))
  {
    if (scanFor(F("alles")))
    {
      DataManager::clearEEPROM();
      Antwort = F("Alles gelöscht.");
      return;
    }
    else if (scanFor("notiz"))
    {
      DataManager::clearFile(notizFile);
      Antwort = "Notiz gelöscht.";
      return;
    }
  }

  //hallo
  if (scanFor(F("hallo")) || scanFor(F("guten tag")) || scanFor(F("hey")) || scanFor(F("hello")))
  {

    Random = random(1, 101);

    if (Random > 50)
    {
      Antwort = F("Was kann ich für dich tun?");
    }
    else if (Random <= 50 && Random >= 0)
    {
      Antwort = F("Womit kann ich dir helfen?");
    }

    return;
  }

  // rechne
  if (scanFor(F("rechne")) || scanFor(F("kalkuliere")))
  {
    Antwort = F("Bitte gib deine Rechnung ein.");
    return;
  }
  if (Antwort == F("Bitte gib deine Rechnung ein.") || wirdGerechnet == true)
  {
    String ergebnis = "";
    String mathAnswer = DataManager::read(matheFile);
    String dataToSend = mathAnswer + " " + StringEingabe;

    SoftwareSerialManager::connect(9600);
    SoftwareSerialManager::write(String("Rechnen ") + dataToSend);

    while (!SoftwareSerialManager::isAvailable())
    {
      delay(1);
    }
    ergebnis = SoftwareSerialManager::read();
    SoftwareSerialManager::disconnect();

    Antwort = "Das Ergebnis ist " + String(ergebnis) + ".";
    BluetoothManager::updateAusgabe();
    mathAnswer = String(ergebnis);
    DataManager::write(matheFile, mathAnswer);
    DataManager::write(systemFile, "newCalc");

    softReset();
    return;
  }

  //Wandle Binärzahl um
  if ((scanFor(F("wandle")) || scanFor(F("wandel")) || scanFor(F("wandlung")) || scanFor(F("forme"))) && scanFor(F("binär")))
  {
    binaerwandlung = true;
    Antwort = F("Bitte gib eine Zahl von 0 bis 255 ein.");
    return;
  }
  if (Antwort == F("Bitte gib eine Zahl von 0 bis 255 ein.") || binaerwandlung == true)
  {
    Rechnen::IntZuByteUmwandeln();
    return;
  }

  // schreibe eine notiz
  if ((scanFor(F("schreib")) || scanFor(F("write"))) && scanFor(F("notiz")))
  {
    Antwort = F("Schreibe deine Notiz in das Textfeld.");
    return;
  }

  // lies meine notiz
  if ((scanFor(F("les")) || scanFor(F("lies")) || scanFor(F("read"))) && scanFor(F("notiz")))
  {
    notiz = DataManager::read(notizFile);
    Antwort = notiz;
    return;
  }

  //danke
  if (scanFor(F("danke")))
  {
    Random = random(1, 101);
    if (Random >= 50)
    {
      Antwort = F("Bitte.");
    }
    else if (Random >= 0 && Random < 50)
    {
      Antwort = F("Immer gerne.");
    }
    return;
  }

  // wer bist du
  if ((scanFor(F("wer")) || scanFor(F("was"))) && scanFor(F("bist du")))
  {
    Random = random(1, 101);
    if (Random >= 66)
    {
      Antwort = F("Ich bin 842, eine künstliche Intelligenz.");
    }
    else if (Random >= 33 && Random < 66)
    {
      Antwort = F("Ich bin die Assistentin von Sebastian Köller.");
    }
    else if (Random < 33 && Random >= 0)
    {
      Antwort = F("Ich bin das Betriebssystem der Mikrocontroller.");
    }
    return;
  }

  // wer hat dich entwickelt
  if (scanFor(F("wer hat dich")) && (scanFor(F("entwickelt")) || scanFor(F("erschaffen"))))
  {
    Antwort = F("Ich wurde von Sebastian Köller entwickelt.");
    return;
  }

  //neustart
  if (scanFor(F("neustart")) || scanFor(F("reset")))
  {
    void (*resetFunc)(void) = 0;
    resetFunc();
  }

  //zufallszahl
  if (scanFor(F("zufallszahl")))
  {

    Antwort = F("Gib bitte das Minimum ein.");
    return;
  }
  if (Antwort == F("Gib bitte das Minimum ein."))
  {
    randMini = StringEingabe;
    Antwort = F("Gib bitte das Maximum ein.");
    return;
  }
  if (Antwort == F("Gib bitte das Maximum ein."))
  {
    randMaxi = StringEingabe;
    Antwort = String(random(randMini.toInt(), randMaxi.toInt() + 1));
    return;
  }

  //analysiere bild
  if (scanFor(F("analysiere")) && scanFor(F("bild")))
  {

    if (scanFor(F("neu")))
    {
      if (DataManager::isEmpty(systemFile) == true)
      {
        DataManager::write(systemFile, "analysiere bild neu");
        Antwort = F("Schließe einen Computer an und starte Image Processor.jar");
        return;
      }

      SerialManager::connect(9600);
      while (!SerialManager::isAvailable())
      {
        delay(1);
      }
      String bildcode = SerialManager::receiveStringFromJavaPC();
      SerialManager::disconnect();

      DataManager::write(bildFile, bildcode);
      Antwort = F("Image Processor.jar kann jetzt geschlossen werden.");
      BluetoothManager::updateAusgabe();

      SoftwareSerialManager::connect(9600);
      SoftwareSerialManager::write(String("Gehirn ") + bildcode);

      while (!SoftwareSerialManager::isAvailable())
      {
        delay(1);
      }
      Antwort = SoftwareSerialManager::read();
      SoftwareSerialManager::disconnect();
      return;
    }
    else if (scanFor(F("letzte")))
    {

      String bildcode = DataManager::read(bildFile);
      SoftwareSerialManager::connect(9600);
      SoftwareSerialManager::write(String("Gehirn ") + bildcode);

      while (!SoftwareSerialManager::isAvailable())
      {
        delay(1);
      }
      Antwort = SoftwareSerialManager::read();
      SoftwareSerialManager::disconnect();
      BluetoothManager::updateAusgabe();
      softReset();
      return;
    }
  }

  //neues passwort & löschen
  if (scanFor(F("passwort")))
  {
    if (scanFor(F("neu")))
    {
      Antwort = F("Gib bitte das neue Passwort ein.");
    }
    else if (scanFor(F("lösch")) || scanFor(F("entfern")))
    {
      DataManager::clearFile(securityFile);
      Antwort = F("Passwort gelöscht.");
    }
    return;
  }
  else if (Antwort == F("Gib bitte das neue Passwort ein."))
  {
    DataManager::write(securityFile, SecurityManager::Encrypt(StringEingabe));
    //save(securityFile, StringEingabe);
    Antwort = F("Passwort gespeichert.");
    return;
  }

  if (scanFor("sende"))
  {
    //Sende über Bluetooth
    if (scanFor("bluetooth"))
    {
      Antwort = F("Gib bitte ein, was ich über Bluetooth senden soll.");
      return;
    }

    //Sende über Serial
    if (scanFor("serial"))
    {
      //An Java-Proramm
      if (scanFor("java"))
      {
        Antwort = F("Gib bitte ein, was ich über die serielle Schnittstelle an ein Java-Programm senden soll.");
        return;
      }
      else
      {
        Antwort = F("Gib bitte ein, was ich über die serielle Schnittstelle senden soll.");
        return;
      }
    }
  }

  //Elektrotechnik:

  //Elektromagnetische Levitation
  if(scanFor(F("levitation")) && (scanFor(F("aktivier")) || scanFor(F("starte")))){
      Antwort = F("Gib bitte ein, an welchem Pin der Hall-Sensor angeschlossen ist.");
      return;
  }
  if(Antwort == F("Gib bitte ein, an welchem Pin der Hall-Sensor angeschlossen ist.")){
    analogLevi = StringEingabe.toInt();
    Antwort = F("Gib bitte nun ein, an welchem Pin der Transistor angeschlossen ist.");
    return;
  }
  if(Antwort == F("Gib bitte nun ein, an welchem Pin der Transistor angeschlossen ist.")){
    digitalLevi = StringEingabe.toInt();
    Antwort = F("Levitationsgerät wird gesteuert...");
    BluetoothManager::updateAusgabe();
    pinMode(digitalLevi, OUTPUT);

    while(!(scanFor("deaktivier") || scanFor("stopp"))){

      if(analogRead(analogLevi) >= 785){
        digitalWrite(digitalLevi, LOW);
      }else {
        digitalWrite(digitalLevi, HIGH);
      }

      BluetoothManager::updateEingabe();
    }
    digitalWrite(digitalLevi, LOW);

    Antwort = F("Steuerung des Levitationsgerätes wurde beendet.");
    return;
  }

  if (scanFor(F("pin")))
  {

    //AnalogWrite
    if (scanFor(F("pwm")))
    {
      for (int i = 13; i >= 0; i--)
      {
        if (scanFor(String(i)))
        {
          Antwort = F("Auf welchen Wert soll der PWM-Pin gesetzt werden?");
          zwischenWert = i;
          return;
        }
      }
    }

    //DigitalWrite
    if (scanFor(F("high")))
    {
      for (int i = 13; i >= 0; i--)
      {
        if (scanFor(String(i)))
        {
          pinMode(i, OUTPUT);
          digitalWrite(i, HIGH);
          Antwort = String(F("Pin ")) + String(i) + F(" auf High gesetzt.");
          return;
        }
      }
    }
    else if (scanFor(F("low")))
    {
      for (int i = 13; i >= 0; i--)
      {
        if (scanFor(String(i)))
        {
          pinMode(i, OUTPUT);
          digitalWrite(i, LOW);
          Antwort = String(F("Pin ")) + String(i) + F(" auf Low gesetzt.");
          return;
        }
      }
    }

    if (scanFor(F("les")) || scanFor(F("lies")) || scanFor(F("read")))
    {

      //AnalogRead
      for (byte i = 0; i < 6; i++)
      {
        if (scanFor(String("a") + String(i)))
        {
          Antwort = String(analogRead(i));
          return;
        }
      }
      //DigitalRead
      for (int i = 13; i >= 0; i--)
      {
        if (scanFor(String(i)))
        {
          pinMode(i, INPUT);
          Antwort = String(digitalRead(i));
          return;
        }
      }
    }

    //Spannungsmessung
    if ((scanFor("miss") || scanFor("mess")) && scanFor("spannung"))
    {
      for (byte i = 0; i < 6; i++)
      {
        if (scanFor(String("a") + String(i)))
        {
          int val = analogRead(i);
          float volt = (val / 1024.0) * 5.0;
          Antwort = "Die Spannung an Pin A" + String(i) + " beträgt " + volt + " Volt.";
          return;
        }
      }
    }
  }
  else if (Antwort == F("Auf welchen Wert soll der PWM-Pin gesetzt werden?"))
  {
    byte b = (byte)StringEingabe.toInt();
    pinMode(zwischenWert, OUTPUT);
    analogWrite(zwischenWert, b);
    Antwort = String(F("Pin ")) + String(zwischenWert) + F(" auf ") + String(b) + F(" gesetzt.");
    return;
  }

  //Was ist auf Pin ...
  if (scanFor(F("pin")) && (scanFor(F("was")) || scanFor(F("belegt"))))
  {
    for (byte i = 0; i < 6; i++)
    {
      if (scanFor(String("a") + String(i)))
      {
        for (byte j = 0; j < 10; j++)
        {
          if (DataManager::read(SAFiles[j]).substring(0, DataManager::read(SAFiles[j]).indexOf(" ")) == (String("a") + String(i)))
          {
            Antwort = DataManager::read(SAFiles[j]);
            return;
          }
        }
        Antwort = F("Dieser Pin ist nicht belegt.");
        return;
      }
    }
    for (int i = 13; i >= 0; i--)
    {
      if (scanFor(String(i)))
      {
        for (byte j = 0; j < 10; j++)
        {
          if (DataManager::read(SAFiles[j]).substring(0, DataManager::read(SAFiles[j]).indexOf(" ")).toInt() == i)
          {
            Antwort = DataManager::read(SAFiles[j]);
            return;
          }
        }
        Antwort = F("Dieser Pin ist nicht belegt.");
        return;
      }
    }
    return;
  }

  //Lösche Pin
  if ((scanFor(F("lösch")) || scanFor(F("entfern"))) && scanFor("pin"))
  {
    if (!scanFor(F("alle")))
    {

      //Analog Pins
      for (byte i = 0; i < 6; i++)
      {
        if (scanFor(String("a") + String(i)))
        {
          for (byte j = 0; j < 10; j++)
          {
            if (DataManager::read(SAFiles[j]).substring(0, DataManager::read(SAFiles[j]).indexOf(" ")) == (String("a") + String(i)))
            {

              DataManager::clearFile(SAFiles[j]);
              Antwort = F("Sensor/Aktor entfernt.");
              return;
            }
          }
          Antwort = F("Dieser Pin ist nicht belegt.");
          return;
        }
      }

      //Digital Pins
      for (int i = 13; i >= 0; i--)
      {
        if (scanFor(String(i)))
        {
          for (byte j = 0; j < 10; j++)
          {
            if (DataManager::read(SAFiles[j]).substring(0, DataManager::read(SAFiles[j]).indexOf(" ")).toInt() == i)
            {

              DataManager::clearFile(SAFiles[j]);
              Antwort = F("Sensor/Aktor entfernt.");
              return;
            }
          }
          Antwort = F("Dieser Pin ist nicht belegt.");
          return;
        }
      }
      Antwort = F("Diesen Pin gibt es nicht.");
      return;
    }
    else
    {
      for (byte i = 0; i < 10; i++)
      {
        DataManager::clearFile(SAFiles[i]);
      }
      Antwort = F("Alle Sensoren/Aktoren entfernt.");
      return;
    }
  }

  //Sensoren und Aktoren
  if (scanFor(F("sensor")) || scanFor(F("aktor")) || scanFor("schalter") || scanFor("piezo"))
  {

    //Neuer Sensor/Aktor
    if (scanFor(F("neu")))
    {

      byte notEmpty = 0;
      for (byte i = 0; i < 10; i++) //10 = SAFiles.length()
      {
        if (DataManager::isEmpty(SAFiles[i]) == false)
        {
          notEmpty++;
        }
      }
      if (notEmpty == 10)
      {
        Antwort = F("Kein freier Platz mehr verfügbar.");
        return;
      }

      //Digitale Sensoren/Aktoren

      //Kippschalter
      if (scanFor("kippschalter"))
      {
        newDigitalSA("kipp", "Kippschalter");
        return;
      }

      //Piezo-Element
      else if (scanFor("piezo"))
      {
        newDigitalSA("piezo", "Piezo-Element");
        return;
      }

      //Analoge Sensoren/Aktoren

      //Temperatursensor
      if (scanFor(F("temperatur")))
      {
        newAnalogSA("temperatur", "Temperatursensor");
        return;
      }

      //Lichtsensor
      else if (scanFor(F("licht")))
      {
        newAnalogSA("licht", "Lichtsensor");
        return;
      }

      //Hallsensor
      else if (scanFor("hall"))
      {
        newAnalogSA("hall", "Hall-Sensor");
        return;
      }
    }
  }

  //Produziere Ton
  if ((scanFor("erzeuge") || scanFor("produziere")) && scanFor("ton"))
  {
    Antwort = F("Gib bitte die Frequenz ein, die gespielt werden soll.");
    return;
  }
  if (scanFor("leise") || scanFor("ruhe") || scanFor("stopp"))
  {
    for (byte i = 0; i < 10; i++)
    {
      if (DataManager::read(SAFiles[i]).indexOf(F("piezo")) >= 0)
      {
        String s = DataManager::read(SAFiles[i]).substring(0, DataManager::read(SAFiles[i]).indexOf(" "));
        int pin = s.toInt();
        noTone(pin);
        Antwort = "Tonausgabe angehalten.";
        return;
      }
    }
    Antwort = F("Ich kann kein Piezo-Element finden.");
    return;
  }
  if (Antwort == F("Gib bitte die Frequenz ein, die gespielt werden soll."))
  {
    long frequenz;
    int pin;
    for (byte i = 0; i < 10; i++)
    {
      if (DataManager::read(SAFiles[i]).indexOf(F("piezo")) >= 0)
      {
        String s = DataManager::read(SAFiles[i]).substring(0, DataManager::read(SAFiles[i]).indexOf(" "));
        pin = s.toInt();
        frequenz = StringEingabe.toInt();
        tone(pin, frequenz);
        Antwort = "Ton mit der Frequenz " + String(frequenz) + " Hz wird gespielt.";
        return;
      }
    }
    Antwort = F("Ich kann kein Piezo-Element finden.");
    return;
  }

  //Miss Ausrichtung
  if ((scanFor("miss") || scanFor("mess")) && scanFor("ausrichtung"))
  {
    int value;
    int pin;
    for (byte i = 0; i < 10; i++)
    {
      if (DataManager::read(SAFiles[i]).indexOf(F("kipp")) >= 0)
      {
        String s = DataManager::read(SAFiles[i]).substring(0, DataManager::read(SAFiles[i]).indexOf(" "));
        pin = s.toInt();
        value = digitalRead(pin);
        if (value == 1)
        {
          Antwort = String(F("Die Ausrichtung beträgt 0°."));
        }
        else
        {
          Antwort = String(F("Die Ausrichtung beträgt 180°."));
        }
        return;
      }
    }
    Antwort = F("Ich kann keinen Kippschalter finden.");
    return;
  }

  //Miss Magnetfeld
  if ((scanFor("miss") || scanFor("mess")) && scanFor("magnetfeld"))
  {
    int value;
    float voltage;
    float magnetField;
    int pin;
    for (byte i = 0; i < 10; i++)
    {
      if (DataManager::read(SAFiles[i]).indexOf(F("hall")) >= 0)
      {
        String s = DataManager::read(SAFiles[i]).substring(0, DataManager::read(SAFiles[i]).indexOf(" "));
        s.replace("a", "");
        pin = s.toInt();
        value = analogRead(pin);
        voltage = (value / 1024.0) * 5.0;
        magnetField = ((voltage - 2.5) * 320) / 10000;
        Antwort = String(F("Die Magnetfeldstärke beträgt ")) + String(magnetField) + F(" Tesla.");
        return;
      }
    }
    Antwort = F("Ich kann keinen Hall-Sensor finden.");
    return;
  }

  //Wie hell ist es
  if (scanFor(F("wie")) && scanFor(F("hell")))
  {
    int lightVal;
    int light;
    int pin;
    for (byte i = 0; i < 10; i++)
    {
      if (DataManager::read(SAFiles[i]).indexOf(F("licht")) >= 0)
      {
        String s = DataManager::read(SAFiles[i]).substring(0, DataManager::read(SAFiles[i]).indexOf(" "));
        s.replace("a", "");
        pin = s.toInt();
        lightVal = analogRead(pin);
        light = lightVal / 4;
        Antwort = String(F("Die Helligkeit beträgt ")) + String(light) + F(" RGB.");
        return;
      }
    }
    Antwort = F("Ich kann keinen Lichtsensor finden.");
    return;
  }

  //wie warm ist es
  if (scanFor(F("wie")) && (scanFor(F("warm")) || scanFor(F("grad"))))
  {
    int pin;
    int pinVal;
    float voltage;
    float temperature;
    for (byte i = 0; i < 10; i++)
    {
      if (DataManager::read(SAFiles[i]).indexOf(F("temperatur")) >= 0)
      {
        String s = DataManager::read(SAFiles[i]).substring(0, DataManager::read(SAFiles[i]).indexOf(" "));
        s.replace("a", "");
        pin = s.toInt();
        pinVal = analogRead(pin);
        voltage = (pinVal / 1024.0) * 5.0;
        temperature = (voltage - 0.5) * 100;
        Antwort = String(F("Die Temperatur beträgt ")) + String(temperature) + F(" °C.");
        return;
      }
    }
    Antwort = F("Ich kann keinen Temperatursensor finden.");
    return;
  }

  // nicht bekannt
  else
  {

    Random = random(1, 101);

    if (Random >= 66)
    {
      Antwort = F("Bitte wiederhole die Eingabe.");
    }
    else if (Random >= 33 && Random < 66)
    {
      Antwort = F("Entschuldigung, ich habe dich nicht verstanden.");
    }
    else if (Random < 33 && Random >= 0)
    {
      Antwort = F("Dieser Befehl befindet sich nicht in meiner Datenbank.");
    }
    return;
  }
}

void (*resetFunc)(void) = 0;
void EingabeAnalyseUndVerarbeitung::reset()
{
  resetFunc();
}

void EingabeAnalyseUndVerarbeitung::newDigitalSA(String name, String text)
{

  for (int i = 13; i >= 0; i--)
  {
    if (scanFor(String(i)))
    {
      //Gibts einen sensor mit demselben pin? Weg!
      for (byte j = 0; j < 10; j++)
      {
        String s = DataManager::read(SAFiles[j]);
        String s2 = s.substring(0, s.indexOf(" "));
        if (String(i) == s2)
        {
          DataManager::clearFile(SAFiles[j]);
        }
      }
      //Freien Platz suchen
      for (byte j = 0; j < 10; j++)
      {
        if (DataManager::isEmpty(SAFiles[j]) == true)
        {
          DataManager::write(SAFiles[j], String(i) + " " + name);
          Antwort = String(text) + " auf Pin " + String(i) + F(" gesetzt.");
          return;
        }
      }
    }
  }
}

void EingabeAnalyseUndVerarbeitung::newAnalogSA(String name, String text)
{

  for (byte i = 0; i < 6; i++)
  {
    if (scanFor(String("a") + String(i)))
    {

      //Gibts einen sensor mit demselben pin? Weg!
      for (byte j = 0; j < 10; j++)
      {
        String s = DataManager::read(SAFiles[j]);
        String s2 = s.substring(0, s.indexOf(" "));
        if (String("a") + String(i) == s2)
        {
          DataManager::clearFile(SAFiles[j]);
        }
      }
      //Freien Platz suchen
      for (byte j = 0; j < 10; j++)
      {
        if (DataManager::isEmpty(SAFiles[j]) == true)
        {
          DataManager::write(SAFiles[j], String("a") + String(i) + " " + name);
          Antwort = String(text) + " auf Pin " + "A" + String(i) + F(" gesetzt.");
          return;
        }
      }
    }
  }
}
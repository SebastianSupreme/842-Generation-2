#include "Rechnen.h"

String Rechnen::Berechnen(String StringEingabe, String mathAns)
{

  if ((StringEingabe.startsWith("sqrt") || StringEingabe.startsWith("sin") || StringEingabe.startsWith("cos") || StringEingabe.startsWith("tan")) && (!(scanFor("+") || scanFor("-") || scanFor("*") || scanFor("/") || scanFor("^"))))
  {

    int firstSpace = StringEingabe.indexOf(" ");
    String Teil1 = StringEingabe.substring(0, firstSpace);
    String secondString = StringEingabe.substring(firstSpace + 1, StringEingabe.length());

    rechenOperator = Teil1;

    if (secondString == "ans")
    {
      zahl1 = mathAns.toDouble();
    }
    else if (secondString == "pi")
    {
      zahl1 = PI;
    }
    else
    {
      zahl1 = secondString.toDouble();
    }

    // Logarithmus
  }
  else if (StringEingabe.startsWith("log"))
  {

    int firstSpace = StringEingabe.indexOf(" ");
    String Teil1 = StringEingabe.substring(0, firstSpace);
    String secondString = StringEingabe.substring(firstSpace + 1, StringEingabe.length());
    String Teil2 = secondString.substring(0, secondString.indexOf(" "));
    String Teil3 = secondString.substring(secondString.indexOf(" ") + 1, secondString.length());

    rechenOperator = Teil1;

    if (Teil2 == "ans")
    {
      zahl1 = mathAns.toDouble();
    }
    else if (Teil2 == "pi")
    {
      zahl1 = PI;
    }
    else
    {
      zahl1 = Teil2.toDouble();
    }
    if (Teil3 == "ans")
    {
      zahl2 = mathAns.toDouble();
    }
    else if (Teil3 == "pi")
    {
      zahl2 = PI;
    }
    else
    {
      zahl2 = Teil3.toDouble();
    }

    // Einfach nur ans?
  }
  else if (StringEingabe == "ans")
  {
    ergebnis = mathAns.toDouble();

    // Einfach nur PI?
  }
  else if (StringEingabe == "pi")
  {
    ergebnis = PI;
  }
  else
  {
    // Gewöhnliche Operatoren

    int firstSpace = StringEingabe.indexOf(" ");
    String Teil1 = StringEingabe.substring(0, firstSpace);
    String secondString = StringEingabe.substring(firstSpace + 1, StringEingabe.length());
    String Teil2 = secondString.substring(0, secondString.indexOf(" "));
    String Teil3 = secondString.substring(secondString.indexOf(" ") + 1, secondString.length());

    rechenOperator = Teil2;

    // Erste Zahl
    // Potenz?
    if (Teil1.indexOf("^") >= 0)
    {
      int davor = Teil1.indexOf("^");
      String ersteZahl = Teil1.substring(0, davor);
      String zweiteZahl = Teil1.substring(davor + 1, Teil1.length());
      double zwischenErgebnis = pow(ersteZahl.toDouble(), zweiteZahl.toDouble());
      zahl1 = zwischenErgebnis;
      // Wurzel?
    }
    else if (Teil1.indexOf("sqrt") >= 0)
    {
      int i = Teil1.indexOf("t");
      String zahl = Teil1.substring(i + 1, Teil1.length());
      if (zahl == "ans")
      {
        zahl1 = sqrt(mathAns.toDouble());
      }
      else if (zahl == "pi")
      {
        zahl1 = sqrt(PI);
      }
      else
      {
        zahl1 = sqrt(zahl.toDouble());
      }
    }
    else if (Teil1.indexOf("sin") >= 0)
    {
      int i = Teil1.indexOf("n");
      String zahl = Teil1.substring(i + 1, Teil1.length());
      if (zahl == "ans")
      {
        zahl1 = sin(mathAns.toDouble());
      }
      else if (zahl == "pi")
      {
        zahl1 = sin(PI);
      }
      else
      {
        zahl1 = sin(zahl.toDouble());
      }
    }
    else if (Teil1.indexOf("cos") >= 0)
    {
      int i = Teil1.indexOf("s");
      String zahl = Teil1.substring(i + 1, Teil1.length());
      if (zahl == "ans")
      {
        zahl1 = cos(mathAns.toDouble());
      }
      else if (zahl == "pi")
      {
        zahl1 = cos(PI);
      }
      else
      {
        zahl1 = cos(zahl.toDouble());
      }
    }
    else if (Teil1.indexOf("tan") >= 0)
    {
      int i = Teil1.indexOf("n");
      String zahl = Teil1.substring(i + 1, Teil1.length());
      if (zahl == "ans")
      {
        zahl1 = tan(mathAns.toDouble());
      }
      else if (zahl == "pi")
      {
        zahl1 = tan(PI);
      }
      else
      {
        zahl1 = tan(zahl.toDouble());
      }
    }
    else if (Teil1.indexOf("ans") >= 0)
    {
      zahl1 = mathAns.toDouble();
      // PI?
    }
    else if (Teil1.indexOf("pi") >= 0)
    {
      zahl1 = PI;
    }
    else
    {
      zahl1 = Teil1.toDouble();
    }

    // Zweite Zahl
    // Potenz?
    if (Teil3.indexOf("^") >= 0)
    {
      int davor = Teil3.indexOf("^");
      String ersteZahl = Teil3.substring(0, davor);
      String zweiteZahl = Teil3.substring(davor + 1, Teil3.length());
      double zwischenErgebnis = pow(ersteZahl.toDouble(), zweiteZahl.toDouble());
      zahl2 = zwischenErgebnis;

      // Wurzel?
    }
    else if (Teil3.indexOf("sqrt") >= 0)
    {
      int i = Teil3.indexOf("t");
      String zahl = Teil3.substring(i + 1, Teil3.length());
      if (zahl == "ans")
      {
        zahl2 = sqrt(mathAns.toDouble());
      }
      else if (zahl == "pi")
      {
        zahl2 = sqrt(PI);
      }
      else
      {
        zahl2 = sqrt(zahl.toDouble());
      }
    }
    else if (Teil3.indexOf("sin") >= 0)
    {
      int i = Teil3.indexOf("n");
      String zahl = Teil3.substring(i + 1, Teil3.length());
      if (zahl == "ans")
      {
        zahl2 = sin(mathAns.toDouble());
      }
      else if (zahl == "pi")
      {
        zahl2 = sin(PI);
      }
      else
      {
        zahl2 = sin(zahl.toDouble());
      }
    }
    else if (Teil3.indexOf("cos") >= 0)
    {
      int i = Teil3.indexOf("s");
      String zahl = Teil3.substring(i + 1, Teil3.length());
      if (zahl == "ans")
      {
        zahl2 = cos(mathAns.toDouble());
      }
      else if (zahl == "pi")
      {
        zahl2 = cos(PI);
      }
      else
      {
        zahl2 = cos(zahl.toDouble());
      }
    }
    else if (Teil3.indexOf("tan") >= 0)
    {
      int i = Teil3.indexOf("n");
      String zahl = Teil3.substring(i + 1, Teil3.length());
      if (zahl == "ans")
      {
        zahl2 = tan(mathAns.toDouble());
      }
      else if (zahl == "pi")
      {
        zahl2 = tan(PI);
      }
      else
      {
        zahl2 = tan(zahl.toDouble());
      }
    }
    // ans?
    else if (Teil3.indexOf("ans") >= 0)
    {
      zahl2 = mathAns.toDouble();
      // PI?
    }
    else if (Teil3.indexOf("pi") >= 0)
    {
      zahl2 = PI;
    }
    else
    {
      zahl2 = Teil3.toDouble();
    }
  }

  // Mathematische Werkzeuge
  if (rechenOperator == "+")
  {
    ergebnis = zahl1 + zahl2;
  }
  if (rechenOperator == "-")
  {
    ergebnis = zahl1 - zahl2;
  }
  if (rechenOperator == "*")
  {
    ergebnis = zahl1 * zahl2;
  }
  if (rechenOperator == "/")
  {
    ergebnis = zahl1 / zahl2;
  }
  if (rechenOperator == "^")
  {
    ergebnis = pow(zahl1, zahl2);
  }
  if (rechenOperator == "sqrt")
  {
    ergebnis = sqrt(zahl1);
  }
  if (rechenOperator == "sin")
  {
    ergebnis = sin(zahl1);
  }
  if (rechenOperator == "cos")
  {
    ergebnis = cos(zahl1);
  }
  if (rechenOperator == "tan")
  {

    ergebnis = tan(zahl1);
  }
  if (rechenOperator == "log")
  {
    ergebnis = log10(zahl2) / log10(zahl1);
  }

  return String(ergebnis);
}
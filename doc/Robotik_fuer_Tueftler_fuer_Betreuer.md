# Robotik für Tüftler - Unterlagen für Betreuer und Interessierte

Infos für Betreuer:

Schritt 1: Einrichten
- Alternativ: `boardLED.ino`, Dateiendung wird möglicherweise nicht angezeigt
- Eingerichtet am 3.6.22:
  - https://www.arduino.cc/en/software
  - Arduino IDE 2.0 RC(2.0.0-rc6)
  - Rechts davon: Windows Win 10 and newer, 64 bits
    `arduino-ide_2.0.0-rc6_Windows_64bit.exe`
  - Empfehlung: Verzeichnisname "Arduino IDE" auf "Arduino IDE 2.0 RC(2.0.0-rc6)" ändern
  - Hintergrund: Vorgeschlagene Installationsverzeichnisse:
    - "Für alle Benutzer dieses Computers (alle Benutzer)": C:\Program Files\Arduino IDE
    - "Nur für mich (andreas)": C:\Users\andreas\AppData\Local\Programs\Arduino IDE
    - Aufpassen mit bestehender Installation in "C:\Program Files (x86)\Arduino"
  - Firewall: Anfragen zu Arduino IDE, mdns-discovery.exe und xxx abgelehnt mit "Abbrechen"
  - Treiber: Arduino USB driver -> Installieren
  - Hintergrund: 
    - Aufgestartet: Hat offenbar entweder alles übernommen aus Arduino IDE 1.8.x Installation oder es ist schon alles dabei
    ... oder verwendet offenbar einfach "C:\Users\andreas\Documents\Arduino" ...
    
  - Bug "Arduino IDE 2.0 RC(2.0.0-rc6)"
    - Active Theme was obviously "Dark (Theia)" but in settings it showed "Light (Arduino)"



Schritt 2: Elemente auf Board kennenlernen
- Fehlermeldungen:
  - "error:"
  - "... could not open port 'COM...'"
- Board LED: `boardLED.ino`: Blaue LED auf ESP DEVKIT v1 board blinkt einmal pro Sekunde.
- Taster auf Board: `boardTaster.ino`: Blaue LED auf ESP DEVKIT v1 board leuchtet, wenn BOOT Taster gedrückt ist.
- Serielle Schnittstelle: `serielleSchnittstelle.ino` Text aus- und eingeben über die serielle Schnittstelle zu/vom seriellen Monitor.
  - Baudrate muss für seriellen Monitor und Plotter richtig eingestellt werden

Schritt 3: Weitere Elemente kennenlernen
- Stromkreis
- Farben der Kabel ... rot: +/Power, schwarz: -/GND
- Zusätzlicher Taster: `taster.ino`: zusätzliche LED: Sketch genau gleich, aber andere Pins.
- Servo: `servo.ino`
  - (Muss da noch etwas nachgeleaden werden? A: Ich glaube nicht.)
  - Sketch: Arduino IDE > Datei > Beispiele > Beispiele aus eigenen Bibliotheken > ESPServo > Sweep
  
Schritt 4: Zusammensetzen
- Servo mit zwei Tastern steuern und via serielle Schnittstelle Winkel anzeigen: `servoMitTasterSteuern.ino`

  
  
Ideen:
- Alle Beispiele in einem Programm
- LED Helligkeit steuern

# Erfahrungen mit dem ESP32 DEVKIT V1
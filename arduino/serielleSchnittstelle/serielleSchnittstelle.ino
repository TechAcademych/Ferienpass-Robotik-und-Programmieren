/*
Text Aus- und Eingabe über die serielle Schnittstelle zu/vom seriellen Monitor.

Seriellen Monitor öffnen via Werkzeuge > Serieller Monitor.
*/

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Hallo, bitte Tasten drücken und mit Return/Enter abschliessen...");
  String eingabe = Serial.readStringUntil('\n'); // wartet für eine Sekunde auf Eingabe, '\n' steht für new line = neue Zeile
  Serial.print("Du hast Folgendes getippt: '");
  Serial.print(eingabe);
  Serial.println("'");
}

/*
LED leuchtet, wenn Taster gedrückt ist.

Genau gleich wie boardTaster, aber andere Pins und externe Beschaltung.
*/

int pinLED = 32;
int pinTaster = 33;

void setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinTaster, INPUT_PULLUP);
}

void loop() {
  int zustandTaste = digitalRead(pinTaster); // LOW: gedrückt, HIGH: nicht gedrückt
  int zustandLED = !zustandTaste;            // zustandLED soll das Gegenteil von zustandTaste sein
  digitalWrite(pinLED, zustandLED);
}

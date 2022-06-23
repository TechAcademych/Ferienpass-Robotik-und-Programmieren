/*
Blaue LED auf ESP DEVKIT v1 board leuchtet, wenn BOOT Taster gedrückt ist.
*/
int pinLED = 2;
int pinTaster = 0;

void setup() {
  pinMode(pinLED, OUTPUT);
  pinMode(pinTaster, INPUT_PULLUP);
}

void loop() {
  int zustandTaste = digitalRead(pinTaster); // LOW: gedrückt, HIGH: nicht gedrückt
  int zustandLED = !zustandTaste;            // zustandLED soll das Gegenteil von zustandTaste sein
  digitalWrite(pinLED, zustandLED);
}

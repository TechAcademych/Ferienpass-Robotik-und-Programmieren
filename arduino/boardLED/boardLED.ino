/*
Blaue LED auf ESP DEVKIT v1 board blinkt einmal pro Sekunde.
*/
int pinLED = 2;

void setup() {
  pinMode(pinLED, OUTPUT);
}

void loop() {
  digitalWrite(pinLED, HIGH);
  delay(500);
  digitalWrite(pinLED, LOW);
  delay(500);
}

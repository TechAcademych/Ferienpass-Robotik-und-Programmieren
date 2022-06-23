/*
Solar Tracker

Version 1.4
*/

#include "taskManager.h"

String version = String("1.4");
enum {S_SOLAR_TRACKER=1, S_NINTY_DEGREE=2} zustaende;

//=========================================
// Task SolarTracker
//=========================================

#include <ESP32Servo.h>

class SolarTracker : public Task{
  protected:
  public:
    //=== Arduino sketch start

    Servo servo_1;  // create servo object to control a servo
    Servo servo_2;  // create servo object to control a servo
    
    // Pins für Fotosensoren   Pin ESP32 DEVKIT V1
    int pin_LDR_1 = A0;  // 36
    int pin_LDR_2 = A3;  // 39
    int pin_LDR_3 = A6;  // 34
    int pin_LDR_4 = A7;  // 35
    // Spannungsteiler als Referenz
    int pin_ref   = A4;  // 32
        
    // Pins für Servos
    int pin_servo_1 = 13;
    int pin_servo_2 = 12;

    int phi_x = 90;
    int phi_y = 90;
    
    int analogReadMean(int pin, int N){
      long accu=0;
      for(int i=0; i<N; i++){
        int v = analogRead(pin); // 12 bit ... 0-4095
        accu += v;
        String s = String(":") + v + " -> " + accu;
        //Serial.println(s);
      }
      return (accu / N) >> 3;
    }

    int incrementPos(int phi, int delta, int schwellwert=30, int phi_min=0, int phi_max=180){
      if(delta > schwellwert){
        phi -= 1;
        if(phi < phi_min) phi = phi_min;
      }else if(delta < -schwellwert){
        phi += 1;
        if(phi > phi_max) phi = phi_max;
      }
      return phi;
    }

    void set90deg() {
      servo_1.write(90);
      servo_2.write(90);
    }
    
    void setup() {
      pinMode(pin_LDR_1, INPUT_PULLUP);
      pinMode(pin_LDR_2, INPUT_PULLUP);
      pinMode(pin_LDR_3, INPUT_PULLUP);
      pinMode(pin_LDR_4, INPUT_PULLUP);
      
      pinMode(pin_ref, INPUT_PULLUP);

      servo_1.attach(pin_servo_1);  // attaches the servo on pin servoPin to the servo object
      servo_2.attach(pin_servo_2);  // attaches the servo on pin servoPin to the servo object
    
      phi_x = 90;
      phi_y = 90;
    }
    
    void loop() {
      long N=100; // Mittelwert über N Messwerte
    
      // Messen
      int ldr_1 = analogReadMean(pin_LDR_1,N);
      int ldr_2 = analogReadMean(pin_LDR_2,N);
      int ldr_3 = analogReadMean(pin_LDR_3,N);
      int ldr_4 = analogReadMean(pin_LDR_4,N);
      int ref   = analogReadMean(pin_ref,N);
    
      // Logik
      int delta_x = (ldr_1 + ldr_4) - (ldr_2 + ldr_3);
      int delta_y = (ldr_2 + ldr_1) - (ldr_3 + ldr_4);
    
      phi_x = incrementPos(phi_x, delta_x);
      phi_y = incrementPos(phi_y, delta_y);
          
      servo_1.write(phi_x);
      servo_2.write(phi_y);
    
      Serial.println(String("ldr_1:") + ldr_1 + ",ldr_2:" + ldr_2 + ",ldr_3:" + ldr_3 + ",ldr_4:"+ ldr_4 + ",ref:"+ ref);
    
      delay(10);
    }
    //=== Arduino sketch end
    
    SolarTracker(int id, String name) : Task(id, name) {}
    String help(){
      return String("      Solar Tracker.");
    }
} solarTracker(S_SOLAR_TRACKER,"SOLAR_TRACKER");

//=========================================
// Hilfe für den Aufbau: Servos in Position 90 Grad setzen
//=========================================

class Set90Deg : public Task{
  protected:
  public:
    //=== Arduino sketch start
    void setup() {
      solarTracker.setup();
      solarTracker.set90deg();
    }
    
    void loop() {
    }
    //=== Arduino sketch end
    
    Set90Deg(int id, String name) : Task(id, name) {}
    String help(){
      return String("      Servos auf 90 Grad setzen.");
    }
} set90Deg(S_NINTY_DEGREE,"NINTY_DEGREE");

//=========================================
// setup und loop
//=========================================

int pinTasterBoard = 0; // Taster auf dem ESP DEVKIT v1 Board
int pinLEDboard = 2;    // Blaue LED auf dem ESP DEVKIT v1 Board
TaskManager taskManager(Serial, pinTasterBoard, pinLEDboard);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("===");
  Serial.println(String()+"Solar Tracker: Version: "+version);
  taskManager.add(solarTracker);
  taskManager.add(set90Deg);
  taskManager.showAllHelp();
  
  Serial.println("===");
  taskManager.setup();
  taskManager.showHelp();
}

void loop() {
  taskManager.loop();
}

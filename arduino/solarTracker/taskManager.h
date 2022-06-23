/*
Ziel:
- Mehrere wählbare Funktionen in einem Sketch vereinen und zwischen Funktionen zur Laufzeit auswählen können.

Beschreibung:
- In einer von Task abgeleiteten Klasse werden
  - alle Elemente spezifiziert, die zu einem normalen Sketch gehören,
  - zusammen mit weiteren Elementen, die das Umschalten zwischen Funktionen unterstützen.
- Die Klasse TaskManager verwaltet die Tasks.

class Beispiel : public Task{
  protected:
  public:
    //=== Arduino sketch start
    void setup() {
    }
    
    void loop() {
    }
    //=== Arduino sketch end
    
    Beispiel(int id, String name) : Task(id, name) {}
    String help(){
      return String("      Beispiel.");
    }
} serialTest(1,"BEISPIEL");
 
*/

#include <functional> // needed for std::reference_wrapper, https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
#include <vector>     // needed for std::vector, https://en.cppreference.com/w/cpp/container/vector

class Task {
  protected:
    int    id;
    String name;
  public:
    Task(int id, String name){
      Task::name = name;
      Task::id = id;
    }
    virtual void setup() {}
    virtual void loop() {}
    virtual void teardown() {}
    virtual String help() { return String("No help"); }

    int getId() { return(id); }
    String getName() { return(name); }
};

class TaskManager {
  protected:
    std::vector<std::reference_wrapper<Task>> taskReferences; // references: Statt kopieren ... komplizierter im Handling
    int currentIndex;
    HardwareSerial *TMSerial = NULL;
    int pinTaster;
    int pinLED;
    
  public:
    TaskManager(HardwareSerial &Serial, int pinTaster, int pinLED);
    
    bool add(Task &task); // Append task to the list of tasks, first task will be run after boot
    
    void setup();    // call setup of current task
    void loop();     // change task if push button was released, then call loop of current task
    void teardown(); // call teardown of current task
    void showHelp(); // call help of current task and output returned string
    
    int getId();      // Get ID of current task
    String getName(); // Get name of current task
    
    void incrementCurrentIndex(); // change task index to the next task index 
    
    void showAllHelp(); // Show help of all registered tasks
};

//=========================================
// Implementation
//=========================================

TaskManager::TaskManager(HardwareSerial &Serial, int pinTaster, int pinLED) {
  TMSerial = &Serial;
  TaskManager::pinTaster = pinTaster;
  TaskManager::pinLED = pinLED;
  currentIndex=-1;
}

bool TaskManager::add(Task &task){
  // Check whether id is already used by another registered task
  taskReferences.push_back(task); // add task at the end of tasks
  currentIndex = 0;
  return false;
}

void TaskManager::setup(){
  TMSerial->println(String()+"setup:");
  if (currentIndex >= 0){
    Task &task = taskReferences.at(currentIndex).get();
    task.setup();
  }
  
  pinMode(pinTaster, INPUT_PULLUP);
  pinMode(pinLED, OUTPUT);
}

void TaskManager::loop(){
  if (digitalRead(pinTaster) == LOW){
    TMSerial->println();
    do{
      TMSerial->print(".");
      delay(20);
    }
    while(digitalRead(pinTaster) == LOW);
    TMSerial->println();
    
    TMSerial->println("======== Wechseln...");
    teardown();
    incrementCurrentIndex();
    setup();
    showHelp();

    TMSerial->println("Blinkcode ausgeben...");
    pinMode(pinLED, OUTPUT);
    digitalWrite(pinLED,LOW);
    //delay(500);
    unsigned int id = getId();
    for(int i=0; i < id; i++){
      digitalWrite(pinLED,HIGH);
      delay(50);
      digitalWrite(pinLED,LOW);
      delay(300);
    }
    delay(800);
    TMSerial->println("Fertig.");
  }

  //TMSerial->println(String()+"loop:");
  if (currentIndex >= 0){
    Task &task = taskReferences.at(currentIndex).get();
    task.loop();
  }
}

void TaskManager::teardown(){
  TMSerial->println(String()+"teardown:");
  if (currentIndex >= 0){
    Task &task = taskReferences.at(currentIndex).get();
    task.teardown();
  }
}

void TaskManager::showHelp() {
  TMSerial->println();
  TMSerial->println(String()+"Aktives Beispiel:");
  if (currentIndex >= 0){
    Task &task = taskReferences.at(currentIndex).get();
    TMSerial->println(String()+"  Name: "+task.getName()+"(id: "+task.getId()+")");
    TMSerial->println(String()+"  Hilfe: ");
    TMSerial->println(task.help());
  }
}

int TaskManager::getId(){
  TMSerial->println(String()+"setup:");
  if (currentIndex >= 0){
    Task &task = taskReferences.at(currentIndex).get();
    return task.getId();
  }
  return -1;
}

String TaskManager::getName(){
  TMSerial->println(String()+"setup:");
  if (currentIndex >= 0){
    Task &task = taskReferences.at(currentIndex).get();
    return task.getName();
  }
  return String();
}

void TaskManager::incrementCurrentIndex() {
  TMSerial->println(String()+"incrementCurrentIndex:");
  if (currentIndex >= 0) {
    currentIndex+=1;
    if(currentIndex >= taskReferences.size()){
      currentIndex = 0;
    }
  }
}
void TaskManager::showAllHelp(){
  TMSerial->println();
  TMSerial->println(String()+"Liste aller Beispiele:");
  for(const auto& taskReference: taskReferences) {
    Task &task = taskReference.get();
    TMSerial->println(String()+"  Name: "+task.getName()+"(id: "+task.getId()+")");
    TMSerial->println(String()+"  Hilfe: ");
    TMSerial->println(task.help());
    TMSerial->println();
  }
}

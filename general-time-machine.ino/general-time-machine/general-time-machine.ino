#include <TimerOne.h>
#define RELAY_PIN 8 

unsigned long previousMillis = 0;   
unsigned long currentMillis;

const unsigned int NEW = 0;
const unsigned int RUNNING = 1;
const unsigned int REST = 2;

const unsigned long SLEEP = 10800000; // 3 hours
const unsigned long RUN = 60000; // 1 min

unsigned int state = NEW;

void setup(void)
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  Timer1.initialize(5000000); // 5 sec
  Timer1.attachInterrupt(runInterrupt);
  Serial.begin(9600);
}

void runInterrupt(void)
{
  currentMillis = millis();
  if(state == NEW) 
  {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(RELAY_PIN, LOW);
    previousMillis = currentMillis;
    state = RUNNING;
  }

  if(state == RUNNING) 
  {
    if(currentMillis - previousMillis > RUN ) {
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(RELAY_PIN, HIGH);
      state = REST;
    }
  }

  if(state == REST) 
  {
    if(currentMillis - previousMillis > SLEEP) {
      state = NEW;
    }
  }
}

void loop(void)
{
  
}

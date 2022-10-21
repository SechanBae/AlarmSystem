//I Sechan Bae, 000803348 certify that this material is my original work. No other person's work has been used without due acknowledgement. I have not made my work available to anyone else."

#include <Arduino.h> 

#define PIN_PIR D5 
#define PIN_BUTTON D6 
#define ALARM_DISABLED  0 
#define ALARM_ENABLE    1 
#define ALARM_COUNTDOWN 2 
#define ALARM_ACTIVE    3 
#define MAXNUMBER_OF_BLINKS 40
#define BLINK_ON_DELAY 200
#define BLINK_OFF_DELAY 50
#define INPUT_DELAY 200
int iAlarmState=1;
int numberOfBlinks=0;
bool expired=false;
bool detected=false; 
bool buttonState=false;


void collectInputs(){
  bool motion;
  motion=digitalRead(PIN_PIR);
  if(motion==true&&iAlarmState==ALARM_ENABLE){
    iAlarmState=ALARM_COUNTDOWN;
  }
  if(digitalRead(PIN_BUTTON)==0){
    if(iAlarmState==ALARM_COUNTDOWN){
      iAlarmState=ALARM_DISABLED;
      numberOfBlinks=0;
    }
    else if(iAlarmState==ALARM_DISABLED){
      iAlarmState=ALARM_ENABLE;
    }
  }
  delay(INPUT_DELAY);
}
void checkAlarmState(){
  switch (iAlarmState)
  {
  case ALARM_DISABLED:
    digitalWrite(LED_BUILTIN,true);
    break;
  
  case ALARM_ENABLE:
    digitalWrite(LED_BUILTIN,true);
    break;
  case ALARM_COUNTDOWN:
    digitalWrite(LED_BUILTIN, false);
    delay(BLINK_ON_DELAY);
    digitalWrite(LED_BUILTIN,true);
    delay(BLINK_OFF_DELAY);
    numberOfBlinks++;
    if(numberOfBlinks==MAXNUMBER_OF_BLINKS){
      iAlarmState=ALARM_ACTIVE;
    }
    break;
  case ALARM_ACTIVE:
    digitalWrite(LED_BUILTIN, false);
    break;
  }
}
void setup() { 
  Serial.begin(115200); 
 
  pinMode(LED_BUILTIN, OUTPUT); 
 
  pinMode(PIN_PIR, INPUT); 
 
  pinMode(PIN_BUTTON, INPUT_PULLUP); 
} 
 
void loop() { 
  collectInputs();
  checkAlarmState();
} 
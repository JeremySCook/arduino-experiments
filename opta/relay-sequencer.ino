//by @jeremyscook 6/19/2024
//could go through different modes/BPM via onboard button???
//hits onboard solenoids to act as a high hat, use SSRs to actuate solenoids
//current version compiles, but not physically tested

#include "OptaBlue.h"

using namespace Opta; //not sure what this is for, but in examples

DigitalStSolidExpansion stsolidExp;

int timeOnDelay = 50; //how long device are active before retract (ms)
int BPM = 120;
int beatDelay = 60000/BPM; //delay between beats in ms
//int beatDelay = 500;
bool sequence0[] = {1,0,1,0,1,0,1,0}; //kick - hit drum with solenoid
bool sequence1[] = {1,1,1,1,1,1,1,0}; //hat - hit tumbler with solenoid - USE RELAYS INSTEAD?
bool sequence2[] = {0,0,1,0,0,0,1,0}; //snare - physical relay fires for snare sound (maybe multiple relays)

void setup() {
  OptaController.begin();
  stsolidExp = OptaController.getExpansion(0); //expansion at index 0 is solid state relay
  pinMode(LED_RELAY1, OUTPUT);
  pinMode(LED_RELAY2, OUTPUT);
  pinMode(LED_RELAY3, OUTPUT);
  pinMode(LED_RELAY4, OUTPUT); //likely not necessary to assign, but doesn't hurt
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);

}

void loop() {
  for(int i = 0; i<8; i++){
    if (sequence0[i] == 1){ //kick drum - solenoid
      //do something - maybe try lights first??
      digitalWrite(LED_RELAY1, HIGH);
      stsolidExp.digitalWrite(0, HIGH);
    }
    if (sequence1[i] == 1){
      digitalWrite(LED_RELAY2, HIGH);
      digitalWrite(RELAY1, HIGH);
      digitalWrite(RELAY2, HIGH);
      digitalWrite(RELAY3, HIGH);
      digitalWrite(RELAY4, HIGH);
    }
    if (sequence2[i] == 1){ //snare - solenoid - maybe hit tumbler?
      digitalWrite(LED_RELAY3, HIGH);
      stsolidExp.digitalWrite(1, HIGH);
    }
    delay(timeOnDelay);
    //turn off outputs
    digitalWrite(LED_RELAY1, LOW);
    digitalWrite(RELAY1, LOW);
    digitalWrite(LED_RELAY2, LOW);
    digitalWrite(LED_RELAY3, LOW);
    digitalWrite(LED_RELAY4, LOW);    
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);
    digitalWrite(RELAY3, LOW);
    digitalWrite(RELAY4, LOW);
    stsolidExp.digitalWrite(0, LOW);
    stsolidExp.digitalWrite(1, LOW);
    delay(beatDelay - timeOnDelay); //time between beats hitting
    //restart the cycle for 8 beats
  }

}

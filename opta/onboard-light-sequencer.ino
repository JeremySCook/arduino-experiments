//could go through different modes/BPM via onboard button???

#include "OptaBlue.h"

int timeOnDelay = 50; //how long device are active before retract (ms)
int BPM = 120;
//int beatDelay = (60/BPM * 1000); //delay between beats in ms
int beatDelay = 500;
bool sequence0[] = {1,1,1,1,1,1,1,1}; //cymbals - every beat - SSR1 activates solenoid to hit tumbler
bool sequence1[] = {0,1,0,1,0,1,0,1}; //bass - every other beat - SSR2 activates solenoid to hit drum
bool sequence2[] = {0,0,0,1,0,0,0,1}; //snare - physical relay fires for snare sound (maybe multiple relays)

void setup() {
  pinMode(LED_RELAY1, OUTPUT);
  pinMode(LED_RELAY2, OUTPUT);
  pinMode(LED_RELAY3, OUTPUT);
  pinMode(LED_RELAY4, OUTPUT); //likely not necessary to assign, but doesn't hurt

}

void loop() {
  for(int i = 0; i<8; i++){
    if (sequence0[i] == 1){
      //do something - maybe try lights first??
      digitalWrite(LED_RELAY1, HIGH);
    }
    if (sequence1[i] == 1){
      digitalWrite(LED_RELAY2, HIGH);
    }
    if (sequence2[i] == 1){
      digitalWrite(LED_RELAY3, HIGH);
    }
    delay(timeOnDelay);
    //turn off outputs
    digitalWrite(LED_RELAY1, LOW);
    digitalWrite(LED_RELAY2, LOW);
    digitalWrite(LED_RELAY3, LOW);
    digitalWrite(LED_RELAY4, LOW);    

    delay(beatDelay - timeOnDelay); //time between beats hitting
    //restart the cycle for 8 beats
  }

}

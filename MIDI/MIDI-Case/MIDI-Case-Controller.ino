#include <MIDI.h>

#define button1 2 //upper-right button
#define button2 3
#define button3 4
#define button4 5
#define button5 6 //lower-left button
#define button6 7
#define button7 8
#define button8 9
#define auxLeftButton 10
#define auxLeftLight 11 //not used, wired to 5V, but could be in the future
#define auxRightButton 12
#define auxRightLight 13 //same as LED_BUILTIN

#define NOTEDELAY 5 //delay

int noteSequence[] = {button5, button6, button7, button8, button4, button3, button2, button1};
//above notes arranged from lower left to right, upper left to right
bool noteInputStatus[] = {0,0,0,0,0,0,0,0};
bool noteStatus[] = {0,0,0,0,0,0,0,0};
int noteValue[] = {60, 62, 64, 65, 67, 69, 71, 72}; //C3, D3, E3, F3, G3, A3, B3, C4

bool auxRightButtonStatus = 1; //pullup, so pushed is 0, not pushed is 1
bool beatOn = 0;
unsigned long beatTime;
int beatHold = 500; //how long in ms until beat is turned off
unsigned long previousMillis = 0;

bool bendStatus = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  pinMode(button7, INPUT_PULLUP);
  pinMode(button8, INPUT_PULLUP);
  pinMode(auxLeftButton, INPUT_PULLUP);
  pinMode(auxLeftLight, OUTPUT);
  pinMode(auxRightButton, INPUT_PULLUP);
  pinMode(auxRightLight, OUTPUT);

  //Serial.begin(9600);
  MIDI.begin(1); //Launch MIDI on channel 1
}

void loop() {
pitchBend();
autoBeat();

for (int i = 0; i <8; i++) {
  if (digitalRead(noteSequence[i]) == 0){ //0 when depressed
    noteInputStatus[i] = 1;
  }
  else{
    noteInputStatus[i] = 0;
  }
}

for (int i = 0; i <8; i++) {
    if (noteInputStatus[i] == 1 && noteStatus[i] == 0) {
    MIDI.sendNoteOn(noteValue[i], 127, 1);
    //Serial.print("Note Sent: "); Serial.println(noteValue[i]);
    noteStatus[i] = 1;
    digitalWrite(auxRightLight, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(auxRightLight, LOW);
    delay(NOTEDELAY);
  }
}

for (int i = 0; i <8; i++) {
    if (noteInputStatus[i] == 0 && noteStatus[i] == 1) {
    MIDI.sendNoteOff(noteValue[i], 127, 1);
    //Serial.print("Note Off: "); Serial.println(noteValue[i]);
    noteStatus[i] = 0;
    digitalWrite(auxRightLight, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(auxRightLight, LOW);
    delay(NOTEDELAY);
 }
}
}

void pitchBend(){
  if(digitalRead(auxLeftButton) == 0 && bendStatus == 0){ //button depressed not bent
    MIDI.sendPitchBend(4500, 1);
    //Serial.println("Pitch Bend On");
    bendStatus = 1;
    digitalWrite(auxRightLight, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(auxRightLight, LOW);
    delay(NOTEDELAY);
  }
  else if(digitalRead(auxLeftButton) == 1 && bendStatus == 1){ //button released and bent
    MIDI.sendPitchBend(0, 1);
    //Serial.println("Pitch Bend Off");
    bendStatus = 0;
    digitalWrite(auxRightLight, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(auxRightLight, LOW);
    delay(NOTEDELAY);
  }
}

void autoBeat(){ //This routine still needs some work - goes on, but never goes off
  auxRightButtonStatus = digitalRead(auxRightButton);
    if(auxRightButtonStatus == 0 && beatOn == 0){
      beatOn = 1;
      delay(200); //debounce delay - could use a better technique?
    }
    else if(auxRightButtonStatus == 0 && beatOn == 1) {
      beatOn = 0;
      delay(200); //debounce delay - use a better technique?
      //Serial.println("Auto Beat Off");
    }
    if(beatOn == 1){
        if((millis() - previousMillis) > 500){
          MIDI.sendNoteOn(60, 127, 1);   
          digitalWrite(auxRightLight, HIGH);
          delay(NOTEDELAY);
          digitalWrite(auxRightLight, LOW);
          previousMillis = millis(); 
        }
    }
}

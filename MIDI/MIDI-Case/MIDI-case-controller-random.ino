//Includes a random note function - compiles but untested.
//Still need to add steps in button sequence to allow it to
//execute @JeremySCook Nov 6, 2024

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

#define NOTEDELAY 3 //debounce delay

int noteSequence[] = {button5, button6, button7, button8, button4, button3, button2, button1};
//above notes arranged from lower left to right, upper left to right
bool noteInputStatus[] = {0,0,0,0,0,0,0,0};
bool noteStatus[] = {0,0,0,0,0,0,0,0};
int noteValue[] = {60, 62, 64, 65, 67, 69, 71, 72}; //C3, D3, E3, F3, G3, A3, B3, C4

//autoBeat variables/constants
bool beatOn = 0;
bool randomNotesOn = 0; //turns output notes on at random
#define RANDOMNOTESTIME 2000 //time between random notes
bool noteOff = 0;
#define BEATHOLD 60 //how long to hold each auto beat
#define BEATTIME 1000 //how long between individual beats?
unsigned long previousMillis = 0;
unsigned long previousMillis1 = 0;
#define AUXDEBOUNCE 500
int buttonState = 0;
int beatStep = 0;
bool bendStatus = 0;
#define SEQUENCEDELAY 20

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

for (int i = 0; i <8; i++) {
  if (digitalRead(noteSequence[i]) == 0){ //0 when depressed
    noteInputStatus[i] = 1;
  }
  else{
    noteInputStatus[i] = 0;
  }
}
pitchBend();
buttonSequence();
autoBeatKit();
randomNotes();
MIDINoteOn();
MIDINoteOff();
}

void MIDINoteOn(){
for (int i = 0; i <8; i++) {
    if (noteInputStatus[i] == 1 && noteStatus[i] == 0) {
    MIDI.sendNoteOn(noteValue[i], 127, 1);
    //Serial.print("Note Sent: "); Serial.println(noteValue[i]);
    noteStatus[i] = 1;
    digitalWrite(auxRightLight, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(auxRightLight, LOW);
  }
}
}

void MIDINoteOff(){
for (int i = 0; i <8; i++) {
    if (noteInputStatus[i] == 0 && noteStatus[i] == 1) {
    MIDI.sendNoteOff(noteValue[i], 127, 1);
    //Serial.print("Note Off: "); Serial.println(noteValue[i]);
    noteStatus[i] = 0;
    digitalWrite(auxRightLight, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(auxRightLight, LOW);
    //delay(NOTEDELAY); --removed to improve speed
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
    //delay(NOTEDELAY); --removed to improve speed
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

void autoBeatKit(){
  bool sequence0[] = {1,0,1,0,1,0,1,0}; //kick - hit drum with solenoid
  bool sequence1[] = {1,1,1,1,1,1,1,1}; //hat - hit tumbler with solenoid - USE RELAYS INSTEAD?
  bool sequence2[] = {0,0,1,0,0,0,1,0}; //snare - physical relay fires for snare sound (maybe multiple relays)

  if((beatOn == 1) && ((millis() - previousMillis) > BEATTIME)){
      //MIDI.sendNoteOn(48, 63, 1);
    if (sequence0[beatStep] == 1) noteInputStatus[0] = 1;
    if (sequence1[beatStep] == 1) noteInputStatus[1] = 1;
    if (sequence2[beatStep] == 1) noteInputStatus[2] = 1;
    MIDINoteOn();
    beatStep += 1;
    if (beatStep == 8) beatStep = 0; //back to 0 once beatStep exceeds 7
    previousMillis = millis();
    delay(BEATHOLD);
    MIDINoteOff(); //not sure this actually does anything, as it's called anyway in main program
    }
}

void randomNotes(){
  if((randomNotesOn == 1) && ((millis() - previousMillis) > RANDOMNOTESTIME)){
    int randomNoteNumber = random(8); //produces a random value between 0 and 7
    noteInputStatus[randomNoteNumber] = 1; //turns note corresponding to random note status to 1
    MIDINoteOn();
    previousMillis = millis();
    //MIDI.sendNoteOn(48, 63, 1); //signal
    delay(BEATHOLD);
    digitalWrite(auxRightLight, HIGH);
    delay(NOTEDELAY);
    digitalWrite(auxRightLight, LOW);
    MIDINoteOff(); //not sure this actually does anything, as it's called anyway in main program
  }
}

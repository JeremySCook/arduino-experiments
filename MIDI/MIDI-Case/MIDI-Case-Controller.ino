#include <MIDI.h>

#define button1 2 //upper-right button
#define button2 3
#define button3 4
#define button4 5
#define button5 6 //lower-left button
#define button6 7
#define button7 8
#define button8 9
#define auxButton 10

#define NOTEDELAY 5 //delay

int noteSequence[] = {button5, button6, button7, button8, button4, button3, button2, button1};
//above notes arranged from lower left to right, upper left to right
bool noteInputStatus[] = {0,0,0,0,0,0,0,0};
bool noteStatus[] = {0,0,0,0,0,0,0,0};
int noteValue[] = {60, 62, 64, 65, 67, 69, 71, 72}; //C3, D3, E3, F3, G3, A3, B3, C4
bool beatOn = 0;
unsigned long beatTime;
int beatHold = 50; //how long in ms until beat is turned off

bool bendStatus = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  pinMode(button7, INPUT_PULLUP);
  pinMode(button8, INPUT_PULLUP);
  pinMode(auxButton, INPUT_PULLUP);

  MIDI.begin(1); //Launch MIDI on channel 1
}

void loop() {
pitchBend();
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
    noteStatus[i] = 1;
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(LED_BUILTIN, LOW);
    delay(NOTEDELAY);
  }
}

for (int i = 0; i <8; i++) {
    if (noteInputStatus[i] == 0 && noteStatus[i] == 1) {
    MIDI.sendNoteOff(noteValue[i], 127, 1);
    noteStatus[i] = 0;
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(LED_BUILTIN, LOW);
    delay(NOTEDELAY);
 }
}
}

void pitchBend(){
  if(digitalRead(auxButton) == 0 && bendStatus == 0){ //button depressed not bent
    MIDI.sendPitchBend(4500, 1);
    bendStatus = 1;
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(LED_BUILTIN, LOW);
    delay(NOTEDELAY);
  }
  else if(digitalRead(auxButton) == 1 && bendStatus == 1){ //button released and bent
    MIDI.sendPitchBend(0, 1);
    bendStatus = 0;
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(NOTEDELAY);
    digitalWrite(LED_BUILTIN, LOW);
    delay(NOTEDELAY);
  }
}

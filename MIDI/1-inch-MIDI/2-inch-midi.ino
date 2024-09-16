/*
Works! Jul 10th, 2024 @JeremySCook
Use ATtiny85 @ 8 MHz Internal clock
New code w/ potentiometer working, 9/3/2024 @JeremySCook
*/

#include <MIDI.h>
#include <SoftwareSerial.h>
#include <tinysnore.h>

#define MIDIOut 0
#define MIDIIn 5 // Reset pin acts as dummy since not needed - tried 99, didn't function correctly
#define LEDOut 1
#define SIG1 1 // ADC Pin 1, corresponds to PB2
#define SIG2 3
#define POTPIN 2
#define NOTEDELAY 5 //delay between LED on/off after sending signal
#define POLLDELAY 30 //snore to save power before registering inputs
#define debounceDelayValue 40 //time in miliseconds to position fingers
#define pitchBendIntensity 3000 //intensity of pitch bends -8192 to 8192 is range of bend
#define pitchBendSteps 8000

bool noteInputStatus[] = {0,0,0,0,0,0};
bool noteStatus[] = {0,0,0,0,0,0};
int noteValue[] = {57, 62, 60, 52, 55, 53}; // 
bool beatOn = 0;
unsigned long beatTime;
int beatHold = 50; //how long in ms until beat is turned off
int pitchBendValue = 0; //start value for pitch bends
int pitchBendValueNew = 0; //new pitch bend value
int pitchBendZeroValue;
bool pitchUpActive = 0;
bool pitchDownActive = 0;

//int beatTime = 0;//also need a millis time that can be used between loops? beatTime

// Define the SoftwareSerial port
SoftwareSerial mySerial(MIDIIn, MIDIOut); // RX, TX
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(LEDOut, OUTPUT);
    //pinMode(POTPIN, INPUT_PULLUP);
    //pitchBendZeroValue = map(analogRead(POTPIN), 0, 1023, -pitchBendSteps, pitchBendSteps);
}

void loop() {

//beat();
//bend(); //pitch bend
bendAbsolute();
debounceDelay(); //time to settle on button(s) pushed

    int SIG1Value = analogRead(SIG1);
    noteInputStatus[0] = 0; noteInputStatus[1] = 0; noteInputStatus[2] = 0; //turns button status off by default
    if (SIG1Value > 832) {noteInputStatus[2] = 1;}
    else if (SIG1Value > 751) {noteInputStatus[1] = 1;}
    else if (SIG1Value > 500) {noteInputStatus[0] = 1;} //both SIG1 buttons pushed (I think)
    
    int SIG2Value = analogRead(SIG2);
    noteInputStatus[3] = 0; noteInputStatus[4] = 0; noteInputStatus[5] = 0; //turns button status off by default    
    if (SIG2Value > 832) {noteInputStatus[5] = 1;}
    else if (SIG2Value > 751) {noteInputStatus[4] = 1;}
    else if (SIG2Value > 500) {noteInputStatus[3] = 1;} //both SIG1 buttons pushed (I think)

for (int i = 0; i < 6; i++) {
  if (noteInputStatus[i] == 1 && noteStatus[i] == 0) {
    //midi2.sendPitchBend(0, 1); //resets the pitch bend
    midi2.sendNoteOn(noteValue[i], 127, 1);
    noteStatus[i] = 1;
    pitchUpActive = 0; //not sure if these pitch ups are needed, but doesn't work without the other set
    pitchDownActive = 0;
    digitalWrite(LEDOut, HIGH); 
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
    snore(NOTEDELAY); //delay after to potentially regain energy???
  }
  else if (noteInputStatus[i] == 0 && noteStatus[i] == 1) {
    midi2.sendNoteOff(noteValue[i], 0, 1);
    noteStatus[i] = 0;
    pitchUpActive = 0;
    pitchDownActive = 0;
    digitalWrite(LEDOut, HIGH);
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
    snore(NOTEDELAY); //delay after to potentially regain energy???
  }
  }
  snore(POLLDELAY); //polls every XXms, sleeps otherwise
}



void debounceDelay(){
  for (int i = 0; i < 6; i++){
  noteInputStatus[i] = 0; //set values to zero by default
  }
  int SIG1Value = analogRead(SIG1);
  int SIG2Value = analogRead(SIG2);
  if(SIG1Value > 50 || SIG2Value > 50){
    snore(debounceDelayValue);
  }
}

//scale bpm from 80 to 160 ==> a delay of 60/80 to 60/160 seconds ==> .75 seconds - .375 seconds
//may be better to scale this directly: 50 off, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160 ==> 12 steps
//use map function to scale between 5 and 12 in order to create set steps - do not execute at 5, multiply
//by 10 otherwise

void beat(){ //not currently used
  int PotMap = map(analogRead(POTPIN), 0, 1023, 1000, 100);
  //int BPM[] = {120, 90, 60, 0}; //

  if (PotMap > 200){ //take out low values to turn off
    int beatDelay = (80000/PotMap); //
    if ((millis() - beatTime) >= beatDelay && beatOn == 0){
    midi2.sendNoteOn(40, 90, 1); // electric snare per general MIDI drum map, could use different instrument (last value)?
    beatTime = millis();
    beatOn = 1;
    digitalWrite(LEDOut, HIGH); 
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
    snore(NOTEDELAY); //delay after to potentially regain energy???
  }
  if ((millis() - beatTime) >= beatHold && beatOn == 1){
    midi2.sendNoteOff(40, 90, 1); // electric snare per general MIDI drum map, could use different instrument (last value)?
    beatOn = 0;
    digitalWrite(LEDOut, HIGH); 
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
    snore(NOTEDELAY); //delay after to potentially regain energy???
  }
  }
}

void bend(){ //not currently used
  pitchBendValueNew = map(analogRead(POTPIN), 0, 1023, -25, 25);
  if ((pitchBendValueNew > (pitchBendValue + 1)) && (pitchDownActive == 0)){
    midi2.sendPitchBend(-pitchBendIntensity, 1);
    pitchBendValue = pitchBendValueNew;
    pitchDownActive = 1;
    pitchUpActive = 0;
    digitalWrite(LEDOut, HIGH); 
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
    snore(NOTEDELAY);
  }
  else if ((pitchBendValueNew < (pitchBendValue - 1)) && (pitchUpActive == 0)){
    midi2.sendPitchBend(pitchBendIntensity, 1);
    pitchBendValue = pitchBendValueNew;
    pitchDownActive = 0;
    pitchUpActive = 1;   
    digitalWrite(LEDOut, HIGH); 
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
    snore(NOTEDELAY);
  }
}

void bendAbsolute(){
  pitchBendValueNew = map(analogRead(POTPIN), 0, 1023, pitchBendSteps, -pitchBendSteps);
  if ((pitchBendValueNew > -800) && (pitchBendValueNew < 800)){
    pitchBendValueNew = 0; //set a dead zone
  }
  if ((pitchBendValueNew > (pitchBendValue + 100)) || (pitchBendValueNew < (pitchBendValue - 100)))  {
    midi2.sendPitchBend(pitchBendValueNew, 1);
    pitchBendValue = pitchBendValueNew;
    digitalWrite(LEDOut, HIGH); 
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
    snore(NOTEDELAY); //delay after to potentially regain energy???
  }
}

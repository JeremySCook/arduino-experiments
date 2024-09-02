/*
Works! Jul 10th, 2024 @JeremySCook
Use ATtiny85 @ 8 MHz Internal clock
New code w/ potentiometer beat trigger compiles, but untested Aug 20th, 2024 @JeremySCook
*/

#include <MIDI.h>
#include <SoftwareSerial.h>
#include <tinysnore.h>

#define MIDIOut 0
#define MIDIIn 5 // Reset pin acts as dummy since not needed - tried 99, didn't function correctly
#define LEDOut 1
#define SIG1 1 // ADC Pin 1, corresponds to PB2
#define SIG2 3
#define POTPIN 4
#define NOTEDELAY 5
#define POLLDELAY 20 //snore to save power before registering inputs

bool noteInputStatus[] = {0,0,0,0};
bool noteStatus[] = {0,0,0,0};
int noteValue[] = {60, 62, 67, 69}; // C3, D3, G3, A3 (notes for CAGE)
//bool beatSelect = 0;
unsigned long beatTime;
//int beatDelay = 500; //time between beats
//int beatTime = 0;//also need a millis time that can be used between loops? beatTime

// Define the SoftwareSerial port
SoftwareSerial mySerial(MIDIIn, MIDIOut); // RX, TX
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(LEDOut, OUTPUT);
    //pinMode(POTPIN, INPUT_PULLUP);
}

void loop() {

beat();
    // Send a MIDI Note On message (Note, Velocity, Channel)
    int SIG1Value = analogRead(SIG1);
    noteInputStatus[0] = 0; noteInputStatus[1] = 0; //turns button status off by default
    if (SIG1Value > 832) {noteInputStatus[0] = 1; noteInputStatus[1] = 1;}
    else if (SIG1Value > 751) {noteInputStatus[1] = 1;}
    else if (SIG1Value > 500) {noteInputStatus[0] = 1;}
    
    int SIG2Value = analogRead(SIG2);
    noteInputStatus[2] = 0; noteInputStatus[3] = 0; //turns button status off by default    
    if (SIG2Value > 832) {noteInputStatus[2] = 1; noteInputStatus[3] = 1;}
    else if (SIG2Value > 751) {noteInputStatus[3] = 1;}
    else if (SIG2Value > 500) {noteInputStatus[2] = 1;}

for (int i = 0; i < 4; i++) {
  if (noteInputStatus[i] == 1 && noteStatus[i] == 0) {
    midi2.sendNoteOn(noteValue[i], 127, 1);
    noteStatus[i] = 1;
    digitalWrite(LEDOut, HIGH); 
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
  }
  else if (noteInputStatus[i] == 0 && noteStatus[i] == 1) {
    midi2.sendNoteOff(noteValue[i], 0, 1);
    noteStatus[i] = 0;
    digitalWrite(LEDOut, HIGH);
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
  }
  }
  snore(POLLDELAY); //polls every 50ms, sleeps otherwise
}

//scale bpm from 80 to 160 ==> a delay of 60/80 to 60/160 seconds ==> .75 seconds - .375 seconds
//may be better to scale this directly: 50 off, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160 ==> 12 steps
//use map function to scale between 5 and 12 in order to create set steps - do not execute at 5, multiply
//by 10 otherwise

void beat(){
  int PotMap = map(analogRead(POTPIN), 0, 1023, 5, 12);
  int BPMMap = PotMap*10; // scales mapped value up to a BPM value
  int beatDelay = (60*1000/BPMMap); // gives a value in milliseconds between each beat
  
  if (BPMMap > 50){ //take out low values to turn off
    if (millis() - beatTime >= beatDelay){
    midi2.sendNoteOn(40, 127, 1); // electric snare per general MIDI drum map, could use different instrument (last value)?
    beatTime = millis();
    digitalWrite(LEDOut, HIGH); 
    snore(NOTEDELAY);
    digitalWrite(LEDOut, LOW);
  }
  }

}

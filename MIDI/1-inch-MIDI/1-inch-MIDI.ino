/*
Works! Jul 10th, 2024 @JeremySCook
New code w/ aux beat trigger compiles, but untested Aug 12th, 2024 @JeremySCook
*/

#include <MIDI.h>
#include <SoftwareSerial.h>
#include <tinysnore.h>

#define MIDIOut 0
#define MIDIIn 5 // Reset pin acts as dummy since not needed - tried 99, didn't function correctly
#define LEDOut 1
#define SIG1 1 // ADC Pin 1, corresponds to PB2
#define SIG2 3
#define AUX 4

bool noteInputStatus[] = {0,0,0,0};
bool noteStatus[] = {0,0,0,0};
int noteValue[] = {60, 61, 62, 63}; // keys corresponding to each note
bool beatSelect = 0;
unsigned long beatTime;
int beatDelay = 500; //time between beats
//int beatTime = 0;//also need a millis time that can be used between loops? beatTime

// Define the SoftwareSerial port
SoftwareSerial mySerial(MIDIIn, MIDIOut); // RX, TX
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(LEDOut, OUTPUT);
    pinMode(AUX, INPUT_PULLUP);
}

void loop() {
    // Select if constant beat is on
    if (beatSelect == 0){beat();}
    bool AUXIn = digitalRead(AUX);
    if (AUXIn == 1 && beatSelect == 0) {
      beatSelect = 1;
      //add in millis() time here?? don't think so
      snore(500); //debounce 1/2 second
    }
    else if (AUXIn == 1 && beatSelect == 1) {
      beatSelect = 0;
      snore(500); //debounce 1/2 second
    }
    
    // Send a MIDI Note On message (Note, Velocity, Channel)
    int SIG1Value = analogRead(SIG1);
    noteInputStatus[0] = 0; noteInputStatus[1] = 0; //turns button status off by default
    if (SIG1Value > 800) {noteInputStatus[0] = 1; noteInputStatus[1] = 1;}
    else if (SIG1Value > 700) {noteInputStatus[1] = 1;}
    else if (SIG1Value > 100) {noteInputStatus[0] = 1;}
    
    int SIG2Value = analogRead(SIG2);
    noteInputStatus[2] = 0; noteInputStatus[3] = 0; //turns button status off by default    
    if (SIG2Value > 800) {noteInputStatus[2] = 1; noteInputStatus[3] = 1;}
    else if (SIG2Value > 700) {noteInputStatus[3] = 1;}
    else if (SIG2Value > 100) {noteInputStatus[2] = 1;}

for (int i = 0; i < 4; i++) {
  if (noteInputStatus[i] == 1 && noteStatus[i] == 0) {
    midi2.sendNoteOn(noteValue[i], 127, 1);
    noteStatus[i] = 1;
    digitalWrite(LEDOut, HIGH); 
    snore(5);
    digitalWrite(LEDOut, LOW);
  }
  else if (noteInputStatus[i] == 0 && noteStatus[i] == 1) {
    midi2.sendNoteOff(noteValue[i], 0, 1);
    noteStatus[i] = 0;
    digitalWrite(LEDOut, HIGH);
    snore(5);
    digitalWrite(LEDOut, LOW);
  }
  }
  snore(50); //polls every 50ms, sleeps otherwise
}

void beat(){
  if (millis() - beatTime >= beatDelay){
    midi2.sendNoteOn(60, 127, 1);
    beatTime = millis();
    digitalWrite(LEDOut, HIGH); 
    snore(5);
    digitalWrite(LEDOut, LOW);
  }


}

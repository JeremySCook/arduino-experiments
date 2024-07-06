//WIP 7/6/2024 @JeremySCook

#include <MIDI.h>
#include <SoftwareSerial.h>

#define MIDIOut 0
#define MIDIIn 5 // Reset pin acts as dummy since not needed?
#define LEDOut 1
#define SIG1 2
#define SIG2 3
#define Aux 4

bool noteInputStatus[] = {0,0,0,0};
bool noteStatus[] = {0,0,0,0};
int noteValue[] = {60, 61, 62, 63}; // keys corresponding to each note

// Define the SoftwareSerial port
SoftwareSerial mySerial(MIDIIn, MIDIOut); // RX, TX
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(LEDOut, OUTPUT);
}

void loop() {
    // Send a MIDI Note On message (Note, Velocity, Channel)
    
    int SIG1Value = analogRead(SIG1);
    if (SIG1Value > 800) {noteInputStatus[1] == 1;}
    else if (SIG1Value > 500) {noteInputStatus[0] == 1;}
    else {noteInputStatus[0] == 0; noteInputStatus[1] == 0;}
    
    int SIG2Value = analogRead(SIG2);
    if (SIG2Value > 800) {noteInputStatus[3] == 1;}
    else if (SIG2Value > 500) {noteInputStatus[2] == 1;}
    else {noteInputStatus[2] == 0; noteInputStatus[3] == 0;}

/*
    if (SIG1Value > 800 && noteStatus[0] == 0) {
    midi2.sendNoteOn(noteValue[0], 127, 1);
    noteStatus[0] = 1;
    }
    else if (SIG1Value > 500 && noteStatus[1] == 0) {
    midi2.sendNoteOn(noteVaue[1], 127, 1);
    noteStatus[1] = 1;
    }
*/   
    
    midi2.sendNoteOn(60, 127, 1);
    digitalWrite(LEDOut, HIGH);
    delay(1000);
    // Send a MIDI Note Off message (Note, Velocity, Channel)
    midi2.sendNoteOff(60, 0, 1);
    digitalWrite(LEDOut, LOW);
    delay(1000);
}

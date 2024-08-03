// LED trigger with MIDI - coded for C3, C#3, D3, D#3
// @jeremyscook 8-3-2024
// Modified from code found below:
// https://www.notesandvolts.com/2015/02/midi-for-arduino-input-test.html

#include <MIDI.h>  // Add Midi Library

#define LED 13
#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5


//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode (LED, OUTPUT);
  pinMode (LED1, OUTPUT); // Set Arduino board pin 13 to output
  pinMode (LED2, OUTPUT); // Set Arduino board pin 13 to output
  pinMode (LED3, OUTPUT); // Set Arduino board pin 13 to output
  pinMode (LED4, OUTPUT); // Set Arduino board pin 13 to output
  MIDI.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  MIDI.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
}

void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.
}

// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) { 
 digitalWrite(LED, HIGH);
 if (pitch == 0x3C){
    digitalWrite(LED1, HIGH);
  }
  if (pitch == 0x3D){
  digitalWrite(LED2, HIGH);
  }
  if (pitch == 0x3E){
    digitalWrite(LED3, HIGH);
  }
  if (pitch == 0x3F){
  digitalWrite(LED4, HIGH);
  }
}

// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED, LOW);
  if (pitch == 0x3C){
    digitalWrite(LED1, LOW);
  }
  if (pitch == 0x3D){
    digitalWrite(LED2, LOW);
  }
  if (pitch == 0x3E){
    digitalWrite(LED3, LOW);
  }
  if (pitch == 0x3F){
    digitalWrite(LED4, LOW);
  }
}

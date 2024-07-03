//modified from code found here: https://www.notesandvolts.com/2015/02/midi-for-arduino-input-test.html
//to use software serial library @JeremySCook 7/2/2024
//Note that pin 13 will not work as serial input, apparenlty per builtin LED

#include <MIDI.h>  // Add Midi Library
#include <SoftwareSerial.h>

#define LED 13    // Arduino Board LED is on Pin 13

SoftwareSerial mySerial(9, 8); // RX, TX - RX (2) used later as no input used
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

//Create an instance of the library with default name, serial port and settings
//MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  pinMode (LED, OUTPUT); // Set Arduino board pin 13 to output
  mySerial.begin(31250); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  midi2.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  midi2.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
}

void loop() { // Main loop
  midi2.read(); // Continuously check if Midi data has been received.
}

// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED,HIGH);  //Turn LED on
}

// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED,LOW);  //Turn LED off
}

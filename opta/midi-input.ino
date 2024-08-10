//Modified for use w/ Arduino Opta - from Notes & Volts originally?
//@JeremySCook Aug 10, 2024

#include <MIDI.h>  // Add Midi Library

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiOpta);

void setup() {
  pinMode (LED_BUILTIN, OUTPUT); // Set Arduino board pin 13 to output
  midiOpta.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  midiOpta.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  midiOpta.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
}

void loop() { // Main loop
  midiOpta.read(); // Continuously check if Midi data has been received.
}

// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED_BUILTIN,HIGH);  //Turn LED on
}

// MyHandleNoteOFF is the function that will be called by the Midi Library
// when a MIDI NOTE OFF message is received.
// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity
void MyHandleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED_BUILTIN,LOW);  //Turn LED off
}

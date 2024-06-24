// Simple tutorial on how to send MIDI message on software serial
// Library https://github.com/FortySevenEffects/arduino_midi_library
// Modified from tutorial by @JeremySCook 6/24/2024

#include <MIDI.h>
#include <SoftwareSerial.h>
using Transport = MIDI_NAMESPACE::SerialMIDI<SoftwareSerial>;
int rxPin = 10; //not actually used here
int txPin = 11;
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
Transport serialMIDI(mySerial);
MIDI_NAMESPACE::MidiInterface<Transport> MIDI((Transport&)serialMIDI);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    MIDI.begin(4);                      // Launch MIDI and listen to channel 4
}

void loop()
{
        digitalWrite(LED_BUILTIN, HIGH);
        MIDI.sendNoteOn(60, 127, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
        delay(1000);		            // Wait for a second
        MIDI.sendNoteOff(60, 0, 1);     // Stop the note
        digitalWrite(LED_BUILTIN, LOW);
        delay(2000);
}

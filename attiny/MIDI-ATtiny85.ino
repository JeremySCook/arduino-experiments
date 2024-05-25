//needs ATtiny85 - will not compile on -45
//Tested May 24th 2024 - @jeremyscook

#include <MIDI.h>
#include <SoftwareSerial.h>

// Define the SoftwareSerial port
SoftwareSerial mySerial(0, 1); // RX, TX
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(2, OUTPUT);
}

void loop() {
    // Send a MIDI Note On message (Note, Velocity, Channel)
    midi2.sendNoteOn(60, 127, 1);
    digitalWrite(2, HIGH);
    delay(1000);
    // Send a MIDI Note Off message (Note, Velocity, Channel)
    midi2.sendNoteOff(60, 0, 1);
    digitalWrite(2, LOW);
    delay(1000);
}

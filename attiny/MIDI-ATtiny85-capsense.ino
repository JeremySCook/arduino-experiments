//needs ATtiny85 - will not compile on -45
//Tested May 24th 2024 - @jeremyscook
//Added touch on ADC Pin 3, works but does not stay on constantly
//(sounds like a telephone ringer)

#include <ADCTouch.h>
#include <MIDI.h>
#include <SoftwareSerial.h>

// Define the SoftwareSerial port
SoftwareSerial mySerial(0, 1); // RX, TX - possible to assign both to same pin in in/out-only situation?
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(2, OUTPUT);
}

void loop() {
    int value0 = ADCTouch.read(3, __AVR_ATtiny85__);
    // Send a MIDI Note On message (Note, Velocity, Channel)
    if (value0 > 750){
    midi2.sendNoteOn(60, 127, 1);
    digitalWrite(2, HIGH);
    delay(10);
    }
    else{
    midi2.sendNoteOff(60, 0, 1);
    digitalWrite(2, LOW);
    delay(10);
    }
}

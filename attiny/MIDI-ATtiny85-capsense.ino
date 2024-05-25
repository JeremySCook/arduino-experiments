//needs ATtiny85 - will not compile on -45
//Tested May 24th 2024 - @jeremyscook

#include <ADCTouch.h>
#include <MIDI.h>
#include <SoftwareSerial.h>

bool onBit = 0; //toggle bit to prevent system from playing note over and over
int capOn = 750;

// Define the SoftwareSerial port
SoftwareSerial mySerial(0, 1); // RX, TX - possible to assign both to same pin in in/out-only situation? (does not appear to work per May 25th (1,1) test)
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(2, OUTPUT);
}

void loop() {
    int value0 = ADCTouch.read(3, __AVR_ATtiny85__);
    // Send a MIDI Note On message (Note, Velocity, Channel)
    if ((value0 >= capOn) && (onBit == 0)){
    midi2.sendNoteOn(60, 127, 1);
    digitalWrite(2, HIGH);
    onBit = 1;
    delay(5);
    }
    if ((value0 < capOn) && (onBit == 1)){
    midi2.sendNoteOff(60, 0, 1);
    digitalWrite(2, LOW);
    onBit = 0;
    delay(5);
    }
    delay(50); //delays implemented to keep from "ringing" on and off
}

// Based on Arduino software serial library found here: https://docs.arduino.cc/learn/built-in-libraries/software-serial/
// Modified by @JeremySCook for MIDI usage - plays C3 every second
// MIDI pin 5 hooked up to TX pin 11, RX not needed here.
// Sends a signal, but not generally exactly correct

#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

// Set up a new SoftwareSerial object
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup()  {
    // Define pin modes for TX and RX
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);

    // Set the baud rate for the SoftwareSerial object
    mySerial.begin(31250);
}

void loop() {
    mySerial.print(0x90);
    mySerial.print(0x3C);
    mySerial.print(0x7F);
    delay(2000); 
}

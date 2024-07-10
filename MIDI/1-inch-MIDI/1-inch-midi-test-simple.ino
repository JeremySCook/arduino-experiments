/*WIP 7/6/2024 @JeremySCook

Programmed 1 inch MIDI at 1 MHz, 3.3V
Works, blinking intermittently

*/

#include <MIDI.h>
#include <SoftwareSerial.h>
#include <tinysnore.h>

#define MIDIOut 0
#define MIDIIn 5 // Reset pin acts as dummy since not needed?
#define LEDOut 1
#define SIG1 2
#define SIG2 3
#define Aux 4

SoftwareSerial mySerial(MIDIIn, MIDIOut); // RX, TX
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(LEDOut, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LEDOut, HIGH);  // turn the LED on (HIGH is the voltage level)
  snore(10);                      // wait for a second
  digitalWrite(LEDOut, LOW);   // turn the LED off by making the voltage LOW
  snore(1000);                      // wait for a second
}

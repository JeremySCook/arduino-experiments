/*WIP 7/6/2024 @JeremySCook

Programmed 1 inch MIDI at 1 MHz, 3.3V
Works, blinking intermittently
sends C3 velocity 127 when programmed at 8 MHz (Jul 10th)
could potentially still work at 1 MHz as the external LED
was switched to not light up when transmitting

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
  midi2.sendNoteOn(60, 127, 1); //sends middle C over and over
  snore(5);
  digitalWrite(LEDOut, HIGH);
  snore(5);                      // wait for a second
  digitalWrite(LEDOut, LOW);   // turn the LED off by making the voltage LOW
  snore(1000);                      // wait for a second
}

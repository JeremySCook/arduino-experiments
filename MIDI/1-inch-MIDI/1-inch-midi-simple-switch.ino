/*WIP 7/6/2024 @JeremySCook

Programmed 1 inch MIDI at 1 MHz, 3.3V
Works, blinking intermittently
sends C3 velocity 127 when programmed at 8 MHz (Jul 10th)
could potentially still work at 1 MHz as the external LED
was switched to not light up when transmitting

//triggers LED and MIDI in current form, but reading is meta event

*/

#include <MIDI.h>
#include <SoftwareSerial.h>
#include <tinysnore.h>

#define MIDIOut 0
#define MIDIIn 5 // Reset pin acts as dummy since not needed?
#define LEDOut 1
#define SIG1 1 // ADC Pin 1, corresponds to PB2
#define SIG2 3
#define Aux 4

bool noteStatus = 0;

SoftwareSerial mySerial(MIDIIn, MIDIOut); // RX, TX
MIDI_CREATE_CUSTOM_INSTANCE(SoftwareSerial, mySerial, midi2, midi::DefaultSettings);

void setup() {
    // Initialize SoftwareSerial
    mySerial.begin(31250); // MIDI baud rate
    pinMode(LEDOut, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {

  int SIG1Value = analogRead(SIG1);
  if (SIG1Value > 200 && noteStatus == 0){
    midi2.sendNoteOn(60, 127, 1); //sends middle C
    noteStatus = 1;
    snore(5);
    digitalWrite(LEDOut, HIGH);
    snore(5);
    digitalWrite(LEDOut, LOW);
    snore(50);
  } 
  else if (SIG1Value < 201 && noteStatus == 1){
    midi2.sendNoteOff(60, 127, 1); //sends middle C off
    noteStatus = 0;
    snore(5);
    digitalWrite(LEDOut, HIGH);
    snore(5);
    digitalWrite(LEDOut, LOW);
    snore(50);
  }
  snore(100); //polls every 10ms, sleeps otherwise
}

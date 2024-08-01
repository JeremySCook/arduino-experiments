#include <MIDI.h>

// Simple tutorial on how to receive and send MIDI messages.
// Here, when receiving any message on channel 4, the Arduino
// will blink a led and play back a note for 1 second.

MIDI_CREATE_DEFAULT_INSTANCE();

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(LED_D0, OUTPUT);
    MIDI.begin(1);                      // Launch MIDI and listen to channel 1
}

void loop()
{
  digitalWrite(LED_D0, HIGH);
    if (MIDI.read())                    // If we have received a message
    {
        digitalWrite(LED_BUILTIN, HIGH);
        MIDI.sendNoteOn(42, 127, 1);    // Send a Note (pitch 42, velo 127 on channel 1)
        delay(1000);		            // Wait for a second
        MIDI.sendNoteOff(42, 0, 1);     // Stop the note
        digitalWrite(LED_BUILTIN, LOW);
    }
}

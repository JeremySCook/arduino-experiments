#include "tinysnore.h"

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(0, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(0, HIGH);  // turn the LED on (HIGH is the voltage level)
  snore(5000);                      // wait for a second
  digitalWrite(0, LOW);   // turn the LED off by making the voltage LOW
  snore(5000);                      // wait for a second
}

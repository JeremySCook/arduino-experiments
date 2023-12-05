/*
 * TINY SNORE EXAMPLE
 * by Connor Nishijima
 * 
 * -------------------------------------------------------------------
 * 
 * TinySnore was designed as the simplest possible solution for
 * putting an ATtiny25/45/85 into deep sleep for custom periods
 * of time. The sleep function has an accuracy down to 16ms, and
 * can accept lengths up to 4,294,967,295ms - which is just under
 * 50 days long! Try and test it, I dare you.
 * 
 * This is basically the default blink sketch using TinySnore during
 * the LOW period of the blink. Because all LEDs are different, here
 * are the stats without the LED connected:
 * 
 * AT 16MHZ (INTERNAL):
 *    5V:
 *      ON:  14.8    mA
 *      OFF:  0.0066 mA
 *    3.3V:
 *      ON:   8.5    mA
 *      OFF:  0.0047 mA
 *
 * AT 8MHZ (INTERNAL):
 *    5V:
 *      ON:   8.6    mA
 *      OFF:  0.0066 mA
 *    3.3V:
 *      ON:   4.7    mA
 *      OFF:  0.0047 mA  
 *      
 * AT 1MHZ (INTERNAL):
 *    5V:
 *      ON:   3.1    mA
 *      OFF:  0.0066 mA
 *    3.3V:
 *      ON:   1.1    mA
 *      OFF:  0.0047 mA
 *      
 * So basically, no matter the frequency, TinySnore should give
 * you 6.6uA @ 5V and 4.7uA @ 3.3V in sleep!
 * 
 * -------------------------------------------------------------------
 * Modified by @jeremyscook 12/5/2023 to act as a "sleep subprocessor" for RPi/other devices
 */

#include "tinysnore.h" // Include TinySnore Library
#define onSwitch 2 // Pin flashing LED is on

void setup() {
  pinMode(onSwitch, OUTPUT);
  //pinMode(led, OUTPUT);
  digitalWrite(onSwitch, HIGH);
  //digitalWrite(led, LOW);
  snore(1000); // MOSFET output OFF for XXX initially

}

void loop() {
  digitalWrite(onSwitch, LOW);
  //digitalWrite(led, HIGH);
  snore(1000); // hold onSwitch LOW for 1 second
  digitalWrite(onSwitch, HIGH);
  //digitalWrite(led, LOW);
  snore(180000); // hold onSwitch HIGH for 3 minutes before restarting again
}

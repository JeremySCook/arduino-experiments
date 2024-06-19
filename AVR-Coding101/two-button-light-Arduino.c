/* ************************************************************************************
* File:    lesson1a.h
* Date:    2023.01.16
* Author:  Bradán Lane STUDIO
*
* This content may be redistributed and/or modified as outlined under the MIT License
*
* ************************************************************************************

## lesson1a.h - General I/O Pins using Arduino framework

Control a single LED using a button. It demonstrates basic input and output using I/O pins.

This is a comparison of lesson 1 when using the Arduino framework.

Each lesson consists of the lesson documentation and coding exercise(s).
The culmination of all exercises for a given lesson are provided in a "lesson<n>.h" file
with the same number as the lesson.

* ************************************************************************************/

// FYI: not all of these includes are needed for every lesson
// they are all included here to simplify progress through all the lessons

// IMPORTANT: in platformio.ini you need to uncomment the line: "framework = arduino" to use this example

#include <Arduino.h>

int main (void) {

	pinMode(PIN_PB5, INPUT_PULLUP);
	pinMode(PIN_PC3, INPUT_PULLUP);
	pinMode(PIN_PA1, OUTPUT);
	pinMode(PIN_PA2, OUTPUT);
	digitalWrite(PIN_PA1, LOW);
	digitalWrite(PIN_PA2, LOW);

	while (1) {

        if ( digitalRead(PIN_PB5) == 0 ) {	// read the button pin to see if it is 0 or 1
			// 0 means the button is pressed
			// turn on the LED by setting the anode pin of the LED to HIGH
			digitalWrite(PIN_PA2, HIGH);
			digitalWrite(PIN_PA1, LOW);
		}
		if ( digitalRead(PIN_PC3) == 0 ) {	// read the button pin to see if it is 0 or 1
			// 0 means the button is pressed
			// turn on the LED by setting the anode pin of the LED to HIGH
			digitalWrite(PIN_PA2, LOW);
			digitalWrite(PIN_PA1, HIGH);
		}
		else {
			// 1 means the button is released
			// turn off the LED by setting the anode pin of the LED to LOW
			digitalWrite(PIN_PA2, LOW);
			digitalWrite(PIN_PA1, LOW);
		}
    }
}

/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
  modified for use with the opta - outputs on USB serial, as well as AUX serial
  @jeremyscook Aug 10, 2024
*/


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial1.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(BTN_USER, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int buttonState = digitalRead(BTN_USER);
  // print out the state of the button:
  Serial.println(buttonState);
  Serial1.println(buttonState+1);
  delay(100);  // delay in between reads for stability
}

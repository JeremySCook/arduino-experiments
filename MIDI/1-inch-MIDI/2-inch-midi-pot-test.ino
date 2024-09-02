/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
  Modified by @JeremySCook Aug 21st, 2024 for potentiometer across pins A0, A1, A2
  Tested on Arduino Pro Mini
*/

// the setup routine runs once when you press reset:

#define LEDPin 1

void setup() {
  pinMode(LEDPin, OUTPUT); //LED pin
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(2);
  int sensorAnalog = map(sensorValue, 8, 1015, 0, 9); // 8 to 1015 to account for imperfect values @ top & bottom

  // PWM LED based on mapped input value:
  // analogWrite(LED_BUILTIN, sensorAnalog); does not seem to work on Pro Mini, wrote analog function below:
  digitalWrite(LEDPin, HIGH);
  delay(sensorAnalog);
  digitalWrite(LEDPin, LOW);
  delay(9 - sensorAnalog); //10 levels including 0 for off

  delay(1);  // delay in between reads for stability
}

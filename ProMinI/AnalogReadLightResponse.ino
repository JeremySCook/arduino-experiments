/*
  Reads an analog input on pin 0, lights onboard LED proportionally
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
  Modified by @JeremySCook Aug 21st, 2024 for potentiometer across pins A0, A1, A2
  Tested on Arduino Pro Mini
*/

// the setup routine runs once when you press reset:
void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A2, LOW);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A1);
  int sensorAnalog = map(sensorValue, 8, 1015, 0, 9); // 8 to 1015 to account for imperfect values @ top & bottom

  // PWM LED based on mapped input value:
  // analogWrite(LED_BUILTIN, sensorAnalog); does not seem to work on Pro Mini, wrote analog function below:
  digitalWrite(LED_BUILTIN, HIGH);
  delay(sensorAnalog);
  digitalWrite(LED_BUILTIN, LOW);
  delay(9 - sensorAnalog); //10 levels including 0 for off

  // print out the value you read:
  Serial.print(sensorValue); Serial.print("  "); Serial.println(sensorAnalog);
  delay(1);  // delay in between reads for stability
}

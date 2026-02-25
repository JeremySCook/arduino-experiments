const int stepCommandPin =   12;
const int stepDirectionPin = 11;
const int stepEnablePin =    10;
const int inputButtonPin =   9;
bool inputButtonState =      0;
bool stepDirectionState =    0;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(stepCommandPin, OUTPUT);
  pinMode(stepDirectionPin, OUTPUT);
  pinMode(inputButtonPin, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  if (digitalRead(inputButtonPin) == LOW) digitalWrite(stepDirectionPin, LOW);
  else digitalWrite(stepDirectionPin, HIGH);
  digitalWrite(stepCommandPin, HIGH);
  delay(10);
  digitalWrite(LED_BUILTIN, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  digitalWrite(stepCommandPin, LOW);
  delay(10);
}

//By Jeremy Cook 12/27/2023 - @jeremyscook
//Actuates relay and LEDs via button or sensor on A0/I1
//Use as you please, public domain

void setup() {
  // Initialize pins as inputs and outputs
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN_USER, INPUT);
  pinMode(A0, INPUT); // A0, which is labeled I1, acting as digital input
  pinMode(RELAY1, OUTPUT);
  pinMode(LED_RELAY1, OUTPUT);
}
//Actually none of above has to be done! Need setup, but can be empty.
//Likely needed to set analog properly 

void loop() {
  bool buttonState = digitalRead(BTN_USER); //bool, because why use an int?
  bool sensorState = digitalRead(A0);
  // Turn the LED_BUILTIN ON
  if(buttonState == 0 or sensorState == 1){
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(RELAY2, HIGH);
  digitalWrite(LED_RELAY2, HIGH);
  delay(10);
  }
  // Turn the user LED_BUILTIN OFF
  if(buttonState == 1 and sensorState == 0){ //both are off, turns off
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(RELAY2, LOW);
  digitalWrite(LED_RELAY2, LOW);
  delay(10);
  }

}

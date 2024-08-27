int lightValue = 2; //2 is off in this case, 1 on
int lightPin= 13; //onboard LED is 13, can be changed if needed

void setup() {
  pinMode(lightPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    lightValue = Serial.parseInt();
    //Serial.println(lightValue);
    if (lightValue == 1) {
      digitalWrite(lightPin, HIGH);
      Serial.println("LED ON PER SERIAL");
    }
    else if (lightValue == 2) {
      digitalWrite(lightPin, LOW);
      Serial.println("LED OFF PER SERIAL");
    }
  }
}

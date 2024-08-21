// Code resources:
// https://maker.pro/arduino/projects/led-controlling-using-serial-monitor-arduino
// https://www.instructables.com/Control-LED-Using-Serial-Monitor/
// https://docs.arduino.cc/tutorials/nano-every/run-4-uart/
// software serial on Arduino Nano 1, transmits to Nano 2, etc
// Can use multiple boards to create a cascade of inputs/outputs

#include <SoftwareSerial.h>
SoftwareSerial auxSerial(5, 6); // RX (yellow), TX (blue)
int lightValue = 2; //2 is off in this case, 1 on
int lightPin= 13; //onboard LED is 13, can be changed if needed
int buttonPin = 3;
bool buttonToggle = 0;
bool buttonValue = 0;

void setup() {
  pinMode(lightPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  auxSerial.begin(9600);
}
void loop() {
  if (Serial.available() > 0) {
    lightValue = Serial.parseInt();
    //Serial.println(lightValue);
    if (lightValue == 1) {
      digitalWrite(lightPin, HIGH);
      Serial.println("LED ON PER SERIAL");
      auxSerial.print(lightValue); //re-transmits value received
    }
    else if (lightValue == 2) {
      digitalWrite(lightPin, LOW);
      Serial.println("LED OFF PER SERIAL");
      auxSerial.print(lightValue); //re-transmits value received
    }
  //Serial.flush(); did not work, used end/begin below
  Serial.end();
  Serial.begin(9600);
  }
  buttonValue = digitalRead(buttonPin);
  if(buttonValue == 0 && lightValue == 1 && buttonToggle == 0) {
    digitalWrite(lightPin, 0);
    lightValue = 2; // 2 = OFF
    auxSerial.print(lightValue); //transmits light value per button
    Serial.println("LED OFF PER BUTTON");
    buttonToggle = 1; // button has been pressed down
  } // low = pressed
  if(buttonValue == 0 && lightValue == 2 && buttonToggle == 0) {
    digitalWrite(lightPin, 1);
    lightValue = 1; // 1 = ON
    auxSerial.print(lightValue); //transmits light value per button
    Serial.println("LED ON PER BUTTON");
    buttonToggle = 1; // button has been pressed down
  }
  if(buttonValue == 1 && buttonToggle == 1){
    buttonToggle = 0; //button has transitioned from down do up, averts multiple inputs
  }
  delay(50);
}

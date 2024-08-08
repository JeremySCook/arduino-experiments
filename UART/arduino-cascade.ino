// Code resources:
// https://maker.pro/arduino/projects/led-controlling-using-serial-monitor-arduino
// https://www.instructables.com/Control-LED-Using-Serial-Monitor/
// https://docs.arduino.cc/tutorials/nano-every/run-4-uart/
// software serial on Arduino Nano 1, transmits to Nano 2, etc
// Can use multiple boards to create a cascade of inputs/outputs

#include <SoftwareSerial.h>
SoftwareSerial auxSerial(2, 3); // RX (purple), TX (blue)

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  auxSerial.begin(9600);
}
void loop() {
  if (Serial.available()) {
    int state = Serial.parseInt();
    Serial.println(state);
    auxSerial.print(state); //re-transmits state value received
    if (state == 1) {
      digitalWrite(13, HIGH);
      Serial.println("LED ON");
    }
    if (state == 2) {
      digitalWrite(13, LOW);
      Serial.println("LED OFF");
    }
    state = 0;
  }
  delay(50);
}

// add jumper for test routine - faster cycline

#include <tinysnore.h>

int LEDneg = 0;
int LEDpos = 1;
int servoPin = 2;
int jumperPin = 3;
long waterCycle = 86400000; // 86400000 is one full day

void setup() {
  pinMode(LEDneg, OUTPUT); // keep this low at all times
  pinMode(LEDpos, OUTPUT); // switch for off/on
  pinMode(servoPin, OUTPUT);
  pinMode(jumperPin, INPUT_PULLUP);
  if (digitalRead(jumperPin) == LOW) waterCycle = 2000;
 
  digitalWrite(LEDneg, LOW); // keep this low at all times
  digitalWrite(LEDpos, HIGH); // blink on on bootup
  snore(500);
  digitalWrite(LEDpos, LOW); // blink on on bootup
  snore(500);
}

// the loop function runs over and over again forever
void loop() {
  servoZero();
  snore(waterCycle); // sleep an entire day
  servoFull();
  snore(waterCycle); // sleep an entire day
}

void servoZero() {
for (int i = 0; i < 100; i++) {
digitalWrite(LEDpos, HIGH);
digitalWrite(servoPin, HIGH);
delayMicroseconds(1000);
digitalWrite(LEDpos, LOW);
digitalWrite(servoPin, LOW);
delayMicroseconds(20000);
}
}

void servoFull() {
for (int i = 0; i < 100; i++) {
digitalWrite(LEDpos, HIGH);
digitalWrite(servoPin, HIGH);
delayMicroseconds(2000);
digitalWrite(LEDpos, LOW);
digitalWrite(servoPin, LOW);
delayMicroseconds(20000);
}
}



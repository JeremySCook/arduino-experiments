// add jumper for test routine - faster cycline

#include <tinysnore.h>
#include <tinyServo85.h>

tinyServo85 servo;

static int LED = 0;
static int servoPin = 2;
static int jumperPin = 3;
static int MOSFET = 4;
long waterCycle = 20000; // 86400000 is one full day

void setup() {
  pinMode(LED, OUTPUT); // indicator LED
  pinMode(servoPin, OUTPUT);
  pinMode(jumperPin, INPUT_PULLUP);
  pinMode(MOSFET, OUTPUT);
  if (digitalRead(jumperPin) == LOW) waterCycle = 2000;
  digitalWrite(MOSFET, HIGH);
  digitalWrite(LED, HIGH);
  snore(500);
  digitalWrite(LED, LOW); // blink on on bootup
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
  digitalWrite(MOSFET, LOW);   // Power on
  digitalWrite(LED, HIGH);
  delay(500);
  servo.attachServo(servoPin);
  servo.setServo(servoPin, 0);       // Move to 0°
  delay(1500);                 // Allow time to move
  servo.detachServo(servoPin);       // Stop pulses, pin becomes INPUT
  digitalWrite(LED, LOW);
  digitalWrite(MOSFET, HIGH);  // Power off
}

void servoFull() {
  digitalWrite(MOSFET, LOW);
  digitalWrite(LED, HIGH);
  delay(500);
  servo.attachServo(servoPin);
  servo.setServo(servoPin, 180);     // Or try 179
  delay(1500);
  servo.detachServo(servoPin);
  digitalWrite(LED, LOW);
  digitalWrite(MOSFET, HIGH);
}



//MOSFET snooze

#include <tinysnore.h>

static int LED = 0;
static int MOSFET = 4;
long offCycle = 3000;
long onCycle = 1000;

void setup() {
  pinMode(LED, OUTPUT); // indicator LED
  pinMode(MOSFET, OUTPUT);
  digitalWrite(MOSFET, HIGH);
  digitalWrite(LED, HIGH);
  digitalWrite(LED, LOW); // blink on on bootup
  snore(500);
}

void loop(){
  digitalWrite(MOSFET, LOW); // LOW MOSFET lets current flow
  digitalWrite(LED, HIGH); // LED Indicator current flowing
  snore(onCycle);
  digitalWrite(MOSFET, HIGH);
  digitalWrite(LED, LOW);
  snore(offCycle);
}

//blinks and sends a software serial message to pin 3
//commented out "CLKPR" lines allow for prescaler

#include <SoftwareSerial.h>

#define RX 3
#define TX 4
SoftwareSerial Serial(RX, TX);

void setup() {
  //CLKPR = 0x80; // enable system clock prescaler
  //CLKPR = 0x06; // set system clock prescaler to 1, chg p32 ATtiny datasheet, eg 0x06 = 64
  pinMode(0, OUTPUT);
  Serial.begin(9600);
  Serial.println("Initializing...");
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(0, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                      // wait for a second
  digitalWrite(0, LOW);   // turn the LED off by making the voltage LOW
  delay(100);                      // wait for a second
  Serial.println("blinking!");
}

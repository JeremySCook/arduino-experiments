#include <Adafruit_PCF8574.h>

/* Example for 3 output LEDs, connected from power to the GPIO expander pin 5, 6, 7
 * Note the LEDs must be connected with the CATHODES to the expander, to SINK current!
 * The PCF8574 cannot SOURCE current!
 * Modified from Adafruit PCF8574 library example code
 * Arduino Opta breakout: https://www.tindie.com/products/35482
 * Find I2C address: https://learn.adafruit.com/scanning-i2c-addresses/arduino
 */

Adafruit_PCF8574 pcf;

void setup() {
  pcf.begin(0x38, &Wire); //change to suit
  pcf.pinMode(7, OUTPUT);
  pcf.pinMode(8, OUTPUT);
  pcf.pinMode(9, OUTPUT);
  pcf.digitalWrite(7, HIGH);  //turn LED off by turning off sinking transistor
  pcf.digitalWrite(6, HIGH);  //turn LED off by turning off sinking transistor
  pcf.digitalWrite(5, HIGH);  //turn LED off by turning off sinking transistor
}

void loop() {
  pcf.digitalWrite(7, LOW);  // turn LED on by sinking current to ground
  pcf.digitalWrite(5, HIGH);  //turn LED off by turning off sinking transistor  
  delay(200);
  pcf.digitalWrite(6, LOW);  // turn LED on by sinking current to ground
  pcf.digitalWrite(7, HIGH);  //turn LED off by turning off sinking transistor  
  delay(200);
  pcf.digitalWrite(5, LOW);  // turn LED on by sinking current to ground
  pcf.digitalWrite(6, HIGH);  //turn LED off by turning off sinking transistor  
  delay(200);
}

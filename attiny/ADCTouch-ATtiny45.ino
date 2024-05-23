#include <ADCTouch.h>

void setup() 
{
    pinMode(0, OUTPUT);
} 

void loop() 
{
    int value0 = ADCTouch.read(2, __AVR_ATtiny45__);
    if (value0 > 500) {
    digitalWrite(0, HIGH);
    }
    else {
    digitalWrite(0, LOW);
    }
    delay(100);
}

//Have not gotten the serial portion to respond yet, but light
//does blink based on contact

#include <ADCTouch.h>
#include <SoftwareSerial.h>

#define RX 3
#define TX 4
SoftwareSerial Serial(RX, TX);

void setup() 
{
    pinMode(0, OUTPUT);
    Serial.begin(9600);
    Serial.println("Initializing...");
} 

void loop() 
{
    int value0 = ADCTouch.read(2, __AVR_ATtiny45__);
    Serial.print("Analog Value: "); Serial.println(value0);
    if (value0 > 600) {
    digitalWrite(0, HIGH);
    }
    else {
    digitalWrite(0, LOW);
    }
    delay(100);
}

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
    int value0 = ADCTouch.read(1, __AVR_ATtiny45__); //pin A1, ie PB2, A2/A3 interfere with TX/RX here
    if (value0 > 600) {
    digitalWrite(0, HIGH);
    }
    else {
    digitalWrite(0, LOW);
    }
    delay(100);
    Serial.print("Analog Value: "); Serial.println(value0);
}

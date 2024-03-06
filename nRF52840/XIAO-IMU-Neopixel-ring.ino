#include <LSM6DS3.h>
#include <Wire.h>

//NeoPixel setup
#include <Adafruit_NeoPixel.h>
#define PIN D6
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

//Create a instance of class LSM6DS3
LSM6DS3 myIMU(I2C_MODE, 0x6A);    //I2C device address 0x6A
float aX, aY, aZ, gX, gY, gZ;
const float accelerationThreshold = 2.5; // threshold of significant in G's

int ringArray[] = {6, 7, 0, 1, 2, 3, 4, 5};

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  myIMU.begin();
  Serial.begin(9600);
}
//seems to not work when serial disconnected - need to find a fix
void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  aZ = myIMU.readFloatAccelZ();
  //aY = myIMU.readFloatAccelY();
  int aZint = aZ*-100;
  int aZmap = map(aZint, -100, 100, 0, 7);
  //int ringPosition = ringArray[aZmap];
  pixels.setPixelColor(ringArray[aZmap], pixels.Color(0, 150, 0));
  pixels.setPixelColor(ringArray[aZmap +1], pixels.Color(0, 75, 75));
  pixels.setPixelColor(ringArray[aZmap -1], pixels.Color(0, 75, 75));
  pixels.show(); 
  Serial.print("AccelZ: "); Serial.println(myIMU.readFloatAccelY(), 3);
  Serial.println(aZint);
  Serial.print("aZmap: ");
  Serial.println(aZmap);
  Serial.print("ringArray value: ");
  Serial.println(ringArray[aZmap]);
  delay(5);
}

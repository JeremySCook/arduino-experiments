/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/
/*

BUTTON_RESPONSE CODE FOR ARDUINO OPTA W/ I2C and Serial
Aux Breakout W/ SSD1306 128x64 SCREEN - breakout sold on jcdevices.com

*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // if purchased from Adafruit, likely 0x3D 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool buttonFlip = 0;
int buttonPresses = 0;
//======================================================

void setup() {
  pinMode(BTN_USER, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(500);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.setRotation(0); // 0, no rotation; 1, 90; 2 180
  display.display();
  delay(500); // Pause for .5 second
  display.clearDisplay();
  drawHeader();
}

void loop() {
  if ((digitalRead(BTN_USER) == LOW) && (buttonFlip == 0)) {
    buttonFlip = 1;
    buttonPresses += 1;
  }
  if ((digitalRead(BTN_USER) == HIGH) && (buttonFlip = 1)) {
    buttonFlip = 0; //release button before counting again
  }
  printPresses();
}

void printPresses(void){
  display.clearDisplay();
  display.setTextSize(4);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(30, 30);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.print(buttonPresses);
  drawHeader();
  display.display();
}

void drawHeader(void){
  display.setTextSize(1);
  display.setCursor(20, 3);
  display.print("presse count:");
}

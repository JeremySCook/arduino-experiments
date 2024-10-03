#include <SPI.h> //needed??
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "OptaBlue.h"
using namespace Opta; //not sure what this is for, but in examples

DigitalStSolidExpansion stsolidExp;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  OptaController.begin(); //maybe needed for SSR expansion? Not sure.
  stsolidExp = OptaController.getExpansion(0); //expansion at index 0 is solid state relay needed???

  display.clearDisplay(); //TAKE THIS OUT AND RUNS (BUT DOES NOTHING W/ SSD1306)
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(false);         // Use full 256 char 'Code Page 437' fon
  display.setRotation(0); //rotates the screen 90 degrees

}

void loop() { // Main loop
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}

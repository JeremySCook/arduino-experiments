//Prints text in different aread of 64x128 .96" OLED screen

#include <TinyWireM.h>
#include <Tiny4kOLED.h>
int delayValue = 500;

void setup() {
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  // Two fonts are supplied with this library, FONT8X16 and FONT6X8
  oled.setFont(FONT8X16);
  oled.clear();
}

void loop() {
    oled.on();
    delay(delayValue);
    oled.clear();
    oled.setCursor(0, 6);
    oled.print("Test -- 1");
    delay(delayValue);
    oled.clear();
    oled.setCursor(10, 0);
    oled.print("Test -- 2");
    delay(delayValue);
    oled.clear();
    oled.setCursor(63, 0);
    oled.print("Test -- 3"); //shows looping
    delay(delayValue);
    oled.clear();
    oled.setCursor(63, 6);
    oled.print("Test -- 4"); //shows looping on same row
    delay(delayValue);
    oled.clear();
    oled.setCursor(0,6 );
    oled.print("turn off OLED"); //will display when turned on unless cleared
    oled.off();
    delay(delayValue);
}


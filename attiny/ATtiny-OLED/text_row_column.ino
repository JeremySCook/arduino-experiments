//Prints text in different aread of 64x128 .96" OLED screen
//by @jeremyscook - tested w/ ATTiny85, internal 8 MHz clock - Nov 1, 2024

#include <TinyWireM.h>
#include <Tiny4kOLED.h>
int delayValue = 500;

void setup() {
  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  // Two fonts are supplied with this library, FONT8X16 and FONT6X8
  oled.setFont(FONT8X16);
  oled.on();
  oled.clear();
}

void loop() {
  for (int i = 0; i < 7; i = i+2){
    //oled.clear();
    oled.setCursor(0, i);
    oled.print("Row # "); oled.print(i);
    delay(delayValue);
  }
delay(1000);
oled.clear();

  for (int i = 0; i < 7; i = i+2){
    //oled.clear();
    int j = i * 16;
    oled.setCursor(j, i);
    oled.print("Col # "); oled.print(j); //last value will wrap
    delay(delayValue);
  }
delay(1000);
oled.clear();

}

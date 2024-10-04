
//For Arduino Opta input w/ SSRs
//Compiled but untested as of Sept 18, 2024
//Add code to show MIDI signals on OLED via new custom adapter?

//setup for SSD1306 module - need splash screen etc?

#include <SPI.h> //needed??
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//3 lines below used to scroll messages, not yet implemented
String messageType[] = {"_______", "PCH ON ", "PCH OFF"};
# define LINES_LENGTH 11
int messageTypeValue[LINES_LENGTH] = {0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0};
int messageValue[LINES_LENGTH] = {127, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0};

#include <MIDI.h>  // Add Midi Library
#include "OptaBlue.h"
using namespace Opta; //not sure what this is for, but in examples

DigitalStSolidExpansion stsolidExp;

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiOpta);

int pitchInputValue[] = {60, 62, 64, 65, 67, 69, 71, 72}; //input notes starting at C3
int pitchSSDMap[] = {0, 1, 2, 3, 4, 5, 6, 7}; //what each note maps to on SSD expansion

void setup() {
  OptaController.begin(); //maybe needed for SSR expansion? Not sure.
  stsolidExp = OptaController.getExpansion(0); //expansion at index 0 is solid state relay needed???
  pinMode (LED_BUILTIN, OUTPUT); // Set Arduino board pin 13 to output

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE, BLACK); // Draw white text, fill background
  display.setTextWrap(false);
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);       // Use full 256 char 'Code Page 437' fon
  display.setRotation(1); //rotates the screen 90 degrees
  display.display();
  
  midiOpta.begin(MIDI_CHANNEL_OMNI); // Initialize the Midi Library.
  // OMNI sets it to listen to all channels.. MIDI.begin(2) would set it 
  // to respond to notes on channel 2 only.
  midiOpta.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  midiOpta.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library 
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
}

void loop() { // Main loop
  midiOpta.read(); // Continuously check if Midi data has been received.
}
// MyHandleNoteON is the function that will be called by the Midi Library
// when a MIDI NOTE ON message is received.
// It will be passed bytes for Channel, Pitch, and Velocity

void MyHandleNoteOn(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED_BUILTIN, HIGH);  //Turn LED on
  Serial.print("Pitch On "); Serial.println(pitch);

  scrollValues(1, pitch); //message type, pitch/note

for(int i = 0; i < 8; i++){
  if (pitch == pitchInputValue[i]){
    stsolidExp.digitalWrite(pitchSSDMap[i], HIGH);
  }
}
stsolidExp.updateDigitalOutputs(); //UPDATE SOLID STATE OUTPUTS-
}

// * A NOTE ON message with Velocity = 0 will be treated as a NOTE OFF message *
// It will be passed bytes for Channel, Pitch, and Velocity

void MyHandleNoteOff(byte channel, byte pitch, byte velocity) { 
  digitalWrite(LED_BUILTIN,LOW);  //Turn LED off
  Serial.print("Pitch Off "); Serial.println(pitch);
  scrollValues(2, pitch); //message type, pitch/note

for(int i = 0; i < 8; i++){
  if (pitch == pitchInputValue[i]){
    stsolidExp.digitalWrite(pitchSSDMap[i], LOW);
  }
}
stsolidExp.updateDigitalOutputs(); //UPDATE SOLID STATE OUTPUTS
}

void scrollValues(int messageTypeValue0, int pitch1){

  for(int i = (LINES_LENGTH - 1); i > -1; i--){
    messageTypeValue[i + 1] = messageTypeValue[i];
    messageValue[i + 1] = messageValue[i]; //wrong message values are displayed
  }
  messageTypeValue[0] = messageTypeValue0;
  messageValue[0] = pitch1;

  for(int i = 0; i < LINES_LENGTH; i++){
  display.setCursor(0, (10 + i*10));
  display.print(messageType[messageTypeValue[i]]); display.print(" "); 
  display.print(messageValue[i]);
  }
  display.display();
}

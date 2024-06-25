//by @jeremyscook 6/24/2024
// Compiles, looks good to logic analyzer, but works poorly on actual MIDI hardware/untested in current version.

// define MIDI message bytes

//bool byte1[] = {1,0,0,1,0,0,0,0}; //status byte 90
//bool byte2[] = {0,0,1,1,1,1,0,0}; //data byte 1 3C
//bool byte3[] = {0,1,1,1,1,1,1,1}; //data byte 2 7F

const byte statusByte = B10010000; //0x90; // Note On channel 1
const byte dataByte1 = B00111100; //0x3C;  // Note number (60)
const byte dataByte2 = B01111111; //0x7F;  // Velocity (127)

// define MIDI transmission variables

const int MIDIOutPin = 11;
const int baudRate = 31250;
const int baudDelayMicroseconds = (1000000 / baudRate); //calculate delay in microseconds
const int delayBeats = 2000; //delay between playing a note in milliseconds

//Arduino Uno Pin 13 attached to MIDI pin X through 220 ohm resistor
//Arduino +5V attached to MIDI pin x through 220 ohm resistor

void setup() {
pinMode(MIDIOutPin, OUTPUT);
digitalWrite(MIDIOutPin, HIGH);

// Initialize serial for debugging if needed
// Serial.begin(9600);

}

void loop() {
  delay(delayBeats);
  // Transmit MIDI message
  transmitMIDI(statusByte);
  transmitMIDI(dataByte1);
  transmitMIDI(dataByte2);
}

void transmitMIDI(byte midiByte) {
  // Start bit (LOW)
  digitalWrite(MIDIOutPin, LOW);
  delayMicroseconds(baudDelayMicroseconds);
  //8 data bits
  for (int i = 0; i < 8; i++) {
    if (midiByte & (1 << i)) {
      digitalWrite(MIDIOutPin, HIGH);   
    }
    else {
      digitalWrite(MIDIOutPin, LOW);
    }
    delayMicroseconds(baudDelayMicroseconds);
  }
  // Stop bit (HIGH)
  digitalWrite(MIDIOutPin, HIGH);
  delayMicroseconds(baudDelayMicroseconds);
}


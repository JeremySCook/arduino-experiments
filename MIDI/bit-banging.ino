//by @jeremyscook 6/24/2024
//gives a result to MIDI monitor software, but not correct
//need to look at this further

int baudRate = 32150;
int baudDelayMicroseconds = ((1.0/baudRate)*1000000);
int delayBeats = 1000; //delay between playing a note in milliseconds
int MIDIOutPin = 13;

bool byte1[] = {1,0,0,1,0,0,0,0}; //status byte 90
bool byte2[] = {0,0,1,1,1,1,0,0}; //data byte 1 3C
bool byte3[] = {0,1,1,1,1,1,1,1}; //data byte 2 7F

//Arduino Uno Pin 13 attached to MIDI pin X through 220 ohm resistor
//Arduino +5V attached to MIDI pin x through 220 ohm resistor

void setup() {
pinMode(13, OUTPUT);
digitalWrite(MIDIOutPin, HIGH);
Serial.begin(9600);

}

void loop() {
delay(delayBeats);
//send first byte - includes start low/end high bits
Serial.println(baudDelayMicroseconds);
digitalWrite(MIDIOutPin, LOW);
Serial.print(0);
delayMicroseconds(baudDelayMicroseconds);
  for(int i = 0; i<8; i++){
    if (byte1[i] == 1){
      digitalWrite(MIDIOutPin, HIGH);
      Serial.print(1);
    }
    else{
      digitalWrite(MIDIOutPin, LOW);
      Serial.print(0);
    }
    delayMicroseconds(baudDelayMicroseconds);
  }
  digitalWrite(MIDIOutPin, HIGH);
  Serial.println(1);
  delayMicroseconds(baudDelayMicroseconds);

//send second byte
  
  digitalWrite(13, LOW);
  delayMicroseconds(baudDelayMicroseconds);
  for(int i = 0; i<8; i++){
    if (byte2[i] == 1){
      digitalWrite(MIDIOutPin, HIGH);    
    }
    else{
      digitalWrite(MIDIOutPin, LOW);
    }
    delayMicroseconds(baudDelayMicroseconds);
  }
  digitalWrite(MIDIOutPin, HIGH);
  delayMicroseconds(baudDelayMicroseconds);

//send third byte
  
  digitalWrite(13, LOW);
  delayMicroseconds(baudDelayMicroseconds);
  for(int i = 0; i<8; i++){
    if (byte3[i] == 1){
      digitalWrite(MIDIOutPin, HIGH);    
    }
    else{
      digitalWrite(MIDIOutPin, LOW);
    }
    delayMicroseconds(baudDelayMicroseconds);
  }
  digitalWrite(MIDIOutPin, HIGH);
  delayMicroseconds(baudDelayMicroseconds);
}

/*
void byteTransmit(sendByte){
  digitalWrite()
  delayMicroseconds(baudDelayMicroseconds)
  for(int i = 0; i<8; i++){
    if (byte1[i] == 1){
      //kick drum - solenoid
    }
    else{

}
*/

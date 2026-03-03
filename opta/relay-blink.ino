// by @jeremyscook 3/3/2026
// general relay example - meant for solenoid valves

int timeOnDelay = 1000; //how long device are active before retract (ms)
void setup() {
}

void loop() {
    digitalWrite(LED_RELAY1, LOW); // pinMode does not have to be declared
    digitalWrite(RELAY1, LOW);
    delay(timeOnDelay);
    digitalWrite(LED_RELAY1, HIGH);
    digitalWrite(RELAY1, HIGH);
    delay(timeOnDelay);
}

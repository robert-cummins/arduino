#include <Arduino.h>

const int READ_PIN = A2;
// float v2 = 0;
int readValue = 0;
const int RED_LED = 13; 
const int GREEN_LED = 12; 

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  Serial.begin(9600);
}


  // ---------------------------
  // Main loop: read sensor, print value, and set corresponding LED
  // ---------------------------
  // Reads the analog value from the sensor connected to READ_PIN
  // and prints it to the serial console.
  // Depending on the value, it sets either the red or green LED on (HIGH) or off (LOW).
  // The threshold value for this decision is 600.
void loop() {
  
  readValue = analogRead(READ_PIN);
  Serial.print("Analog Read Value: ");
  Serial.println(readValue);
  if(readValue < 600){
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    Serial.println("GREEN LED ON");
  } else {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    Serial.println("RED LED ON");
  }
}
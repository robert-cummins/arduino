#include <Arduino.h>

const int READ_PIN = A2;
float v2 = 0;
int readValue = 0;
const int LED_PIN = 9; // Pin for the built-in LED

void setup() {
  pinMode(READ_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(9600);
}



  // Continuously reads the analog input from the potentiometer and
  // uses this value to set the brightness of the built-in LED.
void loop() {
  
  readValue = analogRead(READ_PIN);
  // 2 different ways to convert the analog read value to a PWM value
  int pwmValue = (readValue * 255) / 1023;
  // int pwmValue = map(readValue, 0, 1023, 0, 255);
  analogWrite(LED_PIN, pwmValue);
  
}
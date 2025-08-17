#include <Arduino.h>

// Define the LED pin. Pin 13 is a common choice for onboard LEDs on
// many Arduino-compatible boards, including the Mega 2560 and often ESP32/ESP8266
// development boards that have a built-in LED.
const int LED_PIN = 13;

void setup() {
  // Initialize the LED_PIN as an output.
  pinMode(LED_PIN, OUTPUT);

  // (Optional) Initialize Serial communication for debugging
  Serial.begin(9600);
  Serial.println("Starting Blink Sketch...");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);   // Turn the LED on (HIGH is the voltage level)
  Serial.println("LED ON");
  delay(5000);                   // Wait for a second

  digitalWrite(LED_PIN, LOW);    // Turn the LED off by making the voltage LOW
  Serial.println("LED OFF");
  delay(5000);                   // Wait for a second
}
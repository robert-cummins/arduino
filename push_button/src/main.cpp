#include <Arduino.h>

const int BUTTON_PIN = 12;
int readValue = 0;
const int RED_LED = 8;  
int dt = 50;
int buttonState = 1;          // Current reading
int lastButtonState = 1;      // Previous reading
bool lightOn = false;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  Serial.begin(9600);
}


void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  // Check if button changed from HIGH to LOW (pressed)
  if (lastButtonState == 1 && buttonState == 0) {
    lightOn = !lightOn;  // Toggle light state
    Serial.print("Button pressed! Light is now ");
    Serial.println(lightOn ? "ON" : "OFF");
  }

  digitalWrite(RED_LED, lightOn ? HIGH : LOW);

   // Save the button state for next loop
  lastButtonState = buttonState;

  delay(dt); 

}
#include <Arduino.h>

int speedPin = 5;
int directionPin1 = 4;
int directionPin2 = 3;
int motorSpeed = 255;
int buttonPin = 2;
int buttonValue;
int previousButtonState = HIGH;
int buttonState = HIGH;
boolean motorOn = false;

void setup() {
  Serial.begin(9600);
  pinMode(speedPin, OUTPUT); 
  pinMode(directionPin1, OUTPUT); 
  pinMode(directionPin2, OUTPUT); 
  pinMode(buttonPin, INPUT_PULLUP);
}


/**
 * Continuously checks the state of a button to toggle the motor on and off.
 * - Reads the current button state.
 * - Sets the motor direction pins.
 * - Toggles the motor state when a button press is detected.
 * - Writes the motor speed based on the motor state.
 * - Updates the previous button state for the next loop iteration.
 * - Delays the loop to allow for button debouncing.
 */

void loop() {
  buttonState = digitalRead(buttonPin);
  digitalWrite(directionPin1, HIGH);
  digitalWrite(directionPin2, LOW);
  if (buttonState == LOW && previousButtonState == HIGH) {
    motorOn = !motorOn;
    if(motorOn) {
      analogWrite(speedPin, motorSpeed);
    } else {
      analogWrite(speedPin, 0);
    }
  }
  previousButtonState = buttonState;
  delay(10); 
}
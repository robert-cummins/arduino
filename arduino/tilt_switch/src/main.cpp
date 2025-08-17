#include <Arduino.h>

int tiltSwitchPin = 2;
int redLedPin = 9;
int greenLedPin = 10;

// Variable to store the current button state (HIGH or LOW)
int tiltSwitchValue;

void setup() {
  Serial.begin(9600);

  // Using the internal pull-up resistor
  // see no_resistor_push_button for more info
  pinMode(tiltSwitchPin, INPUT);
  digitalWrite(tiltSwitchPin, HIGH); 
  
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT); 
}

/**
 * Continuously reads the state of the tilt switch and updates the LEDs accordingly.
 * - If the tilt switch is pressed (LOW), the green LED is turned on and the red LED is turned off.
 * - If the tilt switch is not pressed (HIGH), the red LED is turned on and the green LED is turned off.
 * The button state is also printed to the Serial Monitor.
 * The loop runs every 500 milliseconds.
 */

void loop() {
  // Read the button state (LOW = pressed, HIGH = not pressed)
  tiltSwitchValue = digitalRead(tiltSwitchPin);
  
  // Print the value to the Serial Monitor (0 = pressed, 1 = not pressed)
  Serial.println(tiltSwitchValue);
  if(tiltSwitchValue == LOW){
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(redLedPin, LOW);
  } else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
  }

  delay(500);  // Wait 500ms before reading again
}

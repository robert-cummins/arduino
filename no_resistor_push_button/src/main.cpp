#include <Arduino.h>

// Pin connected to one side of the button.
// The other side of the button should be connected to GND.
int buttonPin = 2;

// Variable to store the current button state (HIGH or LOW)
int buttonValue;

void setup() {
  Serial.begin(9600);

  // Shortcut: pinMode(buttonPin, INPUT_PULLUP);  // Enables internal pull-up resistor in one line
  
  // Set the pin mode to INPUT so we can read the button
  pinMode(buttonPin, INPUT);
  
  // Enable the internal pull-up resistor on the button pin.
  // This causes the pin to read HIGH when the button is unpressed.
  // When the button is pressed, it connects to GND, and the pin reads LOW.
  digitalWrite(buttonPin, HIGH);  // or: pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the button state (LOW = pressed, HIGH = not pressed)
  buttonValue = digitalRead(buttonPin);
  
  // Print the value to the Serial Monitor (0 = pressed, 1 = not pressed)
  Serial.println(buttonValue);
  
  delay(100);  // Wait 100ms before reading again
}

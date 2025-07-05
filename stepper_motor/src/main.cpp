#include <Arduino.h>
#include <Stepper.h>

const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
int motSpeed = 10;

int buttonPin = 2;
int buttonValue;
boolean clockwise = true;
int previousButtonState = HIGH;
int buttonState = HIGH;

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(motSpeed);  
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  // Detect button press (transition from HIGH to LOW)
  if (buttonState == LOW && previousButtonState == HIGH) {
    clockwise = !clockwise;  // Toggle direction
    Serial.print("Direction changed to: ");
    Serial.println(clockwise ? "Clockwise" : "Counterclockwise");
  }
  previousButtonState = buttonState;

  // Step small increments continuously
  if (clockwise) {
    myStepper.step(10);
  } else {
    myStepper.step(-10);
  }

  delay(10); 
}
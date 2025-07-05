#include <Arduino.h>
#include <Servo.h>

int xPin = A0;
int yPin = A1;
int switchPin = 9;
int readPin = A1;
int servoPin = 11;

Servo myServo;

int xVal;
int yVal;
int sVal;



void setup() {
  Serial.begin(9600);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(switchPin, INPUT);
  myServo.attach(servoPin);
  
  // Enable Arduino's internal pull-up resistor on the switch pin.
  // This ensures the pin reads HIGH when the joystick button is NOT pressed,
  // because the button connects the pin to ground when pressed (active LOW).
  // If the joystick already has a hardware pull-up resistor, this line can be omitted.
  digitalWrite(switchPin, HIGH);
}

void loop() {
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  sVal = digitalRead(switchPin);
  // Only have one servo so only using xVal for control
  // With 2 I would have control of both axes
  int servoAngle = map(xVal, 0, 1023, 0, 175);
  myServo.write(servoAngle);
  Serial.print("X: ");
  Serial.print(xVal);
  Serial.print(" Y: ");
  Serial.print(yVal);
  Serial.print(" Switch: ");
  Serial.println(sVal);
  delay(100); 
}

#include <Arduino.h>
#include <Servo.h>

int servoPin = 9;
int resistorInput = 0;
int readPin = A1;
Servo myServo;
int lightValue = 0;


void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(resistorInput, INPUT);
}

  // Reads the light level from a light sensor connected to the analog input and
  // maps the value to a servo angle. The servo is then moved to the new angle.
  // The light level is printed to the serial console.
void loop() {
  lightValue = analogRead(readPin);
  Serial.print("Current light level: ");
  Serial.println(lightValue);
  int servoAngle = map(lightValue, 50, 700, 0, 170);
  myServo.write(servoAngle);
  // myServo.write(0);
  delay(100);
}

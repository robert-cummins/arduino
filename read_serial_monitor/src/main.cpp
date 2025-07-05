#include <Arduino.h>

int myNumber;
String msg = "Please enter a number: ";
String msg2 = "Your number is: ";
const int LED_PIN = 9;

void setup() {
 
  Serial.begin(9600);
}


void loop() {
  
  while(Serial.available() == 0) {

  }
  myNumber = Serial.parseInt();
  Serial.print(msg2);
  Serial.println(myNumber);
}
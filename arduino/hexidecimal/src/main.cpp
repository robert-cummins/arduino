#include <Arduino.h>

// start with a binary number
byte myByte = 0001;
void setup() {
  Serial.begin(9600);
}


  // increments myByte by one and prints its value in HEX, BIN, DEC, then waits 500ms
void loop() {
  myByte = myByte += 1;
  Serial.println(myByte, HEX);
  Serial.println(myByte, BIN);
  Serial.println(myByte, DEC);
  delay(500);
}


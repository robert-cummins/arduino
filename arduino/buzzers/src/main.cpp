#include <Arduino.h>

const int BUZZER_PIN = 10;
String input; 
int inputNumber;
int dt1 = 1;
int dt2 = 2;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  // BUZZ if selected number is over 10
  //////////////////////////////////
  // Serial.println("Enter a number:");
  // while (Serial.available() == 0) {
  //   // Wait for input from Serial monitor
  // }
  // input = Serial.readString();
  // inputNumber = input.toInt(); // Convert the input string to an integer
  // if(inputNumber > 10) {

  //   digitalWrite(BUZZER_PIN, HIGH);
  //   Serial.println("Buzzer ON");
  // } else {
  //   digitalWrite(BUZZER_PIN, LOW);
  //   Serial.println("Buzzer OFF");
  // }

  // Changing tone
  for(int i = 0; i < 100; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(dt1);
    digitalWrite(BUZZER_PIN, LOW);
    delay(dt1);
  }

  for(int i = 0; i < 100; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(dt2);
    digitalWrite(BUZZER_PIN, LOW);
    delay(dt2);
  }
}
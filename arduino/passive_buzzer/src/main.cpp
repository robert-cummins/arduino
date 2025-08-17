#include <Arduino.h>

const int BUZZER_PIN = 10;
String input; 
int inputNumber;
int buzzT1 = 1000;
int buzzT2 = 200;

const int READ_PIN = A1;
int readValue = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(READ_PIN, INPUT);
  Serial.begin(9600);
}


void loop() {
  readValue = analogRead(READ_PIN);
  int tone = map(readValue, 0, 1023, 80, 1200); // Map the analog read value to a frequency range
  // Serial.print("Tone: ");
  // Serial.println(tone);
  // Changing tone
  digitalWrite(BUZZER_PIN, HIGH);
  delayMicroseconds(tone);
  digitalWrite(BUZZER_PIN, LOW);
  delayMicroseconds(tone);
}

// #include <Arduino.h>

// const int BUZZER_PIN = 10;
// String input; 
// int inputNumber;
// int buzzT1 = 1000;
// int buzzT2 = 200;

// void setup() {
//   pinMode(BUZZER_PIN, OUTPUT);

//   Serial.begin(9600);
// }


// void loop() {

//   // Changing tone
//   digitalWrite(BUZZER_PIN, HIGH);
//   delayMicroseconds(buzzT1);
//   digitalWrite(BUZZER_PIN, LOW);
//   delayMicroseconds(buzzT1);
// }


#include <Arduino.h>

const int BUTTON_PIN_READ_1 = 12;
const int BUTTON_PIN_READ_2 = 8;
const int BUTTON_PIN_1 = 10;
const int BUTTON_PIN_2 = 11;
const int BUZZER_PIN = 7; 
const int RED_LED = 9;  

int readValueBt1 = 0;
int readValueBt2 = 0;
int brightness = 0;
int dt = 50;

void setup() {
  pinMode(RED_LED, OUTPUT);
  
  pinMode(BUTTON_PIN_1, OUTPUT);
  digitalWrite(BUTTON_PIN_1, HIGH);  // ← power the button from GPIO
  
  pinMode(BUTTON_PIN_2, OUTPUT);
  digitalWrite(BUTTON_PIN_2, HIGH);  // ← power the other button
  
  pinMode(BUTTON_PIN_READ_1, INPUT);
  pinMode(BUTTON_PIN_READ_2, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  readValueBt1 = digitalRead(BUTTON_PIN_READ_1);
  readValueBt2 = digitalRead(BUTTON_PIN_READ_2);

  // Print for debugging:
  Serial.print("Bt1: "); Serial.print(readValueBt1);
  Serial.print(", Bt2: "); Serial.println(readValueBt2);

  // Buzzer OFF by default
  digitalWrite(BUZZER_PIN, LOW);

  // Buzzer ON if **both buttons are pressed** (both LOW)
  if (readValueBt1 == LOW && readValueBt2 == LOW) {
    digitalWrite(BUZZER_PIN, HIGH);
  }

  // Increase brightness if button 1 pressed
  if (readValueBt1 == LOW && brightness < 255) {
    brightness += 2;
    delay(dt);
  }

  // Decrease brightness if button 2 pressed
  if (readValueBt2 == LOW && brightness > 0) {
    brightness -= 2;
    delay(dt);
  }

  // Buzzer ON if brightness max
  if (brightness >= 255) {
    digitalWrite(BUZZER_PIN, HIGH);
  }

  // Set LED brightness
  analogWrite(RED_LED, brightness);
}

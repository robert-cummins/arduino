#include <Arduino.h>
#include <DHT.h>

DHT dht(26, DHT11);

void setup() {
  dht.begin();
  delay(2000); // Wait for DHT sensor to stabilize
  Serial.begin(115200);
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  delay(5000);
}


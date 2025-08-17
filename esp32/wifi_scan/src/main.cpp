#include <Arduino.h>
#include "WiFi.h"

// Setup function runs once when the ESP32 boots
void setup() {
  Serial.begin(115200);                // Start serial communication at 115200 baud
  WiFi.mode(WIFI_STA);                 // Set WiFi to Station mode (ESP32 acts as a WiFi client, not an Access Point)
  WiFi.disconnect();                   // Ensure we are not connected to any network before scanning
  delay(100);                          // Small delay to let WiFi hardware settle
  Serial.println("Setup complete, WiFi is in station mode.");
}

// Main loop runs continuously after setup()
void loop() {
  Serial.println("Scanning for WiFi networks...");

  // Start scanning — returns the number of networks found
  int n = WiFi.scanNetworks();

  Serial.println("Scan complete.");

  if (n == 0) {
    // No networks found
    Serial.println("No networks found.");
  } else {
    // Print how many networks were found
    Serial.print(n);
    Serial.println(" networks found:");

    // Loop through each network and print details
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);                 // Network index (human-friendly, starts at 1)
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));          // SSID (network name)
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));          // Signal strength in dBm (closer to 0 = stronger signal)
      Serial.print(" (");
      
      // Show if the network is open or encrypted
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "open" : "encrypted");

      delay(10);                           // Short delay to keep serial output readable
    }
  }

  Serial.println("");                      // Print an empty line for spacing
  delay(5000);                             // Wait 5 seconds before scanning again
}
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>

const int LED_PIN = 4;
const char* SSID = "ESP32_LED_Control";
const char* PASSWORD = "sheeplee78";

WiFiServer server(80);

String htmlPage() {
  return R"rawliteral(
    <!DOCTYPE html>
    <html>
      <head>
        <title>ESP32 LED Control</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          body { font-family: Arial; text-align: center; margin: 20px; }
          button { 
            padding: 15px 30px; 
            font-size: 16px; 
            margin: 10px; 
            border: none; 
            border-radius: 5px; 
            cursor: pointer; 
          }
          .on-btn { background-color: #4CAF50; color: white; }
          .off-btn { background-color: #f44336; color: white; }
          .status { margin: 20px; font-size: 18px; }
        </style>
      </head>
      <body>
        <h1>ESP32 LED Control</h1>
        <div class="status" id="status">Ready</div>
        <button class="on-btn" onclick="sendCommand('/on')">Turn ON</button>
        <button class="off-btn" onclick="sendCommand('/off')">Turn OFF</button>
        
        <script>
          function sendCommand(path) {
            document.getElementById('status').innerText = 'Sending...';
            fetch(path)
              .then(response => {
                if (response.ok) {
                  document.getElementById('status').innerText = 'Command sent!';
                } else {
                  document.getElementById('status').innerText = 'Error sending command';
                }
              })
              .catch(error => {
                document.getElementById('status').innerText = 'Connection error';
              });
          }
        </script>
      </body>
    </html>
  )rawliteral";
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start with LED off
  
  Serial.begin(115200);
  delay(1000); // CRITICAL: Give serial time to initialize properly
  Serial.println("\nStarting ESP32 Access Point...");

  // IMPROVEMENT 1: Proper WiFi state reset
  // Your original code didn't fully clear previous WiFi state
  WiFi.mode(WIFI_OFF);  // Complete shutdown first
  delay(100);           // Let it settle
  WiFi.mode(WIFI_AP);   // Then start AP mode fresh
  
  // Configure the access point with explicit IP settings
  // Define the local IP address for the access point
  IPAddress local_IP(192, 168, 4, 1);  // IP address: 192.168.4.1
  // Define the gateway IP address for the access point
  IPAddress gateway(192, 168, 4, 1);  // Gateway IP address: 192.168.4.1
  // Define the subnet mask for the access point
  IPAddress subnet(255, 255, 255, 0); // Subnet mask: 255.255.255.0
  
  // IMPROVEMENT 2: Error checking on configuration
  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("AP Config Failed");
    return;
  }

  // IMPROVEMENT 3: Better AP parameters and error checking
  // Channel 6 instead of 1 (less interference), max 4 connections limit
  if (!WiFi.softAP(SSID, PASSWORD, 6, 0, 4)) {
    Serial.println("AP Start Failed");
    return;
  }

  Serial.println("Access Point Started");
  Serial.print("SSID: ");
  Serial.println(SSID);
  Serial.print("Password: ");
  Serial.println(PASSWORD);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  
  server.begin();
  Serial.println("HTTP Server Started");
/*************  ✨ Windsurf Command ⭐  *************/
/**
 * @brief The main loop of the program.
 * 
 * This function periodically checks the status of the access point and
 * handles incoming HTTP requests. It listens for new clients, processes
 * GET requests to turn the LED on or off, and sends an HTTP response with
 * the HTML page containing the button to control the LED.
 * 
 * @throws None
 */
/*******  f8bf98a1-4f9e-4a81-a4bd-43efd07af95d  *******/  Serial.println("Connect to the WiFi network and go to http://192.168.4.1");
}

void loop() {
  // IMPROVEMENT 4: Connection monitoring
  // This helps debug connection issues - shows how many devices are connected
  static unsigned long lastStatusCheck = 0;
  if (millis() - lastStatusCheck > 10000) { // Check every 10 seconds
    Serial.print("Connected stations: ");
    Serial.println(WiFi.softAPgetStationNum());
    lastStatusCheck = millis();
  }
  
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New client connected");
    Serial.print("Client IP: ");
    Serial.println(client.remoteIP()); // IMPROVEMENT 5: Shows which device connected
    
    // IMPROVEMENT 6: Request timeout protection
    // Your original code could hang forever waiting for complete requests
    unsigned long timeout = millis() + 3000; // 3 second timeout
    String currentLine = "";
    String request = "";
    bool headerComplete = false;
    
    // IMPROVEMENT 7: Proper HTTP parsing with timeout
    while (client.connected() && millis() < timeout) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n') {
          // CRITICAL FIX: Check for end of HTTP headers
          // HTTP headers end with blank line (\r\n\r\n)
          if (currentLine.length() == 0) {
            headerComplete = true;
            break; // Exit parsing loop when headers complete
          } 
          else {
            // Store the first line (contains GET request)
            if (request.length() == 0) {
              request = currentLine;
              Serial.print("Request: ");
              Serial.println(request); // IMPROVEMENT 8: Debug output
            }
            currentLine = "";
          }
        } 
        else if (c != '\r') {
          currentLine += c;
        }
      } else {
        // IMPROVEMENT 9: Prevent busy waiting
        delay(1); // Small delay if no data available
      }
    }
    
    // IMPROVEMENT 10: Only process if we got complete headers
    if (headerComplete) {
      // Process the request
      if (request.indexOf("GET /on") >= 0) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("LED turned ON");
      } 
      else if (request.indexOf("GET /off") >= 0) {
        digitalWrite(LED_PIN, LOW);
        Serial.println("LED turned OFF");
      }
      
      // IMPROVEMENT 11: Proper HTTP response format
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type: text/html");
      client.println("Connection: close"); // Tell browser to close connection
      client.println(); // Blank line ends headers
      
      // Send the HTML page
      String page = htmlPage();
      client.print(page);
      client.flush(); // IMPROVEMENT 12: Force data to be sent immediately
      
      Serial.println("Response sent");
    } else {
      Serial.println("Request timeout or incomplete");
    }
    
    // IMPROVEMENT 13: Give client time to receive data before closing
    delay(100);
    client.stop();
    Serial.println("Client disconnected\n");
  }
  
  // IMPROVEMENT 14: Prevent loop from running too fast
  delay(10);
}

/*
KEY DIFFERENCES FROM YOUR ORIGINAL CODE:

1. PROPER WIFI RESET: WiFi.mode(WIFI_OFF) before starting AP
2. ERROR CHECKING: Validates AP configuration and startup
3. BETTER CHANNEL: Uses channel 6 instead of 1 (less congested)
4. CONNECTION LIMITS: Max 4 connections prevents overload
5. REQUEST TIMEOUT: Won't hang on incomplete requests
6. COMPLETE HTTP PARSING: Waits for full headers before processing
7. PROPER RESPONSE FORMAT: Correct HTTP headers and connection handling
8. DEBUG OUTPUT: Shows client IP and request details
9. FORCED FLUSH: Ensures data is sent before closing connection
10. GRACEFUL TIMING: Delays prevent race conditions

WHY IT WORKS NOW:
- Your original broke on the first '\n' character, missing the rest of the HTTP request
- This version waits for the complete HTTP headers (blank line = end)
- Better timing and connection management prevents premature disconnects
- Timeout prevents hanging on bad connections
*/
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

// REPLACE THESE WITH YOUR HOME WIFI CREDENTIALS
const char* WIFI_SSID = "asus";        // Your home WiFi network name
const char* WIFI_PASSWORD = "sheeplee78"; // Your home WiFi password

const int LED_PIN = 4;

WiFiServer server(80);

String htmlPage() {
  // Get the ESP32's local IP address to display on the page
  String localIP = WiFi.localIP().toString();
  
  return R"rawliteral(
    <!DOCTYPE html>
    <html>
      <head>
        <title>ESP32 LED Control - WiFi Station Mode</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          body { 
            font-family: Arial; 
            text-align: center; 
            margin: 20px; 
            background-color: #f0f0f0;
          }
          .container {
            max-width: 500px;
            margin: 0 auto;
            background: white;
            padding: 30px;
            border-radius: 10px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.1);
          }
          button { 
            padding: 15px 30px; 
            font-size: 16px; 
            margin: 10px; 
            border: none; 
            border-radius: 5px; 
            cursor: pointer; 
            transition: background-color 0.3s;
          }
          .on-btn { 
            background-color: #4CAF50; 
            color: white; 
          }
          .on-btn:hover { 
            background-color: #45a049; 
          }
          .off-btn { 
            background-color: #f44336; 
            color: white; 
          }
          .off-btn:hover { 
            background-color: #da190b; 
          }
          .status { 
            margin: 20px; 
            font-size: 18px; 
            padding: 10px;
            border-radius: 5px;
            background-color: #e7e7e7;
          }
          .info {
            background-color: #d4edda;
            color: #155724;
            padding: 10px;
            border-radius: 5px;
            margin: 20px 0;
          }
        </style>
      </head>
      <body>
        <div class="container">
          <h1>ESP32 LED Control</h1>
          <div class="info">
            <strong>Device IP:</strong> )rawliteral" + localIP + R"rawliteral(<br>
            <strong>Status:</strong> Connected to your WiFi network
          </div>
          <div class="status" id="status">Ready</div>
          <button class="on-btn" onclick="sendCommand('/on')">Turn ON</button>
          <button class="off-btn" onclick="sendCommand('/off')">Turn OFF</button>
          <p><small>Access this page from any device on your network!</small></p>
        </div>
        
        <script>
          function sendCommand(path) {
            const statusDiv = document.getElementById('status');
            statusDiv.innerText = 'Sending command...';
            statusDiv.style.backgroundColor = '#fff3cd';
            
            fetch(path)
              .then(response => {
                if (response.ok) {
                  statusDiv.innerText = 'Command sent successfully!';
                  statusDiv.style.backgroundColor = '#d4edda';
                } else {
                  statusDiv.innerText = 'Error sending command';
                  statusDiv.style.backgroundColor = '#f8d7da';
                }
              })
              .catch(error => {
                statusDiv.innerText = 'Connection error - check your network';
                statusDiv.style.backgroundColor = '#f8d7da';
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
  delay(1000);
  Serial.println("\n=== ESP32 WiFi Station Mode ===");

  // Connect to your existing WiFi network (Station Mode)
  WiFi.mode(WIFI_STA); // Station mode - connects to existing WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  Serial.print("Connecting to WiFi network: ");
  Serial.println(WIFI_SSID);
  Serial.print("Connecting");
  
  // Wait for connection with timeout
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 20000) {
    delay(500);
    Serial.print(".");
  }
  
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✓ WiFi Connected Successfully!");
    Serial.println("=== Network Information ===");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    Serial.print("Local IP Address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Gateway IP: ");
    Serial.println(WiFi.gatewayIP());
    Serial.print("Subnet Mask: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("DNS Server: ");
    Serial.println(WiFi.dnsIP());
    Serial.print("Signal Strength (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    
    // Start the HTTP server
    server.begin();
    Serial.println("\n🌐 HTTP Server Started");
    Serial.println("===============================");
    Serial.print("🔗 Access the control panel at: http://");
    Serial.println(WiFi.localIP());
    Serial.println("===============================");
    Serial.println("You can now access this from:");
    Serial.println("- Your laptop browser");
    Serial.println("- Your phone browser");  
    Serial.println("- Any device on your WiFi network");
  } else {
    Serial.println("\n❌ Failed to connect to WiFi!");
    Serial.println("Check your WiFi credentials and try again.");
    Serial.println("Make sure WIFI_SSID and WIFI_PASSWORD are correct.");
    return; // Stop setup if WiFi connection failed
  }
}

void loop() {
  // Check WiFi connection status periodically
  static unsigned long lastWiFiCheck = 0;
  if (millis() - lastWiFiCheck > 30000) { // Check every 30 seconds
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("📶 WiFi Status: Connected | IP: ");
      Serial.print(WiFi.localIP());
      Serial.print(" | Signal: ");
      Serial.print(WiFi.RSSI());
      Serial.println(" dBm");
    } else {
      Serial.println("⚠️  WiFi Connection Lost! Attempting to reconnect...");
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
    lastWiFiCheck = millis();
  }
  
  // Handle incoming HTTP requests
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("\n👤 New client connected");
    Serial.print("Client IP: ");
    Serial.println(client.remoteIP());
    
    unsigned long timeout = millis() + 3000; // 3 second timeout
    String currentLine = "";
    String request = "";
    bool headerComplete = false;
    
    // Parse HTTP request with timeout protection
    while (client.connected() && millis() < timeout) {
      if (client.available()) {
        char c = client.read();
        
        if (c == '\n') {
          if (currentLine.length() == 0) {
            // Empty line means end of HTTP headers
            headerComplete = true;
            break;
          } 
          else {
            // Store the first line (contains GET request)
            if (request.length() == 0) {
              request = currentLine;
              Serial.print("📝 HTTP Request: ");
              Serial.println(request);
            }
            currentLine = "";
          }
        } 
        else if (c != '\r') {
          currentLine += c;
        }
      } else {
        delay(1); // Prevent busy waiting
      }
    }
    
    if (headerComplete) {
      // Process the LED control commands
      if (request.indexOf("GET /on") >= 0) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("💡 LED turned ON");
      } 
      else if (request.indexOf("GET /off") >= 0) {
        digitalWrite(LED_PIN, LOW);
        Serial.println("🌙 LED turned OFF");
      }
      else if (request.indexOf("GET / ") >= 0) {
        Serial.println("🏠 Serving main page");
      }
      
      // Send HTTP response
      client.println("HTTP/1.1 200 OK");
      client.println("Content-type: text/html; charset=UTF-8");
      client.println("Connection: close");
      client.println();
      
      // Send the HTML page
      String page = htmlPage();
      client.print(page);
      client.flush();
      
      Serial.println("✅ Response sent successfully");
    } else {
      Serial.println("⏱️  Request timeout or incomplete");
    }
    
    delay(100); // Give client time to receive data
    client.stop();
    Serial.println("👋 Client disconnected");
  }
  
  delay(10); // Prevent loop from running too fast
}

/*
🔄 CONVERSION NOTES - ACCESS POINT vs STATION MODE:

OLD (Access Point Mode):
- ESP32 creates its own WiFi network
- You connect your device TO the ESP32
- Only works within direct WiFi range
- IP address: 192.168.4.1 (fixed)

NEW (Station Mode):  
- ESP32 connects TO your existing WiFi
- All devices share the same network
- Works anywhere on your WiFi network
- IP address: Assigned by your router (dynamic)

🌟 BENEFITS OF STATION MODE:
1. ✅ No need to switch WiFi networks on your devices
2. ✅ Access from multiple devices simultaneously  
3. ✅ Works from anywhere in your house (WiFi range)
4. ✅ Can add internet connectivity later
5. ✅ More stable - uses your router's proven WiFi stack

📱 HOW TO USE:
1. Update WIFI_SSID and WIFI_PASSWORD with your credentials
2. Upload the code
3. Check Serial Monitor for the IP address (e.g., 192.168.1.145)
4. Open that IP in any browser on your network
5. Control the LED from any connected device!

🔧 TROUBLESHOOTING:
- If connection fails, double-check WiFi credentials
- Make sure you're on 2.4GHz network (ESP32 doesn't support 5GHz)
- Check Serial Monitor for the assigned IP address
- Try accessing from http://IP_ADDRESS (don't forget the http://)
*/
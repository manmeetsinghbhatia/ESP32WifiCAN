#include <WiFi.h>
#include <CAN.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// IP address and port number used by the CAN logger
const IPAddress serverIP(192, 168, 1, 10);
const int serverPort = 1234;

// CAN Tx and Rx pins, and baud rate
const int canTxPin = 16;
const int canRxPin = 17;
const int canBaudRate = 100E3;

WebServer server(80);

void setup() {
  // Start serial communication at 115200 baud
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print IP address of the ESP32
  Serial.print("Web server IP address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize CAN bus
  if (!CAN.begin(canTxPin, canRxPin, canBaudRate)) {
    Serial.println("Failed to start CAN");
    while (1);
  }

  // Set up web server routes
  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);
  
  // Start web server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  // Handle incoming web server requests
  server.handleClient();
}

// Handler function for the root route
void handleRoot() {
  // Build HTML form for submitting a CAN message
  String html = "<!DOCTYPE html><html><body>";
  html += "<h2>Enter a message to send as a CAN message</h2>";
  html += "<form action=\"/submit\" method=\"post\">";
  html += "<input type=\"text\" name=\"message\" maxlength=\"32\"><br><br>";
  html += "<input type=\"submit\" value=\"Submit\">";
  html += "</form></body></html>";
  
  // Send HTML form as response to client
  server.send(200, "text/html", html);
}

// Handler function for the submit route
void handleSubmit() {
  // Get message data from POST request
  String message = server.arg("message");
  
  // If message is not empty, send it as a CAN message
  if (message.length() > 0) {
    // Construct CAN message with ID 0x123
    const uint32_t canId = 0x123;
    uint8_t buf[8];
    int len = message.length();
    if (len > 8) {
      len = 8;
    }
    for (int i = 0; i < len; i++) {
      buf[i] = message[i];
    }
    CAN.beginPacket(canId);
    CAN.write(buf, len);
    CAN.endPacket();
    
    // Print message to serial console
    Serial.print("Sent CAN message: ");
    Serial.println(message);
  }
  
  // Send response to client
  server.send(200, "text/html", "<h2>Message sent!</h2>");
}

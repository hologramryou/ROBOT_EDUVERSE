#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Update these with values suitable for your network.
const char* ssid = "ESP12E_AP";
const char* password = "12345678";

// Create an instance of the WebServer (ESP8266)
ESP8266WebServer server(80);

// Function to handle POST requests
void handlePost() {
  String message = server.arg("plain");  // Get the message sent in the HTTP POST request

  // MotorController for ESP8266
  if (message == "W") {
    Serial.print("CHIMTAO");
    digitalWrite(D5, HIGH);
    delay(20);
    digitalWrite(D6, LOW);
    delay(20);
    digitalWrite(D3, HIGH);
    delay(20);
    digitalWrite(D4, LOW);
    delay(20);
  }

  if (message == "A") {
    Serial.print("DIT");
    digitalWrite(D5, LOW);
    delay(20);
    digitalWrite(D6, HIGH);
    delay(20);
    digitalWrite(D3, HIGH);
    delay(20);
    digitalWrite(D4, LOW);
    delay(20);
  }

  if (message == "S") {
    digitalWrite(D5, LOW);
    delay(20);
    digitalWrite(D6, HIGH);
    delay(20);
    digitalWrite(D3, LOW);
    delay(20);
    digitalWrite(D4, HIGH);
    delay(20);
  }

  if (message == "D") {
    Serial.print("DIT");
    digitalWrite(D5, HIGH);
    delay(20);
    digitalWrite(D6, LOW);
    delay(20);
    digitalWrite(D3, LOW);
    delay(20);
    digitalWrite(D4, HIGH);
    delay(20);
  }

  if (message == "F") {
    Serial.print("DIT");
    digitalWrite(D5, LOW);
    delay(20);
    digitalWrite(D6, LOW);
    delay(20);
    digitalWrite(D3, LOW);
    delay(20);
    digitalWrite(D4, LOW);
    delay(20);
  }

  // Send a response back to the client
  server.send(200, "text/plain", "Message received");
}

void setup_wifi() {
  delay(10);
  // Configure ESP8266 as an access point
  WiFi.softAP(ssid, password);
}

void setup() {
  // Set GPIO pins for ESP12E
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  
  // Start serial communication
  Serial.begin(115200);
  setup_wifi();
  
  // Define the HTTP POST handler
  server.on("/post", HTTP_POST, handlePost);

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();
}

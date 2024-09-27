#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Update these with values suitable for your network.
const char* ssid = "ESP086";
const char* password = "12345678";

// Create an instance of the ESP8266WebServer
ESP8266WebServer server(80);

void handlePost() {
  String message = server.arg("plain");  // Get the message sent in the HTTP POST request
  

//  // MotorController
//  if (message == "W") {
//    Serial.print("CHIMTAO");
//    digitalWrite(1, HIGH);
//    delay(20);
//    digitalWrite(2, HIGH);
//    delay(20);
//    digitalWrite(3, HIGH);
//    delay(20);
//  }
//  IF SHIT USING ONLYANTENNA
  if (message == "W") {
    Serial.print("CHIMTAO");
    digitalWrite(1, HIGH);
    delay(20);
    digitalWrite(0, LOW);
    delay(20);
    digitalWrite(3, HIGH);
    delay(20);
  }
  
  if (message == "A") {
    Serial.print("DIT");
    digitalWrite(1, HIGH);
    delay(20);
    digitalWrite(0, LOW);
    delay(20);
    digitalWrite(3, LOW);
    delay(20);
  }
  
  if (message == "S") {
    digitalWrite(1, LOW);
    delay(20);
    digitalWrite(0, HIGH);
    delay(20);
    digitalWrite(3, LOW);
    delay(20);
  }

  if (message == "D") {
    digitalWrite(1, LOW);
    delay(20);
    digitalWrite(0, LOW);
    delay(20);
    digitalWrite(3, HIGH);
    delay(20);
  }

  if (message == "F") {
    digitalWrite(1, LOW);
    delay(20);
    digitalWrite(0, LOW);
    delay(20);
    digitalWrite(3, LOW);
    delay(20);
  }

  // Send a response back to the client
  server.send(200, "text/plain", "Message received");
}

void setup_wifi() {
  delay(10);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

}

void setup() {
  // Set GPIO pins
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(3, OUTPUT);
  
  //Serial.begin(115200);
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

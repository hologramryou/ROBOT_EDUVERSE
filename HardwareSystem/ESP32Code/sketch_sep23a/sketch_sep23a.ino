#include <WiFi.h>
#include <WebServer.h>  // Use the WebServer library for ESP32

// Update these with values suitable for your network
const char* ssid = "ESP086";
const char* password = "12345678";

// Create an instance of the WebServer
WebServer server(80);

// Pin definitions for motor control
#define FL_MOTOR_PIN1 12  // Front Left Motor
#define FL_MOTOR_PIN2 14
#define FR_MOTOR_PIN1 27  // Front Right Motor
#define FR_MOTOR_PIN2 26
#define RL_MOTOR_PIN1 25  // Rear Left Motor
#define RL_MOTOR_PIN2 33
#define RR_MOTOR_PIN1 32  // Rear Right Motor
#define RR_MOTOR_PIN2 35

// Function to handle POST request
void handlePost() {
  String message = server.arg("plain");  // Get the message sent in the HTTP POST request

  Serial.print("Received Message: ");
  Serial.println(message);

  if (message == "W") {  // Forward
    Serial.println("Moving Forward");
    moveForward();
  } else if (message == "A") {  // Left
    Serial.println("Moving Left");
    strafeLeft();
  } else if (message == "S") {  // Backward
    Serial.println("Moving Backward");
    rotateClockwise();
  } else if (message == "D") {  // Right
    Serial.println("Moving Right");
    rotateCounterClockwise();
  }else if (message == "U") {  // Right
    Serial.println("Up");
    up();
  }else if (message == "I") {  // Right
    Serial.println("Down");
    down();
  } else if (message == "F") {  // Stop
    Serial.println("Stopping");
    stopAllMotors();
  }

  // Send a response back to the client
  server.send(200, "text/plain", "Message received");
}

// Setup Wi-Fi in Access Point mode
void setup_wifi() {
  delay(10);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("WiFi setup complete. AP Mode active.");
}
// Functions to control motor movement
void down() {
  digitalWrite(RL_MOTOR_PIN1, HIGH);
  digitalWrite(RL_MOTOR_PIN2, LOW);
  digitalWrite(RR_MOTOR_PIN1, HIGH);
  digitalWrite(RR_MOTOR_PIN2, LOW);
}
// Functions to control motor movement
void up() {
  digitalWrite(RL_MOTOR_PIN1, HIGH);
  digitalWrite(RL_MOTOR_PIN2, LOW);
  digitalWrite(RR_MOTOR_PIN1, HIGH);
  digitalWrite(RR_MOTOR_PIN2, LOW);
}

// Functions to control motor movement
void moveForward() {
  digitalWrite(FL_MOTOR_PIN1, HIGH);
  digitalWrite(FL_MOTOR_PIN2, LOW);
  digitalWrite(FR_MOTOR_PIN1, HIGH);
  digitalWrite(FR_MOTOR_PIN2, LOW);
}

void moveBackward() {
  digitalWrite(FL_MOTOR_PIN1, LOW);
  digitalWrite(FL_MOTOR_PIN2, HIGH);
  digitalWrite(FR_MOTOR_PIN1, LOW);
  digitalWrite(FR_MOTOR_PIN2, HIGH);
}

void strafeLeft() {
  digitalWrite(FL_MOTOR_PIN1, LOW);
  digitalWrite(FL_MOTOR_PIN2, HIGH);
  digitalWrite(FR_MOTOR_PIN1, HIGH);
  digitalWrite(FR_MOTOR_PIN2, LOW);
}

void strafeRight() {
  digitalWrite(FL_MOTOR_PIN1, HIGH);
  digitalWrite(FL_MOTOR_PIN2, LOW);
  digitalWrite(FR_MOTOR_PIN1, LOW);
  digitalWrite(FR_MOTOR_PIN2, HIGH);
}


void rotateClockwise() {
  digitalWrite(FL_MOTOR_PIN1, HIGH);
  digitalWrite(FL_MOTOR_PIN2, LOW);
  digitalWrite(FR_MOTOR_PIN1, LOW);
  digitalWrite(FR_MOTOR_PIN2, HIGH);
}

void rotateCounterClockwise() {
  digitalWrite(FL_MOTOR_PIN1, LOW);
  digitalWrite(FL_MOTOR_PIN2, HIGH);
  digitalWrite(FR_MOTOR_PIN1, HIGH);
  digitalWrite(FR_MOTOR_PIN2, LOW);
}

void stopAllMotors() {
  digitalWrite(FL_MOTOR_PIN1, LOW);
  digitalWrite(FL_MOTOR_PIN2, LOW);
  digitalWrite(FR_MOTOR_PIN1, LOW);
  digitalWrite(FR_MOTOR_PIN2, LOW);
  digitalWrite(RL_MOTOR_PIN1, LOW);
  digitalWrite(RL_MOTOR_PIN2, LOW);
  digitalWrite(RR_MOTOR_PIN1, LOW);
  digitalWrite(RR_MOTOR_PIN2, LOW);
}

// Setup function
void setup() {
  // Start Serial communication
  Serial.begin(115200);

  // Set GPIO pins as output for motor control
  pinMode(FL_MOTOR_PIN1, OUTPUT);
  pinMode(FL_MOTOR_PIN2, OUTPUT);
  pinMode(FR_MOTOR_PIN1, OUTPUT);
  pinMode(FR_MOTOR_PIN2, OUTPUT);
  pinMode(RL_MOTOR_PIN1, OUTPUT);
  pinMode(RL_MOTOR_PIN2, OUTPUT);
  pinMode(RR_MOTOR_PIN1, OUTPUT);
  pinMode(RR_MOTOR_PIN2, OUTPUT);

  // Initialize Wi-Fi
  setup_wifi();

  // Define the HTTP POST handler
  server.on("/post", HTTP_POST, handlePost);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

// Loop function
void loop() {
  // Handle client requests
  server.handleClient();
}

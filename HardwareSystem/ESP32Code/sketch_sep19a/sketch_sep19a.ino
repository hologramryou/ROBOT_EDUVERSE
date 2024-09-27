#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "ESP12E_AP";  // Replace with your network credentials
const char* password = "12345678";
const char* serverName = "http://192.168.4.1/post";  // Replace with the IP address of the server ESP8266

WiFiClient client;

// Define the pins for the rows
const int rowPins[6] = {4, 0, 2, 14, 12, 13};  // D2 to D8 on ESP12E

void setup() {
  Serial.begin(115200);  // Initialize serial communication at 115200 baud rate

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("Connected to Wi-Fi");


  // Set all row pins as INPUT with internal pull-ups
  for (int i = 0; i < 6; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);  // Use INPUT_PULLUP to enable internal pull-ups
  }
}

void loop() {
  String datasends = "F";  // Default data to send
  
  // Check the state of each button and determine the message to send
  if (digitalRead(rowPins[0]) == LOW) {
    datasends = "A";  // Button on GPIO0 is pressed
  } else if (digitalRead(rowPins[1]) == LOW) {
    datasends = "W";  // Button on GPIO1 is pressed
  } else if (digitalRead(rowPins[4]) == LOW) {
    datasends = "S";  // Button on GPIO2 is pressed
  } else if (digitalRead(rowPins[5]) == LOW) {
    datasends = "D";  // Button on GPIO3 is pressed
  }
  // Iterate through each pin and check its state
//  for (int i = 0; i < 6; i++) {
//    if (digitalRead(rowPins[i]) == 0) {  // Check if the pin is LOW (key pressed or active)
//      Serial.println(i);  // Print the value corresponding to the pin index (1 to 6)
//      delay(200);  // Debounce delay
//    }
//  }

  
  // Check Wi-Fi connection and send HTTP POST request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    http.begin(client, serverName);
    http.addHeader("Content-Type", "text/plain");
    
    int httpResponseCode = http.POST(datasends);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server response: " + response);
    } else {
      Serial.println("Error on sending POST: " + String(httpResponseCode));
    }
    
    http.end();
  } else {
    Serial.println("Wi-Fi Disconnected");
  }

  Serial.println(datasends);  // Print the data being sent to the serial monitor
  delay(10);  // Wait for 1 second before checking again
}

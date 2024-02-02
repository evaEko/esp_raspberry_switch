#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "config.h"

const int turnOnPin = 5; //D1

ESP8266WebServer server(80); // Server on port 80

bool raspberryIsRunning(){
  WiFiClient client;
  HTTPClient http;
  
  http.begin(client, raspberryPiAddress); // Specify the URL
  int httpCode = http.GET(); // Send the request
  http.end(); // Close connection
  return httpCode > 0;
}

void connectToWifi(){
  WiFi.begin(ssid, password); // Connect to the WiFi network

  while (WiFi.status() != WL_CONNECTED) { // Wait for connection
    delay(1000);
  }
 
}

void setup() {

  pinMode(turnOnPin, OUTPUT);
  digitalWrite(turnOnPin, LOW);

  connectToWifi();
 
  //WiFi.localIP()); // Print the local IP

  server.on("/", []() { // Define the handling of the root URL
    server.send(200, "text/plain", "Hello from ESP8266");
  });

  server.on("/turnon", []() {
    if (!raspberryIsRunning()){
        digitalWrite(turnOnPin, HIGH);
        delay(300);
        digitalWrite(turnOnPin, LOW);
        server.send(200, "text/plain", "Turning on... ");
    } else {
        server.send(200, "text/plain", "Already running.");
    }

  });

  server.begin();
}

void loop() {
  server.handleClient();
}

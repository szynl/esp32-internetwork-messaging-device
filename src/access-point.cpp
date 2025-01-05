#include <WiFi.h>
#include <WebServer.h>
#include <WiFiAP.h>

const char* ssid = "ESP32 Soft Access Point";
const char* password = "";

WebServer server(80); // create HTTP server object on port 80

void receiveMessage() {
  String body = server.arg("message"); // retrieve message body from POST request
  Serial.println(body);

  server.send(200, "text/plain", "Message received successfully."); // acknowledge message
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nCreating access point...");

  if (WiFi.softAP(ssid, password)) {
    Serial.println("Successfully created access point.");
  } else {
    Serial.println("Failed to create access point.");
    ESP.restart();
  }

  Serial.print("Your ESP32's IP address is: ");
  Serial.println(WiFi.softAPIP());

  server.on("/send", HTTP_POST, receiveMessage); // define /send route
  server.begin(); // start HTTP server
}

void loop() {
  server.handleClient(); // continuously listen for new HTTP requests from clients
}

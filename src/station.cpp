#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32 Soft Access Point";
const char* password = "";
const char* apIP = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Connecting to access point...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nSuccessfully connected to access point.");

}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http; // create HTTP client object

    String url = "http://" + String(apIP) + "/send";
    http.begin(url);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String message = "TEST MESSAGE";
    
    int responseCode = http.POST("message=" + message);

    if (responseCode > 0 && responseCode < 400) { // range including ESP error codes and HTTP client and server error codes
      Serial.println("Message sent successfully.");
      Serial.print("Response: ");
      Serial.println(http.getString());
    } else {
      Serial.print("Error sending message with response code: ");
      Serial.println(responseCode);
    }

    http.end();

  } else {
    Serial.println("Attemping to reconnect...");
    WiFi.begin(ssid, password);
  }

  delay(5000);

}

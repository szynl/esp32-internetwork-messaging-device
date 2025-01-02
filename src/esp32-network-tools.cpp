#include <WiFi.h>

const char* ssid = "";
const char* password = "";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nConnecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  long connectionStartTime = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - connectionStartTime < 300000) {
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nConnection timed out. Restarting...");
    ESP.restart();
  }

  long connectionDuration = millis() - connectionStartTime;

  Serial.printf("\nSuccessfully connected in %ld ms!\n", connectionDuration);

  Serial.print("Your ESP32's IP address is: ");
  Serial.println(WiFi.localIP());
}

void loop() {

}

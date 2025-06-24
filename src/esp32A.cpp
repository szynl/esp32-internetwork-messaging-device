#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "certsB.h"

namespace displayConfig {
    const int SCREEN_WIDTH = 128;
    const int SCREEN_HEIGHT = 64;
    const int RESET_PIN = -1;
    const uint8_t SCREEN_ADDRESS = 0x3C;
}

Adafruit_SSD1306 display(displayConfig::SCREEN_WIDTH, displayConfig::SCREEN_HEIGHT, &Wire, displayConfig::RESET_PIN);

const char* CLIENT_ID = "ESP32A";
WiFiClientSecure SECURE_CLIENT;
PubSubClient client(SECURE_CLIENT);

void displayMessage(String input, int duration) {
    display.setCursor(0, 0);
    display.println(input);
    display.display();
    delay(duration);
    display.clearDisplay();
}

void displayIncomingPayload(const byte* payload, unsigned int length, int duration) {
    display.setCursor(0, 0);

    for (unsigned int i = 0; i < length; i++) {
        display.print((char) payload[i]);
    }

    display.display();
    delay(duration);
    display.clearDisplay();
}

void establishWiFi(){
    WiFi.begin(SSID, PASSWORD);
    int retries = 0;

    while (WiFi.status() != WL_CONNECTED && retries < 10) {
        Serial.print(".");
        delay(1000);
        retries++;
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Failed to connect to WiFi.\n");
        while(1);
    }

    Serial.println("Successfully connected to WiFi.\n");
}

void establishMQTT() {
    int retries = 0;
    while (!client.connected() && retries < 10) {
        if (client.connect(CLIENT_ID)) {
            Serial.println("Successfully connected to MQTT broker.");
            client.subscribe(MQTT_TOPIC_SUB);
            break;
        } else {
            Serial.print("Failed: ");
            Serial.println(client.state());
            delay(1000);
            retries++;
        }
    }

    if (!client.connected()) {
        Serial.println("Failed to connect to MQTT broker after retries.");
        while (1);
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    String header = "Message received: ";
    displayMessage(header, 2500);
    displayIncomingPayload(payload, length, 5000);
}

void setup() {
    Serial.begin(115200);
    Wire.begin(27, 26);
    establishWiFi();

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("No I2C device detected.");
        while(1);
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    String header = "Initialising...";
    displayMessage(header, 2500);

    SECURE_CLIENT.setCACert(AWS_ROOT_CA);
    SECURE_CLIENT.setCertificate(DEVICE_CERT);
    SECURE_CLIENT.setPrivateKey(DEVICE_PRIVATE_KEY);

    client.setServer(AWS_ENDPOINT, PORT);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        establishMQTT();
    }

    client.loop();

    if (Serial.available()) {
        String message = Serial.readStringUntil('\n');
        message.trim();
        if (message.length() > 0) {
            client.publish(MQTT_TOPIC_PUB, message.c_str());
            String header = "Message sent: ";
            displayMessage(header, 2500);
            displayMessage(message, 5000);
        }
    }
}

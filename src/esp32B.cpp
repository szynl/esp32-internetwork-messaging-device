#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "certsA.h"

const char* CLIENT_ID = "ESP32B";
WiFiClientSecure SECURE_CLIENT;
PubSubClient client(SECURE_CLIENT);

void establishWiFi(){
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nSuccessfully connected to WiFi.\n");
}

void establishMQTT() {
    while (!client.connected()) {
        if (client.connect(CLIENT_ID)) {
            Serial.print("Successfully connected to MQTT broker.\n");
            client.subscribe(MQTT_TOPIC_SUB);
        } else {
            Serial.print("Failed: " + client.state());
        }
    }
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("\nMessage received: ");
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setup() {
    Serial.begin(115200);
    establishWiFi();

    SECURE_CLIENT.setCACert(AWS_ROOT_CA);
    SECURE_CLIENT.setCertificate(DEVICE_CERT);
    SECURE_CLIENT.setPrivateKey(DEVICE_PRIVATE_KEY);

    client.setServer(ENDPOINT, PORT);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        establishMQTT();
    }
    client.loop();
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();
        if (input.length() > 0) {
            client.publish(MQTT_TOPIC_PUB, input.c_str());
            Serial.print("\nMessage sent: ");
            Serial.println(input);
        }
    }
}

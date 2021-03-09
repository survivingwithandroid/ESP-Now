#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);

  // Get Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());

  // Initializing the ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>

typedef struct message {
   float temperature;
   float humidity;
};

struct message myMessage;

void onDataReceiver(const uint8_t * mac, const uint8_t *incomingData, int len) {
   Serial.println("Message received.");
   // We don't use mac to verify the sender
   // Let us transform the incomingData into our message structure
  memcpy(&myMessage, incomingData, sizeof(myMessage));
  Serial.println("=== Data ===");
  Serial.print("Mac address: ");
  for (int i = 0; i < 6; i++) {
      Serial.print("0x");
      Serial.print(mac[i], HEX);
      Serial.print(":");
  }
      
  Serial.print("\n\nTemperature: ");
  Serial.println(myMessage.temperature);
  Serial.print("\nHumidity: ");
  Serial.println(myMessage.humidity);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Get Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("ESP32 ESP-Now Broadcast");

  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  esp_now_register_recv_cb(onDataReceiver);
}

void loop() {
  // put your main code here, to run repeatedly:
}
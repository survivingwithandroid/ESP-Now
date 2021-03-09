#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Adafruit_NeoPixel.h>

#define NUM_OF_LEDS D6
#define PIN 12


typedef struct message {
   int red;
   int green;
   int blue;
} message;

uint8_t key[] =  {0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44, 0x33, 0x44};

message myMessage;

// Neopixel LEDs strip
Adafruit_NeoPixel pixels(NUM_OF_LEDS, PIN, NEO_GRB + NEO_KHZ800);


void onDataReceiver(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
   Serial.println("Message received.");
   // We don't use mac to verify the sender
   // Let us transform the incomingData into our message structure
  memcpy(&myMessage, incomingData, sizeof(myMessage));

 
  Serial.print("Red:");
  Serial.println(myMessage.red); 
  Serial.print("Green:");
  Serial.println(myMessage.green);
  Serial.print("Blue:");
  Serial.println(myMessage.blue);

  pixels.fill(pixels.Color(myMessage.red, myMessage.green, myMessage.blue));
  pixels.show();
}

void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  ESP.eraseConfig();
  // Initialize Neopixel
  pixels.begin();

  // Wifi STA Mode
  WiFi.mode(WIFI_STA);

  // Get Mac Add
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nESP-Now Receiver");
  
  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }
  
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  // We can register the receiver callback function
  esp_now_register_recv_cb(onDataReceiver);
}

void loop() {
  // put your main code here, to run repeatedly:
}
#include <SPI.h>
#include <LoRa.h>

// LoRa pins for TTGO T-Beam
#define SCLK 5
#define MISO 19
#define MOSI 27
#define CS 18
#define RST 23
#define DIO0 26
#define LED_PIN 22 // Pin for LED indicator

// Frequency band for LoRa communication
#define BAND 866E6

void setup() {
  Serial.begin(115200);

  // Setup LoRa transceiver module
  LoRa.setPins(CS, RST, DIO0);

  pinMode(LED_PIN, OUTPUT);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // Try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Received a packet
    Serial.print("Received packet: ");

    // Read packet
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    // Print RSSI of packet
    int rssi = LoRa.packetRssi();
    Serial.print(" with RSSI ");
    Serial.println(rssi);

    // Blink LED on pin 22 to indicate packet reception
    digitalWrite(LED_PIN, HIGH);
    delay(5000);
    digitalWrite(LED_PIN, LOW);

    delay(10000); // Adjust delay as needed
  }
}

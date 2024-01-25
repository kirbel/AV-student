#include <LoRa.h>
#include <SPI.h>

#define MOSI 27
#define SCLK 5
#define CS 18
#define DIO 26
#define RST 23
#define MISO 19

#define BAND 866E6

int counter = 0;

void setup() {
  Serial.begin(115200);

  // SPI LoRa pins
  SPI.begin(SCLK, MISO, MOSI, CS);

  // Setup LoRa transceiver module
  LoRa.setPins(CS, RST, DIO);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(10000);
}
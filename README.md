# AV-student
Дві плати TBeamV1.1 виступають у ролі відправника і приймача(відповідно дві програми). Для перердачі сигналів використовіують технологію LoRa32. Коли приймач отримує сигнал, загараються світодіот
![image](https://github.com/kirbel/AV-student/assets/60318229/eb4dc994-3b6b-46f1-8d84-9ae785167f34)
# Корисні посилання

Посилання на протокод з поясненням - https://randomnerdtutorials.com/ttgo-lora32-sx1276-arduino-ide/

# Код передавача (Sender):
      #include <SPI.h>
      #include <LoRa.h>
      
      // Оголошення пінів для TTGO T-Beam
      #define SCLK 5      // Пін SCLK для SPI
      #define MISO 19     // Пін MISO для SPI
      #define MOSI 27     // Пін MOSI для SPI
      #define CS 18       // Пін CS для LoRa
      #define RST 14      // Пін RST для LoRa
      #define DIO0 26     // Пін DIO0 для LoRa
      #define LED_PIN 22  // Пін для світлодіода індикатора
      
      // Частотний діапазон для LoRa
      #define BAND 866E6
      
      void setup() {
        Serial.begin(115200);
      
        // Налаштування пінів для SPI і LoRa
        SPI.begin(SCLK, MISO, MOSI, CS);
      
        // Налаштування модуля LoRa
        LoRa.setPins(CS, RST, DIO0);
      
        if (!LoRa.begin(BAND)) {
          Serial.println("Starting LoRa failed!");
          while (1);
        }
      
        Serial.println("LoRa Initializing OK!");
      }
      
      void loop() {
        Serial.print("Sending packet: ");
        Serial.println(counter);
      
        // Відправка пакету LoRa до приймача
        LoRa.beginPacket();
        LoRa.print("hello ");
        LoRa.print(counter);
        LoRa.endPacket();
      
        counter++;
      
        delay(10000);
      }
  # Опис коду:
1. Включаємо необхідні бібліотеки SPI та LoRa.
2. Визначаємо піни для з'єднання з модулем LoRa на TTGO T-Beam.
3. Встановлюємо частотний діапазон BAND для LoRa.
4. У функції setup налаштовуємо Serial та SPI, ініціалізуємо модуль LoRa.
5. У функції loop відправляємо пакет LoRa із рядком "hello" та лічильником.
 #  Код приймача (Receiver):
      #include <SPI.h>
      #include <LoRa.h>
      
      // Оголошення пінів для TTGO T-Beam
      #define SCLK 5      // Пін SCLK для SPI
      #define MISO 19     // Пін MISO для SPI
      #define MOSI 27     // Пін MOSI для SPI
      #define CS 18       // Пін CS для LoRa
      #define RST 23      // Пін RST для LoRa
      #define DIO0 26     // Пін DIO0 для LoRa
      #define LED_PIN 22  // Пін для світлодіода індикатора
      
      // Частотний діапазон для LoRa
      #define BAND 866E6
      
      void setup() {
        Serial.begin(115200);
      
        // Налаштування пінів для SPI і LoRa
        SPI.begin(SCLK, MISO, MOSI, CS);
      
        // Налаштування модуля LoRa
        LoRa.setPins(CS, RST, DIO0);
      
        pinMode(LED_PIN, OUTPUT);
      
        if (!LoRa.begin(BAND)) {
          Serial.println("Starting LoRa failed!");
          while (1);
        }
      
        Serial.println("LoRa Initializing OK!");
      }
      
      void loop() {
        // Спроба розібрати пакет
        int packetSize = LoRa.parsePacket();
        if (packetSize) {
          // Отримано пакет
          Serial.print("Received packet: ");
      
          // Зчитування пакету
          while (LoRa.available()) {
            String LoRaData = LoRa.readString();
            Serial.print(LoRaData);
          }
      
          // Вивід RSSI пакету
          int rssi = LoRa.packetRssi();
          Serial.print(" with RSSI ");
          Serial.println(rssi);
      
          // Мигання світлодіода на піні 22 для індикації отриманого пакету
          digitalWrite(LED_PIN, HIGH);
          delay(500);
          digitalWrite(LED_PIN, LOW);
      
          delay(10000); // Затримка, може бути змінена за необхідності
        }
      }
      # Опис коду:
1. Знову включаємо бібліотеки SPI та LoRa.
2. Визначаємо піни для з'єднання з модулем LoRa на TTGO T-Beam.
3. Встановлюємо частотний діапазон BAND для LoRa.
4. У функції setup налаштовуємо Serial та SPI, ініціалізуємо модуль LoRa та встановлюємо пін для світлодіода.
5. У функції loop спроба розібрати пакет, якщо він отриманий. Якщо пакет отримано, виводимо його вміст та RSSI, а також мигаємо світлодіодом на піні 22 для індикації отримання пакету.
   
          
   

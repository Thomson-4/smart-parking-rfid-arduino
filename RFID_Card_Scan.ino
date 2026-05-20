#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

byte readCard[4];

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(9600);
  while (!Serial);  // Wait for serial to initialize (only needed for some boards)
  SPI.begin();       // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522
  delay(4);          // Let the reader settle
  mfrc522.PCD_DumpVersionToSerial(); // Print firmware version
  Serial.println("Place your RFID card near the reader...");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println("Scanned RFID UID:");
  for (uint8_t i = 0; i < mfrc522.uid.size; i++) {
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // Halt PICC communication
  mfrc522.PICC_HaltA();
}

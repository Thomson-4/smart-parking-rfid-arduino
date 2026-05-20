#include <Wire.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define servoPin 2

String UID = "57 05 8C 02"; // Replace with your card UID

MFRC522 rfid(SS_PIN, RST_PIN);
Servo myservo;

int IR1 = 4; // Entry sensor
int IR2 = 3; // Exit sensor

int Slot = 4; // Total number of parking slots
const int MaxSlots = 4;

bool carEntering = false;
bool carExiting = false;

void setup() {
  Serial.begin(9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  myservo.attach(servoPin);
  myservo.write(100); // Close gate initially

  Serial.println("=== SMART PARKING SYSTEM ===");
  delay(3000);

  SPI.begin();
  rfid.PCD_Init();
  Serial.println("System ready. Waiting for cars...");
}

void loop() {
  // Check if a car is entering (IR1 -> IR2)
  if (digitalRead(IR1) == LOW && !carEntering && !carExiting) {
    carEntering = true;
    Serial.println("\nCar Detected at Entry!");

    if (Slot > 0) {
      int pass = rfunc(); // RFID check
      if (pass == 1) {
        smoothOpenGate();
        Slot--;
        Serial.println("Gate Opened! Waiting for car to enter...");

        // Wait for car to cross IR2
        while (digitalRead(IR2) == HIGH) delay(100);
        while (digitalRead(IR2) == LOW) delay(100);

        delay(2000);
        smoothCloseGate();
        Serial.println("Gate Closed after Entry.");
      }
    } else {
      Serial.println("SORRY: Parking Full");
    }
    carEntering = false;
  }

  // Check if a car is exiting (IR2 -> IR1)
  if (digitalRead(IR2) == LOW && !carExiting && !carEntering) {
    if (Slot == MaxSlots) {
      Serial.println("No Cars Left!");
    } else {
      carExiting = true;
      smoothOpenGate();

      if (Slot < MaxSlots) {
        Slot++;
      }

      Serial.println("Car Exiting...");

      // Wait for car to cross IR1
      while (digitalRead(IR1) == HIGH) delay(100);
      while (digitalRead(IR1) == LOW) delay(100);

      delay(2000);
      smoothCloseGate();
      Serial.println("Gate Closed after Exit.");
      carExiting = false;
    }
  }

  // Display available slots every loop
  Serial.print("Available Slots: ");
  Serial.println(Slot);
  delay(1000);
}

// Function to smoothly open the gate
void smoothOpenGate() {
  for (int pos = 100; pos >= 0; pos--) {
    myservo.write(pos);
    delay(10);
  }
}

// Function to smoothly close the gate
void smoothCloseGate() {
  for (int pos = 0; pos <= 100; pos++) {
    myservo.write(pos);
    delay(10);
  }
}

// RFID check function
int rfunc() {
  Serial.println("Please Scan Your Card...");

  while (true) {
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      break;
    }
    delay(300);
  }

  Serial.print("Scanning");
  String ID = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(".");
    ID.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    ID.concat(String(rfid.uid.uidByte[i], HEX));
    delay(300);
  }

  ID.toUpperCase();
  Serial.println();
  Serial.print("Card UID: ");
  Serial.println(ID.substring(1));

  if (ID.substring(1) == UID) {
    Serial.println("Access Granted.");
    return 1;
  } else {
    Serial.println("Access Denied. Wrong card.");
    return 0;
  }
}

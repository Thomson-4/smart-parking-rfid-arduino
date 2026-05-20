# Smart Parking System using RFID and Arduino

An Arduino-based **Smart Parking System** that uses RFID card authentication to control a servo motor gate, with IR sensors to detect car entry/exit and track available parking slots in real time.

---

## How It Works

1. A car arrives at the entry — IR sensor (IR1) detects it
2. The system prompts the driver to **scan their RFID card**
3. If the card UID matches → gate opens (servo motor rotates)
4. Car crosses IR sensor (IR2) → gate closes automatically
5. Available slot count decrements
6. On exit, IR2 detects the car → gate opens → car leaves → slot count increments

---

## Components Required

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Uno | 1 | Microcontroller — runs the main logic |
| MFRC522 RFID Reader | 1 | Reads RFID card UID for authentication |
| RFID Card / Key Fob | 1+ | Card used for access — one UID is whitelisted |
| SG90 Servo Motor | 1 | Acts as the parking gate (opens/closes) |
| IR Sensor Module | 2 | IR1: detects car at entry, IR2: detects car at exit |
| Jumper Wires | Several | Connections between components |
| Breadboard | 1 | For prototyping connections |
| USB Cable (Type-B) | 1 | To upload code and power the Arduino |

---

## Pin Connections

### MFRC522 RFID Reader → Arduino Uno

| RFID Pin | Arduino Pin |
|----------|-------------|
| SDA (SS) | 10 |
| SCK | 13 |
| MOSI | 11 |
| MISO | 12 |
| RST | 9 |
| GND | GND |
| 3.3V | 3.3V |

### Other Components

| Component | Arduino Pin |
|-----------|-------------|
| Servo Motor (Signal) | 2 |
| IR Sensor 1 — Entry | 4 |
| IR Sensor 2 — Exit | 3 |

---

## Libraries Required

Install these from the **Arduino IDE Library Manager** (`Sketch → Include Library → Manage Libraries`):

| Library | How to Install |
|---------|---------------|
| `MFRC522` | Search "MFRC522" by GithubCommunity → Install |
| `Servo` | Built-in — no installation needed |
| `SPI` | Built-in — no installation needed |
| `Wire` | Built-in — no installation needed |

---

## Files

| File | Description |
|------|-------------|
| `RFID_Card_Scan.ino` | Run this **first** to scan your card and get its UID |
| `RFID_Main_Code.ino` | Main parking system — uses the UID from the scan |

---

## Steps to Run

### Step 1 — Get your RFID Card UID

1. Open **Arduino IDE**
2. Open `RFID_Card_Scan.ino`
3. Connect your Arduino via USB
4. Select **Tools → Board → Arduino Uno**
5. Select the correct **Port** under `Tools → Port`
6. Click **Upload** (→)
7. Open **Serial Monitor** (`Tools → Serial Monitor`) — set baud rate to `9600`
8. Place your RFID card near the reader
9. **Copy the UID** printed in the Serial Monitor (e.g. `57 05 8C 02`)

---

### Step 2 — Set your UID in the Main Code

1. Open `RFID_Main_Code.ino`
2. On **line 10**, replace the UID with your card's UID:
   ```cpp
   String UID = "57 05 8C 02"; // Replace with your card UID
   ```

---

### Step 3 — Upload & Run the Main System

1. Open `RFID_Main_Code.ino` in Arduino IDE
2. Click **Upload** (→)
3. Open **Serial Monitor** at baud rate `9600`
4. The system prints:
   ```
   === SMART PARKING SYSTEM ===
   System ready. Waiting for cars...
   ```
5. Trigger IR1 to simulate a car arriving → scan your RFID card → gate opens
6. Trigger IR2 to simulate the car passing → gate closes
7. Monitor available slots in real time on the Serial Monitor

---

## Configuration

| Variable | Default | Description |
|----------|---------|-------------|
| `Slot` | `4` | Total available parking slots |
| `MaxSlots` | `4` | Maximum capacity |
| `UID` | `"57 05 8C 02"` | Whitelisted RFID card UID |
| `servoPin` | `2` | Servo motor signal pin |
| `IR1` | `4` | Entry IR sensor pin |
| `IR2` | `3` | Exit IR sensor pin |

---

## Academic Details

- **Institution:** REVA University, Bengaluru
- **Course:** Computer Organization and Architecture (COA)
- **Academic Year:** 2024–25
- **Semester:** 4th

---

## Author

**Thomson Sunny**  
GitHub: [@Thomson-4](https://github.com/Thomson-4)

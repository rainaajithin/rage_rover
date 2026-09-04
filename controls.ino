#include <Arduino.h>
#include <Wire.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Hardware Pinout
const int PIN_VRX = D0;      // D1 / GPIO 2 (Steering)
const int PIN_VRY = D1;      // D2 / GPIO 3 (Throttle)
const int MPU_ADDR = 0x68;

// BLE Variables
static BLEAdvertisedDevice* targetServer = nullptr;
static BLERemoteCharacteristic* pRemoteChar = nullptr;
static bool doConnect = false;
static bool connected = false;

// Shake Detection Tuning
unsigned long lastShakeTime = 0;
const unsigned long SHAKE_GRACE_MS = 350; 
char lastSentCommand = ' ';
unsigned long lastSendTime = 0;

class AdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.haveServiceUUID() && 
        advertisedDevice.isAdvertisingService(BLEUUID(SERVICE_UUID))) {
      BLEDevice::getScan()->stop();
      targetServer = new BLEAdvertisedDevice(advertisedDevice);
      doConnect = true;
    }
  }
};

bool connectToServer() {
  BLEClient* pClient = BLEDevice::createClient();
  if (!pClient->connect(targetServer)) return false;

  BLERemoteService* pRemoteService = pClient->getService(SERVICE_UUID);
  if (pRemoteService == nullptr) {
    pClient->disconnect();
    return false;
  }

  pRemoteChar = pRemoteService->getCharacteristic(CHARACTERISTIC_UUID);
  if (pRemoteChar == nullptr) {
    pClient->disconnect();
    return false;
  }

  connected = true;
  Serial.println(">>> Controller Connected to Car! <<<");
  return true;
}

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000);

  analogReadResolution(12); // 0 - 4095
  Wire.begin(D4, D5);       // SDA = D4, SCL = D5

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  BLEDevice::init("Standard_Controller");
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
  pBLEScan->setInterval(1349);
  pBLEScan->setWindow(449);
  pBLEScan->setActiveScan(true);
  pBLEScan->start(5, false);

  Serial.println("Searching for Car...");
}

void loop() {
  if (doConnect) {
    connectToServer();
    doConnect = false;
  }

  if (!connected) {
    BLEDevice::getScan()->start(2, false);
    delay(500);
    return;
  }

  // 1. Read MPU6050 Acceleration
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);

  float totalG = 1.0;
  if (Wire.available() >= 6) {
    int16_t rawAX = (Wire.read() << 8) | Wire.read();
    int16_t rawAY = (Wire.read() << 8) | Wire.read();
    int16_t rawAZ = (Wire.read() << 8) | Wire.read();

    float gx = rawAX / 16384.0;
    float gy = rawAY / 16384.0;
    float gz = rawAZ / 16384.0;
    totalG = sqrt(gx * gx + gy * gy + gz * gz);
  }

  // Update shake timestamp when acceleration exceeds bounds
  if (totalG > 1.7 || totalG < 0.4) {
    lastShakeTime = millis();
  }
  bool isAgitated = (millis() - lastShakeTime < SHAKE_GRACE_MS);

  // 2. Read Joystick
  int rawX = analogRead(PIN_VRX);
  int rawY = analogRead(PIN_VRY);
  int byteX = map(rawX, 0, 4095, 255, 0); 
  int byteY = map(rawY, 0, 4095, 255, 0); 

  // Determine if stick is physically tilted out of resting deadband (center is ~127)
  char stickIntent = 'x'; 
if (byteY > 175) {
    stickIntent = 's'; // Pushing stick UP now sends REVERSE ('s')
  } else if (byteY < 80) {
    stickIntent = 'w'; // Pulling stick DOWN now sends FORWARD ('w')
  } else if (byteX > 175) {
    stickIntent = 'a'; // Pushing stick RIGHT now sends LEFT ('a')
  } else if (byteX < 80) {
    stickIntent = 'd'; // Pushing stick LEFT now sends RIGHT ('d')
  }

  // 3. AND LOGIC: Both conditions MUST be satisfied to move
  char cmd = 'x'; // Default to stop

  if (isAgitated && (stickIntent != 'x')) {
    cmd = stickIntent; // Drive with joystick intent only while shaking
  } else {
    cmd = 'x';         // Stop if either condition fails
  }

  // 4. Send command via BLE on change OR pulse every 120ms
  if (cmd != lastSentCommand || (cmd != 'x' && millis() - lastSendTime > 120)) {
    if (pRemoteChar != nullptr && pRemoteChar->canWrite()) {
      pRemoteChar->writeValue((uint8_t*)&cmd, 1);
      lastSentCommand = cmd;
      lastSendTime = millis();
      Serial.printf("Cmd: [%c] | Shaking: %s | Stick: %c | |a|: %4.2fg\n", 
                    cmd, isAgitated ? "YES" : "NO", stickIntent, totalG);
    }
  }

  delay(20);
}
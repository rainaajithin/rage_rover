#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// L298N Direction Pins
const int IN1 = D0; // Left Motor Fwd
const int IN2 = D1; // Left Motor Rev
const int IN3 = D2; // Right Motor Fwd
const int IN4 = D3; // Right Motor Rev

// Watchdog auto-stop pulse timer
unsigned long actionStartTime = 0;
unsigned long actionDuration = 250; // Auto-stop window (ms)
bool isMoving = false;

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  isMoving = false;
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  isMoving = true;
}

void reverse() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  isMoving = true;
}

void turnLeft() {
  digitalWrite(IN1, LOW);  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
  isMoving = true;
}

void turnRight() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  digitalWrite(IN4, HIGH);
  isMoving = true;
}

class CommandCallbacks: public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic *pCharacteristic) {
    std::string rxValue = pCharacteristic->getValue();

    if (rxValue.length() > 0) {
      char cmd = tolower(rxValue[0]);
      actionStartTime = millis();

      switch (cmd) {
        case 'w':
          forward();
          break;

        case 's':
          reverse();
          break;

        case 'a':
          turnLeft(); // Normal Left
          break;

        case 'd':
          turnRight(); // Normal Right
          break;

        case 'x':
        default:
          stopCar();
          break;
      }
    }
  }
};

class ServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("\n>>> Remote Connected! Ready to drive. <<<");
  }
  void onDisconnect(BLEServer* pServer) {
    stopCar();
    Serial.println("\n>>> Remote Disconnected! Car Safe-Stopped. <<<");
    pServer->getAdvertising()->start();
  }
};

void setup() {
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  stopCar();

  BLEDevice::init("XIAO_WASD_Car");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
  );

  pCharacteristic->setCallbacks(new CommandCallbacks());
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();

  Serial.println("Car ready! Waiting for remote...");
}

void loop() {
  // Auto-stop failsafe: stops motors if commands stop arriving
  if (isMoving && (millis() - actionStartTime >= actionDuration)) {
    stopCar();
  }
  delay(10);
}
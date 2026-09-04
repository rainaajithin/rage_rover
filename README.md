
<p align="center">
  <img width="1280" height="640" alt="Rage Rover banner" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />
</p>

<h1 align="center">Rage Rover</h1>
<p align="center"><em>How mad can one joystick make you?</em></p>

---

## Basic Details

**Team Name:** DRACULA

**Team Members**
| Role | Name | Institution |
|---|---|---|
| Member 1 | Rainaa Anna Jithin | Model Engineering College |
| Member 2 | Irene Sara Sam | Model Engineering College |

---


## Project Description

RAGE ROVER is a 2-wheeled robotic car driven by an intentionally frustrating remote controller. To steer, users must physically violently shake and tilt the handheld controller past extreme motion thresholds, while navigating inverted joystick inputs where forward moves backward and left turns right.

---

## The Problem (That Doesn't Exist)

Driving a traditional RC car is dangerously easy and emotionally empty. You push a joystick forward, the car goes forward, and nobody learns anything about suffering. Modern controls coddle drivers with "intuitive handling," completely depriving humanity of physical exertion, wrist workouts, and healthy, rage-induced sweat. In short: RC cars lack friction, struggle, and chaotic rage. We are fixing a non-existent crisis by making simple driving violently exhausting.

## The Solution (That Nobody Asked For)

Rage Rover is an RC car engineered to transform basic steering into a full-body emotional breakdown. To even unlock motor controls, drivers must physically shake and tilt the controller past aggressive MPU6050 motion thresholds, effectively turning driving into a high-stress cardio session. To make matters worse, the joystick controls are completely inverted: forward drives backward, and right turns left. It is useless, deeply counter-intuitive, and guaranteed to ruin friendships within seconds.

---

## Technical Details

### Components Used

**Software**
- **Languages:** C/C++ (Arduino framework)
- **Frameworks:** ESP32 Arduino Core
- **Libraries:** BLEDevice (ESP32 BLE Arduino core), Wire.h
- **Tools:** Arduino IDE 2.x

**Hardware**
- 2× Seeed Studio XIAO ESP32-S3 (one for the handheld remote controller, one for the car's receiver and motor controller)
- 1× MPU6050 6-axis I2C accelerometer/gyroscope module
- 1× 2-axis thumb joystick module
- 1× L298N dual H-bridge motor driver
- 2× N20 motors
- 2× 3.7V battery packs

---

## Implementation

### Setup Instructions
1. Connect the remote controller's XIAO ESP32-S3 to a PC and flash the remote transmitter sketch.
2. Connect the car's XIAO ESP32-S3 to a PC and flash the car receiver/motor controller sketch.
3. Power on the car chassis via the onboard battery pack.
4. Power on the remote controller — the BLE connection will establish automatically.
5. Shake the remote controller to satisfy the kinetic motion threshold, then use the joystick (inverted) to steer.

---

## Project Documentation

### Hardware

<p align="center">
  <img width="1536" height="1024" alt="Hardware overview" src="https://github.com/user-attachments/assets/9210cfdf-643c-4296-bd3f-4c902c6d2672" />
</p>

### Schematic & Circuit

<p align="center">
  <img width="1536" height="1024" alt="Circuit diagram" src="https://github.com/user-attachments/assets/eb35deef-aa0a-4ed5-9635-31c6ac49ae73" />
</p>

### Photos

<p align="center">
  <img width="574" height="671" alt="Rage Rover assembled" src="https://github.com/user-attachments/assets/4b4d3b0d-85fa-4d61-adb4-b1713040a79a" />
</p>

### Demo Video

https://drive.google.com/file/d/1_-RelJPF6Bjjy1MpsJ0dUHFtS6635tTT/view?usp=drive_link

---

## Team Contributions

- **Rainaa Anna Jithin** — Designed the overall system architecture; implemented the BLE GATT client/server communication.
- **Irene Sara Sam** — Developed the remote controller firmware, including joystick analog input processing and MPU6050 kinetic shake detection.

---

<p align="center">Made with ❤️ at TinkerHub Useless Projects</p>

<p align="center">
  <img src="https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F" alt="TinkerHub badge" />
  <img src="https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0" alt="Useless Projects badge" />
</p>

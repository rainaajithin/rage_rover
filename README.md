<img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/3beec071-b7e2-4163-aa66-a8370054c871" /><img width="1600" height="900" alt="image" src="https://github.com/user-attachments/assets/05234aeb-1dd2-4e84-ac59-abf98f2f3668" /><img width="1280" height="640" alt="git (1)" src="https://github.com/user-attachments/assets/8920b256-2ba8-4988-b824-5351134eb4bd" />



# Rage Rover



## Basic Details
### Team Name: DRACULA


### Team Members
- Team Lead: RAINAA ANNA JITHIN - MODEL ENGINEERING COLLEGE
- Member 2:IRENE SARA SAM - MODEL ENGINEERING COLLEGE


### Project Description
RAGE ROVER is a 2-wheeled robotic car driven by an intentionally frustrating remote controller. To steer, users must physically violently shake and tilt the handheld controller past extreme motion thresholds, while navigating inverted joystick inputs where forward moves backward and left turns right.


### The Problem (that doesn't exist)
Driving a traditional RC car is dangerously easy and emotionally empty. You push a joystick forward, the car goes forward, and nobody learns anything about suffering. Modern controls coddle drivers with "intuitive handling," completely depriving humanity of physical exertion, wrist workouts, and healthy, rage-induced sweat. In short: RC cars lack friction, struggle, and chaotic rage. We are fixing a non-existent crisis by making simple driving violently exhausting.

### The Solution (that nobody asked for)
Rage Rover is an RC car engineered to transform basic steering into a full-body emotional breakdown. To even unlock motor controls, drivers must physically shake and tilt the controller past aggressive MPU6050 motion thresholds, effectively turning driving into a high-stress cardio session. To make matters worse, the joystick controls are completely inverted: forward drives backward, and right turns left. It is useless, deeply counter-intuitive, and guaranteed to ruin friendships within seconds.


## Technical Details
### Components Used

Software:
- Languages: C/C++ (Arduino framework)
- Frameworks: ESP32 Arduino Core
- Libraries: BLEDevice (ESP32 BLE Arduino core), Wire.h
- Tools: Arduino IDE 2.x

Hardware:
- 2× Seeed Studio XIAO ESP32-S3 (1× Handheld Remote Controller, 1× Car Receiver & Motor Controller)
- 1× MPU6050 6-Axis I2C Accelerometer/Gyroscope Module
- 1× 2-Axis Thumb Joystick Module
- 1× L298N Dual H-Bridge Motor Driver
- 2x N20 motos
- 2x3.7V battery pack

### Implementation
# Run
- Connect the Remote Controller XIAO ESP32-S3 to the PC and flash the remote transmitter sketch.
- Connect the Car XIAO ESP32-S3 to the PC and flash the car receiver/motor sketch.
- Power on the car chassis via the onboard battery pack.
- Power on the remote controller; the BLE connection will establish automatically.
- Vigorously shake the remote to satisfy the kinetic motion threshold while deflecting the joystick to steer.
 
### Project Documentation
For Hardware:
<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/9210cfdf-643c-4296-bd3f-4c902c6d2672" />

# Schematic & Circuit
<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/6d46c66e-ad93-48a2-92e8-91dc32d80d61" />

# Build Photos
Building process:
<img width="1600" height="900" alt="starting" src="https://github.com/user-attachments/assets/b0945abe-9fed-4374-9528-2cd936f5259e" />

Final:

### Project Demo
# Video
(https://drive.google.com/file/d/18KS-1wlnEKA20yqXWO2W82PpRjaPfdH_/view?usp=sharing)


## Team Contributions
- Rainaa - Designed overall system architecture; implemented the BLE GATT client/server communication
- Irene - Developed the remote controller firmware, handling joystick analog input processing and MPU6050 kinetic shake detection.

---
Made with ❤️ at TinkerHub Useless Projects 

![Static Badge](https://img.shields.io/badge/TinkerHub-24?color=%23000000&link=https%3A%2F%2Fwww.tinkerhub.org%2F)
![Static Badge](https://img.shields.io/badge/UselessProjects--26-26?link=https%3A%2F%2Ftinkerhub.org%2Fevents%2F1M8ORET9A1%2Fuseless-projects-3.0)




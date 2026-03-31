# Wear_Detection
# Smart Multi-Sensor Tyre Wear Monitoring System (IoT Enabled)
### Real-Time Embedded System with Blynk IoT Integration
**Batch 59 SPD Project | Jan-May 2026**
**Institution:** IIITDM Kancheepuram

---

## 📌 Project Overview
We propose a compact real-time multi-sensor embedded system designed to detect and quantify tyre wear during vehicle operation. The system integrates three sensing modalities—Time-of-Flight (ToF), Tachometry, and IMU vibration analysis—to monitor tread wear continuously. 

The **ESP32** fuses this data and streams live telemetry to a **Blynk IoT dashboard**, providing drivers with instant visual feedback and safety alerts on their smartphones.

## 🛠 Features & IoT Integration
The system utilizes three redundant approaches for maximum reliability:

1. **Approach 1: ToF Depth & Servo Sweep (Primary)**
   * **Hardware:** VL53L0X + SG90 Servo.
   * **Function:** Direct tread depth measurement via laser beam.
   * **Blynk Output:** Real-time depth gauge and spatial wear profile.

2. **Approach 2: Kinematic Radius Calculation (Secondary)**
   * **Hardware:** Hall-effect Tachometer + IMU.
   * **Logic:** Calculates $R = V / \omega$ to infer radius reduction as the tyre wears.
   * **Blynk Output:** Live Radius tracking and "Wear Amount" display.

3. **Approach 3: IMU Vibration Analysis (Complementary)**
   * **Hardware:** MPU-6050.
   * **Function:** Captures 6-axis vibration at ~100 Hz to identify uneven wear signatures.
   * **Blynk Output:** Vibration intensity graph to detect "Patchy" wear.

## 🔧 Hardware Specification
| Component | Specification |
| :--- | :--- |
| **MCU** | ESP32 WROOM-32 (Wi-Fi Enabled) |
| **Depth Sensor** | VL53L0X |
| **IMU Sensor** | MPU-6050 |
| **Actuator** | SG90 Servo |
| **Power** | 2x 2000 mAh Li-Po with TP4056 Charging |

## 🚀 Setup Instructions
1. **Blynk Setup:** Create a new template in Blynk.Cloud and add DataStreams for V1 (Depth), V2 (Radius), V3 (Vibration), and V4 (Alerts).
2. **Firmware:** Update the `Template ID`, `Device Name`, and `Auth Token` in the ESP32 code.
3. **Wi-Fi:** Ensure the ESP32 is connected to your mobile hotspot or campus Wi-Fi.
4. **Calibration:** Set the baseline radius ($R_{initial}$) in the code before the first run.

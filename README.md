# Wear_Detection
# Smart Multi-Sensor Tyre Wear Monitoring System (IoT Enabled)
### Real-Time Embedded System with Blynk IoT Integration
**Batch 59 SPD Project | Jan-May 2026**
**Institution:** IIITDM Kancheepuram

---

## 📌 Project Overview
[cite_start]We propose a compact real-time multi-sensor embedded system designed to detect and quantify tyre wear during vehicle operation[cite: 7]. [cite_start]The system integrates three sensing modalities—Time-of-Flight (ToF), Tachometry, and IMU vibration analysis—to monitor tread wear continuously[cite: 8]. 

[cite_start]The **ESP32** fuses this data and streams live telemetry to a **Blynk IoT dashboard**, providing drivers with instant visual feedback and safety alerts on their smartphones[cite: 9, 28].

## 🛠 Features & IoT Integration
The system utilizes three redundant approaches for maximum reliability:

1. **Approach 1: ToF Depth & Servo Sweep (Primary)**
   * [cite_start]**Hardware:** VL53L0X + SG90 Servo[cite: 13, 14].
   * [cite_start]**Function:** Direct tread depth measurement via laser beam[cite: 22].
   * [cite_start]**Blynk Output:** Real-time depth gauge and spatial wear profile[cite: 41].

2. **Approach 2: Kinematic Radius Calculation (Secondary)**
   * [cite_start]**Hardware:** Hall-effect Tachometer + IMU[cite: 15, 39].
   * [cite_start]**Logic:** Calculates $R = V / \omega$ to infer radius reduction as the tyre wears[cite: 38].
   * **Blynk Output:** Live Radius tracking and "Wear Amount" display.

3. **Approach 3: IMU Vibration Analysis (Complementary)**
   * [cite_start]**Hardware:** MPU-6050[cite: 15].
   * [cite_start]**Function:** Captures 6-axis vibration at ~100 Hz to identify uneven wear signatures[cite: 23, 43].
   * [cite_start]**Blynk Output:** Vibration intensity graph to detect "Patchy" wear[cite: 49].

## 🔧 Hardware Specification
| Component | Specification |
| :--- | :--- |
| **MCU** | [cite_start]ESP32 WROOM-32 (Wi-Fi Enabled) [cite: 45] |
| **Depth Sensor** | [cite_start]VL53L0X [cite: 45] |
| **IMU Sensor** | [cite_start]MPU-6050 [cite: 45] |
| **Actuator** | [cite_start]SG90 Servo [cite: 45] |
| **Power** | [cite_start]2x 2000 mAh Li-Po with TP4056 Charging [cite: 19, 45] |

## 🚀 Setup Instructions
1. **Blynk Setup:** Create a new template in Blynk.Cloud and add DataStreams for V1 (Depth), V2 (Radius), V3 (Vibration), and V4 (Alerts).
2. **Firmware:** Update the `Template ID`, `Device Name`, and `Auth Token` in the ESP32 code.
3. **Wi-Fi:** Ensure the ESP32 is connected to your mobile hotspot or campus Wi-Fi.
4. [cite_start]**Calibration:** Set the baseline radius ($R_{initial}$) in the code before the first run[cite: 30].

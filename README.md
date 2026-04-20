# 𝗦𝗺𝗮𝗿𝘁 𝗠𝘂𝗹𝘁𝗶-𝗦𝗲𝗻𝘀𝗼𝗿 𝗧𝘆𝗿𝗲 𝗪𝗲𝗮𝗿 𝗠𝗼𝗻𝗶𝘁𝗼𝗿𝗶𝗻𝗴 𝗦𝘆𝘀𝘁𝗲𝗺 (𝗕𝗹𝘂𝗲𝘁𝗼𝗼𝘁𝗵 𝗘𝗻𝗮𝗯𝗹𝗲𝗱)
### Real-Time Embedded System for Smart Vehicle Safety
**Batch 59 SPD Project | Jan-May 2026** **Institution:** IIITDM Kancheepuram

---

## 📌 Project Overview
We propose a compact real-time multi-sensor embedded system designed to detect and quantify tyre wear during vehicle operation. The system integrates three sensing modalities—Time-of-Flight (ToF), **Self-Correcting Kinematics**, and IMU vibration analysis—to monitor tread wear continuously.

The **ESP32** fuses this data and streams live telemetry via **Bluetooth Serial**, providing a low-latency, wireless diagnostic tool for real-time radius estimation and safety monitoring.

## 🛠 Features & System Logic
The system utilizes three redundant approaches for maximum reliability:

1. **Approach 1: ToF Depth & Servo Sweep (Primary)**
   * **Hardware:** VL53L0X + SG90 Servo.
   * **Function:** Direct tread depth measurement via laser beam scanning across the tyre width.
   * **Output:** Precise millimeter-level depth profiles.

2. **Approach 2: Autonomous Kinematic Alignment (Self-Correction Strategy)**
   * **Hardware:** Dual Motor Encoders + MPU-6050 + TB6612FNG Motor Driver.
   * **Logic:** On system reset, the vehicle performs a **Calibration Run**. It detects yaw deviation (drift) caused by a smaller, worn tyre. The ESP32 dynamically compensates the RPM of the motors to restore a straight trajectory.
   * **Calculation:** Based on the fundamental relationship **$v = R\omega$**. The system derives the worn radius by calculating the ratio of the compensated motor outputs required to maintain equilibrium.
   * **Output:** Real-time Radius and Wear Delta displayed via Bluetooth Serial Monitor.

3. **Approach 3: IMU Vibration Analysis (Complementary)**
   * **Hardware:** MPU-6050.
   * **Function:** Captures 6-axis vibration data at high frequency to identify uneven wear signatures or flat spots.
   * **Output:** Vibration intensity monitoring for "Patchy" wear detection.

## 🔧 Hardware Specification
| Component | Specification |
| :--- | :--- |
| **MCU** | ESP32 WROOM-32 (Dual-Core, Bluetooth Enabled) |
| **Depth Sensor** | VL53L0X Time-of-Flight |
| **IMU Sensor** | MPU-6050 (6-DOF) |
| **Motor Driver** | TB6612FNG (Dual-Channel H-Bridge) |
| **Actuators** | SG90 Servo + High-Torque Gear Motors |
| **Power** | 2x 2000 mAh Li-Po with TP4056 Charging |

## 🚀 Setup & Operation
1. **Connectivity:** Pair your smartphone or laptop with the ESP32 Bluetooth ID.
2. **Telemetry:** Open any Bluetooth Serial Monitor app (Set baud rate to **115200**).
3. **Calibration Phase:** Place the car on a flat surface and press the **Reset** button on the ESP32.
4. **Autonomous Run:** * **Detection:** The car moves forward, using IMU feedback to find the "Equilibrium RPM" required for straight-line travel.
   * **Calculation:** The car stops for 5 seconds to process data.
   * **Report:** The "Wear Report" is printed to the Serial Monitor, displaying the standard radius vs. the estimated radius based on the $v = R\omega$ calculation.

---

**Grateful to my team:** Roshan, Vijay Surya, Pranav Parasuram, Tejhaswin A, Shri Rishabh  
**Mentor:** Dr. Karthick S  

*Looking forward to refining and taking this further!*

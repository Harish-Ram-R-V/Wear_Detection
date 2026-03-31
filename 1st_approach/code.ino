#include <Wire.h>
#include <VL53L0X_mod.h>
#include <ESP32Servo.h> // Library for ESP32 Servo control

// --- Hardware Pins ---
const int SERVO_PIN = 13; // Connect SG90 signal to GPIO 13
VL53L0X_mod sensor;
Servo sweepServo;

// --- Calibration ---
const int TIRE_BASE_DISTANCE = 50; // Distance to a totally bald tire in mm
const int OFFSET = 40;             // Your specific sensor offset

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // Standard I2C pins for ESP32

  // Initialize Servo
  sweepServo.attach(SERVO_PIN);
  sweepServo.write(90); // Start at center

  // Initialize ToF Sensor
  if (!sensor.init()) {
    Serial.println("Failed to detect VL53L0X!");
    while (1);
  }
  sensor.setTimeout(500);
  
  Serial.println("--- Starting Tread Width Sweep ---");
}

void loop() {
  // Sweep from 45 degrees to 135 degrees (adjust for your mount)
  for (int pos = 45; pos <= 135; pos += 15) {
    sweepServo.write(pos);
    delay(300); // Wait for servo to stabilize

    int rawDist = sensor.readRangeSingleMillimeters();
    
    if (sensor.timeoutOccurred()) {
      Serial.print("TIMEOUT ");
    } else {
      int calibratedDist = rawDist - OFFSET;
      // Tread Depth = Distance to casing - Current distance
      int treadDepth = TIRE_BASE_DISTANCE - calibratedDist;

      Serial.print("Angle: "); Serial.print(pos);
      Serial.print(" | Depth: "); Serial.print(treadDepth);
      Serial.println(" mm");
    }
  }
  
  Serial.println("--- Sweep Complete. Repeating... ---");
  delay(2000); // Wait before next full sweep
}

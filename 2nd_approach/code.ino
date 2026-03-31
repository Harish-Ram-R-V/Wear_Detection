#include <Wire.h>
#include <MPU6050.h>

// --- Hardware Connections ---
const int TACHO_PIN = 18;          // Tachometer OUT pin
const int SLOTS = 20;              // Encoder disc slots [cite: 45]
MPU6050 mpu;

// --- Physical Constants (Input your tire specs) ---
const float R_INITIAL = 32.5;      // Initial radius in mm 
const float PI_VAL = 3.14159;

// --- Global Variables ---
volatile unsigned long pulseCount = 0;
unsigned long lastMillis = 0;
float trueVelocity = 0.0;          // V (from IMU integration)

void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); [cite: 25]
  
  pinMode(TACHO_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TACHO_PIN), countPulse, RISING); [cite: 24]

  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 Link Failed!");
    while (1);
  }
  
  Serial.println("System Initialized. Starting Wear Inference...");
  lastMillis = millis();
}

void loop() {
  unsigned long currentTime = millis();
  float dt = (currentTime - lastMillis) / 1000.0; // Time step in seconds

  if (dt >= 1.0) { // Calculate every 1 second [cite: 25]
    
    // 1. Get Angular Velocity (Omega) from Tachometer [cite: 39]
    noInterrupts();
    unsigned long pulses = pulseCount;
    pulseCount = 0;
    interrupts();

    float rps = (float)pulses / SLOTS;
    float omega = rps * 2.0 * PI_VAL; // Radians per second

    // 2. Get Linear Velocity (V) from IMU 
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    
    // Convert raw acceleration to m/s^2 (assuming 2g scale)
    float accelX = (float)ax / 16384.0 * 9.81; 
    
    // Simple Integration: V = V_old + (a * dt)
    // Note: In a real car, use a high-pass filter to remove gravity bias
    trueVelocity += (accelX * dt); 

    // 3. Solve for Current Radius (R = V / Omega) 
    if (omega > 0.5) { // Prevent division by zero when stopped
      float rCurrent = (trueVelocity * 1000.0) / omega; // Radius in mm
      float wearAmount = R_INITIAL - rCurrent;

      // 4. Output Results [cite: 28]
      Serial.print("V: "); Serial.print(trueVelocity); Serial.print(" m/s | ");
      Serial.print("Omega: "); Serial.print(omega); Serial.print(" rad/s | ");
      Serial.print("Current R: "); Serial.print(rCurrent); Serial.print(" mm | ");
      Serial.print("Wear: "); Serial.print(wearAmount); Serial.println(" mm");
      
      // Alert Logic [cite: 27]
      if (wearAmount > 2.0) { // Threshold for dangerous wear
        Serial.println("!!! ALERT: TREAD WEAR EXCEEDED !!!");
      }
    }

    lastMillis = currentTime;
  }
}

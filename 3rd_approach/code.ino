#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Vibration Thresholds (Calibrate these with a new tire first)
const float VIB_THRESHOLD_WARNING = 1.5; 
const float VIB_THRESHOLD_CRITICAL = 3.0;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  Serial.println("Initializing IMU Vibration Monitor...");
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  // Set Accelerometer Range to +/- 4g for better vibration detail
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_4);
  
  Serial.println("Monitoring Vibration Signatures...");
}

void loop() {
  int16_t ax, ay, az;
  float totalVibration = 0;
  int samples = 50; // Analyze a "burst" of 50 samples (~50Hz window)

  float maxMag = 0;
  float minMag = 100;

  for (int i = 0; i < samples; i++) {
    mpu.getAcceleration(&ax, &ay, &az);

    // Convert raw to G-force (for 4g range, divisor is 8192)
    float xG = (float)ax / 8192.0;
    float yG = (float)ay / 8192.0;
    float zG = (float)az / 8192.0;

    // Calculate Magnitude: sqrt(x^2 + y^2 + z^2)
    float magnitude = sqrt(xG * xG + yG * yG + zG * zG);

    if (magnitude > maxMag) maxMag = magnitude;
    if (magnitude < minMag) minMag = magnitude;
    
    delay(10); // Sampling at ~100Hz [cite: 23]
  }

  // Peak-to-Peak Vibration Intensity
  float intensity = maxMag - minMag;

  // Output to Serial for "Electrojects" data logging [cite: 28]
  Serial.print("Vib_Intensity: ");
  Serial.print(intensity);
  Serial.print(" G | Status: ");

  if (intensity > VIB_THRESHOLD_CRITICAL) {
    Serial.println("CRITICAL WEAR / UNEVEN TREAD"); [cite: 43]
  } else if (intensity > VIB_THRESHOLD_WARNING) {
    Serial.println("WARNING: ABNORMAL VIBRATION"); [cite: 43]
  } else {
    Serial.println("NORMAL");
  }
}

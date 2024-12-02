#include <Wire.h>
#include <math.h>

const int MPU = 0x68; // MPU6050 I2C address
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float gyroAngleX, gyroAngleY, gyroAngleZ;
float yaw;
float AccErrorX, AccErrorY, AccErrorZ, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;

void setup() {
  Serial.begin(19200);
  Wire.begin();                      // Initialize communication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        // End the transmission

  delay(20);
}

void loop() {
  // === Read accelerometer data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  // For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value

  // === Read gyroscope data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  // For a range of +-250 degrees/s, we need to divide the raw values by 131, according to the datasheet
  GyroX = (Wire.read() << 8 | Wire.read()) / 131.0; // X-axis value
  GyroY = (Wire.read() << 8 | Wire.read()) / 131.0; // Y-axis value
  GyroZ = (Wire.read() << 8 | Wire.read()) / 131.0; // Z-axis value

  // Print the values on the serial monitor
  Serial.print("AccX: ");
  Serial.print(AccX);
  Serial.print(" \tAccY: ");
  Serial.print(AccY);
  Serial.print(" \tAccZ: ");
  Serial.print(AccZ);
  Serial.print(" \tGyroX: ");
  Serial.print(GyroX);
  Serial.print(" \tGyroY: ");
  Serial.print(GyroY);
  Serial.print(" \tGyroZ: ");
  Serial.println(GyroZ);

 // Add a delay to make the output readable
}

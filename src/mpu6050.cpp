#include "mpu6050.h"

void MPU6050_Init() {
  I2C_Start();
  I2C_Write(MPU6050_ADDR << 1);
  I2C_Write(0x6B); // PWR_MGMT_1 register
  I2C_Write(0);    // Wake up MPU6050
  I2C_Stop();
  
  // Configure MPU6050 for accelerometer readings
  I2C_Start();
  I2C_Write(MPU6050_ADDR << 1);
  I2C_Write(0x1C); // ACCEL_CONFIG register
  I2C_Write(0x00); // Set accelerometer full scale range to ±2g
  I2C_Stop();
}

void MPU6050_ReadAccelerometer(int16_t *AcX, int16_t *AcY, int16_t *AcZ) {
  I2C_Start();
  I2C_Write(MPU6050_ADDR << 1);
  I2C_Write(0x3B); // Starting address for accelerometer data
  I2C_Start();
  I2C_Write((MPU6050_ADDR << 1) | 0x01);
  *AcX = (I2C_ReadAck() << 8) | I2C_ReadAck();
  *AcY = (I2C_ReadAck() << 8) | I2C_ReadAck();
  *AcZ = (I2C_ReadAck() << 8) | I2C_ReadNack();
  I2C_Stop();
}
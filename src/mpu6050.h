#ifndef MPU6050_H_
#define MPU6050_H_

#include "i2c.h"

#define MPU6050_ADDR 0x68

void MPU6050_Init();
void MPU6050_ReadAccelerometer(int16_t *AcX, int16_t *AcY, int16_t *AcZ);

#endif MPU6050_H_
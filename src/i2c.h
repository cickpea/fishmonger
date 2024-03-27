#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void I2C_Init();
void I2C_Start();
void I2C_Stop();
void I2C_Write(uint8_t);
uint8_t I2C_ReadAck();
uint8_t I2C_ReadNack();

#endif I2C_H_
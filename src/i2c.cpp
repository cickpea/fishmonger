#include "i2c.h"

void I2C_Init() {
  TWBR = 0x48; // Set bit rate register (Baudrate: 100kHz @ 16MHz)
  TWSR = 0x00; // Prescaler = 1
  TWCR = (1 << TWEN); // Enable TWI
}

void I2C_Start() {
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
}

void I2C_Stop() {
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
  _delay_us(50);
}

void I2C_Write(uint8_t data) {
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_ReadAck() {
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  while (!(TWCR & (1 << TWINT)));
  return TWDR;
}

uint8_t I2C_ReadNack() {
  TWCR = (1 << TWINT) | (1 << TWEN);
  while (!(TWCR & (1 << TWINT)));
  return TWDR;
}
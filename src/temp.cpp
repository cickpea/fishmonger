#include "temp.h"

uint8_t read_dht_data(uint16_t* temperature, uint16_t* humidity) {
  uint8_t bits[5];
  uint8_t i, j = 0;

  // Reset port
  DHT_DDR |= (1<<DHT_PIN); // Output
  DHT_PORT &= ~(1<<DHT_PIN); // Low
  _delay_ms(18);
  DHT_PORT |= (1<<DHT_PIN); // High
  _delay_us(1);
  DHT_DDR &= ~(1<<DHT_PIN); // Input
  _delay_us(39);

  // Check start condition 1
  if((DHT_PINC & (1<<DHT_PIN))) {
    return -1;
  }
  _delay_us(80);
  // Check start condition 2
  if(!(DHT_PINC & (1<<DHT_PIN))) {
    return -1;
  }
  _delay_us(80);

  // Read the data (40 bits = 5 bytes)
  for (j=0; j<5; j++) { // Read 5 bytes
    uint8_t result=0;

    for(i=0; i<8; i++) { // Read every bit
      while(!(DHT_PINC & (1<<DHT_PIN))); // Wait until pin goes high
      _delay_us(30); // wait for 30us
      if(DHT_PINC & (1<<DHT_PIN)) // If pin is still high
        result |= (1<<(7-i)); // Add a 1 to the data
      while(DHT_PINC & (1<<DHT_PIN)); // Wait until pin goes low
    }

    bits[j] = result;
  }

  // Check checksum
  if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) {
    return -1;
  }

  // Convert data to actual values
  *humidity = ((uint16_t)bits[0] << 8) | bits[1];
  *temperature = ((uint16_t)bits[2] << 8) | bits[3];

  return 0;
}

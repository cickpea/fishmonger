#ifndef TEMP_H_
#define TEMP_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define DHT_PIN PC2
#define DHT_PORT PORTC
#define DHT_DDR DDRC
#define DHT_PINC PINC

uint8_t read_dht_data(uint16_t* temperature, uint16_t* humidity);

#endif TEMP_H_
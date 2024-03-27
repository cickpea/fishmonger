#ifndef TEMP_H_
#define TEMP_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void adc_init();
uint16_t adc_read(uint8_t);
float lm235z_temperature(uint16_t);

#endif TEMP_H_
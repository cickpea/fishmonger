#include "temp.h"

void adc_init() {
	// Set ADC reference voltage to AVCC
	ADMUX |= (1 << REFS0);
	// Enable ADC and set prescaler to 128 for 16MHz clock
	ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t adc_read(uint8_t adc_channel) {
	// Select ADC channel
	ADMUX = (ADMUX & 0xF0) | (adc_channel & 0x0F);
	// Start ADC conversion
	ADCSRA |= (1 << ADSC);
	// Wait for conversion to complete
	while (ADCSRA & (1 << ADSC));
	// Return ADC value
	return ADC;
}

float lm235z_temperature(uint16_t adc_value) {
	// ADC resolution is 10-bit (0-1023)
	// ADC reference voltage is 5V (assuming AVCC)
	// LM235Z produces 10mV/°C output
	return (adc_value* 0.0488); // Convert to temperature in Celsius
}
#ifndef DISTANCE_H_
#define DISTANCE_H_

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define HC_REG DDRB
#define HC_PORT PORTB
#define HC_PIN PINB
#define TRIG_PIN PB1
#define ECHO_PIN PB0

long measureDistance(void);

#endif 
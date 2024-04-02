#include "distance.h"

long measureDistance() {
    long duration, distance;
    
    HC_PORT |= (1 << TRIG_PIN);
    _delay_us(10);
    HC_PORT &= ~(1 << TRIG_PIN);
    
    while (!(HC_PIN & (1 << ECHO_PIN)));

    TCNT1 = 0; 
    TCCR1B |= (1 << CS11); 
    while (HC_PIN & (1 << ECHO_PIN));
    TCCR1B = 0; 
    duration = TCNT1/2; 
    
    distance = duration * 0.017; 
    if (distance >= 400)
        return -1;
    return distance;
}

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "uart_hal.h"
#include "mpu6050.h"
#include "distance.h"
#include "temp.h"

#define BAUD 9600
#define RAD_TO_DEG 57.2958
#define PI 3.1415926

int main()
{
    HC_REG |= (1 << TRIG_PIN);
    HC_REG &= ~(1 << ECHO_PIN);

    uart_init(BAUD, 0);
    I2C_Init();
    MPU6050_Init();

    int16_t AcX, AcY, AcZ;
    double x, y, z, bot = 9.5, height;

    while (1)
    {
        MPU6050_ReadAccelerometer(&AcX, &AcY, &AcZ);
        x = RAD_TO_DEG * (atan2(-AcY, -AcZ) + PI);
        y = RAD_TO_DEG * (atan2(-AcX, -AcZ) + PI);
        z = RAD_TO_DEG * (atan2(-AcY, -AcX) + PI);
        height = fabs(bot * sin(x / RAD_TO_DEG));

        uint16_t adc_value = adc_read(0);                  // Read from ADC channel 0
        float temperature = lm235z_temperature(adc_value); // Convert ADC value to temperature

        long distance = measureDistance();

        char buffer[80];
        snprintf(buffer, sizeof(buffer), "\rAngleX= %.2f\t\theight= %.2f\t\tDistance= %ld cm\t\tTemp= %.2f", x, height, distance, temperature);
        uart_send_string(buffer);

        _delay_ms(1000);
    }

    return 0;
}

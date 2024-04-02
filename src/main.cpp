#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <math.h>
#include "uart_hal.h"
#include "mpu6050.h"
#include "distance.h"

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
    double x, bot = 9.5, height;

    while (1)
    {
        MPU6050_ReadAccelerometer(&AcX, &AcY, &AcZ);
        x = RAD_TO_DEG * (atan2(-AcY, -AcZ) + PI);
        height = -bot * sin(x / RAD_TO_DEG);

        long distance = measureDistance();

        char buffer[50];
        snprintf(buffer, sizeof(buffer), "\r\rAngleX= %.2f\t\tDistance: %ld cm\t\tTemp: %.2f", x, distance);
        uart_send_string(buffer);
        snprintf(buffer, sizeof(buffer), "height= %.2f", height);
        uart_send_string(buffer);

        _delay_ms(1000);
    }

    return 0;
}

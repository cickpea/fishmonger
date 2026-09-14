# fishmonger: Underwater Survey System

Bare-metal AVR firmware for an underwater survey system, built as an academic project at Dalhousie University. The firmware samples an ultrasonic distance sensor, an IMU and a temperature/humidity sensor, and streams readings over UART.

## What it does

The main loop samples once per second and transmits:

- **Distance** from an HC-SR04 ultrasonic sensor, every cycle
- **Height**, derived from the MPU6050 tilt angle and a fixed baseline of 9.5, every cycle
- **Temperature** from the DHT sensor, only when the measured distance is under 20 cm

Humidity is read from the DHT sensor but is not currently transmitted.

## Hardware

| Component | Role |
|---|---|
| Arduino Nano (ATmega328P) | Microcontroller |
| HC-SR04 | Ultrasonic distance sensing |
| MPU6050 | Accelerometer, used to compute tilt |
| DHT22 | Temperature and humidity |

The DHT model is not named in the firmware. DHT22 is the part used in the project documentation.

## Design notes

The firmware is deliberately **not built on the Arduino API**. Each peripheral driver is written against AVR registers:

- `uart_hal` - UART driver with an interrupt-driven RX ring buffer (`USART_RX_vect`) and a TX busy flag
- `i2c` - driver for the ATmega **hardware TWI** peripheral (TWBR, TWSR, TWCR, TWDR), used by the MPU6050
- `distance` - HC-SR04 ranging, using Timer1 (TCNT1) to time the echo pulse
- `mpu6050` - accelerometer initialisation and read; tilt computed with `atan2`
- `temp` - bit-banged DHT protocol with a checksum check

Written in C++ and built with PlatformIO (`platform = atmelavr`, `board = nanoatmega328`). Build flags enable floating point support in `snprintf`.

## Build and flash

```bash
pio run             # compile
pio run -t upload   # flash to the Nano
```

## Repository layout

```
src/
  main.cpp        # main loop: sample, compute, transmit
  distance.*      # ultrasonic ranging
  mpu6050.*       # accelerometer
  i2c.*           # hardware TWI (I2C) driver
  temp.*          # DHT sensor
  uart_hal.*      # UART driver with ISR ring buffer
platformio.ini
```

## Status

Academic prototype, last updated 2024.

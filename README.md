# fishmonger: Underwater Survey System

Bare-metal AVR firmware for an underwater survey system, built as an academic project at Dalhousie University. The device measures water depth and sensor tilt and streams readings over UART.

## What it does

The unit measures three things and reports them over serial once per second:

- **Depth** from an HC-SR04 ultrasonic sensor
- **Wave and tilt angle** from an MPU6050 accelerometer
- **Surface temperature and humidity** from a DHT sensor

It computes a tilt-corrected depth reading, so the recorded depth stays meaningful when the unit is pitching in moving water.

## Hardware

| Component | Role |
|---|---|
| Arduino Nano (ATmega328P) | Microcontroller |
| HC-SR04 | Ultrasonic depth sensing |
| MPU6050 | Accelerometer, tilt and wave measurement |
| DHT11 | Temperature and humidity |

## Design notes

This firmware is deliberately **not built on the Arduino API**. Every peripheral driver is written from scratch against AVR registers:

- `uart_hal` - UART driver with an interrupt-driven RX ring buffer (`USART_RX_vect`) and TX busy flags
- `i2c` - software TWI master (start, stop, write, read) driving the MPU6050
- `distance` - HC-SR04 ranging, using Timer1 to time the echo pulse
- `mpu6050` - accelerometer initialisation and read; tilt computed with `atan2`, depth corrected with `sin`
- `temp` - DHT bit-banged protocol implementation

Written in C++ and built with PlatformIO (`platform = atmelavr`, `board = nanoatmega328`). The build flags enable floating point support in `snprintf`.

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
  i2c.*           # software I2C / TWI
  temp.*          # DHT sensor
  uart_hal.*      # UART driver with ISR ring buffer
platformio.ini
```

## Status

Academic prototype, completed 2024.

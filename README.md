# I2C Device Driver for 8051 (PT-51 Board)

A baremetal I2C device driver written in C for the AT89C5131A-based PT-51
microcontroller. The driver was used to interface a BMP280 pressure sensor
and a DS1307 RTC module, with output on an onboard LCD and over UART.

---

## What it does

- Implements I2C master communication from scratch on the 8051
- Reads the WHO_AM_I register of the BMP280 to verify communication
- Provides a reusable driver library for reading/writing any I2C device
- Interfaces with the DS1307 RTC to fetch and display timestamps in BCD format
- Prints time and temperature data to a PC via UART serial terminal

---

## Driver API

```c
void    I2C_Start(void);
void    I2C_Stop(void);
void    I2C_Write(uint8_t data);
uint8_t I2C_Read(void);
void    I2C_Ack(void);
void    I2C_Nack(void);
```

---

## Hardware

- PT-51 board (AT89C5131A — 8051 core)
- BMP280 pressure + temperature sensor
- DS1307 RTC module
- Onboard 16×2 LCD
- 10 kΩ pull-up resistors on SDA (P4.1) and SCL (P4.0)

---

## Configuration

- I2C speed: 100 kHz
- UART baud rate: 1200
- RTC power-up delay: 200 ms

# EE337 Course Project — I2C Device Driver on PT-51

![IIT Bombay](https://img.shields.io/badge/IIT%20Bombay-EE337-blue)

Course project for **EE337 Microprocessors Laboratory**, Wadhwani Electronics
Laboratory, Electrical Engineering, IIT Bombay.

The project builds a baremetal I2C device driver on the **AT89C5131A-based PT-51
board** to communicate with a BMP280 pressure sensor and a DS1307 RTC module,
progressing from low-level register reads to a reusable driver library and a
full RTC application.

---

## Project Structure
---

## Phases

| Phase | Week | Goal | Points |
|-------|------|------|--------|
| Phase 1 | Week 1 | Baremetal read of BMP280 WHO_AM_I register; LCD debug | 10 |
| Phase 2 | Week 2 | Custom I2C driver library (`i2c.h` / `i2c.c`) | 15 |
| Phase 3 | Week 3 | DS1307 RTC timestamps on LCD + UART to PC | 5 |

---

## Hardware

- PT-51 board (AT89C5131A — 8051 core)
- BMP280 pressure + temperature sensor (I2C slave)
- DS1307 RTC module (I2C slave, 100 kHz)
- 16×2 LCD (onboard, for debug output)
- 10 kΩ pull-up resistors on SDA (`P4.1`) and SCL (`P4.0`)

---

## I2C Driver API (Phase 2)

```c
void    I2C_Start(void);
void    I2C_Stop(void);
void    I2C_Write(uint8_t data);
uint8_t I2C_Read(void);
void    I2C_Ack(void);
void    I2C_Nack(void);
```

Declare in `i2c.h`, define in `i2c.c`. Additional helper functions may be added.

---

## Configuration Notes

- UART baud rate: **1200**
- I2C speed: **100 kHz** (DS1307 requirement)
- RTC power-up delay: **200 ms**
- All DIP switches **OFF** when using Port 1 pins for I2C

---

## References

- Texas Instruments — *Understanding the I2C Bus* (white paper)
- AT89C5131A datasheet — Two Wire Interface section
- BMP280 datasheet — Register Map section
- DS1307 RTC datasheet

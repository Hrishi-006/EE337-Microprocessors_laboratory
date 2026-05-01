#ifndef I2C_DRIVER_H
#define I2C_DRIVER_H

#include <at89c5131.h>

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Send(unsigned char value);
unsigned char I2C_Read(unsigned char ack);
void I2C_WriteRegister(unsigned char dev, unsigned char reg, unsigned char val);
unsigned char I2C_ReadRegister(unsigned char dev, unsigned char reg);

#endif
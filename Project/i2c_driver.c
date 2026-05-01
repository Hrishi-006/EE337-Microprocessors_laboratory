#include <at89c5131.h>
#include "i2c_driver.h"

sfr SSSEL = 0x96;

#define SI   0x08
#define STO  0x10
#define STA  0x20
#define AA   0x04
#define ENS1 0x40

void I2C_Init(void)
{
    SSCON = ENS1;   
    SSSEL = 0x18;   // Set clock (100 kHz approx)
}

void I2C_Start(void)
{
    SSCON |= STA;        // Start condition
    SSCON &= ~SI;
    while (!(SSCON & SI));
    SSCON &= ~STA;
}

void I2C_Stop(void)
{
    SSCON |= STO;        // Stop condition
    SSCON &= ~SI;
    while (SSCON & STO);
}

void I2C_Send(unsigned char value)
{
    SSDAT = value;       // Load data
    SSCON &= ~SI;
    while (!(SSCON & SI));
}

unsigned char I2C_Read(unsigned char ack)
{
    if (ack)
        SSCON |= AA;     // Send ACK
    else
        SSCON &= ~AA;    // Send NACK

    SSCON &= ~SI;
    while (!(SSCON & SI));

    return SSDAT;
}

void I2C_WriteRegister(unsigned char dev, unsigned char reg, unsigned char val)
{
    I2C_Start();
    I2C_Send(dev << 1);   // Write mode
    I2C_Send(reg);        // Register address
    I2C_Send(val);        // Data
    I2C_Stop();
}
unsigned char I2C_ReadRegister(unsigned char dev, unsigned char reg)
{
    unsigned char val;

    I2C_Start();
    I2C_Send(dev << 1); // Write
    I2C_Send(reg);

    I2C_Start();
    I2C_Send((dev << 1) | 1); // Read

    val = I2C_Read(0);    // NACK

    I2C_Stop();

    return val;
}
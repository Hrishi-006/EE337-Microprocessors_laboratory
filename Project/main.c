#include <at89c5131.h>
#include "lcd.h"
#include "i2c_driver.h"
#include "serial.h"

#define RTC_ADDR 0x68
#define BMP280_ADDR 0x76
unsigned int dig_T1;
int dig_T2, dig_T3;
long t_fine;

void lcd_print_bcd(unsigned char val)
{
    lcd_write_char((val >> 4) + '0');
    lcd_write_char((val & 0x0F) + '0');
}

void uart_print_bcd(unsigned char val)
{
    transmit_char((val >> 4) + '0');
    transmit_char((val & 0x0F) + '0');
}


void lcd_print_temp(int temp)
{
    int integer = temp / 100;
    int frac = temp % 100;

    lcd_write_char((integer / 10) + '0');
    lcd_write_char((integer % 10) + '0');
    lcd_write_char('.');
    lcd_write_char((frac / 10) + '0');
    lcd_write_char((frac % 10) + '0');
    lcd_write_char('C');
}

void uart_print_temp(int temp)
{
    int integer = temp / 100;
    int frac = temp % 100;

    transmit_char((integer / 10) + '0');
    transmit_char((integer % 10) + '0');
    transmit_char('.');
    transmit_char((frac / 10) + '0');
    transmit_char((frac % 10) + '0');
    transmit_char('C');
}
void bmp280_read_calib()
{
    unsigned char lsb, msb;

    lsb = I2C_ReadRegister(BMP280_ADDR, 0x88);
    msb = I2C_ReadRegister(BMP280_ADDR, 0x89);
    dig_T1 = (msb << 8) | lsb;

    lsb = I2C_ReadRegister(BMP280_ADDR, 0x8A);
    msb = I2C_ReadRegister(BMP280_ADDR, 0x8B);
    dig_T2 = (msb << 8) | lsb;

    lsb = I2C_ReadRegister(BMP280_ADDR, 0x8C);
    msb = I2C_ReadRegister(BMP280_ADDR, 0x8D);
    dig_T3 = (msb << 8) | lsb;
}
int bmp280_get_temp()
{
    long adc_T;
    long var1, var2;
    int T;

    unsigned char msb, lsb, xlsb;

    msb  = I2C_ReadRegister(BMP280_ADDR, 0xFA);
    lsb  = I2C_ReadRegister(BMP280_ADDR, 0xFB);
    xlsb = I2C_ReadRegister(BMP280_ADDR, 0xFC);

    adc_T = ((long)msb << 12) | ((long)lsb << 4) | (xlsb >> 4);

    var1 = ((((adc_T >> 3) - ((long)dig_T1 << 1))) * ((long)dig_T2)) >> 11;

    var2 = (((((adc_T >> 4) - ((long)dig_T1)) *
              ((adc_T >> 4) - ((long)dig_T1))) >> 12) *
              ((long)dig_T3)) >> 14;
    t_fine = var1 + var2;

    T = (t_fine * 5 + 128) >> 8;   

    return T;
}
void main(void)
{
    unsigned char sec, min, hr;
    int temp;
    lcd_init();
    I2C_Init();
    uart_init();
    msdelay(200);   
    I2C_WriteRegister(RTC_ADDR, 0x00, 0x00);
    I2C_WriteRegister(RTC_ADDR, 0x01, 0x00);
    I2C_WriteRegister(RTC_ADDR, 0x02, 0x12);   
    I2C_WriteRegister(BMP280_ADDR, 0xF4, 0x27);
     bmp280_read_calib();
    lcd_cmd(0x01);
    lcd_write_string("Time & Temp");
    while(1)
    {      
        sec = I2C_ReadRegister(RTC_ADDR, 0x00) & 0x7F;
        min = I2C_ReadRegister(RTC_ADDR, 0x01);
        hr  = I2C_ReadRegister(RTC_ADDR, 0x02);     
        temp = bmp280_get_temp();       
        lcd_cmd(0xC0);
        lcd_print_bcd(hr); lcd_write_char(':');
        lcd_print_bcd(min); lcd_write_char(':');
        lcd_print_bcd(sec);
        lcd_write_string(" ");
        lcd_print_temp(temp);        
        transmit_string("\r\n");
        uart_print_bcd(hr); transmit_char(':');
        uart_print_bcd(min); transmit_char(':');
        uart_print_bcd(sec);
        transmit_string(" Temp:");
        uart_print_temp(temp);
        msdelay(800);
    }
}
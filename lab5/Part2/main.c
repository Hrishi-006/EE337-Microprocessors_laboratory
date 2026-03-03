#include <at89c5131.h>
// Button declaration
sbit button = P0^7;
// Add LCD pin definitions and function declarations here
unsigned int count = 0;
void lcd_init(void);
void lcd_print_number(unsigned int num);
void lcd_write_char(unsigned char ch);
void lcd_cmd(unsigned int i);
void msdelay(unsigned int time);
sbit RS=P0^0;	//Register select
sbit RW=P0^1;	//Read from or write to register
sbit EN=P0^2;	//Enable pin of lcd

void main()
{
// Initialize LCD
lcd_init();

// Configure button pin
// Implement debounce logic
// Increment counter on valid press
// Display counter value on LCD
while(1){

	if(button==1){
		msdelay(20);
		if(button==1){
			count++;
			
			 lcd_cmd(0x01);
       msdelay(2);
       lcd_cmd(0x80);
       lcd_print_number(count);
			 while (button == 1);	// wait till release of button
		}
	}

	}
}
void msdelay(unsigned int time)
{
int i,j;
for(i=0;i<time;i++)
{
for(j=0;j<382;j++);
}
}
void lcd_init(void)
{
	P2=0x00;
	EN=0;
	RS=0;
	RW=0;
	
	lcd_cmd(0x38);	// Function set: 2 Line, 8-bit, 5x7 dots
	msdelay(4);
	lcd_cmd(0x06);	// Entry mode, auto increment with no shift
	msdelay(4);
	lcd_cmd(0x0C);	// Display on, Curson off
	msdelay(4);
	lcd_cmd(0x01);	// LCD clear
	msdelay(4);
	lcd_cmd(0x80);	//Move cursor to Row 1 column 0
}
void lcd_print_number(unsigned int num)
{
    unsigned char hundreds, tens, ones;

    hundreds = num / 100;
    tens = (num / 10) % 10;
    ones = num % 10;

    lcd_write_char(hundreds + '0');
    lcd_write_char(tens + '0');
    lcd_write_char(ones + '0');
}
void lcd_cmd(unsigned int i)
{
	RS=0;
	RW=0;
	EN=1;
	P2=i;
	msdelay(10);
	EN=0;
}
void lcd_write_char(unsigned char ch)
{
	RS=1;
	RW=0;
	EN=1;
	P2=ch;
	msdelay(10);
	EN=0;
}

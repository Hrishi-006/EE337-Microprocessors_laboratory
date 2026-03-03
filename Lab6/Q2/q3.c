#include <at89c5131.h>

sbit pin=P0^7;
unsigned int freq;
unsigned int reload;
unsigned int target;
unsigned char done = 0;
unsigned char t1_count = 0;

//Functions prototype
void timer0delay(void);
void timer1delay(void);
void set_timer0( unsigned int f);



//Main function
void main(void)
{
	ET0 = 1;
	ET1 = 1; 
  EA  = 1;
	
	TMOD = 0x11;
	
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 240;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=50;
	while(done==0);
	TR0=0;
	t1_count=0;
	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 240;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=50;
	while(done==0);
	TR0=0;
	t1_count=0;
	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 270;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=100;
	while(done==0);
	TR0=0;
	t1_count=0;

	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 240;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=100;
	while(done==0);
	TR0=0;
	t1_count=0;
	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 320;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=100;
	while(done==0);
	TR0=0;
	t1_count=0;
	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 300;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=200;
	while(done==0);
	TR0=0;
	t1_count=0;

	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 240;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=50;
	while(done==0);
	TR0=0;
	t1_count=0;
	
	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 240;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=50;
	while(done==0);
	TR0=0;
	t1_count=0;

	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 270;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=100;
	while(done==0);
	TR0=0;
	t1_count=0;
	
	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 240;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=100;
	while(done==0);
	TR0=0;
	t1_count=0;
	
	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 360;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=100;
	while(done==0);
	TR0=0;
	t1_count=0;
	
	
	done=0;
	TH1 = 0xB1;  
	TL1 = 0xE0;
  freq = 320;
	set_timer0(freq);
  TR0 = 1;
	TR1 = 1;
	target=200;
	while(done==0);
	TR0=0;


while(1);
}
void set_timer0( unsigned int f){
	unsigned long count;
	
	count = (1000000UL/f)-7;
	reload= 65536-count;
	TH0 = (reload >> 8);
  TL0 = reload & 0xFF;
}
void timer0_isr() interrupt 1
{
    pin=~pin  ;  // square wave

    // reload based on your frequency
	  TH0 = (reload >> 8)& 0xFF;
    TL0 = reload;
    
}

void timer1_isr() interrupt 3
{
    TH1 = 0xB1;     // reload for 10 ms
    TL1 = 0xE0;

    t1_count++;

    if(t1_count >= target)   // 50 × 10 ms = 500 ms
    {
        done = 1;
        TR1 = 0;         // stop Timer1
    }
}


// Do toc do dong co tu dem xung Encoder

#include <regx52.h>
#include <stdio.h>
#include <math.h>

#define led P0
#define in P3_2
#define led1 P2_0
#define led2 P2_1
#define led3 P2_2
#define led4 P2_3

unsigned long count = 0,f=0,t=0,x=0,a=0,b=0,tb=0;
unsigned char so[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void delay(int time)
{
	while(time --);
}	

void init()
{
	TMOD = 0x10;
	in =1;
	
	EX0=1; // Cho phep dung ngat ngoai 0
	IT0=1; // Kiem tra dieu kien ngat ngoai tai INT0
	
	ET1=1; // Cho phep dung timer 1
	TR1=1; // Bat timer 1
	
	EA=1;  
}
void demxung(void) interrupt 0 using 1
{
	count ++;
}
void timer(void) interrupt 3 using 2
{
	t++;
	TH1=0xfc;
	TL1=0x18;
	TR1=1;
	if(t==1000)
	{
		x= count;
		count =0;
		t=0;
		a=(int)x*2.4247;
		f=(int)(a+b)/2;
		b=a;
		// nhan 2.4247 la de tu xung tim toc do dong co
	}
}

void hienthi(unsigned char nghin, unsigned char tram, unsigned char chuc, unsigned char donvi)	
{

	led1=1;
	led=so[nghin];	
	delay(1000);
	led1=0;
	
	led2=1;
	led=so[tram];	
	delay(1000);
	led2=0;
	
	led3=1;
	led=so[chuc];
	delay(1000);
	led3=0;
	
	led4=1;
	led=so[donvi];
	delay(1000);
	led4=0;
	
}

void main(void)
{
	init();
	while(1)
	{
		hienthi(f/1000,(f%1000)/100,(f%100)/10,f%10);
	}
}


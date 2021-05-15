
// Bam xung PWM dieu khien toc do dong co
////Dung thach anh 11,0592 MHz

#include <regx52.h>
#include <stdio.h>

#define led1 P2_0
#define led2 P2_1
#define led3 P2_2

#define Led7seg P0

const unsigned char led7[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

// Hien thi led 7 thanh

 void Delay(unsigned int count)
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<112;j++);
} 

void hien_thi(unsigned char a, 
	unsigned char b, 
	unsigned char c)
{
	
	Led7seg  = led7[a];
	led1 = 1;
	Delay(3);
	led1=0;
	
	Led7seg = led7[b];
	led2=1;
	Delay(3);
	led2=0;
	
	Led7seg = led7[c];
	led3=1;
	Delay(3);
	led3=0;
	
	
}

void Hien_thi(void) 
{
		hien_thi((du/100),(du%100)/10, (du%10));
}

// Pam xung PWM

#define PWM_Period 64535

sbit Servo_Motor_Pin = P3^0;

unsigned int ON_Period, OFF_Period, duty_cycle;
unsigned char Tonh, Tonl, Toffh, Toffl,du;



void Timer_init()
{
	TMOD = 0x10;
	EA=1;
	ET1=1;	
	TH1 = (PWM_Period >> 8);
	TL1 = PWM_Period;
	TF1 =0;
}

//---------Dieu chinh do rong xung cao va thap
void Timer1_ISR(void) interrupt 3 using 2
{
	Servo_Motor_Pin = ! Servo_Motor_Pin;
	if(Servo_Motor_Pin)
	{
		TH1 = Tonh;
		TL1= Tonl;
	}
	else
	{
		TH1 = Toffh;
		TL1 = Toffl;
	}	
	
}

// Nut an dieu khien

void Timer0_ISR(void)
{
	if(P1_0==0 && du <=95)
	{
		du = du +5;
		while(P1_0==0);
	}
	if(P1_1==0 && du >=5)
	{
		du = du -5;
		while(P1_1==0);
	}
	if(P1_2==0)
	{
		duty_cycle = du;
	}	
	if(P1_3==0)
	{
		TR1=1;
		while(P1_3==0);
	}
	if(P1_4==0)
	{
		TR1=0;
		while(P1_4==0);
	}
}

// Tinh toan tg dem cho High va Low

void Set_DutyCycle_To()
{
	float period = 65535 - PWM_Period;
	ON_Period = (period/100.0) * duty_cycle;
	OFF_Period = (period - ON_Period);
	
	Tonh = (65535 - ON_Period) >> 8;
	Tonl = (65535 - ON_Period )&0x00FF;
	
	Toffh = (65535 - OFF_Period) >> 8;
	Toffl = (65535 - OFF_Period )&0x00FF;
	
}

//---------------------------------------------
int main()
{
	Servo_Motor_Pin=0;
	du=0;
	duty_cycle=0;
	Timer_init();
	while(1)
	{
	Hien_thi();
		Timer0_ISR();
		Set_DutyCycle_To();
	}
}

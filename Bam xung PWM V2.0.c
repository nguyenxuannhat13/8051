// Dieu khien dong co L298 V2.0
// Bam xung PWM dieu khien toc do dong co
// Dieu khien dong co phan cap 25 50 75 100
////Dung thach anh 11,0592 MHz

#include <regx52.h>
#include <stdio.h>

#define a P1_0	// 25%
#define b P1_1	// 50%
#define c P1_2	// 75%
#define d P1_3	// 100%
#define Right P1_4
#define Left P1_5

//Chan noi voi L298
#define Out1 P3_1	
#define Out2 P3_2


#define PWM_Period 45536 // Co the tu thay doi

sbit Servo_Motor_Pin = P3^0; // Chan tin hieu xung PWM noi voi EA hoac EB cua L298

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
	TR1 = 1;
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



void DK(void)
{
	if(a == 0)
	{
		du = 25;
		while(a==0);
	}
	if(b ==0 )
	{
		du = 50;
		while(b==0);
	}
	if(c==0)
	{
		du = 75 ;
		while(c==0);
	}	
	if(d==0)
	{
		du = 100;
		while(d==0);
	}
	if(Right ==0)
	{
		Out1 = 1;
		Out2 = 0;
	}
	if(Left == 0)
	{
		Out1 =0;
		Out2 =1;
	}
	duty_cycle = du;
}

void Set_DutyCycle_To(void)
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
		DK();
		Set_DutyCycle_To();
	}
}

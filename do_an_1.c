#include <REGX52.H>

/*-------------------
	Xe do duong
	Dung L298
	Co dieu khien toc do dong co
	
	
	+) luu y ve cam bien do duong
	

--------------------*/



// Chan ket noi L298

sbit mot1=P2^0;
sbit mot2=P2^1;
sbit mot3=P2^2;
sbit mot4=P2^3;

// Chan ket noi cam bien do duong

sbit s_left=P2^6;
sbit s_right=P2^7;



void forward (void)
{
  mot1=0;
	mot2=1;
	mot3=1;
	mot4=0;
}
void backward (void)
{
  mot1=0;
	mot2=1;
	mot3=0;
	mot4=1;
}
void left (void)
{
  mot1=0;
	mot2=1;
	mot3=0;
	mot4=0;
}
void right (void)
{
  mot1=0;
	mot2=0;
	mot3=1;
	mot4=0;
}
void stop (void)
{
  mot1=0;
	mot2=0;
	mot3=0;
	mot4=0;

   }



// Bam xung PWM dieu khien toc do dong co
////Dung thach anh 11,0592 MHz




 void Delay(unsigned int count)
{
	int i,j;
	for(i=0;i<count;i++)
	for(j=0;j<112;j++);
} 


// dieu hien toc do

#define PWM_Period 55536

sbit Servo_Motor_Pin = P0^0;

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
	TR1=1;
}

//---------Dieu chinh do rong xung cao va thap de dieu khien toc do dong co
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


void Set_DutyCycle_To() // Tinh toan thoi gian cua muc 1 va 0 trong 1 chu ky
{
	float period = 65535 - PWM_Period;
	ON_Period = (period/100.0) * duty_cycle;
	OFF_Period = (period - ON_Period);
	
	Tonh = (65535 - ON_Period) >> 8;
	Tonl = (65535 - ON_Period )&0x00FF;
	
	Toffh = (65535 - OFF_Period) >> 8;
	Toffl = (65535 - OFF_Period )&0x00FF;
	
}

//------------------------------

void main()
{
 Servo_Motor_Pin=0;
 Timer_init();
	s_left=1;
	s_right=1;
	
	duty_cycle=99; // Phan tram cua muc 1 trong 1 chu ky
	while(1)
	{ 	  
  	   
	 if(s_left==0 && s_right==0)
	 {
		 forward();
	 }
	 else if(s_left==1 && s_right==1)
	 {
		 stop();
	 }
	 else if(s_left==0 && s_right==1)
	 {
		 left();
	 }
	 else if(s_left==1 && s_right==0)
	 {
		 right();
	 }
	 Set_DutyCycle_To();
 }
}

#include <regx52.h>

unsigned char led1[]={0xfe,0xfc,0xf8,0xf0,0xe0,0xc0,0x80,0x00}; // 0-7
unsigned char led2[]={0x7f,0x3f,0x1f,0x0f,0x07,0x03,0x01,0x00}; // 7-0
void delay(unsigned char t)
{
	while(t--)
	{
		TMOD= 0x01;
		TH0 = 0xfc;
		TL0= 0x18;
		TR0 =1;
		while(TF0==0);
		TR0=0;
		TF0=0;
	}
}
void sang(unsigned char x)
{
	
	while(x--)
	{
	P0=P1=P2=P3=0x00;
	delay(100);
	P0=P1=P2=P3=0xff;
	delay(100);
	}
}
void sang2(int t)
{
	while(t--)
	{
		P0=P3=0x00;
		delay(100);
		P0=P3=0xff;
		delay(100);
	}
}
void sang3(unsigned char a)
{
	while(a--)
	{
		P1=P2=0;
		delay(100);
		P1=P2=0xff;
		delay(100);
	}
}
void sangtheoluot()
{
	int i;
	for(i=0;i<8;i++)
	{
		P0=P1=P2=P3=led1[i];
		delay(100);
	}
}
void sangtheoluot1()
{
	int i,j;
		P0=P3=0xff;
	for(i=0;i<8;i++)
	{
	
		P1=P2=led1[i];
		delay(100);
	}
		P1=P2=0x00;
	for(j=0;j<8;j++)
	{
	
		P0=P3=led1[j];
		delay(100);
	}
}
void sangtheoluotnguoc()
{
	int i;
	for(i=0;i<8;i++)
	{
		P0=P1=P2=P3=led2[i];
		delay(100);
	}
}
void sangtheoluot2()
{
	int i,j;
		P1=P2=0xff;
	for(i=0;i<8;i++)
	{
	
		P0=P3=led1[i];
		delay(100);
	}
		P0=P3=0x00;
	for(j=0;j<8;j++)
	{
	
		P2=P1=led1[j];
		delay(100);
	}
}
void sangtheoluot3()
	{
		int a,b,c,d;
			P0=P2=P3=0xff;
			for(a=0;a<8;a++)
			{
				P1=led1[a];
				delay(100);
			}
			P1=0x00;
			P0=P2=0xff;
			for(b=0;b<8;b++)
			{
				P3=led1[b];
				delay(100);
			}
			P1=P3=0x00;
			P0=0xff;
			for(c=0;c<8;c++)
			{
				P2=led1[c];
				delay(100);
			}
			P1=P2=P3=0x00;
			for(d=0;d<8;d++)
			{
				P0=led1[d];
				delay(100);
			}	
	}
void sangtheoluot4()
{
	int a,b,c,d;
			P1=P2=P3=0xff;
			for(a=0;a<8;a++)
			{
				P0=led2[a];
				delay(100);
			}
			P0=0x00;
			P1=P3=0xff;
			for(b=0;b<8;b++)
			{
				P2=led2[b];
				delay(100);
			}
			P0=P2=0x00;
			P1=0xff;
			for(c=0;c<8;c++)
			{
				P3=led2[c];
			}
			P0=P2=P3=0x00;
			for(d=0;d<8;d++)
			{
				P1=led2[d];
				delay(100);
			}	
}

void main(void)
{
	while(1)
	{
		
		//sang(5);
		//sangtheoluot();
		//sangtheoluot1();
	//	sangtheoluotnguoc();
	//	sangtheoluotnguoc2();
		sangtheoluot3();
		sangtheoluot4();
	}
	
}

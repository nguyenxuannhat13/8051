
/*------------------
	Giao tiep DHT11 voi AT89S52
	Hien thi LCD1602

-------------------*/


#include <REGX52.H>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LCD1602.h"

sbit DHT11=P2^1;  /* CHan du lieu DHT11 */

int I_RH,D_RH,I_Temp,D_Temp,CheckSum; 

void delay(int n) // delay 
{
		int x,y;
	for(x=0;x<=n;x++)
	{
		for(y=0;y<123;y++);
	}
}

void timer_delay20ms()  /* Delay 20ms */
{
 TMOD = 0x01;
 TH0 = 0xB8;  
 TL0 = 0x0C;  
 TR0 = 1;  
 while(TF0 == 0); 
 TR0 = 0;  
 TF0 = 0;  
}

void timer_delay30us()  /* Delay */
{
 TMOD = 0x01;  
 TH0 = 0xFF;  
 TL0 = 0xF1;  
 TR0 = 1;  
 while(TF0 == 0); 
 TR0 = 0;  
 TF0 = 0;  
}

void Request()   /* Microcontroller send request */
{
 DHT11 = 0;  /* set to low pin */
 timer_delay20ms(); /* wait for 20ms */
 DHT11 = 1;  /* set to high pin */
}

void Response()   /* Receive response from DHT11 */
{
 while(DHT11==1);
 while(DHT11==0);
 while(DHT11==1);
}

int Receive_data()  /* Receive data */
{
 int q,c=0; 
 for (q=0; q<8; q++)
 {
  while(DHT11==0);/* check received bit 0 or 1 */
  timer_delay30us();
  if(DHT11 == 1) /* If high pulse is greater than 30ms */
  c = (c<<1)|(0x01);/* Then its logic HIGH */
  else  /* otherwise its logic LOW */
  c = (c<<1);
  while(DHT11==1);
 }
 return c;
}

void main()
{
 unsigned char dat[20]; // Khai bao mang dung chua du lieu
 LCD_Init();  
 LCD_Gotoxy(0,0);
	LCD_Puts("Loading ...");
	delay(500);
	LCD_Clear();
	
 while(1)
 {  
  Request(); /* send start pulse */
  Response(); /* receive response */
  
  I_RH=Receive_data(); /* store first eight bit in I_RH */
  D_RH=Receive_data(); /* store next eight bit in D_RH */
  I_Temp=Receive_data(); /* store next eight bit in I_Temp */
  D_Temp=Receive_data(); /* store next eight bit in D_Temp */
  CheckSum=Receive_data();/* store next eight bit in CheckSum */

  if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum)
  {
		LCD_Gotoxy(0,0);
		LCD_Puts("Error");
  }
	
  else
  {
   sprintf(dat,"Hum = %d.%d",I_RH,D_RH);
   LCD_Gotoxy(0,0);
		LCD_Puts(dat);
		LCD_Puts(" %");
		
   sprintf(dat,"Tem = %d.%d",I_Temp,D_Temp);   
   LCD_Gotoxy(0,1);
		LCD_Puts(dat);
		LCD_PutChar(0xDF); // Ma Hex cua dau do C
   LCD_Puts("C");
	
// Tong nhiet do + do am		
 //  memset(dat,0,20);
 //  sprintf(dat,"%d   ",CheckSum);
//		LCD_Gotoxy(13,1);
	//	LCD_Puts(dat);
  }  
  delay(100);
 } 
}
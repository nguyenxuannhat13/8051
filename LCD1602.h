

/*Giao tiep 8051 voi LCD1602*/
#include <REGX52.H>
#include <string.h>
#include <stdio.h>
#define VREF                          5


#ifndef _LCD1602_H_
#define _LCD1602_H_
void delay_us(unsigned int t);
void delay_ms(unsigned int t)	;
void LCD_Enable(void);
void LCD_Send4Bit(unsigned char Data);
void LCD_SendCommand(unsigned char command);
void LCD_Clear();
void LCD_Init();
void LCD_Gotoxy(unsigned char x, unsigned char y);
void LCD_PutChar(unsigned char Data);
void LCD_Puts(char *s);
void num_dsp( float number);

#endif
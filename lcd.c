/*
  16x2 LCD (4-bit mode) interfacing with LPC2148(ARM7)
  http://www.electronicwings.com/arm7/lcd-16x2-interfacing-with-lpc2148-4-bit-mode
*/

#include <lpc214x.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "delay.h"


void LCD_CMD(char command)
{
	IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((command & 0xF0)<<8) ); /* Upper nibble of command */
	IO0SET = 0x00000040; /* EN = 1 */
	IO0CLR = 0x00000030; /* RS = 0, RW = 0 */
	delay_ms(5);
	IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = RW = 0)	 */
	delay_ms(5);
	IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((command & 0x0F)<<12) ); /* Lower nibble of command */
	IO0SET = 0x00000040; /* EN = 1 */
	IO0CLR = 0x00000030; /* RS = 0, RW = 0 */
	delay_ms(5);
	IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = RW = 0)	 */
	delay_ms(5);
	
}

void LCD_INIT(void)
{
	IO0DIR = 0x0000FFF0; /* P0.12 to P0.15 LCD Data. P0.4,5,6 as RS RW and EN */
	delay_ms(20);
	LCD_CMD(0x02);  /* Initialize lcd in 4-bit mode */
	LCD_CMD(0x28);  /* 2 lines */
	LCD_CMD(0x0C);   /* Display on cursor off */
	LCD_CMD(0x06);  /* Auto increment cursor */
	LCD_CMD(0x01);   /* Display clear */
	LCD_CMD(0x80);  /* First line first position */
}

void LCD_STRING (char* msg)
{
	uint8_t i=0;
	while(msg[i]!=0)
	{
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((msg[i] & 0xF0)<<8) );
		IO0SET = 0x00000050; /* RS = 1, EN = 1 */
		IO0CLR = 0x00000020; /* RW = 0 */
		delay_ms(2);
		IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = 1, RW = 0) */
		delay_ms(5);
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((msg[i] & 0x0F)<<12) );
		IO0SET = 0x00000050; /* RS = 1, EN = 1 */
		IO0CLR = 0x00000020; /* RW = 0 */
		delay_ms(2);
		IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = 1, RW = 0) */
		delay_ms(5);
		i++;
	}
}

void LCD_CHAR (char msg)
{
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((msg & 0xF0)<<8) );
		IO0SET = 0x00000050; /* RS = 1, EN = 1 */
		IO0CLR = 0x00000020; /* RW = 0 */
		delay_ms(2);
		IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = 1, RW = 0) */
		delay_ms(5);
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | ((msg & 0x0F)<<12) );
		IO0SET = 0x00000050; /* RS = 1, EN = 1 */
		IO0CLR = 0x00000020; /* RW = 0 */
		delay_ms(2);
		IO0CLR = 0x00000040; /* EN = 0, RS and RW unchanged(i.e. RS = 1, RW = 0) */
		delay_ms(5);
}

//int main(void)
//{
//	uint8_t j;
//	j = 0;
//	char val_j[3];
//	LCD_INIT();
//	LCD_STRING("Good Day!");
//	LCD_CMD(0xC0);
//	LCD_STRING("Val of j is:");
//	for(j=0;j<10;j++)
//	{		
//		sprintf(val_j,"%d ",j);
//		LCD_STRING(val_j);	
//		delay_ms(100);
//		LCD_CMD(0xCC);
//	}
//	return 0;
//}
#include "lpc23xx.H"
#include "INOUT.H"


void INOUT(void)
{
PCLKSEL1 = 0x00000000;//bit 2 and 3 select the gpio type and (cluck/n)
	PINSEL0=0x00000000;//all pins of port 0 : gpio
	PINSEL1=0x00000000;//all pins of port 1 : gpio
	
//P0.23
PINSEL1 &=0xFFFF7FFF; //bit 14:15 [01xx] -- P0.23  AD0.0 input from termistor 
	PINSEL1 &=0x00004000;
PINMODE1 &= 0xffffEfff;///bit 14 and 15 [xx10] pin has neither pull-up nor pull-down..
	PINMODE1 |=0x00002000;
FIO0DIR &=0xFFF3FFFF;//bit23=0 [0xxx] Controlled pin is input.

	
PINSEL3 &=0xFFFFFFCF; //bit 4:5 -- P1.18 PWM1.1 OUTPUT 
	PINSEL3 |=0x00000020;
PINMODE3 &= 0xffffffcf;
	
PINSEL3 &=0xFFFFFCFF; //bit9:8 P1.20 1.20 PWM1.2  OUTPUT
	PINSEL3 |=0x00000200;


PINSEL0 &=0xfffffffE; //bit 1:0 [xx10]-->&[1110],|[0010] P0.0 output for led and busser 
	PINSEL0 |=0x00000002;//Function when (10)-->TXD3


PINSEL0 &=0xfffffff3;//bit 3:2 [00xx]-->&[0011] P0.1 gpio for  busser 
FIO0DIR |=0x00000002;//Controlled pin is output.

PINSEL0 &=0xffffffCf;//bit 4:5 [xx00]-->&[1100] P0.2 gpio for 2nd motor 
FIO0DIR |=0x00000004;//Controlled pin is output.

PINSEL0 &=0xffffff3f;//bit 6:7 [00xx]-->&[0011] P0.3 gpio for yellow LED
FIO0DIR |=0x00000008;//Controlled pin is output.

PINSEL1 &=0xcfffffff;//bit 28:29 [xx00]-->&[1100] P0.30 gpio for green LED
FIO0DIR |=0x40000000;//Controlled pin is output.

PINSEL0 &=0x3fffffff;//bit 30:31 [00xx]-->&[0011] P0.31 gpio for red LED
FIO0DIR |=0x80000000;//Controlled pin is output.
	
}

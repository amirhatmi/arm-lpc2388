#include "LPC23xx.H"
#include "UARTInit.h"

void UARTInit(int BDRate)
{
	
	PCONP |= 0x00000004;
	PCLKSEL0 &= 0xFFFFFF3F;//7:6 [00xx] PCLK_UART0 Peripheral clock selection for UART0 
						//  00=>clc/(4) => 64/4=16 MHz
	
	U0LCR |= 0x80; //UART0 Line Control Register //Enable access to Divisor Latches 
	
	//UARTnbaudrate= PCLK/( 16(256UnDLM + UnDLL)(1+DivAddVal/MulVal) )
	//1 =< MULVAL =< 15
	//0 =< DIVADDVAL =< 14
	//DIVADDVAL < MULVAL
	
	int x=16000000/(BDRate*16);
	int dlm=0;
	int dll=0;
	float y;
	
	dlm=x/256;
	dll=x-dlm*256;
	
	y=16000000/(BDRate*16*x);
	int div=(y-1)*10; 

	U0LCR=0x83;
	U0DLL=dll;
	U0DLM=dlm;
	U0FDR=0x000000A0 | div; //3:0 DivAddVal //7:4 MULVAL
	U0LCR=0x03;
	U0FCR = 0x07;
	
}


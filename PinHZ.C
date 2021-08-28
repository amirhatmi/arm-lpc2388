#include "LPC23xx.H"
#include "PinHZ.h"
#include "delay.h"     //User defined library which conatins the delay routines

//pin output is set to HIGH.
void PinSetHigh0(int pinnumber)
{
		pinnumber=(1<<pinnumber);
		FIO0SET |= pinnumber;	/*This register is used to produce a HIGH level output 
														at the port pins configured as GPIO in an OUTPUT mode*/	
}

//pin output is set to LOW.
void PinSetZero0(int pinnumber)
{
		pinnumber=(1<<pinnumber);
		FIO0CLR |=pinnumber;/*This register is used to produce a LOW leveloutput at
													port pins configured as GPIO in anOUTPUT mode.*/
}

void PinPeriodic0HZ(int pinnumber ,int delay_ms)
{
	pinnumber=(1<<pinnumber);
		FIO0SET |=pinnumber;//pin output is set to HIGH.
		delay(delay_ms);
		FIO0CLR |=pinnumber;//pin output is set to LOW.
		delay(delay_ms);
			
}

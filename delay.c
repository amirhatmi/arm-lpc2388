#include "LPC23xx.H"
#include "delay.h"


void delay(unsigned int count)
{
  unsigned int j=0,i=0;
  for(j=0;j<count;j++)
  {
    for(i=0;i<100;i++);
  }
}


/************************************************
**								 DelayMS()
*************************************************/
void delay_ms( double delayInMs)
{
  
	/*
	* setup timer #0 for delay
	*/
	T0TCR = 0x02;		/* reset timer */
	T0PR  = 0x00;		/* set prescaler to zero */
	T0MR0 = delayInMs * (16000000 / 1000-1);
	T0IR  = 0xff;		/* reset all interrrupts */
	T0MCR = 0x04;		/* stop timer on match */
	T0TCR = 0x01;		/* start timer */
  
	/* wait until delay time has elapsed */
	while (T0TCR & 0x01);
  return;
}


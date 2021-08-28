#include "lpc23xx.H"
#include "PWM.H"

/******************************************************************************
**                            PWM0_Start
******************************************************************************/
//Enable PWM by setting the PCR, PTCR registers
void PWM_Start( int ChannelNum )
{
	PCONP |= 0x00000040;    /*bit 6 power    */
		
	/*  single edge, enable */
	if (ChannelNum == 1)
	{
		PWM0PCR |= PWMENA1;
	}
	else if ( ChannelNum == 2 )
  {
		PWM0PCR |= PWMENA2;
	}
	
	PWM1PR = 16-1; // 1 micro-second resolution
	
	PWM0MR0 = PWM_CYCLE;	/* set PWM cycle */
	
	
	PWM0LER = LER0_EN;
	/**/
	
  return;
}


/******************************************************************************
**                            PWM0_WidthSet1
******************************************************************************/
void PWM0_WidthSet1(double Width )
{			
	
	double cycle = PWM_CYCLE;
	PWM0MR1 = cycle * Width;
	
	PWM0TCR = TCR_CNT_EN | TCR_PWM_EN ;	/* counter enable, PWM enable */
	
	PWM0MCR = 1 << 4; /*the PWMTC will be reset if PWMMR0 matches it.*/
	/**/
	
	/* The LER will be cleared when the Match 0 takes place, in order to
	load and execute the new value of match registers, all the PWMLERs need to
	reloaded. all PWM latch enabled */
	PWM0LER = LER0_EN | LER1_EN ;

  return;
}


/******************************************************************************
**                            PWM0_WidthSet2
******************************************************************************/
void PWM0_WidthSet2(double Width )
{				
	
	int cycle = PWM_CYCLE;
	PWM0MR2 = cycle * Width;
	
	PWM0MCR = 1 << 7; /*the PWMTC will be reset if PWMMR0 matches it.*/
	
	/* The LER will be cleared when the Match 0 takes place, in order to
	load and execute the new value of match registers, all the PWMLERs need to
	reloaded. all PWM latch enabled */
	PWM0LER = LER0_EN | LER2_EN ;
	
  return;
}


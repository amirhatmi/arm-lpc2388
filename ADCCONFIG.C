#include "lpc23xx.H"
#include "ADCCONFIG.H"



void ADC0CONFIG(void)
{

	PCONP |= 0X00001000;//ADC power
	PCLKSEL1 &=0xfcffffff; //25:24 [xx00] (taein CLK vorodi ADC)64/4=16MHz
	
	AD0CR |= 0x0020c700; /* bit(21):PDN 
													bit(15:8)[c7]: CLK/(value +1)
													we chosed value=199 ----> fs = 16MHz/200 =80KHz */ 
	
	//Measurement range 0 to 3 V.

}


int ADC0StartReadCH( int channelNum )
{
  AD0CR &= 0xFFFFFF00; /* bit(7:0):channel number is 0 through 7 [00]*/	
  AD0CR |= (1 << 24) | (1 << channelNum);	
				/* (1 << channelNum) switch channel,to be sampled and converted.
					 (1 << 24) bit24 start A/D convert */
}


unsigned int value;
int ADC0DataCH0(void)
{
	value=AD0DR0;
	while((AD0DR0 & 0x80000000)==0); // Wait for end of A/D Conversion
  value=(value>>6) & 0x03FF; /* return A/D conversion value */
	return value;
	
	/*if (AD0STAT >> channelNum )
	{
		
	}*/
}


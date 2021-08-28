#include "lpc23xx.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "temp.h"

#include "PLLCNFG.H"
#include "INOUT.H"
#include "ADCCONFIG.H"

#include "UARTInit.h"
#include "PinHZ.h"

#include "PWM.H"
#include "delay.h"

#include "lcd.H"



volatile double Tmax=60;
volatile double Tmin=25;
volatile double Tmedium=30;

volatile double width1;
volatile double width2;

/****************************************************************
**                           Width1
*****************************************************************/
double Width1(double T)
	{		
		if (T > Tmedium)
		{
			width1 = (T-Tmin+1)/(Tmax-Tmin);
			if (T > Tmax)
			{
				width1=1;
			}
		}
		return width1;
	}
	
	
/****************************************************************
**                           main()
*****************************************************************/	
int main()
{
	CLKSRCSEL = 0x00; // we selected internal source 4Mhz
	
  PLLCNFG(); 		//pll configuration
	CCLKCFG=0x05;	//PLL output divider for system and pripherals ---> 320/(5+1)=64 MHz
	
	
	INOUT();  //pins setting
	
	UARTInit(115200); //baud rate setting 
	
	ADC0CONFIG(); //ADC configuration
	ADC0StartReadCH(0); //we select AD0.0 to be sampled and converted.

	
	LCD_INIT();
	LCD_STRING("temp control");
		LCD_CMD(0xC0);
	LCD_STRING("Val of T is:");


	

	
	double T=temp();
	char temp_v[3];
	
		while(1)
	{
		T=temp();//update temp value
		PinSetHigh0(30);//turn on green LED
		
		
		if( T >= Tmedium )
		{
			PWM_Start(1);//Turn on 1st pwm 
			
			PinSetZero0(30);//turn off green LED			
			PinSetHigh0(3);//turn on yellow LED
			
			while (T >= Tmin)
			{
				T=temp();//update temp value
				width1 = Width1(T);
				
				PWM0_WidthSet1(width1);//update 1st pwm width
				
			if(T >= Tmax )
				{
					width1 = Width1(T);//1st pwm max Width
					PWM0_WidthSet1(width1);
					
					PinSetHigh0(2);//turn on 2nd motor whith high power
					while (T >= Tmedium)
						{
							T=temp();//update temp value			
							while(T >=Tmax)
							{
								PinSetHigh0(1);//Turn on Buzzer
								PinSetHigh0(31);//Turn on red LED
								
								sprintf(temp_v,"%d ",(int)(T));
								LCD_STRING(temp_v);	
								delay_ms(100);
								LCD_CMD(0xCC);
								
								PinSetZero0(1);//turn off Buzzer
								PinSetZero0(31);//turn off red LED
								
								T=temp();//update temp value
							}//while(T >=Tmax)								
						}
					PinSetZero0(2); //turn off 2nd motor when T < Tmedium	

						
					sprintf(temp_v,"%d ",(int)(T));
					LCD_STRING(temp_v);	
					delay_ms(100);
					LCD_CMD(0xCC);
				}//while(T>=Tmedium)	
				
				
				sprintf(temp_v,"%d ",(int)(T));
				LCD_STRING(temp_v);	
				delay_ms(100);
				LCD_CMD(0xCC);
								
			}//while (T >= Tmin)
			PinSetZero0(3);//turn off yellow LED
			
		}//if( T >= Tmedium )	
		
		
		sprintf(temp_v,"%d ",(int)(T));
		LCD_STRING(temp_v);	
		delay_ms(100);
		LCD_CMD(0xCC);
		
		
		
	}//while(1)
}//maine

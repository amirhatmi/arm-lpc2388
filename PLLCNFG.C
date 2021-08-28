#include "lpc23xx.H"
#include "PLLCNFG.H"

 
	
void PLLCNFG(void)
{	
	PLLCON = 0x01;//Enable PLL //The PLLCON register contains the bits that enable and connect the PLL
								// 0 - PLL Enable. //1 - PLL Connect. //7:2 - Reserved
	
  PLLCFG = 0x00000028;//Multiplier and divider setup //14:0 MSEL //23:16 NSEL
											//we allocate (40)decimal to M and our pll out signal is 320Mhz
	
	PLLFEED = 0xAA;         //Feed sequence
  PLLFEED = 0x55;
  
  while(!(PLLSTAT & 0x00000028)); //is locked?
    
  PLLCON = 0x03;          //Connect PLL after PLL is locked
	
  PLLFEED = 0xAA;        //Feed sequence
  PLLFEED = 0x55;
 
}

	
#include "LPC23xx.H"
#include "temp.h"
#include "ADCCONFIG.H"
#include <cmath>


double temp(void)
{
	double ADCdata = ADC0DataCH0();
	

  double A1 =  3.354016E-03;
		double B1 =  2.569850E-04 ;
			double C1 =  2.620131E-06;
				double D1 =  6.383091E-08;
	
		
	//Vin=(VR/Vref)*1023
	double VR = (ADCdata/1023.00)*3.30;
	//VR=5*(R0)/(R0+R)
	double R0=2700.00;
	double R=((5-VR)*R0)/VR;
	double T=1/(  A1+(B1*log(R/10000.00)+(  C1*pow(log(R/10000.00),2) )+(  D1*pow(log(R/10000.00),3) ))  );
	
	double temp= T-273;
	return temp;
}
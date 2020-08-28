#include "touchscreen.h"
#include "printf.h"

void TS_Init(void)
{
	/*Initialize ADC Clock*/
	ADCCON = ((1<<14)|(49<<6));

	/*Initialize ADC_TC Interrupt*/
	/*Clear source pend*/
	ADCUPDN |= (3<<0);
	SUBSRCPND |= (1<<9);
	INTPND |= (1<<31);

	/*Clear mask*/
	INTMSK &= (~(1<<31));
	INTSUBMSK &= (~(1<<9));

	/*Enter Waiting for interrupt mode*/
	ADCTSC = 0xd3;
}


void TS_ADC_TC_Irq(void)
{
	unsigned short xdata, ydata;

	if(ADCUPDN & (1<<0))/*DOWN*/
	{
		/*Auto X,Y measurement*/
		ADCTSC = (1<<2);
		ADCCON |= (1<<0);

		/*Wait for ADC Conversion*/
		while((ADCCON & (1<<15)) == 0);

		/*Read X,Y*/
		xdata = (ADCDAT0 & 0x3FF);
		ydata = (ADCDAT1 & 0x3FF);
		
		printf("(%d, %d)\r\n", xdata, ydata);

		/*Clear Pending*/
		ADCUPDN |= (1<<0);
		SUBSRCPND |= (1<<9);
		INTPND |= (1<<31);

		/*Enter Waiting for interrupt mode*/
		ADCTSC = 0xd3;
		ADCTSC |= (1<<8);
	}
	else if(ADCUPDN & (1<<1))/*UP*/
	{
		/*Clear Pending*/
		ADCUPDN |= (1<<1);
		SUBSRCPND |= (1<<9);
		INTPND |= (1<<31);
	}
}



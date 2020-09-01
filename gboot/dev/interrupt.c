#include "interrupt.h"
#include "led.h"
#include "touchscreen.h"
#include "dm9000.h"

void irq_handler(void)
{
	switch(*pINTOFFSET)
	{
		case 4: /*EINT4_7*/
			if(*pEINTPEND & (1 << 7)) /*EINT7---LAN*/
			{
				*pEINTPEND = (1 << 7);

				dm9000_irq_handler();
			}

			break;

		case 5:	/*EINT8_23*/
			if(*pEINTPEND & (1 << 8)) /*EINT8---KEY1*/
			{
				led_num(1);
				*pEINTPEND |= (1 << 8);
			}
			
			if(*pEINTPEND & (1 << 11)) /*EINT11---KEY2*/
			{
				led_num(2);
				*pEINTPEND |= (1 << 11);
			}

			if(*pEINTPEND & (1 << 13)) /*EINT13---KEY3*/
			{
				led_num(3);
				*pEINTPEND |= (1 << 13);
			}

			if(*pEINTPEND & (1 << 14)) /*EINT14---KEY4*/
			{
				led_num(4);
				*pEINTPEND |= (1 << 14);
			}

			if(*pEINTPEND & (1 << 15)) /*EINT15---KEY5*/
			{
				led_num(5);
				*pEINTPEND |= (1 << 15);
			}

			if(*pEINTPEND & (1 << 19)) /*EINT19---KEY6*/
			{
				led_num(6);
				*pEINTPEND |= (1 << 19);
			}
			*pSRCPND |= (1 << 5);
			*pINTPND |= (1 << 5);
			break;

		case 31: /*ADC*/
			TS_ADC_TC_Irq();
			break;
	}
}

void interrupt_init(void)
{
	/*Enable EINT8_23 in the INTMSK register*/
	*pINTMSK &= INTMSK_CLR_VAL;

	/*Enable Filter, Set Falling edge trigger of
	 *EINT8, EINT11, EINT13, EINT14, EINT15, 
	 *EINT19*/
	*pEXTINT1 &= EXTINT1_MSK;
	*pEXTINT2 &= EXTINT2_MSK;
	*pEXTINT1 |= EXTINT1_SET;
	*pEXTINT2 |= EXTINT2_SET;

	/*Enable EINT8, EINT11, EINT13, EINT14,
	 *EINT15, EINT19*/
	*pEINTMASK &= EINTMASK_CLR_VAL;

	/*Enable Irq in the cpsr*/
	__asm__(
		"mrs r0, cpsr\n"
		"bic r0, #0x80\n"
		"msr cpsr, r0\n"		
	);
}



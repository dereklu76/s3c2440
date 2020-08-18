#include "led.h"

void led_init(void)
{
	*pGPBCON = GPBCON_VAL;
}

void led_on(void)
{
	*pGPBDAT &= (LED1_CLEAR_MASK&LED2_CLEAR_MASK&LED3_CLEAR_MASK&LED4_CLEAR_MASK);
}

void led_off(void)
{
	*pGPBDAT |= (LED1_SET_MASK|LED2_SET_MASK|LED3_SET_MASK|LED4_SET_MASK);
}

void led_num(unsigned char num)
{
	if(num & 0x01)
	{
		/*led1 on*/
		*pGPBDAT &= LED1_CLEAR_MASK;
	}
	else
	{
		/*led1 off*/
		*pGPBDAT |= LED1_SET_MASK;
	}

	if(num & 0x02)
	{
		/*led2 on*/
		*pGPBDAT &= LED2_CLEAR_MASK;
	}
	else
	{
		/*led2 off*/
		*pGPBDAT |= LED2_SET_MASK;
	}

	if(num & 0x04)
	{
		/*led3 on*/
		*pGPBDAT &= LED3_CLEAR_MASK;
	}
	else
	{
		/*led3 off*/
		*pGPBDAT |= LED3_SET_MASK;
	}

	if(num & 0x08)
	{
		/*led4 on*/
		*pGPBDAT &= LED4_CLEAR_MASK;
	}
	else
	{
		/*led4 off*/
		*pGPBDAT |= LED4_SET_MASK;
	}
}



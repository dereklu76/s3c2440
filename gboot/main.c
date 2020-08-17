
#define LED1_GPB5 5
#define LED2_GPB6 6
#define LED3_GPB7 7
#define LED4_GPB8 8

#define LED1_CLEAR_MASK (~(1<<LED1_GPB5))
#define LED2_CLEAR_MASK (~(1<<LED2_GPB6))
#define LED3_CLEAR_MASK (~(1<<LED3_GPB7))
#define LED4_CLEAR_MASK (~(1<<LED4_GPB8))

#define LED1_SET_MASK (1<<LED1_GPB5)
#define LED2_SET_MASK (1<<LED2_GPB6)
#define LED3_SET_MASK (1<<LED3_GPB7)
#define LED4_SET_MASK (1<<LED4_GPB8)

#define pGPBCON ((volatile unsigned long *)0x56000010)
#define pGPBDAT ((volatile unsigned long *)0x56000014)

#define GPBCON_VAL ((1<<16)|(1<<14)|(1<<12)|(1<<10))
#define DELAY_CNT 0xffff

void gboot_delay(void)
{
	int i;

	for(i = 0; i < DELAY_CNT; i++)
	{
	
	}
}

void gboot_main(void)
{
	*pGPBCON = GPBCON_VAL;
	while(1)
	{
		*pGPBDAT &= (LED1_CLEAR_MASK&LED2_CLEAR_MASK&LED3_CLEAR_MASK&LED4_CLEAR_MASK);
		gboot_delay();
		*pGPBDAT |= (LED1_SET_MASK|LED2_SET_MASK|LED3_SET_MASK|LED4_SET_MASK);
		gboot_delay();
	}
}



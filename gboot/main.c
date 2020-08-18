#include "led.h"
#include "button.h"
#include "interrupt.h"

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
	led_init();
	button_init();
	interrupt_init();
	while(1)
	{
//		led_on();
//		gboot_delay();
//		led_off();
//		gboot_delay();
	}
}



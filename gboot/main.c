#include "led.h"
#include "button.h"
#include "interrupt.h"
#include "nandflash.h"
#include "uart.h"
#include "printf.h"

#define DELAY_CNT 0xffff

void gboot_delay(void)
{
	int i;

	for(i = 0; i < DELAY_CNT; i++)
	{
	
	}
}

void error_num(unsigned char num)
{
	while(1)
	{
		led_num(num);
		gboot_delay();
		led_num(0);
		gboot_delay();
	}
}

void gboot_main(void)
{
	int i;
	unsigned char ret;
	unsigned char buf[2048];

	led_init();

	button_init();

	interrupt_init();

	NF_Init();

	Uart0_Init();

	ret = NF_BlockErase(0);
	if(ret)
	{
		error_num(1);
	}

	ret = 0;
	for(i = 0; i < 2048; i++)
	{
		buf[i] = ret++;
	}
	ret = NF_PageWrite(0, buf);
	if(ret)
	{
		error_num(2);
	}

	ret = 1;
	for(i = 0; i < 2048; i++)
	{
		buf[i] = ret++;
	}
	NF_PageRead(0, buf);

	for(i = 0; i < 2048; i++)
	{
		printf("buf[%d]=%x\r\n", i, buf[i]);
	}

	while(1)
	{
//		led_on();
//		gboot_delay();
//		led_off();
//		gboot_delay();
	}
}




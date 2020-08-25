#include "led.h"
#include "button.h"
#include "interrupt.h"
#include "nandflash.h"
#include "uart.h"
#include "printf.h"


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
		printf("NF_BlockErase Error!\r\n");
	}

	ret = 0;
	for(i = 0; i < 2048; i++)
	{
		buf[i] = ret++;
	}
	ret = NF_PageWrite(0, buf);
	if(ret)
	{
		printf("NF_PageWrite Error!\r\n");
	}

	for(i = 0; i < 2048; i++)
	{
		buf[i] = 0;
	}
	NF_PageRead(0, buf);

	printf("NFCONF=%x\r\n", NFCONF);
	printf("NFCONT=%x\r\n", NFCONT);
	printf("NFSTAT=%x\r\n", NFSTAT);

	for(i = 0; i < 2048; i++)
	{
		printf("buf[%d]=%x\r\n", i, buf[i]);
	}

	while(1)
	{
	}
}




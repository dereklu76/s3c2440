#include "led.h"
#include "button.h"
#include "interrupt.h"
#include "nandflash.h"
#include "uart.h"
#include "printf.h"
#include "lcd.h"
#include "touchscreen.h"
#include "dm9000.h"

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

	Lcd_Init();

	TS_Init();

	dm9000_init();

	while(1)
	{
//		Arp_Request();		
	}
}




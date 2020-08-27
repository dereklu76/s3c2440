#include "led.h"
#include "button.h"
#include "interrupt.h"
#include "nandflash.h"
#include "uart.h"
#include "printf.h"
#include "lcd.h"

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

	while(1)
	{
		Lcd_Test();
	}
}




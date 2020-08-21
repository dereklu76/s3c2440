#include "uart.h"


void Uart0_Init(void)
{
	/*GPH3--->RXD0*/
	/*GPH2--->TXD0*/
	GPHCON &= (~(0xf<<4));
	GPHCON |= (0xa<<4);

	/*Normal Mode,N,8,1*/
	ULCON0 = 0x03;

	/*Set Tx and Rx mode to be Interrupt 
	 *request or polling mode.
	 *Select PCLK for the UART baud rate.*/
	UCON0 = 0x05;

	/*Set Baudrate to be 115200bps*/
	/*405 000 000 / 8 / (115200 * 16) - 1*/
	/*26.465*/
	UBRDIV0 = 26;
}



void putc(unsigned char ch)
{
	while((UTRSTAT0 & (1<<2)) == 0);
	UTXH0 = ch;
}


unsigned char getc(void)
{
	while((UTRSTAT0 & (1<<0)) == 0);
	return URXH0;
}





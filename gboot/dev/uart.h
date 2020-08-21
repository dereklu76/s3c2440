#ifndef __UART_H__
#define __UART_H__

#define	ULCON0		(*((volatile unsigned char*)	0x50000000))
#define	UCON0		(*((volatile unsigned short*)	0x50000004))
#define	UFCON0		(*((volatile unsigned char*)	0x50000008))
#define	UTRSTAT0	(*((volatile unsigned char*)	0x50000010))
#define	UERSTAT0	(*((volatile unsigned char*)	0x50000014))
#define	UFSTAT0		(*((volatile unsigned short*)	0x50000018))
#define	UTXH0		(*((volatile unsigned char*)	0x50000020))
#define URXH0		(*((volatile unsigned char*)	0x50000024))
#define UBRDIV0		(*((volatile unsigned short*)	0x50000028))
#define	GPHCON		(*((volatile unsigned long*)	0x56000070))

void Uart0_Init(void);
void putc(unsigned char ch);
unsigned char getc(void);

#endif



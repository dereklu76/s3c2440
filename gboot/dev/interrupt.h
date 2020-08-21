#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define pSRCPND ((volatile unsigned long *)0x4a000000)
#define pINTMSK ((volatile unsigned long *)0x4a000008)
#define pINTPND ((volatile unsigned long *)0x4a000010)
#define pINTOFFSET ((volatile unsigned long *)0x4a000014)

#define pEXTINT0 ((volatile unsigned long *)0x56000088)
#define pEXTINT1 ((volatile unsigned long *)0x5600008c)
#define pEXTINT2 ((volatile unsigned long *)0x56000090)

#define pEINTMASK ((volatile unsigned long *)0x560000a4)
#define pEINTPEND ((volatile unsigned long *)0x560000a8)

#define EINTMASK_EINT8_POS 8
#define EINTMASK_EINT11_POS 11
#define EINTMASK_EINT13_POS 13
#define EINTMASK_EINT14_POS 14
#define EINTMASK_EINT15_POS 15
#define EINTMASK_EINT19_POS 19
#define EINTMASK_CLR_VAL (~((1<<EINTMASK_EINT8_POS)|(1<<EINTMASK_EINT11_POS)|(1<<EINTMASK_EINT13_POS)|(1<<EINTMASK_EINT14_POS)|(1<<EINTMASK_EINT15_POS)|(1<<EINTMASK_EINT19_POS)))

#define INTMSK_EINT8_23 5
#define INTMSK_CLR_VAL (~(1<<INTMSK_EINT8_23))

#define EXTINT1_EINT8_POS 0
#define EXTINT1_EINT11_POS 12
#define EXTINT1_EINT13_POS 20
#define EXTINT1_EINT14_POS 24
#define EXTINT1_EINT15_POS 28
#define EXTINT2_EINT19_POS 12

#define EXTINT1_MSK (~((0xf<<EXTINT1_EINT8_POS)|(0xf<<EXTINT1_EINT11_POS)|(0xf<<EXTINT1_EINT13_POS)|(0xf<<EXTINT1_EINT14_POS)|(0xf<<EXTINT1_EINT15_POS)))
#define EXTINT2_MSK (~(0xf<<EXTINT2_EINT19_POS))

#define EXTINT1_SET ((0xa<<EXTINT1_EINT8_POS)|(0xa<<EXTINT1_EINT11_POS)|(0xa<<EXTINT1_EINT13_POS)|(0xa<<EXTINT1_EINT14_POS)|(0xa<<EXTINT1_EINT15_POS))
#define EXTINT2_SET (0xa<<EXTINT2_EINT19_POS)

void interrupt_init(void);

#endif



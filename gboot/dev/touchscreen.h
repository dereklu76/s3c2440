#ifndef __TOUCHSCREEN_H__
#define __TOUCHSCREEN_H__

#define ADCCON (*((volatile unsigned short*)0x58000000))
#define ADCTSC (*((volatile unsigned short*)0x58000004))
#define ADCDAT0 (*((volatile unsigned short*)0x5800000C))
#define ADCDAT1 (*((volatile unsigned short*)0x58000010))
#define ADCUPDN (*((volatile unsigned char*)0x58000014))

#define SRCPND (*((volatile unsigned long*)0x4a000000))
#define INTMSK (*((volatile unsigned long*)0x4a000008))
#define INTPND (*((volatile unsigned long*)0x4a000010))
#define SUBSRCPND (*((volatile unsigned long*)0x4a000018))
#define INTSUBMSK (*((volatile unsigned long*)0x4a00001c))




void TS_Init(void);
void TS_ADC_TC_Irq(void);

#endif



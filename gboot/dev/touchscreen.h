#ifndef __TOUCHSCREEN_H__
#define __TOUCHSCREEN_H__

#define ADCCON (*((volatile unsigned short*)0x5800000))
#define ADCTSC (*((volatile unsigned short*)0x5800004))
#define ADCDAT0 (*((volatile unsigned short*)0x580000C))
#define ADCDAT1 (*((volatile unsigned short*)0x5800010))
#define ADCUPDN (*((volatile unsigned char*)0x5800014))

#define INTMSK (*((volatile unsigned long*)0x4a000008))
#define INTPND (*((volatile unsigned long*)0x4a000010))
#define SUBSRCPND (*((volatile unsigned long*)0x4a000018))
#define INTSUBMSK (*((volatile unsigned long*)0x4a00001c))




void TS_Init(void);
void TS_ADC_TC_Irq(void);

#endif



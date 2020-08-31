#ifndef __DM9000_H__
#define __DM9000_H__


#define PTK_MAX_LEN 1522
#define DM9000_ID 0x90000a46


#define DM_ADD (*((volatile unsigned short*)0x20000300))
#define DM_DAT (*((volatile unsigned short*)0x20000304))


#define BWSCON (*((volatile unsigned long*)0x48000000))
#define BANKCON4 (*((volatile unsigned long*)0x48000014))
#define GPFCON (*((volatile unsigned long*)0x56000050))
#define EXTINT0 (*((volatile unsigned long*)0x56000088))
#define SRCPND (*((volatile unsigned long*)0x4a000000))
#define INTPND (*((volatile unsigned long*)0x4a000010))
#define INTMSK (*((volatile unsigned long*)0x4a000008))
#define EINTMASK (*((volatile unsigned long*)0x560000a4))
#define EINTPEND (*((volatile unsigned long*)0x560000a8))


#define DM9000_NCR 0x00
#define DM9000_NSR 0x01
#define DM9000_TCR 0x02
#define DM9000_TSR_I 0x03
#define DM9000_TSR_II 0x04
#define DM9000_RCR 0x05
#define DM9000_RSR 0x06
#define DM9000_ROCR 0x07
#define DM9000_BPTR 0x08
#define DM9000_FCTR 0x09
#define DM9000_FCR 0x0a
#define DM9000_EPCR 0x0b
#define DM9000_EPAR 0x0c
#define DM9000_EPDRL 0x0d
#define DM9000_EPDRH 0x0e
#define DM9000_WCR 0x0f
#define DM9000_PAR 0x10
#define DM9000_MAR 0x16
#define DM9000_GPCR 0x1e
#define DM9000_GPR 0x1f
#define DM9000_TRPAL 0x22
#define DM9000_TRPAH 0x23
#define DM9000_RWPAL 0x24
#define DM9000_RWPAH 0x25
#define DM9000_VIDL 0x28
#define DM9000_VIDH 0x29
#define DM9000_PIDL 0x2a
#define DM9000_PIDH 0x2b
#define DM9000_CHIPR 0x2c
#define DM9000_SMCR 0x2f
#define DM9000_MRCMDX 0xf0
#define DM9000_MRCMD 0xf2
#define DM9000_MRRL 0xf4
#define DM9000_MRRH 0xf5
#define DM9000_MWCMDX 0xf6
#define DM9000_MWCMD 0xf8
#define DM9000_MWRL 0xfa
#define DM9000_MWRH 0xfb
#define DM9000_TXPLL 0xfc
#define DM9000_TXPLH 0xfd
#define DM9000_ISR 0xfe
#define DM9000_IMR 0xff


#define GPCR_GPIO0_OUT (1<<0)
#define NCR_LBK_INT_MAC (1<<1)
#define NCR_RST (1<<0)
#define BPTR_BPHW(d) (d<<4)
#define BPTR_JPT_600US (0xf<<0)
#define FCTR_HWOT(d) (d<<4)
#define FCTR_LWOT(d) (d<<0)
#define NSR_WAKEST (1<<5)
#define NSR_TX2END (1<<3)
#define NSR_TX1END (1<<2)
#define ISR_ROOS (1<<3)
#define ISR_ROS (1<<2)
#define ISR_PTS (1<<1)
#define ISR_PRS (1<<0)
#define RCR_DIS_LONG (1<<5)
#define RCR_DIS_CRC (1<<4)
#define RCR_RXEN (1<<0)
#define IMR_PAR (1<<7)
#define TCR_TXREQ (1<<0)




#endif


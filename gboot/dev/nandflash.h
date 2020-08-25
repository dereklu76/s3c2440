#ifndef __NANDFLASH_H__
#define __NANDFLASH_H__

#define NFCONF (*((volatile unsigned short*)0x4e000000))
#define NFCONT (*((volatile unsigned short*)0x4e000004))
#define NFCMMD (*((volatile unsigned char*)0x4e000008))
#define NFADDR (*((volatile unsigned char*)0x4e00000c))
#define NFDATA (*((volatile unsigned char*)0x4e000010))
#define NFSTAT (*((volatile unsigned char*)0x4e000020))

#define NFCONF_TACLS_POS 12
#define NFCONF_TWRPH0_POS 8
#define NFCONF_TWRPH1_POS 4
#define NFCONF_BUSWIDTH_POS 0

#define NFCONF_TACLS_VAL 0
#define NFCONF_TWRPH0_VAL 1
#define NFCONF_TWRPH1_VAL 0
#define NFCONF_BUSWIDTH_VAL 0

#define NFCONF_VAL ((NFCONF_TACLS_VAL<<NFCONF_TACLS_POS)|(NFCONF_TWRPH0_VAL<<NFCONF_TWRPH0_POS) \
		|(NFCONF_TWRPH1_VAL<<NFCONF_TWRPH1_POS)|(NFCONF_BUSWIDTH_VAL<<NFCONF_BUSWIDTH_POS))

#define NFCONT_SoftLock_POS 12
#define NFCONT_nCE_POS 1
#define NFCONT_MODE_POS 0

#define NFSTAT_RnB_Trans_POS 2

void NF_Init(void);
unsigned char NF_BlockErase(unsigned long addr);
void NF_PageRead(unsigned long addr, unsigned char* buf);
unsigned char NF_PageWrite(unsigned long addr, unsigned char* buf);

#endif



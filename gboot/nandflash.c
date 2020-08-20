#include "nandflash.h"

void NF_SelectChip(void)
{
	NFCONT &= (~(1<<NFCONT_nCE_POS));
}

void NF_DeSelectChip(void)
{
	NFCONT |= (1<<NFCONT_nCE_POS);
}

void NF_WaitForRnB(void)
{
	while((NFSTAT&(1<<NFSTAT_RnB_Trans_POS)) == 0);
}

void NF_ClearRnB(void)
{
	NFSTAT |= (1<<NFSTAT_RnB_Trans_POS);
}

void NF_Reset(void)
{
	NF_SelectChip();
	NF_ClearRnB();
	
	/*Send Command 0xff*/
	NFCMMD = 0xff;

	NF_WaitForRnB();

	NF_DeSelectChip();
}

void NF_Init(void)
{
	/*Configure Time Width*/
	NFCONF = NFCONF_VAL;

	/*Enable NAND flash controller*/
	NFCONT |= (1<<NFCONT_MODE_POS);

	/*Disable Soft Lock*/
	NFCONT &= (~(1<<NFCONT_SoftLock_POS));

	NF_Reset();
}

unsigned char NF_BlockErase(unsigned long addr)
{
	unsigned char ret;

	NF_SelectChip();
	NF_ClearRnB();
	NFCMMD = 0x60;
	NFADDR = (unsigned char)(addr>>12);
	NFADDR = (unsigned char)(addr>>20);
	NFADDR = (unsigned char)((addr>>28)&0x1);
	NFCMMD = 0xd0;
	NF_WaitForRnB();
	NFCMMD = 0x70;
	ret = NFDATA;
	NF_DeSelectChip();

	return ret;
}


void NF_PageRead(unsigned long addr, unsigned char* buf)
{
	int i;

	NF_SelectChip();
	NF_ClearRnB();
	NFCMMD = 0x00;
	NFADDR = 0;
	NFADDR = 0;
	NFADDR = (unsigned char)(addr>>12);
	NFADDR = (unsigned char)(addr>>20);
	NFADDR = (unsigned char)((addr>>28)&0x1);
	NFCMMD = 0x30;
	NF_WaitForRnB();
	for(i = 0; i < 2048; i++)
	{
		buf[i] = NFDATA;
	}
	NF_DeSelectChip();
}

unsigned char NF_PageWrite(unsigned long addr, unsigned char* buf)
{
	int i;
	unsigned char ret;

	NF_SelectChip();
	NF_ClearRnB();
	NFCMMD = 0x80;
	NFADDR = 0;
	NFADDR = 0;
	NFADDR = (unsigned char)(addr>>12);
	NFADDR = (unsigned char)(addr>>20);
	NFADDR = (unsigned char)((addr>>28)&0x1);
	for(i = 0; i < 2048; i++)
	{
		NFDATA = buf[i];
	}
	NFCMMD = 0x10;
	NF_WaitForRnB();
	NFCMMD = 0x70;
	ret = NFDATA;
	NF_DeSelectChip();

	return ret;
}



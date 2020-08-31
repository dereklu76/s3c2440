#include "dm9000.h"
#include "printf.h"

unsigned char buffer[1000];
unsigned char mac_addr[6] = {6, 6, 6, 8, 8, 8};

void cs_init(void)
{
	BWSCON &= (~(3<<16));
	BWSCON |= (1<<16);

	BANKCON4 = (0<<13)|(0<<11)|(7<<8)|(1<<6)|(0<<4)|(0<<2)|(0<<0);
}

void dm9000_int_init(void)
{
	GPFCON &= (~(3<<14));
	GPFCON |= (2<<14);

	EXTINT0 &= (~(7<<28));
	EXTINT0 |= (1<<28);

	SRCPND = (1<<4);
	INTPND = (1<<4);

	INTMSK &= (~(1<<4));
	EINTMASK &= (~(1<<7));
}

void dm9000_reg_write(unsigned short reg, unsigned short dat)
{
	DM_ADD = reg;
	DM_DAT = dat;
}

unsigned char dm9000_reg_read(unsigned short reg)
{
	DM_ADD = reg;
	return DM_DAT;
}

void dm9000_reset(void)
{
	dm9000_reg_write(DM9000_GPCR, GPCR_GPIO0_OUT);
	dm9000_reg_write(DM9000_GPR, 0);

	dm9000_reg_write(DM9000_NCR, (NCR_LBK_INT_MAC)|(NCR_RST));
	dm9000_reg_write(DM9000_NCR, 0);


	dm9000_reg_write(DM9000_NCR, (NCR_LBK_INT_MAC)|(NCR_RST));
	dm9000_reg_write(DM9000_NCR, 0);
}

void dm9000_probe(void)
{
	unsigned long id_val;

	id_val = dm9000_reg_read(DM9000_VIDL);
	id_val |= dm9000_reg_read(DM9000_VIDH)<<8;
	id_val |= dm9000_reg_read(DM9000_PIDL)<<16;
	id_val |= dm9000_reg_read(DM9000_PIDH)<<24;

	if(id_val == DM9000_ID)
	{
		printf("dm9000 is found!\r\n");
	}
	else
	{
		printf("dm9000 is not found!\r\n");
	}
}


void dm9000_mac_init(void)
{
	/*Program operating register, only internal phy supported*/
	dm9000_reg_write(DM9000_NCR, 0x0);
	/*TX Polling clear*/
	dm9000_reg_write(DM9000_TCR, 0);
	/*Less 3Kb, 200us*/
	dm9000_reg_write(DM9000_BPTR, BPTR_BPHW(3)|(BPTR_JPT_600US));
	/*Flow Control: High/Low Water*/
	dm9000_reg_write(DM9000_FCTR, FCTR_HWOT(3)|(FCTR_LWOT(8)));
	/*SH FIXME: This looks strange! Flow Control*/
	dm9000_reg_write(DM9000_FCR, 0x0);
	/*Special Mode*/
	dm9000_reg_write(DM9000_SMCR, 0);
	/*clear TX status*/
	dm9000_reg_write(DM9000_NSR, NSR_WAKEST|NSR_TX2END|NSR_TX1END);
	/*Clear interrupt status*/
	dm9000_reg_write(DM9000_ISR, ISR_ROOS|ISR_ROS|ISR_PTS|ISR_PRS);
}

void dm9000_fill_mac(void)
{
	unsigned char i;

	for(i = 0; i < 6; i++)
	{
		dm9000_reg_write(DM9000_PAR+i, mac_addr[i]);
	}
}

void dm9000_activation(void)
{
	dm9000_reg_write(DM9000_RCR, RCR_DIS_LONG|RCR_DIS_CRC|RCR_RXEN);

	/*Enable TX/RX interrupt mask*/
	dm9000_reg_write(DM9000_IMR, IMR_PAR);
}


void dm9000_init(void)
{
	/*initialize chip selection*/
	cs_init();

	/*initialize interrupt*/
	dm9000_int_init();

	/*reset device*/
	dm9000_reset();

	/*search dm9000*/
	dm9000_probe();

	/*mac initialization*/
	dm9000_mac_init();

	/*fill mac address*/
	dm9000_fill_mac();

	/*activate dm9000*/
	dm9000_activation();
}

void dm9000_tx(unsigned char *dat, unsigned short length)
{
	unsigned short i;
	unsigned char status;

	/*Disable interrupt*/
	dm9000_reg_write(DM9000_IMR, 0x80);
	/*write the length of data to be transimited*/
	dm9000_reg_write(DM9000_TXPLL, length & 0xff);
	dm9000_reg_write(DM9000_TXPLH, (length>>8) & 0xff);
	/*write the data to be transimited*/
	DM_ADD = DM9000_MWCMD;
	for(i = 0; i < length; i+= 2)
	{
		DM_DAT = dat[i] | (dat[i+1] << 8);
	}
	/*request transimission*/
	dm9000_reg_write(DM9000_TCR, TCR_TXREQ);
	/*wait for the end of transimission*/
	while(1)
	{
		status = dm9000_reg_read(DM9000_TCR);
		if((status&0x01) == 0)
		{
			break;
		}
	}
	/*clear the pending bit of transimision*/
	dm9000_reg_write(DM9000_NSR, 0x2c);
	/*Restore interrupt enable*/
	dm9000_reg_write(DM9000_IMR, 0x81);
}


unsigned short dm9000_rx(unsigned char *dat)
{
	unsigned char status;
	unsigned short temp, length, i;

	/*Interrupt happened? Clear pending bit*/
	status = dm9000_reg_read(DM9000_ISR);
	if(status & 0x01)
	{
		dm9000_reg_write(DM9000_ISR, 0x01);
	}
	else
	{
		return 0;
	}

	/*Dummy read*/
	dm9000_reg_read(DM9000_MRCMDX);

	/*Read Status*/
	status = dm9000_reg_read(DM9000_MRCMD);

	/*Read package length*/
	length = DM_DAT;

	/*Read package data*/
	if(length < PTK_MAX_LEN)
	{
		for(i = 0; i < length; i+=2)
		{
			temp = DM_DAT;
			dat[i] = (temp & 0xff);
			dat[i+1] = ((temp >> 8) & 0xff);
		}
	}
}


void dm9000_irq_handler(void)
{
	unsigned short len;
	len = dm9000_rx(buffer);

	SRCPND = (1<<4);
	INTPND = (1<<4);
	EINTPEND = (1<<7);
}



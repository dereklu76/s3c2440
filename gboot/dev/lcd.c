#include "lcd.h"

   
unsigned short lcd_buf[240][320] = {0};

void Lcd_Init(void)
{
	int i, j;
	for(i = 0; i < 240; i++)
	{
		lcd_buf[i][0] = ((0x00<<11)|(0x00<<5)|(0x1f<<0)); /*left--->blue*/
		lcd_buf[i][319] = ((0x00<<11)|(0x3f<<5)|(0x00<<0)); /*right--->green*/
	}
	for(i = 0; i < 320; i++)
	{
		lcd_buf[0][i] = ((0x1f<<11)|(0x00<<5)|(0x00<<0)); /*top--->red*/
		lcd_buf[239][i] = ((0x00<<11)|(0x3f<<5)|(0x1f<<0)); /*bottom--->green+blue*/
	}
	/*Initialize the IO Pin to be lcd.*/
	GPCCON = 0xaaaaaaaa;
	GPDCON = 0xaaaaaaaa;
	GPGCON |= (3<<8);

	/*VCLK= , 16bpp TFT, Disable LCD output*/
	LCDCON1 = LCDCON1_VAL;

	/*Set VSPW, VBPD, LINEVAL, VFPD*/
	LCDCON2 = LCDCON2_VAL;

	/*Set HBPD, HOZVAL, HFPD*/
	LCDCON3 = LCDCON3_VAL;

	/*Set HSPW*/
	LCDCON4 = LCDCON4_VAL;

	LCDCON5 = LCDCON5_VAL;	

	/*start address of lcd buffer*/
	LCDSADDR1 = (((unsigned long)lcd_buf)>>1);

	/*end address of lcd buffer*/
	LCDSADDR2 = (((((unsigned long)lcd_buf)+320*240*2)>>1)&0x1fffff);

	LCDSADDR3 = ((0<<11)|(320<<0));

	/*Enable LCD_PWREN output signal*/
	LCDCON5 |= (1<<LCDCON5_PWREN_POS);

	/*Enable video output*/
	LCDCON1 |= (1<<LCDCON1_ENVID_POS);
}


void Lcd_Delay(void)
{
	int i;

	for(i = 0; i < 0xffffff; i++)
	{
	
	}
}


void Lcd_Test(void)
{
	int i, j;

	for(i = 0; i < 240; i++)
	{
		for(j = 0; j < 320; j++)
		{
			lcd_buf[i][j] = ((0x00<<11)|(0x00<<5)|(0x1f<<0));
			Lcd_Delay();
		}
	}

	for(i = 0; i < 240; i++)
	{
		for(j = 0; j < 320; j++)
		{
			lcd_buf[i][j] = ((0x00<<11)|(0x3f<<5)|(0x00<<0));
		}
	}
}



#ifndef __LCD_H__
#define __LCD_H__

#define GPCCON (*((volatile unsigned long*)0x56000020))
#define GPDCON (*((volatile unsigned long*)0x56000030))
#define GPGCON (*((volatile unsigned long*)0x56000060))


#define LCDCON1 (*((volatile unsigned long*)0x4d000000))
#define LCDCON2 (*((volatile unsigned long*)0x4d000004))
#define LCDCON3 (*((volatile unsigned long*)0x4d000008))
#define LCDCON4 (*((volatile unsigned long*)0x4d00000c))
#define LCDCON5 (*((volatile unsigned long*)0x4d000010))
#define LCDSADDR1 (*((volatile unsigned long*)0x4d000014))
#define LCDSADDR2 (*((volatile unsigned long*)0x4d000018))
#define LCDSADDR3 (*((volatile unsigned long*)0x4d00001c))




#define LCDCON1_CLKVAL_POS 8
#define LCDCON1_PNRMODE_POS 5
#define LCDCON1_BPPMODE_POS 1
#define LCDCON1_ENVID_POS 0


#define LCDCON1_CLKVAL_VAL 4     /*video frame frequency 66Hz*/
#define LCDCON1_PNRMODE_VAL 3
#define LCDCON1_BPPMODE_VAL 12
#define LCDCON1_ENVID_VAL 0

#define LCDCON1_VAL ((LCDCON1_CLKVAL_VAL<<LCDCON1_CLKVAL_POS) | \
		(LCDCON1_PNRMODE_VAL<<LCDCON1_PNRMODE_POS) | \
		(LCDCON1_BPPMODE_VAL<<LCDCON1_BPPMODE_POS) | \
		(LCDCON1_ENVID_VAL<<LCDCON1_ENVID_POS))



#define LCDCON2_VBPD_POS 24
#define LCDCON2_LINEVAL_POS 14
#define LCDCON2_VFPD_POS 6
#define LCDCON2_VSPW_POS 0

#define LCDCON2_VBPD_VAL 10
#define LCDCON2_LINEVAL_VAL 239
#define LCDCON2_VFPD_VAL 4
#define LCDCON2_VSPW_VAL 1

#define LCDCON2_VAL ((LCDCON2_VBPD_VAL<<LCDCON2_VBPD_POS)| \
		(LCDCON2_LINEVAL_VAL<<LCDCON2_LINEVAL_POS)| \
		(LCDCON2_VFPD_VAL<<LCDCON2_VFPD_POS)| \
		(LCDCON2_VSPW_VAL<<LCDCON2_VSPW_POS))



#define LCDCON3_HBPD_POS 19
#define LCDCON3_HOZVAL_POS 8
#define LCDCON3_HFPD_POS 0

#define LCDCON3_HBPD_VAL 0x43
#define LCDCON3_HOZVAL_VAL 319
#define LCDCON3_HFPD_VAL 0x04

#define LCDCON3_VAL ((LCDCON3_HBPD_VAL<<LCDCON3_HBPD_POS)| \
		(LCDCON3_HOZVAL_VAL<<LCDCON3_HOZVAL_POS)| \
		(LCDCON3_HFPD_VAL<<LCDCON3_HFPD_POS))



#define LCDCON4_HSPW_POS 0

#define LCDCON4_HSPW_VAL 1

#define LCDCON4_VAL (LCDCON4_HSPW_VAL<<LCDCON4_HSPW_POS)




#define LCDCON5_BPP24BL_POS 12
#define LCDCON5_FRM565_POS 11
#define LCDCON5_INVVCLK_POS 10
#define LCDCON5_INVVLINE_POS 9
#define LCDCON5_INVVFRAME_POS 8
#define LCDCON5_INVVD_POS 7
#define LCDCON5_INVVDEN_POS 6
#define LCDCON5_INVPWREN_POS 5
#define LCDCON5_INVLEND_POS 4
#define LCDCON5_PWREN_POS 3
#define LCDCON5_ENLEND_POS 2
#define LCDCON5_BSWP_POS 1
#define LCDCON5_HWSWP_POS 0

#define LCDCON5_BPP24BL_VAL 0
#define LCDCON5_FRM565_VAL 1
#define LCDCON5_INVVCLK_VAL 1
#define LCDCON5_INVVLINE_VAL 1
#define LCDCON5_INVVFRAME_VAL 1
#define LCDCON5_INVVD_VAL 0
#define LCDCON5_INVVDEN_VAL 0
#define LCDCON5_INVPWREN_VAL 0
#define LCDCON5_INVLEND_VAL 0
#define LCDCON5_PWREN_VAL 0
#define LCDCON5_ENLEND_VAL 0
#define LCDCON5_BSWP_VAL 0
#define LCDCON5_HWSWP_VAL 1

#define LCDCON5_VAL ((LCDCON5_BPP24BL_VAL<<LCDCON5_BPP24BL_POS)| \
		(LCDCON5_FRM565_VAL<<LCDCON5_FRM565_POS)| \
		(LCDCON5_INVVCLK_VAL<<LCDCON5_INVVCLK_POS)| \
		(LCDCON5_INVVLINE_VAL<<LCDCON5_INVVLINE_POS)| \
		(LCDCON5_INVVFRAME_VAL<<LCDCON5_INVVFRAME_POS)| \
		(LCDCON5_INVVD_VAL<<LCDCON5_INVVD_POS)| \
		(LCDCON5_INVVDEN_VAL<<LCDCON5_INVVDEN_POS)| \
		(LCDCON5_INVPWREN_VAL<<LCDCON5_INVPWREN_POS)| \
		(LCDCON5_INVLEND_VAL<<LCDCON5_INVLEND_POS)| \
		(LCDCON5_PWREN_VAL<<LCDCON5_PWREN_POS)| \
		(LCDCON5_ENLEND_VAL<<LCDCON5_ENLEND_POS)| \
		(LCDCON5_BSWP_VAL<<LCDCON5_BSWP_POS)| \
		(LCDCON5_HWSWP_VAL<<LCDCON5_HWSWP_POS))


void Lcd_Init(void);
void Lcd_Test(void);

#endif

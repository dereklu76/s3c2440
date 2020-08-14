

.text
.global _start


@Exception Vector Table
_start:
	b	reset
	ldr	pc,	_undefined_instructions
	ldr	pc,	_software_interrupt
	ldr	pc,	_prefetch_abort
	ldr	pc,	_data_abort
	ldr	pc,	_unused
	ldr	pc,	_irq
	ldr	pc,	_fiq	

_undefined_instructions:
	.word	undefined_instructions
_software_interrupt:
	.word	software_interrupt
_prefetch_abort:
	.word	prefetch_abort
_data_abort:
	.word	data_abort
_unused:
	.word	unused
_irq:
	.word	irq
_fiq:
	.word	fiq

undefined_instructions:
	b .

software_interrupt:
	b .

prefetch_abort:
	b .

data_abort:
	b .

unused:
	b .

irq:
	b .

fiq:
	b .

reset:
	bl set_svc
	bl disable_watchdog
	bl disable_interrupt
	bl disable_mmu
	bl init_pll
	b light_led

set_svc:
	mrs	r0,	cpsr
	bic	r0,	#0x1f
	orr	r0,	#0xd3
	msr	cpsr,	r0
	mov	pc,	lr
	
#define pWTCON	0x53000000
disable_watchdog:
	mov	r0,	#0
	ldr	r1,	=pWTCON
	str	r0,	[r1]
	mov	pc,	lr

#define pINTMSK	0x4a000008
disable_interrupt:
	mvn	r0,	#0
	ldr	r1,	=pINTMSK
	str	r0,	[r1]
	mov	pc,	lr
#define CONTROL_VAL (~((1 << 12)|(1 << 2) | (1 << 0)))

disable_mmu:
	@Invalidate ICache and DCache
	mcr p15, 0, r0, c7, c7, 0
	
	@Disable MMU, ICache and DCache
	mrc p15, 0, r0, c1, c0, 0
	ldr r1, =CONTROL_VAL
	and r0, r0, r1
	mcr p15, 0, r0, c1, c0, 0
	mov pc, lr

#define pCLKDIVN 0x4c000014
#define CLKDIVN_VAL ((2<<1)|(1<<0))
#define iA_OR_nF ((1<<31)|(1<<30))
#define pMPLLCON 0x4c000004
#define MPLLCON_VAL ((127<<12)|(2<<4)|(1<<0))
init_pll:
	@configure the dividing ratio
	@fclk:hclk:pclk
	@1:4:8
	ldr r0, =pCLKDIVN
	ldr r1, =CLKDIVN_VAL
	str r1, [r0]

	@set cpu bus mode to asynchronous mode
	mrc p15, 0, r0, c1, c0, 0
	ldr r1, =iA_OR_nF
	orr r0, r0, r1
	mcr p15, 0, r0, c1, c0, 0
	
	@set pll
	ldr r0, =pMPLLCON
	ldr r1, =MPLLCON_VAL
	str r1, [r0]
	
	@return from init_pll
	mov pc, lr

	

#define LED1_GPB5 5
#define LED2_GPB6 6
#define LED3_GPB7 7
#define LED4_GPB8 8

#define LED1_CLEAR_MASK (~(1<<LED1_GPB5))
#define LED2_CLEAR_MASK (~(1<<LED2_GPB6))
#define LED3_CLEAR_MASK (~(1<<LED3_GPB7))
#define LED4_CLEAR_MASK (~(1<<LED4_GPB8))

#define LED1_SET_MASK (1<<LED1_GPB5)
#define LED2_SET_MASK (1<<LED2_GPB6)
#define LED3_SET_MASK (1<<LED3_GPB7)
#define LED4_SET_MASK (1<<LED4_GPB8)

#define pGPBCON 0x56000010
#define pGPBDAT 0x56000014

#define GPBCON_VAL ((1<<16)|(1<<14)|(1<<12)|(1<<10))
#define DELAY_CNT 0xffff
light_led:
	@set the led port to be output
	ldr r0, =pGPBCON
	ldr r1, =GPBCON_VAL
	str r1, [r0]
led_loop:
	@turn on the led
	ldr r0, =pGPBDAT
	ldr r1, =(LED1_CLEAR_MASK&LED3_CLEAR_MASK)
	str r1, [r0]

	@delay
	ldr r0, =DELAY_CNT
	bl led_delay

	@turn off the led
	ldr r0, =pGPBDAT
	ldr r1, =(LED1_SET_MASK|LED3_SET_MASK)
	str r1, [r0]
	
	@delay
	ldr r0, =DELAY_CNT
	bl led_delay

	@loop
	b led_loop

led_delay:
	cmp r0, #0
	beq delay_end
	sub r0, r0, #1
	b led_delay
delay_end:
	mov pc, lr



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
	sub lr, lr, #4
	push {r0-r12, lr}
	bl irq_handler
	pop {r0-r12, pc}

fiq:
	b .

reset:
	bl set_svc
	bl disable_watchdog
	bl disable_interrupt
	bl disable_mmu
	bl init_pll
	bl init_sdram
	bl copy_to_sdram
	bl init_stack
	bl clear_bss
	ldr pc, =gboot_main
@	b light_led

#define STACK_HEAD_IRQ 0x33000000
#define STACK_HEAD_SVC 0x34000000
init_stack:
	@Enter irq mode
	mrs r0, cpsr
	bic r0, r0, #0x1f
	and r0, r0, #0x12
	msr cpsr, r0

	@Set r13_irq
	ldr sp, =STACK_HEAD_IRQ

	@Enter svc mode
	mrs r0, cpsr
	bic r0, r0, #0x1f
	and r0, r0, #0x13
	msr cpsr, r0

	@Set r13_svc
	ldr sp, =STACK_HEAD_SVC
	mov pc, lr

clear_bss:
	ldr r0, =0x00000000
	ldr r1, =_bss_start
	ldr r2, =_bss_end
clear_loop:
	cmp r1, r2
	beq clear_end
	str r0, [r1]
	add r1, r1, #4
	b clear_loop
clear_end:
	mov pc, lr


copy_to_sdram:
	ldr r0, =0x30008000 @dst
	ldr r1, =0x00000000 @src
	ldr r2, =_bss_end @dst end
copy_loop:
	cmp r0, r2
	beq copy_end
	ldr r3, [r1]
	str r3, [r0]
	add r0, r0, #4
	add r1, r1, #4
	b copy_loop
copy_end:
	mov pc, lr


#define pBWSCON 0x48000000
#define BWSCON_VAL ((2<<28)|(2<<24))
#define pBANKCON6 0x4800001c
#define pBANKCON7 0x48000020
#define BANKCON_VAL ((3<<15)|(1<<0))
#define pREFRESH 0x48000024
#define REFRESH_VAL (1<<23)
#define pBANKSIZE 0x48000028
#define BANKSIZE_VAL ((1<<7)|(1<<5)|(1<<4)|(1<<0))
#define pMRSRB6 0x4800002c
#define pMRSRB7 0x48000030
#define MRSRB_VAL (2<<4)
init_sdram:
	ldr r0, =pBWSCON
	ldr r1, =BWSCON_VAL
	str r1, [r0]

	ldr r0, =pBANKCON6
	ldr r1, =BANKCON_VAL
	str r1, [r0]

	ldr r0, =pBANKCON7
	ldr r1, =BANKCON_VAL
	str r1, [r0]

	ldr r0, =pREFRESH
	ldr r1, =REFRESH_VAL
	str r1, [r0]

	ldr r0, =pBANKSIZE
	ldr r1, =BANKSIZE_VAL
	str r1, [r0]

	ldr r0, =pMRSRB6
	ldr r1, =MRSRB_VAL
	str r1, [r0]

	ldr r0, =pMRSRB7
	ldr r1, =MRSRB_VAL
	str r1, [r0]

	mov pc, lr

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

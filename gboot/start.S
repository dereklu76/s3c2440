

.text
.global _start


@Exception Vector Table
_start:
	ldr	pc,	_reset
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
_reset:
	.word	reset

undefined_instructions:
	b	.

software_interrupt:
	b	.

prefetch_abort:
	b	.

data_abort:
	b	.

unused:
	b	.

irq:
	b	.

fiq:
	b	.

reset:
	bl	set_svc
	bl	disable_watchdog
	bl	disable_interrupt
	bl	disable_mmu
	b	.

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
	mov	pc,	lr



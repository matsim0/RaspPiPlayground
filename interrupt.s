.section .text
.align 3

.globl IRQ_Handler	@; taken from arm manual
IRQ_Handler:
	sub 	lr, lr, #4
	stmfd 	sp!,{lr}			@; store IRQ mode's link register 
    mrs 	r14, spsr		
	stmfd 	sp!, {r14}			@; store IRQ_spsr 
	
	bl		identify_and_clear_source
	
    @; cpsie	i               	@; Enable IRQ
	msr 	cpsr_c, #0x1f		@; switch to system-mode, re-enable interrupts
	stmfd 	sp!, {r0-r3, lr}	@; save lr and changeable registers on system/user? mode stack
	
    bl		C_irq_handler
	
	ldmfd	sp!, {r0-r3, lr}	@; restore system/user mode registers
	msr 	cpsr_c, #0x92		@; switch to IRQ mode, disable interrupts
	@; cpsid 	i                   @; Disable IRQ
	
	ldmfd 	sp!, {r14}			@; get r14 for spsr settings
	msr 	spsr_f, r14			@; restore spsr settings

	ldmfd 	sp!, {pc}^	@; return from IRQ, ^ copies spsr to cpsr, so restores mode which was interrupted

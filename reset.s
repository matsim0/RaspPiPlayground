.section .init		@ landet an 0x8000
.globl _start
_start:
IRQ_VEC:
	LDR pc, Reset_Addr
	LDR pc, Undefined_Addr
	LDR pc, SVC_Addr
	LDR pc, Prefetch_Addr
	LDR pc, Abort_Addr
	NOP                    @ Reserved vector
	LDR pc, IRQ_Addr
	ldr pc, FIQ_Addr

Reset_Addr:     
	.word reset_handler		@ (ist auch startup code)
Undefined_Addr: 
	nop						
SVC_Addr:
    nop
Prefetch_Addr:
	nop
Abort_Addr:
	nop
	nop
IRQ_Addr:
    .word IRQ_Handler
FIQ_Addr:
	nop

reset_handler:
	mov r0, #0x0
	mov r1, #0x8000
	mov r2, #0x40
loop$:						@ kopiert IRQ_VEC an 0x0
	subs r2, #4
	ldr r3, [r1, r2]
	str r3, [r0, r2]
	blo loop$				@ branch, wenn carry-flag nicht gesetzt
	
	;@ (PSR_IRQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD2
    msr cpsr_c,r0
    mov sp,#0x8000

    ;@ (PSR_FIQ_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD1
    msr cpsr_c,r0
    mov sp,#0x4000

    ;@ (PSR_SVC_MODE|PSR_FIQ_DIS|PSR_IRQ_DIS)
    mov r0,#0xD3
    msr cpsr_c,r0
    mov sp,#0x8000000

    ;@ SVC MODE, IRQ ENABLED, FIQ DIS
    ;@mov r0,#0x53
    ;@msr cpsr_c, r0	
	
	bl irq_setup			@ IRQ Setup 
	
	@ cpsie i           		@ Enable IRQ
	bl enable_irq
	bl main

.globl enable_irq
enable_irq:
    mrs r0,cpsr
    bic r0,r0,#0x80
    msr cpsr_c,r0
    bx lr
@; Reset Handler installs interrupt vector table after startup - mainly taken from dwelch67's blinker examples,
@; e.g.: https://github.com/dwelch67/raspberrypi/blob/master/blinker07/vectors.s

.section .init				;@ will be put to 0x8000
.globl _start
_start:
IRQ_VEC:
	LDR pc, Reset_Addr
	LDR pc, Undefined_Addr
	LDR pc, SVC_Addr
	LDR pc, Prefetch_Addr
	LDR pc, Abort_Addr
	NOP                    	;@ Reserved vector
	LDR pc, IRQ_Addr
	ldr pc, FIQ_Addr

Reset_Addr:     
	.word reset_handler		;@ (is also startup code)
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
	@; copy irq table from 0x8000-0x8040 to 0x0-0x40
	mov r0, #0x8000
	mov r1, #0x0
	ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}
    ldmia r0!,{r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!,{r2,r3,r4,r5,r6,r7,r8,r9}	
	
	;@ Bit 7, 6 set to disable irq, fiq, bit 5 cleared (no Thumb mode), bit 4-0 to 10010 for IRQ mode: 11010010
    mov r0,#0xd2
    msr cpsr_c,r0
    mov sp,#0x8000

	;@ Bit 7, 6 set to disable irq, fiq, bit 5 cleared (no Thumb mode), bit 4-0 to 10001 for FIQ mode: 11010001
    mov r0,#0xd1
    msr cpsr_c,r0
    mov sp,#0x4000

	;@ Bit 7, 6 set to disable irq, fiq, bit 5 cleared (no Thumb mode), bit 4-0 to 11111 for System mode: 11011111
    mov r0,#0xdf
    msr cpsr_c,r0
    mov sp,#0x8000000

	b main

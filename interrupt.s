.section .text
.align 3

.globl IRQ_Handler
IRQ_Handler:
    SUB         lr, lr, #4
    SRSDB       sp!,#31          @ Save LR_irq and SPSR_irq to System mode stack
    CPS #031                     @ Switch to System mode
    PUSH        {R0-R3,R12}      @ Store other AAPCS registers
    AND         R1, sp, #4
    SUB         sp, sp, R1
    PUSH        {R1, lr}
    BL          identify_and_clear_source
    CPSIE       i                @ Enable IRQ
    BL          C_irq_handler
    CPSID i                      @ Disable IRQ
    POP         {R1,lr}
    ADD         sp, sp, R1
    POP         {R0-R3, R12}     @ Restore registers
    RFEIA       sp!              @ Return using RFE from System mode stack

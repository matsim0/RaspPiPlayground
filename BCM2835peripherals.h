#ifndef BCM2835peripherals_H
#define BCM2835peripherals_H
	
#define GP_BASE 0x20200000
#define GPFSEL0 GP_BASE
#define GPFSEL1 (GP_BASE + 0x4)
#define GPSET0 (GP_BASE + 0x1c)
#define GPCLR0 (GP_BASE + 0x28)

// System Timer runs with 1 MHz
#define SYSTIM_BASE 0x20003000
#define SYSTIM_CS (SYSTIM_BASE)
#define SYSTIM_CLO (SYSTIM_BASE + 0x4)
#define SYSTIM_CHI (SYSTIM_BASE + 0x8)
#define SYSTIM_C0 (SYSTIM_BASE + 0xc)
#define SYSTIM_C1 (SYSTIM_BASE + 0x10)
#define SYSTIM_C2 (SYSTIM_BASE + 0x14)
#define SYSTIM_C3 (SYSTIM_BASE + 0x18)

// 500ms TIMER
#define TIME_TICK 500000 

// Arm Timer depends on processor clock -> can be slower to save power!
#define TIMER_BASE 0x2000b000
#define TIMER_LOAD (TIMER_BASE + 0x400)
#define TIMER_VALUE (TIMER_BASE + 0x404)
#define TIMER_CONTROL (TIMER_BASE + 0x408)
#define TIMER_IRQACK (TIMER_BASE + 0x40C)
#define TIMER_RAWIRQ (TIMER_BASE + 0x410)
#define TIMER_MASKEDIRQ (TIMER_BASE + 0x414)
#define TIMER_RELOAD (TIMER_BASE + 0x418)

#define IRQ_BASE 0x2000b000
#define IRQ_BASIC_PENDING (IRQ_BASE + 0x200)
#define IRQ_PENDING1 (IRQ_BASE + 0x204)
#define IRQ_PENDING2 (IRQ_BASE + 0x208)
#define FIQ_CONTROL (IRQ_BASE + 0x20c)
#define IRQ_ENABLE1 (IRQ_BASE + 0x210)
#define IRQ_ENABLE2 (IRQ_BASE + 0x214)
#define IRQ_BASIC_ENABLE (IRQ_BASE + 0x218)
#define IRQ_DISABLE1 (IRQ_BASE + 0x21c)
#define IRQ_DISABLE2 (IRQ_BASE + 0x220)
#define IRQ_BASIC_DISABLE (IRQ_BASE + 0x224)
	
#endif
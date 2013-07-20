#include "BCM2835peripherals.h"
#include "typedefs.h"

extern void enable_irq(void);

int main()
{
	volatile uint32_T* systimer_clo; 
	volatile uint32_T* systimer_cs;
	uint32_T* systimer_c1;	
	uint32_T* irq_enable1;
	uint32_T* gpiocntrl;
	
	gpiocntrl = (uint32_T*) GPFSEL1;
	
	systimer_cs = (volatile uint32_T*) SYSTIM_CS;
	systimer_clo = (volatile uint32_T*) SYSTIM_CLO;
	systimer_c1 = (uint32_T*) SYSTIM_C1;

	irq_enable1 = (uint32_T*) IRQ_ENABLE1;
	
	// Set gpio 16 to output
	*gpiocntrl = 1<<18;
	
	// Activate system timer c1
	*systimer_c1 = *systimer_clo + TIME_TICK;
	*systimer_cs = 0x2;
	// Enable Interrupts for system timer c1
	*irq_enable1 = 0x2; 
	// Enable Interrupts on ARM
	enable_irq();
		
	while(1);
	return 1;
}

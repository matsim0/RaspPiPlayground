#include "BCM2835peripherals.h"
#include "typedefs.h"

void irq_setup(void)
{
	// setup system timer und interrupt
	volatile uint32_T* systimer_clo; 
	uint32_T* systimer_cs;
	uint32_T* systimer_c1;
	uint32_T* irq_enable1;
	
	systimer_clo = (volatile uint32_T*) SYSTIM_CLO;
	systimer_cs = (uint32_T*) SYSTIM_CS;
	systimer_c1 = (uint32_T*) SYSTIM_C1;
	irq_enable1 = (uint32_T*) IRQ_ENABLE1;
	
	// Load Timer (Compare Register 1) with tick:
	*systimer_c1 = *systimer_clo + TIME_TICK;
	// enable system timer 1 as irq input (ist in beschreibung nicht drin, sollte aber IRQ0 sein)
	*irq_enable1 = 0x2; 
	// Enable next interrupt by clearing pending bit:
	*systimer_cs = 0x2;
}

void C_irq_handler(void)
{
	//while(1); // stop everything!
}

void identify_and_clear_source(void)
{
}
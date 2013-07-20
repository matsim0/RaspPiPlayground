#include "BCM2835peripherals.h"
#include "typedefs.h"

// 5s TIMER
#define TIME_TICK 5000000 

void irq_setup(void)
{
	// setup system timer und interrupt
	volatile uint32_T* timpointer; 
	uint32_T* pointer;
	// Load Timer (Compare Register 0) with tick:
	pointer = (uint32_T*) SYSTIM_C0;
	timpointer = (volatile uint32_T*) SYSTIM_CLO;
	*pointer = *timpointer + TIME_TICK;
	// enable system timer 0 as irq input (ist in beschreibung nicht drin, sollte aber IRQ0 sein)
	pointer = (uint32_T*) IRQ_ENABLE1;
	*pointer = 0x1; 
	// Enable next interrupt by clearing pending bit:
	pointer = (uint32_T*) SYSTIM_CS;
	*pointer = 0x1;
}

void C_irq_handler(void)
{
	while(1); // stop everything!
}

void identify_and_clear_source(void)
{
}
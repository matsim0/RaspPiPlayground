#include "BCM2835peripherals.h"
#include "typedefs.h"

uint8_T pinstate;

void identify_and_clear_source(void)
{
}

void C_irq_handler(void)
{
	// at the moment, only timer interrupt #1 needs to be acked
	volatile uint32_T* systimer_clo; 
	volatile uint32_T* systimer_cs;
	uint32_T* systimer_c1;
	uint32_T* gpioclear;
	uint32_T* gpioset;

	systimer_cs = (volatile uint32_T*) SYSTIM_CS;
	systimer_clo = (volatile uint32_T*) SYSTIM_CLO;
	systimer_c1 = (uint32_T*) SYSTIM_C1;

	gpioclear = (uint32_T*) GPCLR0;
	gpioset = (uint32_T*) GPSET0;

	// Load Timer (Compare Register 1) with tick:
	*systimer_c1 = *systimer_clo + TIME_TICK;
	// Re-Enable Interrupts
	*systimer_cs = 0x2;	

	if (pinstate) {
		// Clear Pin 16 (sets ACT)
		*gpioclear = 1<<16;	
	} else {
		*gpioset = 1<<16;
	}
	pinstate = !pinstate;

}


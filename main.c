#include "BCM2835peripherals.h"
#include "typedefs.h"

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void enable_irq(void);

void timer_wait(uint32_T waittime)
{
	volatile uint32_T* timerlo;
	uint32_T starttime;
	uint32_T difftime;
	uint32_T acttime;
	timerlo = (volatile uint32_T*) SYSTIM_CLO;
	starttime = *timerlo;
	do {
		acttime = *timerlo;
		difftime = acttime - starttime;			
	} while (difftime <= waittime);
}

int main()
{
	uint32_T* gpiocntrl;
	uint32_T* gpioset;
	uint32_T* gpioclear;
	volatile uint32_T* systimer_clo; 
	volatile uint32_T* systimer_cs;
	uint32_T* systimer_c1;	
	uint32_T* irq_enable1;
	uint32_T* irq_pending1;
	uint32_T bit16 = 1<<16;
	uint32_T i;
	uint32_T rx, ra;
	
	gpiocntrl = (uint32_T*) GPFSEL1;
	gpioset = (uint32_T*) GPSET0;
	gpioclear = (uint32_T*) GPCLR0;
	
	systimer_cs = (volatile uint32_T*) SYSTIM_CS;
	systimer_clo = (volatile uint32_T*) SYSTIM_CLO;
	systimer_c1 = (uint32_T*) SYSTIM_C1;

	irq_enable1 = (uint32_T*) IRQ_ENABLE1;
	irq_pending1 = (uint32_T*) IRQ_PENDING1;
	
	// Set gpio 16 to output
	*gpiocntrl = 1<<18;
	
	// in any case, set systimer new
	
	*systimer_c1 = *systimer_clo + TIME_TICK;
	*systimer_cs = 0x2;
	*irq_enable1 = 0x2; 
	// enable_irq();
		
	while(1) 
	{
		// Clear Pin 16 (sets ACT)
		*gpioclear = 1<<16;
		// Wait for 250000 us
		timer_wait(250000);
		// Set Pin 16 (clears ACT)
		*gpioset = 1<<16;
		// Wait again for a _long_ time
		timer_wait(250000);
		// Check if irq pending register is set
		if (*irq_pending1 & 0x2) while(1);
	}
	return 1;
}

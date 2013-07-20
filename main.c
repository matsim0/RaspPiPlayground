#include "BCM2835peripherals.h"
#include "typedefs.h"

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
//		if (acttime >= starttime)
			difftime = acttime - starttime;
//		else
//			difftime = starttime - acttime;
			
	} while (difftime <= waittime);
}

int main()
{
	uint32_T* gpiocntrl;
	uint32_T* gpioset;
	uint32_T* gpioclear;
	uint32_T bit16 = 1<<16;
	uint32_T i;
	
	gpiocntrl = (uint32_T*) GPFSEL1;
	gpioset = (uint32_T*) GPSET0;
	gpioclear = (uint32_T*) GPCLR0;
	
	// Set gpio 16 to output
	*gpiocntrl = 1<<18;
	
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
	}
	return 1;
}

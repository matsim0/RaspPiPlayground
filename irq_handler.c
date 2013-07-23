#include "BCM2835peripherals.h"
#include "typedefs.h"
#include "drawing.h"
#include "queue.h"	

uint8_T pinstate;

void identify_and_clear_source(void)
{
	// at the moment, only timer interrupt #1 needs to be handled
	volatile uint32_T* systimer_clo; 
	volatile uint32_T* systimer_cs;
	uint32_T* systimer_c1;

	systimer_cs = (volatile uint32_T*) SYSTIM_CS;
	systimer_clo = (volatile uint32_T*) SYSTIM_CLO;
	systimer_c1 = (uint32_T*) SYSTIM_C1;

	// Load Timer (Compare Register 1) with tick:
	*systimer_c1 = *systimer_clo + TIME_TICK;
	// Re-Enable Interrupts
	*systimer_cs = 0x2;	
}

uint32_T rnd;
uint16_T x;
uint16_T y;

void C_irq_handler(void)
{
	uint32_T* gpioclear;
	uint32_T* gpioset;
	//uint16_T x;
	//uint16_T y;
	real32_T y_raw;
	uint32_T message;

	gpioclear = (uint32_T*) GPCLR0;
	gpioset = (uint32_T*) GPSET0;

//	if ( (rnd * TIME_TICK) % 100000 == 0) {	// every 100ms, change pinstate
		if (pinstate) {
			// Clear Pin 16 (sets ACT)
			*gpioclear = 1<<16;	
		} else {
			*gpioset = 1<<16;
		}
		pinstate = !pinstate;
//	}
	
/*	rnd = Random(rnd);
	if (rnd >= 0x10000)
		y++;
	else
		y--;
	if (y >= YW)
		y = YW-1;
	if (y < 0)
		y = 0;
	
	x = (x+1)%XW;
*/
	
	rnd++;
	x = (uint16_T)(rnd % XW); 
	y = (uint16_T)(rnd % YW); // sawtooth
	
	// Write "measurement value" and "time value" to queue, lower 16 bits are x, higher 16 bits are y
	message = (uint32_T)x | ((uint32_T)y <<16);
	writeQueue(0, message);
}


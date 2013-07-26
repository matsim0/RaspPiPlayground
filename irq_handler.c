#include "BCM2835peripherals.h"
#include "typedefs.h"
#include "drawing.h"
#include "queue.h"	
#include "system.h"

uint8_T pinstate;
uint32_T systick;

void identify_and_clear_source(void)
{
	// at the moment, only timer interrupt #1 needs to be handled
	volatile uint32_T* systimer_clo = (volatile uint32_T*) SYSTIM_CLO;
	volatile uint32_T* systimer_cs = (volatile uint32_T*) SYSTIM_CS;
	uint32_T* systimer_c1 = (uint32_T*) SYSTIM_C1;

	// Load Timer (Compare Register 1) with tick:
	*systimer_c1 = *systimer_clo + TIME_TICK;
	// Re-Enable Interrupts
	*systimer_cs = 0x2;	
}

int32_T y_old;	// ok, static should be used...

// Gets called every TIME_TICK timer ticks (timer ticks in us)
void C_irq_handler(void)
{
	uint32_T* gpioclear = (uint32_T*) GPCLR0;;
	uint32_T* gpioset = (uint32_T*) GPSET0;;
	volatile uint32_T* systimer_clo = (volatile uint32_T*) SYSTIM_CLO;
	volatile uint32_T* systimer_chi = (volatile uint32_T*) SYSTIM_CHI;
	uint32_T x;
	int32_T y;
	int32_T u;
	uint32_T message[QUEUE_DIM];

	systick++;
	
	if ( systick % (100 * 1000/TIME_TICK) == 0) {	// every 100ms, change pinstate
		if (pinstate) {
			// Clear Pin 16 (sets ACT)
			*gpioclear = 1<<16;	
		} else {
			*gpioset = 1<<16;
		}
		pinstate = !pinstate;
	}
	
	x = (uint32_T)(systick * TIME_TICK/1000); // x is time in 1ms, systick is in TIME_TICK us
	
	// y is sawtooth
	// y = (uint16_T)(rnd % YW); 
	
	// y is PT1 every 200 ms with T = 70ms
	if ( (x % 400) > 200) {
		u = 0;
	} else {
		u = YW-1;
	}
	// T should be 70 ms, dt is 10ms -> T* is 1/(T/dt + 1) = 1/8
	// For other values, we need to consider scaling the values, e.g. T = 30ms, dt = 1ms => T* = 31:
	// We don't want to divide _or_ use floating point, therefore use a 32bit scaling that 
	// 1.) can represent 1/31 fairly well
	// 2.) can represent the highest value of YW = 480 and the lowest value of 0
	// 3.) uses a divider of 2^n
	// using 480 as highest number, 512 is the next power of 2. using int32, 2^31/2^5 = 2^26 represents a 1.
	// This should be more than sufficient for our needs: 1/31 is then 
	// represented by floor(2^26/31) = 2164802. 2164802/2^26 is 0,0322580636..; 1/31 is 0.0322580645...
	y = (u - y_old)/8 + y_old;
	y_old = y;
	
	// Write "measurement value" and "time value" to queue
	message[0] = x;
	message[1] = (uint32_T)y;
	//message[1] = (uint32_T)u;
	writeQueue(0, message);
}


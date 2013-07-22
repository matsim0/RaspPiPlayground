#include "BCM2835peripherals.h"
#include "typedefs.h"
#include "framebuffer.h"
#include <stdio.h>
#include <math.h>

#define XW 640
#define YW 480

#define ENABLE_IRQ asm("cpsie i")
#define DISABLE_IRQ asm("cpsid i")

int main()
{
	volatile uint32_T* systimer_clo = (volatile uint32_T*) SYSTIM_CLO; 
	volatile uint32_T* systimer_cs = (volatile uint32_T*) SYSTIM_CS;
	uint32_T* systimer_c1 = (uint32_T*) SYSTIM_C1;	
	uint32_T* irq_enable1 = (uint32_T*) IRQ_ENABLE1;
	uint32_T* gpiocntrl = (uint32_T*) GPFSEL1;
	uint32_T* gpioclear = (uint32_T*) GPCLR0;
	
	FrameBufferInfo_T* fbInfoAddr;
	
	// Set gpio 16 to output
	*gpiocntrl = 1<<18;
	
	// Activate system timer c1
	*systimer_c1 = *systimer_clo + TIME_TICK;
	*systimer_cs = 0x2;
	// Enable Interrupts for system timer c1
	*irq_enable1 = 0x2; 

	// Initialise Frame Buffer
	fbInfoAddr = InitialiseFrameBuffer(XW, YW, 16);	
	
	if (fbInfoAddr == NULL)
	{	
		// signal error by lighting ACT and stopping
		*gpioclear = 1<<16;
		while(1);
	}
	
	SetGraphicsAddress(fbInfoAddr);
	
	// Enable Interrupts on ARM
	ENABLE_IRQ;

	SetForeColour(0xffff);
	DrawLine(0,0,639,0);
	//DrawLine(0,10,639,10);
	//DrawLine(0,20,639,30);
	
	while(1) {
		// 16bit colour:
		uint16_T colour;
		uint32_T x;
		uint32_T y;
		uint32_T x_old;
		uint32_T y_old;
		uint32_T rnd;
		
		rnd++;
		
		y = Random(rnd);
		
		x = rnd % XW; 
		y = y>>23;
		
		SetForeColour(colour--);
		DrawLine(x_old, y_old, x, y);
		
		x_old = x;
		y_old = y;
	};
	return 1;
}

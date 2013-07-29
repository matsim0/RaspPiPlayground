#include "BCM2835peripherals.h"
#include "typedefs.h"
#include "framebuffer.h"
#include "drawing.h"
#include "queue.h"
#include <stddef.h>
#include <math.h>
#include "system.h"
#include "tags.h"

#define STRBUFLENGTH 2000

int main()
{
	volatile uint32_T* systimer_clo = (volatile uint32_T*) SYSTIM_CLO; 
	volatile uint32_T* systimer_cs = (volatile uint32_T*) SYSTIM_CS;
	uint32_T* systimer_c1 = (uint32_T*) SYSTIM_C1;	
	uint32_T* irq_enable1 = (uint32_T*) IRQ_ENABLE1;
	uint32_T* gpiocntrl = (uint32_T*) GPFSEL1;
	uint32_T* gpioclear = (uint32_T*) GPCLR0;
	
	FrameBufferInfo_T* fbInfoAddr;

	uint32_T* tag_cmdline;
	
	uint32_T ii;
	uint8_T output[] = "Test Eins\n\t1 23 45";
	
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

	SetForeColour(0xffff);
	DrawLine(0,0,XW-1,0);
	DrawLine(0,10,XW-1,10);
	clearScreen();
	
	for (ii = 0; ii < 26; ii++)
		DrawCharacter(0x41+ii, ii*8, 0);				
	for (ii = 0; ii < 26; ii++)
		DrawCharacter(0x41+ii, 4 + ii*8, 16);				

	DrawLine(0,50,XW-1,30);
	
	DrawString(output, 17, 20, YW/2);
	
	clearScreen();
	
	// Find cmdline tag
	tag_cmdline = FindTag(9);
	DrawString((uint8_T*)(tag_cmdline+2), (*tag_cmdline) - 2, 0, 0);
	
	// Enable Interrupts on ARM
	ENABLE_IRQ;

	// wait until sytick reaches 5 ms
	while(systick < 5000000/TIME_TICK);
	
	while(1) {
		uint16_T x;
		uint16_T y;
		uint16_T x_old;
		uint16_T y_old;
		uint32_T colour;
		uint32_T error;
		uint32_T message[QUEUE_DIM];
		
		if (readQueue(0, message)) {
			x = message[0] % XW;		// time in ms: 1ms is 1 px, wrapped around screen width
			y = message[1];
			if (x > x_old) {
				DrawLine(x_old, y_old, x, y);
			} else {
				clearScreen();
				SetForeColour(colour);
				colour--;
				for (ii = 0; ii < 64; ii++)
					DrawCharacter(0x41+ii, ii*8, 0);				
			}

			x_old = x;
			y_old = y;	
		}

	};
	return 1;
}

#ifndef SYSTEM_H
#define SYSTEM_H

#include "typedefs.h"

// Screen Resolution
#define XW 320
#define YW 240

// 10ms TIMER Task
#define TIME_TICK 10000

// Interrupt Handling
#define ENABLE_IRQ asm("cpsie i")
#define DISABLE_IRQ asm("cpsid i")
	
uint32_T systick;
	
#endif
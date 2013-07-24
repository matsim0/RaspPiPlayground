#ifndef QUEUE_H
#define QUEUE_H

#include "typedefs.h"

#define QUEUE_LENGTH 100
#define NUM_QUEUES 2
#define QUEUE_DIM 2

void writeQueue(uint32_T queue, uint32_T value[]);
uint32_T readQueue(uint32_T queue, uint32_T value[]);
	
#endif
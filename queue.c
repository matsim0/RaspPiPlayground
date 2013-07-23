#include "queue.h"
#include "typedefs.h"

// simple implementation of measurement queues
// interrupt handler fills queue, main.c reads from queue

// Queues
uint32_T Q[QUEUE_LENGTH][NUM_QUEUES];

// "pointers" to actual queue position
uint32_T read_q[NUM_QUEUES];
uint32_T write_q[NUM_QUEUES];

// Writes Value in Queue queue
void writeQueue(uint32_T queue, uint32_T value)
{
	// Wrap around (no handling of overwriting not yet read values!)
	if (write_q[queue] < QUEUE_LENGTH-1)
		write_q[queue]++;
	else
		write_q[queue] = 0;

	Q[write_q[queue]][queue] = value;
}

// Read Value from Queue queue; 
uint32_T readQueue(uint32_T queue, uint32_T* value)
{
	// check if read_q == write_q
	if (read_q[queue] != write_q[queue]) {
		*value = Q[read_q[queue]][queue];
		// Increase read counter, wrapping around
		if (read_q[queue] < QUEUE_LENGTH-1)
			read_q[queue]++;
		else
			read_q[queue] = 0;
		return 1;
	} else {
		return 0;
	}

}

// implementation of postman.s from baking pi tutorials in c
#include "postman.h"
#include "BCM2835peripherals.h"

void MailboxWrite(uint32_T message, uint32_T channel)
{
	volatile uint32_T* mailbox_status = (volatile uint32_T*) GPU_MAILBOX_STATUS;
	uint32_T* mailbox_write = (uint32_T*) GPU_MAILBOX_WRITE;
	if (message & 0xf) return; // make sure lowest 4 bytes are 0
	if (channel > 15) return; // 0-15
	while ( (*mailbox_status & 0x8000000) ); // wait for bit 31 to change to 0
	*mailbox_write = message + channel;
}

uint32_T MailboxRead(uint32_T channel)
{
	volatile uint32_T* mailbox_status = (volatile uint32_T*) GPU_MAILBOX_STATUS;
	volatile uint32_T* mailbox_read = (volatile uint32_T*) GPU_MAILBOX_READ;
	uint32_T message;
	if (channel > 15) return 0; // 0-15
	while(1) {
		while ( (*mailbox_status & 0x4000000) ); // wait for bit 30 to change to 0
		message = *mailbox_read;
		if ( (message & 0xf) == channel ) {
			return message & 0xfffffff0;
		}
	}
}

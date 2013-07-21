// implementation of framebuffer.s from baking pi tutorials in c
#include "framebuffer.h"
#include "postman.h"
#include "BCM2835peripherals.h"
#include <stdlib.h>

extern FrameBufferInfo_T FrameBufferInfo;

FrameBufferInfo_T* InitialiseFrameBuffer(uint32_T width, uint32_T height, uint32_T bitDepth)
{
	uint32_T error;
	uint32_T sendmessage;
//	if ( (width > 4096) | (height > 4096) | (bitDepth > 32) ) return NULL; // check inputs
	
	// Fill FrameBufferInfo struct
	FrameBufferInfo.physWidth = width;
	FrameBufferInfo.physHeight = height;
	FrameBufferInfo.virtualWidth = width;
	FrameBufferInfo.virtualHeight = height;
	FrameBufferInfo.bitDepth = bitDepth;
	
	// Write to Mailbox
	sendmessage = (uint32_T) &FrameBufferInfo + 0x40000000;
	MailboxWrite(sendmessage, 1);
	// Read back from Mailbox - if 0, it succeeded
	error = MailboxRead(1);
	if ( error == 0 ) return (FrameBufferInfo_T*) &FrameBufferInfo;
	// Otherwise, return Error
	return NULL;
}
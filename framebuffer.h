#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "typedefs.h"
	
	typedef struct {
		uint32_T physWidth;
		uint32_T physHeight;
		uint32_T virtualWidth;
		uint32_T virtualHeight;
		uint32_T pitch;
		uint32_T bitDepth;
		uint32_T x;
		uint32_T y;
		void* gpuPointer;
		uint32_T gpuSize;
	} FrameBufferInfo_T;

	FrameBufferInfo_T* InitialiseFrameBuffer(uint32_T width, uint32_T height, uint32_T bitDepth);
	
#endif
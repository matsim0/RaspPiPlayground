#include <stdlib.h>
#include "typedefs.h"
#include "framebuffer.h"

uint32_T foreColour = 0xffff;
FrameBufferInfo_T* graphicsAddress = NULL;

void SetForeColour(uint32_T colour)
{
	foreColour = colour;
}

void SetGraphicsAddress(FrameBufferInfo_T* address)
{
	graphicsAddress = address;
}

void DrawPixel(uint32_T px, uint32_T py)
{
	uint32_T height;
	uint32_T width;
	
	if (graphicsAddress == NULL) return; // check if Address already set
	height = graphicsAddress->physHeight;
	width = graphicsAddress->physWidth;
	if (py >= height) return;
	if (px >= width) return;
	// depending on bitDepth, there are different pointer types:
	if (graphicsAddress->bitDepth <= 8) {
		uint8_T *pixel;
		pixel = graphicsAddress->gpuPointer;
		*(pixel + py * width + px) = (uint8_T) foreColour;
	} else if (graphicsAddress->bitDepth <= 16) {
		uint16_T *pixel;
		pixel = graphicsAddress->gpuPointer;
		*(pixel + py * width + px) = (uint16_T) foreColour;
	} else {
		uint32_T *pixel;
		pixel = graphicsAddress->gpuPointer;
		*(pixel + py * width + px) = (uint32_T) foreColour;
	}
}

void DrawLine(uint32_T x0, uint32_T y0, uint32_T x1, uint32_T y1)
{
	int32_T deltax;
	int32_T stepx;
	int32_T deltay;
	int32_T stepy;
	int32_T error;
	
	if (x1 > x0) {
		deltax = x1 - x0;
		stepx = 1;
	} else {
		deltax = x0 - x1;
		stepx = -1;
	}

	if (y1 > y0) {
		deltay = y1 - y0;
		stepy = 1;
	} else {
		deltay = y0 - y1;
		stepy = -1;
	}
	
	error = deltax - deltay;
	while (x0 != x1 + stepx & y0 != y1 + stepy) {
		DrawPixel(x0, y0);
		if (error * 2 >= -deltay) {
			x0 += stepx;
			error = error - deltay;
		}
		if (error * 2 <= deltax) {
			y0 += stepy;
			error += deltax;
		}
	} 
}

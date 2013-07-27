#include <stddef.h>
#include "typedefs.h"
#include "framebuffer.h"
#include "drawing.h"
#include "system.h"
#include "font.h"

uint32_T foreColour = 0xffff;
uint32_T backColour = 0x000f;
FrameBufferInfo_T* graphicsAddress = NULL;

void SetForeColour(uint32_T colour)
{
	foreColour = colour;
}

void SetGraphicsAddress(FrameBufferInfo_T* address)
{
	graphicsAddress = address;
}

void DrawString(uint8_T string[], uint32_T length, uint32_T x, uint32_T y)
{
	uint32_T ii;
	uint32_T xdraw = x;
	uint32_T ydraw = y;
	if (x > XW - CWIDTH - 1) return; // We do wrap around the screen width to x - therefore it must be possible to draw at least one character
	for (ii = 0; ii < length; ii++)
	{
		if (string[ii] == '\n') {
			xdraw = x;
			ydraw = (ydraw + CHEIGHT) % YW;		
		} else if (string[ii] == '\t') {
			int32_T overlap;
			xdraw = xdraw + 5 * CWIDTH;	
			overlap = xdraw-XW;
			while(overlap >= 0) {
				ydraw = (ydraw + CHEIGHT) % YW;
				xdraw = x + overlap;
				overlap = xdraw - XW;
			}
		} else {			
			DrawCharacter(string[ii], xdraw, ydraw);
			xdraw = xdraw + CWIDTH;
			if (xdraw > XW - 1) {
				xdraw = x;
				ydraw = (ydraw + CHEIGHT) % YW;
			}
		}
	}
}

void DrawCharacter(uint8_T character, uint32_T x, uint32_T y)
{
	uint32_T* charAddress = (uint32_T*)(&font + character*4); 	// Character Pictures are stored in 16 bytes 
	uint32_T row;
	uint32_T bit;
	uint32_T bits;
	if (character > 128) return;
	// in every 32bit row in .bin are 4 Lines for drawing
	for (row = 0; row < 4; row++)
	{
		bits = *(charAddress + row);
		for (bit = 0; bit < 32; bit++)
		{
			if ( (bits >> bit)&0x1 == 0x1) 
				DrawPixel(x + bit%8, y + row*4 + bit/8 );
		}
	}
}

uint32_T clearScreen(void)
{
	uint32_T ii;
	uint16_T* address;			// only implementation for 16bit colour depth
	uint32_T width;
	uint32_T height;

	if (graphicsAddress == NULL) return 0;
	address = graphicsAddress->gpuPointer;
	width = graphicsAddress->physWidth;
	height = graphicsAddress->physHeight;
	for (ii = 0; ii < width*height; ii++)
	{
		*(address + ii) = (uint16_T) backColour;
	}
	return 1;
}

uint32_T DrawPixel(uint32_T px, uint32_T py)
{
	uint32_T height;
	uint32_T width;
	uint16_T *pixel;		// only implementation for 16bit colour depth
	
	if (graphicsAddress == NULL) return 0; // check if Address already set
	height = graphicsAddress->physHeight;
	width = graphicsAddress->physWidth;
	if (py >= height) return;
	if (px >= width) return;
	pixel = graphicsAddress->gpuPointer;
	*(pixel + py * width + px) = (uint16_T) foreColour;
	return 1;
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

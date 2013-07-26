#ifndef DRAWING_H
#define DRAWING_H

#include "framebuffer.h"

void SetForeColour(uint32_T colour);
void SetGraphicsAddress(FrameBufferInfo_T* address);
uint32_T clearScreen(void);
uint32_T DrawPixel(uint32_T px, uint32_T py);
void DrawLine(uint32_T x0, uint32_T y0, uint32_T x1, uint32_T y1);
void DrawCharacter(uint8_T character, uint32_T x, uint32_T y);
void DrawString(uint8_T string[], uint32_T length, uint32_T x, uint32_T y);

#endif
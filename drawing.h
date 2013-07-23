
#ifndef DRAWING_H
#define DRAWING_H

#include "framebuffer.h"

#define XW 640
#define YW 480

void SetForeColour(uint32_T colour);
void SetGraphicsAddress(FrameBufferInfo_T* address);
void clearScreen(void);
void DrawPixel(uint32_T px, uint32_T py);
void DrawLine(uint32_T x0, uint32_T y0, uint32_T x1, uint32_T y1);

#endif
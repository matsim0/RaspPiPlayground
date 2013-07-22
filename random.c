#include "typedefs.h"

uint32_T Random(uint32_T x)
{
	uint16_T a = 0xef00;
	uint16_T b = 1;
	uint16_T c = 73;
	
	return(a*x*x + b*x + c);
}
#define GP_BASE 0x20200000
#define GPFSEL0 GP_BASE
#define GPFSEL1 (GP_BASE + 0x4)
#define GPSET0 (GP_BASE + 0x1c)
#define GPCLR0 (GP_BASE + 0x28)

#define GP_FSELPIN16MASK 0x001C0000

typedef unsigned int  uint32_T;
typedef unsigned char uint8_T;
typedef unsigned short uint16_T ;
typedef int int32_T;
typedef	short int16_T;
typedef char int8_T;

int main()
{
	uint32_T* gpiocntrl;
	uint32_T* gpioset;
	uint32_T* gpioclear;
	uint32_T bit16 = 1<<16;
	uint32_T i;
	
	gpiocntrl = (uint32_T*) GPFSEL1;
	gpioset = (uint32_T*) GPSET0;
	gpioclear = (uint32_T*) GPCLR0;
	
	// Set gpio 16 to output
	*gpiocntrl = (*gpiocntrl & !GP_FSELPIN16MASK) & 1<<18;
	
	while(1) 
	{
		// Clear Pin 16 (sets ACT)
		*gpioclear = 1<<16;
		// Wait for a _long_ time
		for (i = 0; i <= 0x3f000; i++);
		// Set Pin 16 (clears ACT)
		*gpioset = 1<<16;
		// Wait again for a _long_ time
		for (i = 0; i <= 0x3f000; i++);
	}
	return 1;
}

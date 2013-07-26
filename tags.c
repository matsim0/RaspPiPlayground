#include "typedefs.h"
#include <stddef.h>
#include "drawing.h"

// uint32_T** atags = NULL; // List Adresses of Tags
uint32_T* atags[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

uint32_T* FindTag(uint32_T tag)
{
	uint32_T* tagAddr;	// Pointer to Address of tag
	uint32_T tagValue;
	uint16_T tagIndex;
	uint32_T ii;
	
	if (tag > 9 || tag == 0) return NULL;
	if (atags[tag-1] != NULL) return atags[tag-1];
	// tag not yet filled - now we have to fill in the tags
	tagAddr = (uint32_T*) 0x100;
	for (ii = 0; ii < 9; ii++) {
		tagValue = *(tagAddr + 1); // 1. word is size, the comes the half-word with the tag number
		tagIndex = (uint16_T) (tagValue & 0xffff); // just to make sure...
		if (tagIndex == ii+1) {
			atags[ii] = tagAddr;
			tagAddr = (uint32_T*) (tagAddr + *tagAddr);
		} else {
			atags[ii] = NULL;
		}
	}
	return atags[tag-1];
}
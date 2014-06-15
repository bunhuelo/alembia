/*
 * toolkit.c
 *
 *  Created on: 15.06.2014
 *      Author: bunhuelo
 */

#include <stdlib.h>
#include "toolkit.h"

void memrev(unsigned char* destination,unsigned char* source, unsigned int count)
{
	int i;
	if(count<1) exit(0xC001); /* count must be 1 or more */
	for(i=count-1;i>=0;--i) *(destination++)=*(source+i);
}

unsigned char rotl(unsigned char value, unsigned short int shift)
{
    return (value << shift) | (value >> 8 - shift);
}

unsigned char rotr(unsigned char value, unsigned short int shift)
{
    return (value >> shift) | (value << 8 - shift);
}

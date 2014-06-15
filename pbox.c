/*
 * pbox.c
 *
 *  Created on: 14.06.2014
 *      Author: bunhuelo
 */

#include <string.h>

unsigned char tempblock[8];

void pbox(unsigned char* block)
{
	unsigned char i;
	for(i=0;i<8;++i) tempblock[i]=0;

	if (block[0]&1) tempblock[3]|=8;
	if (block[0]&2) tempblock[5]|=1;
	if (block[0]&4) tempblock[1]|=1;
	if (block[0]&8) tempblock[6]|=4;
	if (block[0]&16) tempblock[4]|=4;
	if (block[0]&32) tempblock[7]|=128;
	if (block[0]&64) tempblock[0]|=16;
	if (block[0]&128) tempblock[2]|=1;

	if (block[1]&1) tempblock[2]|=8;
	if (block[1]&2) tempblock[4]|=8;
	if (block[1]&4) tempblock[7]|=8;
	if (block[1]&8) tempblock[3]|=4;
	if (block[1]&16) tempblock[6]|=2;
	if (block[1]&32) tempblock[0]|=32;
	if (block[1]&64) tempblock[5]|=32;
	if (block[1]&128) tempblock[3]|=128;

	if (block[2]&1) tempblock[1]|=32;
	if (block[2]&2) tempblock[6]|=64;
	if (block[2]&4) tempblock[5]|=8;
	if (block[2]&8) tempblock[2]|=2;
	if (block[2]&16) tempblock[7]|=16;
	if (block[2]&32) tempblock[0]|=8;
	if (block[2]&64) tempblock[7]|=2;
	if (block[2]&128) tempblock[3]|=64;

	if (block[3]&1) tempblock[4]|=128;
	if (block[3]&2) tempblock[0]|=128;
	if (block[3]&4) tempblock[2]|=64;
	if (block[3]&8) tempblock[5]|=2;
	if (block[3]&16) tempblock[2]|=4;
	if (block[3]&32) tempblock[7]|=64;
	if (block[3]&64) tempblock[1]|=2;
	if (block[3]&128) tempblock[4]|=2;

	if (block[4]&1) tempblock[0]|=64;
	if (block[4]&2) tempblock[4]|=64;
	if (block[4]&4) tempblock[6]|=8;
	if (block[4]&8) tempblock[3]|=2;
	if (block[4]&16) tempblock[7]|=4;
	if (block[4]&32) tempblock[1]|=4;
	if (block[4]&64) tempblock[5]|=64;
	if (block[4]&128) tempblock[2]|=16;

	if (block[5]&1) tempblock[1]|=64;
	if (block[5]&2) tempblock[4]|=32;
	if (block[5]&4) tempblock[2]|=32;
	if (block[5]&8) tempblock[6]|=32;
	if (block[5]&16) tempblock[0]|=1;
	if (block[5]&32) tempblock[3]|=1;
	if (block[5]&64) tempblock[7]|=1;
	if (block[5]&128) tempblock[6]|=128;

	if (block[6]&1) tempblock[0]|=2;
	if (block[6]&2) tempblock[5]|=128;
	if (block[6]&4) tempblock[4]|=16;
	if (block[6]&8) tempblock[1]|=128;
	if (block[6]&16) tempblock[2]|=128;
	if (block[6]&32) tempblock[5]|=4;
	if (block[6]&64) tempblock[3]|=32;
	if (block[6]&128) tempblock[1]|=8;

	if (block[7]&1) tempblock[1]|=16;
	if (block[7]&2) tempblock[4]|=1;
	if (block[7]&4) tempblock[7]|=32;
	if (block[7]&8) tempblock[0]|=4;
	if (block[7]&16) tempblock[6]|=1;
	if (block[7]&32) tempblock[5]|=16;
	if (block[7]&64) tempblock[6]|=16;
	if (block[7]&128) tempblock[3]|=16;

	memcpy(block,tempblock,8);
}

void invpbox(unsigned char* block)
{
	unsigned char i;
	for(i=0;i<8;++i) tempblock[i]=0;

	if (block[0]&1) tempblock[5]|=16;
	if (block[0]&2) tempblock[6]|=1;
	if (block[0]&4) tempblock[7]|=8;
	if (block[0]&8) tempblock[2]|=32;
	if (block[0]&16) tempblock[0]|=64;
	if (block[0]&32) tempblock[1]|=32;
	if (block[0]&64) tempblock[4]|=1;
	if (block[0]&128) tempblock[3]|=2;

	if (block[1]&1) tempblock[0]|=4;
	if (block[1]&2) tempblock[3]|=64;
	if (block[1]&4) tempblock[4]|=32;
	if (block[1]&8) tempblock[6]|=128;
	if (block[1]&16) tempblock[7]|=1;
	if (block[1]&32) tempblock[2]|=1;
	if (block[1]&64) tempblock[5]|=1;
	if (block[1]&128) tempblock[6]|=8;

	if (block[2]&1) tempblock[0]|=128;
	if (block[2]&2) tempblock[2]|=8;
	if (block[2]&4) tempblock[3]|=16;
	if (block[2]&8) tempblock[1]|=1;
	if (block[2]&16) tempblock[4]|=128;
	if (block[2]&32) tempblock[5]|=4;
	if (block[2]&64) tempblock[3]|=4;
	if (block[2]&128) tempblock[6]|=16;

	if (block[3]&1) tempblock[5]|=32;
	if (block[3]&2) tempblock[4]|=8;
	if (block[3]&4) tempblock[1]|=8;
	if (block[3]&8) tempblock[0]|=1;
	if (block[3]&16) tempblock[7]|=128;
	if (block[3]&32) tempblock[6]|=64;
	if (block[3]&64) tempblock[2]|=128;
	if (block[3]&128) tempblock[1]|=128;

	if (block[4]&1) tempblock[7]|=2;
	if (block[4]&2) tempblock[3]|=128;
	if (block[4]&4) tempblock[0]|=16;
	if (block[4]&8) tempblock[1]|=2;
	if (block[4]&16) tempblock[6]|=4;
	if (block[4]&32) tempblock[5]|=2;
	if (block[4]&64) tempblock[4]|=2;
	if (block[4]&128) tempblock[3]|=1;

	if (block[5]&1) tempblock[0]|=2;
	if (block[5]&2) tempblock[3]|=8;
	if (block[5]&4) tempblock[6]|=32;
	if (block[5]&8) tempblock[2]|=4;
	if (block[5]&16) tempblock[7]|=32;
	if (block[5]&32) tempblock[1]|=64;
	if (block[5]&64) tempblock[4]|=64;
	if (block[5]&128) tempblock[6]|=2;

	if (block[6]&1) tempblock[7]|=16;
	if (block[6]&2) tempblock[1]|=16;
	if (block[6]&4) tempblock[0]|=8;
	if (block[6]&8) tempblock[4]|=4;
	if (block[6]&16) tempblock[7]|=64;
	if (block[6]&32) tempblock[5]|=8;
	if (block[6]&64) tempblock[2]|=2;
	if (block[6]&128) tempblock[5]|=128;

	if (block[7]&1) tempblock[5]|=64;
	if (block[7]&2) tempblock[2]|=64;
	if (block[7]&4) tempblock[4]|=16;
	if (block[7]&8) tempblock[1]|=4;
	if (block[7]&16) tempblock[2]|=16;
	if (block[7]&32) tempblock[7]|=4;
	if (block[7]&64) tempblock[3]|=32;
	if (block[7]&128) tempblock[0]|=32;

	memcpy(block,tempblock,8);
}

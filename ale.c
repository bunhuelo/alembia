/*
 * ale.c
 *
 *  Created on: 13.06.2014
 *      Author: bunhuelo
 */

#include <string.h>
#include <stdio.h>
#include "ale.h"
#include "pbox.h"
#include "sbox_alpha.h"
#include "sbox_bravo.h"
#include "toolkit.h"

unsigned char buffer1[16];
unsigned char buffer2[16];

void ale_encrypt(unsigned char* block, unsigned char* key)
{
	short int round, loopcounter;
	unsigned char keycopy[32];

	memcpy(buffer1,block,16);
	memcpy(keycopy,key,32);

	for(round=0;round<10;++round)
	{
		/* Rearrange bytes */
		memcpy(buffer2,buffer1,4);
		memcpy(buffer2+8,buffer1+4,8);
		memrev(buffer2+4,buffer1+12,4);

		/* P-Box */
		pbox(buffer2); pbox(buffer2+8);

		for(loopcounter=0;loopcounter<16;++loopcounter)
		{
			sboxa(buffer2+loopcounter); /* S-Box Alpha */
			buffer2[loopcounter]^=keycopy[loopcounter]; /* XOR */
			sboxb(buffer2+loopcounter); /* S-Box Bravo */
			buffer2[loopcounter]=rotr(buffer2[loopcounter],(unsigned short int) keycopy[loopcounter+16]%8); /* ROTR */
			buffer2[loopcounter]+=keycopy[loopcounter+16]; /* ADD */
		}

		/* Generate next key */
		for(loopcounter=0;loopcounter<16;++loopcounter)
		{
			keycopy[loopcounter+16]^=(unsigned char) round;
			keycopy[loopcounter+16]=~(*(keycopy+loopcounter+16));
			keycopy[loopcounter]^=keycopy[loopcounter+16];
			keycopy[loopcounter]^=(unsigned char) round;
		}

		/* Prepare for next round */
		memcpy(buffer1,buffer2,16);
	}

	/* Return buffer contents */
	memcpy(block,buffer1,16);
}

void ale_decrypt(unsigned char* block, unsigned char* key)
{
	short int round, loopcounter;
	unsigned char keysched[10][32];

	memcpy(buffer1,block,16);
	memcpy(keysched[0],key,32);

	/* Generate key schedule */
	for(round=1;round<10;++round)
	{
		for(loopcounter=0;loopcounter<16;++loopcounter)
		{
			keysched[round][loopcounter+16]=keysched[round-1][loopcounter+16]^(unsigned char) round-1;
			keysched[round][loopcounter+16]=~keysched[round][loopcounter+16];
			keysched[round][loopcounter]=keysched[round-1][loopcounter]^keysched[round][loopcounter+16];
			keysched[round][loopcounter]^=(unsigned char) round-1;
		}
	}

	/* Decrypt block */
	for(round=9;round>=0;--round)
	{
		for(loopcounter=0;loopcounter<16;++loopcounter)
		{
			buffer1[loopcounter]-=keysched[round][loopcounter+16]; /* SUB */
			buffer1[loopcounter]=rotl(buffer1[loopcounter],(unsigned short int) keysched[round][loopcounter+16]%8); /* ROTL */
			invsboxb(buffer1+loopcounter); /* S-Box Bravo */
			buffer1[loopcounter]^=keysched[round][loopcounter]; /* XOR */
			invsboxa(buffer1+loopcounter); /* S-Box Alpha */
		}

		/* P-Box */
		invpbox(buffer1); invpbox(buffer1+8);

		/* Rearrange bytes */
		memcpy(buffer2,buffer1,4);
		memcpy(buffer2+4,buffer1+8,8);
		memrev(buffer2+12,buffer1+4,4);

		/* Prepare for next round */
		memcpy(buffer1,buffer2,16);
	}

	/* Return buffer contents */
	memcpy(block,buffer1,16);
}



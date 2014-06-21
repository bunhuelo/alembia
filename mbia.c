/*
 * mbia.c
 *
 *  Created on: 13.06.2014
 *      Author: bunhuelo
 */

#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include "mbia.h"
#include "pbox.h"
#include "sbox_alpha.h"
#include "sbox_bravo.h"

void mbia_encrypt(unsigned char* block, unsigned char* key, unsigned char* wpcn)
{
	/* Initialize memory */
	short int round, loopcounter;
	unsigned char** keysched;
	unsigned char buffer1[16], buffer2[4];
	keysched=malloc(sizeof(unsigned char*)*10);
	mlock(keysched,sizeof(unsigned char*)*10);
	for(loopcounter=0;loopcounter<10;++loopcounter)
	{
		keysched[loopcounter]=malloc(sizeof(unsigned char)*32);
		mlock(keysched[loopcounter],sizeof(unsigned char)*32);
	}

	/* Copy buffer */
	memcpy(buffer1,block,16);

	/* Key schedule */
	mbia_keysched(keysched,key,wpcn);

	/* Rounds */
	for(round=0;round<10;++round)
	{
		/* P-Box */
		for(loopcounter=0;loopcounter<keysched[round][4]%16+1;++loopcounter)
		{
			pbox(buffer1); pbox(buffer1+8);
		}

		/* S-Box and P-Box */
		for(loopcounter=0;loopcounter<keysched[round][21]%24+1;++loopcounter)
		{
			sboxa(buffer1+0); sboxb(buffer1+1); sboxb(buffer1+2); sboxa(buffer1+3);
			pbox(buffer1+4);
			sboxb(buffer1+12); sboxa(buffer1+13); sboxa(buffer1+14); sboxb(buffer1+15);
		}

		/* Mixed WPCN operations */
		for(loopcounter=0;loopcounter<3;++loopcounter)
		{
			buffer1[loopcounter]^=wpcn[loopcounter]; /* XOR 012 */
			buffer1[loopcounter+3]-=wpcn[loopcounter]; /* SUB 345 */
			buffer1[loopcounter+6]+=wpcn[loopcounter]; /* ADD 678 */
			buffer1[loopcounter+9]=~(buffer1[loopcounter+9]^wpcn[loopcounter]); /* NOT XOR 9AB */
			buffer1[loopcounter+12]+=wpcn[loopcounter]; /* ADD CDE */
		}
		buffer1[15]^=wpcn[1];

		/* Bytewise substitution */
		for(loopcounter=4;loopcounter<8;++loopcounter)
		{
			sboxb(buffer1+loopcounter);
			sboxa(buffer1+loopcounter+4);
		}

		/* Swap bytes */
		memcpy(buffer2,buffer1+8,4);
		memcpy(buffer1+8,buffer1+4,4);
		memcpy(buffer1+4,buffer2,4);

		/* XOR and ADD */
		for(loopcounter=0;loopcounter<16;++loopcounter)
		{
			switch(keysched[round][15]%4)
			{
				case 0:
					buffer1[loopcounter]^=keysched[round][loopcounter];
					buffer1[loopcounter]+=keysched[round][loopcounter+16];
					break;

				case 1:
					buffer1[loopcounter]+=keysched[round][loopcounter+16];
					buffer1[loopcounter]^=keysched[round][loopcounter];
					break;

				case 2:
					buffer1[loopcounter]+=keysched[round][loopcounter];
					buffer1[loopcounter]^=keysched[round][loopcounter+16];
					break;

				case 3:
					buffer1[loopcounter]^=keysched[round][loopcounter+16];
					buffer1[loopcounter]+=keysched[round][loopcounter];
					break;
			}
		}
	}

	/* Unlock */
	for(loopcounter=0;loopcounter<10;++loopcounter)
	{
		memcpy(keysched[loopcounter],"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",32);
		munlock(keysched[loopcounter],sizeof(unsigned char)*32);
		free(keysched[loopcounter]);
	}
	munlock(keysched,sizeof(unsigned char*)*10);
	free(keysched);

	/* Block done */
	sboxb(&wpcn[0]);
	sboxa(&wpcn[1]);
	sboxa(&wpcn[2]);

	memcpy(block,buffer1,16);
}

void mbia_decrypt(unsigned char* block, unsigned char* key, unsigned char* wpcn)
{
	/* Initialize memory */
	short int round, loopcounter;
	unsigned char** keysched;
	unsigned char buffer1[16], buffer2[4];
	keysched=malloc(sizeof(unsigned char*)*10);
	mlock(keysched,sizeof(unsigned char*)*10);
	for(loopcounter=0;loopcounter<10;++loopcounter)
	{
		keysched[loopcounter]=malloc(sizeof(unsigned char)*32);
		mlock(keysched[loopcounter],sizeof(unsigned char)*32);
	}

	/* Copy buffer */
	memcpy(buffer1,block,16);

	/* Key schedule */
	mbia_keysched((unsigned char**) keysched,key,wpcn);

	/* Rounds */
	for(round=9;round>=0;--round)
	{
		/* XOR and ADD */
		for(loopcounter=0;loopcounter<16;++loopcounter)
		{
			switch(keysched[round][15]%4)
			{
				case 0:
					buffer1[loopcounter]-=keysched[round][loopcounter+16];
					buffer1[loopcounter]^=keysched[round][loopcounter];
					break;

				case 1:
					buffer1[loopcounter]^=keysched[round][loopcounter];
					buffer1[loopcounter]-=keysched[round][loopcounter+16];
					break;

				case 2:
					buffer1[loopcounter]^=keysched[round][loopcounter+16];
					buffer1[loopcounter]-=keysched[round][loopcounter];
					break;

				case 3:
					buffer1[loopcounter]-=keysched[round][loopcounter];
					buffer1[loopcounter]^=keysched[round][loopcounter+16];
					break;
			}
		}

		/* Swap bytes */
		memcpy(buffer2,buffer1+8,4);
		memcpy(buffer1+8,buffer1+4,4);
		memcpy(buffer1+4,buffer2,4);

		/* Bytewise substitution */
		for(loopcounter=4;loopcounter<8;++loopcounter)
		{
			invsboxb(buffer1+loopcounter);
			invsboxa(buffer1+loopcounter+4);
		}

		/* Mixed WPCN operations */
		for(loopcounter=0;loopcounter<3;++loopcounter)
		{
			buffer1[loopcounter]^=wpcn[loopcounter]; /* XOR 012 */
			buffer1[loopcounter+3]+=wpcn[loopcounter]; /* SUB 345 */
			buffer1[loopcounter+6]-=wpcn[loopcounter]; /* ADD 678 */
			buffer1[loopcounter+9]=~(buffer1[loopcounter+9]^wpcn[loopcounter]); /* NOT XOR 9AB */
			buffer1[loopcounter+12]-=wpcn[loopcounter]; /* ADD CDE */
		}
		buffer1[15]^=wpcn[1];

		/* S-Box and P-Box */
		for(loopcounter=0;loopcounter<keysched[round][21]%24+1;++loopcounter)
		{
			invsboxa(buffer1+0); invsboxb(buffer1+1); invsboxb(buffer1+2); invsboxa(buffer1+3);
			invpbox(buffer1+4);
			invsboxb(buffer1+12); invsboxa(buffer1+13); invsboxa(buffer1+14); invsboxb(buffer1+15);
		}

		/* P-Box */
		for(loopcounter=0;loopcounter<keysched[round][4]%16+1;++loopcounter)
		{
			invpbox(buffer1); invpbox(buffer1+8);
		}
	}

	/* Unlock */
	for(loopcounter=0;loopcounter<10;++loopcounter)
	{
		memcpy(keysched[loopcounter],"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",32);
		munlock(keysched[loopcounter],sizeof(unsigned char)*32);
		free(keysched[loopcounter]);
	}
	munlock(keysched,sizeof(unsigned char*)*10);
	free(keysched);

	/* Block done */
	sboxb(&wpcn[0]);
	sboxa(&wpcn[1]);
	sboxa(&wpcn[2]);

	memcpy(block,buffer1,16);
}

void mbia_keysched(unsigned char** keysched, unsigned char* key, unsigned char* wpcn)
{
	short int round;
	short int loopcounter;

	memcpy(keysched[0],key,32);

	for(round=1;round<10;++round)
	{
		memcpy(keysched[round],keysched[round-1],32);
		keysched[round][0]=~(keysched[round][0]^wpcn[0]);
		keysched[round][2]=~(keysched[round][2]^wpcn[1]);
		keysched[round][5]=~(keysched[round][5]^wpcn[2]);
		keysched[round][17]=~(keysched[round][17]-wpcn[0]);
		keysched[round][20]=~(keysched[round][20]-wpcn[1]);
		keysched[round][22]=~(keysched[round][22]-wpcn[2]);
		for(loopcounter=0;loopcounter<16;++loopcounter)
		{
			sboxa(keysched[round]+loopcounter);
			sboxb(keysched[round]+loopcounter+16);
		}
		wpcn[0]^=keysched[round][4];
		wpcn[1]^=keysched[round][15];
		wpcn[2]^=keysched[round][18];
	}
}

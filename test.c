/*
 * test.c
 *
 *  Created on: 14.06.2014
 *      Author: bunhuelo
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "pbox.h"
#include "sbox_alpha.h"
#include "sbox_bravo.h"
#include "ale.h"
#include "mbia.h"

int main()
{
	/* Declare */
	unsigned char *longblock,*testblock,*origblock,*key, *wpcn;
	char testchar,origchar;
	int i,j,fail;

	/* Initialize */
	testblock=malloc(sizeof(unsigned char)*9);
	testblock[8]=0;
	origblock=malloc(sizeof(unsigned char)*9);
	origblock[8]=0;
	longblock=malloc(sizeof(unsigned char)*17);
	longblock[16]=0;
	key=malloc(sizeof(unsigned char)*33);
	key[32]=0;
	wpcn=malloc(sizeof(unsigned char)*4);
	wpcn[4]=0;
	fail=0;

	/* Phase I - PBOX */
	printf("Test phase I - Permutation (pbox.h)\n");
	memcpy(testblock,(unsigned char*) "12345678", 8);
	printf(" Permutation input:   %s\n",testblock);
	pbox(testblock);
	printf(" Permutation output:  %s\n",testblock);
	pbox(testblock);
	printf(" Another permutation: %s\n",testblock);
	invpbox(testblock);
	printf(" And back:            %s\n",testblock);
	invpbox(testblock);
	printf(" And back again:      %s\n",testblock);
	srand(time(NULL));
	for(i=0;i<1000;++i)
	{
		for(j=0;j<8;++j) testblock[j]=(unsigned char) rand()%255+1;
		memcpy(origblock,testblock,8);
		pbox(testblock); pbox(testblock); invpbox(testblock); invpbox(testblock);
		if(strcmp((const char*) testblock,(const char*) origblock)) fail=1;
	}
	if (fail) {printf(" (--) Failed permutation random char test.\n\n");exit(1);}
	else printf(" (++) Successful permutation random char test.\n\n");

	/* Phase II - SBOX ALPHA */
	printf("Test phase II - S-Box Alpha (sbox_alpha.h)\n");
	testchar='@';
	printf(" S-Box input:          %c\n",testchar);
	sboxa((unsigned char*) &testchar);
	printf(" S-Box output:         %c\n",testchar);
	sboxa((unsigned char*) &testchar);
	printf(" Another substitution: %c\n",testchar);
	invsboxa((unsigned char*) &testchar);
	printf(" And back:             %c\n",testchar);
	invsboxa((unsigned char*) &testchar);
	printf(" And back again:       %c\n",testchar);
	for(i=0;i<256;++i)
	{
		testchar=origchar=(unsigned char) i;
		sboxa((unsigned char*) &testchar);
		invsboxa((unsigned char*) &testchar);
		if(origchar!=testchar) fail=1;
	}
	if (fail) {printf(" (--) Failed test of complete S-Box Alpha.\n\n");exit(1);}
	else printf(" (++) Successful test of complete S-Box Alpha.\n\n");

	/* Phase III - SBOX BRAVO */
	printf("Test phase III - S-Box Bravo (sbox_bravo.h)\n");
	testchar='@';
	printf(" S-Box input:          %c\n",testchar);
	sboxb((unsigned char*) &testchar);
	printf(" S-Box output:         %c\n",testchar);
	sboxb((unsigned char*) &testchar);
	printf(" Another substitution: %c\n",testchar);
	invsboxb((unsigned char*) &testchar);
	printf(" And back:             %c\n",testchar);
	invsboxb((unsigned char*) &testchar);
	printf(" And back again:       %c\n",testchar);
	for(i=0;i<256;++i)
	{
		testchar=origchar=(unsigned char) i;
		sboxb((unsigned char*) &testchar);
		invsboxb((unsigned char*) &testchar);
		if(origchar!=testchar) fail=1;
	}
	if (fail) {printf(" (--) Failed test of complete S-Box Bravo.\n\n");exit(1);}
	else printf(" (++) Successful test of complete S-Box Bravo.\n\n");

	/* Phase IV - ALE */
	printf("Test phase IV - ALE\n");
	memcpy(longblock,"0123456789ABCDEF",16);
	memcpy(key,"00001111222233334444555566667777",32);
	printf(" ALE input:     %s\n",longblock);
	ale_encrypt(longblock,key);
	printf(" ALE output:    %s\n",longblock);
	ale_decrypt(longblock,key);
	printf(" ALE decrypted: %s\n\n",longblock);

	/* Phase V - MBIA */
	printf("Test phase V - MBIA\n");
	memcpy(longblock,"0123456789ABCDEF",16);
	memcpy(key,"00001111222233334444555566667777",32);
	printf(" MBIA input:     %s\n",longblock);
	memcpy(wpcn,"\0\0\0",3);
	mbia_encrypt(longblock,key,wpcn);
	printf(" MBIA output:    %s\n",longblock);
	memcpy(wpcn,"\0\0\0",3);
	mbia_decrypt(longblock,key,wpcn);
	printf(" MBIA decrypted: %s\n\n",longblock);

	/* Phase VI - ALEMBIA */
	printf("Test phase V - ALE/MBIA\n");
	memcpy(longblock,"0123456789ABCDEF",16);
	printf(" ALE/MBIA input:     %s\n",longblock);
	memcpy(wpcn,"abc",3);
	memcpy(key,"00001111222233334444555566667777",32);
	mbia_encrypt(longblock,key,wpcn);
	memcpy(key,"88889999AAAABBBBCCCCDDDDEEEEFFFF",32);
	ale_encrypt(longblock,key);
	printf(" ALE/MBIA output:    %s\n",longblock);
	memcpy(wpcn,"abc",3);
	memcpy(key,"88889999AAAABBBBCCCCDDDDEEEEFFFF",32);
	ale_decrypt(longblock,key);
	memcpy(key,"00001111222233334444555566667777",32);
	mbia_decrypt(longblock,key,wpcn);
	printf(" ALE/MBIA decrypted: %s\n\n",longblock);

	/* Clean up */
	free(testblock);free(origblock);free(longblock);free(key);free(wpcn);
	return 0;
}



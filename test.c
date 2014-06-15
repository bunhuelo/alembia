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

int main()
{
	/* Declare */
	unsigned char* testblock;
	unsigned char* origblock;
	char testchar,origchar;
	int i,j,fail;

	/* Initialize */
	testblock=malloc(sizeof(unsigned char)*9);
	testblock[8]=0;
	origblock=malloc(sizeof(unsigned char)*9);
	origblock[8]=0;
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
	if (fail) {printf(" (--) Failed complete S-Box Alpha test.\n\n");exit(1);}
	else printf(" (++) Successful complete S-Box Alpha test.\n\n");

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
	if (fail) {printf(" (--) Failed complete S-Box Bravo test.\n\n");exit(1);}
	else printf(" (++) Successful complete S-Box Bravo test.\n\n");

	/* Clean up */
	free(testblock);
	return 0;
}



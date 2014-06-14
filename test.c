/*
 * test.c
 *
 *  Created on: 14.06.2014
 *      Author: bunhuelo
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pbox.h"
#include "sbox_alpha.h"
#include "sbox_bravo.h"

int main()
{
	/* Declare */
	unsigned char* testblock;

	/* Initialize */
	testblock=malloc(sizeof(unsigned char)*9);
	testblock[8]=0;

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

	/* Clean up */
	free(testblock);
	return 0;
}



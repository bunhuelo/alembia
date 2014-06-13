/*
 * sbox_bravo.h
 *
 *  Created on: 13.06.2014
 *      Author: bunhuelo
 */

#ifndef SBOX_BRAVO_H_
#define SBOX_BRAVO_H_

extern unsigned char c_sboxb[256];
extern unsigned char inv_c_sboxb[256];

extern void sboxb(unsigned char* character);
extern void invsboxb(unsigned char* character);

#endif /* SBOX_BRAVO_H_ */

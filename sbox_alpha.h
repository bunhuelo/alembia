/*
 * sbox_alpha.h
 *
 *  Created on: 13.06.2014
 *      Author: bunhuelo
 */

#ifndef SBOX_ALPHA_H_
#define SBOX_ALPHA_H_

extern unsigned char c_sboxa[256];
extern unsigned char inv_c_sboxa[256];

extern void sboxa(unsigned char* character);
extern void invsboxa(unsigned char* character);

#endif /* SBOX_ALPHA_H_ */

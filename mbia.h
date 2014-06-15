/*
 * mbia.h
 *
 *  Created on: 13.06.2014
 *      Author: bunhuelo
 */

#ifndef MBIA_H_
#define MBIA_H_

extern void mbia_encrypt(unsigned char* block, unsigned char* key, unsigned char* wpcn);
extern void mbia_decrypt(unsigned char* block, unsigned char* key, unsigned char* wpcn);
extern void mbia_keysched(unsigned char** keysched, unsigned char* key, unsigned char* wpcn);

#endif /* MBIA_H_ */

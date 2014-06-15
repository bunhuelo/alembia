/*
 * ale.h
 *
 *  Created on: 13.06.2014
 *      Author: bunhuelo
 */

#ifndef ALE_H_
#define ALE_H_

extern void ale_encrypt(unsigned char* block, unsigned char* key);
extern void ale_decrypt(unsigned char* block, unsigned char* key);

#endif /* ALE_H_ */

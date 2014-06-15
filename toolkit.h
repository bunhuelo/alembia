/*
 * toolkit.h
 *
 *  Created on: 15.06.2014
 *      Author: bunhuelo
 */

#ifndef TOOLKIT_H_
#define TOOLKIT_H_

extern void memrev(unsigned char* destination,unsigned char* source, unsigned int count);
extern unsigned char rotl(unsigned char value, unsigned short int shift);
extern unsigned char rotr(unsigned char value, unsigned short int shift);

#endif /* TOOLKIT_H_ */

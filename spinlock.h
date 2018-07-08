/*
 * spinlock.h
 *
 *  Created on: Jul 2, 2018
 *      Author: Sam2
 */

#ifndef SPINLOCK_H_
#define SPINLOCK_H_


void getHeadLock(); //head (moved by PRU)
void putHeadLock(); //head (moved by PRU)


void getTailLock(); //tail (moved by ARM)
void putTailLock(); //tail (moved by ARM)


void getStatLock();
void putStatLock();

#endif /* SPINLOCK_H_ */

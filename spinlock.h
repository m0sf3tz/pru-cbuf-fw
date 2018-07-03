/*
 * spinlock.h
 *
 *  Created on: Jul 2, 2018
 *      Author: Sam2
 */

#ifndef SPINLOCK_H_
#define SPINLOCK_H_


void getPruLock(); //head (moved by PRU)
void putPruLock(); //head (moved by PRU)


void getArmLock(); //tail (moved by ARM)
void putArmLock(); //tail (moved by ARM)



#endif /* SPINLOCK_H_ */

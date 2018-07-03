/*
 * spinlock.c
 *
 *  Created on: Jul 2, 2018
 *      Author: Sam2
 */
#include <stdint.h>

#include "sharedVariables.h"

void getPruLock(){
    while(*(volatile uint32_t*)PRU_LOCK_OFFSET){}
}

void putPruLock(){
    (*(volatile uint32_t*)PRU_LOCK_OFFSET) = 0;
}

void getArmLock(){
    while(*(volatile uint32_t*)PRU_ARM_OFFSET){}
}

void putArmLock(){
    (*(volatile uint32_t*)PRU_ARM_OFFSET) = 0;
}

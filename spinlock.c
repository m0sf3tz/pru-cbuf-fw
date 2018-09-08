/*
 * spinlock.c
 *
 *  Created on: Jul 2, 2018
 *      Author: Sam2
 */
#include <stdint.h>
#include "spinlock.h"
#include "sharedVariables.h"


void initSpinLock()
{
    putBuffLock();
}

void getBuffLock(){
    while(*(volatile uint32_t*)PRU_LOCK_OFFSET){}
}

void putBuffLock(){
    (*(volatile uint32_t*)PRU_LOCK_OFFSET) = 0;
}

void getTailLock(){
    while(*(volatile uint32_t*)ARM_LOCK_OFFSET){}
}

void putTailLock(){
    (*(volatile uint32_t*)ARM_LOCK_OFFSET) = 0;
}

void getStatLock(){
    while(*(volatile uint32_t*)STAT_LOCK_OFFSET){}
}

void putStatLock(){
    (*(volatile uint32_t*)STAT_LOCK_OFFSET) = 0;
}

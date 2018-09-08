/*
 * spinlock.h
 *
 *  Created on: Jul 2, 2018
 *      Author: Sam2
 */

#pragma once

void initSpinLock();

void getBuffLock();
void putBuffLock();


void getTailLock(); //tail (moved by ARM)
void putTailLock(); //tail (moved by ARM)


void getStatLock();
void putStatLock();


/*
 * shbuf.h
 *
 *  Created on: Sep 6, 2018
 *      Author: Sam2
 */

#ifndef SHBUF_H_
#define SHBUF_H_


#define SHARED_BUFFER_FREE      0
#define SHARED_BUFFER_TAKEN     1
#define ERROR_GETTING_BUFFER 0xFF;



#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>
#include <stdbool.h>

#include "sharedVariables.h"
#include "spinlock.h"
#include "shbuf.h"
#include "projectDefines.h"






void initSharedBuffs();
uint8_t getFreeBuffer();
void setBufferUsed(uint32_t buffer);
void clearBufferUsed(uint32_t buffer);
bool isBufferUsed(uint32_t buffer);
bool areAllBuffersFull();
void putBuff(uint32_t buffer, uint32_t index, uint8_t rx);


#endif /* SHBUF_H_ */

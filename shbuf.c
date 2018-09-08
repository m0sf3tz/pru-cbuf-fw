#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>
#include <stdbool.h>

#include "sharedVariables.h"
#include "spinlock.h"
#include "shbuf.h"
#include "projectDefines.h"

#include "spinLock.h"



//sharedControlBlock is share with the arm PC, here we point it to the adress and init all
//the buffers
void initSharedBuffs()
{

    int iter;
    uint32_t * iterPter = (uint32_t *)SHBUF_CTRL_BLOCK;

    for(iter = 0; iter < SHBUF_TOTAL_BUFS; iter++)
    {
        *iterPter++ = SHARED_BUFFER_FREE;
    }

}

uint8_t getFreeBuffer()
{
    getBuffLock();

    int iter;
    uint32_t * iterPter = (uint32_t *)SHBUF_CTRL_BLOCK;

    for(iter = 0; iter <= SHBUF_TOTAL_BUFS; iter++)
    {
        if (iter == SHBUF_TOTAL_BUFS)
        {
            putBuffLock();
            return ERROR_GETTING_BUFFER;
        }

        if(*iterPter == SHARED_BUFFER_FREE)
        {
            putBuffLock();
            return iter;
        }

        iterPter++;
    }

    putBuffLock();
    return ERROR_GETTING_BUFFER; //error condition

}

void setBufferUsed(uint32_t buffer)
{
    getBuffLock();

    //sanitize input
    if(buffer > SHBUF_TOTAL_BUFS)
    {
        ASSERT(0);
    }

    uint32_t * bufPtr = (uint32_t *)SHBUF_CTRL_BLOCK;

    bufPtr = bufPtr + buffer;

    *bufPtr = SHARED_BUFFER_TAKEN;

    putBuffLock();

}

void clearBufferUsed(uint32_t buffer)
{
    getBuffLock();

    //sanitize input
    if(buffer > SHBUF_TOTAL_BUFS)
    {
        ASSERT(0);
    }

    uint32_t * bufPtr = (uint32_t *)SHBUF_CTRL_BLOCK;

    bufPtr = bufPtr + buffer;

    *bufPtr = SHARED_BUFFER_FREE;

    putBuffLock();

}

bool isBufferUsed(uint32_t buffer)
{
    getBuffLock();

    //sanitize input
    if(buffer > SHBUF_TOTAL_BUFS)
    {
        ASSERT(0);
    }

    uint32_t * bufPtr = (uint32_t *)SHBUF_CTRL_BLOCK;

    bufPtr = bufPtr + buffer;

    if(*bufPtr == SHARED_BUFFER_TAKEN)
    {
        putBuffLock();
        return true;

    }
    else
    {
       putBuffLock();
       return false;
    }


}


bool areAllBuffersFull()
{
    int iter;
    uint32_t * iterPter = (uint32_t *)SHBUF_CTRL_BLOCK;

    for(iter = 0; iter <= SHBUF_TOTAL_BUFS; iter++)
    {
        if (iter == SHBUF_TOTAL_BUFS)
        {
            return true;
        }

        iterPter++;
    }

    return false; //error condition

}
void putBuff(uint32_t buffer, uint32_t index, uint8_t rx)
{
    if(buffer > SHBUF_TOTAL_BUFS)
    {
        ASSERT(0);
    }
    if(index > TOTAL_BYTES_IN_SECTOR)
    {
        ASSERT(0);
    }
    uint32_t offset = (SHBUF0_START + buffer*SHBUF_SIZE + index);
    *(uint32_t *)(offset) = rx;
}


/*
 * cbuf.c
 *
 *  Created on: Jul 1, 2018
 *      Author: Sam2
 */


#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>

#include "spinlock.h"
#include "cbuf.h"


#define DEBUG_MODE 1
//we put in at the head.
//we take out at the tail

extern int x;

static void wrap_around_memput(circular_buf_t * cbuf, char * src, uint32_t len)
{
    if(*cbuf->head + len <= (cbuf->size)){
        memcpy((void*)(*(cbuf->head) + (uint32_t)cbuf->zeroth),(void*)(src), len);
    }
    else
    {
        uint32_t lenTop = (cbuf->size - *cbuf->head);
        uint32_t lenBot = (*cbuf->head + len) % cbuf->size;;

        memcpy((void*)((uint32_t)*cbuf->head + (uint32_t)cbuf->zeroth), (void*)(src                 ), lenTop);
        memcpy((void*)cbuf->zeroth                                   , (void*)((uint32_t)src+lenTop), lenBot);
    }
}
#if DEBUG_MODE  //should only be called from the ARMv7
static void wrap_around_memget(circular_buf_t * cbuf, char * dest, uint32_t len)
{
    getTailLock();
    uint32_t tail = *cbuf->tail;
    putTailLock();

    if(tail + len <= (cbuf->size-1)){
        memcpy((void*)dest, (void*)(tail + (uint32_t)cbuf->zeroth), len);
    }
        else
    {
        uint32_t lenTop = (cbuf->size - tail);
        uint32_t lenBot = (tail + len) % cbuf->size;;

        memcpy((void*)(dest)                 , (void*)(tail       + (uint32_t)cbuf->zeroth), lenTop);
        memcpy((void*)((uint32_t)dest+lenTop), (void*)cbuf->zeroth,                          lenBot);
    }
}
#endif


int circular_buf_reset(circular_buf_t * cbuf, uint32_t * zero, uint32_t size, circular_buf_stats_t * stat, uint32_t * sharedHead, uint32_t * sharedtail)
{
    int r = -1;

    if(cbuf)
    {
        getHeadLock();

        cbuf->zeroth = zero;
        cbuf->head   = sharedHead;  //shared w/ ARM
        cbuf->tail   = sharedtail;  //shared w/ ARM
        cbuf->full   = 0;
        cbuf->size   = size;
        cbuf->stat   = stat;

        //zero out shared variables
        *cbuf->tail = 0;
        *cbuf->head = 0;

        putHeadLock();

        r = 0;
    }

    return r;
}


uint8_t circular_buf_empty(circular_buf_t *  cbuf)
{
    uint32_t head = *cbuf->head;

    getTailLock();
    uint32_t tail = *cbuf->tail;
    putTailLock();

    // We define empty as head == tail
    return (head == tail);
}

uint8_t circular_buf_full(circular_buf_t * cbuf)
{
    return (circular_buf_space(cbuf) == (cbuf->size-1));
}

int circular_buf_space(circular_buf_t * cbuf)
{
    uint32_t head = *cbuf->head;

    getTailLock();
    uint32_t tail = *cbuf->tail;
    putTailLock();

    if(head == tail)
        return cbuf->size;

    else if(head > tail)
        return (cbuf->size - (head - tail) - 1);

    else if(head < tail)
        return (tail - head) - 1;

    else
        return -1;

}

void circular_buf_next_head(circular_buf_t * cbuf, uint32_t put)
{
    getHeadLock();
    *(cbuf->head) = (*(cbuf->head) + put)%cbuf->size;
    putHeadLock();
}

#if DEBUG_MODE  //should only be called from the ARMv7
void circular_buf_next_tail(circular_buf_t * cbuf, uint32_t get)
{
    getTailLock();
    *(cbuf->tail) = (*(cbuf->tail) + get)%cbuf->size;
    putTailLock();
}
#endif

int circular_buf_put(circular_buf_t * cbuf, char * src, size_t len)
{
    int ret = -1;

    uint32_t size = circular_buf_space(cbuf);

    if(len > size){
        getStatLock();
        (*(cbuf->stat)).overflow = 1;
        putStatLock();
        return ret;
    }

    wrap_around_memput(cbuf, src, len);

    circular_buf_next_head(cbuf, len);

    return 1;
}

#if DEBUG_MODE  //should only be called from the ARMv7
int circular_buf_get(circular_buf_t * cbuf, char * dest, size_t len)
{
    int ret = -1;

    uint32_t size = cbuf->size - circular_buf_space(cbuf) - 1;

    if(len > size)
        return ret;

    wrap_around_memget(cbuf, dest, len);

    circular_buf_next_tail(cbuf, len);

    return 1;
}
#endif

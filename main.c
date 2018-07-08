#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>

#include "spinlock.h"
#include "sharedVariables.h"
#include "cbuf.h"

#define PRU_LOCK_OFFSET 0x480CA800
#define ARM_LOCK_OFFSET  0x480CA804

circular_buf_stats_t bufStat;

void init(){
   memset((void*)SHBUF0_START, 0, SHBUF0_SIZE);

    putHeadLock();
    putTailLock();
}



void main(void)
{
    /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
    //zero out the buffers, give up spinlocks incase someone is holding them for some reason
    init();

    //we should not really have to, but lets set the clock on for the spinlock interface just incase we forget to in linux land...
    *(volatile uint32_t*)(0x44E0010C) = 0x2;

    circular_buf_t         buf0;
    circular_buf_stats_t   stat;
    circular_buf_reset(&buf0, (uint32_t*)SHBUF0_START, SHBUF0_SIZE, &stat,(uint32_t*)SHBUF0_HEAD_OFFSET,(uint32_t*)SHBUF0_TAIL_OFFSET);

    uint32_t x = 0;

    while(1){
        char tmp0[]  = {1, 2 ,3 , 4 ,5};
        char tmp1[]  = {0 ,0 ,0 , 0, 0};

        circular_buf_put(&buf0, (char*)&x,  sizeof(uint32_t));
        //circular_buf_get(&buf0, tmp1,  sizeof(tmp1));
        x++;

    }
    /* TODO: Create stop condition, else it will toggle indefinitely */
    while (1) {

    }
}

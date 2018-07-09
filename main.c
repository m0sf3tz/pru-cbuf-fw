#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>

#include "spinlock.h"
#include "sharedVariables.h"
#include "cbuf.h"
#include "lfsr.h"

#define PRU_LOCK_OFFSET 0x480CA800
#define ARM_LOCK_OFFSET  0x480CA804

circular_buf_stats_t bufStat;

void init(){
   memset((void*)SHBUF0_START, 0, SHBUF0_SIZE);

    putHeadLock();
    putTailLock();
}

int x;
lfsr_t glfsr_d0;
uint64_t poly = 0x1081;

void main(void)
{
    x = 0;
    /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
    //zero out the buffers, give up spinlocks incase someone is holding them for some reason
    init();

    //we should not really have to, but lets set the clock on for the spinlock interface just incase we forget to in linux land...
    *(volatile uint32_t*)(0x44E0010C) = 0x2;

    circular_buf_t         buf0;
    circular_buf_stats_t   stat;
    circular_buf_reset(&buf0, (uint32_t*)SHBUF0_START, SHBUF0_SIZE, &stat,(uint32_t*)SHBUF0_HEAD_OFFSET,(uint32_t*)SHBUF0_TAIL_OFFSET);

    GLFSR_init(&glfsr_d0, poly, 0xdeadbeef);

    while(1)
    {
       if(circular_buf_space(&buf0) > 1)
       {
           uint64_t data = (glfsr_d0.data & 0xFF);
           GLFSR_next(&glfsr_d0);
           circular_buf_put(&buf0, (char*)&data,  sizeof(char));
       }
    }

}

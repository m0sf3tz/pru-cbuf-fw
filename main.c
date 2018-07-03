#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>

#include "sharedVariables.h"
#include "cbuf.h"

#define PRU_LOCK_OFFSET 0x480CA800
#define PRU_ARM_OFFSET  0x480CA804

circular_buf_stats_t bufStat;

void cleanBuff0(){
   memset((void*)SHBUF0_START, 0, SHBUF0_SIZE);
}



int u = 0xFFFF;  //data
int z;           //bss

void main(void)
{
    /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

    circular_buf_t         buf0;
    circular_buf_stats_t   stat;
    stat.flags = 1;
    circular_buf_reset(&buf0, (uint32_t*)SHBUF0_START, SHBUF0_SIZE, &stat,(uint32_t*)SHBUF0_HEAD_OFFSET,(uint32_t*)SHBUF0_TAIL_OFFSET);


    while(1){
        char tmp0[]  = {1, 2 ,3 , 4 ,5};
        char tmp1[]  = {0 ,0 ,0 , 0, 0};

        circular_buf_put(&buf0, tmp0,  sizeof(tmp0));
        circular_buf_get(&buf0, tmp1,  sizeof(tmp1));

        if(memcmp( (void*)(tmp0), (void*)(tmp1), sizeof(tmp0)) )
        {
            while(1);
        }
    }
    /* TODO: Create stop condition, else it will toggle indefinitely */
    while (1) {

    }
}

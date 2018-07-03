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
    circular_buf_reset(&buf0, (uint32_t*)SHBUF0_START, SHBUF0_SIZE, &stat);


    while(1){
        char tmp0[] = {1,2,3,4,6,7,8,9,10};
        memcpy(&z, tmp0, 4);
        z = z | u;

        if(circular_buf_space(&buf0) >= sizeof(u) )
            circular_buf_put(&buf0, &z,  4);
    }

    /* TODO: Create stop condition, else it will toggle indefinitely */
    while (1) {

    }
}

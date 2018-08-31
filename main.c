#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>
#include <stdbool.h>

#include "spinlock.h"
#include "sharedVariables.h"
#include "cbuf.h"
#include "lfsr.h"
#include "uartHal.h"

#include "registerOffsets.h"
#include "uart_irda_cir.h"


circular_buf_stats_t bufStat;

void initSpinLock(){
   memset((void*)SHBUF0_START, 0, SHBUF0_SIZE);

    putHeadLock();
    putTailLock();
}


void initClocks()
{
    //we should not really have to, but lets set the clock on for the spinlock interface just incase we forget to in linux land...
    *(volatile uint32_t*)(CLOCK_CTRL_BASE + SPINLOCK_CLK_CTRL_OFFSET) = ENABLE_CLOCK;

    //dito UART2 clocks
    *(volatile uint32_t*)(CLOCK_CTRL_BASE + UART2_CLK_CTRL_OFFSET   ) = ENABLE_CLOCK;
}

char rxByte;

void main(void)
{

    /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;

    *(uint32_t*)(0x90000000) = 0x1234000;


    //start the clocks
    initClocks();

    //zero out the buffers, give up spinlocks in case someone is holding them for some reason
    initSpinLock();

    *(uint32_t*)(0x90000004) = 0x1234001;



    //Initialize the UART
    //initHalUart();

    circular_buf_t         buf0;
    circular_buf_stats_t   stat;
    circular_buf_reset(&buf0, (uint32_t*)SHBUF0_START, SHBUF0_SIZE, &stat,(uint32_t*)SHBUF0_HEAD_OFFSET,(uint32_t*)SHBUF0_TAIL_OFFSET);

    *(uint32_t*)(0x90000008) = 0x1234002;

    while(1)
    {
       if(circular_buf_space(&buf0) > 1)
       {
           if(true == UARTCharsAvail(UART2_OFFSET_BLOCK_START))
           {
               rxByte = UARTFIFOCharGet(UART2_OFFSET_BLOCK_START);
               circular_buf_put(&buf0, (char*)&rxByte,  sizeof(char));
               UARTCharPut(UART2_OFFSET_BLOCK_START, rxByte);
           }
       }
    }

}

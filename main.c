#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>
#include <stdbool.h>

#include "spinlock.h"
#include "sharedVariables.h"
#include "lfsr.h"
#include "uartHal.h"


#include "registerOffsets.h"
#include "uart_irda_cir.h"

#include "buffApp.h"
#include "shbuf.h"
#include "shiftParser.h"




void initClocks()
{
    //we should not really have to, but lets set the clock on for the spinlock interface just incase we forget to in linux land...
    *(volatile uint32_t*)(CLOCK_CTRL_BASE + SPINLOCK_CLK_CTRL_OFFSET) = ENABLE_CLOCK;

    //dito UART2 clocks
    *(volatile uint32_t*)(CLOCK_CTRL_BASE + UART2_CLK_CTRL_OFFSET   ) = 0;
    *(volatile uint32_t*)(CLOCK_CTRL_BASE + UART2_CLK_CTRL_OFFSET   ) = ENABLE_CLOCK;

}

char rxByte;

void main(void)
{

    /* Clear SYSCFG[STANDBY_INIT] to enable OCP master port */
    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;


    //start the clocks
    initClocks();

    //zero out the buffers, give up spinlocks in case someone is holding them for some reason
    initSpinLock();


    //Initialize the UART
    initHalUart();

    //Initialize the structure that keeps track of the shbuffers
    initSharedBuffs();

    //initialize the byte digestor
    initRxDigestor();

    //initialize the shift parser
    initShiftParser();

    volatile int z = 0;


    while(z!= 340343434)
    {

       if(true == UARTCharsAvail(UART2_OFFSET_BLOCK_START))
       {
           rxByte = UARTFIFOCharGet(UART2_OFFSET_BLOCK_START);
           processIncomingData(rxByte);
           z++;
       }

    }
    clearBufferUsed(0);

}

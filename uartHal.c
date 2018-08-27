/*
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *  * Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdint.h>
#include "uartHal.h"
#include <stdbool.h>
#include "registerOffsets.h"


/* The FIFO size on the PRU UART is 16 bytes; however, we are (arbitrarily)
 * only going to send 8 at a time */
#define FIFO_SIZE   16
#define MAX_CHARS   8

/* This hostBuffer structure is temporary but stores a data buffer */
struct {
    uint8_t msg; // Not used today
    uint8_t data[FIFO_SIZE];
} hostBuffer;

/* Making this buffer global will force the received data into memory */
uint8_t buffer[MAX_CHARS];


//this sets up the structure we will use to change the UART5 registers
am335xUart * uartHandle = (am335xUart*)UART2_OFFSET_BLOCK_START;

void uartDebug(void)
{

    uint8_t tx;
    uint8_t cnt;

    /* TODO: If modifying this to send data through the pins then PinMuxing
     * needs to be taken care of prior to running this code.
     * This is usually done via a GEL file in CCS or by the Linux driver */


    /*** INITIALIZATION ***/

    uartHandle->SYSC_bit.SOFTRESET = true;
    while(uartHandle->SYSC_bit.SOFTRESET)
    {
        //chill, hardware will reset this bit to zero once the reset is done
    }

    // Set up UART to function at 115200 baud - DLL divisor is 0x1A at 16x oversample

    //see section 19.3.8.1.2 of AM335x TRM (rev P)
    uartHandle->LCR = 0x0;
    uartHandle->LCR_bit.DIV_EN = 0x1;

    uartHandle->DLL = 0x1A;
    uartHandle->DLH = 0;

    uartHandle->LCR_bit.DIV_EN = 0x0;


    /* Enable Interrupts in UART module. This allows the main thread to poll for
     * Receive Data Available and Transmit Holding Register Empty */
    //uartHandle->IER = 0x7;

    /* If FIFOs are to be used, select desired trigger level and enable
     * FIFOs by writing to FCR. FIFOEN bit in FCR must be set first before
     * other bits are configured */
    /* Enable FIFOs for now at 1-byte, and flush them */
    uartHandle->FCR_bit.RXCLR = true;
    uartHandle->FCR_bit.TXCLR = true;
    uartHandle->FCR_bit.FIFOEN = true;

    /* Choose desired protocol settings by writing to LCR */
    /* 8-bit word, 1 stop bit, no parity, no break control and no divisor latch */
    uartHandle->LCR = 3;

    /* Enable loopback for test */
     //uartHandle->MCR_bit.LOOP = 1;

    //enable the uart and set it to 16X oversample mode.
    uartHandle->MDR1_bit.MODESELECT = UART_MODE_16X;

    /* Choose desired response to emulation suspend events by configuring
     * FREE bit and enable UART by setting UTRST and URRST in PWREMU_MGMT */
    /* Allow UART to run free, enable UART TX/RX */
    //uartHandle->PWREMU_MGMT = 0x6001;

    /*** END INITIALIZATION ***/

    /* Priming the 'hostbuffer' with a message */
    hostBuffer.data[0] = 'H';
    hostBuffer.data[1] = 'e';
    hostBuffer.data[2] = 'l';
    hostBuffer.data[3] = 'l';
    hostBuffer.data[4] = 'o';
    hostBuffer.data[5] = '!';
    hostBuffer.data[6] = '\0';


    /*** SEND SOME DATA ***/

    char temp;
    while(1)
    {
        uartHandle->THR = 24;
        temp = uartHandle->RBR;
    }


    /* Let's send/receive some dummy data */
    for (cnt = 0; cnt < MAX_CHARS; cnt++) {
        /* Load character, ensure it is not string termination */
        if ((tx = hostBuffer.data[cnt]) == '\0')
            break;
        uartHandle->THR = tx;
    }

    /*** DONE SENDING DATA ***/


    /* Halt PRU core */
    __halt();
}


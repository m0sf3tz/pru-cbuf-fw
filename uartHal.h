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

#pragma once

#define UART_MODE_16X 0x0

/* UART Register set */
typedef struct {

    /*
     * RBR and THR register pair
     * This is a unique register pair in that RBR and THR
     * share the same address. RBR is read-only while THR is
     * write-only.
     *
     * Additionally, RBR and THR share an address with DLL. To
     * read/write RBR/THR write 0 to the DLAB bit in the LCR
     * register. To modify DLL write a 1.
     *
     * DLL also has a dedicated
     * address which does not require toggling the DLAB bit.
     */
    union {
        /* PRU_UART_RBR register bit field */
        union {
            volatile uint32_t RBR;

            volatile struct {
                unsigned DATA : 8;      // 7:0
                unsigned rsvd8 : 24;        // 31:8
            } RBR_bit;
        };

        /* PRU_UART_THR register bit field */
        union {
            volatile uint32_t THR;

            volatile struct {
                unsigned DATA : 8;      // 7:0
                unsigned rsvd8 : 24;        // 31:8
            } THR_bit;
        };

    /* PRU_UART_DLL register bit field */
       union {
           volatile uint32_t DLL;

           volatile struct {
               unsigned CLOCK_LSB : 8;      // 7:0
               unsigned rsvd8 : 24;        // 31:8
           } Dll_bit;
       };

    };  // 0x0



    /* PRU_UART_DLL register bit field */
       union {
           volatile uint32_t DLH;

           volatile struct {
               unsigned CLOCK_MSB : 8;      // 7:0
               unsigned rsvd8 : 24;        // 31:8
           } DLH_bit;
       };  // 0x4



    /* FCR register bit field */
    union {
        volatile uint32_t FCR;

        volatile struct { //wrong =)
            unsigned FIFOEN : 1;        // 0
            unsigned RXCLR : 1;     // 1
            unsigned TXCLR : 1;     // 2
            unsigned DMAMODE1 : 1;      // 3
            unsigned rsvd4 : 2;     // 5:4
            unsigned RXFIFTL : 2;       // 7:6
            unsigned rsvd8 : 24;        // 31:8
        } FCR_bit;
    };  // 0x8


    /* PRU_UART_LCR register bit field */
    union {
        volatile uint32_t LCR;

        volatile struct {
            unsigned CHAR_LEN : 2;       // 1:0
            unsigned STB : 1;       // 2
            unsigned PEN : 1;       // 3
            unsigned EPS : 1;       // 4
            unsigned SP : 1;        // 5
            unsigned BC : 1;        // 6
            unsigned DIV_EN : 1;      // 7
            unsigned rsvd8 : 24;        // 31:8
        } LCR_bit;
    };  // 0xC


    /* PRU_UART_MCR register bit field */
    union {
        volatile uint32_t MCR;

        volatile struct {
            unsigned DTR : 1;     // 0
            unsigned RTS : 1;       // 1
            unsigned RISTSCH : 1;      // 2
            unsigned CDSTSCH : 1;      // 3
            unsigned LOOP : 1;      // 4
            unsigned XONEN : 1;       // 5
            unsigned rsvd8 : 26;        // 31:6
        } MCR_bit;
    };  // 0x10


    /* PRU_UART_LSR register bit field */
    union {
        volatile uint32_t LSR;

        volatile struct {
            unsigned DR : 1;        // 0
            unsigned OE : 1;        // 1
            unsigned PE : 1;        // 2
            unsigned FE : 1;        // 3
            unsigned BI : 1;        // 4
            unsigned THRE : 1;      // 5
            unsigned TEMT : 1;      // 6
            unsigned RXFIFOE : 1;       // 7
            unsigned rsvd8 : 24;        // 31:8
        } LSR_bit;
    };  // 0x14


    /* PRU_UART_MSR register bit field */
    union {
        volatile uint32_t MSR;

        volatile struct {
            unsigned DCTS : 1;      // 0
            unsigned DDSR : 1;      // 1
            unsigned TERI : 1;      // 2
            unsigned DCD : 1;       // 3
            unsigned CTS : 1;       // 4
            unsigned DSR : 1;       // 5
            unsigned RI : 1;        // 6
            unsigned CD : 1;        // 7
            unsigned rsvd8 : 24;        // 31:8
        } MSR_bit;
    };  // 0x18


    /* PRU_UART_SCR register bit field */
    union {
        volatile uint32_t SCR;

        volatile struct {
            unsigned SCR : 8;       // 7:0
            unsigned rsvd8 : 24;        // 31:8
        } SCR_bit;
    };  // 0x1C

    //MDR1
    union {
        volatile uint32_t MDR1;

        volatile struct {
            unsigned MODESELECT : 2;  // 0
            unsigned IRSLEEP : 1;       // 3
            unsigned SETTXIR : 1;       // 4
            unsigned SCT : 1;       // 5
            unsigned SIPMODE : 1;       // 6
            unsigned FRAMEENDMODE : 1;        // 7
            unsigned rsvd8 : 24;        // 31:8
        } MDR1_bit;
    };  // 0x18
    //NA
    union {
     volatile uint32_t NA1;
    };  // 0x24

    //NA
    union {
      volatile uint32_t NA2;
    };  // 0x28

    //NA
    union {
       volatile uint32_t NA3;
    };  // 0x2C

    //NA
    union {
        volatile uint32_t NA4;
    };  // 0x30

    //NA
    union {
        volatile uint32_t NA5;
    };  // 0x34

    //NA
    union {
        volatile uint32_t NA6;
    };  // 0x38

    //NA
    union {
        volatile uint32_t NA7;
    };  // 0x3C

    //NA
    union {
        volatile uint32_t NA8;
    };  // 0x40

    //NA
    union {
        volatile uint32_t NA9;
    };  // 0x44

    //NA
    union {
        volatile uint32_t NA10;
    };  // 0x48

    //NA
    union {
        volatile uint32_t NA11;
    };  // 0x4C


    //NA
    union {
            volatile uint32_t NA12;
    };  // 0x50

    //SYSC
    union {
        volatile uint32_t SYSC;

        volatile struct {
            unsigned AUTOIDLE  : 1;      // 0
            unsigned SOFTRESET : 1;      // 1
            unsigned ENAWAKEUP : 1;      // 2
            unsigned IDLEMODE  : 1;       // 3
            unsigned rsvdn     : 28;        // 31:4
        } SYSC_bit;
    };  // 0x54

    //NA
        union {
            volatile uint32_t NA14;
    };  // 0x58

    //NA
        union {
            volatile uint32_t NA15;
    };  // 0x5C

    //NA
        union {
            volatile uint32_t NA16;
    };  // 0x60

    //NA
        union {
            volatile uint32_t NA17;
    };  // 0x64

    //NA
        union {
            volatile uint32_t NA18;
    };  // 0x68

    //NA
        union {
            volatile uint32_t NA19;
    };  // 0x6c

    //NA
        union {
            volatile uint32_t NA20;
    };  // 0x70

    //NA
        union {
            volatile uint32_t NA21;
    };  // 0x74

    //NA
    union {
            volatile uint32_t NA22;
    };  // 0x78

    //NA
    union {
            volatile uint32_t NA23;
    };  // 0x7C

    //NA
        union {
            volatile uint32_t NA24;
    };  // 0x80

    //NA
        union {
            volatile uint32_t NA25;
    };  // 0x84


} am335xUart;



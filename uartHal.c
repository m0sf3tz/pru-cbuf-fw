/**
 * \file   uartEcho.c
 *
 * \brief  This example application demonstrates the working of UART for serial
 *         communication with another device/host by echoing back the data
 *         entered from serial console.
 *
 *         Application Configuration:
 *
 *          Modules Used:
 *              UART0
 *              Interrupt Controller
 *
 *          Configurable Parameters
 *              None
 *
 *          Hard-coded configuration of other parameters:
 *              1) Baud Rate - 115200 bps
 *              2) Word Length - 8 bits
 *              3) Parity - None
 *              4) Stop Bits - 1
 *              5) FIFO Threshold Levels:
 *                 a) TX Trigger Space value - 56
 *                 b) TX Threshold Level - 8 (TX FIFO Size - TX Trigger Space)
 *                 c) RX Threshold Level - 1
 *
 *         Application Use case:
 *             1) Application demonstrates the Receive/Transmit features
 *                of UART using a FIFO.
 *             2) Interrupt features related to FIFO trigger levels are
 *                demonstrated for reading/writing from/to the FIFO.
 *
 *      Running the Example:
 *          On executing the example:
 *          1) A string is displayed on the serial console of the host machine.
 *          2) The user is then expected to key in data on the serial console.
 *             The keyed in data are immediately echoed back by the application
 *             and are visible on the serial console.
 *
 */

/*
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
*/
/*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#include "uart_irda_cir.h"
#include "soc_AM335x.h"
#include "interrupt.h"
#include "evmAM335x.h"
#include "hw_types.h"
#include "consoleUtils.h"
#include "uartHal.h"
#include "registerOffsets.h"

/******************************************************************************
**              INTERNAL MACRO DEFINITIONS
******************************************************************************/
#define BAUD_RATE_57600           (57600)
#define BAUD_RATE_115200          (115200)
#define UART_MODULE_INPUT_CLK     (48000000)

/*
** The number of data bytes to be transmitted to Transmit FIFO of UART
** per generation of the Transmit Empty interrupt. This can take a maximum
** value of TX Trigger Space which is 'TX FIFO size - TX Threshold Level'.
*/
#define NUM_TX_BYTES_PER_TRANS    (56)

/******************************************************************************
**              INTERNAL FUNCTION PROTOTYPES
******************************************************************************/
static void UartFIFOConfigure(void);
static void UartBaudRateSet(void);

void initHalUart()
{

    /* Performing a module reset. */
    UARTModuleReset(SOC_UART_2_REGS);

    /* Performing FIFO configurations. */
    UartFIFOConfigure();

    /* Performing Baud Rate settings. */
    UartBaudRateSet();

    /* Switching to Configuration Mode B. */
    UARTRegConfigModeEnable(SOC_UART_2_REGS, UART_REG_CONFIG_MODE_B);

    /* Programming the Line Characteristics. */
    UARTLineCharacConfig(SOC_UART_2_REGS,
                         (UART_FRAME_WORD_LENGTH_8 | UART_FRAME_NUM_STB_1),
                         UART_PARITY_NONE);

    /* Disabling write access to Divisor Latches. */
    UARTDivisorLatchDisable(SOC_UART_2_REGS);

    /* Disabling Break Control. */
    UARTBreakCtl(SOC_UART_2_REGS, UART_BREAK_COND_DISABLE);

    /* Switching to UART16x operating mode. */
    UARTOperatingModeSelect(SOC_UART_2_REGS, UART16x_OPER_MODE);

}

/*
** A wrapper function performing FIFO configurations.
*/

static void UartFIFOConfigure(void)
{
    unsigned int fifoConfig = 0;

    /*
    ** - Transmit Trigger Level Granularity is 4
    ** - Receiver Trigger Level Granularity is 1
    ** - Transmit FIFO Space Setting is 56. Hence TX Trigger level
    **   is 8 (64 - 56). The TX FIFO size is 64 bytes.
    ** - The Receiver Trigger Level is 1.
    ** - Clear the Transmit FIFO.
    ** - Clear the Receiver FIFO.
    ** - DMA Mode enabling shall happen through SCR register.
    ** - DMA Mode 0 is enabled. DMA Mode 0 corresponds to No
    **   DMA Mode. Effectively DMA Mode is disabled.
    */
    fifoConfig = UART_FIFO_CONFIG(UART_TRIG_LVL_GRANULARITY_4,
                                  UART_TRIG_LVL_GRANULARITY_1,
                                  UART_FCR_TX_TRIG_LVL_56,
                                  1,
                                  1,
                                  1,
                                  UART_DMA_EN_PATH_SCR,
                                  UART_DMA_MODE_0_ENABLE);

    /* Configuring the FIFO settings. */
    UARTFIFOConfig(SOC_UART_2_REGS, fifoConfig);
}

/*
** A wrapper function performing Baud Rate settings.
*/

static void UartBaudRateSet(void)
{
    unsigned int divisorValue = 0;

    /* Computing the Divisor Value. */
    divisorValue = UARTDivisorValCompute(UART_MODULE_INPUT_CLK,
                                         BAUD_RATE_57600,
                                         UART16x_OPER_MODE,
                                         UART_MIR_OVERSAMPLING_RATE_42);

    /* Programming the Divisor Latches. */
    UARTDivisorLatchWrite(SOC_UART_2_REGS, divisorValue);
}

/*
** A wrapper function performing Interrupt configurations.
*/

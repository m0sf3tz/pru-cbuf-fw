/*
 * buffApp.c
 *
 *  Created on: Sep 8, 2018
 *      Author: Sam2
 */



#include <stdint.h>
#include <pru_cfg.h>
#include <cstring>
#include <stdbool.h>

#include "sharedVariables.h"
#include "spinlock.h"
#include "shbuf.h"
#include "projectDefines.h"

#include "shiftParser.h"
#include "buffApp.h"



//These should be static... but if we set them
//to static CCS is not putting them in the
//correct BSS section? Unure why... don't want to dig in
uint8_t   currentBuff;
uint32_t  rxIndex;
bool      processingSector;

void initRxDigestor()
{
    currentBuff = getFreeBuffer();
    rxIndex     = 0;
}


void processIncomingData(uint8_t rxByte)
{
    magicKey_t key = shiftInRxAndSearchForMagicKeys(rxByte);

    if(processingSector == SEARCHING_FOR_SECTOR)
    {
        if (key == START_SECTOR)
        {
            //we found our first sector magic key, start storing the
            //incoming rx data into the currentBuff;
            processingSector =  PROCESSING_SECTOR;
            rxIndex = TRASMIT_SECTOR_B0_INDEX;
            currentBuff = getFreeBuffer();
        }
    }
    else
    {
        if (key == START_SECTOR)
        {
            //a new start key, start processing sector again (this is an error condition)
            rxIndex = TRASMIT_SECTOR_B0_INDEX;
        }
        else if(key == END_SECTOR)
        {
            if (rxIndex == FINAL_INDEX_SAMPLE)
            {
                //we need to put this because we don't start storing values until we
                //have finished getting the start magic key,
                //hence we need to manually put the magic key back in the buffer so it makes sense
                putBuff(currentBuff,NEW_TRASMITION_HEADER_B0_INDEX,NEW_TRASMITION_HEADER_B0);
                putBuff(currentBuff,NEW_TRASMITION_HEADER_B1_INDEX,NEW_TRASMITION_HEADER_B1);
                putBuff(currentBuff,NEW_TRASMITION_HEADER_B2_INDEX,NEW_TRASMITION_HEADER_B2);
                putBuff(currentBuff,NEW_TRASMITION_HEADER_B3_INDEX,NEW_TRASMITION_HEADER_B3);

                //still gotta put the last byte in
                putBuff(currentBuff,rxIndex,rxByte);
                //found a full sector
                setBufferUsed(currentBuff);
                currentBuff = getFreeBuffer();
                processingSector =  SEARCHING_FOR_SECTOR;
            }
        }
        else
        {
            putBuff(currentBuff,rxIndex,rxByte);

            rxIndex++;

            if(rxIndex == TOTAL_BYTES_IN_SECTOR)
            {
                //should have gotten an end key by now
                //start scanning for a new sector
                processingSector =  SEARCHING_FOR_SECTOR;
            }
        }
    }
}

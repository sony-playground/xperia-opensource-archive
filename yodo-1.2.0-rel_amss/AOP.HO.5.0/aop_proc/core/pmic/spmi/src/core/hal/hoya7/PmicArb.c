/**
 * @file:  PmicArb.c
 * 
 * Copyright (c) 2013-2016 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2021/10/26 22:03:12 $
 * $Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/spmi/src/core/hal/hoya7/PmicArb.c#1 $
 * $Change: 33677139 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 8/06/15  More than 256 chan support.
 * 1/20/15  Multiple bus support
 * 12/5/14  Added check to limit the spmi channels equal to spmi interrupts
 * 11/3/14  Automatic channel assignment
 * 05/8/14  Moved the clock status check to other file.
 * 10/1/13  Initial Version
 */

#include "PmicArb.h"
#include "SpmiUtils.h"
#include "SpmiHal.h"
#include "SpmiLogs.h"
#include "SpmiOs.h"
#include "SpmiInfo.h"

//******************************************************************************
// Macros / Definitions / Constants
//******************************************************************************

#define INVALID_SID ((uint8)0x10)
#define INVALID_OWNER ((uint8)0x10)
#define INVALID_DATA ((uint16)0x400)
#define INVALID_VRM_DATA ((uint16)0x100)
#define INVALID_PERIPH_ID 0

// Max number of bytes we can read/write at a time.
#define MAX_TRANSACTION_LEN 8

//******************************************************************************
// Global Data
//******************************************************************************


//******************************************************************************
// Local Helper Functions
//******************************************************************************


static void writeSpmiData(uint8 *base_addr, uint16 channel, uint8* data, uint32 bytesToWrite)
{
    uint32 i;
    uint32 tmp = 0;
    
    for(i = 0; i < sizeof(uint32) && bytesToWrite > 0; i++, bytesToWrite--) {
        ((uint8*)&tmp)[i] = data[i];
    }
    
    SPMI_HWIO_OUT( HWIO_PMIC_ARB_CHNLn_WDATA0_ADDR( base_addr, channel ), tmp );
    
    if(bytesToWrite > 0)
    {
        tmp = 0;
        for(i = 0; i < sizeof(uint32) && bytesToWrite > 0; i++, bytesToWrite--) {
            ((uint8*)&tmp)[i] = data[i + sizeof(uint32)];
        }
        
        SPMI_HWIO_OUT( HWIO_PMIC_ARB_CHNLn_WDATA1_ADDR( base_addr, channel ), tmp );
    }
}

static void readSpmiData(uint8 *base_addr, uint8 owner, uint16 channel, uint8* data, uint32 bytesToRead)
{
    uint32 i;

    uint32 spmiData = SPMI_HWIO_IN( HWIO_PMIC_ARB_OBSq_CHNLn_RDATA0_ADDR( base_addr, owner, channel ) );
        
    for(i = 0; i < sizeof(uint32) && bytesToRead > 0; i++, bytesToRead--) {
        data[i] = ((uint8*)&spmiData)[i];
    }

    if(bytesToRead > 0)
    {
        spmiData = SPMI_HWIO_IN( HWIO_PMIC_ARB_OBSq_CHNLn_RDATA1_ADDR( base_addr, owner, channel ) );

        for(i = 0; i < sizeof(uint32) && bytesToRead > 0; i++, bytesToRead--) {
            data[i + sizeof(uint32)] = ((uint8*)&spmiData)[i];
        }
    }
}

static Spmi_Result waitForStatusDone(uint8 busId, uint8 *base_addr, uint8 owner, boolean isObserver, uint16 channel)
{
    uint32 status = 0;
    uint32 timeout = SPMI_TIMEOUT_USEC;
    Spmi_Result result = SPMI_SUCCESS;
    
    while(status == 0 && timeout-- > 0)
    {
        SpmiOs_Wait( 1 );
        status = isObserver ? SPMI_HWIO_IN( HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR( base_addr, owner, channel ) ) :
                              SPMI_HWIO_IN( HWIO_PMIC_ARB_CHNLn_STATUS_ADDR( base_addr, channel ) );
    }
    
    if(status & HWIO_PMIC_ARB_CHNLn_STATUS_DROPPED_BMSK) 
    {
        result = SPMI_FAILURE_TRANSACTION_DROPPED;
    }
    else if(status & HWIO_PMIC_ARB_CHNLn_STATUS_DONE_BMSK)
    {
        if(status & HWIO_PMIC_ARB_CHNLn_STATUS_FAILURE_BMSK) {
            result = SPMI_FAILURE_TRANSACTION_FAILED;
        }
        else if(status & HWIO_PMIC_ARB_CHNLn_STATUS_DENIED_BMSK) {
            result = SPMI_FAILURE_TRANSACTION_DENIED;
        }
    }
    else if(SPMI_HWIO_IN_FIELD(HWIO_SPMI_GENI_CTRL_ADDR( base_addr, busId ), HWIO_SPMI_GENI_CTRL_M_GENI_DISABLE) ) {
        result = SPMI_FAILURE_BUS_DISABLED;
    }
    else {
        result = SPMI_FAILURE_TRANSACTION_TIMEOUT;
    }

    return result;
}

static __inline boolean isTransactionDone(uint8 *base_addr, uint8 owner, boolean isObserver, uint16 channel)
{
    if(isObserver) {
        return SPMI_HWIO_IN_FIELD( HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_ADDR( base_addr, owner, channel ),
                                   HWIO_PMIC_ARB_OBSq_CHNLn_STATUS_DONE );
    } else {
        return SPMI_HWIO_IN_FIELD( HWIO_PMIC_ARB_CHNLn_STATUS_ADDR( base_addr, channel ),
                                   HWIO_PMIC_ARB_CHNLn_STATUS_DONE );
    }
}

static __inline void writeCommand(uint8 *base_addr,
                                  uint8 owner, 
                                  boolean isObserver,
                                  PmicArbCmd cmd,
                                  uint16 channel,
                                  Spmi_AccessPriority priority,
                                  uint8 regOffset,
                                  uint32 len)
{
    if(isObserver) 
    {
        SPMI_HWIO_OUT( HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDR( base_addr, owner, channel ),
                      (cmd                      << HWIO_PMIC_ARB_OBSq_CHNLn_CMD_OPCODE_SHFT)   |
                      (SPMI_ACCESS_PRIORITY_LOW << HWIO_PMIC_ARB_OBSq_CHNLn_CMD_PRIORITY_SHFT) |
                      (regOffset                << HWIO_PMIC_ARB_OBSq_CHNLn_CMD_ADDRESS_SHFT)  |
                      (len                      << HWIO_PMIC_ARB_OBSq_CHNLn_CMD_BYTE_CNT_SHFT) );
    }
    else 
    {
        SPMI_HWIO_OUT( HWIO_PMIC_ARB_CHNLn_CMD_ADDR( base_addr, channel ),
                      (cmd       << HWIO_PMIC_ARB_CHNLn_CMD_OPCODE_SHFT)   |
                      (priority  << HWIO_PMIC_ARB_CHNLn_CMD_PRIORITY_SHFT) |
                      (regOffset << HWIO_PMIC_ARB_CHNLn_CMD_ADDRESS_OFFSET_SHFT)  |
                      (len       << HWIO_PMIC_ARB_CHNLn_CMD_BYTE_CNT_SHFT) );
    }
}


//******************************************************************************
// Public API Functions
//******************************************************************************

void PmicArb_GetHwStatus(SpmiDevInfo *pDev, PmicArbHwStatus* status)
{
    uint8 * base_addr = pDev->baseAddrs;    
    if(status == NULL) {
        return;
    }
    
    status->irqStatus = SPMI_HWIO_IN( HWIO_SPMI_PROTOCOL_IRQ_STATUS_ADDR( base_addr, pDev->uDevIdx ) );
    status->geniStatus = SPMI_HWIO_IN( HWIO_SPMI_GENI_STATUS_ADDR( base_addr, pDev->uDevIdx ) );
    status->geniCtrl = SPMI_HWIO_IN( HWIO_SPMI_GENI_CTRL_ADDR( base_addr, pDev->uDevIdx ) );
}


Spmi_Result PmicArb_FindChannel(SpmiDevInfo *pDev, uint8 slaveId, uint8 periph, uint8 owner, uint16* channel)
{
    Spmi_Result rslt = SPMI_FAILURE_CHANNEL_NOT_FOUND;
    uint16 idx;
    
    idx = pDev->periphMap[periph];
    
    while ((idx & INVALID_DATA) == 0)
    {
        ChannelMapEntry* entry = &pDev->channelMap[idx];
        
        // If only sid matches, save the channel id and continue looping for owner match
        if (entry->sid == slaveId) {

            rslt = SPMI_SUCCESS;
            *channel = idx;

            // If both owner and sid match, break and return the channel id
            if(entry->owner == owner) {
                break;
            }
        }

        idx = entry->nextIdx;
    }

    // This peripheral is not supported
    if(rslt != SPMI_SUCCESS) {
        SPMI_LOG_TRACE( "Chan not found: bid: %d, sid %d, periph: 0x%x", bid, slaveId, periph );
    } else {
        SPMI_LOG_TRACE( "Found chan: bid: %d, sid %d, periph: 0x%x = %d", bid, slaveId, periph, *channel );
    }

    return rslt;
}

Spmi_Result PmicArb_FindVrmId(SpmiDevInfo *pDev, uint8 sid, uint8 periph, uint16* vrmId)
{
    int16 idx;

    if(periph == INVALID_PERIPH_ID) {

        return SPMI_FAILURE_INVALID_PERIPH_ID;
    }

    idx = pDev->periphMap[periph];

    while ((idx & INVALID_DATA) == 0)
    {
        ChannelMapEntry* entry = &pDev->channelMap[idx];

        if ((entry->sid == sid) && (entry->vrmId != INVALID_VRM_DATA))
        {
            *vrmId = entry->vrmId;
            return SPMI_SUCCESS;
        }

        idx = entry->nextIdx;
    }

    return SPMI_FAILURE_VRM_ID_NOT_FOUND;
}


Spmi_Result PmicArb_ExecuteCommand(SpmiDevInfo *pDev,
                                   PmicArbCmd cmd,
                                   Spmi_AccessPriority priority,
                                   uint8 owner,
                                   uint16 channel,
                                   uint16 offset,
                                   uint8* data,
                                   uint32 dataLen,
                                   uint32* bytesTransacted)
{
    uint32 tmp;
    boolean doRead = FALSE;
    boolean doWrite = FALSE;
    uint8 * base_addr = pDev->baseAddrs;
    
         
    if(data == NULL || dataLen == 0) {
        return SPMI_FAILURE_INVALID_BUFFER;
    }
    
    if(bytesTransacted == NULL) {
        bytesTransacted = &tmp;
    }

    *bytesTransacted = 0;
    channel += pDev->busChanStart;
    
    switch(cmd)
    {
        case PMIC_ARB_CMD_EXTENDED_REG_READ_LONG:
            doRead = TRUE;
            break;
            
        case PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG:
            doWrite = TRUE;
            break;

        default:
            return SPMI_FAILURE_COMMAND_NOT_SUPPORTED;
    }
    
    while(dataLen > 0)
    {
        Spmi_Result result;
        
        // Check if the Done bit is set. If not, the previous transaction is stuck
        if(!isTransactionDone( base_addr, owner, doRead, channel )) {
            return SPMI_FAILURE_BUS_BUSY;
        }
    
        uint32 len = dataLen > MAX_TRANSACTION_LEN ? MAX_TRANSACTION_LEN : dataLen;
        
        if(doWrite) {
            writeSpmiData( base_addr, channel, data + *bytesTransacted, len );
        }
        
        // This is the signal to start the transaction
        // len - 1 because value of 0 means 1 byte and increments from there
        writeCommand( base_addr, owner, doRead, cmd, channel, priority, (uint8)(offset + *bytesTransacted), len - 1 );
        
        if((result = waitForStatusDone( pDev->uDevIdx, base_addr, owner, doRead, channel )) != SPMI_SUCCESS) {
            return result;
        }
        
        if(doRead) {
            readSpmiData( base_addr, owner, channel, data + *bytesTransacted, len );
        }
        
        dataLen -= len;
        *bytesTransacted += len;
    }
    
    return SPMI_SUCCESS;
}

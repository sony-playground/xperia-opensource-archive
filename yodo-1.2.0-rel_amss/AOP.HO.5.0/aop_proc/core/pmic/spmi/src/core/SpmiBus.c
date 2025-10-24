/**
 * @file:  SpmiBus.c
 * 
 * Copyright (c) 2013-2016 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2021/10/26 22:03:12 $
 * $Header: //components/rel/aop.ho/5.0/aop_proc/core/pmic/spmi/src/core/SpmiBus.c#1 $
 * $Change: 33677139 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 1/20/15  Multiple bus support
 * 11/3/14  Automatic channel assignment
 * 6/19/14  Log Fatal if bus is busy
 * 05/8/14  To check the clock status for every transaction failure reason
 * 10/1/13  Initial Version
 */

#include "SpmiBus.h"
#include "SpmiOs.h"
#include "SpmiLogs.h"
#include "PmicArb.h"
#include "SpmiInfo.h"
#include "SpmiBusInternal.h"

//******************************************************************************
// Macros / Definitions
//******************************************************************************

#define INIT_CHECK() if(!spmiDrv.initialized) { return SPMI_FAILURE_NOT_INITIALIZED; }

//******************************************************************************
// Global Data
//******************************************************************************

SpmiDrv spmiDrv = {0};
boolean freeIsrNodes = FALSE;

//******************************************************************************
// Local Helper Functions
//******************************************************************************

static inline void debugTransStart(PmicArbCmd cmd, uint8 busId, uint8 slaveId, uint16 address, uint32 len)
{
    SPMI_LOG_VERBOSE( "cmd %d / busId=%d sid: 0x%02x / addr: %x / len: %d", cmd, busId, slaveId, address, len );

    spmiDrv.debug.busIdx = (spmiDrv.debug.busIdx + 1) % NUM_DEBUG_TRANSACTIONS;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].state = STARTED;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].cmd = cmd;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].busId = busId;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].sid = slaveId;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].pid = address;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].dataLen = len;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].tries = 0;
    spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].startTime = SpmiOs_GetTimeTick();
}

static inline void debugTransEnd(PmicArbCmd cmd, uint8 busId, uint8 slaveId, uint16 address, uint32 len,
                                 uint8* data, uint8 tries, Spmi_Result rslt)
{
    if(spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].cmd == cmd &&
       spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].busId == busId &&
       spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].sid == slaveId &&
       spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].pid == address &&
       spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].dataLen == len) 
    {
        spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].state = FINISHED;
        spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].result = rslt;
        spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].tries = tries;
        spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].duration = 
        SpmiOs_GetTimeTick() - spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].startTime;
        
        if(data != NULL) {
            spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].data0 = *data;
        }
    }
    else {
        spmiDrv.debug.syncFlag = TRUE;
    }
    
    if(rslt != SPMI_SUCCESS)
    {
        spmiDrv.debug.errorIdx = (spmiDrv.debug.errorIdx + 1) % NUM_DEBUG_FAILURES;
        spmiDrv.debug.errorTrans[spmiDrv.debug.errorIdx].info = spmiDrv.debug.busTrans[spmiDrv.debug.busIdx];
        
        PmicArb_GetHwStatus( SPMI_PDEV(spmiDrv.pSpmiInfo, busId), &spmiDrv.debug.errorTrans[spmiDrv.debug.errorIdx].hwStatus );
        SPMI_LOG_WARNING( "cmd: %d / busId=%d sid: 0x%02x / addr: 0x%04x / len: %d / rslt: %d / tries: %d", 
                          cmd, busId, slaveId, address, len, rslt,
                          spmiDrv.debug.busTrans[spmiDrv.debug.busIdx].tries);
    }
}

static Spmi_Result debugExecute(PmicArbCmd cmd,
                                Spmi_AccessPriority priority,
                                uint8 busId,
                                uint8 slaveId,
                                uint16 address,
                                uint8* data,
                                uint32 len,
                                uint32* bytesTransacted)
{
    Spmi_Result rslt;
    boolean retry;
    uint8 tries = 0;
    SpmiDevInfo *pDev;
    uint16 channel;
    

    INIT_CHECK();

    SpmiOs_Lock();
    
    if(busId >= SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo)) {
       return SPMI_FAILURE_INVALID_BUS_ID;
    }

    debugTransStart( cmd, busId, slaveId, address, len );
    
    pDev = SPMI_PDEV(spmiDrv.pSpmiInfo,busId);
    do 
    {
        tries++;
        retry = FALSE;
        rslt = PmicArb_FindChannel(pDev, slaveId, REG_ADDR_TO_PERIPH_ID( address ), spmiDrv.pSpmiInfo->owner, &channel);
        if (SPMI_SUCCESS == rslt)
        {
               rslt = PmicArb_ExecuteCommand( pDev, cmd, priority,
                                              spmiDrv.pSpmiInfo->owner, channel,
                                              REG_ADDR_TO_REG_OFFSET( address ),
                                              data, len, bytesTransacted );
        }
    } while(retry);

    debugTransEnd( cmd, busId, slaveId, address, len, data, tries, rslt );
    
    // Fail-fast by catching some irrecoverable errors
    if(rslt == SPMI_FAILURE_TRANSACTION_TIMEOUT) {
        SPMI_LOG_FATAL( "Timeout while executing SPMI transaction" );
    }
    else if(rslt == SPMI_FAILURE_BUS_BUSY) {
        SPMI_LOG_FATAL( "SPMI bus busy" );
    }

    SpmiOs_Unlock();
    
    return rslt;
}

//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result SpmiBus_DeInit()
{
    spmiDrv.initialized = FALSE;
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBus_ReadLong(uint8 busId,
                             uint32 slaveId,
                             Spmi_AccessPriority priority,
                             uint32 address,
                             uint8* data,
                             uint32 len,
                             uint32* bytesRead)
{
    return debugExecute( PMIC_ARB_CMD_EXTENDED_REG_READ_LONG, priority, busId, slaveId, address, data, len, bytesRead );
}

Spmi_Result SpmiBus_WriteLong(uint8 busId,
                              uint32 slaveId,
                              Spmi_AccessPriority priority,
                              uint32 address,
                              uint8* data,
                              uint32 len)
{
    return debugExecute( PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG, priority, busId, slaveId, address, data, len, NULL );
}

Spmi_Result SpmiBus_GetVrmId(uint8 vSlaveId, uint8 periphId, uint16* vrmId)
{
    Spmi_Result rslt;
    uint8 slaveId;
    uint8 busId;
    SpmiDevInfo *pDev;

    INIT_CHECK();

    if(vrmId == NULL) {

        return SPMI_FAILURE_INVALID_BUFFER;
    }
    
    spmiDecodeVSid( vSlaveId, &busId, &slaveId );
    if(busId >= SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo)) {
       return SPMI_FAILURE_INVALID_BUS_ID;
    }
    
    pDev = SPMI_PDEV(spmiDrv.pSpmiInfo,busId);

    rslt = PmicArb_FindVrmId(pDev, slaveId, periphId, vrmId);
    
    return rslt;
}

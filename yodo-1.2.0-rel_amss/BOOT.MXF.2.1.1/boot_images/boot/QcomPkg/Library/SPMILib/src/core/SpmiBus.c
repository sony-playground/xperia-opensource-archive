/**
 * @file:  SpmiBus.c
 * 
 * Copyright (c) 2013-2022 by Qualcomm Technologies 
 * Incorporated. All Rights Reserved. 
 * 
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SPMILib/src/core/SpmiBus.c#1 $
 * $Change: 39147961 $ 
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

#include <Library/KernelLib.h>
#include "SpmiBus.h"
#include "SpmiOs.h"
#include "SpmiLogs.h"
#include "PmicArb.h"
#include "SpmiInfo.h"
#include "SpmiBusInternal.h"
#include "SpmiPic.h"
#include "SpmiCoreHwio.h"
#include "CoreVerify.h"
//******************************************************************************
// Macros / Definitions
//******************************************************************************

#define NUM_DEBUG_TRANSACTIONS 10
#define NUM_DEBUG_FAILURES 5

#define INIT_CHECK() do {\
  if(!spmiDrv.initialized) { \
    return SPMI_FAILURE_NOT_INITIALIZED; \
    }\
  } while(0)

typedef enum {
    NOT_SET,
    STARTED,
    FINISHED,
} BusDbgState;

typedef struct {
    uint8 busId;
    uint8 sid;
    uint16 pid;
    uint8 data0;
    Spmi_Result result;
    PmicArbCmd cmd;
    uint8 dataLen;
    uint64 startTime;
    uint32 duration;
    uint8 tries;
    BusDbgState state;
} BusDbgInfo;

typedef struct {
    BusDbgInfo info;
    PmicArbHwStatus hwStatus;
} BusErrDbgInfo;

typedef struct
{
    uint8 busIdx;
    uint8 errorIdx;
    uint8 isrIdx;
    BusDbgInfo busTrans[NUM_DEBUG_TRANSACTIONS];
    BusErrDbgInfo errorTrans[NUM_DEBUG_FAILURES];
    uint16 rsltCnt[SPMI_RESULT_MAX];
    boolean syncFlag;
} SpmiBusDebugInfo;

typedef struct 
{
    boolean initialized;
    uint16  uid;
    SpmiBusDebugInfo debug;
    SpmiInfo        *pSpmiInfo;
} SpmiDrv;

//******************************************************************************
// Global Data
//******************************************************************************

SpmiDrv spmiDrv = {0};
boolean freeIsrNodes = FALSE;
LockHandle* pSpmiBusLock = NULL;


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

        if(rslt < SPMI_RESULT_MAX) {
            spmiDrv.debug.rsltCnt[rslt]++;
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
    Spmi_Result rslt = SPMI_SUCCESS;
    boolean retry;
    uint8 tries = 0;
    SpmiDevInfo *pDev;
    uint16 channel;
    

    INIT_CHECK();

    if(busId >= SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo)) {
       return SPMI_FAILURE_INVALID_BUS_ID;
    }

    debugTransStart( cmd, busId, slaveId, address, len );
    
    pDev = SPMI_PDEV(spmiDrv.pSpmiInfo,busId);
    do 
    {
        tries++;
        retry = FALSE;
        rslt = SPMI_SUCCESS;

        if (busId != 0)
        {
          rslt = (PmicArb_IsBusEnabled(pDev)) ? SPMI_SUCCESS : SPMI_FAILURE_INVALID_BUS_ID;
        }

        if (rslt == SPMI_SUCCESS)
        {
          rslt = PmicArb_FindChannel(pDev, slaveId, REG_ADDR_TO_PERIPH_ID( address ), spmiDrv.pSpmiInfo->owner, &channel);
        }

        if (SPMI_SUCCESS == rslt) {
           rslt = PmicArb_ExecuteCommand( pDev, cmd, priority,
                                          spmiDrv.pSpmiInfo->owner, channel,
                                          REG_ADDR_TO_REG_OFFSET( address ),
                                          data, len, bytesTransacted );     
        }

        // Adjust result if a more specific root cause can be found
        if(rslt != SPMI_SUCCESS) 
        {
            if(SpmiOs_GetAhbClkState( pDev ) == SPMI_CLK_OFF) {
                rslt = SPMI_FAILURE_AHB_CLK_IS_OFF;
            }
            else if(SpmiOs_GetSerialClkState( pDev ) == SPMI_CLK_OFF) {
                rslt = SPMI_FAILURE_SERIAL_CLK_IS_OFF;
            }

            retry = SpmiOs_HandleTransactionError( pDev, &rslt, cmd, slaveId, address, tries );
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
    
    return rslt;
}

//******************************************************************************
// Public API Functions
//******************************************************************************
Spmi_Result SpmiBus_Init()
{
    Spmi_Result rslt;
    uint32 bid;
    SpmiDevInfo *pDev;

    if(spmiDrv.initialized) {
        return PmicArb_UpdateCache(spmiDrv.pSpmiInfo);
    }
    
    SPMI_LOG_INIT();

    if((rslt = SpmiOs_Init(&spmiDrv.pSpmiInfo)) != SPMI_SUCCESS) {
        return rslt;
    }
    
    if((rslt = PmicArb_Init( spmiDrv.pSpmiInfo)) != SPMI_SUCCESS) {
        return rslt;
    }

    spmiDrv.pSpmiInfo->hasInterruptSupport = FALSE;
    
    for(bid = 0; bid < SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo); bid++)
    {
        pDev = SPMI_PDEV(spmiDrv.pSpmiInfo, bid);

        if((rslt = SpmiPic_Init( pDev, spmiDrv.pSpmiInfo->owner)) != SPMI_SUCCESS) {
            return rslt;
        }
    }

    InitRecursiveLock ("SpmiBus", &pSpmiBusLock);
    spmiDrv.initialized = TRUE;

    return SPMI_SUCCESS;
}

void SpmiBus_EnableAuxBus(uint32 busId)
{
  uint8 *base_addr = NULL;
  SpmiDevInfo *pDev;
  pDev = SPMI_PDEV(spmiDrv.pSpmiInfo, busId);
  if(pDev == NULL)
  {
    return;
  }

  base_addr = pDev->baseAddrs;
  SPMI_HWIO_OUT_SET( HWIO_SPMI_CFG_REG_ADDR( base_addr, pDev->uDevIdx ), HWIO_SPMI_CFG_REG_ARBITER_ENABLE_BMSK );

}


Spmi_Result SpmiBus_DeInit()
{
    spmiDrv.initialized = FALSE;
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBus_ReadLong(uint32 busId,
                             uint32 slaveId,
                             Spmi_AccessPriority priority,
                             uint32 address,
                             uint8* data,
                             uint32 len,
                             uint32* bytesRead)
{
  Spmi_Result rslt = SPMI_SUCCESS;

  AcquireLock(pSpmiBusLock);
  rslt = debugExecute( PMIC_ARB_CMD_EXTENDED_REG_READ_LONG, priority, busId, slaveId, address, data, len, bytesRead );
  ReleaseLock(pSpmiBusLock);

  return rslt;
}

Spmi_Result SpmiBus_WriteLong(uint32 busId,
                              uint32 slaveId,
                              Spmi_AccessPriority priority,
                              uint32 address,
                              uint8* data,
                              uint32 len)
{
  Spmi_Result rslt = SPMI_SUCCESS;
  INIT_CHECK();

  AcquireLock(pSpmiBusLock);
  rslt = debugExecute( PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG, priority, busId, slaveId, address, data, len, NULL);
  ReleaseLock(pSpmiBusLock);

  return rslt;
}

Spmi_Result SpmiBus_PBSWriteLong(uint32 busId,
                              uint32 slaveId,
                              Spmi_AccessPriority priority,
                              uint32 address,
                              uint8* data,
                              uint32 len)
{
  Spmi_Result rslt = SPMI_SUCCESS;
  INIT_CHECK();

  AcquireLock(pSpmiBusLock);
  rslt = debugExecute( PMIC_ARB_CMD_EXTENDED_PBS_REG_WRITE_LONG, priority, busId, slaveId, address, data, len, NULL);
  ReleaseLock(pSpmiBusLock);

  return rslt;
}

Spmi_Result SpmiBus_Command(uint32 busId, uint32 slaveId, Spmi_AccessPriority priority, Spmi_Command cmd)
{
    return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
}

Spmi_Result SpmiBus_ReadModifyWriteLongByte(uint32 busId,
                                            uint32 slaveId,
                                            Spmi_AccessPriority priority,
                                            uint32 address,
                                            uint8 data,
                                            uint8 mask,
                                            uint8 *byteWritten)
{
    Spmi_Result rslt;
    uint8 readData;
    INIT_CHECK();

    AcquireLock(pSpmiBusLock);
    if((rslt = SpmiBus_ReadLong( busId, slaveId, priority, address, &readData, 1, NULL )) != SPMI_SUCCESS) {
        ReleaseLock(pSpmiBusLock);
        return rslt;
    }

    readData &= ~mask;
    readData |= data & mask;

    if((rslt = SpmiBus_WriteLong( busId, slaveId, priority, address, &readData, 1 )) != SPMI_SUCCESS) {
        ReleaseLock(pSpmiBusLock);
        return rslt;
    }

    *byteWritten = readData;

    ReleaseLock(pSpmiBusLock);

    return SPMI_SUCCESS;
}


Spmi_Result SpmiBus_GetNumDevices(uint8 *uNumDevices)
{
    INIT_CHECK();
    *uNumDevices = spmiDrv.pSpmiInfo->uNumDevices;
    return SPMI_SUCCESS;
}

SpmiDevInfo *SpmiBus_GetDevInfo(uint8 vSlaveId)
{
    uint8 busId;

    spmiDecodeVSid( vSlaveId, &busId, NULL );

    if( !spmiDrv.initialized ||
        busId >= SPMI_NUM_BUSES_SUPPORTED(spmiDrv.pSpmiInfo) )
    {
        return NULL;
    }
    
    return SPMI_PDEV(spmiDrv.pSpmiInfo,busId);
}

SpmiInfo* SpmiBus_GetInfo(void)
{
    if(!spmiDrv.initialized)
    {
        return NULL;
    }
    
    return spmiDrv.pSpmiInfo;
}

Spmi_Result SpmiBus_GetChannel(uint8 busId, uint8 slaveId, uint8 periphId, uint16* channel)
{
    Spmi_Result rslt = SPMI_SUCCESS;
    SpmiDevInfo *pDev;
    INIT_CHECK();
    pDev = SPMI_PDEV(spmiDrv.pSpmiInfo, busId);
    uint16 irqOwnerMask = 0, periphOwnerMask = 0;

    if(channel == NULL)
    {
      return SPMI_FAILURE_INVALID_PARAMETER;
    }

    if((rslt = PmicArb_FindChannel( pDev, slaveId, periphId, spmiDrv.pSpmiInfo->owner, channel )) != SPMI_SUCCESS)
    {
        return rslt;
    }

    slaveId = 0;
    periphId = 0;
    rslt = PmicArb_GetChannelInfo(pDev, *channel, &slaveId, &periphId, 
                                   &irqOwnerMask, &periphOwnerMask);

    if (periphOwnerMask != pDev->ownerMaskMap[spmiDrv.pSpmiInfo->owner])
    {
      return SPMI_FAILURE_INVALID_OWNER;
    }

    return rslt;
}

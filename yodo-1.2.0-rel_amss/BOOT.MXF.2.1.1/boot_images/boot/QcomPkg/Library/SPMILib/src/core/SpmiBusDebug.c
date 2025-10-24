/**
 * @file:  SpmiBusDebug.c
 * 
 * Copyright (c) 2013-2022 by Qualcomm Technologies 
 * Incorporated. All Rights Reserved. 
 * 
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SPMILib/src/core/SpmiBusDebug.c#1 $
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

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIHWIO.h>
#include "npa.h"
#include "ClockDefs.h"

//******************************************************************************
// Macros / Definitions
//******************************************************************************

#define NUM_DEBUG_TRANSACTIONS 10
#define NUM_DEBUG_FAILURES 5

#define INIT_CHECK() do {\
  if(!spmiDrvDebug.initialized) { \
    return SPMI_FAILURE_NOT_INITIALIZED; \
    }\
  } while(0)

#define PMIC_ARB_SPMI_DBG_QDSS_CLK_CLIENT_NAME "/pmic-arb/spmi-dbg"

typedef enum {
    NOT_SET,
    STARTED,
    FINISHED,
} BusDbgState;

typedef struct {
    uint64 startTime;
    Spmi_Result result;
    PmicArbCmd cmd;
    BusDbgState state;
    uint32 duration;
    uint16 pid;
    uint8 vsid;
    uint8 data0;
    uint8 dataLen;
    uint8 tries;
} BusDbgInfo;

typedef struct {
    BusDbgInfo info;
    PmicArbHwStatus hwStatus;
} BusErrDbgInfo;

typedef struct
{
    BusDbgInfo busTrans[NUM_DEBUG_TRANSACTIONS];
    BusErrDbgInfo errorTrans[NUM_DEBUG_FAILURES];
    uint16 rsltCnt[SPMI_RESULT_MAX];
    uint8 busIdx;
    uint8 errorIdx;
    uint8 isrIdx;
    boolean syncFlag;
} SpmiBusDebugInfo;

typedef struct 
{
    SpmiBusDebugInfo  debug;
    SpmiInfo          *pSpmiInfo;
    npa_client_handle hQDSSClkVote;
    uint16            uid;
    boolean           initialized;
} SpmiDrv;

//******************************************************************************
// Global Data
//******************************************************************************

SpmiDrv spmiDrvDebug = {0};
boolean freeIsrNodes = FALSE;
static LockHandle* pSpmiBusLock = NULL;
static EFI_HWIO_PROTOCOL *HWIOProtocol = NULL;
extern SpmiDebugFuseInfo spmiDbgFuse;

//******************************************************************************
// Local Helper Functions
//******************************************************************************

static inline void debugTransStart(PmicArbCmd cmd, uint8 vSlaveId, uint16 address, uint32 len)
{
    SPMI_LOG_VERBOSE( "cmd %d / vsid: 0x%02x / addr: %x / len: %d", cmd, vSlaveId, address, len );
    
    spmiDrvDebug.debug.busIdx = (spmiDrvDebug.debug.busIdx + 1) % NUM_DEBUG_TRANSACTIONS;
    spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].state = STARTED;
    spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].cmd = cmd;
    spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].vsid = vSlaveId;
    spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].pid = address;
    spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].dataLen = len;
    spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].tries = 0;
    spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].startTime = SpmiOs_GetTimeTick();
}

static inline void debugTransEnd(PmicArbCmd cmd, uint8 vSlaveId, uint16 address, uint32 len, 
                                 uint8* data, uint8 tries, Spmi_Result rslt)
{
    if(spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].cmd == cmd &&
       spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].vsid == vSlaveId &&
       spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].pid == address &&
       spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].dataLen == len) 
    {
        spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].state = FINISHED;
        spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].result = rslt;
        spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].tries = tries;
        spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].duration = 
        SpmiOs_GetTimeTick() - spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].startTime;
        
        if(data != NULL) {
            spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].data0 = *data;
        }

        if(rslt < SPMI_RESULT_MAX) {
            spmiDrvDebug.debug.rsltCnt[rslt]++;
        }
    }
    else {
        spmiDrvDebug.debug.syncFlag = TRUE;
    }
    
    if(rslt != SPMI_SUCCESS)
    {
        uint8 bid;
        spmiDecodeVSid( vSlaveId, &bid, NULL );
                
        spmiDrvDebug.debug.errorIdx = (spmiDrvDebug.debug.errorIdx + 1) % NUM_DEBUG_FAILURES;
        spmiDrvDebug.debug.errorTrans[spmiDrvDebug.debug.errorIdx].info = spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx];
        
        PmicArb_GetHwStatus( SPMI_PDEV(spmiDrvDebug.pSpmiInfo, bid), &spmiDrvDebug.debug.errorTrans[spmiDrvDebug.debug.errorIdx].hwStatus );
        SPMI_LOG_WARNING( "cmd: %d / vsid: 0x%02x / addr: 0x%04x / len: %d / rslt: %d / tries: %d", 
                          cmd, vSlaveId, address, len, rslt,
                          spmiDrvDebug.debug.busTrans[spmiDrvDebug.debug.busIdx].tries);
    }
}

static Spmi_Result debugExecute_DebugIf(PmicArbCmd cmd,
                                        Spmi_AccessPriority priority,
                                        uint8 busId,
                                        uint8 vSlaveId,
                                        uint16 address,
                                        uint8* data,
                                        uint32 len,
                                        uint32* bytesTransacted)
{
    Spmi_Result rslt = SPMI_SUCCESS;
    boolean retry;
    uint8 slaveId;
    uint8 tries = 0;
    SpmiDevInfo *pDev;
    
    INIT_CHECK();
    
    slaveId = vSlaveId;
    if(busId >= SPMI_NUM_BUSES_SUPPORTED(spmiDrvDebug.pSpmiInfo)) {
       return SPMI_FAILURE_INVALID_BUS_ID;
    }
    debugTransStart( cmd, vSlaveId, address, len );

    pDev = SPMI_PDEV(spmiDrvDebug.pSpmiInfo,busId);
    npa_issue_scalar_request(spmiDrvDebug.hQDSSClkVote, CLOCK_QDSS_LEVEL_DEBUG);
    do 
    {
        tries++;
        retry = FALSE;
        rslt = PmicArb_ExecuteCommandDebug ( pDev->baseAddrsDebugIf, cmd, priority,
                                             slaveId, address,
                                             data, len, bytesTransacted );     

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

    debugTransEnd( cmd, vSlaveId, address, len, data, tries, rslt );
    
    // Fail-fast by catching some irrecoverable errors
    if(rslt == SPMI_FAILURE_TRANSACTION_TIMEOUT) {
        SPMI_LOG_FATAL( "Timeout while executing SPMI transaction" );
    }
    else if(rslt == SPMI_FAILURE_BUS_BUSY) {
        SPMI_LOG_FATAL( "SPMI bus busy" );
    }
    npa_complete_request(spmiDrvDebug.hQDSSClkVote);
    
    return rslt;
}

//******************************************************************************
// Public API Functions
//******************************************************************************

Spmi_Result SpmiBusDebug_Init()
{
    Spmi_Result rslt;
    EFI_STATUS Status;
    SpmiDevInfo *pDev;
    uint32 *debug_fuse_if;
    
    if(spmiDrvDebug.initialized) {
        return SPMI_SUCCESS;
    }
    
    SPMI_LOG_INIT();

    if((rslt = SpmiOs_Init(&spmiDrvDebug.pSpmiInfo)) != SPMI_SUCCESS) {
        return rslt;
    }

    pDev = SPMI_PDEV(spmiDrvDebug.pSpmiInfo, 0);
    if (HWIOProtocol == NULL)
    {
        Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&HWIOProtocol);
        if ((EFI_SUCCESS != Status) || (HWIOProtocol == NULL))
        {
            return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
        }
    }

    Status = HWIOProtocol->MapRegionByAddress(HWIOProtocol, pDev->baseAddrsDebugIf, &pDev->baseAddrsDebugIf);
    if (EFI_SUCCESS != Status)
    {
        DEBUG((EFI_D_ERROR, "ERROR: Fail to map SPMI debug register interface \n\r"));
        return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
    }
    
    Status = HWIOProtocol->MapRegionByAddress(HWIOProtocol, 
                                              (UINT8 *)((uintnt)spmiDbgFuse.regAddrsDebugFuse & 0xfffff000), 
                                              (UINT8 **)&debug_fuse_if);
    if (EFI_SUCCESS != Status)
    {
        // Mark the debug fuse value to not supported if register mapping failed
        DEBUG((EFI_D_ERROR, "ERROR: Fail to map debug fuse registers \n\r"));
        spmiDbgFuse.DebugFuseValueCurrent = ~spmiDbgFuse.DebugFuseValueEn;
    }
    else
    {
       spmiDbgFuse.DebugFuseValueCurrent = *spmiDbgFuse.regAddrsDebugFuse;
       //DEBUG((EFI_D_ERROR, "PmicDxe: fuse register valuse 0x%x \n\r", spmiDbgFuse.DebugFuseValueCurrent));
    }

    spmiDrvDebug.pSpmiInfo->hasInterruptSupport = FALSE;
    
    InitRecursiveLock ("SpmiBus", &pSpmiBusLock);

    // Initialize NPA client handle to /clk/qdss node.
    spmiDrvDebug.hQDSSClkVote = npa_create_sync_client("/clk/qdss",
                                                       PMIC_ARB_SPMI_DBG_QDSS_CLK_CLIENT_NAME,
                                                       NPA_CLIENT_REQUIRED);

    if(!spmiDrvDebug.hQDSSClkVote)
    {
        DEBUG((EFI_D_ERROR, "ERROR: Fail to init client handle to QDSS clock node\n\r"));
        return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
    }

    spmiDrvDebug.initialized = TRUE;

    return SPMI_SUCCESS;
}

Spmi_Result SpmiBusDebug_DeInit()
{
    spmiDrvDebug.initialized = FALSE;
    return SPMI_SUCCESS;
}

Spmi_Result SpmiBus_ReadLongDebug(uint32 busId,
                                  uint32 vSlaveId,
                                  Spmi_AccessPriority priority,
                                  uint32 address,
                                  uint8* data,
                                  uint32 len,
                                  uint32* bytesRead)
{
  Spmi_Result rslt = SPMI_SUCCESS;

  AcquireLock(pSpmiBusLock);
  rslt = debugExecute_DebugIf( PMIC_ARB_CMD_EXTENDED_REG_READ_LONG, priority, busId, vSlaveId, address, data, len, bytesRead );
  ReleaseLock(pSpmiBusLock);

  return rslt;
}

Spmi_Result SpmiBus_WriteLongDebug(uint32 busId,
                                   uint32 vSlaveId,
                                   Spmi_AccessPriority priority,
                                   uint32 address,
                                   uint8* data,
                                   uint32 len)
{
  Spmi_Result rslt = SPMI_SUCCESS;
  INIT_CHECK();

  AcquireLock(pSpmiBusLock);
  rslt = debugExecute_DebugIf( PMIC_ARB_CMD_EXTENDED_REG_WRITE_LONG, priority, busId, vSlaveId, address, data, len, NULL);
  ReleaseLock(pSpmiBusLock);

  return rslt;
}

Spmi_Result SpmiBus_ReadModifyWriteLongByteDebug(uint32 busId,
                                                 uint32 vSlaveId,
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
    if((rslt = SpmiBus_ReadLongDebug( busId, vSlaveId, priority, address, &readData, 1, NULL )) != SPMI_SUCCESS) {
        ReleaseLock(pSpmiBusLock);
        return rslt;
    }

    readData &= ~mask;
    readData |= data & mask;

    if((rslt = SpmiBus_WriteLongDebug( busId, vSlaveId, priority, address, &readData, 1 )) != SPMI_SUCCESS) {
        ReleaseLock(pSpmiBusLock);
        return rslt;
    }

    *byteWritten = readData;

    ReleaseLock(pSpmiBusLock);

    return SPMI_SUCCESS;
}

Spmi_Result SpmiBus_VerifyDebugMode()
{
   // Check if fuse is correct
   if ((spmiDbgFuse.DebugFuseValueCurrent & spmiDbgFuse.DebugFuseMask) == spmiDbgFuse.DebugFuseValueEn) {
      return SPMI_SUCCESS;
   }
   else {
      return SPMI_FAILURE_FUNCTIONALITY_NOT_SUPPORTED;
   }
}


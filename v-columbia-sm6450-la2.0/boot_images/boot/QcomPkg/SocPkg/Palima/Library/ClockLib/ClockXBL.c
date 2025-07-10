/** @file ClockXBL.c

  This file implements specialized image specific functions such
  as init image, enable DCVS, etc. In case of UEFI, we have few
  place holders for now.

  Copyright (c) 2021, Qualcomm Technologies, Inc.
                   All rights reserved.
                 QUALCOMM Proprietary/GTDR

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 05/30/14   sj      Fixed 64 bit compilation errors
 05/08/14   sr      Ported to 8994.
 08/09/12   sr      Ported to 8974.
 12/23/10   vs      Created.

=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockApps.h"
#include <Library/KernelLib.h>

/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Externals
==========================================================================*/

/*=========================================================================
      Prototypes
==========================================================================*/

/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * UEFI Clock Driver local context.
 */
typedef struct
{
  boolean        bLowPowerMode;
  uint32         nSilverPerfLevel;
} ClockLocalCtxtType;

/*=========================================================================
      Data
==========================================================================*/

ClockLocalCtxtType  ClockLocalCtxt;

#define   CLOCK_CLUSTER_LOW_PERF_LEVEL            0 // 300Mhz


/* =========================================================================
**  Function : Clock_EnterLowPowerMode
** =========================================================================*/
/*
  See DDIClock.h
*/

ClockResult Clock_EnterLowPowerMode
(
  ClockDrvCtxt *pDrvCtxt
)
{
  ClockResult         eResult;
  uint32              perfLevel, pnFrequencyHz;

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Do not allow nested entries of the Low Power Mode.                    */
  /*-----------------------------------------------------------------------*/

  if (ClockLocalCtxt.bLowPowerMode == TRUE)
  {
    DALCLOCK_FREE(pDrvCtxt);
    return CLOCK_ERROR;
  }


  /*-----------------------------------------------------------------------*/
  /* Reduce each core's frequency to the lowest possible.                  */
  /*-----------------------------------------------------------------------*/
  // Set Silver cluster CPU0 perf level
  ClockLocalCtxt.nSilverPerfLevel = 0;
  eResult = Clock_GetCpuPerfLevel( CLOCK_APPS_CPU_C0, &perfLevel);
  if (eResult == CLOCK_SUCCESS)
  {
    ClockLocalCtxt.nSilverPerfLevel = perfLevel;
    // Set Silver cluster 0  to lowest perf level (300Mhz)
    eResult = Clock_SetCpuPerfLevel(CLOCK_APPS_CPU_C0, CLOCK_CLUSTER_LOW_PERF_LEVEL, &pnFrequencyHz);
  }
  else
  {
    DEBUG ((EFI_D_ERROR, "Clock_SetCpuPerfLevel CLOCK_APPS_CPU_C0 : Fail\n"));
  }

  ClockLocalCtxt.bLowPowerMode = TRUE;

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_EnterLowPowerMode */


/* =========================================================================
**  Function : Clock_ExitLowPowerMode
** =========================================================================*/
/*
  See DDIClock.h
*/

ClockResult Clock_ExitLowPowerMode
(
  ClockDrvCtxt *pDrvCtxt
)
{
  ClockResult  eResult = CLOCK_SUCCESS;
  uint32       pnFrequencyHz;

  DALCLOCK_LOCK(pDrvCtxt);

  /*-----------------------------------------------------------------------*/
  /* Make sure the Low Power Mode is active before exiting it.             */
  /*-----------------------------------------------------------------------*/

  if (ClockLocalCtxt.bLowPowerMode == FALSE)
  {
    DALCLOCK_FREE(pDrvCtxt);
    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* Restore frequencies for CPU clusters to the nominal level.            */
  /*-----------------------------------------------------------------------*/
  /* Silver Cluster */
  eResult = Clock_SetCpuPerfLevel(CLOCK_APPS_CPU_C0, ClockLocalCtxt.nSilverPerfLevel, &pnFrequencyHz); //CLOCK_SILVER_NOMINAL_PERF_LEVEL
  if (eResult != CLOCK_SUCCESS)
  {
    DEBUG ((EFI_D_ERROR, "Clock_ExitLowPowerMode: Set Silver Perf level Fail\n"));
  }

  ClockLocalCtxt.bLowPowerMode = FALSE;

  DALCLOCK_FREE(pDrvCtxt);

  ClockIdType nSourceId;
  ClockSourceNodeType *pSource = NULL;
  ClockNameListType   *pSourceName = NULL;
  ClockNameListType    SourcesToDeInitialize[] = {
    { "disp_cc_pll0" },
    { "disp_cc_pll1" },
    { NULL },
  };
  

  for (pSourceName = SourcesToDeInitialize; pSourceName->szName != NULL; pSourceName++)
  {
    Clock_GetSourceId(pDrvCtxt->hClient, pSourceName->szName, &nSourceId);
    pSource = Clock_GetSourceNode(nSourceId);
    if ((pSource != NULL) && CLOCK_REF_COUNT_TOTAL(pSource) <= 0)
    {
      pSource->VRegRequest.eVRegLevel = RAIL_VOLTAGE_LEVEL_OFF;
      pSource->VRegRequest.bSuppressible = FALSE;
      pSource->pActiveFreqConfig = NULL;
      pSource->NPAHandle = NULL;
      pSource->NPAHandleSuppressible = NULL;
      pSource->nCalibration = 0;
      CLOCK_FLAG_CLEAR(pSource, INITIALIZED);
    }
  }

  return eResult;

} /* END Clock_ExitLowPowerMode */

/**
  LPM feature - Clock_LowPowerModeHandler

  @param[IN] CodeType        :EFI_PROGRESS_CODE
  @param[IN] Value           :PcdLpm refer QcomPkg.dec for the value details
  @param[IN] Instance        : 0
  @param[IN] *CallerId       : Caller Id who initiated this CB
  @param[IN] *Data OPTIONAL  : Extended data refer LPM_EVENT_EXT_DATA in lpm.h

  @return
  EFI_SUCCESS                : CB handled
  EFI_UNSUPPORTED            : CB not intended for this module
**/

STATIC void Clock_LowPowerModeHandler(enum PwrTxnType mode, ClockDrvCtxt *pDrvCtxt)
{
  switch(mode)
  {
    case DevicePwrOFF :
      Clock_EnterLowPowerMode(pDrvCtxt);
      break;
    case DevicePwrON :
      Clock_ExitLowPowerMode(pDrvCtxt);
      break;
    default :
      break;
  }
}


/**
  Register/Unregister LPM support to get LPM entry/exit status in CB

  @param[IN] bIsRegisterLpm  : TRUE - Register LPM handler
                               FALSE - UnRegister LPM handler
  @return
  EFI_SUCCESS                : CB registered .
  EFI_DEVICE_ERROR           : device reported an error.
  EFI_UNSUPPORTED            : not supported by this device.
  EFI_INVALID_PARAMETER      : Parameter passed is incorrect.
**/

ClockResult
Clock_RegisterLPMCallBacks (BOOLEAN bIsRegisterLpm)
{
  EFI_STATUS    Status = EFI_SUCCESS;
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxt();

  if(bIsRegisterLpm)
  {
    Status = RegisterDevicePowerTransitionCallback ((PwrTxnNotifyFn)Clock_LowPowerModeHandler, pDrvCtxt);
  }
  else
  {
    Status = UnRegisterDevicePowerTransitionCallback ((PwrTxnNotifyFn)Clock_LowPowerModeHandler);
  }

  return (Status == EFI_SUCCESS)? CLOCK_SUCCESS: CLOCK_ERROR;
}


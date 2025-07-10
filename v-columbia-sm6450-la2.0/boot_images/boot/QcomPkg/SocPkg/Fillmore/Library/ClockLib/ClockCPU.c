/*
===========================================================================
*/
/**
  @file ClockCPU.c

  This file contains the clock device driver CPU specific code.
*/
/*
  ====================================================================

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/ClockLib/ClockCPU.c#5 $
  $DateTime: 2021/12/06 07:29:00 $
  $Author: pwbldsvc $
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "../HALclkLib/HALclkHWIO.h"
#include "ClockApps.h"
#include "Drivers/ClockDxe/ClockDriver.h"
#include "Drivers/ClockDxe/ClockDriverImage.h"
#include "QdssSWEvent.h"
#include "tracer_event_ids.h"
/*=========================================================================
      Function Prototypes
==========================================================================*/

/*=========================================================================
      Data Declarations
==========================================================================*/

#define MIN_PERF_LEVEL 0
#define MIN_PERF_LEVEL_FREQUENCY 300000000


/*=========================================================================
  Extern
==========================================================================*/
volatile uint32_t Clock_CpuStub = FALSE;


/*=========================================================================
      Functions
==========================================================================*/


/* =========================================================================
**  Function : Clock_InitDCVS
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_InitDCVS
(
  void
)
{
  /*-----------------------------------------------------------------------*/
  /* Make sure DCVS is enabled.                                            */
  /*-----------------------------------------------------------------------*/
  ClockDrvCtxt      *pDrvCtxt = Clock_GetDrvCtxt();
  pDrvCtxt->bDCVSEnabled = TRUE;

  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return CLOCK_SUCCESS;

} /* END Clock_InitDCVS */


/* =========================================================================
**  Function : Clock_SetCPUConfig
** =========================================================================*/

ClockResult Clock_SetCPUConfig
(
  ClockDrvCtxt                  *pDrvCtxt,
  ClockAppsCPUType               eCPU,
  uint32                         nPerfLevel
)
{
  ClockResult          eResult = CLOCK_SUCCESS;
  ClockAppsCtxtType *pAppsCtxt;

  DALCLOCK_LOCK(pDrvCtxt);
  pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;

  /*-----------------------------------------------------------------------*/
  /* Sanity checks.                                                        */
  /*-----------------------------------------------------------------------*/

  if (pAppsCtxt == NULL )
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockLog,
                      "Invalid configuration detected by Clock_SetCPUConfig.");
    DALCLOCK_FREE(pDrvCtxt);
    ERR_FATAL("Clock_SetCPUConfig", 0, 0, 0);
    return CLOCK_ERROR;
  }

  /*-----------------------------------------------------------------------*/
  /* If the desired frequency has already been set, just return.           */
  /*-----------------------------------------------------------------------*/

  if (pAppsCtxt->aCPU[eCPU].pBSPConfig->pConfig->aPerfConfig[nPerfLevel].nFreqHz == pAppsCtxt->aCPU[eCPU].pActiveConfig->nFreqHz)
  {
    DALCLOCK_FREE(pDrvCtxt);
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Use EPSS to set the desired perf level.                                */
  /*-----------------------------------------------------------------------*/

  if (!HAL_clk_EPSS_SET_DESIRED_PERF_LEVEL((HAL_clk_APCSCPUType)eCPU, nPerfLevel))
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockLog,
                      "Invalid EPSS configuration detected by Clock_SetCPUConfig.");
    DALCLOCK_FREE(pDrvCtxt);
    ERR_FATAL("Clock_SetCPUConfig", 0, 0, 0);
    return CLOCK_ERROR;
  }

  if (CLOCK_GLOBAL_FLAG_IS_SET(LOG_CLOCK_FREQ_CHANGE))
  {
    ULOG_RT_PRINTF_2 (
      pDrvCtxt->hClockLog,
      "Freq[/clk/cpu%d] = %lu (Hz)",
      eCPU,
      pAppsCtxt->aCPU[eCPU].pBSPConfig->pConfig->aPerfConfig[nPerfLevel].nFreqHz);
  }
  DALCLOCK_FREE(pDrvCtxt);

  /*
   * Log CPU frequency change event.
   */
  QDSS_SWEVENT(CLOCK_EVENT_CPU_FREQ, eCPU, pAppsCtxt->aCPU[eCPU].pBSPConfig->pConfig->aPerfConfig[nPerfLevel].nFreqHz);

  /*-----------------------------------------------------------------------*/
  /* Update state.                                                         */
  /*-----------------------------------------------------------------------*/
  DALCLOCK_LOCK(pDrvCtxt);

  pAppsCtxt->aCPU[eCPU].pActiveConfig = &pAppsCtxt->aCPU[eCPU].pBSPConfig->pConfig->aPerfConfig[nPerfLevel];
  pAppsCtxt->aCPU[eCPU].ActiveMuxConfig.nFreqHz = pAppsCtxt->aCPU[eCPU].pBSPConfig->pConfig->aPerfConfig[nPerfLevel].nFreqHz;

  DALCLOCK_FREE(pDrvCtxt);

  return eResult;

} /* END Clock_SetCPUConfig */


/* =========================================================================
**  Function : ClockApps_GetMaxPerfLevel
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult
ClockApps_GetMaxPerfLevel (
  uint32 nCPU,
  uint32 *pnPerfLevel
)
{
  ClockDrvCtxt              *pDrvCtxt = Clock_GetDrvCtxt();
  ClockAppsCtxtType         *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
  ClockAppsBSPCPUConfigType *pBSPConfig;

  if(Clock_CpuStub)
  {
    *pnPerfLevel = MIN_PERF_LEVEL;
    return CLOCK_SUCCESS;
  }
  else
  {
  if ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pBSPConfig = pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig;

  if (pBSPConfig == NULL)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  if (pnPerfLevel)
  {
    *pnPerfLevel = pBSPConfig->nMaxPerfLevel;
  }

  return CLOCK_SUCCESS;
}
}

/* =========================================================================
**  Function : ClockApps_GetMinPerfLevel
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult ClockApps_GetMinPerfLevel
(
  uint32 nCPU,
  uint32 *pnPerfLevel
)
{
  ClockDrvCtxt              *pDrvCtxt = Clock_GetDrvCtxt();
  ClockAppsCtxtType         *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
  ClockAppsBSPCPUConfigType *pBSPConfig;
  if(Clock_CpuStub)
  {
    *pnPerfLevel = MIN_PERF_LEVEL;
    return CLOCK_SUCCESS;
  }
  else
  {
  if ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pBSPConfig = pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig;

  if (pBSPConfig == NULL)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  if (pnPerfLevel)
  {
    *pnPerfLevel = pBSPConfig->nMinPerfLevel;
  }

  return CLOCK_SUCCESS;
}
}

/* =========================================================================
**  Function : ClockApps_GetCpuPerfLevelFrequency
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult
ClockApps_GetCpuPerfLevelFrequency (
  uint32 nCPU,
  uint32 nPerfLevel,
  uint32 *pnFrequencyHz,
  uint32 *pnRequiredVoltage
)
{
  ClockDrvCtxt              *pDrvCtxt = Clock_GetDrvCtxt();
  ClockAppsCtxtType         *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
  ClockAppsBSPCPUConfigType *pBSPConfig;

  if(Clock_CpuStub)
  {
    *pnFrequencyHz = MIN_PERF_LEVEL_FREQUENCY;
    return CLOCK_SUCCESS;
  }
  else
  {
  if ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pBSPConfig = pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig;

  if (pBSPConfig == NULL)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  if (nPerfLevel < pBSPConfig->nMinPerfLevel || nPerfLevel > pBSPConfig->nMaxPerfLevel)
  {
    return CLOCK_ERROR_OUT_OF_RANGE_PARAMETER;
  }

  if (pnFrequencyHz)
  {
    *pnFrequencyHz = Clock_MapPerfLevelToFrequency(pDrvCtxt, (ClockAppsCPUType)nCPU, nPerfLevel);
  }

  if (pnRequiredVoltage)
  {
    *pnRequiredVoltage = Clock_MapPerfLevelToVoltage(pDrvCtxt, (ClockAppsCPUType)nCPU, nPerfLevel);
  }

  return CLOCK_SUCCESS;
}
}

/* ===========================================================================
**  Function :  ClockApps_DetectCPUFrequency
**
** ======================================================================== */

ClockResult  ClockApps_DetectCPUFrequency
(
  uint32 nCPU,
  uint32 *nFreqHz
)
{
  uint32                       nVcIndex;
   ClockAppsCPUType             eCPU = (ClockAppsCPUType)nCPU;
   ClockDrvCtxt                 *pDrvCtxt = Clock_GetDrvCtxt();
   ClockAppsCtxtType            *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
   ClockAppsBSPCPUConfigType    *pBSPConfig;

  if(Clock_CpuStub)
  {
    *nFreqHz = MIN_PERF_LEVEL_FREQUENCY;
    return CLOCK_SUCCESS;
  }
  else
  {
    pBSPConfig = pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig;
    if(HAL_clk_EPSS_READ_VCINDEX((HAL_clk_APCSCPUType)nCPU, &nVcIndex))
    {
      pAppsCtxt->aCPU[eCPU].pActiveConfig = &pBSPConfig->aPerfConfig[nVcIndex];
      *nFreqHz = pBSPConfig->aPerfConfig[nVcIndex].nFreqHz;
      return CLOCK_SUCCESS;
    }
    return CLOCK_ERROR;
  }
}

/* =========================================================================
**  Function : ClockApps_GetCPUFrequencyLevels
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult
ClockApps_GetCPUFrequencyLevels (
  uint32 nCPU,
  uint32 *pnFrequencyLevels
)
{
  ClockResult                    eResult=CLOCK_SUCCESS;
  ClockDrvCtxt                 *pDrvCtxt = Clock_GetDrvCtxt();
  ClockAppsCtxtType            *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
  ClockAppsBSPCPUConfigType    *pBSPConfig;

  if(Clock_CpuStub)
  {
    *pnFrequencyLevels = MIN_PERF_LEVEL;
    return CLOCK_SUCCESS;
  }
  else
  {
    if ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL)
    {
      return CLOCK_ERROR_INVALID_PARAMETER;
    }

    pBSPConfig = pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig;

    if (pBSPConfig == NULL)
    {
      return CLOCK_ERROR_INTERNAL;
    }

    *pnFrequencyLevels = pBSPConfig->nMaxPerfLevel +1;

    return eResult;
  }
}

/* =========================================================================
**  Function : ClockApps_GetCPUFrequencyPlan
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult
ClockApps_GetCPUFrequencyPlan (
  uint32 nCPU,
  ClockFreqPlanType *pCPUFreqPlan,
  uint32 nSize
)
{
  ClockResult                 eResult=CLOCK_SUCCESS;
  ClockDrvCtxt              *pDrvCtxt = Clock_GetDrvCtxt();
  uint32                    nRowNumber = 0;
  ClockAppsCtxtType         *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
  ClockAppsBSPCPUConfigType *pBSPConfig;

  if(Clock_CpuStub)
  {
    return CLOCK_SUCCESS;
  }
  else
  {
    if ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL)
    {
      return CLOCK_ERROR_INVALID_PARAMETER;
    }

    pBSPConfig = pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig;

    if (pBSPConfig == NULL)
    {
      return CLOCK_ERROR_INTERNAL;
    }

    //If the size of the table to be dumped is less than that of frequency plan
    if(nSize < (pBSPConfig->nMaxPerfLevel+1))
    {
      return CLOCK_ERROR_INVALID_PARAMETER;
    }

    for (nRowNumber = 0; nRowNumber <=pBSPConfig->nMaxPerfLevel; nRowNumber++)
    {
      (pCPUFreqPlan + nRowNumber)->nFreqHz = pBSPConfig->aPerfConfig[nRowNumber].nFreqHz;
      (pCPUFreqPlan + nRowNumber)->eVRegLevel = pBSPConfig->aPerfConfig[nRowNumber].nVoltageUV;
    }
    return eResult;
  }
}


/* =========================================================================
**  Function : ClockApps_SetCPUFrequency
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult
ClockApps_SetCPUFrequency (
  uint32 nCPU,
  uint32 nFrequencyHz,
  uint32 *pnResultFreqHz
)
{
  ClockResult                  eResult=CLOCK_SUCCESS;
  ClockDrvCtxt               *pDrvCtxt = Clock_GetDrvCtxt();
  ClockAppsCtxtType          *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
  uint32                     nRowNumber;
  ClockAppsBSPCPUConfigType  *pBSPConfig;

  if(Clock_CpuStub)
  {
    return CLOCK_SUCCESS;
  }
  else
  {
    if ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL)
    {
      return CLOCK_ERROR_INVALID_PARAMETER;
    }

    pBSPConfig = pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig;

    if (pBSPConfig == NULL)
    {
      return CLOCK_ERROR_INTERNAL;
    }

    for (nRowNumber = 0; nRowNumber <= pBSPConfig->nMaxPerfLevel; nRowNumber++)
    {
      if(nFrequencyHz <= pBSPConfig->aPerfConfig[nRowNumber].nFreqHz)
      {
          break;
      }
    }

    if(nRowNumber > pBSPConfig->nMaxPerfLevel)
    {
      nRowNumber = pBSPConfig->nMaxPerfLevel;
    }

    /* Check the state of DCVS and return immediately if DCVS is disabled. */
    if (pDrvCtxt->bDCVSEnabled == TRUE || CLOCK_GLOBAL_FLAG_IS_SET(CPU_TEST_IN_PROGRESS))
    {
      eResult = Clock_SetCPUConfig(
                pDrvCtxt,
                (ClockAppsCPUType)nCPU,
                nRowNumber);

      if (eResult == CLOCK_SUCCESS && pnResultFreqHz != NULL)
      {
         *pnResultFreqHz = pAppsCtxt->aCPU[nCPU].pActiveConfig->nFreqHz;
      }
    }

    return eResult;
  }
}
/* =========================================================================
**  Function : ClockApps_GetCPUFrequency
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult
ClockApps_GetCPUFrequency (
  uint32 nCPU,
  uint32 *pnFrequencyHz
)
{
  ClockDrvCtxt                 *pDrvCtxt = Clock_GetDrvCtxt();
  ClockAppsCtxtType            *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
  uint32                       nActivePerfLevel;

  if ((pnFrequencyHz == NULL) || ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL))
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if (pAppsCtxt == NULL)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  if(Clock_CpuStub)
  {
    *pnFrequencyHz = MIN_PERF_LEVEL_FREQUENCY;
    return CLOCK_SUCCESS;
  }
  else
  {
    if (HAL_clk_EPSS_READ_VCINDEX((HAL_clk_APCSCPUType)nCPU, &nActivePerfLevel))
    {
      *pnFrequencyHz =  pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig->aPerfConfig[nActivePerfLevel].nFreqHz;
       return CLOCK_SUCCESS;
    }
    else
    {
      *pnFrequencyHz = 0;
      return CLOCK_ERROR;
    }
  }
}

/* =========================================================================
**  Function : ClockApps_SetCpuPerfLevel
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult
ClockApps_SetCpuPerfLevel (
  uint32 nCPU,
  uint32 nPerfLevel,
  uint32 *pnFrequencyHz
)
{
  ClockResult                  eResult=CLOCK_SUCCESS;
  ClockDrvCtxt              *pDrvCtxt = Clock_GetDrvCtxt();
  ClockAppsCtxtType         *pAppsCtxt = (ClockAppsCtxtType *)pDrvCtxt->pImageCtxt;
  ClockAppsBSPCPUConfigType *pBSPConfig;

  if(Clock_CpuStub)
  {
    return CLOCK_SUCCESS;
  }
  else
  {
  if (pnFrequencyHz == NULL)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  *pnFrequencyHz = 0;

  if ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  pBSPConfig = pAppsCtxt->aCPU[nCPU].pBSPConfig->pConfig;

  if (pBSPConfig == NULL)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  /* Clamp the given perf level within the valid range. */
    if (nPerfLevel < pBSPConfig->nMinPerfLevel)
    {
      nPerfLevel = pBSPConfig->nMinPerfLevel;
    }
    if (nPerfLevel > pBSPConfig->nMaxPerfLevel)
    {
      nPerfLevel = pBSPConfig->nMaxPerfLevel;
    }

  /* Check the state of DCVS and return immediately if DCVS is disabled. */
  if (pDrvCtxt->bDCVSEnabled == TRUE || CLOCK_GLOBAL_FLAG_IS_SET(CPU_TEST_IN_PROGRESS))
  {
    eResult = Clock_SetCPUConfig(
              pDrvCtxt,
              (ClockAppsCPUType)nCPU,
              nPerfLevel);

    if (eResult == CLOCK_SUCCESS)
    {
      *pnFrequencyHz = pBSPConfig->aPerfConfig[nPerfLevel].nFreqHz;
    }
  }

  return eResult;
}
}

/* =========================================================================
**  Function : ClockApps_GetCpuPerfLevel
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult
ClockApps_GetCpuPerfLevel (
  uint32 nCPU,
  uint32 *pnPerfLevel
)
{
  if ((pnPerfLevel == NULL) || ((ClockAppsCPUType)nCPU >= CLOCK_APPS_CPU_TOTAL))
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  if(Clock_CpuStub)
  {
    *pnPerfLevel = MIN_PERF_LEVEL;
    return CLOCK_SUCCESS;
  }
  else
  {
    if (HAL_clk_EPSS_READ_VCINDEX((HAL_clk_APCSCPUType)nCPU, pnPerfLevel))
    {
      return CLOCK_SUCCESS;
    }
    else
    {
      *pnPerfLevel = 0;
      return CLOCK_ERROR;
    }
  }
}



ClockResult Clock_ProcessorRestore
(
  ClockHandle        hClient,
  ClockSleepModeType eMode,
  uint32_t           nFlags
)
{
  ClockResult result = CLOCK_SUCCESS;

  /* No processor restore functionality yet */
  return result;
}



ClockResult Clock_ProcessorSleep
(
  ClockHandle        hClient,
  ClockSleepModeType eMode,
  uint32_t           nFlags
)
{
  ClockResult result = CLOCK_SUCCESS;

  /* No processor sleep functionality yet */
  return result;
}

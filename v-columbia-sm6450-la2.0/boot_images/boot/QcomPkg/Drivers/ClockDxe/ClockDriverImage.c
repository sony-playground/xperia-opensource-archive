/*
===========================================================================
*/
/**
  @file ClockDriverImage.c

  Interface implementation file for the clock device driver.
*/
/*
  ====================================================================

  Copyright (c) 2020-2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.0/QcomPkg/Drivers/ClockDxe/ClockDriverImage.c#2 $
  $DateTime: 2021/09/10 23:54:52 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriverImage.h"



/*=========================================================================
      Externs
==========================================================================*/

extern uint32_t Clock_GetDebugMuxInputDiv
(
  ClockDebugMuxType *pDebugMux,
  uint32_t           nMuxSel
);


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_GetMaxPerfLevel
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult
Clock_GetMaxPerfLevel
(
  uint32_t     nCPU,
  uint32_t    *pnPerfLevel
)
{ 
  return ClockApps_GetMaxPerfLevel ( nCPU, pnPerfLevel);
}


/* =========================================================================
**  Function : Clock_GetMinPerfLevel
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_GetMinPerfLevel
(
  uint32_t  nCPU,
  uint32_t  *pnPerfLevel
)
{ 
  return ClockApps_GetMinPerfLevel( nCPU, pnPerfLevel);
}


/* =========================================================================
**  Function : Clock_GetCpuPerfLevelFrequency
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult
Clock_GetCpuPerfLevelFrequency (
  uint32_t  nCPU,
  uint32_t  nPerfLevel,
  uint32_t  *pnFrequencyHz,
  uint32_t  *pnRequiredVoltage
)
{
  return  ClockApps_GetCpuPerfLevelFrequency(nCPU, nPerfLevel, pnFrequencyHz, pnRequiredVoltage);
}


/* ===========================================================================
**  Function :  Clock_DetectCPUFrequency
**    
** ======================================================================== */

ClockResult  Clock_DetectCPUFrequency
(
  uint32_t  nCPU,
  uint32_t  *nFreqHz
)
{
 return ClockApps_DetectCPUFrequency(nCPU, nFreqHz);
}

/* =========================================================================
**  Function : Clock_GetCPUFrequencyLevels
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult
Clock_GetCPUFrequencyLevels (
  uint32_t  nCPU,
  uint32_t  *pnFrequencyLevels 
)
{
   return ClockApps_GetCPUFrequencyLevels(nCPU, pnFrequencyLevels);
}
 
/* =========================================================================
**  Function : Clock_GetCPUFrequencyPlan
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult
Clock_GetCPUFrequencyPlan (
  uint32_t  nCPU,
  ClockFreqPlanType *pCPUFreqPlan,
  uint32_t  nSize
)
{
 return ClockApps_GetCPUFrequencyPlan(nCPU, pCPUFreqPlan, nSize);
} 
 

/* =========================================================================
**  Function : Clock_SetCPUFrequency
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult
Clock_SetCPUFrequency(
  uint32_t  nCPU,
  uint32_t  nFrequencyHz,
  uint32_t  *pnResultFreqHz
)
{
  return ClockApps_SetCPUFrequency(nCPU, nFrequencyHz, pnResultFreqHz);
}

/* =========================================================================
**  Function : Clock_GetCPUFrequency
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult
Clock_GetCPUFrequency(
  uint32_t  nCPU,
  uint32_t  *pnFrequencyHz
)
{
    return ClockApps_GetCPUFrequency(nCPU, pnFrequencyHz);
}

/* =========================================================================
**  Function : Clock_SetCpuPerfLevel
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult
Clock_SetCpuPerfLevel(
  uint32_t  nCPU,
  uint32_t  nPerfLevel,
  uint32_t  *pnFrequencyHz
)
{
   return ClockApps_SetCpuPerfLevel(nCPU, nPerfLevel, pnFrequencyHz);
}

/* =========================================================================
**  Function : Clock_GetCpuPerfLevel
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult
Clock_GetCpuPerfLevel(
  uint32_t  nCPU,
  uint32_t  *pnPerfLevel
)
{
    return ClockApps_GetCpuPerfLevel(nCPU, pnPerfLevel);
}


// Functions from ClockDriver.c

/* =========================================================================
**  Function : Clock_FrameworkInit
** =========================================================================*/
/*
  See ClockDriver.h
*/
ClockResult Clock_FrameworkInit (void)
{
    return CLOCK_SUCCESS;
}


/* =========================================================================
**  Function : Clock_EnableClockPostProcess
** =========================================================================*/
/*
  See ClockDriver.h
*/

void Clock_EnableClockPostProcess
(
  ClockClientRefCountType *pClientRefCount,
  ClockNodeType           *pClock
)
{
#if 0
  /*
   * Validate arguments.
   */
  if (!pClientRefCount || !pClock || !pClock->pDomain)
  {
    return;
  }

  /*
   * Short-circuit if domain is suppressible.
   */
  if (CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE))
  {
    return;
  }

  /*
   * Short-circuit if not the first required request from this client.
   */
  if (CLOCK_REF_COUNT_REQ(pClientRefCount) != 1)
  {
    return;
  }

  /*
   * Update metrics.
   */
  Clock_EnableUpdateMetrics((ClockClientCtxt *)pClientRefCount->hClient,
    pClock->pDomain->pSource);
#endif

} /* END Clock_EnableClockPostProcess */


/* =========================================================================
**  Function : Clock_DisableClockPostProcess
** =========================================================================*/
/*
  See ClockDriver.h
*/

void Clock_DisableClockPostProcess
(
  ClockClientRefCountType *pClientRefCount,
  ClockNodeType           *pClock
)
{
#if 0
  /*
   * Validate arguments.
   */
  if (!pClientRefCount || !pClock || !pClock->pDomain)
  {
    return;
  }

  /*
   * Short-circuit if domain is suppressible.
   */
  if (CLOCK_FLAG_IS_SET(pClock->pDomain, SUPPRESSIBLE))
  {
    return;
  }

  /*
   * Short-circuit if not the last required request from this client.
   */
  if (CLOCK_REF_COUNT_REQ(pClientRefCount) != 0)
  {
    return;
  }

  /*
   * Update metrics.
   */
  Clock_DisableUpdateMetrics((ClockClientCtxt *)pClientRefCount->hClient,
    pClock->pDomain->pSource);
#endif

} /* END Clock_DisableClockPostProcess */




/*=========================================================================
**  Function : Clock_CreatePDEventProcess
** =========================================================================*/
/*
  See ClockDriver.h
*/
void Clock_CreatePDEventProcess
(
  ClockPDCtxt *pPD
)
{
  return ;
}


/*=========================================================================
**  Function : Clock_DestroyPDEventProcess
** =========================================================================*/
/*
  See ClockDriver.h
*/
void Clock_DestroyPDEventProcess
(
  ClockPDCtxt *pPD
)
{
  return ;
}

/* =========================================================================
**  Function : Clock_GetMaxDomainCorner
** =========================================================================*/
/**
  See ClockDriverImage.h
*/

ClockResult Clock_GetMaxDomainCorner
(
  ClockDomainNodeType *pDomain,
  rail_voltage_level  *peVRegLevel
)
{
  const ClockFMaxType *pFMax;

  if (!pDomain || !pDomain->aFMax || !peVRegLevel)
  {
    return CLOCK_ERROR;
  }

  for (pFMax = pDomain->aFMax; pFMax->nMaxFreqHz; pFMax++)
  {
    if (Clock_IsBSPSupported(&pFMax->HWVersion))
    {
      *peVRegLevel = pFMax->eVRegLevel;
    }
  }

  return CLOCK_SUCCESS;

} /* END Clock_GetMaxDomainCorner */

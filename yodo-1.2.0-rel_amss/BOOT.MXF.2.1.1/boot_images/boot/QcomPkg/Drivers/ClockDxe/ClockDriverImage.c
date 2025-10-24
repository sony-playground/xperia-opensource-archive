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

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/ClockDxe/ClockDriverImage.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockApps.h"
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

ClockResult Clock_GetMaxPerfLevel
(
  uint32_t     nClusterIndex,
  uint32_t    *pnPerfLevel
)
{
  return ClockApps_Query(nClusterIndex, -1, CLOCKAPPS_REQUEST_DATA_MAX_PERF_LEVEL, pnPerfLevel);
}


/* =========================================================================
**  Function : Clock_GetMinPerfLevel
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_GetMinPerfLevel
(
  uint32_t   nClusterIndex,
  uint32_t  *pnPerfLevel
)
{ 
  return ClockApps_Query(nClusterIndex, -1, CLOCKAPPS_REQUEST_DATA_MIN_PERF_LEVEL, pnPerfLevel);
}


/* =========================================================================
**  Function : Clock_GetCpuPerfLevelFrequency
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_GetCpuPerfLevelFrequency (
  uint32_t   nClusterIndex,
  uint32_t   nPerfLevel,
  uint32_t  *pnFreqHz,
  uint32_t  *pnRequiredVoltage
)
{
  ClockResult eResult;
  eResult  = ClockApps_Query(nClusterIndex, nPerfLevel, CLOCKAPPS_REQUEST_DATA_FREQUENCY_HZ, pnFreqHz);
  eResult |= ClockApps_Query(nClusterIndex, nPerfLevel, CLOCKAPPS_REQUEST_DATA_VOLTAGE_UV, pnRequiredVoltage);
  return eResult;
}


/* =========================================================================
**  Function : Clock_GetCPUFrequencyLevels
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_GetCPUFrequencyLevels (
  uint32_t   nClusterIndex,
  uint32_t  *pnFrequencyLevels 
)
{
   return ClockApps_Query(nClusterIndex, -1, CLOCKAPPS_REQUEST_DATA_NUMBER_OF_PERF_LEVELS, pnFrequencyLevels);
}
 
/* =========================================================================
**  Function : Clock_GetCPUFrequencyPlan
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_GetCPUFrequencyPlan (
  uint32_t           nClusterIndex,
  ClockFreqPlanType *pCPUFreqPlan,
  uint32_t           nSize
)
{
  ClockResult eResult = CLOCK_ERROR;
  uint32_t    nPerfLevel=0, nTotalPerfLevels=0;
  eResult = ClockApps_Query(nClusterIndex, -1, CLOCKAPPS_REQUEST_DATA_NUMBER_OF_PERF_LEVELS, &nTotalPerfLevels);
  if (nSize > nTotalPerfLevels)
    nSize = nTotalPerfLevels;
  
  for (nPerfLevel = 0; nPerfLevel < nSize; nPerfLevel++)
  {
    eResult |= ClockApps_Query(nClusterIndex, nPerfLevel, CLOCKAPPS_REQUEST_DATA_FREQUENCY_HZ, &pCPUFreqPlan[nPerfLevel].nFreqHz);
    eResult |= ClockApps_Query(nClusterIndex, nPerfLevel, CLOCKAPPS_REQUEST_DATA_VOLTAGE_UV, &pCPUFreqPlan[nPerfLevel].eVRegLevel);
  }

  return eResult;
} /* END ClockApps_GetCPUFrequencyPlan */

/* =========================================================================
**  Function : Clock_SetCPUFrequency
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_SetCPUFrequency(
  uint32_t   nClusterIndex,
  uint32_t   nFrequencyHz,
  uint32_t  *pnResultFreqHz
)
{
  return ClockApps_SetCPUFrequency(nClusterIndex, nFrequencyHz, pnResultFreqHz);
}

/* =========================================================================
**  Function : Clock_GetCPUFrequency
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_GetCPUFrequency(
  uint32_t   nClusterIndex,
  uint32_t  *pnFrequencyHz
)
{
  return ClockApps_GetCPUFrequency(nClusterIndex, pnFrequencyHz);
}

/* =========================================================================
**  Function : Clock_SetCpuPerfLevel
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_SetCpuPerfLevel(
  uint32_t   nClusterIndex,
  uint32_t   nPerfLevel,
  uint32_t  *pnFrequencyHz
)
{
  return ClockApps_SetCPUPerfLevel(nClusterIndex, nPerfLevel, pnFrequencyHz);
}

/* =========================================================================
**  Function : Clock_GetCpuPerfLevel
** =========================================================================*/
/*
  See ClockDriverImage.h
*/

ClockResult Clock_GetCpuPerfLevel(
  uint32_t   nClusterIndex,
  uint32_t  *pnPerfLevel
)
{
  return ClockApps_GetCPUPerfLevel(nClusterIndex, pnPerfLevel);
}

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


/*=========================================================================
**  Function : Clock_FrameworkInit
** =========================================================================*/
/*
  See ClockDriver.h
*/
ClockResult Clock_FrameworkInit
(
  void
)
{
  return CLOCK_SUCCESS;
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

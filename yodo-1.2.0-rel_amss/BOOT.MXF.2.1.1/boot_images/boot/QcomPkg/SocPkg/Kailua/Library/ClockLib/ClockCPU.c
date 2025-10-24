/*
===========================================================================
*/
/**
  @file ClockCPU.c

  This file contains the clock device driver CPU specific code.
*/
/*
  ====================================================================

  Copyright (c) 2021, 2022 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/ClockLib/ClockCPU.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $
  ====================================================================
*/

/*=============================================================================
      Include Files
=============================================================================*/

#include "ClockApps.h"
#include "Drivers/ClockDxe/ClockDriver.h"
#include "./../HALclkLib/HALclkEPSS.h"

extern ClockAppsBSPType ClockAppsBSP;
extern ClockAppsCtxtType ClockAppsCtxt;

/*=============================================================================
      Functions
=============================================================================*/

/* ============================================================================
**  Function : Clock_InitCPUBSP
** ==========================================================================*/
ClockResult Clock_InitCPUBSP
(
  void
)
{
  ClockAppsClusterNodeType     *pCluster = NULL;
  HAL_clk_ClusterPerfLevelType  PerfLevelDetails = {0};
  uint32_t             nClusterOffset=0, nPerfLevel=0;
  uint32_t             nPrevLval=0, nPrevVoltage=0;

  for (nClusterOffset = 0; nClusterOffset < ClockAppsBSP.nNumClusters; nClusterOffset++)
  {
    pCluster = &ClockAppsBSP.aClusters[nClusterOffset];
    for (nPerfLevel = CLOCK_APSS_MIN_PERF_LEVEL; nPerfLevel < CLOCK_APSS_TOTAL_PERF_LEVELS; nPerfLevel++)
    {
      pCluster->HALCluster.pmControl->ReadPerfLevelConfig(&(pCluster->HALCluster), nPerfLevel, &PerfLevelDetails);
      if (PerfLevelDetails.nL == nPrevLval && PerfLevelDetails.nOpenLoopVoltage == nPrevVoltage)
        break;
      nPrevLval = PerfLevelDetails.nL;
      nPrevVoltage = PerfLevelDetails.nOpenLoopVoltage;

      /*
       * ClockSource 0 is GPLL and non-zero is APPS PLL.
       * Registers have voltage value in Milli Volts.
       */
      pCluster->aBSP[nPerfLevel].nFreqHz    = (PerfLevelDetails.nSource)? (PerfLevelDetails.nL * CLOCK_APPS_XO_FREQ): CLOCK_APSS_MIN_PERF_LEVEL_FREQ;
      pCluster->aBSP[nPerfLevel].nVoltageUV = MILLI_VOLT_TO_MICRO_VOLT(PerfLevelDetails.nOpenLoopVoltage);
    }
    pCluster->nMaxPerfLevel = nPerfLevel - 1;
  }
  return CLOCK_SUCCESS;
} /* END Clock_InitCPUBSP */


/* ============================================================================
**  Function : Clock_InitCPU
** ==========================================================================*/

ClockResult Clock_InitCPU
(
  void
)
{
  ClockResult                eResult = CLOCK_SUCCESS;

  /*-----------------------------------------------------------------------*/
  /* Initialize the Apps BSP data.                                         */
  /*-----------------------------------------------------------------------*/
  eResult = Clock_InitCPUBSP();
  if (eResult != CLOCK_SUCCESS){
    DEBUG((EFI_D_WARN, "Clock_InitCPUBSP failed."));
    return eResult;
  }

  return CLOCK_SUCCESS;
} /* END Clock_InitCPU */


/* ============================================================================
**  Function : ClockApps_Query
** ==========================================================================*/
ClockResult ClockApps_Query
(
  uint32_t                   nClusterIndex,
  uint32_t                   nInput,
  ClockApps_RequestDataType  eRequestType,
  uint32_t                  *pnResult
)
{
  ClockResult               eResult = CLOCK_SUCCESS;
  ClockAppsClusterNodeType *pCluster = NULL;
  
  if (!(nClusterIndex < ClockAppsBSP.nNumClusters) || !pnResult)
    return CLOCK_ERROR_INVALID_PARAMETER;

  pCluster = &(ClockAppsBSP.aClusters[nClusterIndex]);
  switch (eRequestType)
  {
    case CLOCKAPPS_REQUEST_DATA_NUMBER_OF_PERF_LEVELS:
      *pnResult = pCluster->nMaxPerfLevel;
      break;

    case CLOCKAPPS_REQUEST_DATA_FREQUENCY_HZ:
      if (nInput > pCluster->nMaxPerfLevel)
        eResult = CLOCK_ERROR_OUT_OF_RANGE_PARAMETER;
      else
        *pnResult = pCluster->aBSP[nInput].nFreqHz;
      break;

    case CLOCKAPPS_REQUEST_DATA_VOLTAGE_UV:
      if (nInput > pCluster->nMaxPerfLevel)
        eResult = CLOCK_ERROR_OUT_OF_RANGE_PARAMETER;
      else
        *pnResult = pCluster->aBSP[nInput].nVoltageUV;
      break;

    case CLOCKAPPS_REQUEST_DATA_MIN_PERF_LEVEL:
      *pnResult = pCluster->nMinPerfLevel;
      break;

    case CLOCKAPPS_REQUEST_DATA_MAX_PERF_LEVEL:
      *pnResult = pCluster->nMaxPerfLevel;
      break;

    case CLOCKAPPS_REQUEST_DATA_ACTIVE_PERF_LEVEL:
      *pnResult = pCluster->nActivePerfLevel;
      break;

    default:
      *pnResult = 0;
      eResult = CLOCK_ERROR_NOT_FOUND;
      break;
  }

  return eResult;
} /* END ClockApps_Query */


/* =========================================================================
**  Function : ClockApps_GetCPUFrequency
** =========================================================================*/

ClockResult ClockApps_GetCPUFrequency
(
  uint32_t    nClusterIndex,
  uint32_t   *pnFreqHz
)
{
  boolean                   bStatus = FALSE;
  uint32_t                  nDetectedVcIndex=0;
  ClockAppsClusterNodeType *pCluster = NULL;
  
  if (!(nClusterIndex < ClockAppsBSP.nNumClusters) || !pnFreqHz)
    return CLOCK_ERROR_INVALID_PARAMETER;

  pCluster = &(ClockAppsBSP.aClusters[nClusterIndex]);
  bStatus  = pCluster->HALCluster.pmControl->GetActivePerfLevel(&(pCluster->HALCluster), &nDetectedVcIndex);

  *pnFreqHz = pCluster->aBSP[nDetectedVcIndex].nFreqHz;
  return  (bStatus)? CLOCK_SUCCESS : CLOCK_ERROR;
} /* END ClockApps_GetCPUFrequency */


/* =========================================================================
**  Function : ClockApps_GetCPUPerfLevel
** =========================================================================*/

ClockResult ClockApps_GetCPUPerfLevel
(
  uint32_t    nClusterIndex,
  uint32_t   *pnPerfLevel
)
{
  boolean bStatus = FALSE;
  ClockAppsClusterNodeType *pCluster = NULL;
  
  if (!(nClusterIndex < ClockAppsBSP.nNumClusters) || !pnPerfLevel)
    return CLOCK_ERROR_INVALID_PARAMETER;

  pCluster = &(ClockAppsBSP.aClusters[nClusterIndex]);
  bStatus = pCluster->HALCluster.pmControl->GetActivePerfLevel(&(pCluster->HALCluster), pnPerfLevel);

  return  (bStatus)? CLOCK_SUCCESS : CLOCK_ERROR;
} /* END ClockApps_GetCPUPerfLevel */


/* ===========================================================================
**  Function :  ClockApps_DetectCPUPerfLevel
** ======================================================================== */

ClockResult ClockApps_DetectCPUPerfLevel
(
  uint32_t    nClusterIndex,
  uint32_t   *pnPerfLevel
)
{
  boolean bStatus = FALSE;
  ClockAppsClusterNodeType *pCluster = NULL;
  
  if (!(nClusterIndex < ClockAppsBSP.nNumClusters))
    return CLOCK_ERROR_INVALID_PARAMETER;

  pCluster = &(ClockAppsBSP.aClusters[nClusterIndex]);
  bStatus  = pCluster->HALCluster.pmControl->GetActivePerfLevel(&(pCluster->HALCluster), &(pCluster->nActivePerfLevel));

  if (pnPerfLevel)
    *pnPerfLevel = pCluster->nActivePerfLevel;
  return  (bStatus)? CLOCK_SUCCESS : CLOCK_ERROR;
} /* END ClockApps_DetectCPUPerfLevel */

/* ===========================================================================
**  Function :  ClockApps_DetectCPUFrequency
** ======================================================================== */

ClockResult ClockApps_DetectCPUFrequency
(
  uint32_t    nClusterIndex,
  uint32_t   *pnFreqHz
)
{
  boolean bStatus = FALSE;
  ClockAppsClusterNodeType *pCluster =  NULL;
  
  if (!(nClusterIndex < ClockAppsBSP.nNumClusters))
    return CLOCK_ERROR_INVALID_PARAMETER;

  pCluster = &(ClockAppsBSP.aClusters[nClusterIndex]);
  bStatus  = pCluster->HALCluster.pmControl->GetActivePerfLevel(&(pCluster->HALCluster), &(pCluster->nActivePerfLevel));

  if (pnFreqHz)
    *pnFreqHz = pCluster->aBSP[pCluster->nActivePerfLevel].nFreqHz;
  return  (bStatus)? CLOCK_SUCCESS : CLOCK_ERROR;
} /* END ClockApps_DetectCPUFrequency */


/* =========================================================================
**  Function : ClockApps_SetCPUPerfLevel
** =========================================================================*/

ClockResult ClockApps_SetCPUPerfLevel
(
  uint32_t    nClusterIndex,
  uint32_t    nPerfLevel,
  uint32_t   *pnResultPerfLevel
)
{
  boolean        bStatus = FALSE;
  uint32_t       nCoreOffset = 0;       /* NOTE: UEFI sets vote for only Core 0. */
  ClockAppsClusterNodeType *pCluster = NULL;
  
  if (!(nClusterIndex < ClockAppsBSP.nNumClusters))
    return CLOCK_ERROR_INVALID_PARAMETER;

  pCluster = &(ClockAppsBSP.aClusters[nClusterIndex]);
  if (nPerfLevel > pCluster->nMaxPerfLevel)
    return CLOCK_ERROR_OUT_OF_RANGE_PARAMETER;

  if ((nClusterIndex == (ClockAppsBSP.nNumClusters-1)) & HAL_clk_PerCoreL3VottingEnabled())    /* NOTE: L3 is assumed to be at last */
    bStatus   = pCluster->HALCluster.pmControl->SetL3PerfLevel(&(pCluster->HALCluster), nCoreOffset, nPerfLevel);
  else
    bStatus   = pCluster->HALCluster.pmControl->SetCorePerfLevel(&(pCluster->HALCluster), nCoreOffset, nPerfLevel);

  bStatus  |= pCluster->HALCluster.pmControl->GetActivePerfLevel(&(pCluster->HALCluster), &(pCluster->nActivePerfLevel));

  if (CLOCK_FLAG_IS_SET((&ClockAppsBSP), LOG_FREQ_CHANGE))
  {
    ULOG_RT_PRINTF_3 (ClockAppsCtxt.hClockAppsULog,
      "Freq[/clk/cpu%d] = Requested: %lu (Hz), Active: %lu (Hz)",
      nClusterIndex, nPerfLevel, pCluster->nActivePerfLevel);
  }

  if (pnResultPerfLevel)
    *pnResultPerfLevel = pCluster->nActivePerfLevel;
  return  (bStatus)? CLOCK_SUCCESS : CLOCK_ERROR;
} /* END ClockApps_SetCPUPerfLevel */


/* =========================================================================
**  Function : ClockApps_SetCPUFrequency
** =========================================================================*/

ClockResult ClockApps_SetCPUFrequency
(
  uint32_t    nClusterIndex,
  uint32_t    nFreqHz,
  uint32_t   *pnResultFreqHz
)
{
  ClockResult       eResult=CLOCK_SUCCESS;
  uint32_t          nPerfLevel = 0;
  ClockAppsClusterNodeType *pCluster = NULL;
  
  if (!(nClusterIndex < ClockAppsBSP.nNumClusters) || !nFreqHz)
    return CLOCK_ERROR_INVALID_PARAMETER;

  pCluster = &(ClockAppsBSP.aClusters[nClusterIndex]);

  for (nPerfLevel = pCluster->nMinPerfLevel; nPerfLevel <= pCluster->nMaxPerfLevel; nPerfLevel++)
  {
    if(nFreqHz <= pCluster->aBSP[nPerfLevel].nFreqHz)
      break;
  }
  eResult = ClockApps_SetCPUPerfLevel(nClusterIndex, nPerfLevel, NULL);

  if (pnResultFreqHz)
    *pnResultFreqHz = pCluster->aBSP[pCluster->nActivePerfLevel].nFreqHz;
  return eResult;
} /* END ClockApps_SetCPUFrequency */


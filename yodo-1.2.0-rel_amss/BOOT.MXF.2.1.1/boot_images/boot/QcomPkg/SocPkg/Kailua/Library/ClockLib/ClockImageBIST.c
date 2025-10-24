/*
===========================================================================
*/
/**
  @file ClockImageBIST.c

*/
/*
  ====================================================================

  Copyright (c) 2021 Qualcomm Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/ClockLib/ClockImageBIST.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockApps.h"
#include "Drivers/ClockDxe/ClockDriver.h"
#include <Library/KernelLib.h> // for ThreadSleep

/*=========================================================================
      Externals
==========================================================================*/
extern ClockAppsBSPType ClockAppsBSP;
extern ClockAppsCtxtType ClockAppsCtxt;


/*=========================================================================
      Macros
==========================================================================*/

#define CLOCK_BIST_ERROR_MARGIN_PPM 100     /* Expressed in PPM */
#define ABS_DIFF(v1, v2)  ((v1 >= v2) ? (v1 - v2) : (v2 - v1))


/*=========================================================================
      Data Declarations
==========================================================================*/

ClockNameListType apcs_clks[] =
{
  { "apss_cc_silver_pre_acd_debug_div_clk_src" },
  { "apss_cc_silver_post_acd_debug_div_clk_src" },
  { "apss_cc_gold_pre_acd_debug_div_clk_src" },
  { "apss_cc_gold_post_acd_debug_div_clk_src" },
  { "apss_cc_l3_pre_acd_debug_div_clk_src" },
  { "apss_cc_l3_post_acd_debug_div_clk_src" },
  { "apss_cc_gold_plus_pre_acd_debug_div_clk_src" },
  { "apss_cc_gold_plus_post_acd_debug_div_clk_src" },
  { NULL }
};


/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_TestCPUConfig
** =========================================================================*/
/*
  Test a single CPU frequency.
*/

static ClockResult Clock_TestCPUConfig
(
  uint32_t             nClusterIndex
)
{
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxt();
  uint32_t nLastActiveFreq = 0, nRequestedFreq = 0;
  uint32_t nAchievedFreq = 0, nTotalFreqLevel = 0;
  uint32_t nFreqLevel = 0, nMeasuredFreq=0, i=0;
  ClockIdType nClockId;
  
  ULOG_RT_PRINTF_0 (ClockAppsCtxt.hClockAppsULog, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
  ULOG_RT_PRINTF_1 (ClockAppsCtxt.hClockAppsULog, "\tTesting CPU %u\n", nClusterIndex);
  if (CLOCK_SUCCESS != ClockApps_Query(nClusterIndex, -1, CLOCKAPPS_REQUEST_DATA_NUMBER_OF_PERF_LEVELS, &nTotalFreqLevel)){
      ULOG_RT_PRINTF_1 (ClockAppsCtxt.hClockAppsULog,
            "ClockApps_GetCPUFrequencyLevels failed for CLUSTER %u\n", nClusterIndex);
      return CLOCK_ERROR;
    }
  for (nFreqLevel=0; nFreqLevel< nTotalFreqLevel; nFreqLevel++){
    if (CLOCK_SUCCESS != ClockApps_GetCPUFrequency (nClusterIndex, &nLastActiveFreq)){
      ULOG_RT_PRINTF_3 (ClockAppsCtxt.hClockAppsULog, "ClockApps_GetCPUFrequency failed to get active Freq of CPU %u before switching from %u -> %u\n", nClusterIndex, nLastActiveFreq, nRequestedFreq);
      continue;
    }
    ClockApps_Query(nClusterIndex, nFreqLevel, CLOCKAPPS_REQUEST_DATA_FREQUENCY_HZ, &nRequestedFreq);
    if (CLOCK_SUCCESS != ClockApps_SetCPUFrequency (nClusterIndex, nRequestedFreq, &nAchievedFreq)){
      ULOG_RT_PRINTF_3 (ClockAppsCtxt.hClockAppsULog, "ClockApps_SetCPUFrequency failed to switch CPU %u from %u -> %u\n", nClusterIndex, nLastActiveFreq, nRequestedFreq);
      continue;
    }
    if ((nAchievedFreq == nRequestedFreq) && (nAchievedFreq != nLastActiveFreq)){
      ULOG_RT_PRINTF_3 (ClockAppsCtxt.hClockAppsULog, "CPU %u is switching from %u -> %u\n", nClusterIndex, nLastActiveFreq, nRequestedFreq);
    }else{
      ULOG_RT_PRINTF_3 (ClockAppsCtxt.hClockAppsULog, "CPU %u Failed to switch from %u -> %u\n", nClusterIndex, nLastActiveFreq, nRequestedFreq);
    }
    ULOG_RT_PRINTF_3 (ClockAppsCtxt.hClockAppsULog, "Core: %u nRequestedFreq: %10u nAchievedFreq: %10u \n", nClusterIndex, nRequestedFreq, nAchievedFreq);

    for (i = 0; apcs_clks[i].szName != NULL; i++, nMeasuredFreq=0)
    {
       if ((Clock_GetId(pDrvCtxt->hClient, "apss_cc", &nClockId) == CLOCK_SUCCESS) &&
           (Clock_MeasureFrequencyEx(pDrvCtxt->hClient, nClockId,i+1, &nMeasuredFreq) == CLOCK_SUCCESS))
       {
           ULOG_RT_PRINTF_2 (ClockAppsCtxt.hClockAppsULog, "Success Clock: %50a at MeasureFreq: %10u \n", apcs_clks[i].szName, nMeasuredFreq );
       }
       else
       {     
           ULOG_RT_PRINTF_2 (ClockAppsCtxt.hClockAppsULog, "Failed Clock: %50a at MeasureFreq: %10u \n", apcs_clks[i].szName, nMeasuredFreq );
       }
    }
    ULOG_RT_PRINTF_0 (ClockAppsCtxt.hClockAppsULog,  "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n");
  }
  return CLOCK_SUCCESS;
} /* END Clock_TestCPUConfig */


/* =========================================================================
**  Function : Clock_ImageBIST
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_ImageBIST
(
  bool     *bBISTPassed,
  uint32_t *nFailedTests
)
{
  uint32_t          nFailedImageTests = 0;
  uint32_t          nClusterIndex;

  // INFO: Enable all CPU Cores before Testing.
  MpcoreInitDeferredCores (0);

  ULOG_RT_PRINTF_0 (ClockAppsCtxt.hClockAppsULog, "Running Image BIST:");
  for (nClusterIndex = 0; nClusterIndex < ClockAppsBSP.nNumClusters; nClusterIndex++){
    if(CLOCK_SUCCESS != Clock_TestCPUConfig(nClusterIndex)){
        nFailedImageTests++;
    }
  }

  if (nFailedImageTests == 0)
  {
   ULOG_RT_PRINTF_0 (ClockAppsCtxt.hClockAppsULog, "   Clock Image BIST Passed!");
  }
  else
  {
    ULOG_RT_PRINTF_0 (ClockAppsCtxt.hClockAppsULog, "   Clock Image BIST Failed!");
    *nFailedTests += nFailedImageTests;
    *bBISTPassed = false;
  }
  return CLOCK_SUCCESS;
} /* END Clock_ImageBIST */


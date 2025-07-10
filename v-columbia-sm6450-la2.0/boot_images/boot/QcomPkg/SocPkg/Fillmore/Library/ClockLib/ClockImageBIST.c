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
  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/ClockLib/ClockImageBIST.c#5 $
  $DateTime: 2021/10/21 21:26:38 $
  $Author: pwbldsvc $
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockApps.h"
#include "busywait.h"
#include <Library/KernelLib.h> // for ThreadSleep

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
  ClockAppsCPUType   eCPU,
  ClockFreqPlanType  aFreqPlan[],
  uint32             nPlanLen
)
{
  ClockDrvCtxt *pDrvCtxt = Clock_GetDrvCtxt();
  uint32_t nLastActiveFreq = 0;
  uint32_t nRequestedFreq = 0;
  uint32_t nAchievedFreq = 0;
  int32_t nFreqLevel = 0;
  uint32_t nCurrentActiveFreq = 0;
  uint32_t i=0, freq=0;
  ClockIdType nClockId;

   DEBUG((EFI_D_WARN, "Testing CPU %d\n", eCPU));
   DEBUG((EFI_D_WARN, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n"));
  ULOG_RT_PRINTF_1(pDrvCtxt->hClockBISTLog, "\tTesting CPU %d", eCPU);
    for (nFreqLevel=MIN_PERF_LEVEL; nFreqLevel< nPlanLen; nFreqLevel++){
        if (CLOCK_SUCCESS == ClockApps_GetCPUFrequency (eCPU, &nLastActiveFreq)){
            nRequestedFreq = aFreqPlan[nFreqLevel].nFreqHz;
            if (CLOCK_SUCCESS == ClockApps_SetCPUFrequency (eCPU, nRequestedFreq, &nAchievedFreq)){
                busywait(100);
                if (CLOCK_SUCCESS == ClockApps_GetCPUFrequency (eCPU, &nCurrentActiveFreq)){
                    if ((nAchievedFreq == nRequestedFreq) &&
                        (nAchievedFreq == nCurrentActiveFreq)){
                        ULOG_RT_PRINTF_3(pDrvCtxt->hClockBISTLog, "CPU %d is switching from %d -> %d", eCPU, nLastActiveFreq, nRequestedFreq);
                    }else{
                        ULOG_RT_PRINTF_3(pDrvCtxt->hClockBISTLog, "CPU %d Failed to switch from %d -> %d", eCPU, nLastActiveFreq, nRequestedFreq);
                    }
                }else{
                    ULOG_RT_PRINTF_3(pDrvCtxt->hClockBISTLog, "ClockApps_GetCPUFrequency failed to get active Freq of CPU %d after switching from %d -> %d", eCPU, nLastActiveFreq, nRequestedFreq);
                }
            }else{
                ULOG_RT_PRINTF_3(pDrvCtxt->hClockBISTLog, "ClockApps_SetCPUFrequency failed to switch CPU %d from %d -> %d", eCPU, nLastActiveFreq, nRequestedFreq);
            }

            DEBUG((EFI_D_WARN, "Core: %u nRequestedFreq: %10u nAchievedFreq: %10u \n", eCPU, nRequestedFreq, nAchievedFreq ));

            for (i = 0; apcs_clks[i].szName != NULL; i++)
            {
              if ((Clock_GetId(pDrvCtxt->hClient, "apss_cc", &nClockId) == CLOCK_SUCCESS) &&
                  (Clock_MeasureFrequencyEx(pDrvCtxt->hClient, nClockId,i+1, &freq) == CLOCK_SUCCESS))
              {
                 busywait(5);
                 DEBUG((EFI_D_WARN, "Success Clock: %50a at MeasureFreq: %10u \n", apcs_clks[i].szName, freq ));
              }
              else
              {     
                  DEBUG((EFI_D_WARN, "Failed Clock: %50a at MeasureFreq: %10u \n", apcs_clks[i].szName, freq ));
    
              }
            }
            DEBUG((EFI_D_WARN, "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ \n"));
        }else{
            ULOG_RT_PRINTF_3(pDrvCtxt->hClockBISTLog, "ClockApps_GetCPUFrequency failed to get active Freq of CPU %d before switching from %d -> %d", eCPU, nLastActiveFreq, nRequestedFreq);
        }
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

  uint32_t nFailedImageTests = 0;
  ClockAppsCPUType   eCPU;
  ClockDrvCtxt        *pDrvCtxt = Clock_GetDrvCtxt();
  uint32 aFreqLevels[CLOCK_APPS_CPU_TOTAL] = {0};
  ClockFreqPlanType aFreqPlan[CLOCK_APPS_CPU_TOTAL][CLOCK_EPSS_LUT_MAX_ROWS] = {0};

  // INFO: Enable all CPU Cores before Testing.
  MpcoreInitDeferredCores (0);

  ULOG_RT_PRINTF_0(pDrvCtxt->hClockBISTLog, "Running Image BIST:");
    for (eCPU = CLOCK_APPS_CPU_C0; eCPU < CLOCK_APPS_CPU_TOTAL; eCPU++){
        if (CLOCK_SUCCESS == ClockApps_GetCPUFrequencyLevels (eCPU, &aFreqLevels[eCPU])){
            //memset(aFreqPlan, 0x0,sizeof (aFreqPlan))
            if (CLOCK_SUCCESS == ClockApps_GetCPUFrequencyPlan(eCPU, aFreqPlan[eCPU], aFreqLevels[eCPU])){
                if(CLOCK_SUCCESS != Clock_TestCPUConfig(eCPU, aFreqPlan[eCPU], aFreqLevels[eCPU])){
                    nFailedImageTests++;
                }
            }else{
                DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
                        "ClockApps_GetCPUFrequencyPlan failed for CLUSTER %d", eCPU);
                nFailedImageTests++;
            }
        }else{
            DALSYS_LogEvent(DALDEVICEID_CLOCK, DALSYS_LOGEVENT_FATAL_ERROR,
                "ClockApps_GetCPUFrequencyLevels failed for CLUSTER %d", eCPU);
            nFailedImageTests++;
        }
    }

  if (nFailedImageTests == 0)
  {
    ULOG_RT_PRINTF_0(pDrvCtxt->hClockBISTLog, "   Clock Image BIST Passed!");
  }
  else
  {
    ULOG_RT_PRINTF_0(pDrvCtxt->hClockBISTLog, "   Clock Image BIST Failed!");
    *nFailedTests += nFailedImageTests;
    *bBISTPassed = false;
  }
  return CLOCK_SUCCESS;

} /* END Clock_ImageBIST */


/*
===========================================================================
*/
/**
  @file ClockBIST.c

  Interface implementation file for the clock device driver
  Built-In-Self-Test (BIST).
*/
/*
  ====================================================================

  Copyright (c) 2011-2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/ClockDxe/ClockBIST.c#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "stdint.h"
#include "stdbool.h"
#include "Clock.h"
#include "ClockDriver.h"
#include "HALclk.h"
#include "busywait.h"

extern DALResult  Clock_GetPropertyHandle(const char* str, void** handle );
/*=========================================================================
      Definitions
==========================================================================*/

/*
 * The measured clock frequency must match the desired frequency within
 * the following error margin expressed in PPM of the desired
 * frequency, with a minimum error tolerance of 1 kHz.
 */
#define CLOCK_BIST_ERROR_MARGIN_PPM         100     /* Expressed in PPM */
#define CLOCK_BIST_ERROR_MINIMUM_TOLERANCE  1000    /* Expressed in Hz */

/*
 * Macro to return absolute value of the difference between two values
 */
#define ABS_DIFF(v1, v2)  ((v1 >= v2) ? (v1 - v2) : (v2 - v1))

/*
 * This is the maximum number of delay attempts that will be made when
 * waiting for a clock change (config, enable, disable, etc) to propagate
 * to the status register.
 */
#define CLOCK_BIST_CONFIG_DELAY_ATTEMPTS    150    /* Expressed in iterations */

/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_CheckBistExceptions
** =========================================================================*/
/**
  Check the given clock name against the clock names in the BIST exceptions
  clock name array.

  Some clocks are expected to fail the BIST under certain conditions. The
  names of these clocks are listed in an array together with other BSP data.
  This function searches that array for the given name and returns the
  result of that search.

  @param *pBISTExceptions [in] -- Handle to the BIST exceptions list
  @param *szName [in] -- Name of the clock to check.

  @return
  TRUE -- The clock name was found in the BIST exceptions array.
  FALSE -- The clock name is not in the array.

  @dependencies
  None.
*/

static boolean Clock_CheckBistExceptions
(
  ClockNameListType *pBISTExceptions,
  const char    *szName
)
{
  uint32 nIndex;

  for (nIndex = 0; pBISTExceptions[nIndex].szName != NULL; nIndex++)
  {
    if (strcmp(pBISTExceptions[nIndex].szName, szName) == 0)
    {
      return TRUE;
    }
  }

  return FALSE;

} /* END Clock_CheckBistExceptions */



/* =========================================================================
**  Function : Clock_CheckIfExcludedFromBist
** =========================================================================*/
/**
  Check the given clock name against the clock names in the list of clocks
  excluded from the BIST clock name array.

  Some clocks cannot be tested by the BIST under certain conditions. The
  names of these clocks are listed in an array together with other BSP data.
  This function searches that array for the given name and returns the
  result of that search.

  @param *pExcludeFromBist [in] -- Pointer to the list structure.
  @param *szName [in] -- Name of the clock to check.

  @return
  TRUE -- The clock name was found in the array.
  FALSE -- The clock name is not in the array.

  @dependencies
  None.
*/

static boolean Clock_CheckIfExcludedFromBist
(
  ClockNameListType *pExcludeFromBist,
  const char        *szName
)
{
  uint32 nIndex;

  for (nIndex = 0; pExcludeFromBist[nIndex].szName != NULL; nIndex++)
  {
    if (strcmp(pExcludeFromBist[nIndex].szName, szName) == 0)
    {
      return TRUE;
    }
  }

  return FALSE;

} /* END Clock_CheckIfExcludedFromBist */



/* =========================================================================
**  Function : Clock_TestClockFunctions
** =========================================================================*/
/**
  Perform a non-destructive built-in self test of all clock functions on the
  specified clock.

  @param ClockId [in] -- ID of the particular clock being tested.
  @param bIsClockSupportedIsOn [in] -- Specifies whether the clock supports
                                       "IsOn" API functionality
  @param bIsClockSupportedCalcFreq [in] -- Specifies whether the clock supports
                                           "CalcFreq" API functionality

  @return
  true -- BIST was successful.
  false -- BIST failed.

  @dependencies
  Core and image initialization must be complete prior to running the BIST.
*/

static bool Clock_TestClockFunctions
(
  ClockIdType ClockId,
  bool        bIsClockSupportedIsOn,
  bool        bIsClockSupportedCalcFreq
)
{
  ClockResult         eResult;
  bool                bStatus = FALSE;
  uint32_t            nFreqHz = 0;
  uint32_t            nFreqError;
  uint32_t            nFreqErrorMargin;
  ClockMuxConfigType  *pBSPConfig;
  bool                bBISTPassed = true;
  uint32_t            nTimeout;
  uint32_t            i;
  ClockNodeType      *pClock;
  ClockDrvCtxt       *pDrvCtxt = Clock_GetDrvCtxt();

  /*-----------------------------------------------------------------------*/
  /* Validate args.                                                        */
  /*-----------------------------------------------------------------------*/

  pClock = Clock_GetClockNode(ClockId);
  if (!pClock)
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   Invalid clock id:  %d", ClockId);
    return false;
  }

  /*-----------------------------------------------------------------------*/
  /* Set frequency if clock has not been initialized.                      */
  /*-----------------------------------------------------------------------*/

  if (pClock->pDomain != NULL &&
      pClock->pDomain->aBSP != NULL &&
      pClock->pDomain->pActiveMuxConfig == NULL)
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   Initializing clock domain");

    /* Loop over all configurations */
    for (i = 0; i < pClock->pDomain->nBSPLen; i++)
    {
      pBSPConfig = &pClock->pDomain->aBSP[i];

      /* Skip configurations that aren't for this chip or version. */
      if ( !Clock_IsBSPSupported(&pBSPConfig->HWVersion) )
      {
        continue;
      }

      /* Set the new frequency */
      eResult = Clock_SetFrequency(pDrvCtxt->hClient, ClockId,
        pBSPConfig->nFreqHz, CLOCK_FREQUENCY_HZ_EXACT, &nFreqHz);

      /* Check results of the operation */
      if (eResult != CLOCK_SUCCESS)
      {
        bBISTPassed = false;
        ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   SetFrequency: ERROR");
      }
      else
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   SetFrequency:  %d Hz", nFreqHz);
      }

      /* The returned frequency must match the desired frequency exactly */
      if (pBSPConfig->nFreqHz != nFreqHz)
      {
        bBISTPassed = false;
        ULOG_RT_PRINTF_2 (pDrvCtxt->hClockBISTLog,
                          "   Frequency mismatch -- wanted: %d Hz vs got: %d Hz",
                          pBSPConfig->nFreqHz, nFreqHz);
      }

      break;
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Turn on the clock.                                                    */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_Enable(pDrvCtxt->hClient, ClockId);
  if (eResult != CLOCK_SUCCESS)
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   Enable: ERROR");

    /* If this operation failed, there is no point in continuing the test */
    return false;
  }
  else
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   Enable: SUCCESS");
  }

  /*-----------------------------------------------------------------------*/
  /* Test whether the clock was enabled successfully.                      */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_IsEnabled(pDrvCtxt->hClient, ClockId, &bStatus);
  if (eResult != CLOCK_SUCCESS)
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsEnabled: ERROR");
  }
  else
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   IsEnabled: %d", bStatus);
  }

  /* If this operation failed, we need to clean up before returning */
  if (eResult != CLOCK_SUCCESS || bStatus == 0)
  {
    bBISTPassed = false;
  }
  else
  {
    /* Verify the clock is "on" if this function is supported */
    if (bIsClockSupportedIsOn)
    {
      eResult = Clock_IsOn(pDrvCtxt->hClient, ClockId, &bStatus);
      if (eResult != CLOCK_SUCCESS)
      {
        bBISTPassed = false;
        ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: ERROR");
      }
      else
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   IsOn: %d", bStatus);

        /*
         * Since the clock is enabled and IsOn API is supported,
         * if it's not on, we have an error.
         */
        if (!bStatus)
        {
          bBISTPassed = false;
          ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: status mismatch");
        }
      }
    }
    else
    {
      ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: NOT SUPPORTED");
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Test all defined frequencies for this clock if possible.              */
  /*-----------------------------------------------------------------------*/

  if (bBISTPassed == true)
  {
    /* Make sure the clock handle is valid and supports frequency configuration */
    if (pClock->pDomain == NULL ||
        pClock->pDomain->aBSP == NULL ||
        CLOCK_FLAG_IS_SET(pClock->pDomain, DFS_CONTROLLED))
    {
      if (pClock->pDomain && CLOCK_FLAG_IS_SET(pClock->pDomain, DFS_CONTROLLED))
      {
        ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   SetFrequency: Skipping due to DFS control");
      }
      else
      {
        ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   SetFrequency: NOT SUPPORTED");
      }

      /* Just calculate the current clock frequency and report it */
      if (bIsClockSupportedCalcFreq)
      {
        eResult = Clock_MeasureFrequency(pDrvCtxt->hClient, ClockId, &nFreqHz);
        if (eResult != CLOCK_SUCCESS)
        {
          bBISTPassed = false;
          ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: ERROR");
        }
        else
        {
          ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: %d Hz", nFreqHz);
        }
      }
      else
      {
        ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: NOT SUPPORTED");
      }
    }
    else
    {
      /* Loop over all configurations */
      for (i = 0; i < pClock->pDomain->nBSPLen; i++)
      {
        pBSPConfig = &pClock->pDomain->aBSP[i];

        /* Skip configurations that aren't for this chip or version. */
        if ( !Clock_IsBSPSupported(&pBSPConfig->HWVersion) )
        {
          continue;
        }

        /* Select the new frequency to test */
        eResult = Clock_SetFrequency(pDrvCtxt->hClient, ClockId,
          pBSPConfig->nFreqHz, CLOCK_FREQUENCY_HZ_EXACT, &nFreqHz);

        /* Check results of the operation */
        if (eResult != CLOCK_SUCCESS)
        {
          bBISTPassed = false;
          ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   SetFrequency: ERROR");
        }
        else
        {
          ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   SetFrequency:  %d Hz", nFreqHz);
        }

        /* The returned frequency must match the desired frequency exactly */
        if (pBSPConfig->nFreqHz != nFreqHz)
        {
          bBISTPassed = false;
          ULOG_RT_PRINTF_2 (pDrvCtxt->hClockBISTLog,
                            "   Frequency mismatch -- wanted: %d Hz vs got: %d Hz",
                            pBSPConfig->nFreqHz, nFreqHz);
        }

        /*
         * Allow sufficient time for the clock status to propagate after
         * applying a new configuration.  This is needed due to issues
         * seen on 9x15 where 0 MHz was measured on clocks after a slow
         * speed was configured but not fully propagated.
         */
        if (bIsClockSupportedIsOn)
        {
          nTimeout = 0;

          do
          {
            busywait(1);
            eResult = Clock_IsOn(pDrvCtxt->hClient, ClockId, &bStatus);

            /* Check results of the operation */
            if (eResult != CLOCK_SUCCESS)
            {
              ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: ERROR");
            }

          } while ( (eResult == CLOCK_SUCCESS) &&
                    (!bStatus              ) &&
                    (nTimeout++ < CLOCK_BIST_CONFIG_DELAY_ATTEMPTS) );

          /* Log a warning if the clock does not turn ON */
          if (eResult != CLOCK_SUCCESS || !bStatus)
          {
            bBISTPassed = false;

            ULOG_RT_PRINTF_1(pDrvCtxt->hClockBISTLog,
                             "   Unable to turn ON clock: %s.",
                             pClock->szName);
          }
        }

        /* Measure the frequency of the clock */
        if (bIsClockSupportedCalcFreq)
        {
          eResult = Clock_MeasureFrequency(pDrvCtxt->hClient, ClockId, &nFreqHz);

          /* Check results of the operation */
          if (eResult != CLOCK_SUCCESS)
          {
            bBISTPassed = false;
            ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: ERROR");
          }
          else
          {
            ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: %d Hz", nFreqHz);
          }

          /* Compute the error rate between the desired and the measured values */
          nFreqError = ABS_DIFF(pBSPConfig->nFreqHz, nFreqHz);
          nFreqErrorMargin = (uint32_t)(((uint64_t)pBSPConfig->nFreqHz * CLOCK_BIST_ERROR_MARGIN_PPM) / 1000000);

          /* Ignore any error within the permitted tolerance value */
          if (nFreqError > CLOCK_BIST_ERROR_MINIMUM_TOLERANCE)
          {
            /* The calculated frequency must match the desired frequency to some degree */
            if (nFreqError > nFreqErrorMargin)
            {
              bBISTPassed = false;
              ULOG_RT_PRINTF_2 (pDrvCtxt->hClockBISTLog,
                                "   Frequency error %d Hz exceeds error margin of %d Hz",
                                nFreqError, nFreqErrorMargin);
            }
            else
            {
              ULOG_RT_PRINTF_2 (pDrvCtxt->hClockBISTLog,
                                "   Frequency error %d Hz is within error margin of %d Hz",
                                nFreqError, nFreqErrorMargin);
            }
          }
          else
          {
            ULOG_RT_PRINTF_2 (pDrvCtxt->hClockBISTLog,
                              "   Frequency error %d Hz is within error tolerance of %d Hz",
                              nFreqError, CLOCK_BIST_ERROR_MINIMUM_TOLERANCE);
          }
        }
        else
        {
          ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: NOT SUPPORTED");
        }
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Turn off the clock after completing the test.                         */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_Disable(pDrvCtxt->hClient, ClockId);
  if (eResult != CLOCK_SUCCESS)
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   Disable: ERROR");
    return false;
  }
  else
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   Disable: SUCCESS");
  }

  /*-----------------------------------------------------------------------*/
  /* Test whether the clock was disabled successfully.                     */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_IsEnabled(pDrvCtxt->hClient, ClockId, &bStatus);
  if (eResult != CLOCK_SUCCESS)
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsEnabled: ERROR");
  }
  else
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   IsEnabled: %d", bStatus);
  }

  /* Update the test result to be returned */
  if (eResult != CLOCK_SUCCESS || bStatus == 1)
  {
    bBISTPassed = false;
  }
  else
  {
    /*
     * Allow sufficient time for clocks to turn off.  This is needed
     * due to issues seen on 9x15 where clocks with slow configurations
     * took longer for the off status to propagate.
     */
    if (bIsClockSupportedIsOn)
    {
      nTimeout = 0;

      do
      {
        busywait(1);
        eResult = Clock_IsOn(pDrvCtxt->hClient, ClockId, &bStatus);

        /* Check results of the operation */
        if (eResult != CLOCK_SUCCESS)
        {
          ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: ERROR");
        }

      } while ( (eResult == CLOCK_SUCCESS) &&
                (bStatus               ) &&
                (nTimeout++ < CLOCK_BIST_CONFIG_DELAY_ATTEMPTS) );

      ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   IsOn: %d", bStatus);

      /* Log a warning if the clock does not turn OFF */
      if (eResult != CLOCK_SUCCESS || bStatus)
      {
        bBISTPassed = false;

        ULOG_RT_PRINTF_1(pDrvCtxt->hClockBISTLog,
                         "   Unable to turn OFF clock: %s.",
                         pClock->szName);
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Return final result.                                                  */
  /*-----------------------------------------------------------------------*/

  return bBISTPassed;

} /* END Clock_TestClockFunctions */


/* =========================================================================
**  Function : Clock_TestClock
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockResult Clock_TestClock
(
  ClockIdType ClockId
)
{
  DALResult      eResult;
  bool           bStatus = FALSE;
  uint32_t       nFreqHz = 0;
  bool           bIsClockSupportedEnable;
  bool           bIsClockSupportedIsOn;
  bool           bIsClockSupportedCalcFreq;
  bool           bBISTPassed = true;
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  ClockNodeType *pClock = Clock_GetClockNode(ClockId);

  /*-----------------------------------------------------------------------*/
  /* Initialize the BIST log.                                              */
  /*-----------------------------------------------------------------------*/

  if (pDrvCtxt->hClockBISTLog == NULL)
  {
    ULogFront_RealTimeInit (&pDrvCtxt->hClockBISTLog, "Clock BIST Log",
                            pDrvCtxt->nBISTLogSize,
                            ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);
    ULogCore_HeaderSet (pDrvCtxt->hClockBISTLog,
                        "Content-Type: text/tagged-log-1.0;");
  }

  /*-----------------------------------------------------------------------*/
  /* Sanity check the handle.                                              */
  /*-----------------------------------------------------------------------*/

  if (pClock == NULL)
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog,
                      "   INVALID CONFIGURATION DETECTED -- test aborted");
    return CLOCK_ERROR;
  }

  if (CLOCK_FLAG_IS_SET(pClock, EXPLICIT_ACCESS_ONLY))
  {
    return CLOCK_SUCCESS;
  }

  /*-----------------------------------------------------------------------*/
  /* Identify the clock in the log by name and run the available tests.    */
  /*-----------------------------------------------------------------------*/

  ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog,
                    "Testing %s...", pClock->szName);

  /*
   * Determine whether the clock supports "Enable" API functionality
   */

  bIsClockSupportedEnable = HAL_clk_IsClockSupported (&pClock->HALClock,
                                                      HAL_CLK_CLOCK_API_ENABLE);

  /*
   * Determine whether the clock supports "IsOn" API functionality
   */

  bIsClockSupportedIsOn = HAL_clk_IsClockSupported (&pClock->HALClock,
                                                    HAL_CLK_CLOCK_API_ISON);

  /*
   * Determine whether the clock supports "CalcFreq" API functionality
   */

  bIsClockSupportedCalcFreq = HAL_clk_IsClockSupported (&pClock->HALClock,
                                                        HAL_CLK_CLOCK_API_CALCFREQ);

  /*
   * Determine if the clock is already enabled
   */

  eResult = Clock_IsEnabled(pDrvCtxt->hClient, ClockId, &bStatus);
  if (eResult != CLOCK_SUCCESS)
  {
    ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsEnabled: ERROR");

    /* We must terminate the test here */
    return CLOCK_ERROR;
  }

  /*
   * If the clock is enabled, we'll assume it's in use and we can only verify
   * that it's on and check its frequency.
   */

  if (bStatus)
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   IsEnabled: %d", bStatus);

    /* Verify the clock is "on" if this function is supported */
    if (bIsClockSupportedIsOn)
    {
      eResult = Clock_IsOn(pDrvCtxt->hClient, ClockId, &bStatus);
      if (eResult != CLOCK_SUCCESS)
      {
        bBISTPassed = false;
        ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: ERROR");
      }
      else
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   IsOn: %d", bStatus);

        /*
         * Since the clock is enabled and IsOn API is supported,
         * if it's not on, we have an error.
         */
        if (!bStatus)
        {
          bBISTPassed = false;
          ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: status mismatch");
        }
      }
    }
    else
    {
      ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: NOT SUPPORTED");
    }

    if (bIsClockSupportedCalcFreq)
    {
      eResult = Clock_MeasureFrequency(pDrvCtxt->hClient, ClockId, &nFreqHz);
      if (eResult != CLOCK_SUCCESS)
      {
        bBISTPassed = false;
        ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: ERROR");
      }
      else
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: %d Hz", nFreqHz);
      }
    }
    else
    {
      ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   MeasureFrequency: NOT SUPPORTED");
    }
  }
  else
  {
    /*
     * If the clock is disabled and it supports the "Enable" API, then it's not in use
     * and we can perform a complete test. Verify one more time that the clock is truly
     * "off" before proceeding to the complete test just in case the "Enable" API is
     * returning an erroneous result.
     */
    if (bIsClockSupportedEnable)
    {
      /* Verify the clock is truly "off" if this function is supported */
      if (bIsClockSupportedIsOn)
      {
        eResult = Clock_IsOn(pDrvCtxt->hClient, ClockId, &bStatus);
        if (eResult != CLOCK_SUCCESS)
        {
          bBISTPassed = false;
          ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   IsOn: ERROR");
        }
        else
        {
          ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   IsOn: %d", bStatus);

          /*
           * If the clock is "on", we cannot continue with the complete test;
           * we must stop the test, but we cannot return failure because for
           * some clocks this is a legitimate state because these clocks may
           * be voted for by different masters. Therefore, we may think that
           * the clock is disabled because we voted for it to be disabled, but
           * in fact, the clock is "on" because one or more of the other masters
           * has voted for this clock to remain "on".
           */
          if (bStatus)
          {
            ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog,
                              "   IsOn: status mismatch -- test aborted");
            return CLOCK_SUCCESS;
          }
        }
      }

      /* Continue with the complete test if passed all the safety checks. */
      if (bBISTPassed)
      {
        bBISTPassed = Clock_TestClockFunctions(ClockId,
                                                bIsClockSupportedIsOn,
                                                bIsClockSupportedCalcFreq);
      }
    }
    else
    {
      ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog, "   Enable: NOT SUPPORTED");
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Log final result.                                                     */
  /*-----------------------------------------------------------------------*/

  if (bBISTPassed)
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   Clock %s BIST Passed!",
                      pClock->szName);
    return CLOCK_SUCCESS;
  }
  else
  {
    ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "   Clock %s BIST Failed!",
                      pClock->szName);
    return CLOCK_ERROR;
  }

} /* END Clock_TestClock */



/* =========================================================================
**  Function : Clock_BIST
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockResult Clock_BIST
(
  void
)
{
  ClockResult    eResult;
  uint32_t       nClockIndex;
  ClockNodeType *pClock;
  ClockIdType    ClockId = 0;
  bool           bBISTPassed = true;
  uint32_t       nFailedTests = 0;
  ClockDrvCtxt  *pDrvCtxt = Clock_GetDrvCtxt();
  uint32         i;
  ClockPowerDomainNodeType  *pPowerDomain;
  void* pExcludeFromBist = NULL;
  void* pBISTDependencies = NULL;
  void* pExcludedPowerDomains = NULL;
  void* pBISTExceptions = NULL;

  /*-----------------------------------------------------------------------*/
  /* Initialize the BIST log.                                              */
  /*-----------------------------------------------------------------------*/

  ULogFront_RealTimeInit (&pDrvCtxt->hClockBISTLog, "Clock BIST Log",
                          pDrvCtxt->nBISTLogSize,
                          ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);
  ULogCore_HeaderSet (pDrvCtxt->hClockBISTLog,
                      "Content-Type: text/tagged-log-1.0;");

  /* Get the handle for the lists */
  eResult = Clock_GetPropertyHandle("BISTDependencies",&pBISTDependencies);
  eResult = Clock_GetPropertyHandle("ExcludeFromBist",&pExcludeFromBist);
  eResult = Clock_GetPropertyHandle("ExcludedPowerDomains",&pExcludedPowerDomains);
  eResult = Clock_GetPropertyHandle("BISTExceptions",&pBISTExceptions);

  /*
   * Enable any clocks that need to be enabled prior to running the BIST.
   */
  if (pBISTDependencies != NULL)
  {
    for (i = 0; ((ClockNameListType*)pBISTDependencies)[i].szName != NULL; i++)
    {
      if (Clock_GetClockId(pDrvCtxt->hClient, ((ClockNameListType*)pBISTDependencies)[i].szName, &ClockId) == DAL_SUCCESS)
      {
        pClock = Clock_GetClockNode(ClockId);
        if (pClock == NULL)
        {
          ULOG_RT_PRINTF_2 (pDrvCtxt->hClockBISTLog, "Failed to retrieve clock pointer for ID %d for BIST dependency clock %s",
            (int)ClockId, ((ClockNameListType*)pBISTDependencies)[i].szName);
          DEBUG((EFI_D_WARN, "Failed to retrieve clock pointer for ID %d for BIST dependency clock %a\n",(int)ClockId,((ClockNameListType*)pBISTDependencies)[i].szName));
        }
        else
        {
          if (Clock_EnableClock(pDrvCtxt->hClient, ClockId) != DAL_SUCCESS)
          {
            ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "Failed to enable BIST dependency clock %s",
              ((ClockNameListType*)pBISTDependencies)[i].szName);
            DEBUG((EFI_D_WARN, "Failed to enable BIST dependency clock %a\n",((ClockNameListType*)pBISTDependencies)[i].szName));
          }
        }
      }
      else
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "Failed to retrieve ID for BIST dependency clock %s",
          ((ClockNameListType*)pBISTDependencies)[i].szName);
        DEBUG((EFI_D_WARN, "Failed to retrieve ID for BIST dependency clock %a\n",((ClockNameListType*)pBISTDependencies)[i].szName));
      }
    }
  }

  /*
   * Enable the power domains so that clocks turns on.
   */
  for (i = 0; i < pDrvCtxt->pBSP->nNumPowerDomains; i++)
  {
    pPowerDomain = &pDrvCtxt->pBSP->aPowerDomains[i];

    /*
     * Check the power domain name against the list of power domains that should not be
     * enabled before running the BIST and skip this power domain if it is in the list.
     */
    if (pExcludedPowerDomains != NULL)
    {
      if (Clock_CheckIfExcludedFromBist((ClockNameListType*)pExcludedPowerDomains, pPowerDomain->szName) == TRUE)
      {
        continue;
      }
    }

    /*
     * Do not enable power domains which are already turned on,
     * and do not disable them at the end.
     */

    if (!HAL_clk_IsPowerDomainOn(&pPowerDomain->HALPowerDomain))
    {
      if ( Clock_GetId(pDrvCtxt->hClient, pPowerDomain->szName, &ClockId) == CLOCK_SUCCESS && 
           Clock_EnablePowerDomain(pDrvCtxt->hClient, ClockId) != CLOCK_SUCCESS)
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockBISTLog, "Failed to enable %s",
          pPowerDomain->szName);
      }
    }
  }

  /*-----------------------------------------------------------------------*/
  /* Test each clock node.                                                 */
  /*-----------------------------------------------------------------------*/

  for (nClockIndex = 0; nClockIndex < pDrvCtxt->pBSP->nNumClocks; nClockIndex++)
  {
    pClock = &pDrvCtxt->pBSP->aClocks[nClockIndex];

    /*
     * Check the clock name against the list of clocks that should not
     * be running the BIST and skip this clock if it is in the list.
     */
    if (pExcludeFromBist != NULL)
    {
      if (Clock_CheckIfExcludedFromBist((ClockNameListType*)pExcludeFromBist, pClock->szName) == TRUE)
      {
        continue;
      }
    }

    /*
     * Check the clock name against the list of clocks that are expected
     * to fail BIST under certain conditions and mark this clock
     * appropriately.
     */
    if (pBISTExceptions != NULL)
    {
      if (Clock_CheckBistExceptions((ClockNameListType*)pBISTExceptions, pClock->szName) == TRUE)
      {
        CLOCK_FLAG_SET(pClock, BIST_FAILURE_ANTICIPATED);
      }
    }
    Clock_GetId(pDrvCtxt->hClient, pClock->szName, &ClockId);
    eResult = Clock_TestClock (ClockId);
    if (eResult != DAL_SUCCESS)
    {
      /*
       * Determine whether the BIST for this clock was expected to fail.
       * If so, don't count the failure against the rest of the test.
       */
      if (CLOCK_FLAG_IS_SET(pClock, BIST_FAILURE_ANTICIPATED))
      {
        ULOG_RT_PRINTF_0 (pDrvCtxt->hClockBISTLog,
                          "   Failure Anticipated -- Ignoring Result.");
      }
      else
      {
        bBISTPassed = false;
        nFailedTests++;
      }
    }
  }

  /* Run the image-specific BIST. */
  Clock_ImageBIST(&bBISTPassed, &nFailedTests);

  /*-----------------------------------------------------------------------*/
  /* Log final result.                                                     */
  /*-----------------------------------------------------------------------*/

  if (bBISTPassed)
  {
    ULOG_RT_PRINTF_0(pDrvCtxt->hClockBISTLog, "Clock BIST Passed!");
    return CLOCK_SUCCESS;
  }
  else
  {
    ULOG_RT_PRINTF_2(pDrvCtxt->hClockBISTLog,
                     "Clock BIST Failed %d out of %d tests!",
                     nFailedTests, nClockIndex);
    return CLOCK_ERROR;
  }

} /* END Clock_BIST */


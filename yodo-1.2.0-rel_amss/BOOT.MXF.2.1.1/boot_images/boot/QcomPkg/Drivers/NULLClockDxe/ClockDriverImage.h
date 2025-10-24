#ifndef __CLOCKDRIVERIMAGE_H__
#define __CLOCKDRIVERIMAGE_H__
/*
===========================================================================
*/
/**
  @file ClockDriverImage.h

  Header file for the clock device driver APT's exposed to clients.
*/
/*
  ====================================================================

  Copyright (c) 2020 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/NULLClockDxe/ClockDriverImage.h#1 $
  $DateTime: 2022/08/18 10:15:46 $
  $Author: pwbldsvc $

  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDriver.h"

/*=========================================================================
      Function Definitions
==========================================================================*/

/*=========================================================================
**  Function : Clock_GetMaxPerfLevel
** =========================================================================*/
/*
  Returns the maximum defined performance level for the processor clock.

  This function returns the maximum defined processor performance level.
  Each performance level corresponds to a unique clock/voltage pair.

  Parameters Description:

  @param nCPU        [in]  -- Specifies the CPU core/cluster of interest.
  @param pnPerfLevel [out] -- Pointer to fill in with the maximum
                              performance level.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERROR   -- Valid configuration is not available.

*/

ClockResult
Clock_GetMaxPerfLevel (
  uint32_t nCPU,
  uint32_t *pnPerfLevel
);


/* =========================================================================
**  Function : Clock_GetMinPerfLevel
** =========================================================================*/
/*
  Returns the minimum defined performance level for the processor clock.

  This function returns the minimum defined processor performance level.
  Each performance level corresponds to a unique clock/voltage pair.

  Parameters Description:

  @param nCPU        [in]  -- Specifies the CPU core/cluster of interest.
  @param pnPerfLevel [out] -- Pointer to fill in with the minimum
                              performance level.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERROR   -- Valid configuration is not available.

*/

ClockResult Clock_GetMinPerfLevel
(
  uint32_t nCPU,
  uint32_t *pnPerfLevel
);


/* =========================================================================
**  Function : Clock_GetCPUFrequencyLevels
** =========================================================================*/
/*
  Returns the number of defined performance level for the specified CPU.

  This function returns the number of defined processor performance level.
  Each performance level corresponds to a unique clock/voltage pair.

  Parameters Description:

  @param nCPU              [in]  -- Specifies the CPU core/cluster of interest.
  @param pnFrequencyLevels [out] -- Pointer to the number of frequency levels.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERROR   -- Valid configuration is not available.

*/
ClockResult
Clock_GetCPUFrequencyLevels (
  uint32_t nCPU,
  uint32_t *pnFrequencyLevels 
);


/* =========================================================================
**  Function : Clock_GetCPUFrequencyPlan
** =========================================================================*/
/*
  Dumps the frequency plan for the specified CPU in the Table passed as pointer.

  This function dumps the frequency plan in the table pointer passed for the specified CPU.

  Parameters Description:

  @param nCPU              [in]  -- Specifies the CPU core/cluster of interest.
  @param pCPUFreqPlan      [in]  -- Pointer to the table storing the frequency plan of the corresponding CPU.
  @param nSize             [in]  -- Size of the Frequency plan table, expected value to be:
                                    (No. of Perf Levels * sizeof(ClockFreqPlanType))

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERROR   -- Valid configuration is not available.

*/
ClockResult
Clock_GetCPUFrequencyPlan (
  uint32_t            nCPU,
  ClockFreqPlanType *pCPUFreqPlan,
  uint32_t            nSize
);


/* =========================================================================
**  Function : Clock_SetCPUFrequency
** =========================================================================*/
/*
  Changes the processor clock speed and voltage.

  This function changes the performance level of the specified CPU to the
  specified frequency and the corresponding voltage level.

  Parameters Description:

  @param nCPU             [in]  -- Specifies the CPU core/cluster of interest.
  @param nFrequencyHz     [in]  -- User requested frequency.
  @param pnResultFreqHz   [out] -- Pointer to the actual frequency achieved.(It is an optional parameter)

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERROR   -- Valid configuration is not available.

*/
ClockResult
Clock_SetCPUFrequency (
  uint32_t nCPU,
  uint32_t nFrequencyHz,
  uint32_t *pnResultFreqHz
);


/* ===========================================================================
**  Function :  Clock_DetectCPUFrequency
**    
** ======================================================================== 
*/
/*
  Returns the current clock speed in Hz of the given processor.

  This function returns the current CPU frequency.

  Parameters Description:

  @param nCPU             [in]  -- Specifies the CPU core/cluster of interest.
  @param nFreqHz          [out] -- Pointer to fill in with the corresponding
                                    frequency in Hz.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERROR   -- Valid configuration is not available.

*/
ClockResult  
Clock_DetectCPUFrequency(
	 uint32_t  nCPU,
	 uint32_t  *nFreqHz
);


/* =========================================================================
**  Function : Clock_GetCPUFrequency
** =========================================================================*/
/*
  Returns the current clock speed in Hz of the given processor.

  This function returns the current CPU frequency.

  Parameters Description:

  @param nCPU             [in]  -- Specifies the CPU core/cluster of interest.
  @param pnFrequencyHz    [out] -- Pointer to fill in with the corresponding
                                    frequency in Hz.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERROR   -- Valid configuration is not available.

*/
ClockResult
Clock_GetCPUFrequency (
  uint32_t nCPU,
  uint32_t *pnFrequencyHz
);

/* =========================================================================
**  Function : Clock_GetCpuPerfLevelFrequency
** =========================================================================*/
/*
  Returns clock speed in Hz and required voltage in mV that corresponds to
  the given perfomance level.

  This function returns clock speed in Hz and required voltage in mV that
  corresponds to the given perfomance level.

  Parameters Description:

  @param nCPU              [in]  -- Specifies the CPU core of interest.
  @param nPerfLevel        [in]  -- Specifies the performance level of interest.
  @param pnFrequencyHz     [out] -- Pointer to fill in with the corresponding
                                    frequency in Hz.
  @param pnRequiredVoltage [out] -- Pointer to fill in with the corresponding
                                    required voltage in mV.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, frequency and voltage filled in.
  CLOCK_ERROR   -- Valid configuration is not available.

*/

ClockResult
Clock_GetCpuPerfLevelFrequency (
  uint32_t nCPU,
  uint32_t nPerfLevel,
  uint32_t *pnFrequencyHz,
  uint32_t *pnRequiredVoltage
);


/* =========================================================================
**  Function : Clock_SetCpuPerfLevel
** =========================================================================*/
/*
  Changes the processor clock speed and voltage.

  This function changes the performance level of the specified CPU to the
  specified frequency and the corresponding voltage level.

  Parameters Description:

  @param nCPU          [in]  -- Specifies the CPU core of interest.
  @param nPerfLevel    [in]  -- Specifies the desired performance level.
  @param pnFrequencyHz [out] -- Pointer to the actual CPU frequency in Hz.

  Return Value:

  @return
  CLOCK_SUCCESS -- The desired performance level has been successfully set.
  CLOCK_ERROR   -- Invalid parameters, or configuration.

*/

ClockResult
Clock_SetCpuPerfLevel (
  uint32_t nCPU,
  uint32_t nPerfLevel,
  uint32_t *pnFrequencyHz
);


/* =========================================================================
**  Function : Clock_GetCpuPerfLevel
** =========================================================================*/
/*
  Returns the current performance level of the given processor.

  This function retrieves the performance level of the specified CPU and
  returns that value to the caller.

  Parameters Description:

  @param nCPU        [in]  -- Specifies the CPU core of interest.
  @param pnPerfLevel [out] -- Pointer to the current performance level.

  Return Value:

  @return
  CLOCK_SUCCESS -- The current performance level value has been
                 successfully retrieved.
  CLOCK_ERROR   -- Unable to retrieve the current performance level
                 value.
*/

ClockResult
Clock_GetCpuPerfLevel (
  uint32_t nCPU,
  uint32_t *pnPerfLevel
);

/*=========================================================================
      Forward references
==========================================================================*/


 bool    Clock_CheckNameList
(
  const char  *szListName,
  const char  *szClockName
);

/*=========================================================================
      Stubbed out functions
==========================================================================*/

static inline ClockResult Clock_LoadNV( ClockDrvCtxt *pDrvCtxt){return CLOCK_SUCCESS;}
ClockResult Clock_ProcessorSleep(   ClockHandle        hClient,  ClockSleepModeType  eMode,  uint32_t  nFlags);
ClockResult Clock_ProcessorRestore(   ClockHandle        hClient,  ClockSleepModeType  eMode,  uint32_t  nFlags);

ClockResult Clock_ResetClock_STM(ClockHandle hClient, ClockIdType nClockId, ClockResetType  eReset);

#endif /* !__CLOCK_DRIVERIMAGE_H__ */


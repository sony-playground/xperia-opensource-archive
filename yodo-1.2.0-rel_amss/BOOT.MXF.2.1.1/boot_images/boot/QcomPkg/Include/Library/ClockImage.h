#ifndef __CLOCKIMAGE_H__
#define __CLOCKIMAGE_H__

/*
==============================================================================

FILE: ClockImage.h

DESCRIPTION:
  Clock driver Image Specific API's public interface.

==============================================================================

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/Library/ClockImage.h#1 $

==============================================================================
Copyright (c) 2020 QUALCOMM Technologies Incorporated.
All Rights Reserved.
QUALCOMM Proprietary/GTDR
==============================================================================

*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockDefs.h"
#if 0
#include "Drivers/ClockDxe/ClockBSP.h"
#include "stdbool.h"
#include "stdint.h"
#include "npa.h"

/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * Image BSP type.
 */
typedef struct
{
  npa_resource_state  nInitCPUState;  /**< Initial CPU state (0 to leave unchanged). */
  bool                bDisableDCS;    /**< Disable dynamic CPU frequency scaling. */
} ClockImageBSPType;


/**
 * CPU context type.
 */
typedef struct
{
  ClockIdType         ClockId;          /**< CPU clock identifier. */
  ClockNodeType      *pClock;           /**< CPU clock. */
  ClockMuxConfigType *pNASConfig;       /**< Pending NAS configuration. */
  uint32_t            nNASRequestCount; /**< Number of active NAS requests. */
  uint32_t            nDisableDCS;      /**< Mask of flags disabling dynamic CPU frequency scaling */
} ClockCPUCtxtType;


/**
 * Image context type.
 */
typedef struct
{
  ClockImageBSPType *pBSP;        /**< Image BSP data. */
  void              *pTargetCtxt; /**< Target-specific context. */
  ClockCPUCtxtType   CPUCtxt;     /**< CPU context. */
} ClockImageCtxtType;
#endif


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

  @param hClient     [in]  -- Handle to the client.
  @param nCPU        [in]  -- Specifies the CPU core/cluster of interest.
  @param pnPerfLevel [out] -- Pointer to fill in with the maximum
                              performance level.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERRORR   -- Valid configuration is not available.

*/

ClockResult
Clock_GetMaxPerfLevel (
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnPerfLevel
);


/* =========================================================================
**  Function : Clock_GetMinPerfLevel
** =========================================================================*/
/*
  Returns the minimum defined performance level for the processor clock.

  This function returns the minimum defined processor performance level.
  Each performance level corresponds to a unique clock/voltage pair.

  Parameters Description:

  @param hClient     [in]  -- Handle to the client.
  @param nCPU        [in]  -- Specifies the CPU core/cluster of interest.
  @param pnPerfLevel [out] -- Pointer to fill in with the minimum
                              performance level.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERRORR   -- Valid configuration is not available.

*/

ClockResult Clock_GetMinPerfLevel
(
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnPerfLevel
);


/* =========================================================================
**  Function : Clock_GetCPUFrequencyLevels
** =========================================================================*/
/*
  Returns the number of defined performance level for the specified CPU.

  This function returns the number of defined processor performance level.
  Each performance level corresponds to a unique clock/voltage pair.

  Parameters Description:

  @param hClient           [in]  -- Handle to the client.
  @param nCPU              [in]  -- Specifies the CPU core/cluster of interest.
  @param pnFrequencyLevels [out] -- Pointer to the number of frequency levels.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERRORR   -- Valid configuration is not available.

*/
ClockResult
Clock_GetCPUFrequencyLevels (
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnFrequencyLevels 
);


/* =========================================================================
**  Function : Clock_GetCPUFrequencyPlan
** =========================================================================*/
/*
  Dumps the frequency plan for the specified CPU in the Table passed as pointer.

  This function dumps the frequency plan in the table pointer passed for the specified CPU.

  Parameters Description:

  @param hClient           [in]  -- Handle to the client.
  @param nCPU              [in]  -- Specifies the CPU core/cluster of interest.
  @param pCPUFreqPlan      [in]  -- Pointer to the table storing the frequency plan of the corresponding CPU.
  @param nSize             [in]  -- Size of the Frequency plan table, expected value to be:
                                    (No. of Perf Levels * sizeof(ClockFreqPlanType))

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERRORR   -- Valid configuration is not available.

*/
ClockResult
Clock_GetCPUFrequencyPlan (
  ClockHandle         hClient,
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

  @param hClient          [in]  -- Handle to the client.
  @param nCPU             [in]  -- Specifies the CPU core/cluster of interest.
  @param nFrequencyHz     [in]  -- User requested frequency.
  @param pnResultFreqHz   [out] -- Pointer to the actual frequency achieved.(It is an optional parameter)

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERRORR   -- Valid configuration is not available.

*/
ClockResult
Clock_SetCPUFrequency (
  ClockHandle  hClient,
  uint32_t     nCPU,
  uint32_t     nFrequencyHz,
  uint32_t    *pnResultFreqHz
);

/* =========================================================================
**  Function : Clock_GetCPUFrequency
** =========================================================================*/
/*
  Returns the current clock speed in Hz of the given processor.

  This function returns the current CPU frequency.

  Parameters Description:

  @param hClient          [in]  -- Handle to the client.
  @param nCPU             [in]  -- Specifies the CPU core/cluster of interest.
  @param pnFrequencyHz    [out] -- Pointer to fill in with the corresponding
                                    frequency in Hz.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, performance level
                 filled in.
  CLOCK_ERRORR   -- Valid configuration is not available.

*/
ClockResult
Clock_GetCPUFrequency (
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnFrequencyHz
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

  @param hClient           [in]  -- Handle to the client.
  @param nCPU              [in]  -- Specifies the CPU core of interest.
  @param nPerfLevel        [in]  -- Specifies the performance level of interest.
  @param pnFrequencyHz     [out] -- Pointer to fill in with the corresponding
                                    frequency in Hz.
  @param pnRequiredVoltage [out] -- Pointer to fill in with the corresponding
                                    required voltage in mV.

  Return Value:

  @return
  CLOCK_SUCCESS -- Valid configuration is available, frequency and voltage filled in.
  CLOCK_ERRORR   -- Valid configuration is not available.

*/

ClockResult
Clock_GetCpuPerfLevelFrequency (
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t    nPerfLevel,
  uint32_t   *pnFrequencyHz,
  uint32_t   *pnRequiredVoltage
);


/* =========================================================================
**  Function : Clock_SetCpuPerfLevel
** =========================================================================*/
/*
  Changes the processor clock speed and voltage.

  This function changes the performance level of the specified CPU to the
  specified frequency and the corresponding voltage level.

  Parameters Description:

  @param hClient       [in]  -- Handle to the client.
  @param nCPU          [in]  -- Specifies the CPU core of interest.
  @param nPerfLevel    [in]  -- Specifies the desired performance level.
  @param pnFrequencyHz [out] -- Pointer to the actual CPU frequency in Hz.

  Return Value:

  @return
  CLOCK_SUCCESS -- The desired performance level has been successfully set.
  CLOCK_ERRORR   -- Invalid parameters, or configuration.

*/

ClockResult
Clock_SetCpuPerfLevel (
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t    nPerfLevel,
  uint32_t   *pnFrequencyHz
);


/* =========================================================================
**  Function : Clock_GetCpuPerfLevel
** =========================================================================*/
/*
  Returns the current performance level of the given processor.

  This function retrieves the performance level of the specified CPU and
  returns that value to the caller.

  Parameters Description:
 
  @param hClient     [in]  -- Handle to the client.
  @param nCPU        [in]  -- Specifies the CPU core of interest.
  @param pnPerfLevel [out] -- Pointer to the current performance level.

  Return Value:

  @return
  CLOCK_SUCCESS -- The current performance level value has been
                 successfully retrieved.
  CLOCK_ERRORR   -- Unable to retrieve the current performance level
                 value.
*/

ClockResult
Clock_GetCpuPerfLevel (
  ClockHandle hClient,
  uint32_t    nCPU,
  uint32_t   *pnPerfLevel
);

#endif /* __CLOCKIMAGE_H__ */

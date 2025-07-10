#ifndef __HALCLKAPCS_H__
#define __HALCLKAPCS_H__

/*
===========================================================================
*/
/**
  @file HALclkAPCS.h

  Header APCS-specific HAL functions.
*/
/*
  ====================================================================

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================


  ====================================================================
*/

/* ============================================================================
**    Include files
** ==========================================================================*/

#include "HALclkInternal.h"


/* ============================================================================
**    Definitions
** ==========================================================================*/

/*
 * EPSS definitions
 */
#define EPSS_LUT_MAX_ROWS  40


/* ============================================================================
**    Typedefs
** ==========================================================================*/

/**
 * Enumeration of CPU/Clusters.
 */
typedef enum
{
  HAL_CLK_APCS_CPU_CLUSTER0,
  HAL_CLK_APCS_CPU_CLUSTER1,
  HAL_CLK_APCS_CPU_L3,
  HAL_CLK_APCS_CPU_TOTAL,

  HAL_ENUM_32BITS(CLK_APCS_CPU)
} HAL_clk_APCSCPUType;


/**
 * Enumeration of CPU/Clusters.
 */
typedef enum
{
  HAL_CLK_APCS_CPU_CLUSTER0_C0,
  HAL_CLK_APCS_CPU_CLUSTER0_C1,
  HAL_CLK_APCS_CPU_CLUSTER0_C2,
  HAL_CLK_APCS_CPU_CLUSTER0_C3,
  HAL_CLK_APCS_CPU_CLUSTER1_C0,
  HAL_CLK_APCS_CPU_CLUSTER1_C1,
  HAL_CLK_APCS_CPU_CLUSTER1_C2,
  HAL_CLK_APCS_CPU_CLUSTER1_C3,
  HAL_CLK_APCS_CPU_CLUSTERL3,
  HAL_CLK_APCS_CPU_CORE_TOTAL
  
} HAL_clk_APCSCoreType;


/* ============================================================================
**    Functions
** ==========================================================================*/

/* ===========================================================================
**  Function : HAL_clk_EPSS_LUT_READ_FREQUENCY
**
** ======================================================================== */
/**
  Read the programmed data of the specified row of the EPSS Look-Up-Table
  Frequency values.

  @param eCore      [in]  -- CPU cluster to read.
  @param nRow       [in]  -- Row of the EPSS Look-Up-Table to read.
  @param nPllSource [out] -- Clock Source value read.
  @param nLVal      [out] -- PLL L-Value value read.

  @return
  TRUE  -- Configuration read successfully.
  FALSE -- Failed to read configuration for any reason.

  @dependencies
  None.
*/

boolean HAL_clk_EPSS_LUT_READ_FREQUENCY
(
  HAL_clk_APCSCPUType  eCore,
  uint32               nRow,
  uint32              *nClkSource,
  uint32              *nLVal
);



/* ===========================================================================
**  Function : HAL_clk_EPSS_READ_VCINDEX
**
** ======================================================================== */
/**

@param nCPU            [in]   -- CPU cluster to read.
@param nVcIndex        [out]  -- Active VC index.
@dependencies
None.
*/

boolean HAL_clk_EPSS_READ_VCINDEX
(
  HAL_clk_APCSCPUType  eCore,
  uint32               *nVcIndex
);

/* ===========================================================================
**  Function : HAL_clk_EPSS_LUT_READ_VOLTAGE
**
** ======================================================================== */
/**
Read the programed data of the specified row of the EPSS Look-Up-Table
Voltage values.

@param eCore            [in]  -- CPU cluster to read.
@param nRow             [in]  -- Row of the EPSS Look-Up-Table to read.
@param nOpenLoopVoltage [out] -- Open Loop Voltage value read.

@return
TRUE  -- Configuration read successfully.
FALSE -- Failed to read configuration for any reason.

@dependencies
None.
*/

boolean HAL_clk_EPSS_LUT_READ_VOLTAGE
(
HAL_clk_APCSCPUType  eCore,
uint32               nRow,
uint32              *nOpenLoopVoltage
);

/* ===========================================================================
**  Function : HAL_clk_EPSS_SET_DESIRED_PERF_LEVEL
**
** ======================================================================== */
/**
  Request for a specific performance state.

  @param eCore  [in] -- CPU cluster to affect.
  @param nIndex [in] -- Index into the EPSS LUT.

  @return
  TRUE  -- Operation succeeded.
  FALSE -- Operation failed for any reason.

  @dependencies
  EPSS must be programmed and enabled prior to this call.
*/

boolean HAL_clk_EPSS_SET_DESIRED_PERF_LEVEL
(
  HAL_clk_APCSCPUType eCore,
  uint32              nIndex
);


/* ===========================================================================
**  Function : HAL_clk_EPSS_SET_L3_PERF_LEVEL
**
** ======================================================================== */
/**
  Request for a performance state of L3 for specific CPU Core.

  @param eCore  [in] -- CPU cluster to affect.
  @param nIndex [in] -- Index into the EPSS LUT.

  @return
  TRUE  -- Operation succeeded.
  FALSE -- Operation failed for any reason.

  @dependencies
  EPSS must be programmed and enabled prior to this call.
*/

boolean HAL_clk_EPSS_SET_L3_PERF_LEVEL
(
  HAL_clk_APCSCoreType   eCore,
  uint32                 nIndex
);


/* ===========================================================================
**  HAL_clk_InitMiscRegisters
**
** ======================================================================== */

void HAL_clk_InitMiscRegisters
(
  void
);


/* ===========================================================================
**  HAL_clk_EnableDCDs
**
** ======================================================================== */

void HAL_clk_EnableDCDs
(
  void
);


#endif


/**
==============================================================================
  @file ClockSec.c

  Clock functions for XBL SecLib.

  Copyright (c) 2021 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential.

==============================================================================
*/

/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "HALclkHWIO.h"
#include "ClockBoot.h"

/*=========================================================================
                       MACRO DEFINITIONS
==========================================================================*/

/*=========================================================================
      TypeDefs
==========================================================================*/

/*=========================================================================
      Data
==========================================================================*/

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/* ============================================================================
**  Function : ClockSec_Init
** ============================================================================
*/
/*!
    This function initializes clock resources for SecLib

    @return
    CLOCK_SUCCESS -- Initialization succeeded.
    CLOCK_ERROR   -- Initialization failed.

*/
ClockResult ClockSec_Init
(
  void
)
{
  /*
   * Power domains required for XPU access prior to XBL Loader.
   * IPA GDSC is already enabled in Clock_Init()
   */
  HWIO_OUTF(GCC_APCS_TZ_IPA_SGDSCR, SW_OVERRIDE, 0);
  HWIO_OUTF(GCC_APCS_TZ_IPA_SGDSCR, RETAIN_FF_ENABLE, 1);

  HWIO_OUTF(GCC_UFS_PHY_GDSCR, SW_COLLAPSE, 0);
  while(!HWIO_INF(GCC_UFS_PHY_GDSCR, PWR_ON));
  HWIO_OUTF(GCC_APCS_TZ_UFS_MEM_PHY_SGDSCR, SW_OVERRIDE, 0);
  HWIO_OUTF(GCC_APCS_TZ_UFS_MEM_PHY_SGDSCR, RETAIN_FF_ENABLE, 1);

  /*
   * Clocks required for XPU access.
   */
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, QDSS_CFG_AHB_CLK_ENA, 1);
  HWIO_OUTF(GCC_QSPI_CNOC_PERIPH_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_QSPI_CORE_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(DPCC_DCNOC_SHRM_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_UFS_PHY_ICE_CORE_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_UFS_PHY_AHB_CBCR, CLK_ENABLE, 1);

  return CLOCK_SUCCESS;
}


/* ============================================================================
**  Function : ClockSec_ExitBoot
** ============================================================================
*/
/*!

    This function turns off clocks that are no longer needed after SecLib
    exits.

    @return
    CLOCK_SUCCESS -- Initialization succeeded.
    CLOCK_ERROR   -- Initialization failed.

*/
ClockResult ClockSec_ExitBoot
(
  void
)
{
  /*
   * Disable clocks that are no longer required.
   */
  HWIO_OUTF(GCC_IPA_2X_CBCR, CLK_ENABLE, 0);
  HWIO_OUTF(GCC_IPA_AHB_CBCR, CLK_ENABLE, 0);
  HWIO_OUTF(GCC_IPA_CBCR, CLK_ENABLE, 0);

  /*
   * Disable power domains that are no longer required.
   */
  HWIO_OUTF(GCC_IPA_GDSCR, SW_COLLAPSE, 1);

  return CLOCK_SUCCESS;
}

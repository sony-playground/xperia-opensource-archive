/**
==============================================================================
  @file ClockSec.c

  Clock functions for XBL SecLib.

  Copyright (c) 2020 QUALCOMM Technologies, Inc.  All Rights Reserved.  
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
   */
  HWIO_OUTF(GCC_IPA_GDSCR, SW_COLLAPSE, 0);
  while(!HWIO_INF(GCC_IPA_GDSCR, PWR_ON));
  HWIO_OUTF(GCC_APCS_TZ_IPA_SGDSCR, SW_OVERRIDE, 0);
  HWIO_OUTF(GCC_APCS_TZ_IPA_SGDSCR, RETAIN_FF_ENABLE, 1);

  /*
   * Clocks required for XPU access prior to XBL Loader.
   */
  /* TODO: Figure out clocks needed for LLCC access. */
  HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE, QDSS_CFG_AHB_CLK_ENA, 1);
  HWIO_OUTF(GCC_IPA_2X_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_IPA_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_IPA_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_IPCC_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_IPCC_CORE_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_PIMEM_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_PIMEM_AXI_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_QSPI_CNOC_PERIPH_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_QSPI_CORE_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(DPCC_SHRM_DCNOC_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_SDCC1_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_SDCC1_ICE_CORE_CBCR, CLK_ENABLE, 1);

  /* Enabling the GCC_UFS_PHY_AHB_CBCR, 
   * Since it is required in device programmer path to accessthe UFS region
   * In cold boot path this clk is enabled by PBL
   */
  HWIO_OUTF(GCC_UFS_PHY_AHB_CBCR , CLK_ENABLE, 1); 
  

  /*
   * To address DDR read path failure observed when switching fast SHUB
   * clock from Clock-Plan 6 on GCC_GPLL5 to Clock-Plan 5 on GCC_GPLL4,
   * HW fix was designed and introduced through ECO nr. QCTDD06083810.
   * However, this HW fix is disabled by default and legacy HW design
   * is in place. To enable the HW fix solution, the following bits need
   * to be programmed to 0x1:
   * GCC_SPARE1_REG[SPARE_BITS[0]] to enable fix for GCC_GPLL0
   * GCC_SPARE1_REG[SPARE_BITS[1]] to enable fix for GCC_GPLL1
   * GCC_SPARE1_REG[SPARE_BITS[4]] to enable fix for GCC_GPLL4
   * GCC_SPARE1_REG[SPARE_BITS[5]] to enable fix for GCC_GPLL5
   * Need to enable this in XBL Sec since AC admins are unwilling to
   * open RG and change to TZ only for security issues. This should
   * technically be done in AOP.
   */
  HWIO_OUTM(GCC_SPARE1_REG, 0x33, 0x33);

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

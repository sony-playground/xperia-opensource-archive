/**
==============================================================================

  @file ClockTarget.c

  Target specific clock management

  Copyright (c) 2021 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential.

==============================================================================
*/


/*==========================================================================
                               INCLUDE FILES
===========================================================================*/
#include "HALclkHWIO.h"
#include "ClockBSP.h"
#include "ClockBoot.h"


/* ============================================================================
**    Prototypes
** ==========================================================================*/

bool HAL_clk_xbl_ZondaEvoV2PLLConfigPLL
(
  HAL_clk_xbl_SourceDescType *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig,
  HAL_clk_xbl_SourceConfigMode eMode
);

/*=========================================================================
      Globals
==========================================================================*/

/*
 * We need to define aPllVoteAddrList for each target so that ClockBaseLib
 * knows where to vote for each master.
 */
uintptr_t aPllVoteAddrList[CLOCK_MASTER_MAX_SIZE] = {
  [CLOCK_MASTER_APCS] = HWIO_ADDR(GCC_APCS_PLL_BRANCH_ENA_VOTE),
  [CLOCK_MASTER_RPMH] = HWIO_ADDR(GCC_SPARE_PLL_BRANCH_ENA_VOTE),
  [CLOCK_MASTER_AOSS] = HWIO_ADDR(GCC_RPM_PLL_BRANCH_ENA_VOTE),
};

ClockResult Clock_InitImage(rail_voltage_level eBootCorner);

extern HAL_clk_xbl_SourceControlType HAL_clk_xbl_ZondaevoPLLControl;

HAL_clk_xbl_SourceControlType HAL_clk_xbl_ZondaevoV2PLLControl;


/* ============================================================================
**  Function : Clock_GetChipFamily
** ============================================================================
*/
/**
  Get Chip family.
*/
ChipInfoFamilyType Clock_GetChipFamily(void)
{
	return CHIPINFO_FAMILY_FILLMORE;
}


/* ============================================================================
**  Function : Clock_GetChipVersion
** ============================================================================
*/
/**
  Get Chip family.
*/
ChipInfoVersionType Clock_GetChipVersion(void)
{
  return CHIPINFO_VERSION(HWIO_INF(TCSR_SOC_HW_VERSION, MAJOR_VERSION),
                          HWIO_INF(TCSR_SOC_HW_VERSION, MINOR_VERSION));
}


/* ============================================================================
**  Function : Clock_InitTarget
** ============================================================================
*/
/**
  Performs target specific init.
*/
ClockResult Clock_InitTarget(rail_voltage_level eBootCorner)
{
  /*
   * Override Zonda control structure for V2 PLL workaround.
   */
  HAL_clk_xbl_ZondaevoV2PLLControl =
  (HAL_clk_xbl_SourceControlType) {
    .Enable         = HAL_clk_xbl_ZondaevoPLLControl.Enable,
    .IsEnabled      = HAL_clk_xbl_ZondaevoPLLControl.IsEnabled,
    .Config         = HAL_clk_xbl_ZondaevoPLLControl.Config,
    .ConfigPLL      = HAL_clk_xbl_ZondaEvoV2PLLConfigPLL,
    .EnableVote     = HAL_clk_xbl_ZondaevoPLLControl.EnableVote,
    .IsVoteEnabled  = HAL_clk_xbl_ZondaevoPLLControl.IsVoteEnabled,
    .SetCalConfig   = HAL_clk_xbl_ZondaevoPLLControl.SetCalConfig,
    .SetRegSettings = HAL_clk_xbl_ZondaevoPLLControl.SetRegSettings,
  };

  /*
   * Set Zonda PLL overrides for V2 as per Kryo HPG
   * Need to follow up with HW about why this is needed.
  */
  HWIO_OUT(APSS_CC_SILVER_PLL_SW_OVRD, 1);
  HWIO_OUT(APSS_CC_L3_PLL_SW_OVRD , 1);
  HWIO_OUT(APSS_CC_GOLD_PLL_SW_OVRD , 1);
  HWIO_OUT(APSS_CC_GOLD_PLUS_PLL_SW_OVRD , 1);

  return Clock_InitImage(eBootCorner);
}

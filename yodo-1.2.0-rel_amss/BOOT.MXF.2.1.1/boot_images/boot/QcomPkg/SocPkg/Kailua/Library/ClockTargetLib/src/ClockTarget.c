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

/* ============================================================================
**  Function : Clock_GetChipFamily
** ============================================================================
*/
/**
  Get Chip family.
*/
ChipInfoFamilyType Clock_GetChipFamily(void)
{
	return CHIPINFO_FAMILY_KAILUA;
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
   * Set Zonda PLL overrides for V2 as per Kryo HPG.
   * These requirements were snuck in by HW for Waipio without
   * any involvement from SW. Kailua inherited this mess.
   * Must work with HW to standardize design of the PLL control.
   */
  HWIO_OUT(APSS_CC_SILVER_PLL_SW_OVRD, 1);
  HWIO_OUT(APSS_CC_L3_PLL_SW_OVRD , 1);
  HWIO_OUT(APSS_CC_GOLD_PLL_SW_OVRD , 1);
  HWIO_OUT(APSS_CC_GOLD_PLUS_PLL_SW_OVRD , 1);

  return Clock_InitImage(eBootCorner);
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

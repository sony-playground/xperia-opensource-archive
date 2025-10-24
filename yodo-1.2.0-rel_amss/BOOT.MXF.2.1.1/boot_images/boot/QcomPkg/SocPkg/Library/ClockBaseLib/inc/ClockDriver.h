#ifndef CLOCKDRIVER_H
#define CLOCKDRIVER_H

/**
==============================================================================

  @file ClockDriver.h

  Clock driver functions for PLL and clock management

  Copyright (c) 2016-2019 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential.

==============================================================================
*/

#include <stdbool.h>
#include <HALcomdef.h>
#include "ClockBoot.h"
#include "ClockBSP.h"
#include "ChipInfoDefs.h"

/*=========================================================================
      Definitions
==========================================================================*/

/*=========================================================================
      Type Definitions
==========================================================================*/

/**
 * Clock config setting CP data for sharing with AOP
 */
typedef struct
{
  uint8 nSHUB;        // System HUB
  uint8 nSNOC;        // System NOC
  uint8 nCNOC;        // Config NOC
  uint8 nCDSP;        // CDSP NOC
  uint8 nCE;          // Crypto Engine
  uint8 nIPA;         // IPA
  uint8 nDDR;         // DDR
  uint8 nReserved;   // Reserved
} ClockCfgCPType;


/*
 * ClockIdCategoryType
 *
 * Clock ID categories.
 */
typedef enum
{
  CLOCK_ID_CATEGORY_NONE = 0,
  CLOCK_ID_CATEGORY_CLOCK,
  CLOCK_ID_CATEGORY_POWERDOMAIN,
  CLOCK_ID_CATEGORY_SOURCE,
  CLOCK_ID_CATEGORY_DEBUGMUX,
  CLOCK_ID_CATEGORY_DIVIDER,
  CLOCK_ID_CATEGORY_FUNCGROUP,

  CLOCK_ID_CATEGORY_TOTAL,
} ClockIdCategoryType;


/*
 * Clock driver context
 */
typedef struct
{
  bool               bInitialized;
  ClockHandle        nHandle;
  rail_voltage_level eBootCorner;
} ClockDriverCtxtType;


/* =========================================================================
**  Function : Clock_ConfigurePLL
** =========================================================================*/
/**
  Configures a PLL but do not enable it.  If the PLL is already enabled or
  set to FSM mode, this will fail.

  @param pSource -  [IN] PLL configuration structure
  @param pConfig -  [IN] PLL frequency configuration
  @return
  TRUE -- Configuration was successful
  FALSE -- The PLL was already enabled or in FSM mode.

*/
bool Clock_ConfigurePLL(ClockSourceNodeType *pSource, const ClockSourceFreqConfigType *pConfig);

/* =========================================================================
**  Function : Clock_EnableClockInternal
** =========================================================================*/
bool Clock_EnableClockInternal (uintptr_t nCBCRAddr);

/* =========================================================================
**  Function : Clock_DisableClockInternal
** =========================================================================*/
bool Clock_DisableClockInternal (uintptr_t nCBCRAddr);

/* =========================================================================
**  Function : Clock_EnableBootClocks
** =========================================================================*/
/**
  Enable boot clocks and GDSCs.
*/
void Clock_EnableBootClocks(void);

/* ===========================================================================
**  Clock_EnablePowerDomainInternal
** ======================================================================== */
bool Clock_EnablePowerDomainInternal (uintptr_t nGDSCRAddr);

/* ===========================================================================
**  Clock_DisablePowerDomainInternal
** ======================================================================== */
bool Clock_DisablePowerDomainInternal (uintptr_t nGDSCRAddr);

/* =========================================================================
**  Function : Clock_GetDomainFreqConfig
** =========================================================================*/
/**
  Get configured domain frequency.
*/
uint32 Clock_GetDomainFrequency (ClockDomainNodeType *pDomain);

/* =========================================================================
**  Function : Clock_SetDomainFreq
** =========================================================================*/
/**
  Set domain frequency to nMinFreqKHz.
*/
bool Clock_SetDomainFreq(ClockDomainNodeType *pDomain, uint32_t nFreqKHz, ClockFrequencyType eMatch);

/* =========================================================================
**  Function : Clock_SetDomainFMax
** =========================================================================*/
/**
  Set domain frequency to the max supported in eCorner.
*/
bool Clock_SetDomainFMax (ClockDomainNodeType *pDomain, rail_voltage_level eCorner);

/* =========================================================================
**  Function : Clock_SetDomainBootFMax
** =========================================================================*/
/**
  Set domain frequency to the max supported by the default boot corner.
*/
void Clock_SetDomainBootFMax (ClockDomainNodeType *pDomain);

/* =========================================================================
**  Function : Clock_GetGroupFrequency
** =========================================================================*/
/**
  Get the active frequency of a clock group.
*/
ClockResult Clock_GetGroupFrequency(ClockGroupType *pClockGroup, uint32_t *pnFrequencyHz);

/* ============================================================================
**  Function : Clock_InitImage
** ============================================================================
*/
/**
  Performs Image specific init.
*/
ClockResult Clock_InitTarget(rail_voltage_level eBootCorner);

/* ============================================================================
**  Function : Clock_GetChipFamily
** ============================================================================
*/
/**
  Get Chip family.
*/
ChipInfoFamilyType Clock_GetChipFamily(void);

/* ============================================================================
**  Function : Clock_GetChipVersion
** ============================================================================
*/
/**
  Get Chip family.
*/
ChipInfoVersionType Clock_GetChipVersion(void);

#endif /* CLOCKDRIVER_H */

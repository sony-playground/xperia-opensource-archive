#ifndef __CLOCK_TARGET_H__
#define __CLOCK_TARGET_H__

/*
================================================================================
*/
/**
  @file clock_target.h
  @brief Public interface include file for accessing the target-specific
         definitions of the clock driver.
*/
/*
  ==============================================================================

  Copyright (c) 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

  ==============================================================================

  $Header: //components/rel/aop.ho/5.0/aop_proc/core/api/systemdrivers/clock/kailua/clock_target.h#3 $
  $DateTime: 2022/04/08 11:44:05 $
  $Author: pwbldsvc $

  ==============================================================================
*/

/*==============================================================================
  Includes
==============================================================================*/

#include <stdint.h>


/*==============================================================================
  Macros
==============================================================================*/

#define CLOCK_SMEM_VERSION    2


/*==============================================================================
  Type definitions
==============================================================================*/

/**
 * Clock config setting data from bootloader
 */
typedef struct
{
  uint8_t nSHUB;        // System Hub
  uint8_t nSNOC;        // System NOC
  uint8_t nCNOC;        // Config NOC
  uint8_t nCDSP;        // CDSP NOC
  uint8_t nCE;          // Crypto Engine
  uint8_t nIPA;         // IPA
  uint8_t nDDR;         // DDR
  uint8_t nReserved;    // Reserved

} ClockCfgCPType;


/*==============================================================================
  Prototypes
==============================================================================*/

/* =============================================================================
**  Function : Clock_PostAWSMInit
** ===========================================================================*/
/**
  This function is invoked by sleep driver after AWSM feature is enabled. It
  disables the SW CLK_ENA for all the clocks controlled by AWSM.

  @param
  None.

  @return
  CLOCK_SUCCESS -- Always

  @dependencies
  AWSM feature should be enabled prior to this for stability.
*/

int32_t Clock_PostAWSMInit
(
  void
);

#endif /* __CLOCK_TARGET_H__ */

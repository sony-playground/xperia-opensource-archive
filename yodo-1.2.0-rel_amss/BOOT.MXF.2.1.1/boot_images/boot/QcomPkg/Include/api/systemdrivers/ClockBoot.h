#ifndef __CLOCKBOOT_H__
#define __CLOCKBOOT_H__

/** @file ClockBoot.h

  This file contains the external interface definitions for the clock regime device driver.
  This driver is support for the Krait Second Primary Boot Loader.

  Copyright (c) 2016-2017 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential.

=============================================================================*/

/*=========================================================================
      Includes
==========================================================================*/

#include "ClockDefs.h"


/*=========================================================================
      Interface Declarations
==========================================================================*/

/* ============================================================================
**  Function : Clock_Init
** ============================================================================
*/
/*!

    This function turns on the required clocks and configures
    CPU and NOC boot performance level.

    @return
    CLOCK_SUCCESS -- Initialization was successful.
    CLOCK_ERROR   -- Initialization failed.

   @dependencies
    None.

*/
ClockResult Clock_Init(void);


/* ============================================================================
**  Function : Clock_ExitBoot
** ============================================================================
*/
/*!

    This function turns off clocks that were used during boot, but are not
    needed after boot.  This should be called at the end of boot.

    @return
    CLOCK_SUCCESS -- Initialization was successful.
    CLOCK_ERROR   -- Initialization failed.

   @dependencies
    Call this last in the boot sequence.

*/
ClockResult Clock_ExitBoot(void);


/* ========================================================================
**  Function : Clock_SetBIMCSpeed
** ======================================================================*/
/*
    Description: API for setting DDR frequency

    @param nFreqKHz - DDR frequency in KHz

    @return TRUE on success.

    @dependencies
    None.

    @sa None
*/
boolean Clock_SetBIMCSpeed(uint32 nFreqKHz );


/* ============================================================================
**  Function : Clock_InitRPM
** ============================================================================
*/
/*!

    This function does any initialization before RPM launches.  SMEM is now
    usable.

    @return
    CLOCK_SUCCESS -- Initialization was successful.
    CLOCK_ERROR   -- Initialization failed.

   @dependencies
    Requires SMEM

*/
ClockResult Clock_InitRPM(void);


/* ============================================================================
 **  Function : ClockSec_Init
 ** ============================================================================
 */
/*!
  Perform initial clock configuration required by SecLib

  @return - CLOCK_SUCCESS - if successful

  @dependencies
  None.

  @sa None
 */
ClockResult ClockSec_Init(void);


/* ============================================================================
 **  Function : ClockSec_ExitBoot
 ** ============================================================================
 */
/*!
  Clean up clock configuration after SecLib is finished

  @return - CLOCK_SUCCESS - if successful

  @dependencies
  None.

  @sa None
 */
ClockResult ClockSec_ExitBoot(void);


#endif  /* __CLOCKBOOT_H__ */

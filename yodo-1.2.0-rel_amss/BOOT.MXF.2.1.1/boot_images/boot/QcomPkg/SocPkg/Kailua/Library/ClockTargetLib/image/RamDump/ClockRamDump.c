/**
==============================================================================
  @file ClockRamDump.c

  Clock functions for the XBL RAM Dump image, which primarily supports a 
  video splash screen.

==============================================================================
            Copyright (c) 2021 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "HALclkHWIO.h"
#include "ClockDriver.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/* =========================================================================
**  Function : Clock_InitImage
** =========================================================================*/
/**
  This function initializes the MDSS clock dependancies.

  @dependencies
  None.
*/
ClockResult Clock_InitImage
(
  rail_voltage_level eBootCorner
)
{
  /* Be sure that DISP_CC is available */
  HWIO_OUTF(GCC_DISP_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_MMNOC_AT_CBCR, CLK_ENABLE, 1);

  return CLOCK_SUCCESS;
}

/* =========================================================================
**  Function : Clock_GetGroupFrequency
** =========================================================================*/
/**
  Get the active frequency of a clock group.
*/
ClockResult Clock_GetGroupFrequency
(
  ClockGroupType *pClockGroup,
  uint32_t    *pnFrequencyHz
)
{
   return CLOCK_ERROR_NOT_SUPPORTED;
}

/* =========================================================================
**  Function : Clock_InitRPM
** =========================================================================*/
/**
   Stub API to satisfy boot interface requirements.
*/
ClockResult Clock_InitRPM( void )
{
  return CLOCK_SUCCESS;
}

/* =========================================================================
**  Function : Clock_ExitBoot
** =========================================================================*/
/**
  Stub API to satisfy boot interface requirements.
*/
ClockResult Clock_ExitBoot(void)
{
  return CLOCK_SUCCESS;
}
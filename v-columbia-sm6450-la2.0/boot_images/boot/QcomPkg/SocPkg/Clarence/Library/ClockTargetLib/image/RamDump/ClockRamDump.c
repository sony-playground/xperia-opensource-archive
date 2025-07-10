/**
==============================================================================
  @file ClockRamDump.c

  Clock functions for the XBL RAM Dump image, which primarily supports a 
  video splash screen.

==============================================================================
            Copyright (c) 2016-2019 QUALCOMM Technologies Incorporated.
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

/* ============================================================================
**  Function : Clock_OverrideMMCXArc
** ============================================================================
  This function overrides the MMCX ARC state to allow Display clocks to be turned on.
  Requirements : MMCX needs to be enabled by direct PMIC writes in boot for this override to be used.
*/
static void Clock_OverrideMMCXArc
(
  boolean ena
)
{
  if(ena)
  {
    HWIO_OUTI(RPMH_ARC_SW_OVERRIDE_PWR_CTRL2_MASK_RMm, 8, 0xffffffff);
    HWIO_OUTI(RPMH_ARC_SW_OVERRIDE_PWR_CTRL_MASK_RMm, 8, 0xffffffff);
  }
  else
  {
    HWIO_OUTI(RPMH_ARC_SW_OVERRIDE_PWR_CTRL_MASK_RMm, 8, 0x00000000);
    HWIO_OUTI(RPMH_ARC_SW_OVERRIDE_PWR_CTRL2_MASK_RMm, 8, 0x00000000);
  }
}


/* =========================================================================
**  Function : Clock_InitSources
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

  // Clock_OverrideMMCXArc( TRUE );
  /* Be sure that DISP_CC is available */
  HWIO_OUTF(GCC_DISP_AHB_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_MMNOC_HF_AT_CBCR, CLK_ENABLE, 1);
  HWIO_OUTF(GCC_MMNOC_SF_AT_CBCR, CLK_ENABLE, 1);

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
/*
==============================================================================

FILE:         ClockTargetBSP.c

DESCRIPTION:
  This file contains the Target Specific functionality (and all misc api's).
  
==============================================================================

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/ClockLib/ClockTarget.c#1 $

==============================================================================
            Copyright (c) 2021, 2022 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/


/*=========================================================================
      Include Files
==========================================================================*/
#include "ClockApps.h"
#include "Drivers/ClockDxe/ClockDriverImage.h"
#include "HALhwio.h"
#include "../HALclkLib/HALclkHWIO.h"
#include "Library/HALclkGeneric.h"
#include "busywait.h"

/*=========================================================================
      Macros
==========================================================================*/



/*=========================================================================
      Externals
==========================================================================*/
extern ClockAppsBSPType ClockAppsBSP;
extern ClockAppsCtxtType ClockAppsCtxt;

/*=========================================================================
      Prototypes
==========================================================================*/


/*=========================================================================
      Type Definitions
==========================================================================*/



/*=========================================================================
      Data Declarations
==========================================================================*/

/* =========================================================================
**  Function : Clock_InitTarget
** =========================================================================*/
/*
  See ClockApps.h
*/
ClockResult Clock_InitTarget
(
  void
)
{
  ClockResult eResult = CLOCK_SUCCESS;

  ULogFront_RealTimeInit (&(ClockAppsCtxt.hClockAppsULog),
                          "Clock_Apps_Log", ClockAppsCtxt.nLogSize,
                          ULOG_MEMORY_LOCAL, ULOG_LOCK_OS);
  ULogCore_HeaderSet (ClockAppsCtxt.hClockAppsULog,
                      "Content-Type: text/tagged-log-1.0;");

  eResult = Clock_InitImage();
  if (eResult != CLOCK_SUCCESS)
  {
    return CLOCK_ERROR;
  }

  return CLOCK_SUCCESS;

} /* END Clock_InitTarget */


/* =========================================================================
**  Function : Clock_DeInitTarget
** =========================================================================*/
/*
  See ClockApps.h
*/
/**
  De-Initialization and cleanup of the target specific portion of the clock driver.
  It is specific to the image and chipset we are running on.

  @return
  CLOCK_SUCCESS - Sucessfully Initialize the target specific portion of the clock driver.

  @dependencies
  None.
*/

ClockResult Clock_DeInitTarget
(
  void
)
{
  /*-----------------------------------------------------------------------*/
  /* Clear out driver context data.                                        */
  /*-----------------------------------------------------------------------*/
  memset(&ClockAppsBSP,  0x0, sizeof(ClockAppsBSPType));
  memset(&ClockAppsCtxt, 0x0, sizeof(ClockAppsCtxtType));

  return CLOCK_SUCCESS;

} /* END Clock_DeInitTarget */


/* =========================================================================
**  Function : Clock_GetBootCorner
** =========================================================================*/
/**
  Returns the configured boot voltage corner for the given rail stored in a
  BSP data structure.

  @param szRailName  [in] -- Name of the rail.
  @param eBootCorner [out] -- The configured boot corner to return.

  @return
  CLOCK_SUCCESS if the value was found and retrieved, CLOCK_ERROR otherwise.

  @dependencies
  None.
*/

ClockResult Clock_GetBootCorner
(
  const char         *szRailName,
  rail_voltage_level *eBootCorner
)
{
  ClockResult              eResult;
  ClockRailConfigType     *ClockRailConfig;
  uint32_t                 nIndex;

  if (!szRailName || !eBootCorner)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  /*-----------------------------------------------------------------------*/
  /* Get the boot voltage corner table.                                    */
  /*-----------------------------------------------------------------------*/

  eResult = Clock_GetPropertyHandle("ClockRailConfig", (void**)(&ClockRailConfig));

  if (eResult == CLOCK_SUCCESS)
  {
    for (nIndex = 0; ClockRailConfig[nIndex].sName != NULL; nIndex++)
    {
      if (strcmp(ClockRailConfig[nIndex].sName, szRailName) == 0)
      {
        *eBootCorner = ClockRailConfig[nIndex].eBootCorner;
        return CLOCK_SUCCESS;
      }
    }
    *eBootCorner = RAIL_VOLTAGE_LEVEL_OFF;
    return CLOCK_ERROR_NOT_FOUND;
  }

  return eResult;

} /* END Clock_GetBootCorner */


void HAL_clk_InitMiscRegisters()
{  
}

void HAL_clk_EnableDCDs()
{
  //HWIO_CAM_CC_CAMNOC_AXI_DCD_DIV_DCDR_OUT(1);
  HWIO_VCODEC_VIDEO_CC_MVS0C_DIV_DCDR_OUT(1);
  HWIO_VCODEC_VIDEO_CC_MVS1C_DIV_DCDR_OUT(1);
} /* HAL_clk_EnableDCDs */

/* ===========================================================================
**  HAL_clk_GPUGxPowerDomainEnable
** ======================================================================== */
/*
 * GPU CC HPG, 9.3.1 VDD GX power on sequence
 */
void HAL_clk_GPUGxPowerDomainEnable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uintnt nAddr;
  uint32_t nVal, nMask;

  nAddr = pmPowerDomainDesc->VoterRegister.nAddr;
  if(nAddr)
  {
    nMask = pmPowerDomainDesc->VoterRegister.nMask;
  }
  else
  {
    nAddr = pmPowerDomainDesc->nGDSCRAddr;
    nMask = HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
  }

  /*
   * Sanity check
   */
  if (nAddr == 0)
  {
    return;
  }

  /*
   * Assert CSR SW Reset (This is necessary to flush out the demet cells
   * in GFX PMIC domain)
   */
  HWIO_OUT(GPUCC_GPU_CC_GX_BCR, 1);
  HWIO_OUT(GPUCC_GPU_CC_ACD_BCR, 1);
  HWIO_OUT(GPUCC_GPU_CC_ACD_MISC, 1);

  /*
   * Make sure that above BLK_ARES is kept asserted for at least 1us before
   * being de-asserted (This is necessary as in HW there are 3 demet cells __on
   * CXO clk to synchronize the BLK_ARES
   */
  busywait(1);

  /*
   * De-assert CSR SW Reset
   */
  HWIO_OUT(GPUCC_GPU_CC_GX_BCR, 0);
  HWIO_OUT(GPUCC_GPU_CC_ACD_BCR, 0);
  HWIO_OUT(GPUCC_GPU_CC_ACD_MISC, 0);

  /*
   * Assert below CSR to reset AON logic on PMIC rail
   */
  HWIO_OUTF(GPUCC_GPU_CC_GX_DOMAIN_MISC3, GPU_GX_RAIL_RESET, 1);
  /*
   * Keep above reset asserted for at least 1us before de-asserting it.
   */
  busywait(1);
  /*
   * De-assert the CSR
   */
  HWIO_OUTF(GPUCC_GPU_CC_GX_DOMAIN_MISC3, GPU_GX_RAIL_RESET, 0);
  /*
   * Clear below register to release clamp (default state is clamped)
   */
  HWIO_OUTF(GPUCC_GPU_CC_GX_DOMAIN_MISC3, GPU_GX_RAIL_CLAMP_IO, 0);

  /*
   * Power on GPU HM (default state is powered off)
   */
  nVal  = inpdw(nAddr);
  /*
   * Clear the SW PD collapse bit
   */
  nVal &= ~nMask;
  outpdw(nAddr, nVal);

  /*
   * Wait for PD ON
   */
  while (!(inpdw(pmPowerDomainDesc->nGDSCRAddr) & HAL_CLK_GDSCR_PWR_ON_FMSK));

} /* END HAL_clk_GPUGxPowerDomainEnable */


/* ===========================================================================
**  HAL_clk_GPUGxPowerDomainDisable
** ======================================================================== */

void HAL_clk_GPUGxPowerDomainDisable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uintnt nAddr;
  uint32_t nVal, nMask;

  nAddr = pmPowerDomainDesc->VoterRegister.nAddr;
  if(nAddr)
  {
    nMask = pmPowerDomainDesc->VoterRegister.nMask;
  }
  else
  {
    nAddr = pmPowerDomainDesc->nGDSCRAddr;
    nMask = HAL_CLK_GDSCR_SW_COLLAPSE_FMSK;
  }

  /*
   * Sanity check
   */
  if (nAddr == 0)
  {
    return;
  }

  /*
   * Set the SW PD collapse bit
   */
  nVal  = inpdw(nAddr);
  nVal |= nMask;
  outpdw(nAddr, nVal);

  /*
   * Wait for PD OFF
   */
  while ((inpdw(pmPowerDomainDesc->nGDSCRAddr) & HAL_CLK_GDSCR_PWR_ON_FMSK));

  /*
   * Assert below register to release clamp (default state is clamped)
   */
  HWIO_OUTF(GPUCC_GPU_CC_GX_DOMAIN_MISC3, GPU_GX_RAIL_CLAMP_IO, 1);


} /* END HAL_clk_GPUGxPowerDomainDisable */

HAL_clk_PowerDomainControlType HAL_clk_GPUGxPowerDomainControl =
{
   .Enable     = HAL_clk_GPUGxPowerDomainEnable,
   .Disable    = HAL_clk_GPUGxPowerDomainDisable,
   .IsEnabled  = HAL_clk_GenericPowerDomainIsEnabled,
   .IsOn       = HAL_clk_GenericPowerDomainIsOn,
   .EnableHW   = HAL_clk_GenericPowerDomainEnableHW,
   .DisableHW  = HAL_clk_GenericPowerDomainDisableHW
};

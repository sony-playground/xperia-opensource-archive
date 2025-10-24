/*
==============================================================================

FILE:         HALclkPongoEvoPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Pongo PLL control.
  These PLLs are of the Pongo PLL variety.

==============================================================================

                             Edit History

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/ClockBaseLib/hal/hw/HALclkPongoEvoPLL.c#1 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
06/07/14   sr      Created

==============================================================================
    Copyright (c) 2016 - 2019 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "HALhwio.h"
#include "HALclkXBLInternal.h"
#include "HALclkGenericPLL.h"
#include "HALclkPongoEvoPLL.h"
#include "busywait.h"
#include "stdbool.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/


/* ============================================================================
**    Definitions
** ==========================================================================*/

/*
 * HAL_CLK_PLL_MODE_*
 *
 * Definitions for configuring the PLLn_MODE register.
 */
#define HAL_CLK_PLL_MODE_ACTIVE    \
  (HWIO_FMSK(PLL_MODE, LOCK_DET) | \
   HWIO_FMSK(PLL_MODE, RESET_N)  | \
   HWIO_FMSK(PLL_MODE, OUTCTRL))

/*
 * Definitions for configuring the PLL in FSM Mode
 */
#define HAL_CLK_PLL_BIAS_COUNT_VAL   (0x6 << HWIO_SHFT(PLL_MODE, BIAS_COUNT))
#define HAL_CLK_PLL_LOCK_COUNT_VAL   (0x0 << HWIO_SHFT(PLL_MODE, LOCK_COUNT))

/*
 * HAL_CLK_PLL_INIT_TIME_US
 *
 * Init time in microseconds after de-asserting PLL reset (normal mode).
 */
#define HAL_CLK_PLL_INIT_TIME_US 5

/*
 * HAL_CLK_PLL_WARMUP_TIME_US
 *
 * Warm-up time in microseconds after turning on the PLL.
 */
#define HAL_CLK_PLL_WARMUP_TIME_US 50

/*
 * HAL_CLK_LOCK_TIMEOUT_US
 *
 * Timeout in usec for PLL_LOCK_DET to get set.
 * For Pongo, this is 50us worst-case lock time.  However, when
 * the PLL is sourced from RO, it may take longer for initial lock, 
 * up to 1.5 ms.
 */
#define HAL_CLK_LOCK_TIMEOUT_US 1500


/* ============================================================================
**    Functions Prototypes
** ==========================================================================*/

/*
 * Source control functions.  These can be used if some of the control
 * needs to be overridden by a specific PLL.
 */
bool HAL_clk_xbl_PongoEvoPLLEnable           ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceDisableModeType eMode, void *pData );
bool HAL_clk_xbl_PongoEvoPLLIsEnabled        ( HAL_clk_xbl_SourceDescType *pSource );
void HAL_clk_xbl_PongoEvoPLLConfig           ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceConfigType eConfig );
bool HAL_clk_xbl_PongoEvoPLLConfigPLL        ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig, HAL_clk_xbl_SourceConfigMode eMode );
bool HAL_clk_xbl_PongoEvoPLLSetCalConfig     ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig );
void HAL_clk_xbl_PongoEvoPLLSetRegSettings   ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_SourceRegSettingsType *pmSettings );


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_xbl_PongoEvoPLLControl
 *
 * Control function array for the Pongo PLLs.
 */
HAL_clk_xbl_SourceControlType HAL_clk_xbl_PongoevoPLLControl =
{
  .Enable           = HAL_clk_xbl_PongoEvoPLLEnable,
  .IsEnabled        = HAL_clk_xbl_PongoEvoPLLIsEnabled,
  .Config           = HAL_clk_xbl_PongoEvoPLLConfig,
  .ConfigPLL        = HAL_clk_xbl_PongoEvoPLLConfigPLL,
  .SetCalConfig     = HAL_clk_xbl_PongoEvoPLLSetCalConfig,
  .SetRegSettings   = HAL_clk_xbl_PongoEvoPLLSetRegSettings,
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/


/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLPostDivToHW
**
** ======================================================================== */

uint32_t HAL_clk_xbl_PongoEvoPLLPostDivToHW (uint32_t nDivider)
{
  if (nDivider)
  {
    nDivider--;
  }

  return nDivider;

} /* END HAL_clk_xbl_PongoEvoPLLPostDivToHW */


/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLPostDivFromHW
**
** ======================================================================== */

uint32_t HAL_clk_xbl_PongoEvoPLLPostDivFromHW (uint32_t nDivider)
{
  return nDivider + 1;

} /* END HAL_clk_xbl_PongoEvoPLLPostDivFromHW */



/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLEnable
**
** ======================================================================== */

bool HAL_clk_xbl_PongoEvoPLLEnable
(
  HAL_clk_xbl_SourceDescType        *pSource,
  HAL_clk_xbl_SourceDisableModeType  eMode,
  void                          *pData
)
{
  uint32_t nModeVal;
  bool     bResult;

  /*
   * Check if PLL is already enabled and return
   */
  if (HAL_clk_xbl_PongoEvoPLLIsEnabled(pSource))
  {
    return TRUE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Set the PLL opmode to run mode.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_RUN);

  /*
   * Wait for the PLL to lock within the timeout period.
   */
  bResult =
    HAL_clk_xbl_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HWIO_FMSK(PLL_MODE, LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the lock detect failed.
   */
  if (!bResult)
  {
    return FALSE;
  }

  /*
   * Request for second calibration.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, REQUESTS_CAL, 1);
  busywait(1);
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, REQUESTS_CAL, 0);
  
  /*
   * Put the PLL in active mode
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  /*
   * Switch from XO over to the PLL reference clock.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, CLOCK_SELECT);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  return TRUE;

} /* END HAL_clk_xbl_PongoEvoPLLEnable */


/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLIsEnabled
**
** ======================================================================== */

bool HAL_clk_xbl_PongoEvoPLLIsEnabled
(
  HAL_clk_xbl_SourceDescType *pSource
)
{
  uint32_t nModeVal;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Check whether the PLL is enabled.
   */
  return ((nModeVal & HAL_CLK_PLL_MODE_ACTIVE) == HAL_CLK_PLL_MODE_ACTIVE);

} /* END HAL_clk_xbl_PongoEvoPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLConfig
**
** ======================================================================== */

void HAL_clk_xbl_PongoEvoPLLConfig
(
  HAL_clk_xbl_SourceDescType   *pSource,
  HAL_clk_xbl_SourceConfigType  eConfig
)
{
  /*
   * Take action.
   */
  switch (eConfig)
  {
    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_EVEN_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_MAIN_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, OUT_MAIN_HW_CTL, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_HW_CTL_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, OUT_EVEN_HW_CTL, 1);
      break;

    default:
      break;
  }

} /* END HAL_clk_xbl_PongoEvoPLLConfig */


/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLConfigPLLNormal
**
** ======================================================================== */

bool HAL_clk_xbl_PongoEvoPLLConfigPLLNormal
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig
)
{
  uint32_t nModeVal;
  uint32_t nUserVal;
  bool  bResult = FALSE;

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Program L/Alpha values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pSource, pConfig->nL);
  

  /* 
   * Enable the PLL.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, 1);
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, RESET_N, 1);
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, CAL_XO_PRESENT, 1);

  /*
   * Wait for the PLL to lock within the timeout period.
   */
  bResult =
    HAL_clk_xbl_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HWIO_FMSK(PLL_MODE, LOCK_DET),
      HAL_CLK_LOCK_TIMEOUT_US);

  /*
   * Return immediately if the lock detect failed.
   */
  if (!bResult)
  {
    return FALSE;
  }
 
  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal  =  HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pSource);
  nUserVal &= ~HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_MAIN);
  nUserVal &= ~HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_EVEN);

  /*
   * Program the post-div value.
   */
  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POST_DIV_RATIO_MAIN,
    HAL_clk_xbl_PongoEvoPLLPostDivToHW(pConfig->PostDivs.Pongoevo.nMain));

  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POST_DIV_RATIO_EVEN,
    HAL_clk_xbl_PongoEvoPLLPostDivToHW(pConfig->PostDivs.Pongoevo.nEven));

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pSource, nUserVal);

  return TRUE;

} /* END HAL_clk_xbl_PongoEvoPLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLConfigPLL
**
** ======================================================================== */

bool HAL_clk_xbl_PongoEvoPLLConfigPLL
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig,
  HAL_clk_xbl_SourceConfigMode     eMode
)
{
  switch (eMode)
  {
    case HAL_CLK_SOURCE_CONFIG_MODE_NORMAL:
      return HAL_clk_xbl_PongoEvoPLLConfigPLLNormal(pSource, pConfig);

    default:
      return FALSE;
  }

} /* END HAL_clk_xbl_PongoEvoPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLSetCalConfig
**
** ======================================================================== */

bool HAL_clk_xbl_PongoEvoPLLSetCalConfig
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig
)
{
  /* No calibration supported */
  return TRUE;

} /* HAL_clk_xbl_PongoEvoPLLSetCalConfig */


/* ===========================================================================
**  HAL_clk_xbl_PongoEvoPLLSetRegSettings
**
** ======================================================================== */

void HAL_clk_xbl_PongoEvoPLLSetRegSettings
(
  HAL_clk_xbl_SourceDescType              *pSource,
  const HAL_clk_xbl_SourceRegSettingsType *pmSettings
)
{
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL,    pSource, pmSettings->nConfigCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U,  pSource, pmSettings->nConfigCtl1);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U1, pSource, pmSettings->nConfigCtl2);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U2, pSource, pmSettings->nConfigCtl3);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL,      pSource, pmSettings->nTestCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U,    pSource, pmSettings->nTestCtl1);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U1,   pSource, pmSettings->nTestCtl2);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U2,   pSource, pmSettings->nTestCtl3);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U3,   pSource, pmSettings->nTestCtl4);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL,      pSource, pmSettings->nUserCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U,    pSource, pmSettings->nUserCtl1);

} /* END HAL_clk_xbl_PongoEvoPLLSetRegSettings */


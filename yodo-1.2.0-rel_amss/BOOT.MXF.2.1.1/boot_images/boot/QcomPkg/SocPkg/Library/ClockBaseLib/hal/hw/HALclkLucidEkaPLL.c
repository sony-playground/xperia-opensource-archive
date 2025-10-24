/*
==============================================================================

FILE:         HALclkLucidEkaPLL.c

DESCRIPTION:
  This file contains the clock HAL code for the LucidEka PLL control.
  These PLLs are of the LucidEka PLL variety.

==============================================================================
    Copyright (c) 2020 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include "stdint.h"
#include "HALhwio.h"
#include "HALclkXBLInternal.h"
#include "HALclkGenericPLL.h"
#include "HALclkLucidEkaPLL.h"
#include "busywait.h"
#include "stdbool.h"

/* ============================================================================
**    Definitions
** ==========================================================================*/

/*
 * HAL_CLK_PLL_MODE_ACTIVE
 */
#define HAL_CLK_PLL_MODE_ACTIVE  \
  (HWIO_FMSK(PLL_MODE, PLL_LOCK_DET)  | \
   HWIO_FMSK(PLL_MODE, PLL_RESET_N))

/*
 * HAL_CLK_LOCK_TIMEOUT_US
 *
 * Timeout in US for PLL_LOCK_DET to get set.
 */
#define HAL_CLK_LOCK_TIMEOUT_US 200

/*
 * CLOCK_WAIT_FOR_PLL_LOCK
 *
 * Flag for whether to wait for the PLL to lock or not.
 */
#define CLOCK_WAIT_FOR_PLL_LOCK TRUE

/* ============================================================================
**    Functions Prototypes
** ==========================================================================*/

static bool HAL_clk_xbl_LucidEkaPLLEnable           ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceDisableModeType eMode, void *pData );
static bool HAL_clk_xbl_LucidEkaPLLIsEnabled        ( HAL_clk_xbl_SourceDescType *pSource );
static void HAL_clk_xbl_LucidEkaPLLConfig           ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceConfigType eConfig );
static bool HAL_clk_xbl_LucidEkaPLLConfigPLL        ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig, HAL_clk_xbl_SourceConfigMode eMode );
static bool HAL_clk_xbl_LucidEkaPLLEnableVote       ( HAL_clk_xbl_SourceDescType *pSource );
static bool HAL_clk_xbl_LucidEkaPLLSetCalConfig     ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig );
static void HAL_clk_xbl_LucidEkaPLLSetRegSettings   ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_SourceRegSettingsType *pmSettings );


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_xbl_LucidEkaPLLControl
 *
 * Control function array for the LucidEka PLLs.
 */
HAL_clk_xbl_SourceControlType HAL_clk_xbl_LucidekaPLLControl =
{
  .Enable           = HAL_clk_xbl_LucidEkaPLLEnable,
  .IsEnabled        = HAL_clk_xbl_LucidEkaPLLIsEnabled,
  .Config           = HAL_clk_xbl_LucidEkaPLLConfig,
  .ConfigPLL        = HAL_clk_xbl_LucidEkaPLLConfigPLL,
  .EnableVote       = HAL_clk_xbl_LucidEkaPLLEnableVote,
  .SetCalConfig     = HAL_clk_xbl_LucidEkaPLLSetCalConfig,
  .SetRegSettings   = HAL_clk_xbl_LucidEkaPLLSetRegSettings,
};

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clk_xbl_LucidEkaPLLEnableVote
**
** ======================================================================== */

static bool HAL_clk_xbl_LucidEkaPLLEnableVote
(
  HAL_clk_xbl_SourceDescType *pSource
)
{
  uint32_t nVal;
  bool     bResult;

  /*
   * Set the appropriate bit.
   */
  nVal = inpdw(pSource->VoterRegister.nAddr) | pSource->VoterRegister.nMask;
  outpdw(pSource->VoterRegister.nAddr, nVal);

  /*
   * Wait for the PLL to go active during the 15 us timeout period.
   */
  bResult =
    HAL_clk_xbl_ValidateRegSetTimeout(
      HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
      HAL_CLK_PLL_MODE_ACTIVE,
      HAL_CLK_LOCK_TIMEOUT_US);

  return bResult;

} /* END HAL_clk_xbl_LucidEkaPLLEnableVote */


/* ===========================================================================
**  HAL_clk_xbl_LucidEkaPLLEnable
**
**  The appropriate enable mode is executed based on the eMode parameter.
**
**  Returns:
**    bool - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */

static bool HAL_clk_xbl_LucidEkaPLLEnable
(
  HAL_clk_xbl_SourceDescType        *pSource,
  HAL_clk_xbl_SourceDisableModeType  eMode,
  void                          *pData
)
{
  bool bResult;

  /*
   * Set desired operational mode.
   * This field is ignored when the PLL is in FSM mode.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_RUN);

  /*
   * Take PLL out of reset, which will switch to configured OPMODE.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_RESET_N, 1);

  /*
   * Wait for the PLL to lock if needed.
   */
  bResult = HAL_clk_xbl_ValidateRegSetTimeout(
              HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
              HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
              HAL_CLK_LOCK_TIMEOUT_US);
  if (!bResult)
  {
    return FALSE;
  }

  /*
   * Enable the PLL outputs.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_OUTCTRL, 1);

  return TRUE;

} /* END of HAL_clk_xbl_LucidEkaPLLEnable */


/* ===========================================================================
**  HAL_clk_xbl_LucidEkaPLLIsEnabled
**
** ======================================================================== */

static bool HAL_clk_xbl_LucidEkaPLLIsEnabled
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

} /* END HAL_clk_xbl_LucidEkaPLLIsEnabled */


/* ===========================================================================
**  HAL_clk_xbl_LucidEkaPLLConfig
**
** ======================================================================== */

static void HAL_clk_xbl_LucidEkaPLLConfig
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
    case HAL_CLK_CONFIG_PLL_FSM_MODE_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, ENABLE_VOTE_RUN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_EVEN_EN, 1);
      break;

    case HAL_CLK_CONFIG_PLL_ODD_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_ODD_EN, 1);
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

    case HAL_CLK_CONFIG_PLL_ODD_OUTPUT_HW_CTL_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, OUT_ODD_HW_CTL, 1);
      break;

    default:
      break;
  }

} /* END HAL_clk_xbl_LucidEkaPLLConfig */


/* ===========================================================================
**  HAL_clk_xbl_LucidEkaPLLConfigPLLNormal
**
**  Returns:
**    bool - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static bool HAL_clk_xbl_LucidEkaPLLConfigPLLNormal
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig
)
{
  uint32_t nUserVal;
  uint32_t nOddDiv, nEvenDiv;
  bool     bPLLInFSMMode;

  /*
   * Check PLL mode.
   */
  bPLLInFSMMode = HAL_CLK_PLL_HWIO_INF(PLL_USER_CTL, pSource, ENABLE_VOTE_RUN);

  /*
   * Program L value.
   */
  HAL_CLK_PLL_HWIO_OUTF(PLL_L_VAL, pSource, PLL_L_VAL, pConfig->nL);

  /*
   * Program fractional value.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pSource, pConfig->nFracVal);

  nUserVal = HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL, pSource);
  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserVal &= ~(HWIO_FMSK(PLL_USER_CTL, PRE_DIV_RATIO) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_ODD) |
                HWIO_FMSK(PLL_USER_CTL, POST_DIV_RATIO_EVEN));

  /*
   * Program the post-div values.
   */
  nOddDiv = pConfig->PostDivs.Lucideka.nOdd;
  nEvenDiv = pConfig->PostDivs.Lucideka.nEven;
  if (nEvenDiv > 0)
  {
    nEvenDiv--;
  }
  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POST_DIV_RATIO_ODD, nOddDiv);
  nUserVal |= HWIO_FVAL(PLL_USER_CTL, POST_DIV_RATIO_EVEN, nEvenDiv);

  /*
   * Finally program the USER_CTL register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL, pSource, nUserVal);

  /*
   * For FSM, set the rest_n to bring the PLL out of reset as part of the 
   * steps to enable FSM mode.  This is a one-time programming.
   */
  if (bPLLInFSMMode)
  {
    HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_RESET_N, 1);
  }

  return TRUE;

} /* END HAL_clk_xbl_LucidEkaPLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clk_xbl_LucidEkaPLLConfigPLL
**
**  Returns:
**    bool - TRUE if successfully configured. FALSE otherwise.
** ======================================================================== */

static bool HAL_clk_xbl_LucidEkaPLLConfigPLL
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig,
  HAL_clk_xbl_SourceConfigMode     eMode
)
{
  switch (eMode)
  {
    case HAL_CLK_SOURCE_CONFIG_MODE_NORMAL:
      return HAL_clk_xbl_LucidEkaPLLConfigPLLNormal(pSource, pConfig);

    default:
      return FALSE;
  }

} /* END HAL_clk_xbl_LucidEkaPLLConfigPLL */


/* ===========================================================================
**  HAL_clk_xbl_LucidEkaPLLSetCalConfig
**
** ======================================================================== */

static bool HAL_clk_xbl_LucidEkaPLLSetCalConfig
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig
)
{
  HAL_CLK_PLL_HWIO_OUTF(PLL_L_VAL, pSource, PLL_CAL_L_VAL, pConfig->nL);
  return TRUE;

} /* HAL_clk_xbl_LucidEkaPLLSetCalConfig */


/* ===========================================================================
**  HAL_clk_xbl_LucidEkaPLLSetRegSettings
**
** ======================================================================== */

static void HAL_clk_xbl_LucidEkaPLLSetRegSettings
(
  HAL_clk_xbl_SourceDescType              *pSource,
  const HAL_clk_xbl_SourceRegSettingsType *pmSettings
)
{
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL,    pSource, pmSettings->nConfigCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U,  pSource, pmSettings->nConfigCtl1);
  HAL_CLK_PLL_HWIO_OUT(PLL_CONFIG_CTL_U1, pSource, pmSettings->nConfigCtl2);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL,      pSource, pmSettings->nTestCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U,    pSource, pmSettings->nTestCtl1);
  HAL_CLK_PLL_HWIO_OUT(PLL_TEST_CTL_U1,   pSource, pmSettings->nTestCtl2);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL,      pSource, pmSettings->nUserCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U,    pSource, pmSettings->nUserCtl1);

} /* END HAL_clk_xbl_LucidEkaPLLSetRegSettings */

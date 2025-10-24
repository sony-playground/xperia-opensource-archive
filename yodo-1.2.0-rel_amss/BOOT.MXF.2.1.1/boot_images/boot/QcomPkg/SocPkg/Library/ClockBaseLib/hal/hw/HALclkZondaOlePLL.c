/*
==============================================================================

FILE:         HALclkZondaOlePLL.c

DESCRIPTION:
  This file contains the clock HAL code for the Zonda Ole PLL control.
  These PLLs are of the Zonda PLL variety.

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
#include "HALclkZondaOlePLL.h"
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
#define HAL_CLK_PLL_MODE_ACTIVE  \
  (HWIO_FMSK(PLL_MODE, PLL_OUTCTRL)  | \
   HWIO_FMSK(PLL_MODE, PLL_BYPASSNL) | \
   HWIO_FMSK(PLL_MODE, PLL_LOCK_DET) | \
   HWIO_FMSK(PLL_MODE, PLL_RESET_N))

/*
 * HAL_CLK_LOCK_TIMEOUT_US
 *
 * Timeout in usec for PLL_LOCK_DET to get set.
 * For Zonda, this is 50us worst-case lock time.
 */
#define HAL_CLK_LOCK_TIMEOUT_US 50


/* ============================================================================
**    Functions Prototypes
** ==========================================================================*/

bool HAL_clk_xbl_ZondaOlePLLEnable           ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceDisableModeType eMode, void *pData );
bool HAL_clk_xbl_ZondaOlePLLIsEnabled        ( HAL_clk_xbl_SourceDescType *pSource );
void HAL_clk_xbl_ZondaOlePLLConfig           ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceConfigType eConfig );
bool HAL_clk_xbl_ZondaOlePLLConfigPLL        ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig, HAL_clk_xbl_SourceConfigMode eMode );
bool HAL_clk_xbl_ZondaOlePLLEnableVote       ( HAL_clk_xbl_SourceDescType *pSource );
bool HAL_clk_xbl_ZondaOlePLLSetCalConfig     ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig );
void HAL_clk_xbl_ZondaOlePLLSetRegSettings   ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_SourceRegSettingsType *pmSettings );


/* ============================================================================
**    Data Declarations
** ==========================================================================*/

/*
 * HAL_clk_xbl_ZondaOlePLLControl
 *
 * Control function array for the Zonda PLLs.
 */
HAL_clk_xbl_SourceControlType HAL_clk_xbl_ZondaolePLLControl =
{
  .Enable           = HAL_clk_xbl_ZondaOlePLLEnable,
  .IsEnabled        = HAL_clk_xbl_ZondaOlePLLIsEnabled,
  .Config           = HAL_clk_xbl_ZondaOlePLLConfig,
  .ConfigPLL        = HAL_clk_xbl_ZondaOlePLLConfigPLL,
  .EnableVote       = HAL_clk_xbl_ZondaOlePLLEnableVote,
  .SetCalConfig     = HAL_clk_xbl_ZondaOlePLLSetCalConfig,
  .SetRegSettings   = HAL_clk_xbl_ZondaOlePLLSetRegSettings,
};


/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clk_xbl_LucidOlePLLEnableVote
**
** ======================================================================== */

bool HAL_clk_xbl_ZondaOlePLLEnableVote
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

} /* END HAL_clk_xbl_ZondaOlePLLEnableVote */


/* ===========================================================================
**  HAL_clk_xbl_ZondaOlePLLPostDivToHW
**
** ======================================================================== */

uint32_t HAL_clk_xbl_ZondaOlePLLPostDivToHW (uint32_t nDivider)
{
  switch (nDivider)
  {
    case 0:
    case 1:   return 0; /* Divide-by-1 */
    case 2:   return 1; /* Divide-by-2 */
    case 4:   return 3; /* Divide-by-4 */
    case 8:   return 2; /* Divide-by-8 */
    default:
      return 0;
  }

} /* END HAL_clk_xbl_ZondaOlePLLPostDivToHW */

 
/* ===========================================================================
**  HAL_clk_xbl_ZondaOlePLLEnable
**
**  The appropriate enable mode is executed based on the eMode parameter.
**
**  Returns:
**    bool - TRUE if successfully enabled. FALSE otherwise.
** ======================================================================== */
 
bool HAL_clk_xbl_ZondaOlePLLEnable
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
  if (HAL_clk_xbl_ZondaOlePLLIsEnabled(pSource))
  {
    return TRUE;
  }

  /*
   * Read current mode value.
   */
  nModeVal = HAL_CLK_PLL_HWIO_IN(PLL_MODE, pSource);

  /*
   * Assert PLL bypass and bring pll out of reset.
   * This latches L and Alpha values.
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_BYPASSNL);
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_RESET_N);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);
  
  /*
   * Set desired operational mode.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_OPMODE, pSource, HAL_PLL_OPMODE_RUN);
  
  /*
   * Normal lock detect for PLL.
   */
  bResult = HAL_clk_xbl_ValidateRegSetTimeout(
              HAL_CLK_PLL_HWIO_ADDR(PLL_MODE, pSource),
              HWIO_FMSK(PLL_MODE, PLL_LOCK_DET),
              HAL_CLK_LOCK_TIMEOUT_US);    

  /*
   * Return immediately if the lock detect failed.
   */
  if (!bResult)
  {
    return FALSE;
  }

  /*
   * Put the PLL in active mode
   */
  nModeVal |= HWIO_FMSK(PLL_MODE, PLL_OUTCTRL);
  HAL_CLK_PLL_HWIO_OUT(PLL_MODE, pSource, nModeVal);

  return TRUE;
 
} /* END of HAL_clk_xbl_ZondaOlePLLEnable */


/* ===========================================================================
**  HAL_clk_xbl_ZondaOlePLLIsEnabled
**
** ======================================================================== */

bool HAL_clk_xbl_ZondaOlePLLIsEnabled
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

} /* END HAL_clk_xbl_ZondaOlePLLIsEnabled */


/* ===========================================================================
**  HAL_clk_xbl_ZondaOlePLLConfig
**
** ======================================================================== */

void HAL_clk_xbl_ZondaOlePLLConfig
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
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_EVEN_ENABLE, 1);
      break;

    case HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE:
      HAL_CLK_PLL_HWIO_OUTF(PLL_USER_CTL, pSource, PLLOUT_MAIN_ENABLE, 1);
      break;

    default:
      break;
  }

} /* END HAL_clk_xbl_ZondaOlePLLConfig */


/* ===========================================================================
**  HAL_clk_xbl_ZondaOlePLLConfigPLLNormal
**
** ======================================================================== */

bool HAL_clk_xbl_ZondaOlePLLConfigPLLNormal
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig
)
{
  uint32_t nUserUVal;
  uint32_t bPLLInFSMMode = 0;
  uint16_t nFracVal = 0;

  /*
   * Check PLL FSM mode.
   */
  bPLLInFSMMode = HAL_CLK_PLL_HWIO_INF(PLL_USER_CTL, pSource, ENABLE_VOTE_RUN);

  /*
   * Program L/Alpha values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pSource, pConfig->nL);

  /*
   * Get the CONFIG value and clear out fields we will configure.
   */
  nUserUVal  =  HAL_CLK_PLL_HWIO_IN(PLL_USER_CTL_U, pSource);
  nUserUVal &= ~(HWIO_FMSK(PLL_USER_CTL_U, FRAC_ALPHA_MN_MODE) |
                HWIO_FMSK(PLL_USER_CTL_U, PLL_FRAC_MODE_ENABLE) |
                HWIO_FMSK(PLL_USER_CTL_U, PRE_DIV_2_ENABLE) |
                HWIO_FMSK(PLL_USER_CTL_U, POST_DIV_CONTROL));

  /*
   * Program the post-div value.
   */
  nUserUVal |= HWIO_FVAL(PLL_USER_CTL_U, POST_DIV_CONTROL,
    HAL_clk_xbl_ZondaOlePLLPostDivToHW(pConfig->PostDivs.Zonda.nMain));

  /*
   *  Check fractional output or integer output.
   */
  if (pConfig->eFracMode == HAL_CLK_PLL_FRAC_MODE_MN)
  {
    /*
     * MN Mode
     */
    nFracVal = (uint16_t)(pConfig->nFracVal & 0x0000FFFF);
    nFracVal |= (uint16_t)((pConfig->nFracVal & 0xFFFF0000) >> 8);
    nUserUVal |= HWIO_FMSK(PLL_USER_CTL_U, FRAC_ALPHA_MN_MODE);
    nUserUVal |= HWIO_FMSK(PLL_USER_CTL_U, PLL_FRAC_MODE_ENABLE);
  }
  else
  {
    /*
     * Default to Alpha mode
     */
    nFracVal = (uint16_t)pConfig->nFracVal;
    nUserUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, FRAC_ALPHA_MN_MODE);
    nUserUVal |= HWIO_FMSK(PLL_USER_CTL_U, PLL_FRAC_MODE_ENABLE);
  }
    
    
  HAL_CLK_PLL_HWIO_OUTF(PLL_ALPHA_VAL, pSource, PLL_ALPHA_VAL, nFracVal);

  /*
   * Finally program the USER_CTL_U register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pSource, nUserUVal);

   /*
   * For FSM, set the rest_n to bring the PLL out of reset as part of the 
   * steps to enable FSM mode.  This is a one-time programming.
   */
  if (bPLLInFSMMode)
  {
    HAL_CLK_PLL_HWIO_OUTF(PLL_MODE, pSource, PLL_RESET_N, 1);
  }

  return TRUE;

} /* END HAL_clk_xbl_ZondaOlePLLConfigPLLNormal */


/* ===========================================================================
**  HAL_clk_xbl_ZondaOlePLLConfigPLL
**
** ======================================================================== */

bool HAL_clk_xbl_ZondaOlePLLConfigPLL
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig,
  HAL_clk_xbl_SourceConfigMode     eMode
)
{
  switch (eMode)
  {
    case HAL_CLK_SOURCE_CONFIG_MODE_NORMAL:
      return HAL_clk_xbl_ZondaOlePLLConfigPLLNormal(pSource, pConfig);

    default:
      return FALSE;
  }

} /* END HAL_clk_xbl_ZondaOlePLLConfigPLL */


/* ===========================================================================
**  HAL_clk_xbl_ZondaOlePLLSetCalConfig
**
** ======================================================================== */

bool HAL_clk_xbl_ZondaOlePLLSetCalConfig
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig
)
{
  /* No calibration required. */
  return TRUE;

} /* HAL_clk_xbl_ZondaOlePLLSetCalConfig */


/* ===========================================================================
**  HAL_clk_xbl_ZondaOlePLLSetRegSettings
**
** ======================================================================== */

void HAL_clk_xbl_ZondaOlePLLSetRegSettings
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
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL,      pSource, pmSettings->nUserCtl);
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U,    pSource, pmSettings->nUserCtl1);

} /* END HAL_clk_xbl_ZondaOlePLLSetRegSettings */


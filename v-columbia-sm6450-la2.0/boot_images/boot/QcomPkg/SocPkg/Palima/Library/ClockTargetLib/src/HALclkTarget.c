/**
==============================================================================

  @file HALclkTarget.c

  Target specific control structures

  Copyright (c) 2021 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential.

==============================================================================
*/

/* ============================================================================
**    Include Files
** ==========================================================================*/

#include "stdint.h"
#include "HALhwio.h"
#include "HALclkXBLInternal.h"
#include "HALclkGenericPLL.h"
#include "HALclkZondaEvoPLL.h"
#include "stdbool.h"
#include "HALclkHWIO.h"
#include "ClockDriver.h"

/* ============================================================================
**    Data Declarations
** ==========================================================================*/

bool HAL_clk_xbl_PongoOlePLLEnable               ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceDisableModeType eMode, void *pData );
bool HAL_clk_xbl_PongoOlePLLIsEnabled            ( HAL_clk_xbl_SourceDescType *pSource );
void HAL_clk_xbl_PongoOlePLLConfig               ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceConfigType eConfig );
bool HAL_clk_xbl_PongoOlePLLConfigPLL            ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig, HAL_clk_xbl_SourceConfigMode eMode );
bool HAL_clk_xbl_PongoOlePLLSetCalConfig         ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig );
void HAL_clk_xbl_PongoOlePLLSetRegSettings       ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_SourceRegSettingsType *pmSettings );
void HAL_clk_xbl_PongoOlePLLPalimaSetRegSettings ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_SourceRegSettingsType *pmSettings);


HAL_clk_xbl_SourceControlType HAL_clk_xbl_PongoolePalimaPLLControl =
{
  .Enable           = HAL_clk_xbl_PongoOlePLLEnable,
  .IsEnabled        = HAL_clk_xbl_PongoOlePLLIsEnabled,
  .Config           = HAL_clk_xbl_PongoOlePLLConfig,
  .ConfigPLL        = HAL_clk_xbl_PongoOlePLLConfigPLL,
  .SetCalConfig     = HAL_clk_xbl_PongoOlePLLSetCalConfig,
  .SetRegSettings   = HAL_clk_xbl_PongoOlePLLPalimaSetRegSettings,
};


/* ============================================================================
**    Functions
** ==========================================================================*/

/* ===========================================================================
**  HAL_clk_xbl_ZondaOleWAPLLPostDivToHW
**
** ======================================================================== */

static uint32_t HAL_clk_xbl_ZondaOleWAPLLPostDivToHW (uint32_t nDivider)
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

} /* END HAL_clk_xbl_ZondaOleWAPLLPostDivToHW */


/* ===========================================================================
**  HAL_clk_xbl_ZondaOleWAPLLConfigPLL
**
** ======================================================================== */

bool HAL_clk_xbl_ZondaOleWAPLLConfigPLL
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig,
  HAL_clk_xbl_SourceConfigMode     eMode
)
{
  uint32_t nUserUVal;
  uint16_t nFracVal = 0;

  /*
   * Program L/Alpha values.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_L_VAL, pSource, pConfig->nL);

  /*
   * Program L/Alpha values.
   * For Palima, The internal PLL L value register is treated as don't care.
   * We need to write to the external register.
   */
  if (pSource->nAddr == HWIO_ADDR(APSS_CC_SILVER_PLL_MODE))
  {
    HWIO_OUT(APSS_CC_SILVER_PLL_LVAL, pConfig->nL);
  }
  else if (pSource->nAddr == HWIO_ADDR(APSS_CC_GOLD_PLL_MODE))
  {
    HWIO_OUT(APSS_CC_GOLD_PLL_LVAL, pConfig->nL);
  }
  else if (pSource->nAddr == HWIO_ADDR(APSS_CC_L3_PLL_MODE))
  {
    HWIO_OUT(APSS_CC_L3_PLL_LVAL, pConfig->nL);
  }
  else if (pSource->nAddr == HWIO_ADDR(APSS_CC_GOLDPLUS_PLL_MODE))
  {
    HWIO_OUT(APSS_CC_GOLD_PLUS_PLL_LVAL, pConfig->nL);
  }

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
    HAL_clk_xbl_ZondaOleWAPLLPostDivToHW(pConfig->PostDivs.Zonda.nMain));

  /*
   *  Check fractional output or integer output.
   */
  if (pConfig->nFracVal)
  {
    /*
     * Default to Alpha mode
     */
    nFracVal = (uint16_t)pConfig->nFracVal;
    nUserUVal &= ~HWIO_FMSK(PLL_USER_CTL_U, FRAC_ALPHA_MN_MODE);
    nUserUVal |= HWIO_FMSK(PLL_USER_CTL_U, PLL_FRAC_MODE_ENABLE);
    HAL_CLK_PLL_HWIO_OUT(PLL_ALPHA_VAL, pSource, nFracVal);
  }

  /*
   * Finally program the USER_CTL_U register.
   */
  HAL_CLK_PLL_HWIO_OUT(PLL_USER_CTL_U, pSource, nUserUVal);

  return TRUE;

} /* END HAL_clk_xbl_ZondaOleWAPLLConfigPLL */

void HAL_clk_xbl_PongoOlePLLPalimaSetRegSettings
(
  HAL_clk_xbl_SourceDescType              *pSource,
  const HAL_clk_xbl_SourceRegSettingsType *pmSettings
)
{
  uint32_t nK = 0;

  HAL_clk_xbl_PongoOlePLLSetRegSettings(pSource, pmSettings);

  nK = HWIO_INF(QFPROM_CORR_CALIBRATION_ROW23_LSB, AOSS_K_15_6) << 6 |
       HWIO_INF(QFPROM_CORR_CALIBRATION_ROW22_MSB, AOSS_K_5_0);

  if (nK)
  {
    HWIO_OUTF(AOSS_CC_PLL1_PLL_CONFIG_CTL_U2, TEMPCOMP_K_DEFAULT, nK);
    HWIO_OUTF(AOSS_CC_PLL1_PLL_TEST_CTL_U2, DISABLE_PCAL, 1);
    HWIO_OUTF(AOSS_CC_PLL1_PLL_TEST_CTL_U1, ENABLE_PCODE_CAL, 1);
    HWIO_OUTF(AOSS_CC_PLL1_PLL_TEST_CTL_U1,
              FORCE_PCAL_VALUE,
              HWIO_INF(QFPROM_CORR_CALIBRATION_ROW23_MSB, AOSS_RDOPCODE) << 2);
    HWIO_OUTF(AOSS_CC_PLL1_PLL_TEST_CTL_U1,
              FORCE_TDO_PCAL_VALUE,
              HWIO_INF(QFPROM_CORR_CALIBRATION_ROW23_MSB, AOSS_TDOPCODE) << 2);
  }
}

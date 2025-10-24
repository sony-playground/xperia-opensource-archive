/*
==============================================================================

FILE:         HALclk.c

DESCRIPTION:
  Common code for the clock HAL module.

==============================================================================
            Copyright (c) 2012 - 2020 QUALCOMM Technologies, Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/
#include "stdint.h"
#include "HALclkXBLInternal.h"
#include <HALhwio.h>
#include "busywait.h"


/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/

/* ============================================================================
**    Typedefs
** ==========================================================================*/

/*============================================================================

               FUNCTION DEFINITIONS FOR MODULE

============================================================================*/

/* ===========================================================================
**  HAL_clk_xbl_EnableSource
**
** ======================================================================== */

boolean HAL_clk_xbl_EnableSource
(
  HAL_clk_xbl_SourceDescType *pSource,
  HAL_clk_xbl_SourceDisableModeType  eMode,
  void                          *pData
)
{
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->Enable != NULL)
  {
    return pSource->pmControl->Enable(pSource, eMode, pData);
  }

  return FALSE;

} /* END HAL_clk_xbl_EnableSource */


/* ===========================================================================
**  HAL_clk_xbl_EnableSourceVote
**
** ======================================================================== */

boolean HAL_clk_xbl_EnableSourceVote
(
  HAL_clk_xbl_SourceDescType *pSource
)
{
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->EnableVote != NULL)
  {
    return pSource->pmControl->EnableVote(pSource);
  }

  return FALSE;

} /* END HAL_clk_xbl_EnableSourceVote */


/* ===========================================================================
**  HAL_clk_xbl_ConfigSource
**
** ======================================================================== */

void HAL_clk_xbl_ConfigSource
(
  HAL_clk_xbl_SourceDescType *pSource,
  HAL_clk_xbl_SourceConfigType eConfig
)
{
  /*
   * Configure the source if possible.
   */
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->Config != NULL)
  {
    pSource->pmControl->Config(pSource, eConfig);
  }

} /* END HAL_clk_xbl_ConfigSource */


/* ===========================================================================
**  HAL_clk_xbl_ConfigPLL
**
** ======================================================================== */

boolean HAL_clk_xbl_ConfigPLL
(
  HAL_clk_xbl_SourceDescType *pSource,
  const HAL_clk_xbl_PLLConfigType *pConfig,
  HAL_clk_xbl_SourceConfigMode     eMode
)
{
  /*
   * Configure the source if possible.
   */
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->ConfigPLL != NULL)
  {
    return pSource->pmControl->ConfigPLL(pSource, pConfig, eMode);
  }

  return FALSE;

} /* END HAL_clk_xbl_ConfigPLL */


/* ===========================================================================
**  HAL_clk_xbl_IsSourceEnabled
**
** ======================================================================== */

boolean HAL_clk_xbl_IsSourceEnabled
(
  HAL_clk_xbl_SourceDescType *pSource
)
{
  /*
   * Invoke the callback.
   */
  if (pSource != NULL &&
      pSource->pmControl != NULL &&
      pSource->pmControl->IsEnabled != NULL)
  {
    return pSource->pmControl->IsEnabled(
      pSource);
  }

  return FALSE;

} /* END HAL_clk_xbl_IsSourceEnabled */


/* ===========================================================================
**  HAL_clk_xbl_ValidateRegSetTimeout
**
** ======================================================================== */

boolean HAL_clk_xbl_ValidateRegSetTimeout
(
  uintnt    nAddr,
  uint32_t  nMask,
  uint32_t  nTimeoutUS
)
{
  /*
   * Wait for the register field to set during the timeout period.
   */
  do
  {
    if (in_dword_masked(nAddr, nMask))
    {
      return TRUE;
    }
    /*
     * Wait 1 us between each register read.
     */
    else
    {
      busywait(1);
    }
  }

  /*
   * nTimeoutUS is post-decremented to guarantee that we waited up to
   * the original nTimeoutUS value.
   */
  while(nTimeoutUS--);

  return FALSE;

} /* END HAL_clk_xbl_ValidateRegSetTimeout */


boolean HAL_clk_xbl_SetSourceCalConfig
(
  HAL_clk_xbl_SourceDescType      *pSource,
  const HAL_clk_xbl_PLLConfigType *pmConfig
)
{
  if (pSource                           != NULL &&
      pSource->pmControl                != NULL &&
      pSource->pmControl->SetCalConfig  != NULL)
  {
    return pSource->pmControl->SetCalConfig(pSource, pmConfig);
  }

  return FALSE;
}


void HAL_clk_xbl_SetSourceRegSettings
(
  HAL_clk_xbl_SourceDescType              *pSource,
  const HAL_clk_xbl_SourceRegSettingsType *pmSettings
)
{
  if (pSource                               != NULL &&
      pSource->pmControl                    != NULL &&
      pSource->pmControl->SetRegSettings    != NULL)
  {
    pSource->pmControl->SetRegSettings(pSource, pmSettings);
  }
}

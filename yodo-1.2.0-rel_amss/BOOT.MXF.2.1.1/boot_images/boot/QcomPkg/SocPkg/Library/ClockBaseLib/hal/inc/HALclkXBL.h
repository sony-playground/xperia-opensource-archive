#ifndef __HALCLK_H__
#define __HALCLK_H__
/*
==============================================================================

FILE:         HALclk.h

DESCRIPTION:

==============================================================================

                             Edit History

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Library/ClockBaseLib/hal/inc/HALclkXBL.h#1 $

when       who     what, where, why
--------   ---     -----------------------------------------------------------
07/18/11   vs      Ported from the latest clock driver.


==============================================================================
            Copyright (c) 2020 QUALCOMM Technologies, Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*============================================================================

                     INCLUDE FILES FOR MODULE

============================================================================*/

#include <HALcomdef.h>

/*============================================================================

             DEFINITIONS AND DECLARATIONS FOR MODULE

=============================================================================*/

#ifndef MIN
  #define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
  #define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif


/*
 * Macro to generate the hardware version number from a given major
 * and minor number.  Used when comparing against return value of
 * HAL_clk_GetChipVersion(). For example to check if this is at least
 * version 1.2:
 *   if (HAL_clk_GetChipVersion() >= HAL_CLK_CHIP_VERSION(1,2))
 */
#define HAL_CLK_CHIP_VERSION(major, minor)  (((major) << 16) | (minor))


/*
 * Value used to indicate clock has no debug mux connection.
 */
#define HAL_CLK_NO_DEBUG_MUX_SEL  0xFFFFFFFF


/* ============================================================================
**    Typedefs
** ==========================================================================*/

/*
 * Forward declaration of structs b/c of the cross references within these
 * structs
 */
typedef struct HAL_clk_xbl_ClockDescType       HAL_clk_xbl_ClockDescType;
typedef struct HAL_clk_xbl_ClockDomainDescType HAL_clk_xbl_ClockDomainDescType;
typedef struct HAL_clk_xbl_SourceDescType      HAL_clk_xbl_SourceDescType;
typedef struct HAL_clk_xbl_PowerDomainDescType HAL_clk_xbl_PowerDomainDescType;
typedef struct HAL_clk_xbl_DividerDescType     HAL_clk_xbl_DividerDescType;
typedef struct HAL_clk_xbl_DebugMuxDescType    HAL_clk_xbl_DebugMuxDescType;


/*
 * HAL_clk_xbl_ClockMuxConfigType
 *
 * Parameters used for configuring a standard clock multiplexer.
 *
 *  eSource  - The source to use.
 *  nDiv2x   - The integer (2 * divider) value to use.
 *  nM       - The M value for any M/N counter, or 0 to bypass.
 *  nN       - The N value for any M/N counter.
 *  nDFSIdx  - The DFS index this config is used for. 0xFF if not used in DFS.
 */
typedef struct
{
  uint8   nMuxSel;
  uint8   nDiv2x;
  uint16  nM;
  uint16  nN;
  uint8   nDFSIdx;
} HAL_clk_xbl_ClockMuxConfigType;


/*
 * HAL_clk_xbl_SourceConfigType
 *
 * Configuration enumerations for sources.
 *
 */
typedef enum
{
  HAL_CLK_CONFIG_SOURCE_NULL = 0,

  HAL_CLK_CONFIG_PLL_FSM_MODE_ENABLE,
  HAL_CLK_CONFIG_PLL_FSM_MODE_DISABLE,
  HAL_CLK_CONFIG_PLL_AUX_OUTPUT_DISABLE,
  HAL_CLK_CONFIG_PLL_AUX_OUTPUT_ENABLE,
  HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_DISABLE,
  HAL_CLK_CONFIG_PLL_AUX2_OUTPUT_ENABLE,
  HAL_CLK_CONFIG_PLL_TEST_OUTPUT_DISABLE,
  HAL_CLK_CONFIG_PLL_TEST_OUTPUT_ENABLE,
  HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_DISABLE,
  HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE,
  HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_DISABLE,
  HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE,
  HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL_ENABLE,
  HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_DISABLE,
  HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_HW_CTL_ENABLE,
  HAL_CLK_CONFIG_PLL_ODD_OUTPUT_ENABLE,
  HAL_CLK_CONFIG_PLL_ODD_OUTPUT_DISABLE,
  HAL_CLK_CONFIG_PLL_ODD_OUTPUT_HW_CTL_ENABLE,
  HAL_CLK_CONFIG_PLL_DROOP_DETECTION_DISABLE,
  HAL_CLK_CONFIG_PLL_DROOP_DETECTION_ENABLE,
  HAL_CLK_CONFIG_PLL_OUT_INV_EN_DISABLE,
  HAL_CLK_CONFIG_PLL_OUT_INV_EN_ENABLE,
  HAL_CLK_CONFIG_PLL_MASTER_EN_DISABLE,
  HAL_CLK_CONFIG_PLL_MASTER_EN_ENABLE,
  HAL_CLK_CONFIG_PLL_BIST_EN_DISABLE,
  HAL_CLK_CONFIG_PLL_BIST_EN_ENABLE,

  HAL_CLK_CONFIG_XO_CHIP_BUFFER_USING_EXT_CLK_SRC,
  HAL_CLK_CONFIG_XO_USING_EXT_CRYSTAL,
  HAL_CLK_CONFIG_XO_GAIN_0,
  HAL_CLK_CONFIG_XO_GAIN_1,
  HAL_CLK_CONFIG_XO_GAIN_2,
  HAL_CLK_CONFIG_XO_GAIN_3,
  HAL_CLK_CONFIG_XO_GAIN_4,
  HAL_CLK_CONFIG_XO_GAIN_5,
  HAL_CLK_CONFIG_XO_GAIN_6,
  HAL_CLK_CONFIG_XO_GAIN_7,

  HAL_CLK_CONFIG_XO_DOUBLER_DCC,

  HAL_ENUM_32BITS(CLK_SOURCE_CONFIG)
} HAL_clk_xbl_SourceConfigType;


/*
 * HAL_clk_xbl_PLLPostDivType
 *
 * PLL-specific post dividers.
 */
typedef union
{
  struct
  {
    uint8 nEven;
    uint8 nOdd;
  } Lucidevo;

  struct
  {
    uint8 nEven;
    uint8 nOdd;
  } Lucidole;

  struct
  {
    uint8 nEven;
    uint8 nOdd;
  } Lucideka;

  struct
  {
    uint8 nEven;
    uint8 nOdd;
  } Taycan;

  struct
  {
	uint8 nMain;
  } Zonda;

  struct
  {
    uint8 nMain;
    uint8 nEven;
  } Pongoevo;

  struct
  {
    uint8 nMain;
    uint8 nEven;
  } Pongoole;

  struct
  {
    uint8 nMain;
    uint8 nEven;
  } Pongoeka;

  struct
  {
    uint8 nMain;
    uint8 nEven;
    uint8 nAux;
  } Zondaole;
  
} HAL_clk_xbl_PLLPostDivType;


/*
 * HAL_clk_xbl_SourceRegSettingsType
 *
 * Source register settings.
 */
typedef struct
{
  uint32 nConfigCtl;
  uint32 nConfigCtl1;
  uint32 nConfigCtl2;
  uint32 nConfigCtl3;
  uint32 nTestCtl;
  uint32 nTestCtl1;
  uint32 nTestCtl2;
  uint32 nTestCtl3;
  uint32 nTestCtl4;
  uint32 nUserCtl;
  uint32 nUserCtl1;
  uint32 nUserCtl2;
  uint32 nUserCtl3;
} HAL_clk_xbl_SourceRegSettingsType;

/*
 * HAL_clk_xbl_PLLFracModeType
 *
 * PLL fractional modes.
 */
typedef enum
{
  HAL_CLK_PLL_FRAC_MODE_UNKNOWN,
  HAL_CLK_PLL_FRAC_MODE_ALPHA,
  HAL_CLK_PLL_FRAC_MODE_MN,
} HAL_clk_xbl_PLLFracModeType;

/*
 * HAL_clk_xbl_PLLConfigType
 *
 * Parameters used for configuring a source that is a PLL.
 *
 *  nFracVal              - Fractional value, interpreted based on eFracMode.
 *  PostDivs              - Post dividers.
 *  nL                    - The L value for the PLL.  The PLL output frequency is derived
 *                          as out_freq = ((in_freq / nPreDiv) * (L + M/N)) / nPostDiv.
 */
typedef struct
{
  uint64                        nFracVal;
  HAL_clk_xbl_PLLFracModeType   eFracMode;
  HAL_clk_xbl_PLLPostDivType    PostDivs;
  uint8                         nL;
} HAL_clk_xbl_PLLConfigType;


/*
 * HAL_clk_xbl_SourceConfigMode
 *
 *  This enumeration defines the behavior when configuring a PLL.
 *
 *  NORMAL
 *   - Configure the PLL using every field in the source config
 *     structure. This is also known as legacy mode config.
 *
 *  SLEW
 *   - Dynamically re-configure the PLL using only the L/Alpha/AlphaU
 *     fields in the source config structure.  This config mode cannot
 *     re-configure to a frequency that requires a VCO change.
 *
 *  PENDING
 *   - Same as NORMAL mode except we do not trigger the re-configuration
 *     since we expect the HW to latch on to the new configuration
 *     values upon being re-enabled by HW (e.g. SPM).  This mode is
 *     useful for the case where the PLL must be configured to be
 *     enabled by HW at the calibration frequency when exiting sleep.
 */
typedef enum
{
  HAL_CLK_SOURCE_CONFIG_MODE_NORMAL,
  HAL_CLK_SOURCE_CONFIG_MODE_SLEW,
  HAL_CLK_SOURCE_CONFIG_MODE_PENDING,

  HAL_CLK_NUM_OF_SOURCE_CONFIG_MODES,

  HAL_ENUM_32BITS(CLK_SOURCE_CONFIG_MODES)
} HAL_clk_xbl_SourceConfigMode;


/*
 * HAL_clk_xbl_SourceDisableModeType
 *
 *  This enumeration defines the behavior when enabling/disabling a PLL.
 *
 *  NORMAL
 *    - Turns the BIAS circuitry off.
 *    - Perform a normal bringup/shutdown of the PLL.
 *
 *  STANDBY
 *    - Leaves the BIAS circuitry on.
 *    - The saved calibration results in faster enable times at the expense of
 *      higher power usage.
 *
 *  SAVE
 *    - Turns the BIAS circuitry off.
 *    - Save the PLL calibration data to non-volatile storage.
 *      The calibration data is restored when enabling the PLL to skip the
 *      calibration step.
 *
 *  FREEZE
 *    - Disable the PLL output.
 *    - Set the PLL freeze bit.
 *    - Calibration is maintained.
 */
typedef enum
{
  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL            = 0,
  HAL_CLK_SOURCE_DISABLE_MODE_STANDBY           = 1,
  HAL_CLK_SOURCE_DISABLE_MODE_SAVE              = 2,
  HAL_CLK_SOURCE_DISABLE_MODE_FREEZE            = 3,
  HAL_ENUM_32BITS(CLK_SOURCE_DISABLE_MODES)
} HAL_clk_xbl_SourceDisableModeType;


/*============================================================================

               FUNCTION DECLARATIONS FOR MODULE

============================================================================*/


/* ============================================================================
**    Mandatory Functions
** ==========================================================================*/

boolean HAL_clk_xbl_EnableSource            ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceDisableModeType eMode, void *pData );
boolean HAL_clk_xbl_EnableSourceVote        ( HAL_clk_xbl_SourceDescType *pSource );
void    HAL_clk_xbl_ConfigSource            ( HAL_clk_xbl_SourceDescType *pSource, HAL_clk_xbl_SourceConfigType eConfig );
boolean HAL_clk_xbl_IsSourceEnabled         ( HAL_clk_xbl_SourceDescType *pSource );
boolean HAL_clk_xbl_IsSourceVoteEnabled     ( HAL_clk_xbl_SourceDescType *pSource );
boolean HAL_clk_xbl_ConfigPLL               ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig, HAL_clk_xbl_SourceConfigMode eMode );
void    HAL_clk_xbl_SetSourceRegSettings    ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_SourceRegSettingsType *pmSettings );
boolean HAL_clk_xbl_SetSourceCalConfig      ( HAL_clk_xbl_SourceDescType *pSource, const HAL_clk_xbl_PLLConfigType *pmConfig );

boolean HAL_clk_xbl_ValidateRegSetTimeout   ( uintnt nAddr, uint32 nMask, uint32 nTimeoutUS );
boolean HAL_clk_xbl_ValidateRegClearTimeout ( uintnt nAddr, uint32 nMask, uint32 nTimeoutUS );

#endif /* !HALCLK_H */


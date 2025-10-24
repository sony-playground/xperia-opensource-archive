/**
==============================================================================

  @file ClockDriver.c

  Clock driver functions for PLL and clock management

  Copyright (c) 2020 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential.

==============================================================================
*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "ClockBoot.h"
#include "busywait.h"
#include "ClockDriver.h"
#include "ClockBSP.h"
#include "ChipInfo.h"
#include "Clock.h"
#include "voltage_level.h"
#include "CoreVerify.h"
#include "HALclk.h"

/*=========================================================================
      Macro Definitions
==========================================================================*/

/*
 * Clock driver global handle.
 */
#define CLK_GLOBAL_HANDLE         0xDEADBEEF

/*
 * Boot corner.
 */
#define CLOCK_BOOT_CORNER         RAIL_VOLTAGE_LEVEL_NOM

#define CLOCK_UPDATE_TIMEOUT_US   1000

#define CLK_ENABLE_MSK            0x00000001
#define CLK_OFF_MSK               0x80000000
#define CLK_OFF_SHFT              31
#define CLK_HW_CTL_MSK            0x2
#define CLK_GDSCR_SW_COLLAPSE_MSK 0x00000001
#define CLK_GDSCR_PWR_ON_MSK      0x80000000
#define CLK_GDSCR_TIMEOUT_US      150
#define CLK_CDIVR_CLK_DIV_FMSK    0xF

/*
 * Clock ID macros.
 */
#define CLOCK_MAKE_ID(cat, idx)   (((cat) << 16) | (idx))
#define CLOCK_GET_ID_CATEGORY(id) (((id) & 0xFFFF0000) >> 16)
#define CLOCK_GET_ID_INDEX(id)    ((id) & 0xFFFF)
#define CLOCK_ID_INVALID          0

/*
 * NOT_2D / NOT_N_MINUS_M
 *
 * Macros to return the inverted value of the 2D field or (N - M)
 * in a type 1 mux structure.  Used to prepare the value for writing
 * to the hardware register field.
 */
#define NOT_2D(mux)         (~(mux)->nN)
#define NOT_N_MINUS_M(mux)  (~((mux)->nN - (mux)->nM))

/*
 * HALF_DIVIDER
 *
 * Macro to return the normalized half divider for a given mux structure.
 * NOTE: Expecting (2 * divider) value as input.
 */
#define HALF_DIVIDER(mux)  ((mux)->nDiv2x ? (((mux)->nDiv2x) - 1) : 0)

/*
 * Common root clock command fields/masks (*_CMD_RCGR)
 */
#define CLOCK_CMD_CGR_ROOT_OFF_FMSK                                  0x80000000
#define CLOCK_CMD_CGR_ROOT_EN_FMSK                                   0x00000002
#define CLOCK_CMD_CFG_UPDATE_FMSK                                    0x00000001
#define CLOCK_CMD_CFG_UPDATE_SHFT                                    0

/*
 * Common root clock configuration registers and their relative offset to
 * the first register (*_CMD_CGR)
 */
#define CLOCK_CMD_REG_OFFSET                                         0
#define CLOCK_CFG_REG_OFFSET                                         0x4
#define CLOCK_M_REG_OFFSET                                           0x8
#define CLOCK_N_REG_OFFSET                                           0xC
#define CLOCK_D_REG_OFFSET                                           0x10

/*
 * Common root clock config fields/masks (*_CFG_RCGR)
 */
#define CLOCK_CFG_RCGR_MODE_FMSK                                      0x00003000
#define CLOCK_CFG_RCGR_MODE_SHFT                                      0xc
#define CLOCK_CFG_RCGR_SRC_SEL_FMSK                                   0x00000700
#define CLOCK_CFG_RCGR_SRC_SEL_SHFT                                   0x8
#define CLOCK_CFG_RCGR_SRC_DIV_FMSK                                   0x0000001F
#define CLOCK_CFG_RCGR_SRC_DIV_SHFT                                   0

#define CLOCK_CFG_CFG_DUAL_EDGE_MODE_VAL                             0x2
#define CLOCK_CFG_CFG_BYPASS_MODE_VAL                                0x0


/*===========================================================================
                      FUNCTION PROTOTYPES
===========================================================================*/
static const HAL_clk_xbl_SourceRegSettingsType *Clock_GetSourceRegSettings(ClockSourceNodeType *pSource);
static const ClockSourceFreqConfigType *Clock_GetSourceFreqConfig(ClockSourceNodeType *pSource, uint32_t nMinFreqKHz);
static const ClockSourceFreqConfigType *Clock_GetSourceCalConfig(ClockSourceNodeType *pSource);
static ClockResult Clock_GetClockGroupId(const char *szName, ClockIdType *pId);
static ClockResult Clock_GetClockId(const char *szName, ClockIdType *pId);
static ClockResult Clock_GetPowerDomainId(const char *szName, ClockIdType *pId);
static ClockResult Clock_GetDividerId(const char *szName, ClockIdType *pId);
static bool Clock_IsBSPSupported(const ClockHWVersionType *pHWVersion);

/*=========================================================================
      Globals
==========================================================================*/

extern uintptr_t aPllVoteAddrList[CLOCK_MASTER_MAX_SIZE];

extern ClockBSPType ClockBSP;

static rail_voltage_level geBootCorner = CLOCK_BOOT_CORNER;

static bool gbInitialized = FALSE;

/*
 * GetId function type.
 */
typedef ClockResult (*ClockGetIdFn) (const char *, ClockIdType *);

/*
 * Object-specific GetId function pointers.
 */
static ClockGetIdFn ClockGetIdFunctions[] =
{
  Clock_GetClockGroupId,
  Clock_GetClockId,
  Clock_GetPowerDomainId,
  Clock_GetDividerId,
};


/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 

/* =========================================================================
**  Function : Clock_ConfigurePLL
** =========================================================================*/
/**
  Configures a PLL.

  @param pSource -  [IN] PLL configuration structure
  @param pConfig -  [IN] PLL frequency configuration

*/
bool Clock_ConfigurePLL
(
  ClockSourceNodeType             *pSource,
  const ClockSourceFreqConfigType *pConfig
)
{
  uintptr_t nVoteAddr;
  const ClockSourceFreqConfigType *pCalConfig;
  const HAL_clk_xbl_SourceRegSettingsType *pRegSettings;
  const HAL_clk_xbl_PLLConfigType *pHALConfig;
  HAL_clk_xbl_SourceDescType nHALSource;

  if (!pSource)
  {
    return FALSE;
  }

  /*
   * Do not try to configure PLL if already configured.
   */
  if (pSource->nFlags & CLOCK_FLAG_INITIALIZED)
  {
    return TRUE;
  }
  /*
   * Do not try to configure PLL if read only flag is set.
   */
  if (pSource->nFlags & CLOCK_FLAG_READ_ONLY)
  {
    pSource->nFlags |= CLOCK_FLAG_INITIALIZED;
    return TRUE;
  }

  nHALSource.VoterRegister = pSource->VoterRegister;
  nHALSource.pmControl     = pSource->pmControl;
  nHALSource.nAddr         = pSource->nAddr;
  nVoteAddr                = pSource->VoterRegister.nAddr;

  /*
   * If the PLL is locked, return
   */
  if (HAL_clk_xbl_IsSourceEnabled(&nHALSource))
  {
    pSource->nFlags |= CLOCK_FLAG_INITIALIZED | CLOCK_FLAG_ENABLED;
    return TRUE;
  }

  pRegSettings = Clock_GetSourceRegSettings(pSource);
  
  if(pRegSettings)
  {
    HAL_clk_xbl_SetSourceRegSettings(&nHALSource, pRegSettings);
  }

  /* Enable any outputs for this PLL */
  HAL_clk_xbl_ConfigSource(&nHALSource, HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_ENABLE);
  if (pSource->nConfigMask & CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE)
  {
    HAL_clk_xbl_ConfigSource(&nHALSource, HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_ENABLE);
  }
  if (pSource->nConfigMask & CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE)
  {
    HAL_clk_xbl_ConfigSource(&nHALSource, HAL_CLK_CONFIG_PLL_ODD_OUTPUT_ENABLE);
  }
  if (pSource->nConfigMask & CLOCK_CONFIG_PLL_EARLY_OUTPUT_ENABLE)
  {
    HAL_clk_xbl_ConfigSource(&nHALSource, HAL_CLK_CONFIG_PLL_EARLY_OUTPUT_ENABLE);
  }
  if (pSource->nConfigMask & CLOCK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL)
  {
    HAL_clk_xbl_ConfigSource(&nHALSource, HAL_CLK_CONFIG_PLL_MAIN_OUTPUT_HW_CTL_ENABLE);
  }
  if (pSource->nConfigMask & CLOCK_CONFIG_PLL_EVEN_OUTPUT_HW_CTL)
  {
    HAL_clk_xbl_ConfigSource(&nHALSource, HAL_CLK_CONFIG_PLL_EVEN_OUTPUT_HW_CTL_ENABLE);
  }
  if (pSource->nConfigMask & CLOCK_CONFIG_PLL_ODD_OUTPUT_HW_CTL)
  {
    HAL_clk_xbl_ConfigSource(&nHALSource, HAL_CLK_CONFIG_PLL_ODD_OUTPUT_HW_CTL_ENABLE);
  }

  if(pConfig == NULL && pSource->aBSP)
  {
    uint32_t i;
   
    /*
     * Search through table to find correct PLL configs
     * based on the HW version.
     */
    for (i = 0; i < pSource->nBSPLen; i++)
    {
      if (Clock_IsBSPSupported(&pSource->aBSP[i].HWVersion))
      {
        /*
         * Found the correct PLL configs. Break out of loop
         */
        pConfig = &pSource->aBSP[i];
        break;
      }
    }
  }

  /*
   * Unused PLLs may not have any frequency configurations. In this case,
   * return early without configuring the frequency-specific portion. Still
   * configure the CONFIG/TEST_CTL settings, since even though the PLL won't
   * be used for anything, out-of-date settings will still trigger APT test
   * failures.
   */
  if (!pConfig)
  {
    pSource->nFlags |= CLOCK_FLAG_INITIALIZED;
    return TRUE;
  }

  /* 
   * If there is an address for a voting register, then the PLL is in
   * FSM voteable mode. In this case, the enable vote run mode.
   */

  if (nVoteAddr != 0)
  {
    HAL_clk_xbl_ConfigSource(&nHALSource, HAL_CLK_CONFIG_PLL_FSM_MODE_ENABLE);
  }

  pHALConfig = &pConfig->HALConfig;

  pCalConfig = Clock_GetSourceCalConfig(pSource);
  if(pCalConfig)
  {
    HAL_clk_xbl_SetSourceCalConfig(&nHALSource, &pCalConfig->HALConfig);
  }

  HAL_clk_xbl_ConfigPLL(&nHALSource, pHALConfig, HAL_CLK_SOURCE_CONFIG_MODE_NORMAL);

  pSource->nFlags |= CLOCK_FLAG_INITIALIZED;

  return TRUE;
}


/* ============================================================================
**  Function : Clock_EnablePLL
** ============================================================================
*/
/*!
    Enable a PLL.  If it is voteable, it will be set for FSM mode
    and voted for using the vote register. Doesn't configure the PLL.

    @param pSource -  [IN] PLL configuration structure
    @param eVoteMaster - [IN] Master who is voting for this PLL
    @param pConfig -  [IN] PLL frequency configuration
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

static bool Clock_EnablePLL
(
  ClockSourceNodeType             *pSource,
  ClockMasterType                  eVoteMaster,
  const ClockSourceFreqConfigType *pConfig
)
{
  uintptr_t nVoteAddr;
  HAL_clk_xbl_SourceDescType nHAL;

  if (!pSource || eVoteMaster >= CLOCK_MASTER_MAX_SIZE)
  {
    return FALSE;
  }

  nVoteAddr = pSource->VoterRegister.nAddr;

  /*
   * If the PLL is FSM voteable, vote on behalf of domain master
   */
  if (nVoteAddr && aPllVoteAddrList[eVoteMaster])
  {
    pSource->VoterRegister.nAddr = aPllVoteAddrList[eVoteMaster];
  }

  Clock_ConfigurePLL(pSource, pConfig);

  nHAL.VoterRegister = pSource->VoterRegister;
  nHAL.pmControl     = pSource->pmControl;
  nHAL.nAddr         = pSource->nAddr;

  /*
   * Enable the PLL. If there is an address for a voting register, then the
   * PLL is in FSM voteable mode. In this case, the enable sequence is
   * handled in hardware, guided by the BIAS and LOCK counts.
   */
  if (nVoteAddr != 0)
  {
    if (!HAL_clk_xbl_EnableSourceVote(&nHAL))
    {
      return FALSE;
    }
  }
  else
  {
    if (!HAL_clk_xbl_EnableSource(&nHAL,
                                  HAL_CLK_SOURCE_DISABLE_MODE_NORMAL,
                                  NULL))
    {
      return FALSE;
    }
  }

  pSource->nFlags |= CLOCK_FLAG_ENABLED;

  return TRUE;
}


/* ============================================================================
**  Function : Clock_EnableSource
** ============================================================================
*/

bool Clock_EnableSource
(
  ClockSourceNodeType             *pSource,
  ClockMasterType                  eVoteMaster,
  const ClockSourceFreqConfigType *pConfig
)
{
  bool bResult = TRUE;

  if (!pSource || eVoteMaster >= CLOCK_MASTER_MAX_SIZE)
  {
    return FALSE;
  }

  if (pSource->nAddr != 0 &&
      (!(pSource->nFlags & CLOCK_FLAG_ENABLED)))
  {
    bResult = Clock_EnablePLL(pSource, eVoteMaster, pConfig);
  }

  return bResult;
}


/* =========================================================================
**  Function : Clock_IsBSPSupported
** =========================================================================*/
/**
  See ClockDriver.h
*/

bool Clock_IsBSPSupported
(
  const ClockHWVersionType *pHWVersion
)
{
  uint32_t nHWVersion, nHWMaxVersion, nHWMinVersion;

  /*-----------------------------------------------------------------------*/
  /* Validate argument pointer is usable.                                  */
  /*-----------------------------------------------------------------------*/

  if (pHWVersion == NULL)
  {
    return FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate chip family. If not provided then we do not check.           */
  /*-----------------------------------------------------------------------*/

  if ((pHWVersion->eChipInfoFamily != 0) &&
      (pHWVersion->eChipInfoFamily != Clock_GetChipFamily()))
  {
    return FALSE;
  }

  /*-----------------------------------------------------------------------*/
  /* Get the actual hardware revision.                                     */
  /*-----------------------------------------------------------------------*/

  nHWVersion = Clock_GetChipVersion();

  nHWMinVersion =
    CHIPINFO_VERSION(pHWVersion->Min.nMajor, pHWVersion->Min.nMinor);
  nHWMaxVersion =
    CHIPINFO_VERSION(pHWVersion->Max.nMajor, pHWVersion->Max.nMinor);

  /*-----------------------------------------------------------------------*/
  /* No chip version data implies support in all HW versions.              */
  /*-----------------------------------------------------------------------*/

  if ((nHWMinVersion == 0) && (nHWMaxVersion == 0))
  {
    return TRUE;
  }

  /*-----------------------------------------------------------------------*/
  /* Validate the HW version falls within the min/max.                     */
  /*-----------------------------------------------------------------------*/

  if ((nHWVersion >= nHWMinVersion) && (nHWVersion < nHWMaxVersion))
  {
    return TRUE;
  }
  else
  {
    return FALSE;
  }
}


/* =========================================================================
**  Function : Clock_GetSourceCalConfig
** =========================================================================*/
/**
  Get source calibration configuration.
*/

static const ClockSourceFreqConfigType *Clock_GetSourceCalConfig
(
  ClockSourceNodeType *pSource
)
{
  const ClockSourceFreqConfigType *pCalConfig;
  uint32_t i;

  for (i = 0; i < pSource->nCalibrationFreqConfigLen; i++)
  {
    pCalConfig = &pSource->pCalibrationFreqConfig[i];
    if (Clock_IsBSPSupported(&pCalConfig->HWVersion))
    {
      return pCalConfig;
    }
  }

  return NULL;
}


/* =========================================================================
**  Function : Clock_GetSourceRegSettings
** =========================================================================*/
/**
  See ClockDriver.h
*/

static const HAL_clk_xbl_SourceRegSettingsType *Clock_GetSourceRegSettings
(
  ClockSourceNodeType *pSource
)
{
  const ClockSourceRegSettingsType *pRegSettings;
  uint32_t i;

  for (i = 0; i < pSource->nRegSettingsLen; i++)
  {
    pRegSettings = &pSource->pRegSettings[i];
    if (Clock_IsBSPSupported(&pRegSettings->HWVersion))
    {
      return &pRegSettings->HALSettings;
    }
  }

  return NULL;
}


/* =========================================================================
**  Function : Clock_GetDomainFrequency
** =========================================================================*/
/**
  See ClockDriver.h
*/

uint32_t Clock_GetDomainFrequency
(
  ClockDomainNodeType *pDomain
)
{
  if (!pDomain->pActiveMuxConfig)
  {
    return 0;
  }

  return pDomain->pActiveMuxConfig->nFreqHz;
}


/* =========================================================================
**  Function : Clock_GetDomainFreqConfig
** =========================================================================*/
/**
  See ClockDriver.h
*/

const ClockMuxConfigType *Clock_GetDomainFreqConfig
(
  ClockDomainNodeType *pDomain, 
  uint32_t             nFreqKHz,
  ClockFrequencyType   eMatch
)
{
  ClockMuxConfigType *pConfig;
  uint32_t nFreqHz = nFreqKHz * 1000;
  uint32_t i;
  
  if (eMatch == CLOCK_FREQUENCY_KHZ_AT_LEAST)
  {
    for (i = 0; i < pDomain->nBSPLen; i++)
    {
      pConfig = &pDomain->aBSP[i];
      if (pConfig->nFreqHz >= nFreqHz &&
          Clock_IsBSPSupported(&pConfig->HWVersion))
      {
        return pConfig;
      }
    }
  }
  else if (eMatch == CLOCK_FREQUENCY_KHZ_AT_MOST)
  {
    for (i = pDomain->nBSPLen - 1; i >= 0; i--)
    {
      pConfig = &pDomain->aBSP[i];
      if (pConfig->nFreqHz <= nFreqHz &&
          Clock_IsBSPSupported(&pConfig->HWVersion))
      {
        return pConfig;
      }
    }
  }

  return NULL;
}


/* =========================================================================
**  Function : Clock_GetDomainFMaxConfig
** =========================================================================*/
/**
  See ClockDriver.h
*/

ClockMuxConfigType *Clock_GetDomainFMaxConfig
(
  ClockDomainNodeType *pDomain, 
  rail_voltage_level   eCorner
)
{
  ClockMuxConfigType *pConfig;
  uint32_t i;

  for (i = pDomain->nBSPLen - 1; i >= 0; i--)
  {
    pConfig = &pDomain->aBSP[i];
    if (pConfig->eVRegLevel <= eCorner &&
        Clock_IsBSPSupported(&pConfig->HWVersion))
    {
      return pConfig;
    }
  }

  return NULL;
}


/* =========================================================================
**  Function : Clock_ConfigMux
** =========================================================================*/
/**
  See ClockDriver.h
*/

static bool Clock_ConfigMux (uintptr_t nCmdRCGRAddr, const HAL_clk_xbl_ClockMuxConfigType *pConfig)
{
  uintptr_t nCfgRCGRAddr;
  uint32_t nCmdRCGRVal,  nCfgRCGRVal;
  uintptr_t nMAddr, nNAddr, nDAddr;
  uint32_t nTimeout = 0;

  nCmdRCGRVal  = inpdw(nCmdRCGRAddr);
  nCfgRCGRAddr = nCmdRCGRAddr + CLOCK_CFG_REG_OFFSET; 
  nCfgRCGRVal  = inpdw(nCfgRCGRAddr);

  /* Clear the fields. */
  nCfgRCGRVal &= ~(CLOCK_CFG_RCGR_SRC_SEL_FMSK |
                  CLOCK_CFG_RCGR_SRC_DIV_FMSK |
                  CLOCK_CFG_RCGR_MODE_FMSK);

  /* Program the source and divider values. */
  nCfgRCGRVal |= (pConfig->nMuxSel << CLOCK_CFG_RCGR_SRC_SEL_SHFT)
                  & CLOCK_CFG_RCGR_SRC_SEL_FMSK;
  nCfgRCGRVal |= ((HALF_DIVIDER(pConfig) << CLOCK_CFG_RCGR_SRC_DIV_SHFT)
                  & CLOCK_CFG_RCGR_SRC_DIV_FMSK);

  /* Set MND counter mode depending on if it is in use. */
  if (pConfig->nM != 0 && (pConfig->nM < pConfig->nN))
  {
    nMAddr = nCmdRCGRAddr + CLOCK_M_REG_OFFSET;
    nNAddr = nCmdRCGRAddr + CLOCK_N_REG_OFFSET;
    nDAddr = nCmdRCGRAddr + CLOCK_D_REG_OFFSET;

    outpdw(nMAddr, pConfig->nM);
    outpdw(nNAddr, NOT_N_MINUS_M(pConfig));
    outpdw(nDAddr, NOT_2D(pConfig));

    nCfgRCGRVal |= ((CLOCK_CFG_CFG_DUAL_EDGE_MODE_VAL << CLOCK_CFG_RCGR_MODE_SHFT)
                    & CLOCK_CFG_RCGR_MODE_FMSK);
  }

  /* Write the final CFG register value. */
  outpdw(nCfgRCGRAddr, nCfgRCGRVal);

  /* Trigger the update. */
  nCmdRCGRVal |= CLOCK_CMD_CFG_UPDATE_FMSK;
  outpdw(nCmdRCGRAddr, nCmdRCGRVal);

  /* Wait until update finishes. */
  while ( inpdw(nCmdRCGRAddr) & CLOCK_CMD_CFG_UPDATE_FMSK )
  {
    if ( nTimeout++ >= CLOCK_UPDATE_TIMEOUT_US )
    {
      return FALSE;
    }

    busywait(1);
  }

  return TRUE;
}


/* =========================================================================
**  Function : Clock_SetDomainFreqConfig
** =========================================================================*/
/**
  See ClockDriver.h
*/

bool Clock_SetDomainFreqConfig
(
  ClockDomainNodeType      *pDomain,
  const ClockMuxConfigType *pConfig
)
{
  const ClockSourceFreqConfigType *pSrcConfig = NULL;
  ClockSourceNodeType *pSource = NULL;

  /* Validate args. */
  CORE_VERIFY_PTR(pDomain);
  CORE_VERIFY_PTR(pConfig);

  /* Short-circuit any redundant configuration requests. */
  if (pConfig == pDomain->pActiveMuxConfig)
  {
    return TRUE;
  }

  /* Validate array index - no BSP entry for XO. */
  if (SRC_IDX_NULL == pConfig->nSourceIdx)
  {
    pSource = NULL;
  }
  else if (pConfig->nSourceIdx >= ClockBSP.nNumSources)
  {
    return FALSE;
  }
  else
  {
    pSource = ClockBSP.aSources[pConfig->nSourceIdx];
  }

  /* Enable non-XO sources. */
  if (pSource)
  {
    if (pConfig->nSourceFreqConfigIdx < pSource->nBSPLen)
    {
      pSrcConfig = &pSource->aBSP[pConfig->nSourceFreqConfigIdx];
    }

    if (!Clock_EnableSource(pSource, pDomain->eMaster, pSrcConfig))
    {
      return FALSE;
    }
  }

  if (pDomain->nGenType & CLOCK_DOMAIN_TYPE_RCG)
  {
    Clock_ConfigMux(pDomain->nCGRAddr, &pConfig->HALConfig);
  }
  else
  {
    outpdw((uintptr_t)(pDomain->nCGRAddr), pConfig->HALConfig.nMuxSel);
  }
  

  pDomain->pActiveMuxConfig = pConfig;

  return TRUE;
}


/* =========================================================================
**  Function : Clock_SetDomainFreq
** =========================================================================*/
/**
  See ClockDriver.h
*/

bool Clock_SetDomainFreq
(
  ClockDomainNodeType *pDomain,
  uint32_t             nFreqKHz,
  ClockFrequencyType   eMatch
)
{
  const ClockMuxConfigType *pConfig;

  pConfig = Clock_GetDomainFreqConfig(pDomain, nFreqKHz, eMatch);

  CORE_VERIFY(pConfig);

  return Clock_SetDomainFreqConfig(pDomain, pConfig);
}


/* =========================================================================
**  Function : Clock_SetDomainFMax
** =========================================================================*/
/**
  See ClockDriver.h
*/

bool Clock_SetDomainFMax
(
  ClockDomainNodeType *pDomain,
  rail_voltage_level   eCorner
)
{
  ClockMuxConfigType *pConfig;

  pConfig = Clock_GetDomainFMaxConfig(pDomain, eCorner);
  if (!pConfig)
  {
    return FALSE;
  }

  return Clock_SetDomainFreqConfig(pDomain, pConfig);
}


/* =========================================================================
**  Function : Clock_SetDomainBootFMax
** =========================================================================*/
/**
  See ClockDriver.h
*/

void Clock_SetDomainBootFMax
(
  ClockDomainNodeType *pDomain
)
{
  CORE_VERIFY(Clock_SetDomainFMax(pDomain, geBootCorner));
}


/* =========================================================================
**  Function : Clock_EnableBootClocks
** =========================================================================*/
/**
  Enable boot clocks and GDSCs.
*/
void Clock_EnableBootClocks
(
  void
)
{
  uintptr_t nAddr;
  uint32_t nMask;
  uint32_t i;

  for (i = 0; i < ClockBSP.nNumPDEnables; i++)
  {
    nAddr = ClockBSP.aPDEnable[i];
    outpdw(nAddr, inpdw(nAddr) & ~0x1);
  }

  for (i = 0; i < ClockBSP.nNumBranchEnables; i++)
  {
    nAddr = ClockBSP.aBranchEnable[i];
    outpdw(nAddr, inpdw(nAddr) | 0x1);
  }

  for (i = 0; i < ClockBSP.nNumBranchVotes; i++)
  {
    nAddr = ClockBSP.aBranchVote[i].nAddr;
    nMask = ClockBSP.aBranchVote[i].nMask;
    outpdw(nAddr, inpdw(nAddr) | nMask);
  }
}

  
/* =========================================================================
**  Function : Clock_EnableClockInternal
** =========================================================================*/
/*!
    Enable a Clock and poll for CLK_OFF BIT. 

    @param CBCR_addr - Address of the CBCR register
    TRUE -- CBCR programming successful.
    FALSE -- CBCR programming failed.

    @dependencies
    None.

    @sa None
*/
bool Clock_EnableClockInternal
(
  uintptr_t nCBCRAddr
)
{
  CORE_VERIFY(nCBCRAddr);

  outpdw(nCBCRAddr, inpdw(nCBCRAddr) | CLK_ENABLE_MSK);
 
  /*
   * Poll for clock on.
   */
  if (!(inpdw(nCBCRAddr) & CLK_HW_CTL_MSK))
  {
    while((inpdw(nCBCRAddr) & CLK_OFF_MSK) != 0)
    {
      busywait(1);
    }
  }

  return TRUE;
}


/* =========================================================================
**  Function : Clock_DisableClockInternal
** =========================================================================*/
/*!
    Disable a Clock.

    @param CBCR_addr - Address of the CBCR register
    TRUE -- CBCR programming successful.
    FALSE -- CBCR programming failed.

    @dependencies
    None.

    @sa None
*/
bool Clock_DisableClockInternal
(
  uintptr_t nCBCRAddr
)
{
  CORE_VERIFY(nCBCRAddr);

  outpdw(nCBCRAddr, inpdw(nCBCRAddr) & ~CLK_ENABLE_MSK);

  return TRUE;
}


/* ===========================================================================
**  Clock_EnablePowerDomainInternal
** ======================================================================== */
/*!
    Enable a GDSC. 

    @param nGDSCRAddr - Address of the GDSCR register
    TRUE -- GDSCR programming successful.
    FALSE -- GDSCR programming failed.

    @dependencies
    None.

    @sa None
*/
bool Clock_EnablePowerDomainInternal
(
  uintptr_t nGDSCRAddr
)
{
  uint32_t nVal;
  uint32_t nTimeout = 0;

  CORE_VERIFY(nGDSCRAddr);

  nVal  = inpdw(nGDSCRAddr);

  /*
   * Clear the SW PD collapse bit
   */
  nVal &= ~CLK_GDSCR_SW_COLLAPSE_MSK;
  outpdw(nGDSCRAddr, nVal);

  /*
   * Wait for PD ON
   */
  while( !(inpdw(nGDSCRAddr) & CLK_GDSCR_PWR_ON_MSK) )
  {
    if (nTimeout++ >= CLK_GDSCR_TIMEOUT_US)
    {
      return FALSE;
    }
    busywait(1);
  }
  return TRUE;

} /* END Clock_EnablePowerDomainInternal */


/* ===========================================================================
**  Clock_DisablePowerDomainInternal
** ======================================================================== */
/*!
    Disable a GDSC. 

    @param nGDSCRAddr - Address of the GDSCR register
    TRUE -- GDSCR programming successful.
    FALSE -- GDSCR programming failed.

    @dependencies
    None.

    @sa None
*/
bool Clock_DisablePowerDomainInternal
(
  uintptr_t nGDSCRAddr
)
{
  uint32_t nVal;

  CORE_VERIFY(nGDSCRAddr);

  nVal  = inpdw(nGDSCRAddr);

  /* Set the SW PD collapse bit */
  nVal |= CLK_GDSCR_SW_COLLAPSE_MSK;
  outpdw(nGDSCRAddr, nVal);

  return TRUE;
} /* END Clock_DisablePowerDomainInternal */


/* =========================================================================
**  Function : Clock_EnableClock
** =========================================================================*/
/**
  Enable clock branch
*/
ClockResult Clock_EnableClock
(
  ClockNodeType *pClock
)
{
  uintptr_t nCBCRAddr = 0;
  uintptr_t nVoteAddr = 0;
  uint32_t nVoteMask = 0;

  CORE_VERIFY(pClock);

  nCBCRAddr = pClock->nBranchAddr;
  nVoteAddr = pClock->mHWVotable.nAddr;
  nVoteMask = pClock->mHWVotable.nMask;
  
  if(nVoteAddr && nVoteMask)
  {
    outpdw(nVoteAddr, inpdw(nVoteAddr) | nVoteMask);
  }
  else
  {
    outpdw(nCBCRAddr, inpdw(nCBCRAddr) | CLK_ENABLE_MSK);
  }  

  if (!(inpdw(nCBCRAddr) & CLK_HW_CTL_MSK) && 
      !(pClock->nFlags & CLOCK_FLAG_NO_POLL_AFTER_ENABLE))
  {
    while((inpdw(nCBCRAddr) & CLK_OFF_MSK) != 0)
    {
      busywait(1);
    }
  }

  return CLOCK_SUCCESS;

} /* END Clock_EnableClock */


/* =========================================================================
**  Function : Clock_DisableClock
** =========================================================================*/
/**
  Disable clock branch
*/
ClockResult Clock_DisableClock
(
  ClockNodeType *pClock
)
{
  uintptr_t nCBCRAddr = 0;
  uintptr_t nVoteAddr = 0;
  uint32_t nVoteMask = 0;

  CORE_VERIFY(pClock);

  nCBCRAddr = pClock->nBranchAddr;
  nVoteAddr = pClock->mHWVotable.nAddr;
  nVoteMask = pClock->mHWVotable.nMask;
  
  if(nVoteAddr && nVoteMask)
  {
    outpdw(nVoteAddr, inpdw(nVoteAddr) & ~nVoteMask);
  }
  else
  {
    outpdw(nCBCRAddr, inpdw(nCBCRAddr) & ~CLK_ENABLE_MSK);
  }

  return CLOCK_SUCCESS;

} /* END Clock_DisableClock */


/* =========================================================================
**  Function : Clock_IsClockOn
** =========================================================================*/
/**
  See Clock.h
*/
static ClockResult Clock_IsClockOn
(
  ClockNodeType *pClock,
  bool          *pbIsOn
)
{
  uintptr_t nCBCRAddr = 0;

  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  nCBCRAddr = pClock->nBranchAddr;

  *pbIsOn = ((inpdw(nCBCRAddr) & CLK_OFF_MSK) >> CLK_OFF_SHFT) == 0;

  return CLOCK_SUCCESS;

} /* END Clock_DisableClock */

/* ===========================================================================
**  Clock_PowerDomainEnable
** ======================================================================== */
/**
  Enable a Power Domain
*/
ClockResult Clock_EnablePowerDomain
(
  ClockPowerDomainNodeType *pPowerDomain
)
{
  uint32_t nTimeout = 0;
  uint32_t nVal = 0;
  uintptr_t nGDSCRAddr = 0;

  CORE_VERIFY(pPowerDomain);
  
  nGDSCRAddr = pPowerDomain->HALPowerDomain.nGDSCRAddr;
  nVal  = inpdw(nGDSCRAddr);

  /*
   * Clear the SW PD collapse bit
   */
  nVal &= ~CLK_GDSCR_SW_COLLAPSE_MSK;
  outpdw(nGDSCRAddr, nVal);

  /*
   * Wait for PD ON
   */
  while( !(inpdw(nGDSCRAddr) & CLK_GDSCR_PWR_ON_MSK) )
  {
    if (nTimeout++ >= CLK_GDSCR_TIMEOUT_US)
    {
      return FALSE;
    }
    busywait(1);
  }

  return CLOCK_SUCCESS;

} /* END Clock_PowerDomainEnable */


/* ===========================================================================
**  Clock_PowerDomainDisable
** ======================================================================== */
/**
  Disable a Power Domain
*/
ClockResult Clock_DisablePowerDomain
(
  ClockPowerDomainNodeType *pPowerDomain
)
{
  uint32_t nVal = 0;
  uintptr_t nGDSCRAddr = 0;

  CORE_VERIFY(pPowerDomain);

  nGDSCRAddr = pPowerDomain->HALPowerDomain.nGDSCRAddr;
  nVal  = inpdw(nGDSCRAddr);

  /* Set the SW PD collapse bit */
  nVal |= CLK_GDSCR_SW_COLLAPSE_MSK;
  outpdw(nGDSCRAddr, nVal);

  return CLOCK_SUCCESS; 
} /* END Clock_PowerDomainDisable */


/* =========================================================================
**  Function : Clock_GetClockId
** =========================================================================*/
/**
  See ClockDriver.h
*/
static ClockResult Clock_GetClockId
(
  const char  *szName,
  ClockIdType *pId
)
{
  uint32_t i;

  if (!szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  for (i = 0; i < ClockBSP.nNumClocks; i++)
  {
    if (!strcmp(szName, ClockBSP.aClocks[i].szName))
    {
      *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_CLOCK, i);
      return CLOCK_SUCCESS;
    }
  }

  *pId = CLOCK_ID_INVALID;
  return CLOCK_ERROR_NOT_FOUND;
} /* END Clock_GetClockId */


/* =========================================================================
**  Function : Clock_GetPowerDomainId
** =========================================================================*/
/**
  See ClockDriver.h
*/
static ClockResult Clock_GetPowerDomainId
(
  const char  *szName,
  ClockIdType *pId
)
{
  uint32_t i;

  if (!szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  for (i = 0; i < ClockBSP.nNumPowerDomains; i++)
  {
    if (!strcmp(szName, ClockBSP.aPowerDomains[i].szName))
    {
      *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_POWERDOMAIN, i);
      return CLOCK_SUCCESS;
    }
  }

  *pId = CLOCK_ID_INVALID;
  return CLOCK_ERROR_NOT_FOUND;
} /* END Clock_GetPowerDomainId */


/* =========================================================================
**  Function : Clock_GetClockGroupId
** =========================================================================*/
/**
  See ClockDriver.h
*/
static ClockResult Clock_GetClockGroupId
(
  const char  *szName,
  ClockIdType *pId
)
{
  uint32_t i;

  if (!szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  for (i = 0; i < ClockBSP.nNumClockGroups; i++)
  {
    if (!strcmp(szName, ClockBSP.aClockGroups[i].szName))
    {
      *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_FUNCGROUP, i);
      return CLOCK_SUCCESS;
    }
  }

  *pId = CLOCK_ID_INVALID;
  return CLOCK_ERROR_NOT_FOUND;
} /* END Clock_GetClockId */


/* =========================================================================
**  Function : Clock_GetDividerId
** =========================================================================*/
/**
  Get ID of a divider
*/
static ClockResult Clock_GetDividerId
(
  const char  *szName,
  ClockIdType *pId
)
{
  uint32_t i;

  if (!szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  for (i = 0; i < ClockBSP.nNumDividers; i++)
  {
    if (!strcmp(szName, ClockBSP.aDividers[i].szName))
    {
      *pId = CLOCK_MAKE_ID(CLOCK_ID_CATEGORY_DIVIDER, i);
      return CLOCK_SUCCESS;
    }
  }

  *pId = CLOCK_ID_INVALID;
  return CLOCK_ERROR_NOT_FOUND;
} /* END Clock_GetDividerId */


/*=========================================================================
**  Function : Clock_GetClockNode
** =========================================================================*/
/**
  Get pointer to a particular Clock Node based to Clock ID.
*/

static ClockNodeType *Clock_GetClockNode
(
  ClockIdType ClockId
)
{
  ClockIdCategoryType  nCat   = CLOCK_GET_ID_CATEGORY(ClockId);
  uint32_t             nIndex = CLOCK_GET_ID_INDEX(ClockId);

  if (nCat == CLOCK_ID_CATEGORY_CLOCK &&
      nIndex < ClockBSP.nNumClocks)
  {
    return &ClockBSP.aClocks[nIndex];
  }

  return NULL;
} /* END Clock_GetClockNode */


/*=========================================================================
**  Function : Clock_GetPowerDomainNode
** =========================================================================*/
/**
  Get pointer to a particular Power Domain Node based to Clock ID.
*/

static ClockPowerDomainNodeType *Clock_GetPowerDomainNode
(
  ClockIdType ClockId
)
{
  ClockIdCategoryType  nCat   = CLOCK_GET_ID_CATEGORY(ClockId);
  uint32_t             nIndex = CLOCK_GET_ID_INDEX(ClockId);

  if (nCat == CLOCK_ID_CATEGORY_POWERDOMAIN &&
      nIndex < ClockBSP.nNumPowerDomains)
  {
    return &ClockBSP.aPowerDomains[nIndex];
  }

  return NULL;
} /* END Clock_GetPowerDomainNode */


/*=========================================================================
**  Function : Clock_GetClockGroupNode
** =========================================================================*/
/**
  Get pointer to a particular Clock Group based to Clock ID.
*/

static ClockGroupType *Clock_GetClockGroupNode
(
  ClockIdType ClockId
)
{
  ClockIdCategoryType  nCat   = CLOCK_GET_ID_CATEGORY(ClockId);
  uint32_t             nIndex = CLOCK_GET_ID_INDEX(ClockId);

  if (nCat == CLOCK_ID_CATEGORY_FUNCGROUP &&
      nIndex < ClockBSP.nNumClockGroups)
  {
    return &ClockBSP.aClockGroups[nIndex];
  }

  return NULL;
} /* END Clock_GetClockGroupNode */


/*=========================================================================
**  Function : Clock_GetDividerNode
** =========================================================================*/
/**
  Get pointer to a particular Divider Node based to Clock ID.
*/

static ClockDividerNodeType *Clock_GetDividerNode
(
  ClockIdType ClockId
)
{
  ClockIdCategoryType  nCat   = CLOCK_GET_ID_CATEGORY(ClockId);
  uint32_t             nIndex = CLOCK_GET_ID_INDEX(ClockId);

  if (nCat == CLOCK_ID_CATEGORY_DIVIDER &&
      nIndex < ClockBSP.nNumDividers)
  {
    return &ClockBSP.aDividers[nIndex];
  }

  return NULL;
} /* END Clock_GetDividerNode */


/* =========================================================================
**  Function : Clock_EnableClockGroupEx
** =========================================================================*/
/**
  Enable a clock group.
*/
static ClockResult Clock_EnableClockGroupEx
(
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  uint32_t i;
  ClockResult eResult = CLOCK_SUCCESS;

  ClockGroupType *pClockGroup = Clock_GetClockGroupNode(ClockId);

  CORE_VERIFY(pClockGroup);
  
  /*
   * Enable Power Domains.
   */
  for (i = 0; i < pClockGroup->nPowerDomains; i++)
  {
    if (!Clock_EnablePowerDomainInternal(pClockGroup->aPowerDomains[i]))
    {
      return CLOCK_ERROR;
    }
  }
  
  /*
   * Enable Clocks.
   */
  for (i = 0; i < pClockGroup->nClocks; i++)
  {
    eResult = Clock_EnableClock(&pClockGroup->aClocks[i]);
    if (eResult != CLOCK_SUCCESS)
    {
      return eResult;
    }
  }

  return CLOCK_SUCCESS;

} /* END Clock_EnableClockGroupEx */


/* =========================================================================
**  Function : Clock_DisableClockGroupEx
** =========================================================================*/
/**
  Disable a clock group.
*/
static ClockResult Clock_DisableClockGroupEx
(
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  uint32_t i;
  ClockResult eResult = CLOCK_SUCCESS;

  ClockGroupType *pClockGroup = Clock_GetClockGroupNode(ClockId);

  CORE_VERIFY(pClockGroup);
  
  /*
   * Disable Clocks.
   */
  for (i = 0; i < pClockGroup->nClocks; i++)
  {
    eResult = Clock_DisableClock(&pClockGroup->aClocks[i]);
    if (eResult != CLOCK_SUCCESS)
    {
      return eResult;
    }
  }
    
  /*
   * Disable Power Domains.
   */
  for (i = 0; i < pClockGroup->nPowerDomains; i++)
  {
    eResult = Clock_DisablePowerDomainInternal(pClockGroup->aPowerDomains[i]);
    if (eResult != CLOCK_SUCCESS)
    {
      return eResult;
    }
  }

  return CLOCK_SUCCESS;

} /* END Clock_DisableClockGroupEx */


/* =========================================================================
**  Function : Clock_SetClockGroupFrequencyEx
** =========================================================================*/
/**
  Set frequency of clock group.
*/
static ClockResult Clock_SetClockGroupFrequencyEx
(
  ClockIdType          ClockId,
  uint32_t             nFreq,
  ClockFrequencyType   eMatch,
  uint32_t             nFlags
)
{
  uint32_t i =0;
  rail_voltage_level eCorner;
  ClockGroupType *pClockGroup = Clock_GetClockGroupNode(ClockId);

  CORE_VERIFY(pClockGroup);

  if (eMatch == CLOCK_FREQUENCY_KHZ_AT_LEAST ||
      eMatch == CLOCK_FREQUENCY_KHZ_AT_MOST)
  {
    if (pClockGroup->nDomains > 1)
    {
      return CLOCK_ERROR_NOT_SUPPORTED;
    }

    if (!Clock_SetDomainFreq(pClockGroup->aDomains[0], nFreq, eMatch))
    {
      return CLOCK_ERROR;
    }
  }
  else if (eMatch == CLOCK_FREQUENCY_FMAX)
  {
    eCorner = (rail_voltage_level)nFreq;

    for (i = 0; i < pClockGroup->nDomains; i++)
    {
      if (!Clock_SetDomainFMax(pClockGroup->aDomains[i], eCorner))
      {
        return CLOCK_ERROR;
      }
    }
  }
  else
  {
    return CLOCK_ERROR_NOT_SUPPORTED;
  }

  return CLOCK_SUCCESS;
}


/* =========================================================================
**  Function : Clock_IsClockEnabled
** =========================================================================*/
/**
  See Clock.h
*/
static ClockResult Clock_IsClockEnabled
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool      *pbIsEnabled
)
{
  uintnt nCBCRAddr;
  ClockNodeType *pClock = Clock_GetClockNode(ClockId);

  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  nCBCRAddr = pClock->nBranchAddr;
  *pbIsEnabled = inpdw(nCBCRAddr) & 0x1;

  return CLOCK_SUCCESS;
} /* END Clock_IsClockEnabled */


/* =========================================================================
**  Function : Clock_IsClockGroupOn
** =========================================================================*/
/**
  Checks if a clock group is on.
*/
static ClockResult Clock_IsClockGroupOn
(
  ClockIdType  ClockId,
  bool         *pbIsOn
)
{
  ClockResult eResult = CLOCK_SUCCESS;
  uint32_t i;

  ClockGroupType *pClockGroup = Clock_GetClockGroupNode(ClockId);

  if (!pClockGroup)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }
  
  *pbIsOn = TRUE;

  for(i = 0; i < pClockGroup->nClocks; i++)
  {
    if (!(pClockGroup->aClocks[i].nFlags & CLOCK_FLAG_NO_POLL_AFTER_ENABLE))
    {
      eResult = Clock_IsClockOn(&pClockGroup->aClocks[i], pbIsOn);
      if (eResult != CLOCK_SUCCESS ||
          !*pbIsOn)
      {
        return eResult;
      }
    }
  }

  return eResult;
}

/* =========================================================================
**  Function : Clock_ResetGroup
** =========================================================================*/
/**
  Resets a functional group.
*/
static ClockResult Clock_ResetGroup
(
  ClockIdType    ClockId,
  ClockResetType eReset
)
{
  ClockGroupType *pClockGroup = Clock_GetClockGroupNode(ClockId);

  CORE_VERIFY(pClockGroup);

  if (eReset == CLOCK_RESET_ASSERT || eReset == CLOCK_RESET_PULSE)
  {
    outpdw((uintptr_t)pClockGroup->nResetAddr, 1);
  }

  busywait(1);

  if (eReset == CLOCK_RESET_DEASSERT || eReset == CLOCK_RESET_PULSE)
  {
    outpdw((uintptr_t)pClockGroup->nResetAddr, 0);
  }

  busywait(1);

  return CLOCK_SUCCESS;
}

/* =========================================================================
**  Function : Clock_ConfigDivider
** =========================================================================*/
/**
  Configure a divider.
*/
void Clock_ConfigDivider
(
  HAL_clk_xbl_DividerDescType *pmDividerDesc,
  uint32                   nDiv
)
{
  uintnt nAddr;
  uint32 nVal;

  nAddr = pmDividerDesc->nAddr;

  /*
   * Sanity check
   */
  if (nAddr == 0)
  {
    return;
  }

  nVal = inpdw(nAddr);
  if (nDiv <= 1)
  {
    nDiv = 0;
  }
  else
  {
    nDiv--;
  }

  /*
   * Clear previous divider value.
   */
  nVal &= ~CLK_CDIVR_CLK_DIV_FMSK;

  /*
   * Set divider value.
   */
  nVal |= nDiv & CLK_CDIVR_CLK_DIV_FMSK;

  /*
   * Write final value.
   */
  outpdw(nAddr, nVal);

} /* END HAL_clk_xbl_GenericDividerConfigDivider */


/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/

/* =========================================================================
**  Function : Clock_Init
** =========================================================================*/
/**
  See ClockBoot.h
*/
ClockResult Clock_Init()
{
  ClockResult eResult = CLOCK_SUCCESS;

  if (gbInitialized)
  {
    return CLOCK_SUCCESS;
  }

  /*
   * Set Boot Corner
   */
  geBootCorner = CLOCK_BOOT_CORNER;
  
  /*
   * Initialize Target.
   */
  eResult = Clock_InitTarget(geBootCorner);
  if (eResult != CLOCK_SUCCESS)
  {
    return eResult;
  }

  gbInitialized = TRUE;

  return CLOCK_SUCCESS;
}


/* =========================================================================
**  Function : Clock_Attach
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_Attach
(
  ClockHandle *pHandle,
  const char  *szName
)
{
  if (!pHandle)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  *pHandle = CLK_GLOBAL_HANDLE;

  return CLOCK_SUCCESS;
}


/* =========================================================================
**  Function : Clock_Detach
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_Detach
(
  ClockHandle hClient
)
{
  return CLOCK_SUCCESS;
}


/* =========================================================================
**  Function : Clock_GetId
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_GetId
(
  ClockHandle  hClient,
  const char  *szName,
  ClockIdType *pId
)
{
  ClockIdType   nId;
  ClockGetIdFn  fGetId;
  ClockResult   eResult;
  uint32_t      i;

  if (!hClient || !szName || !pId)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  for (i = 0; i < SIZEOF_ARRAY(ClockGetIdFunctions); i++)
  {
    fGetId = ClockGetIdFunctions[i];
    eResult = fGetId(szName, &nId);
    if (eResult == CLOCK_SUCCESS)
    {
      *pId = nId;
      return CLOCK_SUCCESS;
    }
  }

  *pId = CLOCK_ID_INVALID;
  return CLOCK_ERROR_NOT_FOUND;
}


/* =========================================================================
**  Function : Clock_EnableEx
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_EnableEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_FUNCGROUP:
      return Clock_EnableClockGroupEx(ClockId, nFlags);

    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_EnableClock(Clock_GetClockNode(ClockId));
    
    case CLOCK_ID_CATEGORY_POWERDOMAIN:
      return Clock_EnablePowerDomain(Clock_GetPowerDomainNode(ClockId));

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }
} /* END Clock_EnableEx */


/* =========================================================================
**  Function : Clock_DisableEx
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_DisableEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFlags
)
{
  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_FUNCGROUP:
      return Clock_DisableClockGroupEx(ClockId, nFlags);

    case CLOCK_ID_CATEGORY_CLOCK:
      return Clock_DisableClock(Clock_GetClockNode(ClockId));
    
    case CLOCK_ID_CATEGORY_POWERDOMAIN:
      return Clock_DisablePowerDomain(Clock_GetPowerDomainNode(ClockId));

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }
}


/* =========================================================================
**  Function : Clock_SetFrequencyEx
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_SetFrequencyEx
(
  ClockHandle          hClient,
  ClockIdType          ClockId,
  uint32_t             nFreq,
  ClockFrequencyType   eMatch,
  uint32_t            *pnResultFreq,
  uint32_t             nFlags
)
{
  ClockNodeType *pClock;

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_FUNCGROUP:
      return Clock_SetClockGroupFrequencyEx(
               ClockId, nFreq, eMatch, nFlags);
    
    case CLOCK_ID_CATEGORY_CLOCK:
      pClock = Clock_GetClockNode(ClockId);
      CORE_VERIFY(pClock);
      CORE_VERIFY(pClock->pDomain);
      CORE_VERIFY(Clock_SetDomainFreq(pClock->pDomain, nFreq, eMatch));
      return CLOCK_SUCCESS;

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }
}


/* =========================================================================
**  Function : Clock_GetFrequency
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_GetFrequency
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  uint32_t    *pnFrequencyHz
)
{
  ClockNodeType  *pClock;
  ClockGroupType *pClockGroup;

  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_CLOCK:
      pClock = Clock_GetClockNode(ClockId);
      CORE_VERIFY(pClock);
      CORE_VERIFY(pClock->pDomain);
      *pnFrequencyHz = Clock_GetDomainFrequency(pClock->pDomain);
      return CLOCK_SUCCESS;

    case CLOCK_ID_CATEGORY_FUNCGROUP:
      pClockGroup = Clock_GetClockGroupNode(ClockId);
      CORE_VERIFY(pClockGroup);
      return Clock_GetGroupFrequency(pClockGroup, pnFrequencyHz);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED; 
  } 
  return CLOCK_SUCCESS;
}

/* =========================================================================
**  Function : Clock_SelectExternalSourceEx
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_SelectExternalSourceEx
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nFreqHz,
  uint32_t    nSource,
  uint32_t    nDiv2x,
  uint32_t    nM,
  uint32_t    nN,
  uint32_t    n2D,
  uint32_t    nFlags
)
{
  HAL_clk_xbl_ClockMuxConfigType muxConfig = {0};
  ClockNodeType *pClock = Clock_GetClockNode(ClockId);

  if (!pClock)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }

  muxConfig.nMuxSel = nSource;
  muxConfig.nDiv2x  = nDiv2x;
  muxConfig.nM      = nM;
  muxConfig.nN      = nN;

  Clock_ConfigMux(pClock->pDomain->nCGRAddr, &muxConfig);

  return CLOCK_SUCCESS;
} /* END Clock_SelectExternalClockSourceEx */


/* =========================================================================
**  Function : Clock_IsOn
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_IsOn
(
  ClockHandle  hClient,
  ClockIdType  ClockId,
  bool        *pbIsOn
)
{
  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_FUNCGROUP:
      return Clock_IsClockGroupOn(ClockId, pbIsOn);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }
} /* END Clock_IsEnabled */


/* =========================================================================
**  Function : Clock_SetDivider
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_SetDivider
(
  ClockHandle hClient,
  ClockIdType ClockId,
  uint32_t    nDivider
)
{
  ClockDividerNodeType *pDivider = Clock_GetDividerNode(ClockId);

  if (!hClient || !pDivider)
  {
    return CLOCK_ERROR_INVALID_PARAMETER;
  }
  
  Clock_ConfigDivider(&pDivider->HALDivider, nDivider);

  return CLOCK_SUCCESS;

} /* END Clock_SetDivider */


/* =========================================================================
**  Function : Clock_Reset
** =========================================================================*/
/**
  See Clock.h
*/
ClockResult Clock_Reset
(
  ClockHandle    hClient,
  ClockIdType    ClockId,
  ClockResetType eReset
)
{
  switch (CLOCK_GET_ID_CATEGORY(ClockId))
  {
    case CLOCK_ID_CATEGORY_FUNCGROUP:
      return Clock_ResetGroup(ClockId, eReset);

    default:
      return CLOCK_ERROR_NOT_SUPPORTED;
  }
} /* END Clock_Reset */

/*
==============================================================================

FILE:         HALCLKEPSS.c

DESCRIPTION:
  Implimentation for EPSS HAL module.

==============================================================================

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/HALclkLib/HALclkEPSS.c#1 $

==============================================================================
            Copyright (c) 2021, 2022 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/

/*============================================================================
                     INCLUDE FILES FOR MODULE
============================================================================*/

#include "HALclkEPSS.h"
#include "HALclkHWIO.h"
#include "ClockApps.h"

/*============================================================================
               FUNCTION DEFINITIONS FOR MODULE
============================================================================*/

static  boolean  HAL_clk_SetCorePerfLevel
(
  const HAL_clk_ClusterDescType   *pHALCluster,
  const uint32_t                   nCoreOffset,
  const uint32_t                   nVcIndex
)
{
  HAL_CLK_HWIO_OUTFI(pHALCluster, COREd_PERF_STATE_DESIRED, nCoreOffset, SW_INDEX, nVcIndex);
  return TRUE;
}

static  boolean  HAL_clk_SetL3PerfLevel
(
  const HAL_clk_ClusterDescType   *pHALCluster,
  const uint32_t                   nCoreOffset,
  const uint32_t                   nVcIndex
)
{
  HAL_CLK_HWIO_OUTFI(pHALCluster, COREd_L3_VOTING, nCoreOffset, VC, nVcIndex);
  return TRUE;
}

static  boolean  HAL_clk_GetCorePerfLevel
(
  const HAL_clk_ClusterDescType   *pHALCluster,
  const uint32_t                   nCoreOffset,
  uint32_t                        *pnVcIndex
)
{
  *pnVcIndex = HAL_CLK_HWIO_INFI(pHALCluster, COREd_PERF_STATE_DESIRED, nCoreOffset, SW_INDEX);
  return TRUE;
}

static  boolean  HAL_clk_GetL3PerfLevel
(
  const HAL_clk_ClusterDescType   *pHALCluster,
  const uint32_t                   nCoreOffset,
  uint32_t                        *pnVcIndex
)
{
  *pnVcIndex = HAL_CLK_HWIO_INFI(pHALCluster, COREd_L3_VOTING, nCoreOffset, VC);
  return TRUE;
}

static  boolean  HAL_clk_GetConfig
(
  const HAL_clk_ClusterDescType   *pHALCluster,
  const HAL_clk_ClusterConfigType  eConfig,
  void                            *pConfigValue
)
{
  switch (eConfig)
  {
    case HAL_CLK_APSS_DCVS_ENABLED:
      *((boolean*)pConfigValue) = (boolean)HAL_CLK_HWIO_INF(pHALCluster, CC_DCVS, EN);
      break;
    default:
      return FALSE;
  }
  return TRUE;
}

static  boolean  HAL_clk_GetActivePerfLevel
(
  const HAL_clk_ClusterDescType   *pHALCluster,
  uint32_t                        *pnVcIndex
)
{
  uint16_t nCount = HAL_CLK_EPSS_TIMEOUT_COUNTER;
  while ((--nCount) & !(HAL_CLK_HWIO_INF(pHALCluster, DCVS_IN_PROGRESS, STATUS)));
  *pnVcIndex = HAL_CLK_HWIO_INF(pHALCluster, DOMAIN_STATE, VC_IDX);
  return (nCount > 0) ? TRUE : FALSE;
}

static  boolean  HAL_clk_ReadPerfLevelConfig
(
  const HAL_clk_ClusterDescType   *pHALCluster,
  const uint32_t                   nVcIndex,
  HAL_clk_ClusterPerfLevelType    *pPerfLevel
)
{
  pPerfLevel->nOpenLoopVoltage = HAL_CLK_HWIO_INFI(pHALCluster, DCVS_LUT_r_VOLTAGE,   nVcIndex, OLV);
  pPerfLevel->nL               = HAL_CLK_HWIO_INFI(pHALCluster, DCVS_LUT_r_FREQUENCY, nVcIndex, LVAL);
  pPerfLevel->nSource          = HAL_CLK_HWIO_INFI(pHALCluster, DCVS_LUT_r_FREQUENCY, nVcIndex, CLKSRC);
  return TRUE;
}

boolean  HAL_clk_PerCoreL3VottingEnabled
(
  void
)
{
  //return HWIO_EPSSTOP_L3_VOTING_EN_INM(HWIO_FMSK(EPSSTOP_L3_VOTING_EN, L3_VOTING_ENABLE));
  return TRUE;
}



/* ============================================================================
**    Data Declarations
** ==========================================================================*/


HAL_clk_ClusterControlType HAL_clk_GenericEPSSControl =
{
  .SetCorePerfLevel    = HAL_clk_SetCorePerfLevel,
  .SetL3PerfLevel      = HAL_clk_SetL3PerfLevel,
  .GetCorePerfLevel    = HAL_clk_GetCorePerfLevel,
  .GetL3PerfLevel      = HAL_clk_GetL3PerfLevel,
  .GetConfig           = HAL_clk_GetConfig,
  .GetActivePerfLevel  = HAL_clk_GetActivePerfLevel,
  .ReadPerfLevelConfig = HAL_clk_ReadPerfLevelConfig,
};

/*
===========================================================================
*/
/**
  @file ClockApps.c

  Main entry point for the SDM845 main application processor clock driver.
*/
/*
  ====================================================================

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Waipio/Library/ClockLib/ClockApps.c#12 $
  $DateTime: 2021/09/20 16:38:17 $
  $Author: pwbldsvc $
  ====================================================================
*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "ClockApps.h"
#include "Library/HALclkGeneric.h"
#include "HALhwio.h"
#include "../HALclkLib/HALclkHWIO.h"
#include "busywait.h"
#include "Drivers/ClockDxe/ClockDriverImage.h"
#include <Library/KernelLib.h>

/*=========================================================================
      Type Definitions
==========================================================================*/

/*=========================================================================
      Externs
==========================================================================*/

extern HAL_clk_ClockControlType           HAL_clk_GenericClockControl;
extern HAL_clk_ClockDomainControlType     HAL_clk_GenericDomainControl;

uint32 Clock_ActiveCPUCore;

/*=========================================================================
      Function Prototypes
==========================================================================*/

extern ClockResult Clock_RegisterLPMCallBacks (BOOLEAN bIsRegisterLpm);

/*=========================================================================
      Data
==========================================================================*/

/*
 * Clock Apps context.
 */
ClockAppsCtxtType Clock_AppsCtxt;

/*=========================================================================
      Data Declarations
==========================================================================*/
uint32 Clock_InitStub = FALSE;

#define SILVER_CLUSTER_CORE0 0x0
#define GOLD_CLUSTER_CORE0 0x4


/* ===========================================================================
**  HAL_clk_PCIePowerDomainEnable
** ======================================================================== */

void HAL_clk_PCIePowerDomainEnable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uintnt nAddr, nCfg2Addr, nGDSCAddr;
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
  
//  nVal  = inpdw(nAddr);
//  if ((nVal & HAL_CLK_GDSCR_SW_COLLAPSE_FMSK) == 0)
//  {
//     return;  // if its already enabled, just return
//  }
  
  /* set GDSC_MEM_PWRUP_ACK_OVERRIDE */
  nCfg2Addr = pmPowerDomainDesc->nGDSCRAddr + 8;
  nVal  = inpdw(nCfg2Addr);
  nVal = nVal | (1 << 18);
  outpdw(nCfg2Addr, nVal);

  /* set HW CONTROL to 0 */
  nGDSCAddr = pmPowerDomainDesc->nGDSCRAddr;
  nVal  = inpdw(nGDSCAddr);  
  nVal &= ~HAL_CLK_GDSCR_HW_CONTROL_FMSK;
  outpdw(nGDSCAddr, nVal);

  /* set RETAIN_FF_ENABLE to 0
   * HW CR: QCTDD07883093
   * INFO: eventhough by default it will be left 0 (becouse clock driver is not setting it)
   *       but as a part of gdsc collapse FSM this signal goes 1 and come back to 0.
   *       if we set to 0, explicity, duration of that signal will stay in 1 will be less
   *       that is the behavior of this signal. we will have to write 0 everytime we enable or disable GDSC
   */
  nGDSCAddr = pmPowerDomainDesc->nGDSCRAddr;
  nVal  = inpdw(nGDSCAddr);
  nVal &= ~HAL_CLK_GDSCR_RETAIN_FF_ENABLE_BMSK;
  outpdw(nGDSCAddr, nVal);

  nVal  = inpdw(nAddr);

  /*
   * Clear the SW PD collapse bit
   */
  nVal &= ~nMask;
  outpdw(nAddr, nVal);

#if 0
  /*
   * INFO: we need not to set RETAIN_FF_ENABLE bit Pcie gdsc's.
   * By design, it is not expected. It was messing with the way Pcie core are reset.
   * Check RETAIN_FF_ENABLE and set it if it's not set.
   */
   if(pmPowerDomainDesc->VoterRegister.nAddr == 0)
   {
     if(0x0 == (nVal & HAL_CLK_GDSCR_RETAIN_FF_ENABLE_BMSK))
     {
       nVal |= HAL_CLK_GDSCR_RETAIN_FF_ENABLE_BMSK;
       outpdw(pmPowerDomainDesc->nGDSCRAddr, nVal);
     }
   }
#endif
  /*
   * Wait for PD ON
   */
  while (!(inpdw(pmPowerDomainDesc->nGDSCRAddr) & HAL_CLK_GDSCR_PWR_ON_FMSK));

} /* END HAL_clk_PCIePowerDomainEnable */


/* ===========================================================================
**  HAL_clk_PCIePowerDomainDisable
** ======================================================================== */

void HAL_clk_PCIePowerDomainDisable
(
  HAL_clk_PowerDomainDescType *pmPowerDomainDesc
)
{
  uintnt nAddr, nGDSCAddr;
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

  /* set HW CONTROL to 0*/
  nGDSCAddr = pmPowerDomainDesc->nGDSCRAddr;
  nVal  = inpdw(nGDSCAddr); 
  nVal &= ~HAL_CLK_GDSCR_HW_CONTROL_FMSK;
  outpdw(nGDSCAddr, nVal);

  /* set RETAIN_FF_ENABLE to 0
   * HW CR: QCTDD07883093
   * INFO: eventhough by default it will be left 0 (becouse clock driver is not setting it)
   *       but as a part of gdsc collapse FSM this signal goes 1 and come back to 0.
   *       if we set to 0, explicity, duration of that signal will stay in 1 will be less
   *       that is the behavior of this signal. we will have to write 0 everytime we enable or disable GDSC
   */
  nGDSCAddr = pmPowerDomainDesc->nGDSCRAddr;
  nVal  = inpdw(nGDSCAddr);
  nVal &= ~HAL_CLK_GDSCR_RETAIN_FF_ENABLE_BMSK;
  outpdw(nGDSCAddr, nVal);

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

} /* END HAL_clk_PCIePowerDomainDisable */


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

HAL_clk_PowerDomainControlType HAL_clk_PCIePowerDomainControl =
{
   .Enable     = HAL_clk_PCIePowerDomainEnable,
   .Disable    = HAL_clk_PCIePowerDomainDisable,
   .IsEnabled  = HAL_clk_GenericPowerDomainIsEnabled,
   .IsOn       = HAL_clk_GenericPowerDomainIsOn,
   .EnableHW   = HAL_clk_GenericPowerDomainEnableHW,
   .DisableHW  = HAL_clk_GenericPowerDomainDisableHW
};

HAL_clk_PowerDomainControlType HAL_clk_GPUGxPowerDomainControl =
{
   .Enable     = HAL_clk_GPUGxPowerDomainEnable,
   .Disable    = HAL_clk_GPUGxPowerDomainDisable,
   .IsEnabled  = HAL_clk_GenericPowerDomainIsEnabled,
   .IsOn       = HAL_clk_GenericPowerDomainIsOn,
   .EnableHW   = HAL_clk_GenericPowerDomainEnableHW,
   .DisableHW  = HAL_clk_GenericPowerDomainDisableHW
};

/*=========================================================================
      Externals
==========================================================================*/

/*=========================================================================
      Functions
==========================================================================*/

/* =========================================================================
**  Function : Clock_InitTarget
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_InitTarget
(
void
)
{
  ClockResult        eResult = CLOCK_SUCCESS;
  ClockAppsBSPType  *pAppsBSPConfig;
  uint32             i;
  ClockDrvCtxt      *pDrvCtxt = Clock_GetDrvCtxt();
  uint32_t           nFreqHzBootCore=0, nFreqHzL3=0;
  ClockIdType        nClockId;
  const char        *szBootCoreName = "";
  ClockNameListType *pDCDEnableDependencies= NULL;
  ClockNameListType *pDCDDisableDependencies= NULL;

  if(!Clock_InitStub)
  {  

  /*
   * Hookup the apps context to the driver context.
   */
  pDrvCtxt->pImageCtxt = &Clock_AppsCtxt;

  /*-----------------------------------------------------------------------*/
  /* Initialize the Apps BSP data.                                         */
  /*-----------------------------------------------------------------------*/

  pAppsBSPConfig = Clock_GetAppsBSP();

  for (i = 0; i < CLOCK_APPS_CPU_TOTAL; i++)
  {
    /*
     * Hookup the BSP data.
     */
    switch (i)
    {
      case CLOCK_APPS_CPU_C0:
        Clock_AppsCtxt.aCPU[i].pBSPConfig = &pAppsBSPConfig->aCPUConfig[CLOCK_APPS_CPU_CLUSTER_C0];
        break;

      case CLOCK_APPS_CPU_C1:
        Clock_AppsCtxt.aCPU[i].pBSPConfig = &pAppsBSPConfig->aCPUConfig[CLOCK_APPS_CPU_CLUSTER_C1];
        break;

      case CLOCK_APPS_CPU_C2:
        Clock_AppsCtxt.aCPU[i].pBSPConfig = &pAppsBSPConfig->aCPUConfig[CLOCK_APPS_CPU_CLUSTER_C2];
        break;

      case CLOCK_APPS_CPU_L3:
       Clock_AppsCtxt.aCPU[i].pBSPConfig = &pAppsBSPConfig->aCPUConfig[CLOCK_APPS_CPU_CLUSTER_L3];
        break;

      default:
        return CLOCK_ERROR_INTERNAL;
    }
  }


  eResult = Clock_InitAppsBSP(pDrvCtxt);
  if (eResult != CLOCK_SUCCESS)
  {
    return CLOCK_ERROR_INTERNAL;
  }

  /*-----------------------------------------------------------------------*/
  /* Name and configure the CPU clocks.                                    */
  /*-----------------------------------------------------------------------*/

  for (i = 0; i < CLOCK_APPS_CPU_TOTAL; i++)
  {
    /* Default all CPU active configuration to the first BSP entry. */
    Clock_AppsCtxt.aCPU[i].pActiveConfig = &Clock_AppsCtxt.aCPU[i].pBSPConfig->pConfig->aPerfConfig[0];
  }
  /*-----------------------------------------------------------------------*/
  /* Initialize the DCVS module.                                           */
  /*-----------------------------------------------------------------------*/

  Clock_InitDCVS();

  /*-----------------------------------------------------------------------*/
  /* Initialize QDSS.                                                      */
  /*-----------------------------------------------------------------------*/
  Clock_InitQDSS();

  /*-----------------------------------------------------------------------*/
  /* Getting the current core.                                           */
  /*-----------------------------------------------------------------------*/

  Clock_ActiveCPUCore = MpcoreGetCurrCpu();

  /*-----------------------------------------------------------------------*/
  /* Detecting Current PerfLevel frequency.                          */
  /*-----------------------------------------------------------------------*/

  if(Clock_ActiveCPUCore == SILVER_CLUSTER_CORE0)
  {
    if(Clock_DetectCPUFrequency(CLOCK_APPS_CPU_C0,&nFreqHzBootCore) != CLOCK_SUCCESS)
    {
      return CLOCK_ERROR_INTERNAL;
    }
    szBootCoreName = "Silver";
  }
  else if(Clock_ActiveCPUCore == GOLD_CLUSTER_CORE0)
  {
    if(Clock_DetectCPUFrequency(CLOCK_APPS_CPU_C1,&nFreqHzBootCore) != CLOCK_SUCCESS)
    {
      return CLOCK_ERROR_INTERNAL;
    }
    szBootCoreName = "Gold";
  }
  if(Clock_DetectCPUFrequency(CLOCK_APPS_CPU_L3,&nFreqHzL3) != CLOCK_SUCCESS)
  {
    return CLOCK_ERROR_INTERNAL;
  }
  DEBUG((EFI_D_WARN, " >>> Clock_ActiveCPUCore: %d\n >>> %a Cluster: %8d Hz\n >>> L3 Cluster: %8d Hz\n", Clock_ActiveCPUCore, szBootCoreName, nFreqHzBootCore, nFreqHzL3));

  /*-----------------------------------------------------------------------*/
  /* Register LPM callbacks.                                               */
  /*-----------------------------------------------------------------------*/
  eResult = Clock_RegisterLPMCallBacks(TRUE);
  if (eResult != CLOCK_SUCCESS)
  {
    DEBUG((EFI_D_WARN, "Clock_RegisterLPMCallBacks Failed\n"));
  }

  /*-----------------------------------------------------------------------*/
  /* Update miscellaneous GPU registers.                                   */
  /*-----------------------------------------------------------------------*/

  HAL_clk_InitMiscRegisters();

  /*-----------------------------------------------------------------------*/
    /* Enable Multimedia DCD's.                                               */
    /*-----------------------------------------------------------------------*/ 

   eResult = Clock_GetPropertyHandle("ClockDCDEnableDependencies", (void**)&pDCDEnableDependencies);
    if (eResult != CLOCK_SUCCESS){
      return CLOCK_ERROR;
    }

    for (i = 0; pDCDEnableDependencies[i].szName != NULL; i++){
      if ((Clock_GetClockId(pDrvCtxt->hClient, pDCDEnableDependencies[i].szName, &nClockId) == CLOCK_SUCCESS) &&
          (Clock_EnableEx(pDrvCtxt->hClient, nClockId, 0) == CLOCK_SUCCESS))
      {
         busywait(5);
      }
      else
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog, "Failed to Enable DCD dependency clock %s", pDCDEnableDependencies[i].szName);
        DEBUG((EFI_D_WARN, "Failed to Enable DCD dependency clock %a", pDCDEnableDependencies[i].szName));
        return CLOCK_ERROR;
      }
    }

    HAL_clk_EnableDCDs();

    eResult = Clock_GetPropertyHandle("ClockDCDDisableDependencies", (void**)&pDCDDisableDependencies);
    if (eResult != CLOCK_SUCCESS){
        return CLOCK_ERROR;
    }

    for (i = 0; pDCDDisableDependencies[i].szName != NULL; i++){
      if ((Clock_GetClockId(pDrvCtxt->hClient, pDCDDisableDependencies[i].szName, &nClockId) == CLOCK_SUCCESS) &&
          (Clock_DisableEx(pDrvCtxt->hClient, nClockId, 0) == CLOCK_SUCCESS))
      {
        continue;
      }
      else
      {
        ULOG_RT_PRINTF_1 (pDrvCtxt->hClockLog, "Failed to Disable DCD dependency clock %s", pDCDDisableDependencies[i].szName);
        DEBUG((EFI_D_WARN, "Failed to Disable DCD dependency clock %a", pDCDDisableDependencies[i].szName));
      }
    }

  
  /*-----------------------------------------------------------------------*/
  /* Run the BIST if enabled.                                              */
  /*-----------------------------------------------------------------------*/
  if (pDrvCtxt->nBISTLogSize == 0)
  {
    pDrvCtxt->nBISTLogSize = CLOCK_BIST_DEFAULT_LOG_SIZE;
  }

  if (pDrvCtxt->bBISTEnabled)
  {
    Clock_BIST ();
  }
}
  /*-----------------------------------------------------------------------*/
  /* Good to go.                                                           */
  /*-----------------------------------------------------------------------*/

  return eResult;

} /* END Clock_InitTarget */


/* =========================================================================
**  Function : Clock_DeInitTarget
** =========================================================================*/
/*
  See ClockDriver.h
*/

ClockResult Clock_DeInitTarget
(
  ClockDrvCtxt *pDrvCtxt
)
{
  /*-----------------------------------------------------------------------*/
  /* Clear out driver context data.                                        */
  /*-----------------------------------------------------------------------*/

  memset((void *)pDrvCtxt->pImageCtxt, 0x0, sizeof(ClockAppsCtxtType));

  return CLOCK_SUCCESS;

} /* END Clock_DeInitTarget */


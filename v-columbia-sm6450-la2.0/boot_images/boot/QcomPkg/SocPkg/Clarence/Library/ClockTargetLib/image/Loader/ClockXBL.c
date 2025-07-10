/*
==============================================================================
  @file ClockXBL.c

  Clock functions for the XBL Loader Clock Driver.

  Copyright (c) 2021-2023 QUALCOMM Technologies, Inc.  All rights reserved.

==============================================================================
*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "HALclkHWIO.h"
#include "Clock.h"
#include "ClockBoot.h"
#include "ClockDriver.h"
#include "ClockBSPExtern.h"
#include "railway.h"
#include "CoreMsgRam.h"
#include "smem.h"
#include "string.h"
#include "CoreVerify.h"
#include "ChipInfo.h"

/*=========================================================================
                       MACRO DEFINITIONS
==========================================================================*/
#define CLK_HW_CTL_MASK 0x2
#define CLK_DCD_ENABLE  0x1
#define CLK_ENA_MASK    0x1

#define CLOCK_SMEM_VERSION 2

#define SOC_RUMI 1
#define SOC_PLATFORM_TYPE_MASK 0x3
#define RUMI_CHECK() ((HWIO_IN(TCSR_SOC_EMULATION_TYPE) & SOC_PLATFORM_TYPE_MASK) == SOC_RUMI)

uint32 DDR_GetPerfLevel();
uint32 DDR_GetFreqInKhz();
void Clock_UpdateMCShubMinMaxFreq();
void Clock_UpdateVCDsMinMaxFreq(void);
void ChipInfo_UpdateDisabledCPUsToDDRLocation(void);

/*=========================================================================
      TypeDefs
==========================================================================*/

/* Data structure for Railway data */
typedef struct
{
  char*             CxRail;
  int               nCxRailId;
  railway_voter_t   CxVoter;
  char*             EBIRail;
  int               nEBIRailId;
  railway_voter_t   EBIVoter;
}Clock_RailwayType;

typedef struct
{
  uint16  nVersion;         /* A version number to verify matching XBL and RPM data structures */
  uint16  nBootCPOffset;    /* Offset to boot CP table address */
} Clock_SMEMInfoType;


/*=========================================================================
      Data
==========================================================================*/

Clock_RailwayType ClockRailway =
{
  "vddcx",
  0,
  0,
  "vdda_ebi",
  0,
  0
};

ClockDomainNodeType *Clock_InitDomains[] =
{
  /*
   * GCC Domains
   */
  &ClockDomain_GCC_GCCAGGRENOC,
  &ClockDomain_GCC_GCCCE1,
  &ClockDomain_GCC_GCCCNOCCENTERQX,
  &ClockDomain_GCC_GCCCNOCPCIEQX,
  &ClockDomain_GCC_GCCCNOCPERIPH,
  &ClockDomain_GCC_GCCCONFIGNOC,
  &ClockDomain_GCC_GCCCONFIGNOCDDRSSSF,
  &ClockDomain_GCC_GCCDPM,
  &ClockDomain_GCC_GCCGPUMEMNOCGFX,
  &ClockDomain_GCC_GCCMEMNOC,
  &ClockDomain_GCC_GCCMMUTCU,
  &ClockDomain_GCC_GCCSHRM,
  &ClockDomain_GCC_GCCSYSNOC,
  &ClockDomain_GCC_GCCSYSNOCGCAXI,
  &ClockDomain_GCC_GCCSYSNOCSFAXI,
  /*
   * AOSS Domains
   */
  &ClockDomain_AOSSCC_AOSSCCAOP,
  &ClockDomain_AOSSCC_AOSSCCEUDAT,
  &ClockDomain_AOSSCC_AOSSCCIBI,
  &ClockDomain_AOSSCC_AOSSCCRO,
  &ClockDomain_AOSSCC_AOSSCCSPMIAODSER,
  &ClockDomain_AOSSCC_AOSSCCSWAO,
  &ClockDomain_AOSSCC_AOSSCCSWAOTS,
};

/* Clock performance CP for sharing with AOP */
ClockCfgCPType Clock_PerfData;

/* DCD control variables. */
boolean Boot_Clock_DCD = TRUE;

/* List of registers to initialize for DCD setup. */
uint64 Clock_DCD_Cfg[] =
{
  // DCD enable registers
  HWIO_ADDR(GCC_AGGRE_NOC_PCIE_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_WEST_TUNNEL_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CFG_NOC_LPASS_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CNOC_CENTER_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_DDRSS_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_LPASS_AHB_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_NORTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_SOUTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_WEST_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MMNOC_HF_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MMNOC_SF_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SHRM_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_GC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_LPASS_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_NAV_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_SOUTH_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_TME_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_SOUTH_QX_M_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_VIDEO_VENUS_DIV_DCDR),


  //Fixed CDIV DCD(s)
  HWIO_ADDR(GCC_CONFIG_NOC_CENTER_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_WPSS_AXI_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_GPU_MEMNOC_GFX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_IPA_2X_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MEMNOC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MMU_TCU_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MSS_OFFLINE_AXI_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MSS_Q6_MEMNOC_AXI_DCD_CDIV_DCDR),
};

/* ODSC control variables. */
boolean Boot_Clock_ODSC_Ctl = TRUE;

/*
 * Generate this list
 */
uint32_t Clock_ODSC_Ctl_Cfg[] =
{
  /*==========================
      ODSC Clocks
  ============================*/
  HWIO_ADDR(GCC_QMIP_AGGRE_NOC_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_CAMERA_NRT_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_CAMERA_RT_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_VCODEC_AHB_CBCR),
  //HWIO_ADDR(GCC_QUPV3_WRAP_0_S_AHB_CBCR), /* disabling due to Multi EE issue */
  //HWIO_ADDR(GCC_QUPV3_WRAP_1_S_AHB_CBCR),
  HWIO_ADDR(GCC_PDM_AHB_CBCR),
  HWIO_ADDR(GCC_AOSS_CNOC_S_AHB_CBCR),
  HWIO_ADDR(GCC_CE1_AHB_CBCR),
  //HWIO_ADDR(GCC_QMIP_LPASS_TBU_AHB_CBCR), //enabled in EXIT BOOT.
  HWIO_ADDR(GCC_RBCPR_CX_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXA_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_PCIE_AHB_CBCR),
  HWIO_ADDR(GCC_MSS_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_MSS_OFFLINE_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_MSS_Q6_CFG_AHB_CBCR),
  //HWIO_ADDR(GCC_QMIP_GPU_AHB_CBCR), //enabled in EXIT BOOT.
  HWIO_ADDR(GCC_IPCC_AHB_CBCR),
  HWIO_ADDR(GCC_DPM_CX_AHB_CBCR),
  HWIO_ADDR(GCC_DPM_MX_AHB_CBCR),
  HWIO_ADDR(GCC_WPSS_THROTTLE_AHB_CBCR),

};

/* DCG control variables. */
boolean Boot_Clock_DCG_Ctl = TRUE;

uint32_t Clock_DCG_Ctl_Cfg[] =
{
  HWIO_ADDR(GCC_TIC_CBCR),
  HWIO_ADDR(GCC_TIC_CFG_QX_CBCR),
  HWIO_ADDR(GCC_MSS_SNOC_AXI_CBCR),
  // HWIO_ADDR(GCC_GPU_MEMNOC_GFX_CBCR), // enabled in EXIT BOOT
  HWIO_ADDR(GCC_MSS_OFFLINE_AXI_CBCR),
  //HWIO_ADDR(GCC_WPSS_AXI_CBCR),
  HWIO_ADDR(GCC_WPSS_THROTTLE_AXI_CBCR),
  HWIO_ADDR(GCC_MSS_Q6_MEMNOC_AXI_CBCR),
};

ClockSourceNodeType* aGplls[] =
{
  &ClockSource_GCC_GCCGPLL0,
  &ClockSource_GCC_GCCGPLL1,
  &ClockSource_GCC_GCCGPLL2,
  &ClockSource_GCC_GCCGPLL4,
  &ClockSource_GCC_GCCGPLL5,
  &ClockSource_GCC_GCCGPLL6,
  &ClockSource_GCC_GCCGPLL7,
  &ClockSource_GCC_GCCGPLL8,
  &ClockSource_GCC_GCCGPLL9,
  &ClockSource_GCC_GCCGPLL10,
};

uint32_t tbu_tcu_clocks[] =
{ 
  //HWIO_ADDR(GCC_AGGRE_NOC_PCIE_TBU_CBCR), //votable clk
  HWIO_ADDR(GCC_AGGRE_NOC_AUDIO_TBU_CBCR),
  HWIO_ADDR(GCC_AGGRE_NOC_TBU1_CBCR),
  HWIO_ADDR(GCC_AGGRE_NOC_TBU2_CBCR),
  // HWIO_ADDR(GCC_DDRSS_PCIE_SF_TBU_CBCR), // equivalent not available in the list of TZ clockBSP.c
  // HWIO_ADDR(GCC_QMIP_LPASS_TBU_AHB_CBCR), // equivalent not available in the list of TZ clockBSP.c
  HWIO_ADDR(GCC_MMNOC_TBU_HF0_CBCR),
  HWIO_ADDR(GCC_MMNOC_TBU_HF1_CBCR),
  HWIO_ADDR(GCC_MMNOC_TBU_SF0_CBCR),
  //HWIO_ADDR(GCC_DDRSS_TCU_CBCR), // equivalent not available in the list of TZ clockBSP.c
  HWIO_ADDR(GCC_MMU_TCU_CBCR),
};

static void Clock_DisabeTBUTCU_Clks
(
  void
)
{
  uintptr_t nAddr;

  for (int i = 0; i < SIZEOF_ARRAY(tbu_tcu_clocks); i++)
  {
    nAddr = tbu_tcu_clocks[i];
    outpdw(nAddr, inpdw(nAddr) & ~0x1UL);
  }
  HWIO_OUTF(GCC_RPM_CLOCK_BRANCH_ENA_VOTE , AGGRE_NOC_PCIE_TBU_CLK_ENA,0x0);
}

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

static ClockDomainNodeType* Clock_GetBootCoreDomain
(
  void
)
{
   uint64_t nMpidr;
   uint64_t nBootCoreIdx = 0;

   __asm__ __volatile__("mrs %0, MPIDR_EL1":"=r"(nMpidr));

  nBootCoreIdx = ((nMpidr & (0xFFFF))>> 0x8);

  if (nBootCoreIdx == 0)
  {
    return &ClockDomain_APSSCC_APSSCCSILVERGFMUX;
  }
  else if (nBootCoreIdx == 4)
  {
    return &ClockDomain_APSSCC_APSSCCGOLDGFMUX;
  }

  return NULL;
}

/* ========================================================================
**  Function : Clock_InitVoltageRails
** ======================================================================*/
/*
    Description: Initialize voltage rails

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
bool Clock_InitVoltageRails
(
  rail_voltage_level eBootCorner
)
{
  /* Setup railways */
  ClockRailway.nCxRailId = RAIL_NOT_SUPPORTED_BY_RAILWAY;
  ClockRailway.nEBIRailId = RAIL_NOT_SUPPORTED_BY_RAILWAY;

  /* Initialize CX & VDDA_EBI Rails */
  ClockRailway.nCxRailId = rail_id(ClockRailway.CxRail);
  ClockRailway.nEBIRailId = rail_id(ClockRailway.EBIRail);

  if( (RAIL_NOT_SUPPORTED_BY_RAILWAY == ClockRailway.nCxRailId) ||
      (RAIL_NOT_SUPPORTED_BY_RAILWAY == ClockRailway.nEBIRailId) )
  {
    return FALSE;
  }

  ClockRailway.CxVoter = railway_create_voter(ClockRailway.nCxRailId,RAILWAY_CLOCK_DRIVER_VOTER_ID);
  ClockRailway.EBIVoter = railway_create_voter(ClockRailway.nEBIRailId,RAILWAY_CLOCK_DRIVER_VOTER_ID);

  railway_corner_vote(ClockRailway.CxVoter, RAILWAY_NOMINAL);
  railway_corner_vote(ClockRailway.EBIVoter, RAILWAY_SVS);
  railway_transition_rails();
  
  return TRUE;
}


/* ========================================================================
**  Function : Clock_InitDDR
** ======================================================================*/
/*
    Description: Configure all clocks needed for DDR configuration.  This
    extension API is used for bootup and emergency download mode.

    @param None
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/
static bool Clock_InitDDR
(
  void
)
{
  /* Set MSG_RAM base address for passing smem address to AOP since there is no smem driver in AOP
   * This address is based on target specific.
   * It needs to sync up with AOP team when porting this code to new target
   */
  /* TODO: Why is this being done here? Not our responsibility. */
  msg_ram_init_base( (uint32*)(AOP_SS_MSG_RAM_START_ADDRESS_BASE + AOP_SS_MSG_RAM_DRV14_BASE) );

  /*
   * DDRSS HPG section 2.1.1 - GCC Programming
   *
   * These are required, otherwise DDR gets stuck entering power collapse.
   * There should be a HW CR for this, but it hasn't been filed yet.
   */
   //SHUB VCD
  HWIO_OUTF(GCC_MEMNOC_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_GPU_AXI_CBCR, IGNORE_PMU_CLK_DIS,1);
  HWIO_OUTF(GCC_DDRSS_GPU_AXI_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_TCU_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  //MMNOC VCD
  HWIO_OUTF(GCC_DDRSS_MMNOC_SF_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_MMNOC_HF_QX_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  //SYSNOC VCD
  HWIO_OUTF(GCC_DDRSS_PCIE_SF_TBU_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_CONFIG_NOC_SF_CBCR, IGNORE_RPMH_CLK_DIS,1);
  HWIO_OUTF(GCC_DDRSS_SNOC_SF_AXI_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_SNOC_GC_AXI_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  //MODEM VCD
  HWIO_OUTF(GCC_DDRSS_MSS_Q6_AXI_CBCR, IGNORE_RPMH_CLK_DIS,1);
  HWIO_OUTF(GCC_DDRSS_MODEM_CBCR, IGNORE_RPMH_CLK_DIS,1);

  return TRUE;
}


/* ============================================================================
**  Function : Clock_SetSysPerfLevel
** ============================================================================
*/
/**
  Configure NOCs and RPM to a perf level.

  @return
  TRUE -- NOCs were configured to perf level successful.
  FALSE -- Configuration failed.

  @dependencies
  None.

  @sa
  Clock_Init.
*/

static boolean Clock_SetSysPerfLevel
(
  void
)
{
  for (int i = 0; i < SIZEOF_ARRAY(Clock_InitDomains); i++)
  {
    Clock_SetDomainBootFMax(Clock_InitDomains[i]);
  }
  
  /* QCTDD10187115 WA for AOP PDC issue when PLL goes to standby.
  *  design suggested to apply this settings once PLL's are configured.
  *  Profiling Time Stamp 4 (sequence resume) value of PDC core is not correct 
  *  when sequence wake up happens. This issue observed only when Pongo PLL put on standby mode during AOSS sleep.
  *  WA suggested is to Put PLL in bypass mode which will provide clock (32Khz) to demet cell during sleep.
  */
  HWIO_OUTF(AOSS_CC_PLL1_OUTCTRL, SEL,0x1);
  HWIO_OUTF(AOSS_CC_PLL1_PLL_USER_CTL_U, XO_CLK_AT_OUT, 0x1);
  HWIO_OUTF(AOSS_CC_PLL_CLK_SEL, PLL1_CLK_XO_SEL, 0x1);

  return TRUE;
}


/* ============================================================================
**  Function : Clock_SetCPUPerfLevel
** ============================================================================
*/
/**
  Configure CPU to a specific perf level.

  @return
  TRUE -- CPU configuration to perf level was successful.
  FALSE -- Configuration failed.

  @dependencies
  None.

  @sa
  Clock_Init.
*/
static boolean Clock_SetCPUPerfLevel
(
  void
)
{
  ClockDomainNodeType *pBootDomain, *pNonBootDomain;

  /* Requirement:  Apps needs 600 MHz GPLL0 for low voltage corners */
  if (!Clock_SetDomainFreq(&ClockDomain_GCC_GCCCPUSSGPLL0,
                           600000,
                           CLOCK_FREQUENCY_KHZ_AT_LEAST))
  {
    return FALSE;
  }
  
  /*
   * Detect boot core.
   */
  pBootDomain = Clock_GetBootCoreDomain();

  /*
   * Assert if booting from unsupported core.
   */
  CORE_VERIFY_PTR(pBootDomain);
  
  /*
   * Booting from Silver core.
   */
  if (pBootDomain == &ClockDomain_APSSCC_APSSCCSILVERGFMUX)
  {
    pNonBootDomain = &ClockDomain_APSSCC_APSSCCGOLDGFMUX;
  }
  /*
   * Booting from Gold core.
   */
  else
  {
    pNonBootDomain = &ClockDomain_APSSCC_APSSCCSILVERGFMUX;
  }

  /* Set CPU speed */
  Clock_SetDomainBootFMax(pBootDomain);

  if (!Clock_SetDomainFreq(pNonBootDomain,
                           600000,
                           CLOCK_FREQUENCY_KHZ_AT_LEAST))
  {
    return FALSE;
  }

  /* Set L3 speed */
  Clock_SetDomainBootFMax(&ClockDomain_APSSCC_APSSCCL3GFMUX);

  return TRUE;
}


/* ============================================================================
**  Function : Clock_InitLPASS
** ============================================================================
*/
/*!

Configure LPASS core clocks to turn on LPASS.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_InitLPASS
(
  void
)
{

  ChipInfoResult eResult = CHIPINFO_ERROR;
  boolean mask;

  eResult = ChipInfo_IsPartDisabled(CHIPINFO_PART_AUDIO, 0, &mask);
  if(eResult == CHIPINFO_SUCCESS && mask != TRUE)
  {
  /*
   * LPASS Core needs to be powered up so that ICB can progream
   * LPASS with it's SCID.
   */
  Clock_EnableClockInternal(HWIO_ADDR(GCC_CFG_NOC_LPASS_CBCR));
  Clock_EnableClockInternal(HWIO_ADDR(GCC_LPASS_CFG_NOC_SWAY_CBCR));

 /* LPASS CORE HM NOT present in clarence. */
#if 0
  /*
   * Following instructions from LPASS HPG V9.5
   * See section 3.4.1.2:
   * Initial POR Power UP sequence of LPASS_CORE_HM performed by APPS
   */
  HWIO_OUTF(LPASS_LPASS_TOP_CC_LPI_SWAY_AHB_LS_CBCR, HW_CTL, 1);
  Clock_EnablePowerDomainInternal(HWIO_ADDR(LPASS_LPASS_CORE_HM_GDSCR));

  /*
   * Lahaina RUMI doesn't seem to support this yet. Remove polling to unblock
   * initial RUMI testing.
   */
  if (!RUMI_CHECK())
  {
    while(!HWIO_INF(LPASS_LPASS_CORE_GDS_HM_READY, LPASS_CORE_HM));
  }

  HWIO_OUTF(LPASS_LPASS_CORE_HM_GDSCR, RETAIN_FF_ENABLE, 1);

  Clock_EnableClockInternal(HWIO_ADDR(LPASS_LPASS_CORE_CC_SYSNOC_MPORT_CORE_CBCR));
#endif
 }
  return TRUE;
} /* END Clock_InitLPASS */


/* ============================================================================
**  Function : Clock_DeInitLPASS
** ============================================================================
*/
/*!

Turn off LPASS.

    @param None.
    @return
    TRUE -- Initialization was successful.
    FALSE -- Initialization failed.

    @dependencies
    None.

    @sa None
*/

boolean Clock_DeInitLPASS
(
  void
)
{

  ChipInfoResult eResult = CHIPINFO_ERROR;
  boolean mask;

  eResult = ChipInfo_IsPartDisabled(CHIPINFO_PART_AUDIO, 0, &mask);
  if(eResult == CHIPINFO_SUCCESS && mask != TRUE)
  {
  /*
   * Disable clocks that were enabled in Clock_InitLPASS and not needed anymore.
   */
   
  /* LPASS CORE HM not present. NA for clarence.*/
  #if 0
  Clock_DisableClockInternal(HWIO_ADDR(LPASS_LPASS_CORE_CC_SYSNOC_MPORT_CORE_CBCR));
  Clock_DisablePowerDomainInternal(HWIO_ADDR(LPASS_LPASS_CORE_HM_GDSCR));
  HWIO_OUTF(LPASS_LPASS_TOP_CC_LPI_SWAY_AHB_LS_CBCR, HW_CTL, 0);
  #endif
  Clock_DisableClockInternal(HWIO_ADDR(GCC_LPASS_CFG_NOC_SWAY_CBCR));
  }
  return TRUE;
} /* END Clock_DeInitLPASS */


/* ============================================================================
**  Function : Clock_EnableDynClkDivide
** ============================================================================
*/
/**
  Enable dynamic clock dividers.
*/

static void Clock_EnableDynClkDivide
(
  void
)
{
  int i;

  /* Initialize the registers for DCD */
  for (i = 0; i < SIZEOF_ARRAY(Clock_DCD_Cfg); i++ )
  {
    outpdw(Clock_DCD_Cfg[i], CLK_DCD_ENABLE);
  }
}


/* ============================================================================
**  Function : Clock_EnableHwCtl
** ============================================================================
*/
/**
  Enable on-demand slave clocking
*/

static void Clock_EnableODSCCtl
(
  void
)
{
  uintptr_t nAddr;

  for (int i = 0; i < SIZEOF_ARRAY(Clock_ODSC_Ctl_Cfg); i++)
  {
    nAddr = Clock_ODSC_Ctl_Cfg[i];
    outpdw(nAddr, inpdw(nAddr) | CLK_HW_CTL_MASK);
  }
}

static void Clock_EnableDCGCtl
(
  void
)
{
  uintptr_t nAddr;

  for (int i = 0; i < SIZEOF_ARRAY(Clock_DCG_Ctl_Cfg); i++)
  {
    nAddr = Clock_DCG_Ctl_Cfg[i];
    outpdw(nAddr, inpdw(nAddr) | CLK_HW_CTL_MASK);
    //outpdw(nAddr, inpdw(nAddr) & ~0x1UL);
  }
}

/* ============================================================================
**  Function : Clock_InitRefgen
** ============================================================================
*/
/**
  Initialize PHY_REFGEN.
*/

static void Clock_InitRefgen
(
  void
)
{
   uint32 dacc_fuse=0;
  /*
   * REfgen HPG Section 2.1.2
   * REFGEN NXGEN register settings recommendation for XBL
   */

  /*
   * TBD [ Program the Vcomp threshold level.]
   */
  // HWIO_OUT(PHY_REFGEN_0_NORTH_IP_TUNEH, ???);
  // HWIO_OUT(PHY_REFGEN_SOUTH_IP_TUNEH, ???);

  /*
   * Bring up REFGEN into function mode
   */

  // Check whether Initialization done
  if (!RUMI_CHECK())
  {
    while(!HWIO_INF(PHY_REFGEN_0_NORTH_RESTRIM_CODE_STATUS, REFGEN_READY));
    while(!HWIO_INF(PHY_REFGEN_SOUTH_RESTRIM_CODE_STATUS, REFGEN_READY));
  }

  // Programs REFGEN to accept votes via Hardware pins.
  HWIO_OUT(PHY_REFGEN_0_NORTH_CMN_REFGEN_CTRL1, 0x8);
  HWIO_OUT(PHY_REFGEN_SOUTH_CMN_REFGEN_CTRL1, 0x8);

  //Prepare for future analog rail collapse - clamp analog inputs to digital
  //Write REFGEN_CTRL2[1:0] = 0x03
  //Write DEBUG_CTRL[4]=0x1 - This is set by POR data

  HWIO_OUT(PHY_REFGEN_0_NORTH_CMN_REFGEN_CTRL2, 0x3);
  HWIO_OUT(PHY_REFGEN_SOUTH_CMN_REFGEN_CTRL2, 0x3);
  
  dacc_fuse = HWIO_INF(QFPROM_CORR_CALIBRATION_ROW3_LSB,REFGEN_SOUTH_IP_TUNEH)|
     HWIO_INF(QFPROM_CORR_CALIBRATION_ROW3_LSB,REFGEN_0_NORTH_IP_TUNEH);

  if(dacc_fuse)
  {
    HWIO_OUTF(PHY_REFGEN_SOUTH_IP_TUNEH, CMN_IP_TUNE_CTRLH_4_0,HWIO_INF(QFPROM_CORR_CALIBRATION_ROW3_LSB,REFGEN_SOUTH_IP_TUNEH));
    HWIO_OUTF(PHY_REFGEN_0_NORTH_IP_TUNEH, CMN_IP_TUNE_CTRLH_4_0, HWIO_INF(QFPROM_CORR_CALIBRATION_ROW3_LSB,REFGEN_0_NORTH_IP_TUNEH));
  }

}


/* =========================================================================
**  Function : Clock_GetGroupFrequency
** =========================================================================*/
/**
  Get the active frequency of a clock group.
*/
ClockResult Clock_GetGroupFrequency
(
  ClockGroupType *pClockGroup,
  uint32_t       *pnFrequencyHz
)
{
  ClockDomainNodeType *pBootDomain;

  if (!strcmp("apss", pClockGroup->szName))
  {
    pBootDomain = Clock_GetBootCoreDomain();
    CORE_VERIFY_PTR(pBootDomain);
    *pnFrequencyHz = Clock_GetDomainFrequency(pBootDomain);
    return CLOCK_SUCCESS;
  }
  else if (!strcmp("ddrss", pClockGroup->szName))
  {
    *pnFrequencyHz = DDR_GetFreqInKhz() * 1000; // KHz -> Hz
    return CLOCK_SUCCESS;
  }
  else if (pClockGroup->nDomains == 1)
  {
    *pnFrequencyHz = Clock_GetDomainFrequency(pClockGroup->aDomains[0]);
    return CLOCK_SUCCESS;
  }

  return CLOCK_ERROR_NOT_SUPPORTED;
}


/* ============================================================================
**  Function : Clock_QueryDDRPerfLevel
** ============================================================================
*/
/*!
    This function queries the DDR clock performance level.
  
  @param
    [in]nLevel - for DRR perf level
    
  @return
    TRUE  - success
    FALSE - failed
   
  @dependencies
    None.

*/
static bool Clock_QueryDDRPerfLevel(uint8* nLevel)
{
  *nLevel = DDR_GetPerfLevel();

  return TRUE;
}


/* ============================================================================
**  Function : Clock_ShareDataToAOP
** ============================================================================
*/
/*!
    This function is used for saving clock configure performance levels into SMEM
  for sharing with AOP.  AOP needs the know current performance level settings in
  XBL, so it can put the same initial vote during AOP initialize.
  
  @param
    None
    
  @return
    CLOCK_SUCCESS -- Initialization succeeded.
    CLOCK_ERROR   -- Initialization failed.
   
  @dependencies
    None.

*/
static ClockResult Clock_ShareDataToAOP( void )
{
  Clock_SMEMInfoType* pSMEMInfo;
  uint32 nTip, nSize;
  uint32 smem_size = sizeof(Clock_SMEMInfoType) + sizeof(ClockCfgCPType);
  void *pSMEM = smem_alloc(SMEM_CLOCK_INFO, smem_size);

  if(pSMEM == NULL) return CLOCK_ERROR;
  
  // Query DDR perf level so that we can write it to SMEM
  if (!Clock_PerfData.nDDR)
  {
    if (!Clock_QueryDDRPerfLevel(&Clock_PerfData.nDDR))
      return CLOCK_ERROR;
  }

  Clock_PerfData.nSHUB = ClockDomain_GCC_GCCMEMNOC.pActiveMuxConfig->HALConfig.nDFSIdx;

  /* Store smem address in msg_ram since there is no smem driver in AOP */
  msg_ram_set_smem_address((uint32)(uintptr_t)SMEM_CLOCK_INFO, (uint32)(uintptr_t)pSMEM);

  /* Store SMEMInfo */
  pSMEMInfo = pSMEM;
  pSMEMInfo->nVersion = CLOCK_SMEM_VERSION;
  pSMEMInfo->nBootCPOffset = sizeof(Clock_SMEMInfoType);

  /* Store BootCfgCP info */
  nTip = sizeof(Clock_SMEMInfoType);
  nSize = sizeof(ClockCfgCPType);
  memscpy( (pSMEM+nTip), nSize, &Clock_PerfData, nSize);
  nTip += nSize;

  if ( nTip == smem_size )
    return CLOCK_SUCCESS;
  else
    return CLOCK_ERROR;
}


/* ============================================================================
**  Function : Clock_InitRPM()
** ============================================================================
*/
/**
  Perform any initialization needed just before RPM starts.  SMEM is available
  at this time.

  @param
  @return
  CLOCK_SUCCESS -- Initialization succeeded.
  CLOCK_ERROR   -- Initialization failed.

  @dependencies
  None.

  @sa
  Clock_Init.
  boot_smem_init
*/
ClockResult Clock_InitRPM( void )
{
  ChipInfo_UpdateDisabledCPUsToDDRLocation();
  Clock_UpdateMCShubMinMaxFreq();
  /* Store config data to SMEM for sharing with AOP */
  return Clock_ShareDataToAOP();
}


/* ============================================================================
**  Function : Clock_ApplyWorkarounds()
** ============================================================================
*/
/**
  Appply HW workarounds

  @dependencies
  None.
*/
static void Clock_ApplyWorkarounds(void)
{
  /*
   * All the below workarounds are described in
   * Clocks HPG Section 14: Known bugs and workarounds
   */

  /*
   * SW WA to address CR QCTDD06646862 : This overrides the IGNORE_PMU_CLK_DIS
   * bit for pcie axi master clock.This setting will disable h/w clock gating
   * for gcc_pcie_0/1_mstr_axi_clk.Otherwise the clocks stay off in L1ss
   * causing access issue to MHI registers.
   */
    
   HWIO_OUTF(GCC_PCIE_0_MSTR_AXI_CBCR, IGNORE_PMU_CLK_DIS,0x1);

  /* 
   * WA for QCTDD09243048 : SMMU Sync/TLBI timeout issue is reported
   * during boot-up due to presence of pending transactions in SMMU-TCU,
   * awaiting walker(PTW) responses from GEMNOC.Below WA resolves this issue.
   */

  HWIO_OUTF(GCC_MMU_TCU_CBCR,IGNORE_PMU_CLK_DIS,0x1);
  
  /*
   * To address the CR QCTDD08009315 set GCC_WPSS_AXI_CBCR__IGNORE_PMU_CLK_DIS 
   * as is required gcc_wpss_axi_clk for TZ static XPU configuration. 
   * Since WPSS is in off state, and PMU disables gcc_wpss_axi_clk.
   */
   
  HWIO_OUTF(GCC_WPSS_AXI_CBCR,IGNORE_PMU_CLK_DIS,0x1);
  
  /* QCTDD07831731 Timestamp stall issue in SNOC-VCD collapse scenario */
  HWIO_OUTF(GCC_QDSS_STM_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  
  /*
   * SW needs to program IGNORE_RPMH_CLK_DIS bit of GCC_AGGRE_NOC_*_TUNNEL_CBCR
   * to 1 (since we need CONFIG NOC clocks to be running even when RPMh does a
   * sysnoc VCD clk_disable). The clock will be stopped by arc_cx_clk_dis
   * before CX collapse.
   */
  HWIO_OUTF(GCC_AGGRE_NOC_EAST_TUNNEL_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_AGGRE_NOC_NORTH_TUNNEL_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_AGGRE_NOC_SOUTH_TUNNEL_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_AGGRE_NOC_WEST_TUNNEL_ASYNC_BRIDGE_CENTER_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_AGGRE_NOC_WEST_TUNNEL_CBCR, IGNORE_RPMH_CLK_DIS, 1);

  /*
   * To address the CR QCTDD07047020, SW should program the S and W values to
   * 0x1 (from 0x2) for the following clocks (pscbc power down/up (req/ack) is
   * taking ~4.5us, due to this overall PMU wakeup or sleep times are getting\
   * extended (close to 5.5us)):
   */

  // set wakeup value
  HWIO_OUTF(GCC_AGGRE_NOC_AUDIO_TBU_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_PCIE_TBU_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_TBU1_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_TBU2_CBCR, WAKEUP, 1);
  HWIO_OUTF(GCC_DISP_HF_AXI_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF0_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF1_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_SF0_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMU_TCU_CBCR, WAKEUP, 1); 



  // set sleep value
  HWIO_OUTF(GCC_AGGRE_NOC_AUDIO_TBU_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_PCIE_TBU_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_TBU1_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_TBU2_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_DISP_HF_AXI_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF0_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF1_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_SF0_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMU_TCU_CBCR, SLEEP, 1);


  //Need to retain only SYS_TCU memory content across XO shutdown
  HWIO_OUTF(GCC_MMU_TCU_CBCR,       FORCE_MEM_CORE_ON, 1);


  /*
   * Set MICRO_FORCE_MEM_CORE_ON so that memories are retained during
   * PMU gating.
   */
  HWIO_OUTF(GCC_MMU_TCU_SREG_MISC, MMU_TCU_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_ANOC_TBU_SREG_MISC, AUDIO_TBU_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_ANOC_TBU_SREG_MISC, TBU_1_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_ANOC_TBU_SREG_MISC, TBU_2_MICRO_FORCE_MEM_CORE_ON, 1);

  /*
   * gcc_memred_p2s_clk is unused post boot.
   */
  HWIO_OUTF(GCC_MEMRED_P2S_CBCR , CLK_ENABLE, 0);

  /* QCTDD10170163 needs to set IGNORE RPMH CLK DISABLE for PMU CORE CBCR.
   * ace condition between DDRAUX turning the PMU VCD off during DDRSS power down and AOP
   * trying to handle a PMU error
   */
   HWIO_OUTF(GCC_PMU_CORE_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  Clock_DisabeTBUTCU_Clks();
}


/* ============================================================================
**  Function : Clock_DisableUnusedClocks()
** ============================================================================
*/
/**
  Disable unused clocks to save power.

  @dependencies
  None.
*/
static bool Clock_DisableUnusedClocks(void)
{
 /* Disabling these debug clocks is causing boot up crashes when CPUCP ACG feature is enabled.
   Issue is not seen when jtag attached. without JTAG NOC error for unclocked access to ETM Register space. */

#if 0
  /*
   * The following clocks default on but are debug related.
   * Turning them off to optimize power.
   */
  if (!Clock_DisableClockInternal(HWIO_ADDR(GCC_APSS_QDSS_APB_CBCR)))
    return FALSE;
  if (!Clock_DisableClockInternal(HWIO_ADDR(GCC_APSS_QDSS_TSCTR_CBCR)))
    return FALSE;
  if (!Clock_DisableClockInternal(HWIO_ADDR(GCC_CPUSS_AT_CBCR)))
    return FALSE;
  if (!Clock_DisableClockInternal(HWIO_ADDR(GCC_CPUSS_TRIG_CBCR)))
    return FALSE;
#endif


  return TRUE;
}


/* ============================================================================
**  Function : Clock_InitImage
** ============================================================================
*/
/*!

    This function initializes clock resources for XBL Loader
*/
ClockResult Clock_InitImage
(
  rail_voltage_level eBootCorner
)
{  
  /* Need to put OPMODE under SW control. */
  HWIO_OUTF(AOSS_CC_PLL0_MODE_SEL, SELECT_BIT0, 1);
  HWIO_OUTF(AOSS_CC_PLL1_MODE_SEL, SELECT_BIT0, 1);
  /* Enabling the gpll-0 Odd output manually as not set in PBL */
  HWIO_OUTF(GCC_GPLL0_PLL_USER_CTL, POST_DIV_RATIO_ODD, 2); //Enabling POST_DIV_RATIO_ODD to 2(DIVIDE_BY_3)
  HWIO_OUTF(GCC_GPLL0_PLL_USER_CTL, PLLOUT_ODD_EN, 1);

  /*
   * Speed up the CPU and NOCs.
   */
  if (!Clock_SetCPUPerfLevel()) return CLOCK_ERROR;
  if (!Clock_SetSysPerfLevel()) return CLOCK_ERROR;

  /* Select AOP PLL1 as the source for AOP_PLL0 */
  HWIO_OUTF( AOSS_CC_PLL_CLK_SEL, PLL0_CLK_REF_SEL, 1);

  Clock_EnableBootClocks();

  /*Enbaling UFS JTAG programmer path. without this, REFGEN Access is failing.*/
  Clock_EnableClockInternal(HWIO_ADDR(GCC_CFG_NOC_LPASS_CBCR));
  
  Clock_InitRefgen();

 /* Skipping below code for Device Programmer path */
  if(PcdGet32 (PcdBuildType) == 4)
  {
	return CLOCK_SUCCESS;
  }
  if (!Clock_DisableUnusedClocks()) return CLOCK_ERROR;

  /*
   * Init LPASS.
   */
  if (!Clock_InitLPASS()) return CLOCK_ERROR;

  /*
   * Initialize DDR clocks.
   */
  if (!Clock_InitDDR()) return CLOCK_ERROR;

  /*
   * Enable Spread spectrum for GPLL9.
   * Setting comes from HSR.
   * Mike will work on auto-generating this for Kailua.
   */
  HWIO_OUT(GCC_GPLL9_PLL_SSC, 0xFF08);

  /*
   * Configure all GPLLs.
   */
  for (int i = 0; i < SIZEOF_ARRAY(aGplls); i++)
  {
    Clock_ConfigurePLL(aGplls[i], NULL);
  }

  /*
   * Apply clock workarounds for HW issue
   */
  Clock_ApplyWorkarounds();

  /*
   * Enable ODSC
   */
  if (Boot_Clock_ODSC_Ctl == TRUE)
  {
    Clock_EnableODSCCtl();
  }

  /*
   * Enable DCG
   */
  if (Boot_Clock_DCG_Ctl == TRUE)
  {
    Clock_EnableDCGCtl();
  }

  /*
   * Enable HW clock dividers based on activity
   */
  if (Boot_Clock_DCD == TRUE)
  {
    Clock_EnableDynClkDivide();
  }

  return CLOCK_SUCCESS;
}


/* ============================================================================
**  Function : Clock_ExitBoot
** ============================================================================
*/
/*!

    This function turns off clocks that were used during boot, but are not
    needed after boot.  This should be called at the end of boot.

    @return
    CLOCK_SUCCESS -- Initialization succeeded.
    CLOCK_ERROR   -- Initialization failed.

   @dependencies
    None.

*/
ClockResult Clock_ExitBoot(void)
{
  Clock_UpdateVCDsMinMaxFreq();
  /*
   * De-init LPASS.
   */
  if (!Clock_DeInitLPASS()) return CLOCK_ERROR;


  //Enabling ODSC and DCG after ICB_Config_Init is done, otherwise bootup crash is seen
  HWIO_OUTF(GCC_QMIP_GPU_AHB_CBCR, HW_CTL,0x1);
  HWIO_OUTF(GCC_QMIP_LPASS_TBU_AHB_CBCR, HW_CTL,0x1);
  HWIO_OUTF(GCC_GPU_MEMNOC_GFX_CBCR, HW_CTL,0x1);

  return CLOCK_SUCCESS;
}

/*
==============================================================================
  @file ClockXBL.c

  Clock functions for the XBL Loader Clock Driver.

  Copyright (c) 2017-2019 QUALCOMM Technologies, Inc.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential.

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
  &ClockDomain_GCC_GCCCNOCNORTHQX,
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
  HWIO_ADDR(DPCC_MC_SRC0_ROOT_DCD_DIV_DCDR),
  HWIO_ADDR(DPCC_MC_SRC1_ROOT_DCD_DIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_EAST_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_EAST_TUNNEL_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_NORTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_NORTH_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_NORTH_TUNNEL_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_PCIE_NORTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_TUNNEL_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_WEST_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_WEST_TUNNEL_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CFG_NOC_LPASS_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CNOC_CENTER_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CNOC_NORTH_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_CENTER_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_DDRSS_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_EAST_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_MMNOC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_NORTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_SOUTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_WEST_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CPUSS_AXI_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_GPU_MEMNOC_GFX_DCD_CDIV_DCDR),
  // HWIO_ADDR(GCC_IPA_2X_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  // HWIO_ADDR(GCC_MEMNOC_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  HWIO_ADDR(GCC_MMNOC_HF_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MMNOC_SF_QX_DCD_CDIV_DCDR),
  // HWIO_ADDR(GCC_MMU_TCU_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  // HWIO_ADDR(GCC_MSS_OFFLINE_AXI_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  // HWIO_ADDR(GCC_MSS_Q6_MEMNOC_AXI_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  HWIO_ADDR(GCC_SHRM_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_GC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_LPASS_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_NAV_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_TME_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_TURING_Q6_AXI_DCD_CDIV_DCDR),
  // HWIO_ADDR(TURING_STRM_COMMON_DCD_CDIV_DCDR), // Will be cleared by Turing SSR
  /*
   * Mutimedia DCDs are enabled in TZ
   */
  // HWIO_ADDR(CAM_CC_CAMNOC_AXI_DCD_DIV_DCDR),
  // HWIO_ADDR(VCODEC_VIDEO_CC_MVS0C_DIV_DCDR),
  // HWIO_ADDR(VCODEC_VIDEO_CC_MVS1C_DIV_DCDR),
};

/* ODSC control variables. */
boolean Boot_Clock_HW_Ctl = TRUE;

/*
 * Generate this list
 */
uint32_t Clock_HwCtl_Cfg[] =
{
  /*==========================
      ODSC Clocks
  ============================*/

  // HWIO_ADDR(GCC_AGGRE_NOC_AHB_CBCR),  // Side effect to power seqs. Clocks HPG Ch 12.2
  // HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_AHB_CFG_CBCR), // Side effect to power seqs. Clocks HPG Ch 12.2
  HWIO_ADDR(GCC_AOSS_CNOC_S_AHB_CBCR),
  // HWIO_ADDR(GCC_BOOT_ROM_AHB_CBCR), // block's main clock, connected to BOOT image rom and other logic, Clocks HPG Ch 12.2
  HWIO_ADDR(GCC_CE1_AHB_CBCR),
  HWIO_ADDR(GCC_DPM_CX_AHB_CBCR),
  HWIO_ADDR(GCC_DPM_MX_AHB_CBCR),
  // HWIO_ADDR(GCC_GPU_CFG_AHB_CBCR), // Clock used for internal AHB traffic as well as different event sampling., Clocks HPG Ch 12.2
  HWIO_ADDR(GCC_IPCC_AHB_CBCR),
  /*
   * QCTDD06416011: MMNOC Error Interrupt is not pending at GIC when
   * QDSC is enabled
   */
  // HWIO_ADDR(GCC_MMNOC_AHB_CFG_CBCR),
  HWIO_ADDR(GCC_MSS_CFG_AHB_CBCR),
  // HWIO_ADDR(GCC_PCIE_0_CFG_AHB_CBCR), // used for summary interrupt processing and synchronization, Clocks HPG Ch 12.2
  // HWIO_ADDR(GCC_PCIE_0_SLV_AXI_CBCR), // used for summary interrupt processing and synchronization, Clocks HPG Ch 12.2
  // HWIO_ADDR(GCC_PCIE_1_CFG_AHB_CBCR), // used for summary interrupt processing and synchronization, Clocks HPG Ch 12.2
  // HWIO_ADDR(GCC_PCIE_1_SLV_AXI_CBCR), // used for summary interrupt processing and synchronization, Clocks HPG Ch 12.2
  HWIO_ADDR(GCC_PDM_AHB_CBCR),
  // HWIO_ADDR(GCC_QDSS_CFG_AHB_CBCR), // Side effect to power sequence., Clocks HPG Ch 12.2
  HWIO_ADDR(GCC_QMIP_AGGRE_NOC_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_CAMERA_NRT_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_CAMERA_RT_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_DISP_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_GPU_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_LPASS_TBU_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_MSS_OFFLINE_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_MSS_Q6_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_PCIE_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_TURING_NSP_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_CV_CPU_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_CVP_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_V_CPU_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_VCODEC_AHB_CBCR),
  HWIO_ADDR(GCC_QUPV3_WRAP_0_S_AHB_CBCR),
  HWIO_ADDR(GCC_QUPV3_WRAP_1_S_AHB_CBCR),
  HWIO_ADDR(GCC_QUPV3_WRAP_2_S_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_CX_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MMCX_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXA_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXC_AHB_CBCR),
  HWIO_ADDR(GCC_SP_CFG_AHB_CBCR),
  // HWIO_ADDR(GCC_TCU_CFG_QX_CBCR), // used for registers local for SMMU, Clocks HPG Ch 12.2
  // HWIO_ADDR(GCC_TLMM_AHB_CBCR), // clock is used for summary interrupt processing, Clocks HPG Ch 12.2
  HWIO_ADDR(GCC_TURING_CFG_AHB_CBCR),

  /*
   * External disable signals from outside the NOC keeps these slaves off even
   * when there is a bus transaction directed to one of these slaves. ODSC has
   * been disabled as a workaround for this issue.
   */
  // HWIO_ADDR(GCC_CAMERA_AHB_CBCR),
  // HWIO_ADDR(GCC_DISP_AHB_CBCR),
  // HWIO_ADDR(GCC_IPA_AHB_CBCR),
  // HWIO_ADDR(GCC_UFS_PHY_AHB_CBCR),
  // HWIO_ADDR(GCC_VIDEO_AHB_CBCR),

  /*
   * QCTDD06117925: ODSC FSM stuck at WFOFF state, which is a transient state
   * between ON and OFF. In this state odsc_cbc_en is 0 and clk is expected to
   * stop toggle so that FSM can go to OFF, but hw_clk_en is forced to be 1 and
   * keeps the clk toggling.
   */
  // HWIO_ADDR(GCC_AHB2PHY_NORTH_CBCR),
  // HWIO_ADDR(GCC_AHB2PHY_SOUTH_CBCR),
  // HWIO_ADDR(GCC_CFG_NOC_PCIE_ANOC_AHB_CBCR),
  // HWIO_ADDR(GCC_VS_CTRL_AHB_CBCR),

  /*==========================
      MEMNOC Clocks
  ============================*/

  /*
   *  ECO for QCTDD07108582 for Waipio v1 causes more issues.
   *  This clock must be enabled under SW control as a workaround.
   *  QCTDD07436397 tracks the ECO bug.
   */
  //HWIO_ADDR(GCC_DDRSS_GPU_AXI_CBCR),
  HWIO_ADDR(GCC_DDRSS_MSS_Q6_AXI_CBCR),
  HWIO_ADDR(GCC_DDRSS_TCU_CBCR),
  HWIO_ADDR(GCC_DDRSS_TURING_Q6_AXI_CBCR),

  /*
   * RUMI will crash in TZ SMMU init if this clock is turned off
   */
  // HWIO_ADDR(GCC_GPU_MEMNOC_GFX_CBCR),

  HWIO_ADDR(GCC_MEMNOC_CBCR),
  HWIO_ADDR(GCC_MSS_OFFLINE_AXI_CBCR),
  HWIO_ADDR(GCC_MSS_Q6_MEMNOC_AXI_CBCR),
  HWIO_ADDR(GCC_TURING_Q6_AXI_CBCR),
  HWIO_ADDR(GCC_TURING_Q6_TBU0_CBCR),
  HWIO_ADDR(GCC_TURING_Q6_TBU1_CBCR),
  HWIO_ADDR(GCC_AGGRE_NOC_PCIE_TBU_CBCR),
};

ClockSourceNodeType* aGplls[] =
{
  &ClockSource_GCC_GCCGPLL0,
  &ClockSource_GCC_GCCGPLL1,
  &ClockSource_GCC_GCCGPLL2,
  &ClockSource_GCC_GCCGPLL3,
  &ClockSource_GCC_GCCGPLL4,
  &ClockSource_GCC_GCCGPLL5,
  &ClockSource_GCC_GCCGPLL6,
  &ClockSource_GCC_GCCGPLL7,
  &ClockSource_GCC_GCCGPLL8,
  &ClockSource_GCC_GCCGPLL9,
};


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
    return &ClockDomain_APSSCC_APSSCCSILVERMUX;
  }
  else if (nBootCoreIdx == 4)
  {
    return &ClockDomain_APSSCC_APSSCCGOLDMUX;
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
  HWIO_OUTF(GCC_DDRSS_CONFIG_NOC_SF_CBCR, IGNORE_RPMH_CLK_DIS,1);
  HWIO_OUTF(GCC_DDRSS_GPU_AXI_CBCR, IGNORE_PMU_CLK_DIS,1);
  HWIO_OUTF(GCC_DDRSS_GPU_AXI_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_MMNOC_HF_QX_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_MMNOC_SF_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_MODEM_CBCR, IGNORE_RPMH_CLK_DIS,1);
  HWIO_OUTF(GCC_DDRSS_MSS_Q6_AXI_CBCR, IGNORE_RPMH_CLK_DIS,1);
  HWIO_OUTF(GCC_DDRSS_PCIE_SF_TBU_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_SNOC_GC_AXI_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_SNOC_SF_AXI_CBCR, IGNORE_RPMH_CLK_DIS, 1); 
  HWIO_OUTF(GCC_DDRSS_TCU_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_TURING_Q6_AXI_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_MEMNOC_CBCR, IGNORE_RPMH_CLK_DIS, 1);

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
  if (pBootDomain == &ClockDomain_APSSCC_APSSCCSILVERMUX)
  {
    pNonBootDomain = &ClockDomain_APSSCC_APSSCCGOLDMUX;
  }
  /*
   * Booting from Gold core.
   */
  else
  {
    pNonBootDomain = &ClockDomain_APSSCC_APSSCCSILVERMUX;
  }

  /* Set CPU speed */
  Clock_SetDomainBootFMax(pBootDomain);

  if (!Clock_SetDomainFreq(pNonBootDomain,
                           600000,
                           CLOCK_FREQUENCY_KHZ_AT_LEAST))
  {
    return FALSE;
  }

  if (!Clock_SetDomainFreq(&ClockDomain_APSSCC_APSSCCGOLDPLUSMUX,
                           600000,
                           CLOCK_FREQUENCY_KHZ_AT_LEAST))
  {
    return FALSE;
  }

  /* Set L3 speed */
  Clock_SetDomainBootFMax(&ClockDomain_APSSCC_APSSCCL3MUX);

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
  /*
   * LPASS Core needs to be powered up so that ICB can progream
   * LPASS with it's SCID.
   */
  Clock_EnableClockInternal(HWIO_ADDR(GCC_CFG_NOC_LPASS_CBCR));
  Clock_EnableClockInternal(HWIO_ADDR(GCC_LPASS_CFG_NOC_SWAY_CBCR));

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
  /*
   * Disable clocks that were enabled in Clock_InitLPASS and not needed anymore.
   */
  Clock_DisableClockInternal(HWIO_ADDR(LPASS_LPASS_CORE_CC_SYSNOC_MPORT_CORE_CBCR));
  Clock_DisablePowerDomainInternal(HWIO_ADDR(LPASS_LPASS_CORE_HM_GDSCR));
  HWIO_OUTF(LPASS_LPASS_TOP_CC_LPI_SWAY_AHB_LS_CBCR, HW_CTL, 0);
  Clock_DisableClockInternal(HWIO_ADDR(GCC_LPASS_CFG_NOC_SWAY_CBCR));

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

static void Clock_EnableHwCtl
(
  void
)
{
  uintptr_t nAddr;

  for (int i = 0; i < SIZEOF_ARRAY(Clock_HwCtl_Cfg); i++)
  {
    nAddr = Clock_HwCtl_Cfg[i];
    outpdw(nAddr, inpdw(nAddr) | CLK_HW_CTL_MASK);
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
  /*
   * REfgen HPG Section 2.1.2
   * REFGEN NXGEN register settings recommendation for XBL
   */

  /*
   * TBD [ Program the Vcomp threshold level.]
   */
  // HWIO_OUT(PHY_REFGEN_0_NORTH_IP_TUNEH, ???);
  // HWIO_OUT(PHY_REFGEN_SOUTH_IP_TUNEH, ???);
  // HWIO_OUT(PHY_REFGEN_2_NORTH_IP_TUNEH, ???);

  /*
   * Bring up REFGEN into function mode
   */

  // Check whether Initialization done
  if (!RUMI_CHECK())
  {
    while(!HWIO_INF(PHY_REFGEN_0_NORTH_RESTRIM_CODE_STATUS, REFGEN_READY));
    while(!HWIO_INF(PHY_REFGEN_SOUTH_RESTRIM_CODE_STATUS, REFGEN_READY));
    while(!HWIO_INF(PHY_REFGEN_2_NORTH_RESTRIM_CODE_STATUS, REFGEN_READY));
  }

  // Programs REFGEN to accept votes via Hardware pins.
  HWIO_OUT(PHY_REFGEN_0_NORTH_CMN_REFGEN_CTRL1, 0x8);
  HWIO_OUT(PHY_REFGEN_SOUTH_CMN_REFGEN_CTRL1, 0x8);
  HWIO_OUT(PHY_REFGEN_2_NORTH_CMN_REFGEN_CTRL1, 0x8);

  //Prepare for future analog rail collapse - clamp analog inputs to digital
  HWIO_OUT(PHY_REFGEN_0_NORTH_CMN_REFGEN_CTRL2, 0x3);
  HWIO_OUT(PHY_REFGEN_SOUTH_CMN_REFGEN_CTRL2, 0x3);
  HWIO_OUT(PHY_REFGEN_2_NORTH_CMN_REFGEN_CTRL2, 0x3);
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

  if (!strcmp("core", pClockGroup->szName))
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
   * To address QCTDD07073315, we need to set the following bits
   * SMMU clock disable signal sometimes gets stuck at 0x1 which forces these
   * clocks off incorrectly. set IGNORE_PMU_CLK_DIS to allow these clocks to
   * turn on.
   */
  HWIO_OUTF(GCC_AGGRE_NOC_AUDIO_TBU_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  //HWIO_OUTF(GCC_AGGRE_NOC_PCIE_TBU_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  HWIO_OUTF(GCC_AGGRE_NOC_TBU1_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  HWIO_OUTF(GCC_AGGRE_NOC_TBU2_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  HWIO_OUTF(GCC_DDRSS_TCU_CBCR, IGNORE_PMU_CLK_DIS, 0x1);
  //HWIO_OUTF(GCC_MMNOC_TBU_HF0_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  //HWIO_OUTF(GCC_MMNOC_TBU_HF1_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  //HWIO_OUTF(GCC_MMNOC_TBU_HF2_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  //HWIO_OUTF(GCC_MMNOC_TBU_HF3_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  //HWIO_OUTF(GCC_MMNOC_TBU_SF0_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  //HWIO_OUTF(GCC_MMNOC_TBU_SF1_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  HWIO_OUTF(GCC_TURING_Q6_TBU0_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  HWIO_OUTF(GCC_TURING_Q6_TBU1_CBCR, IGNORE_PMU_CLK_DIS,0x1);
  
  /*
   * SW WA to address CR QCTDD06646862 : This overrides the IGNORE_PMU_CLK_DIS
   * bit for pcie axi master clock.This setting will disable h/w clock gating
   * for gcc_pcie_0/1_mstr_axi_clk.Otherwise the clocks stay off in L1ss
   * causing access issue to MHI registers.
   */
    
   HWIO_OUTF(GCC_PCIE_0_MSTR_AXI_CBCR, IGNORE_PMU_CLK_DIS,0x1);
   HWIO_OUTF(GCC_PCIE_1_MSTR_AXI_CBCR, IGNORE_PMU_CLK_DIS,0x1);

  /* 
   * WA for QCTDD09243048 : SMMU Sync/TLBI timeout issue is reported
   * during boot-up due to presence of pending transactions in SMMU-TCU,
   * awaiting walker(PTW) responses from GEMNOC.Below WA resolves this issue.
   */

  HWIO_OUTF(GCC_MMU_TCU_CBCR,IGNORE_PMU_CLK_DIS,0x1);
  
  /*
   * SW needs to program IGNORE_RPMH_CLK_DIS bit of GCC_AGGRE_NOC_*_TUNNEL_CBCR
   * to 1 (since we need CONFIG NOC clocks to be running even when RPMh does a
   * sysnoc VCD clk_disable). The clock will be stopped by arc_cx_clk_dis
   * before CX collapse.
   */
  HWIO_OUTF(GCC_AGGRE_NOC_EAST_TUNNEL_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_AGGRE_NOC_NORTH_TUNNEL_CBCR, IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_AGGRE_NOC_SOUTH_TUNNEL_CBCR, IGNORE_RPMH_CLK_DIS, 1);
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
  HWIO_OUTF(GCC_CAMERA_HF_AXI_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_CAMERA_SF_AXI_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_DISP_HF_AXI_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_DISP_SF_AXI_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF0_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF1_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF2_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF3_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_SF0_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_SF1_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_MMU_TCU_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_TURING_Q6_TBU0_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_TURING_Q6_TBU1_CBCR, WAKEUP, 1);
  HWIO_OUTF(GCC_VIDEO_AXI0_CBCR, WAKEUP, 1); 
  HWIO_OUTF(GCC_VIDEO_AXI1_CBCR, WAKEUP, 1); 

  // set sleep value
  HWIO_OUTF(GCC_AGGRE_NOC_AUDIO_TBU_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_PCIE_TBU_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_TBU1_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_AGGRE_NOC_TBU2_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_CAMERA_HF_AXI_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_CAMERA_SF_AXI_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_DISP_HF_AXI_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_DISP_SF_AXI_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF0_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF1_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF2_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_HF3_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_SF0_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMNOC_TBU_SF1_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_MMU_TCU_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_TURING_Q6_TBU0_CBCR, SLEEP, 1); 
  HWIO_OUTF(GCC_TURING_Q6_TBU1_CBCR, SLEEP, 1);
  HWIO_OUTF(GCC_VIDEO_AXI0_CBCR, SLEEP, 1);
  HWIO_OUTF(GCC_VIDEO_AXI1_CBCR, SLEEP, 1);

  /*
   * Program debug dividers for gold core so that the frequency can be
   * measured accurately.
   */
  HWIO_OUTF(APSS_CC_GOLD_PRE_ACD_DEBUG_DIV_CDIVR, CLK_DIV, 7);
  HWIO_OUTF(APSS_CC_GOLD_POST_ACD_DEBUG_DIV_CDIVR, CLK_DIV, 7);
  HWIO_OUTF(APSS_CC_GOLD_PLUS_PRE_ACD_DEBUG_DIV_CDIVR, CLK_DIV, 7);
  HWIO_OUTF(APSS_CC_GOLD_PLUS_POST_ACD_DEBUG_DIV_CDIVR, CLK_DIV, 7);

  /*
   * HW CR QCTDD04458151
   *
   * These TBU/TCU clocks are SREG_PSCBCs, but aren't under a GDSC. Since
   * there's no GDSC, the SREG_PSCBC memory collapse signal is taken
   * from the RPMh signal when BCM enters CP0. However, since there's no
   * GDS HW controller there's also no handshake with the TCU, which causes
   * issues. The memories must be retained across collapse if there's no
   * handshake. The MMNOC TBU clocks are under a GDSC, so no need to force
   * the memories on for them.
   */
  HWIO_OUTF(GCC_AGGRE_NOC_AUDIO_TBU_CBCR, FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_AGGRE_NOC_TBU1_CBCR,      FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_AGGRE_NOC_TBU2_CBCR,      FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_MMU_TCU_CBCR,             FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GPUCC_GPU_CC_MEMNOC_GFX_CBCR, FORCE_MEM_CORE_ON, 1);

  /*
   * Set MICRO_FORCE_MEM_CORE_ON so that memories are retained during
   * PMU gating.
   */
  HWIO_OUTF(GCC_MMU_TCU_SREG_MISC, MMU_TCU_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_ANOC_TBU_SREG_MISC, AUDIO_TBU_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_ANOC_TBU_SREG_MISC, TBU_1_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_ANOC_TBU_SREG_MISC, TBU_2_MICRO_FORCE_MEM_CORE_ON, 1);

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
  
  /*
   * Aggre noc west clocks are tied low and default on.
   * Turning them off to optimize power.
   */
  if (!Clock_DisableClockInternal(HWIO_ADDR(GCC_AGGRE_NOC_WEST_AXI_CBCR )))
    return FALSE;
  if (!Clock_DisableClockInternal(HWIO_ADDR(GCC_AGGRE_NOC_WEST_TUNNEL_CBCR)))
    return FALSE;

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

  /*
   * Speed up the CPU and NOCs.
   */
  if (!Clock_SetCPUPerfLevel()) return CLOCK_ERROR;
  if (!Clock_SetSysPerfLevel()) return CLOCK_ERROR;

  /* Select AOP PLL1 as the source for AOP_PLL0 */
  HWIO_OUTF( AOSS_CC_PLL_CLK_SEL, PLL0_CLK_REF_SEL, 1);

  Clock_EnableBootClocks();
  Clock_InitRefgen();

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
   * Enable DCG
   */
  if (Boot_Clock_HW_Ctl == TRUE)
  {
    Clock_EnableHwCtl();
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
  /*
   * De-init LPASS.
   */
  if (!Clock_DeInitLPASS()) return CLOCK_ERROR;

  return CLOCK_SUCCESS;
}

/*
==============================================================================
  @file ClockXBL.c

  Clock functions for the XBL Loader Clock Driver.

  Copyright (c) 2021-2022 QUALCOMM Technologies, Inc.  All Rights Reserved.
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
#include "icbcfg.h"
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

/*=========================================================================
      Globals
==========================================================================*/

extern ClockBSPType ClockBSP;

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
  &ClockDomain_AOSSCC_AOSSCCRO,
  &ClockDomain_AOSSCC_AOSSCCSWAO,
  &ClockDomain_AOSSCC_AOSSCCSWAOTS,
};

/* Clock performance CP for sharing with AOP */
ClockCfgCPType Clock_PerfData;

/* DCD control variables. */
boolean Boot_Clock_DCD = TRUE;

/* List of registers to initialize for DCD setup. */
uint32_t Clock_DCD_Cfg[] =
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
  HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_HS_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_SOUTH_TUNNEL_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_WEST_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_AGGRE_NOC_WEST_TUNNEL_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CFG_NOC_LPASS_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CNOC_CENTER_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CNOC_NORTH_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CNOC_PERIPH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CNOC_PERIPH_NORTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CNOC_PERIPH_SOUTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_CENTER_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_DDRSS_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_EAST_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_MMNOC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_NORTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_SOUTH_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CONFIG_NOC_WEST_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_CPUSS_AXI_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_GPU_MEMNOC_GFX_DCD_CDIV_DCDR), // Enabled because DCD cannot be used
  // HWIO_ADDR(GCC_IPA_2X_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  HWIO_ADDR(GCC_LPASS_DCD_CDIV_DCDR),
  // HWIO_ADDR(GCC_MEMNOC_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  HWIO_ADDR(GCC_MMNOC_HF_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MMNOC_SF_QX_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_MMU_TCU_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  // HWIO_ADDR(GCC_MSS_OFFLINE_AXI_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  // HWIO_ADDR(GCC_MSS_Q6_MEMNOC_AXI_DCD_CDIV_DCDR), // Should be DCG, Clocks HPG Ch 4
  HWIO_ADDR(GCC_SHRM_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_GC_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_NAV_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_SF_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_SYS_NOC_TME_DCD_CDIV_DCDR),
  HWIO_ADDR(GCC_TURING_Q6_AXI_DCD_CDIV_DCDR),
  // All other DCDs are enabled in TZ
};

/* ODSC control variables. */
boolean Boot_Clock_HW_Ctl = TRUE;

/*
 * Generate this list
 */
uint32_t Clock_HwCtl_Cfg[] =
{
  // On Demand Slave Clocking (ODSC)
  // Kailua GCC HPG Chapter 5
  HWIO_ADDR(GCC_QMIP_AGGRE_NOC_AHB_CBCR),
//  HWIO_ADDR(GCC_TCU_CFG_QX_CBCR), // TCU page table corruption
  HWIO_ADDR(GCC_CAMERA_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_CAMERA_NRT_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_CAMERA_RT_AHB_CBCR),
  HWIO_ADDR(GCC_DISP_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_DISP_AHB_CBCR),
  HWIO_ADDR(GCC_VIDEO_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_CVP_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_VCODEC_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_V_CPU_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_VIDEO_CV_CPU_AHB_CBCR),
  HWIO_ADDR(GCC_QDSS_CFG_AHB_CBCR),
//  HWIO_ADDR(GCC_AHB2PHY_0_CBCR), // DDR Training hang
  HWIO_ADDR(GCC_QUPV3_I2C_S_AHB_CBCR),
  HWIO_ADDR(GCC_QUPV3_WRAP_1_S_AHB_CBCR),
  HWIO_ADDR(GCC_QUPV3_WRAP_2_S_AHB_CBCR),
  HWIO_ADDR(GCC_PDM_AHB_CBCR),
//  HWIO_ADDR(GCC_BOOT_ROM_AHB_CBCR), // CR QCTDD08308674
//  HWIO_ADDR(GCC_TLMM_AHB_CBCR), // CR QCTDD08308674
  HWIO_ADDR(GCC_AOSS_CNOC_S_AHB_CBCR),
  HWIO_ADDR(GCC_CE1_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_LPASS_QTB_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_TURING_NSP_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_CX_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXC_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_MXA_AHB_CBCR),
  HWIO_ADDR(GCC_RBCPR_NSP_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_PCIE_AHB_CBCR),
//  HWIO_ADDR(GCC_PCIE_0_SLV_AXI_CBCR),
//  HWIO_ADDR(GCC_PCIE_0_CFG_AHB_CBCR),
//  HWIO_ADDR(GCC_PCIE_1_SLV_AXI_CBCR),
//  HWIO_ADDR(GCC_PCIE_1_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_UFS_PHY_AHB_CBCR),
  HWIO_ADDR(GCC_VS_CTRL_AHB_CBCR),
  HWIO_ADDR(GCC_IPA_AHB_CBCR),
  HWIO_ADDR(GCC_MSS_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_MSS_OFFLINE_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_MSS_Q6_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_GPU_CFG_AHB_CBCR),
  HWIO_ADDR(GCC_QMIP_GPU_AHB_CBCR),
  HWIO_ADDR(GCC_SP_CFG_AHB_CBCR),
//  HWIO_ADDR(GCC_AHB2PHY_1_CBCR), // DDR Training hang
  HWIO_ADDR(GCC_RBCPR_MMCX_AHB_CBCR),
  HWIO_ADDR(GCC_IPCC_AHB_CBCR),
  HWIO_ADDR(GCC_DPM_CX_AHB_CBCR),
  HWIO_ADDR(GCC_DPM_MX_AHB_CBCR),

  // DDRSS HW_CTL List
  // Kailua GCC HPG Chapter 5.1.1
  HWIO_ADDR(GCC_DDRSS_MSS_Q6_AXI_CBCR),
  HWIO_ADDR(GCC_DDRSS_GPU_AXI_CBCR),
  HWIO_ADDR(GCC_GPU_MEMNOC_GFX_CBCR),
//  HWIO_ADDR(GCC_MMU_TCU_CBCR),
//  HWIO_ADDR(GCC_DDRSS_TCU_CBCR),
  HWIO_ADDR(GCC_MEMNOC_CBCR),
  HWIO_ADDR(GCC_DDRSS_TURING_Q6_AXI_CBCR),
  HWIO_ADDR(GCC_MSS_OFFLINE_AXI_CBCR),
  HWIO_ADDR(GCC_MSS_Q6_MEMNOC_AXI_CBCR),
//  HWIO_ADDR(GCC_TURING_Q6_QTB0_CBCR),
  HWIO_ADDR(GCC_TURING_Q6_AXI_CBCR),
//  HWIO_ADDR(GCC_LPASS_AUDIO_QTB_CBCR),
  HWIO_ADDR(GCC_DDRSS_LPASS_SHUB_CBCR),
  HWIO_ADDR(GCC_LPASS_AON_NOC_DDRSS_SHUB_CBCR),
//  HWIO_ADDR(GCC_LPASS_AGGRE_NOC_MPU_CLIENT_DDRSS_SHUB_CBCR),
//  HWIO_ADDR(GCC_LPASS_HW_AF_NOC_DDRSS_SHUB_CBCR),
//  HWIO_ADDR(GCC_LPASS_AGGRE_NOC_DDRSS_SHUB_CBCR),
};

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

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
   * DDRSS HPG section 2.1.4 - 2.1.4 GCC Programming (Kailua)
   *
   * In PMU Bypass Mode, Kailua GEMNOC requires all its initiator clocks for
   * non-datapath operations. Examples include NIU configuration access and power
   * collapse handshake. GEMNOC is triggered for power collapse as part of the
   * SHUB VCD, after other VCDs.  As RPMh power collapses those other VCDs, it
   * asserts an RPMh clock disable on those VCD clocks to save power. Due to
   * this, when GEMNOC tries to power collapse and requests its clock for those
   * initiators, it doesn’t get the clock, resulting in a hang. For this reason,
   * the following one time settings are necessary to prevent RPMh from blocking
   * GEMNOC’s clkon requests.
   */

  /*
   * Ignore RPMH
   */
  HWIO_OUTF(GCC_DDRSS_CONFIG_NOC_SF_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_GPU_AXI_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_LPASS_SHUB_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_MMNOC_HF_QX_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_MMNOC_SF_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_MODEM_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_MSS_Q6_AXI_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_PCIE_SF_QTB_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_SNOC_GC_AXI_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_SNOC_SF_AXI_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_TCU_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_TURING_Q6_AXI_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_MEMNOC_CBCR,  IGNORE_RPMH_CLK_DIS, 1);
  HWIO_OUTF(GCC_PMU_CORE_CBCR,  IGNORE_RPMH_CLK_DIS, 1);


  /*
   * Ignore PMU
   */
  HWIO_OUTF(GCC_CAMERA_HF_AXI_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_CAMERA_SF_AXI_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_GPU_AXI_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_DDRSS_TCU_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_DISP_HF_AXI_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_LPASS_AGGRE_NOC_DDRSS_SHUB_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_LPASS_AGGRE_NOC_MPU_CLIENT_DDRSS_SHUB_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_LPASS_AON_NOC_DDRSS_SHUB_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_LPASS_HW_AF_NOC_DDRSS_SHUB_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_MMU_TCU_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_SYS_NOC_GC_AXI_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_TURING_MMNOC_SF_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_TURING_Q6_AXI_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_VIDEO_AXI0_CBCR, IGNORE_PMU_CLK_DIS, 1);
  HWIO_OUTF(GCC_VIDEO_AXI1_CBCR, IGNORE_PMU_CLK_DIS, 1);

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
  /* Requirement:  Apps needs 600 MHz GPLL0 for low voltage corners */
  Clock_SetDomainBootFMax(&ClockDomain_GCC_GCCCPUSSGPLL0);

  /* Set CPU speed */
  Clock_SetDomainBootFMax(&ClockDomain_APSSCC_APSSCCSILVERMUX);

  /* Set L3 speed */
  Clock_SetDomainBootFMax(&ClockDomain_APSSCC_APSSCCL3MUX);

  /* Set Gold core speed */
  Clock_SetDomainBootFMax(&ClockDomain_APSSCC_APSSCCGOLDMUX);

  /* Set Gold Plus core speed */
  Clock_SetDomainBootFMax(&ClockDomain_APSSCC_APSSCCGOLDPLUSMUX);

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
  HWIO_OUTF(LPASS_LPASS_TOP_CC_LPASS_CORE_SWAY_AHB_LS_CBCR, HW_CTL, 1);
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
  HWIO_OUTF(LPASS_LPASS_TOP_CC_LPASS_CORE_SWAY_AHB_LS_CBCR, HW_CTL, 0);
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
  /* Initialize the registers for DCD */
  for (int i = 0; i < SIZEOF_ARRAY(Clock_DCD_Cfg); i++ )
  {
    outpdw((uintptr_t)Clock_DCD_Cfg[i], CLK_DCD_ENABLE);
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

  if(ICBCFG_SUCCESS == ICB_Config_EarlyInit("/dev/icbcfg/boot"))
  {
    for (int i = 0; i < SIZEOF_ARRAY(Clock_HwCtl_Cfg); i++)
    {
      nAddr = Clock_HwCtl_Cfg[i];
      outpdw(nAddr, inpdw(nAddr) | CLK_HW_CTL_MASK);
    }
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
  
  /* section 2.1.14 from the REFGEN HPG
   * By default, STATUS_TIMER = 0x2
   * -- refgen status wait timer 1.5uSec for refgens in all NXGEN IPs, 
   * except: 
   * Kailua R1(1.00 and 1.01) register configuration in XBL 
   * 0x0000007C STATUS_TIMER = 0x1 -- refgen status wait timer 1.8uSec 
   * Reason for the SWA in XBL is because REFGEN core clk in Kailua R1 is 9.6MHz
  */
  if ((ChipInfo_GetChipVersion() < CHIPINFO_VERSION(2,0)))
  {
    HWIO_OUT(PHY_REFGEN_0_NORTH_STATUS_TIMER, 0x1);
    HWIO_OUT(PHY_REFGEN_SOUTH_STATUS_TIMER, 0x1);
    HWIO_OUT(PHY_REFGEN_2_NORTH_STATUS_TIMER, 0x1);
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
  if (!strcmp("core", pClockGroup->szName))
  {
    *pnFrequencyHz = Clock_GetDomainFrequency(&ClockDomain_APSSCC_APSSCCSILVERMUX);
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
    Clock_PerfData.nDDR = DDR_GetPerfLevel();
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
   * To address DDR read path failure observed when switching fast SHUB
   * clock from Clock-Plan 6 on GCC_GPLL5 to Clock-Plan 5 on GCC_GPLL4,
   * HW fix was designed and introduced through ECO nr. QCTDD06083810.
   * However, this HW fix is disabled by default and legacy HW design
   * is in place. To enable the HW fix solution, the following bits need
   * to be programmed to 0x1:
   */
  HWIO_OUTM(GCC_SPARE1_REG, 0x33, 0x33);

  /*
   * Temporary workaround for VAPPS power down hang.
   * Follow up required to understand the issue and implement any
   * required long term solution.
   */
  HWIO_OUTF(GCC_TURING_MMNOC_SF_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);

  /*
   * For the following TCU clocks (TCU-QTB link clocks) we need to program
   * IGNORE_RPMH_CLK_DIS in the respective CBCR register (CR QCTDD08205470),
   * for fencing issues:
   */
  HWIO_OUTF(GCC_TCU_ANOC_QTB1_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);
  HWIO_OUTF(GCC_TCU_ANOC_QTB2_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);
  HWIO_OUTF(GCC_TCU_MMNOC_QTB_SF_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);
  HWIO_OUTF(GCC_TCU_MMNOC_QTB_HF01_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);
  HWIO_OUTF(GCC_TCU_MMNOC_QTB_HF23_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);
  HWIO_OUTF(GCC_TCU_ANOC_PCIE_QTB_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);
  HWIO_OUTF(GCC_TCU_TURING_Q6_QTB0_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);
  HWIO_OUTF(GCC_TCU_LPASS_AUDIO_QTB_CBCR, IGNORE_RPMH_CLK_DIS, 0x1);

  /*
   * GCC HPG Section 6.10
   * Micro/Macro Handling of Memory Sleep signals.
   */
  HWIO_OUTF(GCC_MMU_TCU_SREG_MISC, MMU_TCU_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_LPASS_SREG_MISC, AUDIO_QTB_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_MMNOC_SREG_MISC, SF_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_MMNOC_SREG_MISC, HF_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_TURING_QTB_SREG_MISC, QTB_0_MICRO_FORCE_MEM_CORE_ON, 1);
  HWIO_OUTF(GCC_ANOC_PCIE_SREG_MISC, AGGRE_NOC_PCIE_AXI_MICRO_FORCE_MEM_CORE_ON, 1);

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
   * Issues are seen during AOSS collapse/wake sequences when the PLL isn't
   * outputting a clock. To fix these we always need an output clock even when
   * the PLL is in STANDBY. Therefore, select SLEEP_CLK as the bypass clock and
   * keep OUTCTRL under SW mode so it remains enabled even when the PLL has
   * been put into STANDBY by HW. The Pongo HAL code should configure
   * XO_CLK_AT_OUT to 1 so the reference clock (SLEEP_CLK in this case) is
   * bypassed to the outputs when not in RUN.
   */
  HWIO_OUTF(AOSS_CC_PLL_CLK_SEL, PLL1_CLK_XO_SEL, 1);
  HWIO_OUTF(AOSS_CC_PLL1_OUTCTRL, SEL, 1);

  /*
   * Speed up the CPU and NOCs.
   */
  if (!Clock_SetCPUPerfLevel()) return CLOCK_ERROR;

  /*
   * Increase CDIVs before ramping up their associated RCG frequencies, since
   * some clock's timing closure expects a static divide and increasing the RCG
   * first would overclock them.
   */
  HWIO_OUTF(AOSS_CC_RO_DIV_CDIVR, CLK_DIV, 1);
  HWIO_OUTF(AOSS_CC_EUD_AT_DIV_CDIVR, CLK_DIV, 4);

  if (!Clock_SetSysPerfLevel()) return CLOCK_ERROR;

  /* Select AOP PLL1 as the source for AOP_PLL0 */
  HWIO_OUTF(AOSS_CC_PLL_CLK_SEL, PLL0_CLK_REF_SEL, 1);

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
   * Configure all sources.
   */
  for (int i = 0; i < ClockBSP.nNumSources; i++)
  {
    Clock_ConfigurePLL(ClockBSP.aSources[i], NULL);
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
   * Enable DCD
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

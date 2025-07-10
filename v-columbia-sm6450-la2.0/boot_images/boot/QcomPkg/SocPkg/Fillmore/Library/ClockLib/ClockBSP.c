/*
==============================================================================

FILE:         ClockBSP.c

DESCRIPTION:
  This file contains the clock driver BSP data.

  Auto-generated from the following IPCat controller releases:

    SM7450v1 (fillmore_1.0):
      PLL_HSR   : 5.0
      APSS_CC     : fillmore_apss_cc_fillmore_apss_1.0_p3q3r88_fp13 [fillmore_apss_cc.r2]
      CAM_CC    : fillmore_cam_cc_z_cam_cc_fillmore_5.2_p3q2r11_fp13 [fillmore_cam_cc.r3]
      DISP_CC   : fillmore_disp_cc_z_disp_cc_fillmore_5.2_p3q2r23_fp10 [fillmore_disp_cc.r2]
      GCC         : fillmore_gcc_z_fillmore_clk_ctl_1.0_p3q3r24_fp18 [fillmore_gcc.r13]
      GPU_CC    : fillmore_gpu_cc_z_gpu_cc_fillmore_5.2_p3q2r5_fp6 [fillmore_gpu_cc.r3]
      VIDEO_CC  : fillmore_video_cc_z_video_cc_fillmore_5.2_p3q2r23_fp9 [fillmore_video_cc.r3]


  Generated using the following clockdrivergen settings:

CLOCKDRIVERGEN_CONFIG = \
{'db_override': {'GCC': {'cbc': {'gcc_cxo2_tx1_clkref_en1': {'d_registers': {'cbcr_name': 'GCC_CXO2_TX1_CLKREF_EN1'},
                                                             'd_sw_owner': {'APCS': 'RW'},
                                                             'l_master': ['bi_tcxo']},
                                 'gcc_eusb3_0_clkref_en': {'d_registers': {'cbcr_name': 'GCC_EUSB3_0_CLKREF_EN'},
                                                           'd_sw_owner': {'APCS': 'RW'},
                                                           'l_master': ['bi_tcxo']},
                                 'gcc_gpu_memnoc_gfx_clk_en': {'d_registers': {'cbcr_name': 'GCC_GPU_MEMNOC_GFX_CLK_EN'},
                                                               'd_sw_owner': {'APCS': 'RW'},
                                                               'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_AUDIO_TBU_CLK'},
                                                                                'd_sw_owner': {'APCS': 'RW'},
                                                                                'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_TBU_CLK'},
                                                                               'd_sw_owner': {'APCS': 'RW'},
                                                                               'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_aggre_noc_mmu_tbu1_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU1_CLK'},
                                                                           'd_sw_owner': {'APCS': 'RW'},
                                                                           'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_aggre_noc_mmu_tbu2_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU2_CLK'},
                                                                           'd_sw_owner': {'APCS': 'RW'},
                                                                           'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_all_smmu_mmu_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_ALL_SMMU_MMU_CLK'},
                                                                     'd_sw_owner': {'APCS': 'RW'},
                                                                     'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_gpu_smmu_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_GPU_SMMU_CLK'},
                                                                 'd_sw_owner': {'APCS': 'RW'},
                                                                 'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF0_CLK'},
                                                                          'd_sw_owner': {'APCS': 'RW'},
                                                                          'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF1_CLK'},
                                                                          'd_sw_owner': {'APCS': 'RW'},
                                                                          'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_tbu_hf2_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF2_CLK'},
                                                                          'd_sw_owner': {'APCS': 'RW'},
                                                                          'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_tbu_hf3_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF3_CLK'},
                                                                          'd_sw_owner': {'APCS': 'RW'},
                                                                          'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF0_CLK'},
                                                                          'd_sw_owner': {'APCS': 'RW'},
                                                                          'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF1_CLK'},
                                                                          'd_sw_owner': {'APCS': 'RW'},
                                                                          'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_mmu_tcu_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_MMU_TCU_CLK'},
                                                                'd_sw_owner': {'APCS': 'RW'},
                                                                'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_turing_mmu_tbu0_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_TURING_MMU_TBU0_CLK'},
                                                                        'd_sw_owner': {'APCS': 'RW'},
                                                                        'l_master': ['bi_tcxo']},
                                 'gcc_hlos1_vote_turing_mmu_tbu1_clk': {'d_registers': {'cbcr_name': 'GCC_HLOS1_VOTE_TURING_MMU_TBU1_CLK'},
                                                                        'd_sw_owner': {'APCS': 'RW'},
                                                                        'l_master': ['bi_tcxo']},
                                 'gcc_memnoc_mss_offline_clk_en': {'d_registers': {'cbcr_name': 'GCC_MEMNOC_MSS_OFFLINE_CLK_EN'},
                                                                   'd_sw_owner': {'APCS': 'RW'},
                                                                   'l_master': ['bi_tcxo']},
                                 'gcc_memnoc_mss_q6_clk_en': {'d_registers': {'cbcr_name': 'GCC_MEMNOC_MSS_Q6_CLK_EN'},
                                                              'd_sw_owner': {'APCS': 'RW'},
                                                              'l_master': ['bi_tcxo']},
                                 'gcc_memnoc_turing_clk_en': {'d_registers': {'cbcr_name': 'GCC_MEMNOC_TURING_CLK_EN'},
                                                              'd_sw_owner': {'APCS': 'RW'},
                                                              'l_master': ['bi_tcxo']},
                                 'gcc_mmu_memnoc_tcu_clk_en': {'d_registers': {'cbcr_name': 'GCC_MMU_MEMNOC_TCU_CLK_EN'},
                                                               'd_sw_owner': {'APCS': 'RW'},
                                                               'l_master': ['bi_tcxo']},
                                 'gcc_pcie_0_clkref_en': {'d_registers': {'cbcr_name': 'GCC_PCIE_0_CLKREF_EN'},
                                                          'd_sw_owner': {'APCS': 'RW'},
                                                          'l_master': ['bi_tcxo']},
                                 'gcc_qlink_clkref_en': {'d_registers': {'cbcr_name': 'GCC_QLINK_CLKREF_EN'},
                                                         'd_sw_owner': {'APCS': 'RW'},
                                                         'l_master': ['bi_tcxo']},
                                 'gcc_ufs_0_clkref_en': {'d_registers': {'cbcr_name': 'GCC_UFS_0_CLKREF_EN'},
                                                         'd_sw_owner': {'APCS': 'RW'},
                                                         'l_master': ['bi_tcxo']},
                                 'gcc_ufs_pad_clkref_en': {'d_registers': {'cbcr_name': 'GCC_UFS_PAD_CLKREF_EN'},
                                                           'd_sw_owner': {'APCS': 'RW'},
                                                           'l_master': ['bi_tcxo']},
                                 'gcc_usb3_0_clkref_en': {'d_registers': {'cbcr_name': 'GCC_USB3_0_CLKREF_EN'},
                                                          'd_sw_owner': {'APCS': 'RW'},
                                                          'l_master': ['bi_tcxo']},
                                 'gcc_wpss_axi_clk_en': {'d_registers': {'cbcr_name': 'GCC_WPSS_AXI_CLK_EN'},
                                                         'd_sw_owner': {'APCS': 'RW'},
                                                         'l_master': ['bi_tcxo']}},
                         'sm_gdsc': {'gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_AUDIO_TBU_GDS'},
                                                                                    'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_TBU_GDS'},
                                                                                   'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_aggre_noc_mmu_tbu1_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU1_GDS'},
                                                                               'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_aggre_noc_mmu_tbu2_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU2_GDS'},
                                                                               'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_all_smmu_mmu_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_ALL_SMMU_MMU_GDS'},
                                                                         'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_gpu_smmu_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_GPU_SMMU_GDS'},
                                                                     'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF0_GDS'},
                                                                              'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF1_GDS'},
                                                                              'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_tbu_hf2_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF2_GDS'},
                                                                              'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_tbu_hf3_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF3_GDS'},
                                                                              'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF0_GDS'},
                                                                              'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF1_GDS'},
                                                                              'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_mmu_tcu_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_MMU_TCU_GDS'},
                                                                    'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_turing_mmu_tbu0_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_TURING_MMU_TBU0_GDS'},
                                                                            'd_sw_owner': {'APCS': 'RW'}},
                                     'gcc_hlos1_vote_turing_mmu_tbu1_gds': {'d_registers': {'gdscr_name': 'GCC_HLOS1_VOTE_TURING_MMU_TBU1_GDS'},
                                                                            'd_sw_owner': {'APCS': 'RW'}}}}},
 'filter_warning': 'sw',
 'generators': [{'options': {'clock_flags': {'gcc_qupv3_wrap0_s0_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap0_s1_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap0_s2_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap0_s3_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap0_s4_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap0_s5_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap0_s6_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap0_s7_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap1_s0_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap1_s1_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap1_s2_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap1_s3_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap1_s4_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap1_s5_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap1_s6_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_qupv3_wrap1_s7_clk_src': ['DOMAIN_WAIT_FOR_ROOT_OFF'],
                                             'gcc_sys_noc_cpuss_ahb_clk': ['SUPPRESSIBLE',
                                                                           'LEAVE_ALWAYS_ON']},
                             'clock_flags_hal': {'disp_cc_mdss_mdp_clk_src': ['DOMAIN_HW_CLK_CONTROL'],
                                                 'gcc_pcie_0_aux_clk_src': ['DOMAIN_HW_CLK_CONTROL']},
                             'driver_flags': ['LOG_CLOCK_FREQ_CHANGE',
                                              'LOG_SOURCE_STATE_CHANGE'],
                             'env': ['apcs', 'gpuss'],
                             'hal_ctl_structs': {'gcc_pcie_0_gdsc': 'HAL_clk_PCIePowerDomainControl',
                                                 'gpu_cc_gx_gdsc': 'HAL_clk_GPUGxPowerDomainControl'},
                             'include_divider': ['.*'],
                             'include_file': {'HALclkPLLSettings.h': False},
                             'include_fmax': ['.*'],
                             'include_source_map': ['.*'],
                             'map_bases': True,
                             'multi_rail': True,
                             'npa_rename': {'/vcs/mxc': '/vcs/vdd_mxc',
                                            '/vcs/vdd_cam_cx': '/vcs/vdd_mm',
                                            '/vcs/vdd_mxa': '/vcs/vdd_mx'},
                             'standalone_bcrs': ['.*pcie.*', '.*usb.*']},
                 'output_dir': 'fillmore_output_dir',
                 'type': 'dalclock'}],
 'target': ['fillmore']}

==============================================================================

$Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/ClockLib/ClockBSP.c#9 $

==============================================================================
            Copyright (c) 2021, 2022, 2023 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/ClockDxe/ClockBSP.h"
#include "../HALclkLib/HALclkHWIO.h"
#include "HALhwio.h"


/*=========================================================================
      Externs
==========================================================================*/

extern HAL_clk_ClockControlType           HAL_clk_GenericClockControl;
extern HAL_clk_ClockDomainControlType     HAL_clk_GenericDomainControl;
extern HAL_clk_ClockDomainControlType     HAL_clk_GenericDomainMuxControl;
extern HAL_clk_DividerControlType         HAL_clk_GenericDividerControl;
extern HAL_clk_PowerDomainControlType     HAL_clk_GenericPowerDomainControl;
extern HAL_clk_SourceControlType          HAL_clk_LucidevoPLLControl;
extern HAL_clk_SourceControlType          HAL_clk_RivianevoPLLControl;

/*
 * Debug mux control structures.
 */
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlAPSSCC_fillmore;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlCAMCC_fillmore;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlDISPCC_fillmore;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlGCC_fillmore;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlGPUCC_fillmore;
extern HAL_clk_DebugMuxControlType        HAL_clk_DebugMuxControlVIDEOCC_fillmore;

/*
 * Custom control structures.
 */
extern HAL_clk_PowerDomainControlType     HAL_clk_GPUGxPowerDomainControl;
extern HAL_clk_PowerDomainControlType     HAL_clk_PCIePowerDomainControl;


/*=========================================================================
      Data Declarations
==========================================================================*/


/*=========================================================================
      Bases
==========================================================================*/

uintptr_t HAL_clk_nHWIOBaseAPSSHM;
uintptr_t HAL_clk_nHWIOBaseCLKCTL;
uintptr_t HAL_clk_nHWIOBaseGFX;
uintptr_t HAL_clk_nHWIOBaseIRIS;
uintptr_t HAL_clk_nHWIOBaseMDSS;
uintptr_t HAL_clk_nHWIOBaseTITANSS;

static ClockBaseType aBases[] =
{
  { APSS_HM_BASE_PHYS,        APSS_HM_BASE_SIZE,        &HAL_clk_nHWIOBaseAPSSHM       },
  { CLK_CTL_BASE_PHYS,        CLK_CTL_BASE_SIZE,        &HAL_clk_nHWIOBaseCLKCTL       },
  { GFX_BASE_PHYS,            GFX_BASE_SIZE,            &HAL_clk_nHWIOBaseGFX          },
  { IRIS_BASE_PHYS,           IRIS_BASE_SIZE,           &HAL_clk_nHWIOBaseIRIS         },
  { MDSS_BASE_PHYS,           MDSS_BASE_SIZE,           &HAL_clk_nHWIOBaseMDSS         },
  { TITAN_SS_BASE_PHYS,       TITAN_SS_BASE_SIZE,       &HAL_clk_nHWIOBaseTITANSS      },
};

/*=========================================================================
      Voltage Rails
==========================================================================*/

enum
{
  RAIL_IDX_VDD_CAM_CX,
  RAIL_IDX_VDD_CX,
  RAIL_IDX_VDD_GX,
  RAIL_IDX_VDD_MXA,
  RAIL_IDX_VDD_MXC,
};

#define RAIL_VDD_CAM_CX      (1 << RAIL_IDX_VDD_CAM_CX)
#define RAIL_VDD_CX          (1 << RAIL_IDX_VDD_CX)
#define RAIL_VDD_GX          (1 << RAIL_IDX_VDD_GX)
#define RAIL_VDD_MXA         (1 << RAIL_IDX_VDD_MXA)
#define RAIL_VDD_MXC         (1 << RAIL_IDX_VDD_MXC)

static ClockRailType ClockRail_VDDCAMCX =
{
  .szName = "/vcs/vdd_mm",
};

static ClockRailType ClockRail_VDDCX =
{
  .szName = "/vcs/vdd_cx",
};

static ClockRailType ClockRail_VDDGX =
{
  .szName = "/vcs/vdd_gx",
};

static ClockRailType ClockRail_VDDMXA =
{
  .szName = "/vcs/vdd_mx",
};

static ClockRailType ClockRail_VDDMXC =
{
  .szName = "/vcs/vdd_mxc",
};

static ClockRailType *aRails[] =
{
  [RAIL_IDX_VDD_CAM_CX]   = &ClockRail_VDDCAMCX,
  [RAIL_IDX_VDD_CX]       = &ClockRail_VDDCX,
  [RAIL_IDX_VDD_GX]       = &ClockRail_VDDGX,
  [RAIL_IDX_VDD_MXA]      = &ClockRail_VDDMXA,
  [RAIL_IDX_VDD_MXC]      = &ClockRail_VDDMXC,
};

/*=========================================================================
      Debug Muxes
==========================================================================*/

static ClockDebugMuxType ClockDebugMux_GCC =
{
  .szName       = "gcc",
  .nDivider     = 2,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlGCC_fillmore,
  },
};

static ClockDebugMuxInputDivType aMuxInputDividers_APSSCC[] =
{
  { 1, 4 },
  { 2, 4 },
  { 3, 8 },
  { 4, 8 },
  { 5, 4 },
  { 6, 4 },
  { 7, 8 },
  { 8, 8 },
  { CLOCK_DEBUG_MUX_INPUT_DIV_END },
};

static ClockDebugMuxType ClockDebugMux_APSSCC =
{
  .szName       = "apss_cc",
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 279,
  .anInputDivs  = aMuxInputDividers_APSSCC,
  .nDivider     = 4,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlAPSSCC_fillmore,
  },
};

static ClockDebugMuxType ClockDebugMux_CAMCC =
{
  .szName       = "cam_cc",
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 107,
  .nDivider     = 4,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlCAMCC_fillmore,
  },
};

static ClockDebugMuxType ClockDebugMux_DISPCC =
{
  .szName       = "disp_cc",
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 113,
  .nDivider     = 4,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlDISPCC_fillmore,
  },
};

static ClockDebugMuxType ClockDebugMux_GPUCC =
{
  .szName       = "gpu_cc",
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 366,
  .nDivider     = 2,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlGPUCC_fillmore,
  },
};

static ClockDebugMuxType ClockDebugMux_VIDEOCC =
{
  .szName       = "video_cc",
  .pParent      = &ClockDebugMux_GCC,
  .nParentSel   = 122,
  .nDivider     = 3,
  .HALDebugMux  = {
    .pmControl  = &HAL_clk_DebugMuxControlVIDEOCC_fillmore,
  },
};

static ClockDebugMuxType *aDebugMuxes[] =
{
  &ClockDebugMux_APSSCC,
  &ClockDebugMux_CAMCC,
  &ClockDebugMux_DISPCC,
  &ClockDebugMux_GCC,
  &ClockDebugMux_GPUCC,
  &ClockDebugMux_VIDEOCC,
};


/*=========================================================================
      Primary Sources
==========================================================================*/

static ClockSourceNodeType ClockSource_XO =
{
  .szName    = "/pmic/client/xo",
  .nFlags    = 0x0,
};


/*=========================================================================
      Source Register Settings
==========================================================================*/

static const ClockSourceRegSettingsType ClockSourceRegSettings_CAMCC_CAMCCPLL0[] =
{
  {
    .HALSettings = {
      .nConfigCtl   = 0x20485699,
      .nConfigCtl1  = 0x00182261,
      .nConfigCtl2  = 0x32AA299C,
      .nTestCtl     = 0x00000000,
      .nTestCtl1    = 0x00000000,
      .nTestCtl2    = 0x00000000,
      .nUserCtl     = 0x00000000,
      .nUserCtl1    = 0x00000805,
    },
  },
};

static const ClockSourceRegSettingsType ClockSourceRegSettings_CAMCC_CAMCCPLL2[] =
{
  {
    .HALSettings = {
      .nConfigCtl   = 0x90008820,
      .nConfigCtl1  = 0x00890263,
      .nConfigCtl2  = 0x00000217,
      .nTestCtl     = 0x00000000,
      .nTestCtl1    = 0x00000000,
      .nUserCtl     = 0x00000000,
      .nUserCtl1    = 0x00000000,
    },
  },
};


/*=========================================================================
      Source BSP
==========================================================================*/

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL0
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL0[] =
{
  { 1200000000, &ClockSource_XO, { 0, 0, 1, 62,  0x00008000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2, .Lucidevo.nOdd = 3} }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};
static const ClockSourceFreqConfigType ClockSourceBSPCal_CAMCC_CAMCCPLL0[] =
{
  { 1305600000, &ClockSource_XO, { 0, 0, 1, 68,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL1
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL1[] =
{
  {  520000000, &ClockSource_XO, { 0, 0, 1, 27,  0x00001555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_LOW_SVS,   },
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_LOW_SVS,   },
  {  900000000, &ClockSource_XO, { 0, 0, 1, 46,  0x0000E000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1120000000, &ClockSource_XO, { 0, 0, 1, 58,  0x00005555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1400000000, &ClockSource_XO, { 0, 0, 1, 72,  0x0000EAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL2
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL2
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL2[] =
{
  {  960000000, &ClockSource_XO, { 0, 0, 1, 50,  0x00000000, HAL_CLK_PLL_FRAC_MODE_UNKNOWN, {.Rivianevo.nEven = 2}       }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL3
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL3
 *   ClockSource_CAMCC_CAMCCPLL4
 *   ClockSource_CAMCC_CAMCCPLL5
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL3[] =
{
  {  560000000, &ClockSource_XO, { 0, 0, 1, 29,  0x00002AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_LOW_SVS,   },
  {  676000000, &ClockSource_XO, { 0, 0, 1, 35,  0x00003555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  {  950000000, &ClockSource_XO, { 0, 0, 1, 49,  0x00007AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1200000000, &ClockSource_XO, { 0, 0, 1, 62,  0x00008000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1440000000, &ClockSource_XO, { 0, 0, 1, 75,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_CAMCC_CAMCCPLL6
 *
 * Used by:
 *   ClockSource_CAMCC_CAMCCPLL6
 */
static const ClockSourceFreqConfigType ClockSourceBSP_CAMCC_CAMCCPLL6[] =
{
  {  960000000, &ClockSource_XO, { 0, 0, 1, 50,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2}        }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_DISPCC_DISPCCPLL0
 *
 * Used by:
 *   ClockSource_DISPCC_DISPCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_DISPCC_DISPCCPLL0[] =
{
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS,   },
  {  975000000, &ClockSource_XO, { 0, 0, 1, 50,  0x0000C800, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1125000000, &ClockSource_XO, { 0, 0, 1, 58,  0x00009800, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1500000000, &ClockSource_XO, { 0, 0, 1, 78,  0x00002000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_DISPCC_DISPCCPLL1
 *
 * Used by:
 *   ClockSource_DISPCC_DISPCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_DISPCC_DISPCCPLL1[] =
{
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS,   },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL0
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL0[] =
{
  {  600000000, &ClockSource_XO, { 0, 0, 1, 31,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {.Lucidevo.nEven = 2, .Lucidevo.nOdd = 3} }, RAIL_VOLTAGE_LEVEL_LOW_SVS,   },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL2
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL2[] =
{
  { 1100000000, &ClockSource_XO, { 0, 0, 1, 57,  0x00004AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL4
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL4[] =
{
  {  806000000, &ClockSource_XO, { 0, 0, 1, 41,  0x0000FAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL6
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL6[] =
{
  {  750000000, &ClockSource_XO, { 0, 0, 1, 39,  0x00001000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_GCC_GCCGPLL9
 *
 * Used by:
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GCC_GCCGPLL9[] =
{
  {  808000000, &ClockSource_XO, { 0, 0, 1, 42,  0x00001555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_GPUCC_GPUCCPLL0
 *
 * Used by:
 *   ClockSource_GPUCC_GPUCCPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GPUCC_GPUCCPLL0[] =
{
  {  460000000, &ClockSource_XO, { 0, 0, 1, 23,  0x0000F555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1,},
  {  570000000, &ClockSource_XO, { 0, 0, 1, 29,  0x0000B000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS,   },
  {  886000000, &ClockSource_XO, { 0, 0, 1, 46,  0x00002555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1080000000, &ClockSource_XO, { 0, 0, 1, 56,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1216000000, &ClockSource_XO, { 0, 0, 1, 63,  0x00005555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1352000000, &ClockSource_XO, { 0, 0, 1, 70,  0x00006AAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1560000000, &ClockSource_XO, { 0, 0, 1, 81,  0x00004000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 1650000000, &ClockSource_XO, { 0, 0, 1, 85,  0x0000F000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_NOM,       },
  { 1760000000, &ClockSource_XO, { 0, 0, 1, 91,  0x0000AAAA, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_TUR,       },
};

/*
 * ClockSourceBSP_GPUCC_GPUCCPLL1
 *
 * Used by:
 *   ClockSource_GPUCC_GPUCCPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_GPUCC_GPUCCPLL1[] =
{
  { 1000000000, &ClockSource_XO, { 0, 0, 1, 52,  0x00001555, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
};

/*
 * ClockSourceBSP_VIDEOCC_VIDEOPLL0
 *
 * Used by:
 *   ClockSource_VIDEOCC_VIDEOPLL0
 */
static const ClockSourceFreqConfigType ClockSourceBSP_VIDEOCC_VIDEOPLL0[] =
{
  {  604800000, &ClockSource_XO, { 0, 0, 1, 31,  0x00008000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_LOW_SVS,   },
  {  720000000, &ClockSource_XO, { 0, 0, 1, 37,  0x00008000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1014000000, &ClockSource_XO, { 0, 0, 1, 52,  0x0000D000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1094400000, &ClockSource_XO, { 0, 0, 1, 57,  0x00000000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1098000000, &ClockSource_XO, { 0, 0, 1, 57,  0x00003000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1332000000, &ClockSource_XO, { 0, 0, 1, 69,  0x00006000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};

/*
 * ClockSourceBSP_VIDEOCC_VIDEOPLL1
 *
 * Used by:
 *   ClockSource_VIDEOCC_VIDEOPLL1
 */
static const ClockSourceFreqConfigType ClockSourceBSP_VIDEOCC_VIDEOPLL1[] =
{
  {  840000000, &ClockSource_XO, { 0, 0, 1, 43,  0x0000C000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS,       },
  { 1098000000, &ClockSource_XO, { 0, 0, 1, 57,  0x00003000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
  { 1332000000, &ClockSource_XO, { 0, 0, 1, 69,  0x00006000, HAL_CLK_PLL_FRAC_MODE_ALPHA, {{0}}                      }, RAIL_VOLTAGE_LEVEL_SVS_L1,    },
};


/*=========================================================================
      Sources
==========================================================================*/

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL0 =
{
  .szName       = "cam_cc_pll0",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL0),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE |
                  CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL1 =
{
  .szName       = "cam_cc_pll1",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL1),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL2 =
{
  .szName       = "cam_cc_pll2",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL2,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL2),
  .nRailMask    = RAIL_VDD_MXA,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL2_PLL_MODE),
    .pmControl      = &HAL_clk_RivianevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSP_CAMCC_CAMCCPLL2,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL2),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL2,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL2),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL3 =
{
  .szName       = "cam_cc_pll3",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL3,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL3),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL3_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL4 =
{
  .szName       = "cam_cc_pll4",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL3,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL3),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL4_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL5 =
{
  .szName       = "cam_cc_pll5",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL3,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL3),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL5_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_CAMCC_CAMCCPLL6 =
{
  .szName       = "cam_cc_pll6",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_CAMCC_CAMCCPLL6,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_CAMCC_CAMCCPLL6),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(CAM_CC_PLL6_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_DISPCC_DISPCCPLL0 =
{
  .szName       = "disp_cc_pll0",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_DISPCC_DISPCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_DISPCC_DISPCCPLL0),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(DISP_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_DISPCC_DISPCCPLL1 =
{
  .szName       = "disp_cc_pll1",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_DISPCC_DISPCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_DISPCC_DISPCCPLL1),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(DISP_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL0 =
{
  .szName       = "gcc_gpll0",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL0),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE |
                  CLOCK_CONFIG_PLL_FSM_MODE_ENABLE |
                  CLOCK_CONFIG_PLL_ODD_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL0_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x1},
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL2 =
{
  .szName       = "gcc_gpll2",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL2,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL2),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL2_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x4},
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL4 =
{
  .szName       = "gcc_gpll4",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL4,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL4),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL4_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x10},
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL6 =
{
  .szName       = "gcc_gpll6",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL6,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL6),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL6_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x40},
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GCC_GCCGPLL9 =
{
  .szName       = "gcc_gpll9",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL |
                  CLOCK_FLAG_READ_ONLY,
  .aBSP         = ClockSourceBSP_GCC_GCCGPLL9,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GCC_GCCGPLL9),
  .nRailMask    = RAIL_VDD_CX,
  .nConfigMask  = CLOCK_CONFIG_PLL_FSM_MODE_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GCC_GPLL9_PLL_MODE),
    .VoterRegister  = {HWIO_PHYS(GCC_PROC_CLK_PLL_ENA_VOTE), 0x200},
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GPUCC_GPUCCPLL0 =
{
  .szName       = "gpu_cc_pll0",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_GPUCC_GPUCCPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GPUCC_GPUCCPLL0),
  .nRailMask    = RAIL_VDD_MXA,
  .nConfigMask  = CLOCK_CONFIG_PLL_EVEN_OUTPUT_ENABLE,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GPUCC_GPU_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_GPUCC_GPUCCPLL1 =
{
  .szName       = "gpu_cc_pll1",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_GPUCC_GPUCCPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_GPUCC_GPUCCPLL1),
  .nRailMask    = RAIL_VDD_MXA,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(GPUCC_GPU_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_VIDEOCC_VIDEOPLL0 =
{
  .szName       = "video_pll0",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_VIDEOCC_VIDEOPLL0,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_VIDEOCC_VIDEOPLL0),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(VCODEC_VIDEO_CC_PLL0_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};

static ClockSourceNodeType ClockSource_VIDEOCC_VIDEOPLL1 =
{
  .szName       = "video_pll1",
  .nFlags       = CLOCK_FLAG_INTERNAL_CONTROL,
  .aBSP         = ClockSourceBSP_VIDEOCC_VIDEOPLL1,
  .nBSPLen      = SIZEOF_ARRAY(ClockSourceBSP_VIDEOCC_VIDEOPLL1),
  .nRailMask    = RAIL_VDD_MXC,
  .nConfigMask  = 0x0,
  .eDisableMode = HAL_CLK_SOURCE_DISABLE_MODE_STANDBY,
  .HALSource = {
    .nAddr          = HWIO_PHYS(VCODEC_VIDEO_CC_PLL1_PLL_MODE),
    .pmControl      = &HAL_clk_LucidevoPLLControl,
  },
  .pCalibrationFreqConfig     = ClockSourceBSPCal_CAMCC_CAMCCPLL0,
  .nCalibrationFreqConfigLen  = SIZEOF_ARRAY(ClockSourceBSPCal_CAMCC_CAMCCPLL0),
  .pRegSettings               = ClockSourceRegSettings_CAMCC_CAMCCPLL0,
  .nRegSettingsLen            = SIZEOF_ARRAY(ClockSourceRegSettings_CAMCC_CAMCCPLL0),
};


static ClockSourceNodeType *aSources[] =
{
  &ClockSource_CAMCC_CAMCCPLL0,
  &ClockSource_CAMCC_CAMCCPLL1,
  &ClockSource_CAMCC_CAMCCPLL2,
  &ClockSource_CAMCC_CAMCCPLL3,
  &ClockSource_CAMCC_CAMCCPLL4,
  &ClockSource_CAMCC_CAMCCPLL5,
  &ClockSource_CAMCC_CAMCCPLL6,
  &ClockSource_DISPCC_DISPCCPLL0,
  &ClockSource_DISPCC_DISPCCPLL1,
  &ClockSource_GCC_GCCGPLL0,
  &ClockSource_GCC_GCCGPLL2,
  &ClockSource_GCC_GCCGPLL4,
  &ClockSource_GCC_GCCGPLL6,
  &ClockSource_GCC_GCCGPLL9,
  &ClockSource_GPUCC_GPUCCPLL0,
  &ClockSource_GPUCC_GPUCCPLL1,
  &ClockSource_VIDEOCC_VIDEOPLL0,
  &ClockSource_VIDEOCC_VIDEOPLL1,
  &ClockSource_XO,
};


/*=========================================================================
      Dividers
==========================================================================*/

static ClockDividerNodeType aDividers[] =
{
  {
    .szName    = "cam_cc_debug_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_pll_test_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_bps_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_BPS_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_ife_0_csid_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_IFE_0_CSID_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_ife_0_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_IFE_0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_ife_1_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_IFE_1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_ife_2_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_IFE_2_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_ipe_0_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_IPE_0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "cam_cc_spdm_jpeg_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(CAM_CC_SPDM_JPEG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_debug_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_byte0_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_BYTE0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_byte1_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_BYTE1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_DPTX0_LINK_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_DPTX1_LINK_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_DPTX2_LINK_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_DPTX3_LINK_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_debug_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_crypto_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_CRYPTO_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel1_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_PIXEL1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_PIXEL_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_mdp_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_MDP_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk0_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_PCLK0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk1_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_PCLK1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_rot_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_MDSS_SPDM_ROT_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "disp_cc_pll_test_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(DISP_CC_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_0_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPLL0_UFS_PHY_RX_SYMBOL_0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_1_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPLL0_UFS_PHY_RX_SYMBOL_1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_tx_symbol_0_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPLL0_UFS_PHY_TX_SYMBOL_0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpu_pll0_main_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPU_PLL0_MAIN_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_gpu_trig_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_GPU_TRIG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_pdm_xo4_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_PDM_XO4_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap0_core_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP0_CORE_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap1_core_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gcc_usb30_prim_mock_utmi_postdiv_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GCC_USB30_PRIM_MOCK_UTMI_POSTDIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_debug_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_demet_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_DEMET_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_hub_ahb_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_HUB_AHB_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_hub_cx_int_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_HUB_CX_INT_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_pll_test_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_spdm_gx_gfx3d_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_SPDM_GX_GFX3D_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "gpu_cc_xo_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(GPUCC_GPU_CC_XO_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_debug_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_DEBUG_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_mvs0_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_mvs0c_div2_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_DIV2_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_mvs1_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_mvs1c_div2_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_DIV2_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
  {
    .szName    = "video_cc_pll_test_div_clk_src",
    .nFlags    = 0x0,
    .HALDivider = {
      .nAddr       = HWIO_PHYS(VCODEC_VIDEO_CC_PLL_TEST_DIV_CDIVR),
      .pmControl   = &HAL_clk_GenericDividerControl,
    },
  },
};

/*=========================================================================
      Domain BSP
==========================================================================*/

/*
 * ClockDomainBSP_CAMCC_CAMCCBPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCBPS
 *   ClockDomain_CAMCC_CAMCCJPEG
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCBPS[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  160000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  200000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL6,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[5] = CAM_CC_PLL6_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCAMNOCAXI
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXI
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCAMNOCAXI[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  240000000, &ClockSource_CAMCC_CAMCCPLL6,             { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[5] = CAM_CC_PLL6_OUT_EVEN */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL6,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[5] = CAM_CC_PLL6_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCCI0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCCI0[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   37500000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     32,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCPHYRX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCPHYRX[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  200000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  266666667, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     3,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCSI0PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI1PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI2PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI3PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI4PHYTIMER
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  200000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCFASTAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCFASTAHB
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCFASTAHB[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   80000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     15,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  100000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  200000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCICP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCICP
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCICP[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL6,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = CAM_CC_PLL6_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE0
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIFE0[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  280000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 0] /* 280.0  */ },    /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
  {  338000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 1] /* 338.0  */ },    /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
  {  475000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 2] /* 475.0  */ },    /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 3] /* 600.0  */ },    /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
  {  720000000, &ClockSource_CAMCC_CAMCCPLL3,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 4] /* 720.0  */ },    /* Mux[6] = CAM_CC_PLL3_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIFE0CSID
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE0CSID
 *   ClockDomain_CAMCC_CAMCCIFE1CSID
 *   ClockDomain_CAMCC_CAMCCIFE2CSID
 *   ClockDomain_CAMCC_CAMCCIFELITECSID
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIFE0CSID[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  266666667, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     3,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIFE1
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE1
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIFE1[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  280000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 0] /* 280.0  */ },    /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
  {  338000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 1] /* 338.0  */ },    /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
  {  475000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 2] /* 475.0  */ },    /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 3] /* 600.0  */ },    /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
  {  720000000, &ClockSource_CAMCC_CAMCCPLL4,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 4] /* 720.0  */ },    /* Mux[6] = CAM_CC_PLL4_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIFE2
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE2
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIFE2[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  280000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 0] /* 280.0  */ },    /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
  {  338000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 1] /* 338.0  */ },    /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
  {  475000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 2] /* 475.0  */ },    /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
  {  600000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 3] /* 600.0  */ },    /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
  {  720000000, &ClockSource_CAMCC_CAMCCPLL5,             { 6,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL3[ 4] /* 720.0  */ },    /* Mux[6] = CAM_CC_PLL5_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIFELITE
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFELITE
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIFELITE[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  400000000, &ClockSource_CAMCC_CAMCCPLL0,             { 3,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[3] = CAM_CC_PLL0_OUT_ODD */
  {  480000000, &ClockSource_CAMCC_CAMCCPLL6,             { 5,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = CAM_CC_PLL6_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCIPE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIPE0
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCIPE0[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  260000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 0] /* 260.0  */ },    /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 1] /* 300.0  */ },    /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
  {  450000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 2] /* 450.0  */ },    /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
  {  560000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 3] /* 560.0  */ },    /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
  {  700000000, &ClockSource_CAMCC_CAMCCPLL1,             { 4,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_CAMCC_CAMCCPLL1[ 4] /* 700.0  */ },    /* Mux[4] = CAM_CC_PLL1_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCMCLK0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCMCLK0
 *   ClockDomain_CAMCC_CAMCCMCLK1
 *   ClockDomain_CAMCC_CAMCCMCLK2
 *   ClockDomain_CAMCC_CAMCCMCLK3
 *   ClockDomain_CAMCC_CAMCCMCLK4
 *   ClockDomain_CAMCC_CAMCCMCLK5
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCMCLK0[] =
{
  {   19200000, &ClockSource_CAMCC_CAMCCPLL2,             { 5,     2,     1,     50,    0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = CAM_CC_PLL2_OUT_MAIN */
  {   24000000, &ClockSource_CAMCC_CAMCCPLL2,             { 5,     20,    1,     4,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = CAM_CC_PLL2_OUT_MAIN */
  {   68571429, &ClockSource_CAMCC_CAMCCPLL2,             { 5,     28,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = CAM_CC_PLL2_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCQDSSDEBUG
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCQDSSDEBUG
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCQDSSDEBUG[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   75000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     16,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  150000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {  300000000, &ClockSource_CAMCC_CAMCCPLL0,             { 1,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[1] = CAM_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCSLEEP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLEEP
 *   ClockDomain_DISPCC_DISPCCSLEEP
 *   ClockDomain_VIDEOCC_VIDEOCCSLEEP
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCSLEEP[] =
{
  {      32000, NULL,                                     { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = CHIP_SLEEP_CLK */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCSLOWAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLOWAHB
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCSLOWAHB[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   66666667, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     18,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
  {   80000000, &ClockSource_CAMCC_CAMCCPLL0,             { 2,     15,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[2] = CAM_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_CAMCC_CAMCCXO
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCXO
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK1
 *   ClockDomain_DISPCC_DISPCCMDSSVSYNC
 *   ClockDomain_DISPCC_DISPCCXO
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
 *   ClockDomain_GCC_GCCUSB3PRIMPHYAUX
 *   ClockDomain_VIDEOCC_VIDEOCCAHB
 *   ClockDomain_VIDEOCC_VIDEOCCXO
 */
static ClockMuxConfigType ClockDomainBSP_CAMCC_CAMCCXO[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSAHB
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSAHB
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSAHB[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   37500000, &ClockSource_DISPCC_DISPCCPLL1,           { 4,     32,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[4] = DISP_CC_PLL1_OUT_MAIN */
  {   75000000, &ClockSource_DISPCC_DISPCCPLL1,           { 4,     16,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[4] = DISP_CC_PLL1_OUT_MAIN */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSESC0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 *   ClockDomain_DISPCC_DISPCCMDSSESC1
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSESC0[] =
{
  {    6400000, &ClockSource_XO,                          { 0,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {    7680000, &ClockSource_XO,                          { 0,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {    9600000, &ClockSource_XO,                          { 0,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   12800000, &ClockSource_XO,                          { 0,     3,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSMDP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSMDP
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSMDP[] =
{
  {  200000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 0] /* 600.0  */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  325000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 1] /* 975.0  */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  375000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 2] /* 1125.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
  {  500000000, &ClockSource_DISPCC_DISPCCPLL0,           { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_DISPCC_DISPCCPLL0[ 3] /* 1500.0 */ },  /* Mux[1] = DISP_CC_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_DISPCC_DISPCCMDSSROT
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSROT
 */
static ClockMuxConfigType ClockDomainBSP_DISPCC_DISPCCMDSSROT[] =
{
  {  200000000, &ClockSource_DISPCC_DISPCCPLL1,           { 4,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[4] = DISP_CC_PLL1_OUT_MAIN */
  {  300000000, &ClockSource_DISPCC_DISPCCPLL1,           { 4,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[4] = DISP_CC_PLL1_OUT_MAIN */
};

/*
 * ClockDomainBSP_GCC_GCCGP1
 *
 * Used by:
 *   ClockDomain_GCC_GCCGP1
 *   ClockDomain_GCC_GCCGP2
 *   ClockDomain_GCC_GCCGP3
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCGP1[] =
{
  {   50000000, &ClockSource_GCC_GCCGPLL0,                { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP111_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP12_CLKGEN_ACGC_CLK */
  {  200000000, &ClockSource_GCC_GCCGPLL0,                { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP12_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCPCIE0AUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0AUX
 *   ClockDomain_GCC_GCCUFSPHYPHYAUX
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCPCIE0AUX[] =
{
  {    9600000, &ClockSource_XO,                          { 0,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PHYRCHNG
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP13_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCPDM2
 *
 * Used by:
 *   ClockDomain_GCC_GCCPDM2
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCPDM2[] =
{
  {   60000000, &ClockSource_GCC_GCCGPLL0,                { 1,     20,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP9_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP0S0
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S0
 *   ClockDomain_GCC_GCCQUPV3WRAP0S1
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0S0[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP8_CLKGEN_ACGC_CLK */
  {  102400000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     128,   375,   0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {  112000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     28,    75,    0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {  117964800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     6144,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {  120000000, &ClockSource_GCC_GCCGPLL0,                { 6,     5,     0,     0,     0x06 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCQUPV3WRAP0S2
 *
 * Note: These frequencies are used by domains possibly under DFS control. The
 *       DFS-enable state will be detected during init. If under DFS control,
 *       the domain will dynamically allocate its own BSP array and populate
 *       it with configurations detected from the DFS registers.
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S2
 *   ClockDomain_GCC_GCCQUPV3WRAP0S3
 *   ClockDomain_GCC_GCCQUPV3WRAP0S4
 *   ClockDomain_GCC_GCCQUPV3WRAP0S5
 *   ClockDomain_GCC_GCCQUPV3WRAP0S6
 *   ClockDomain_GCC_GCCQUPV3WRAP0S7
 *   ClockDomain_GCC_GCCQUPV3WRAP1S2
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 *   ClockDomain_GCC_GCCQUPV3WRAP1S7
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCQUPV3WRAP0S2[] =
{
  {    7372800, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     384,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   14745600, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     768,   15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0x00 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   29491200, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     1536,  15625, 0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   32000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     75,    0x01 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   48000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     25,    0x02 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   64000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     16,    75,    0x03 }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   80000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     4,     15,    0x04 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {   96000000, &ClockSource_GCC_GCCGPLL0,                { 6,     2,     8,     25,    0x05 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP106_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 1,     12,    0,     0,     0x06 }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP8_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCSDCC2APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC2APPS
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCSDCC2APPS[] =
{
  {     400000, &ClockSource_XO,                          { 0,     24,    1,     4,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[0] = BI_TCXO */
  {   25000000, &ClockSource_GCC_GCCGPLL0,                { 6,     24,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {   50000000, &ClockSource_GCC_GCCGPLL0,                { 6,     12,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  100000000, &ClockSource_GCC_GCCGPLL0,                { 6,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP105_CLKGEN_ACGC_CLK */
  {  202000000, &ClockSource_GCC_GCCGPLL9,                { 2,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     },                                                            /* Mux[2] = GCC_GPLL9_OUT_MAIN */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYAXI[] =
{
  {   25000000, &ClockSource_GCC_GCCGPLL0,                { 6,     24,    0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP113_CLKGEN_ACGC_CLK */
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP113_CLKGEN_ACGC_CLK */
  {  150000000, &ClockSource_GCC_GCCGPLL0,                { 1,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP14_CLKGEN_ACGC_CLK */
  {  300000000, &ClockSource_GCC_GCCGPLL0,                { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP14_CLKGEN_ACGC_CLK */
  {  375000000, &ClockSource_GCC_GCCGPLL6,                { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        },                                                            /* Mux[2] = GCC_GPLL6_OUT_MAIN_PWRGRP0_CLKGEN_ACGC_CLK */
  {  403000000, &ClockSource_GCC_GCCGPLL4,                { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR_L1,     },                                                            /* Mux[5] = GCC_GPLL4_OUT_MAIN_PWRGRP4_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUFSPHYICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUFSPHYICECORE[] =
{
  {   75000000, &ClockSource_GCC_GCCGPLL0,                { 6,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP113_CLKGEN_ACGC_CLK */
  {  150000000, &ClockSource_GCC_GCCGPLL0,                { 1,     8,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP14_CLKGEN_ACGC_CLK */
  {  300000000, &ClockSource_GCC_GCCGPLL0,                { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP14_CLKGEN_ACGC_CLK */
  {  550000000, &ClockSource_GCC_GCCGPLL2,                { 2,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        },                                                            /* Mux[2] = GCC_GPLL2_OUT_MAIN */
  {  600000000, &ClockSource_GCC_GCCGPLL0,                { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR_L1,     },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP14_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static ClockMuxConfigType ClockDomainBSP_GCC_GCCUSB30PRIMMASTER[] =
{
  {   66666667, &ClockSource_GCC_GCCGPLL0,                { 6,     9,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },                                                            /* Mux[6] = GCC_GPLL0_OUT_EVEN_PWRGRP104_CLKGEN_ACGC_CLK */
  {  133333333, &ClockSource_GCC_GCCGPLL0,                { 1,     9,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
  {  200000000, &ClockSource_GCC_GCCGPLL0,                { 1,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
  {  240000000, &ClockSource_GCC_GCCGPLL0,                { 1,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        },                                                            /* Mux[1] = GCC_GPLL0_OUT_MAIN_PWRGRP6_CLKGEN_ACGC_CLK */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCFF
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCFF
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCFF[] =
{
  {  200000000, NULL,                                     { 5,     6,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[5] = GPLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCGMU
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGMU
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCGMU[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[0] = BI_TCXO */
  {  200000000, NULL,                                     { 6,     3,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[6] = GPLL0_OUT_MAIN_DIV */
  {  500000000, &ClockSource_GPUCC_GPUCCPLL1,             { 3,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[3] = GPU_CC_PLL1_OUT_MAIN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCGXGFX3D
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGXGFX3D
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCGXGFX3D[] =
{
  {  230000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[0] /* 420.0  */ },  /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  285000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 1] /* 570.0  */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  443000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 2] /* 886.0  */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  540000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 3] /* 1080.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  608000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L2,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 4] /* 1216.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  676000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 5] /* 1352.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  780000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM_L1,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 6] /* 1560.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  825000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR,        {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 7] /* 1650.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
  {  880000000, &ClockSource_GPUCC_GPUCCPLL0,             { 1,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_TUR_L1,     {{0}}, &ClockSourceBSP_GPUCC_GPUCCPLL0[ 8] /* 1760.0 */ },    /* Mux[1] = GPU_CC_PLL0_OUT_EVEN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCHUB
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCHUB
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCHUB[] =
{
  {  150000000, NULL,                                     { 6,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[6] = GPLL0_OUT_MAIN_DIV */
  {  240000000, NULL,                                     { 5,     5,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        },                                                            /* Mux[5] = GPLL0_OUT_MAIN */
  {  300000000, NULL,                                     { 5,     4,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        },                                                            /* Mux[5] = GPLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_GPUCC_GPUCCXO
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCXO
 */
static ClockMuxConfigType ClockDomainBSP_GPUCC_GPUCCXO[] =
{
  {   19200000, &ClockSource_XO,                          { 0,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },                                                            /* Mux[0] = BI_TCXO */
};

/*
 * ClockDomainBSP_VIDEOCC_VIDEOCCMVS0
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS0
 */
static ClockMuxConfigType ClockDomainBSP_VIDEOCC_VIDEOCCMVS0[] =
{
  {  604800000, &ClockSource_VIDEOCC_VIDEOPLL0,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL0[ 0] /* 604.0  */ },  /* Mux[1] = VIDEO_PLL0_OUT_MAIN */
  {  720000000, &ClockSource_VIDEOCC_VIDEOPLL0,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_LOW_SVS,    {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL0[ 1] /* 720.0  */ },  /* Mux[1] = VIDEO_PLL0_OUT_MAIN */
  { 1014000000, &ClockSource_VIDEOCC_VIDEOPLL0,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL0[ 2] /* 1014.0 */ },  /* Mux[1] = VIDEO_PLL0_OUT_MAIN */
  { 1094400000, &ClockSource_VIDEOCC_VIDEOPLL0,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL0[ 3] /* 1094.0 */ },  /* Mux[1] = VIDEO_PLL0_OUT_MAIN */
  { 1098000000, &ClockSource_VIDEOCC_VIDEOPLL0,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS_L1,     {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL0[ 4] /* 1098.0 */ },  /* Mux[1] = VIDEO_PLL0_OUT_MAIN */
  { 1332000000, &ClockSource_VIDEOCC_VIDEOPLL0,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL0[ 5] /* 1332.0 */ },  /* Mux[1] = VIDEO_PLL0_OUT_MAIN */
};

/*
 * ClockDomainBSP_VIDEOCC_VIDEOCCMVS1
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS1
 */
static ClockMuxConfigType ClockDomainBSP_VIDEOCC_VIDEOCCMVS1[] =
{
  {  840000000, &ClockSource_VIDEOCC_VIDEOPLL1,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL1[ 0] /* 840.0  */ },  /* Mux[1] = VIDEO_PLL1_OUT_MAIN */
  { 1098000000, &ClockSource_VIDEOCC_VIDEOPLL1,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_SVS,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL1[ 1] /* 1098.0 */ },  /* Mux[1] = VIDEO_PLL1_OUT_MAIN */
  { 1332000000, &ClockSource_VIDEOCC_VIDEOPLL1,           { 1,     2,     0,     0,     0xFF }, RAIL_VOLTAGE_LEVEL_NOM,        {{0}}, &ClockSourceBSP_VIDEOCC_VIDEOPLL1[ 2] /* 1332.0 */ },  /* Mux[1] = VIDEO_PLL1_OUT_MAIN */
};


/*=========================================================================
      Domain Source Maps
==========================================================================*/

/*
 * ClockSourceMap_APSSCC_APSSCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_APSSCC_APSSCCDEBUGMUX
 */
static const ClockSourceMapType ClockSourceMap_APSSCC_APSSCCDEBUGMUX[] =
{
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCBPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCBPS
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXI
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 *   ClockDomain_CAMCC_CAMCCCSI0PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI1PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI2PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI3PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI4PHYTIMER
 *   ClockDomain_CAMCC_CAMCCFASTAHB
 *   ClockDomain_CAMCC_CAMCCICP
 *   ClockDomain_CAMCC_CAMCCIFE0CSID
 *   ClockDomain_CAMCC_CAMCCIFE1CSID
 *   ClockDomain_CAMCC_CAMCCIFE2CSID
 *   ClockDomain_CAMCC_CAMCCIFELITE
 *   ClockDomain_CAMCC_CAMCCIFELITECSID
 *   ClockDomain_CAMCC_CAMCCJPEG
 *   ClockDomain_CAMCC_CAMCCQDSSDEBUG
 *   ClockDomain_CAMCC_CAMCCSLOWAHB
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCBPS[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            },
  { 2,  600000000, &ClockSource_CAMCC_CAMCCPLL0,            },
  { 3,  400000000, &ClockSource_CAMCC_CAMCCPLL0,            },
  { 5,  480000000, &ClockSource_CAMCC_CAMCCPLL6,            },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCDEBUGMUX
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCDEBUGMUX[] =
{
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCIFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE0
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCIFE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL3,            },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCIFE1
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE1
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCIFE1[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL4,            },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCIFE2
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE2
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCIFE2[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 6,          0, &ClockSource_CAMCC_CAMCCPLL5,            },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCIPE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIPE0
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCIPE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 4,          0, &ClockSource_CAMCC_CAMCCPLL1,            },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCMCLK0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCMCLK0
 *   ClockDomain_CAMCC_CAMCCMCLK1
 *   ClockDomain_CAMCC_CAMCCMCLK2
 *   ClockDomain_CAMCC_CAMCCMCLK3
 *   ClockDomain_CAMCC_CAMCCMCLK4
 *   ClockDomain_CAMCC_CAMCCMCLK5
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCMCLK0[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 3,  480000000, &ClockSource_CAMCC_CAMCCPLL2,            },
  { 5,  960000000, &ClockSource_CAMCC_CAMCCPLL2,            },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCPLLTESTMUX
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCPLLTESTMUX[] =
{
  { 0, 1200000000, &ClockSource_CAMCC_CAMCCPLL0,            },
  { 1,          0, &ClockSource_CAMCC_CAMCCPLL1,            },
  { 2,  960000000, &ClockSource_CAMCC_CAMCCPLL2,            },
  { 3,          0, &ClockSource_CAMCC_CAMCCPLL3,            },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCSLEEP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLEEP
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCSLEEP[] =
{
  { 0,      32000, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_CAMCC_CAMCCXO
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCXO
 */
static const ClockSourceMapType ClockSourceMap_CAMCC_CAMCCXO[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSAHB
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSAHB
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSAHB[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 4,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          },
  { 6,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSBYTE0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE1
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK1
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSBYTE0[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,          0, NULL,                                    },
  { 2,          0, NULL,                                    },
  { 3,          0, NULL,                                    },
  { 4,          0, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX
 *   ClockDomain_DISPCC_DISPCCMDSSVSYNC
 *   ClockDomain_DISPCC_DISPCCXO
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,          0, NULL,                                    },
  { 2,          0, NULL,                                    },
  { 3,          0, NULL,                                    },
  { 4,          0, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,          0, NULL,                                    },
  { 2,          0, NULL,                                    },
  { 3,          0, NULL,                                    },
  { 4,          0, NULL,                                    },
  { 6,          0, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSESC0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 *   ClockDomain_DISPCC_DISPCCMDSSESC1
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSESC0[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 2,          0, NULL,                                    },
  { 4,          0, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCMDSSMDP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSMDP
 *   ClockDomain_DISPCC_DISPCCMDSSROT
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCMDSSMDP[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,          0, &ClockSource_DISPCC_DISPCCPLL0,          },
  { 4,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          },
  { 6,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCPLLTESTMUX
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCPLLTESTMUX[] =
{
  { 0,          0, &ClockSource_DISPCC_DISPCCPLL0,          },
  { 1,  600000000, &ClockSource_DISPCC_DISPCCPLL1,          },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_DISPCC_DISPCCSLEEP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCSLEEP
 */
static const ClockSourceMapType ClockSourceMap_DISPCC_DISPCCSLEEP[] =
{
  { 0,      32000, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCGP1
 *
 * Used by:
 *   ClockDomain_GCC_GCCGP1
 *   ClockDomain_GCC_GCCGP2
 *   ClockDomain_GCC_GCCGP3
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCGP1[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 5,      32000, NULL,                                    },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPCIE0AUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0AUX
 *   ClockDomain_GCC_GCCUSB3PRIMPHYAUX
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPCIE0AUX[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 5,      32000, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPCIE0PHYRCHNG
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PHYRCHNG
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPCIE0PHYRCHNG[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPCIE0PIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PIPE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPCIE0PIPE[] =
{
  { 0,          0, NULL,                                    },
  { 1,          0, NULL,                                    },
  { 2,   19200000, &ClockSource_XO,                         },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCPDM2
 *
 * Used by:
 *   ClockDomain_GCC_GCCPDM2
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCPDM2[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCQUPV3WRAP0S0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S0
 *   ClockDomain_GCC_GCCQUPV3WRAP0S1
 *   ClockDomain_GCC_GCCQUPV3WRAP0S2
 *   ClockDomain_GCC_GCCQUPV3WRAP0S3
 *   ClockDomain_GCC_GCCQUPV3WRAP0S4
 *   ClockDomain_GCC_GCCQUPV3WRAP0S5
 *   ClockDomain_GCC_GCCQUPV3WRAP0S6
 *   ClockDomain_GCC_GCCQUPV3WRAP0S7
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 *   ClockDomain_GCC_GCCQUPV3WRAP1S2
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 *   ClockDomain_GCC_GCCQUPV3WRAP1S7
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCQUPV3WRAP0S0[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCSDCC2APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC2APPS
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCSDCC2APPS[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 2,  808000000, &ClockSource_GCC_GCCGPLL9,               },
  { 5,  806000000, &ClockSource_GCC_GCCGPLL4,               },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYAXI[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 2,  750000000, &ClockSource_GCC_GCCGPLL6,               },
  { 3, 1100000000, &ClockSource_GCC_GCCGPLL2,               },
  { 4, 1066000000, NULL,                                    },
  { 5,  806000000, &ClockSource_GCC_GCCGPLL4,               },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYICECORE[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 2, 1100000000, &ClockSource_GCC_GCCGPLL2,               },
  { 4, 1066000000, NULL,                                    },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYPHYAUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYPHYAUX
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYPHYAUX[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYRXSYMBOL0
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL0[] =
{
  { 0,          0, NULL,                                    },
  { 1,          0, NULL,                                    },
  { 2,   19200000, &ClockSource_XO,                         },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL1
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYRXSYMBOL1
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL1[] =
{
  { 0,          0, NULL,                                    },
  { 1,          0, NULL,                                    },
  { 2,   19200000, &ClockSource_XO,                         },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUFSPHYTXSYMBOL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYTXSYMBOL0
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUFSPHYTXSYMBOL0[] =
{
  { 0,          0, NULL,                                    },
  { 1,          0, NULL,                                    },
  { 2,   19200000, &ClockSource_XO,                         },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUSB30PRIMMASTER[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUSB30PRIMMOCKUTMI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUSB30PRIMMOCKUTMI[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,  600000000, &ClockSource_GCC_GCCGPLL0,               },
  { 6,  300000000, &ClockSource_GCC_GCCGPLL0,               },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GCC_GCCUSB3PRIMPHYPIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB3PRIMPHYPIPE
 */
static const ClockSourceMapType ClockSourceMap_GCC_GCCUSB3PRIMPHYPIPE[] =
{
  { 0,          0, NULL,                                    },
  { 1,  400000000, NULL,                                    },
  { 2,   19200000, &ClockSource_XO,                         },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCDEBUGMUX
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCDEBUGMUX[] =
{
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCFF
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCFF
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCFF[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 5,  600000000, NULL,                                    },
  { 6,  300000000, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCGMU
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGMU
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCGMU[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,          0, &ClockSource_GPUCC_GPUCCPLL0,            },
  { 3, 1000000000, &ClockSource_GPUCC_GPUCCPLL1,            },
  { 5,  600000000, NULL,                                    },
  { 6,  300000000, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCGXGFX3D
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGXGFX3D
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCGXGFX3D[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,          0, &ClockSource_GPUCC_GPUCCPLL0,            },
  { 2,          0, &ClockSource_GPUCC_GPUCCPLL0,            },
  { 3, 1000000000, &ClockSource_GPUCC_GPUCCPLL1,            },
  { 4, 1000000000, &ClockSource_GPUCC_GPUCCPLL1,            },
  { 5,  600000000, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCHUB
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCHUB
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCHUB[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 3, 1000000000, &ClockSource_GPUCC_GPUCCPLL1,            },
  { 5,  600000000, NULL,                                    },
  { 6,  300000000, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCPLLTESTMUX
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCPLLTESTMUX[] =
{
  { 0,          0, &ClockSource_GPUCC_GPUCCPLL0,            },
  { 1, 1000000000, &ClockSource_GPUCC_GPUCCPLL1,            },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_GPUCC_GPUCCXO
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCXO
 */
static const ClockSourceMapType ClockSourceMap_GPUCC_GPUCCXO[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCAHB
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCAHB
 *   ClockDomain_VIDEOCC_VIDEOCCXO
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCAHB[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCMVS0
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS0
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCMVS0[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,          0, &ClockSource_VIDEOCC_VIDEOPLL0,          },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCMVS1
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS1
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCMVS1[] =
{
  { 0,   19200000, &ClockSource_XO,                         },
  { 1,          0, &ClockSource_VIDEOCC_VIDEOPLL1,          },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCPLLTESTMUX[] =
{
  { 0,          0, &ClockSource_VIDEOCC_VIDEOPLL0,          },
  { 1,          0, &ClockSource_VIDEOCC_VIDEOPLL1,          },
  { CLOCK_SOURCE_MAP_END }
};

/*
 * ClockSourceMap_VIDEOCC_VIDEOCCSLEEP
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCSLEEP
 */
static const ClockSourceMapType ClockSourceMap_VIDEOCC_VIDEOCCSLEEP[] =
{
  { 0,      32000, NULL,                                    },
  { 7,  400000000, NULL,                                    },
  { CLOCK_SOURCE_MAP_END }
};


/*=========================================================================
      Domain FMAX
==========================================================================*/

/*
 * ClockDomainFMax_APSSCC_APSSCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_APSSCC_APSSCCDEBUGMUX
 */
static const ClockFMaxType ClockDomainFMax_APSSCC_APSSCCDEBUGMUX[] =
{
  {  192000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  273600000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  350400000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  441600000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  494400000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  542400000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  600000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     },
  {  676800000, RAIL_VOLTAGE_LEVEL_TUR_L3,     },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCBPS
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCBPS
 *   ClockDomain_CAMCC_CAMCCJPEG
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCBPS[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  480000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  600000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCAMNOCAXI
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCAMNOCAXI
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCAMNOCAXI[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  480000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCCI0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCCI0
 *   ClockDomain_CAMCC_CAMCCCCI1
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCCI0[] =
{
  {   37500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCPHYRX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCPHYRX
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCPHYRX[] =
{
  {  266666667, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  400000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCCSI0PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI1PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI2PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI3PHYTIMER
 *   ClockDomain_CAMCC_CAMCCCSI4PHYTIMER
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCDEBUGMUX
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCDEBUGMUX[] =
{
  {  600000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCFASTAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCFASTAHB
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCFASTAHB[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  200000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  400000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCICP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCICP
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCICP[] =
{
  {  400000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  480000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  600000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCIFE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE0
 *   ClockDomain_CAMCC_CAMCCIFE1
 *   ClockDomain_CAMCC_CAMCCIFE2
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCIFE0[] =
{
  {  338000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  475000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  600000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  720000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCIFE0CSID
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFE0CSID
 *   ClockDomain_CAMCC_CAMCCIFE1CSID
 *   ClockDomain_CAMCC_CAMCCIFE2CSID
 *   ClockDomain_CAMCC_CAMCCIFELITECSID
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCIFE0CSID[] =
{
  {  400000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCIFELITE
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIFELITE
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCIFELITE[] =
{
  {  400000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  480000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCIPE0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCIPE0
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCIPE0[] =
{
  {  300000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  450000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  560000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  700000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCMCLK0
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCMCLK0
 *   ClockDomain_CAMCC_CAMCCMCLK1
 *   ClockDomain_CAMCC_CAMCCMCLK2
 *   ClockDomain_CAMCC_CAMCCMCLK3
 *   ClockDomain_CAMCC_CAMCCMCLK4
 *   ClockDomain_CAMCC_CAMCCMCLK5
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCMCLK0[] =
{
  {   68571429, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCPLLTESTMUX
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCPLLTESTMUX[] =
{
  {  600000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1200000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCQDSSDEBUG
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCQDSSDEBUG
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCQDSSDEBUG[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCSLEEP
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLEEP
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCSLEEP[] =
{
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCSLOWAHB
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCSLOWAHB
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCSLOWAHB[] =
{
  {   80000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_CAMCC_CAMCCXO
 *
 * Used by:
 *   ClockDomain_CAMCC_CAMCCXO
 */
static const ClockFMaxType ClockDomainFMax_CAMCC_CAMCCXO[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSAHB
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSAHB
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSAHB[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {   37500000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {   75000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE0
 *   ClockDomain_DISPCC_DISPCCMDSSBYTE1
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0[] =
{
  {  187500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  358000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX
 *   ClockDomain_DISPCC_DISPCCMDSSESC0
 *   ClockDomain_DISPCC_DISPCCMDSSESC1
 *   ClockDomain_DISPCC_DISPCCMDSSVSYNC
 *   ClockDomain_DISPCC_DISPCCXO
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK[] =
{
  {  270000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  540000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  810000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0[] =
{
  {  337500000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  405000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  675000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSDPTX3LINK
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSDPTX3LINK[] =
{
  {  270000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  594000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  810000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSMDP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSMDP
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSMDP[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  325000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  375000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  500000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK0
 *   ClockDomain_DISPCC_DISPCCMDSSPCLK1
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0[] =
{
  {  328125000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  525000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  625000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCMDSSROT
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCMDSSROT
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCMDSSROT[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  300000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCPLLTESTMUX
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCPLLTESTMUX[] =
{
  {  500000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1000000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_DISPCC_DISPCCSLEEP
 *
 * Used by:
 *   ClockDomain_DISPCC_DISPCCSLEEP
 */
static const ClockFMaxType ClockDomainFMax_DISPCC_DISPCCSLEEP[] =
{
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCGP1
 *
 * Used by:
 *   ClockDomain_GCC_GCCGP1
 *   ClockDomain_GCC_GCCGP2
 *   ClockDomain_GCC_GCCGP3
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCGP1[] =
{
  {   50000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  100000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  200000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPCIE0AUX
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0AUX
 *   ClockDomain_GCC_GCCUFSPHYPHYAUX
 *   ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI
 *   ClockDomain_GCC_GCCUSB3PRIMPHYAUX
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE0AUX[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPCIE0PHYRCHNG
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PHYRCHNG
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE0PHYRCHNG[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  100000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPCIE0PIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCPCIE0PIPE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPCIE0PIPE[] =
{
  {  125000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  250000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCPDM2
 *
 * Used by:
 *   ClockDomain_GCC_GCCPDM2
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCPDM2[] =
{
  {   60000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP0S0
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S0
 *   ClockDomain_GCC_GCCQUPV3WRAP0S1
 *   ClockDomain_GCC_GCCQUPV3WRAP1S0
 *   ClockDomain_GCC_GCCQUPV3WRAP1S1
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP0S0[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  120000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCQUPV3WRAP0S2
 *
 * Used by:
 *   ClockDomain_GCC_GCCQUPV3WRAP0S2
 *   ClockDomain_GCC_GCCQUPV3WRAP0S3
 *   ClockDomain_GCC_GCCQUPV3WRAP0S4
 *   ClockDomain_GCC_GCCQUPV3WRAP0S5
 *   ClockDomain_GCC_GCCQUPV3WRAP0S6
 *   ClockDomain_GCC_GCCQUPV3WRAP0S7
 *   ClockDomain_GCC_GCCQUPV3WRAP1S2
 *   ClockDomain_GCC_GCCQUPV3WRAP1S3
 *   ClockDomain_GCC_GCCQUPV3WRAP1S4
 *   ClockDomain_GCC_GCCQUPV3WRAP1S5
 *   ClockDomain_GCC_GCCQUPV3WRAP1S6
 *   ClockDomain_GCC_GCCQUPV3WRAP1S7
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCQUPV3WRAP0S2[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  100000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCSDCC2APPS
 *
 * Used by:
 *   ClockDomain_GCC_GCCSDCC2APPS
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCSDCC2APPS[] =
{
  {  100000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  202000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUFSPHYAXI
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYAXI
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUFSPHYAXI[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  375000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  403000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUFSPHYICECORE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYICECORE
 *   ClockDomain_GCC_GCCUFSPHYUNIPROCORE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUFSPHYICECORE[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  550000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  600000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0
 *
 * Used by:
 *   ClockDomain_GCC_GCCUFSPHYRXSYMBOL0
 *   ClockDomain_GCC_GCCUFSPHYRXSYMBOL1
 *   ClockDomain_GCC_GCCUFSPHYTXSYMBOL0
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0[] =
{
  {   75000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  150000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUSB30PRIMMASTER
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB30PRIMMASTER
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUSB30PRIMMASTER[] =
{
  {   66666667, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  133333333, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  200000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  240000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  0  }
};

/*
 * ClockDomainFMax_GCC_GCCUSB3PRIMPHYPIPE
 *
 * Used by:
 *   ClockDomain_GCC_GCCUSB3PRIMPHYPIPE
 */
static const ClockFMaxType ClockDomainFMax_GCC_GCCUSB3PRIMPHYPIPE[] =
{
  {  125000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  312500000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCDEBUGMUX
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCDEBUGMUX
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCDEBUGMUX[] =
{
  {  230000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  285000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  443000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  540000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  608000000, RAIL_VOLTAGE_LEVEL_SVS_L2,     },
  {  676000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  780000000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  825000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  880000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCFF
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCFF
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCFF[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCGMU
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGMU
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCGMU[] =
{
  {  200000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  500000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCGXGFX3D
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCGXGFX3D
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCGXGFX3D[] =
{
  {  230000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  285000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  443000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  540000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  608000000, RAIL_VOLTAGE_LEVEL_SVS_L2,     },
  {  676000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  780000000, RAIL_VOLTAGE_LEVEL_NOM_L1,     },
  {  825000000, RAIL_VOLTAGE_LEVEL_TUR,        },
  {  880000000, RAIL_VOLTAGE_LEVEL_TUR_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCHUB
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCHUB
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCHUB[] =
{
  {  150000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  240000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  300000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCPLLTESTMUX
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCPLLTESTMUX[] =
{
  {  570000000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  716000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  { 1000000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  {  0  }
};

/*
 * ClockDomainFMax_GPUCC_GPUCCXO
 *
 * Used by:
 *   ClockDomain_GPUCC_GPUCCXO
 */
static const ClockFMaxType ClockDomainFMax_GPUCC_GPUCCXO[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS_D1, },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCAHB
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCAHB
 *   ClockDomain_VIDEOCC_VIDEOCCXO
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCAHB[] =
{
  {   19200000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCMVS0
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS0
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCMVS0[] =
{
  {  720000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1014000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  { 1098000000, RAIL_VOLTAGE_LEVEL_SVS_L1,     },
  { 1332000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCMVS1
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCMVS1
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCMVS1[] =
{
  {  840000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1098000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  { 1332000000, RAIL_VOLTAGE_LEVEL_NOM,        },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCPLLTESTMUX
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCPLLTESTMUX[] =
{
  {  800000000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  { 1000000000, RAIL_VOLTAGE_LEVEL_SVS,        },
  {  0  }
};

/*
 * ClockDomainFMax_VIDEOCC_VIDEOCCSLEEP
 *
 * Used by:
 *   ClockDomain_VIDEOCC_VIDEOCCSLEEP
 */
static const ClockFMaxType ClockDomainFMax_VIDEOCC_VIDEOCCSLEEP[] =
{
  {      32000, RAIL_VOLTAGE_LEVEL_LOW_SVS,    },
  {  0  }
};


/*=========================================================================
      Domains
==========================================================================*/

static ClockDomainNodeType ClockDomain_APSSCC_APSSCCDEBUGMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_APSSCC_APSSCCDEBUGMUX,
  .aSourceMap = ClockSourceMap_APSSCC_APSSCCDEBUGMUX,
  .pSource   = NULL,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(APSS_CC_DEBUG_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCBPS =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCBPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCBPS),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCBPS,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_BPS_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCAMNOCAXI =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCAMNOCAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCAMNOCAXI),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCAMNOCAXI,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CAMNOC_AXI_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCCI0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCCI0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCCI0),
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCCI0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CCI_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCCI1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCCI0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCCI0),
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCCI0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CCI_1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCPHYRX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCPHYRX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCPHYRX),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXA | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCPHYRX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CPHY_RX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI0PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI0PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI1PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI1PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI2PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI2PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI3PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI3PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCCSI4PHYTIMER =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCCSI0PHYTIMER),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCCSI0PHYTIMER,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_CSI4PHYTIMER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCDEBUGMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCDEBUGMUX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCDEBUGMUX,
  .pSource   = NULL,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_DEBUG_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCFASTAHB =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCFASTAHB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCFASTAHB),
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCFASTAHB,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_FAST_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCICP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCICP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCICP),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCICP,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_ICP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE0),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCIFE0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE0CSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE0CSID,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE0CSID),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0CSID,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_0_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE1),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCIFE1,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE1CSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE0CSID,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE0CSID),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0CSID,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_1_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE2 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE2),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCIFE2,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFE2CSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE0CSID,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE0CSID),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0CSID,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_2_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFELITE =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFELITE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFELITE),
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFELITE,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_LITE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIFELITECSID =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIFE0CSID,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIFE0CSID),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIFE0CSID,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IFE_LITE_CSID_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCIPE0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCIPE0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCIPE0),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCIPE0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCIPE0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_IPE_0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCJPEG =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCBPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCBPS),
  .nRailMask = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCBPS,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_JPEG_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK2 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK3 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK4 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK4_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCMCLK5 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCMCLK0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCMCLK0),
  .nRailMask = RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCMCLK0,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCMCLK0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_MCLK5_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCPLLTESTMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCPLLTESTMUX,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCPLLTESTMUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_PLL_TEST_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCQDSSDEBUG =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCQDSSDEBUG,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCQDSSDEBUG),
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCQDSSDEBUG,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_QDSS_DEBUG_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCSLEEP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLEEP),
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCSLEEP,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCSLEEP,
  .pSource   = NULL,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_SLEEP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCSLOWAHB =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLOWAHB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLOWAHB),
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCSLOWAHB,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCBPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_SLOW_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_CAMCC_CAMCCXO =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CAM_CX,
  .aFMax     = ClockDomainFMax_CAMCC_CAMCCXO,
  .aSourceMap = ClockSourceMap_CAMCC_CAMCCXO,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(CAM_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSAHB =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSAHB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSAHB),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSAHB,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSAHB,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSBYTE0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_BYTE0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSBYTE1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSBYTE0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_BYTE1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_LINK_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX1_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX1_LINK_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX1_PIXEL0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX1_PIXEL1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX2_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0LINK,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX2_LINK_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX2_PIXEL0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX2_PIXEL1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX3_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX3LINK,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0LINK,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX3_LINK_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_DPTX3_PIXEL0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSESC0 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSESC0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSESC0),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSESC0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_ESC0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSESC1 =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSESC0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSESC0),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSESC0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_ESC1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSMDP =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSMDP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSMDP),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSMDP,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSMDP,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_MDP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSPCLK0 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_PCLK0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSPCLK1 =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSPCLK0,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSBYTE0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_PCLK1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSROT =
{
  .aBSP      = ClockDomainBSP_DISPCC_DISPCCMDSSROT,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_DISPCC_DISPCCMDSSROT),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSROT,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSMDP,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_ROT_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCMDSSVSYNC =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_MDSS_VSYNC_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCPLLTESTMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCPLLTESTMUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCPLLTESTMUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_PLL_TEST_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCSLEEP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLEEP),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCSLEEP,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCSLEEP,
  .pSource   = NULL,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_SLEEP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_DISPCC_DISPCCXO =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_DISPCC_DISPCCMDSSDPTX0AUX,
  .aSourceMap = ClockSourceMap_DISPCC_DISPCCMDSSDPTX0AUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(DISP_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_CLOCKDRIVERGENXO =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = 0x0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = 0,
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = 0x0,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = 0,
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCAGGRENOC =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_AGGRE_NOC_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCAGGRENOCPCIE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_AGGRE_NOC_PCIE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCCNOCPCIEQX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CNOC_PCIE_QX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCCNOCPERIPH =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CNOC_PERIPH_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCCONFIGNOC =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_CONFIG_NOC_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCGP1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCGP1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCGP1),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCGP1,
  .aSourceMap = ClockSourceMap_GCC_GCCGP1,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_GP1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCGP2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCGP1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCGP1),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCGP1,
  .aSourceMap = ClockSourceMap_GCC_GCCGP1,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_GP2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCGP3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCGP1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCGP1),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCGP1,
  .aSourceMap = ClockSourceMap_GCC_GCCGP1,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_GP3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCGPUMEMNOCGFX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_GPU_MEMNOC_GFX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCMMNOCHFQX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_MMNOC_HF_QX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCMMNOCSFQX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_MMNOC_SF_QX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE0AUX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCPCIE0AUX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCPCIE0AUX),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0AUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_0_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nFlags     = HAL_CLK_FLAG_DOMAIN_HW_CLK_CONTROL,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE0PHYRCHNG =
{
  .aBSP      = ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCPCIE0PHYRCHNG),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0PHYRCHNG,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0PHYRCHNG,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_0_PHY_RCHNG_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPCIE0PIPE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0PIPE,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0PIPE,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PCIE_0_PIPE_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCPDM2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCPDM2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCPDM2),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPDM2,
  .aSourceMap = ClockSourceMap_GCC_GCCPDM2,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_PDM2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQDSSATBA =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QDSS_ATB_A_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQDSSATBB =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QDSS_ATB_B_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQDSSTRIG =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QDSS_TRIG_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0CORE2X =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_CORE_2X_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S4_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S5_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S6_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP0S7 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP0_S7_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1CORE2X =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_2X_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S0 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S1 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S0,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S2 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S2_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S3 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S3_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S4 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S4_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S5 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S5_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S6 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S6_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCQUPV3WRAP1S7 =
{
  .aBSP      = ClockDomainBSP_GCC_GCCQUPV3WRAP0S2,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCQUPV3WRAP0S2),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCQUPV3WRAP0S2,
  .aSourceMap = ClockSourceMap_GCC_GCCQUPV3WRAP0S0,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_DOMAIN_WAIT_FOR_ROOT_OFF,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_QUPV3_WRAP1_S7_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 16,
    .nDFSStates = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCSDCC2APPS =
{
  .aBSP      = ClockDomainBSP_GCC_GCCSDCC2APPS,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCSDCC2APPS),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCSDCC2APPS,
  .aSourceMap = ClockSourceMap_GCC_GCCSDCC2APPS,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SDCC2_APPS_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCSLEEP =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SLEEP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCSYSNOC =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_SYS_NOC_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYAXI =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYAXI,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYAXI),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYAXI,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYAXI,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_AXI_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYICECORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYICECORE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYICECORE),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYICECORE,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYICECORE,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_ICE_CORE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYPHYAUX =
{
  .aBSP      = ClockDomainBSP_GCC_GCCPCIE0AUX,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCPCIE0AUX),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYPHYAUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_PHY_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYRXSYMBOL0 =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL0,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_RX_SYMBOL_0_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYRXSYMBOL1 =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYRXSYMBOL1,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_RX_SYMBOL_1_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYTXSYMBOL0 =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYRXSYMBOL0,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYTXSYMBOL0,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_TX_SYMBOL_0_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUFSPHYUNIPROCORE =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUFSPHYICECORE,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUFSPHYICECORE),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCUFSPHYICECORE,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYICECORE,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_UFS_PHY_UNIPRO_CORE_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB30PRIMMASTER =
{
  .aBSP      = ClockDomainBSP_GCC_GCCUSB30PRIMMASTER,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GCC_GCCUSB30PRIMMASTER),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GCC_GCCUSB30PRIMMASTER,
  .aSourceMap = ClockSourceMap_GCC_GCCUSB30PRIMMASTER,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_USB30_PRIM_MASTER_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
    .nMNDWidth  = 8,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCUSB30PRIMMOCKUTMI,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_USB30_PRIM_MOCK_UTMI_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB3PRIMPHYAUX =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCPCIE0AUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_USB3_PRIM_PHY_AUX_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCUSB3PRIMPHYPIPE =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCUSB3PRIMPHYPIPE,
  .aSourceMap = ClockSourceMap_GCC_GCCUSB3PRIMPHYPIPE,
  .pSource   = NULL,
  .nFlags    = CLOCK_FLAG_DOMAIN_FORCE_SETTINGS,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_USB3_PRIM_PHY_PIPE_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCVSENSOR =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_VSENSOR_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GCC_GCCXO =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GCC_GCCPCIE0AUX,
  .aSourceMap = ClockSourceMap_GCC_GCCUFSPHYPHYAUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = CLOCK_FLAG_READ_ONLY,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GCC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCDEBUGMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCDEBUGMUX,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCDEBUGMUX,
  .pSource   = NULL,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_DEBUG_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCFF =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCFF,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCFF),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCFF,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCFF,
  .pSource   = NULL,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_FF_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCGMU =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCGMU,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCGMU),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXA,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCGMU,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCGMU,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_GMU_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCGXGFX3D =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCGXGFX3D,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCGXGFX3D),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_GX | RAIL_VDD_MXA | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCGXGFX3D,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCGXGFX3D,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_GX_GFX3D_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCHUB =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCHUB,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCHUB),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCHUB,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCHUB,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_HUB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCPLLTESTMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCPLLTESTMUX,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCPLLTESTMUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_PLL_TEST_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_GPUCC_GPUCCXO =
{
  .aBSP      = ClockDomainBSP_GPUCC_GPUCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_GPUCC_GPUCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_GPUCC_GPUCCXO,
  .aSourceMap = ClockSourceMap_GPUCC_GPUCCXO,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(GPUCC_GPU_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCAHB =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCAHB,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCAHB,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_AHB_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCMVS0 =
{
  .aBSP      = ClockDomainBSP_VIDEOCC_VIDEOCCMVS0,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_VIDEOCC_VIDEOCCMVS0),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCMVS0,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCMVS0,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCMVS1 =
{
  .aBSP      = ClockDomainBSP_VIDEOCC_VIDEOCCMVS1,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_VIDEOCC_VIDEOCCMVS1),
  .nRailMask = RAIL_VDD_CX | RAIL_VDD_MXC,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCMVS1,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCMVS1,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX =
{
  .aBSP      = NULL,
  .nBSPLen   = 0,
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCPLLTESTMUX,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCPLLTESTMUX,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_PLL_TEST_MUX_MUXR),
    .pmControl  = &HAL_clk_GenericDomainMuxControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCSLEEP =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCSLEEP,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCSLEEP),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCSLEEP,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCSLEEP,
  .pSource   = NULL,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_SLEEP_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};

static ClockDomainNodeType ClockDomain_VIDEOCC_VIDEOCCXO =
{
  .aBSP      = ClockDomainBSP_CAMCC_CAMCCXO,
  .nBSPLen   = SIZEOF_ARRAY(ClockDomainBSP_CAMCC_CAMCCXO),
  .nRailMask = RAIL_VDD_CX,
  .aFMax     = ClockDomainFMax_VIDEOCC_VIDEOCCAHB,
  .aSourceMap = ClockSourceMap_VIDEOCC_VIDEOCCAHB,
  .pSource   = &ClockSource_XO,
  .nFlags    = 0x0,
  .HALDomain = {
    .nCGRAddr   = HWIO_PHYS(VCODEC_VIDEO_CC_XO_CMD_RCGR),
    .pmControl  = &HAL_clk_GenericDomainControl,
  },
};


static ClockDomainNodeType *aDomains[] =
{
  &ClockDomain_APSSCC_APSSCCDEBUGMUX,
  &ClockDomain_CAMCC_CAMCCBPS,
  &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
  &ClockDomain_CAMCC_CAMCCCCI0,
  &ClockDomain_CAMCC_CAMCCCCI1,
  &ClockDomain_CAMCC_CAMCCCPHYRX,
  &ClockDomain_CAMCC_CAMCCCSI0PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI1PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI2PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI3PHYTIMER,
  &ClockDomain_CAMCC_CAMCCCSI4PHYTIMER,
  &ClockDomain_CAMCC_CAMCCDEBUGMUX,
  &ClockDomain_CAMCC_CAMCCFASTAHB,
  &ClockDomain_CAMCC_CAMCCICP,
  &ClockDomain_CAMCC_CAMCCIFE0,
  &ClockDomain_CAMCC_CAMCCIFE0CSID,
  &ClockDomain_CAMCC_CAMCCIFE1,
  &ClockDomain_CAMCC_CAMCCIFE1CSID,
  &ClockDomain_CAMCC_CAMCCIFE2,
  &ClockDomain_CAMCC_CAMCCIFE2CSID,
  &ClockDomain_CAMCC_CAMCCIFELITE,
  &ClockDomain_CAMCC_CAMCCIFELITECSID,
  &ClockDomain_CAMCC_CAMCCIPE0,
  &ClockDomain_CAMCC_CAMCCJPEG,
  &ClockDomain_CAMCC_CAMCCMCLK0,
  &ClockDomain_CAMCC_CAMCCMCLK1,
  &ClockDomain_CAMCC_CAMCCMCLK2,
  &ClockDomain_CAMCC_CAMCCMCLK3,
  &ClockDomain_CAMCC_CAMCCMCLK4,
  &ClockDomain_CAMCC_CAMCCMCLK5,
  &ClockDomain_CAMCC_CAMCCPLLTESTMUX,
  &ClockDomain_CAMCC_CAMCCQDSSDEBUG,
  &ClockDomain_CAMCC_CAMCCSLEEP,
  &ClockDomain_CAMCC_CAMCCSLOWAHB,
  &ClockDomain_CAMCC_CAMCCXO,
  &ClockDomain_DISPCC_DISPCCMDSSAHB,
  &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
  &ClockDomain_DISPCC_DISPCCMDSSBYTE1,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
  &ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0,
  &ClockDomain_DISPCC_DISPCCMDSSESC0,
  &ClockDomain_DISPCC_DISPCCMDSSESC1,
  &ClockDomain_DISPCC_DISPCCMDSSMDP,
  &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
  &ClockDomain_DISPCC_DISPCCMDSSPCLK1,
  &ClockDomain_DISPCC_DISPCCMDSSROT,
  &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
  &ClockDomain_DISPCC_DISPCCPLLTESTMUX,
  &ClockDomain_DISPCC_DISPCCSLEEP,
  &ClockDomain_DISPCC_DISPCCXO,
  &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
  &ClockDomain_GCC_CLOCKDRIVERGENXO,
  &ClockDomain_GCC_GCCAGGRENOC,
  &ClockDomain_GCC_GCCAGGRENOCPCIE,
  &ClockDomain_GCC_GCCCNOCPCIEQX,
  &ClockDomain_GCC_GCCCNOCPERIPH,
  &ClockDomain_GCC_GCCCONFIGNOC,
  &ClockDomain_GCC_GCCGP1,
  &ClockDomain_GCC_GCCGP2,
  &ClockDomain_GCC_GCCGP3,
  &ClockDomain_GCC_GCCGPUMEMNOCGFX,
  &ClockDomain_GCC_GCCMMNOCHFQX,
  &ClockDomain_GCC_GCCMMNOCSFQX,
  &ClockDomain_GCC_GCCPCIE0AUX,
  &ClockDomain_GCC_GCCPCIE0PHYRCHNG,
  &ClockDomain_GCC_GCCPCIE0PIPE,
  &ClockDomain_GCC_GCCPDM2,
  &ClockDomain_GCC_GCCQDSSATBA,
  &ClockDomain_GCC_GCCQDSSATBB,
  &ClockDomain_GCC_GCCQDSSTRIG,
  &ClockDomain_GCC_GCCQUPV3WRAP0CORE2X,
  &ClockDomain_GCC_GCCQUPV3WRAP0S0,
  &ClockDomain_GCC_GCCQUPV3WRAP0S1,
  &ClockDomain_GCC_GCCQUPV3WRAP0S2,
  &ClockDomain_GCC_GCCQUPV3WRAP0S3,
  &ClockDomain_GCC_GCCQUPV3WRAP0S4,
  &ClockDomain_GCC_GCCQUPV3WRAP0S5,
  &ClockDomain_GCC_GCCQUPV3WRAP0S6,
  &ClockDomain_GCC_GCCQUPV3WRAP0S7,
  &ClockDomain_GCC_GCCQUPV3WRAP1CORE2X,
  &ClockDomain_GCC_GCCQUPV3WRAP1S0,
  &ClockDomain_GCC_GCCQUPV3WRAP1S1,
  &ClockDomain_GCC_GCCQUPV3WRAP1S2,
  &ClockDomain_GCC_GCCQUPV3WRAP1S3,
  &ClockDomain_GCC_GCCQUPV3WRAP1S4,
  &ClockDomain_GCC_GCCQUPV3WRAP1S5,
  &ClockDomain_GCC_GCCQUPV3WRAP1S6,
  &ClockDomain_GCC_GCCQUPV3WRAP1S7,
  &ClockDomain_GCC_GCCSDCC2APPS,
  &ClockDomain_GCC_GCCSLEEP,
  &ClockDomain_GCC_GCCSYSNOC,
  &ClockDomain_GCC_GCCUFSPHYAXI,
  &ClockDomain_GCC_GCCUFSPHYICECORE,
  &ClockDomain_GCC_GCCUFSPHYPHYAUX,
  &ClockDomain_GCC_GCCUFSPHYRXSYMBOL0,
  &ClockDomain_GCC_GCCUFSPHYRXSYMBOL1,
  &ClockDomain_GCC_GCCUFSPHYTXSYMBOL0,
  &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
  &ClockDomain_GCC_GCCUSB30PRIMMASTER,
  &ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI,
  &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
  &ClockDomain_GCC_GCCUSB3PRIMPHYPIPE,
  &ClockDomain_GCC_GCCVSENSOR,
  &ClockDomain_GCC_GCCXO,
  &ClockDomain_GPUCC_GPUCCDEBUGMUX,
  &ClockDomain_GPUCC_GPUCCFF,
  &ClockDomain_GPUCC_GPUCCGMU,
  &ClockDomain_GPUCC_GPUCCGXGFX3D,
  &ClockDomain_GPUCC_GPUCCHUB,
  &ClockDomain_GPUCC_GPUCCPLLTESTMUX,
  &ClockDomain_GPUCC_GPUCCXO,
  &ClockDomain_VIDEOCC_VIDEOCCAHB,
  &ClockDomain_VIDEOCC_VIDEOCCMVS0,
  &ClockDomain_VIDEOCC_VIDEOCCMVS1,
  &ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX,
  &ClockDomain_VIDEOCC_VIDEOCCSLEEP,
  &ClockDomain_VIDEOCC_VIDEOCCXO,
};


/*=========================================================================
      Clocks
==========================================================================*/

static ClockNodeType aClocks[] =
{
  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCBPS                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_bps_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCBPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x2FE00ED4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 20,
    },
  },
  {
    .szName    = "cam_cc_spdm_bps_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCBPS,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xF0BFA945,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_BPS_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 21,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCAMNOCAXI                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_bps_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x27EC2F88,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_AXI_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 22,
    },
  },
  {
    .szName    = "cam_cc_camnoc_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x8AA30E80,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 60,
    },
  },
  {
    .szName    = "cam_cc_ife_0_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x62A5CCDC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_AXI_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 37,
    },
  },
  {
    .szName    = "cam_cc_ife_1_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD12D93AA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_AXI_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 45,
    },
  },
  {
    .szName    = "cam_cc_ife_2_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x31E1D953,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_AXI_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 83,
    },
  },
  {
    .szName    = "cam_cc_ife_lite_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC87AC598,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 73,
    },
  },
  {
    .szName    = "cam_cc_ipe_0_axi_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCAMNOCAXI,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x831626E2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_0_AXI_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 27,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCCI0                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cci_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCCI0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x2F0FA585,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CCI_0_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 57,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCCI1                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_cci_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCCI1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x0072D990,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CCI_1_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 58,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCPHYRX                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csiphy0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x5BD9C966,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY0_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 9,
    },
  },
  {
    .szName    = "cam_cc_csiphy1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD1C62B7E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY1_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 11,
    },
  },
  {
    .szName    = "cam_cc_csiphy2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFB341D3F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY2_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 13,
    },
  },
  {
    .szName    = "cam_cc_csiphy3_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x29439ED4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY3_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 15,
    },
  },
  {
    .szName    = "cam_cc_csiphy4_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xDB01488B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSIPHY4_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 17,
    },
  },
  {
    .szName    = "cam_cc_ife_0_cphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x94279150,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_CPHY_RX_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 36,
    },
  },
  {
    .szName    = "cam_cc_ife_1_cphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x0BA4A1D1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_CPHY_RX_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 44,
    },
  },
  {
    .szName    = "cam_cc_ife_2_cphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x2EB3D283,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_CPHY_RX_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 82,
    },
  },
  {
    .szName    = "cam_cc_ife_lite_cphy_rx_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCPHYRX,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x51577E4F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_CPHY_RX_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 49,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI0PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi0phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI0PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xDF3E55F8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI0PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 8,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI1PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi1phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI1PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xBD91807B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI1PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 10,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI2PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi2phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI2PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x411BC4E9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI2PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 12,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI3PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi3phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI3PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD8F7C361,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI3PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 14,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCCSI4PHYTIMER                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_csi4phytimer_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCCSI4PHYTIMER,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xB18687E2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CSI4PHYTIMER_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCDEBUGMUX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_debug_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCDEBUGMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x8E6D4CE1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCFASTAHB                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_bps_areg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x94A0ECE6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_AREG_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 23,
    },
  },
  {
    .szName    = "cam_cc_ife_0_areg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x5349F70E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_AREG_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 31,
    },
  },
  {
    .szName    = "cam_cc_ife_1_areg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x66ACAB0B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_AREG_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 41,
    },
  },
  {
    .szName    = "cam_cc_ife_2_areg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x5FA50AFC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_AREG_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 55,
    },
  },
  {
    .szName    = "cam_cc_ipe_0_areg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCFASTAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x647660BB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_0_AREG_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 28,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCICP                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_icp_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCICP,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFDC6BEB1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_ICP_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 53,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE0                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x93CC2ED3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 30,
    },
  },
  {
    .szName    = "cam_cc_ife_0_dsp_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xCA294DE3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_DSP_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 33,
    },
  },
  {
    .szName    = "cam_cc_spdm_ife_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x8B62CE74,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_IFE_0_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE0CSID                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_0_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0CSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x336D0D27,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_CSID_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 34,
    },
  },
  {
    .szName    = "cam_cc_spdm_ife_0_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE0CSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD05FD3DB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_IFE_0_CSID_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 35,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE1                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x20EDB204,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 39,
    },
  },
  {
    .szName    = "cam_cc_ife_1_dsp_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x44BE7A4B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_DSP_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 42,
    },
  },
  {
    .szName    = "cam_cc_spdm_ife_1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x1522372D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_IFE_1_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 40,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE1CSID                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_1_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE1CSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x3BA9C280,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_CSID_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 43,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE2                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x1A2BDA1C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 7,
    },
  },
  {
    .szName    = "cam_cc_spdm_ife_2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xDB780231,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_IFE_2_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 56,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFE2CSID                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_2_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFE2CSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x9068AD14,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_CSID_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 81,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFELITE                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_lite_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFELITE,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD0972606,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 47,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIFELITECSID                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ife_lite_csid_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIFELITECSID,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC6E06EE3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_CSID_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 48,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCIPE0                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_ipe_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIPE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xA15076BA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_0_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 25,
    },
  },
  {
    .szName    = "cam_cc_spdm_ipe_0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCIPE0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xF8B85420,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_IPE_0_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 26,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCJPEG                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_jpeg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCJPEG,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x9F6924DC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_JPEG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 51,
    },
  },
  {
    .szName    = "cam_cc_spdm_jpeg_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCJPEG,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x244595C2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SPDM_JPEG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 52,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK0                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk0_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK0,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xAFDBB67A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK0_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 1,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK1                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk1_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK1,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x57396D81,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK1_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 2,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK2                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk2_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK2,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x70806571,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK2_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 3,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK3                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk3_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK3,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x35F364E9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK3_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 4,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK4                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk4_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK4,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x315FF885,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK4_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 5,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCMCLK5                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_mclk5_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCMCLK5,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD8521D1F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_MCLK5_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 6,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCPLLTESTMUX                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_pll_test_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCPLLTESTMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x519E3D27,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCQDSSDEBUG                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_qdss_debug_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCQDSSDEBUG,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x1843A6D1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_QDSS_DEBUG_CBCR), HWIO_PHYS(CAM_CC_QDSS_DEBUG_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 62,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCSLEEP                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_sleep_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLEEP,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xCFDF030C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_SLEEP_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 66,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCSLOWAHB                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_bps_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xCE8465C2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_BPS_AHB_CBCR), HWIO_PHYS(CAM_CC_BPS_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 24,
    },
  },
  {
    .szName    = "cam_cc_core_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xA974C223,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CORE_AHB_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 64,
    },
  },
  {
    .szName    = "cam_cc_cpas_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x7E6C7824,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CPAS_AHB_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 59,
    },
  },
  {
    .szName    = "cam_cc_icp_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x32CA8C6A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_ICP_AHB_CBCR), HWIO_PHYS(CAM_CC_ICP_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 54,
    },
  },
  {
    .szName    = "cam_cc_ife_0_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x487AF310,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_0_AHB_CBCR), HWIO_PHYS(CAM_CC_IFE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 38,
    },
  },
  {
    .szName    = "cam_cc_ife_1_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xB9F23991,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_1_AHB_CBCR), HWIO_PHYS(CAM_CC_IFE_1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 46,
    },
  },
  {
    .szName    = "cam_cc_ife_2_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xB13B77AD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_2_AHB_CBCR), HWIO_PHYS(CAM_CC_IFE_2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 84,
    },
  },
  {
    .szName    = "cam_cc_ife_lite_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x27E3565D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IFE_LITE_AHB_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 50,
    },
  },
  {
    .szName    = "cam_cc_ipe_0_ahb_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCSLOWAHB,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0x93BDABBB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_IPE_0_AHB_CBCR), HWIO_PHYS(CAM_CC_IPE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 29,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_CAMCC_CAMCCXO                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "cam_cc_camnoc_dcd_xo_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xD2B89C42,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_CAMNOC_DCD_XO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 61,
    },
  },
  {
    .szName    = "cam_cc_gdsc_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xC9FEBE6E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_GDSC_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 65,
    },
  },
  {
    .szName    = "cam_cc_qdss_debug_xo_clk",
    .pDomain   = &ClockDomain_CAMCC_CAMCCXO,
    .pDebugMux = &ClockDebugMux_CAMCC,
    .nUniqueId = 0xFC7EF9CE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(CAM_CC_QDSS_DEBUG_XO_CBCR), HWIO_PHYS(CAM_CC_QDSS_DEBUG_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 63,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSAHB                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_ahb1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xBD9DA764,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_AHB1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 57,
    },
  },
  {
    .szName    = "disp_cc_mdss_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xD86CF434,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_AHB_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 52,
    },
  },
  {
    .szName    = "disp_cc_mdss_non_gdsc_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xD594BB06,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_NON_GDSC_AHB_CBCR), HWIO_PHYS(DISP_CC_MDSS_RSCC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 58,
    },
  },
  {
    .szName    = "disp_cc_mdss_rscc_ahb_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSAHB,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x23666C25,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_RSCC_AHB_CBCR), HWIO_PHYS(DISP_CC_MDSS_RSCC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 60,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSBYTE0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_byte0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x62A800C1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_BYTE0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 21,
    },
  },
  {
    .szName    = "disp_cc_mdss_byte0_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xEC7D494E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_BYTE0_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 22,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSBYTE1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_byte1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x0DE1DE46,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_BYTE1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 23,
    },
  },
  {
    .szName    = "disp_cc_mdss_byte1_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSBYTE1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xFEEDA5FA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_BYTE1_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 24,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0AUX,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xC2E18940,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_AUX_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 33,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xC95B6162,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 30,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x15BD0141,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_LINK_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 27,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xEBAC4D27,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 29,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx0_usb_router_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xDFF7A70E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_USB_ROUTER_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 28,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx1_usb_router_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xB01596F5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_USB_ROUTER_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 37,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x75EFBB45,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 65,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x92F8B42B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 31,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x72B57E57,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_PIXEL_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 66,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx0_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x5908B325,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX0_PIXEL1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_dp_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX0PIXEL1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x24157A60,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_DP_PIXEL1_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 67,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1AUX,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xA4C9FCBA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_AUX_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 40,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xDC4577D5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 39,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xA6B8960A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_LINK_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 36,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx1_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xE09D4224,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 38,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xECF3AF7D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_PIXEL0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 34,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx1_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX1PIXEL1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x715982F2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX1_PIXEL1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 35,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2AUX,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xEE4EC3B3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_AUX_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 46,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xD3922A9C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 45,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x98555F85,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_LINK_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 43,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx2_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xB5F9954A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 44,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x2A4E6380,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_PIXEL0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 41,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx2_pixel1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX2PIXEL1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xBABE80B9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX2_PIXEL1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 42,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_aux_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3AUX,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xB5F17EF7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_AUX_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 50,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_crypto_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x9E1CCAE7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_CRYPTO_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 51,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xCE228C2D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_LINK_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 48,
    },
  },
  {
    .szName    = "disp_cc_mdss_dptx3_link_intf_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3LINK,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xCEC7F620,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_LINK_INTF_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 49,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_dptx3_pixel0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSDPTX3PIXEL0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x153148BC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_DPTX3_PIXEL0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 47,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSESC0                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_esc0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSESC0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x4485FD1B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_ESC0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 25,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSESC1                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_esc1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSESC1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x27702EBC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_ESC1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 26,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSMDP                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_mdp1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x085D62A2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_MDP1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 53,
    },
  },
  {
    .szName    = "disp_cc_mdss_mdp_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x6A10EA96,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_MDP_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 17,
    },
  },
  {
    .szName    = "disp_cc_mdss_mdp_lut1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x70F2ED4E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_MDP_LUT1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 55,
    },
  },
  {
    .szName    = "disp_cc_mdss_mdp_lut_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xF02E7C9A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_MDP_LUT_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 19,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_mdp_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSMDP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x8D7A3901,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_MDP_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 63,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSPCLK0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_pclk0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xDF2F28DF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_PCLK0_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 15,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk0_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK0,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x757CD20E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_PCLK0_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 61,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSPCLK1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_pclk1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xEC01E1B5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_PCLK1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_pclk1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSPCLK1,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x3C6FD75A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_PCLK1_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 62,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSROT                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_rot1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSROT,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x29400086,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_ROT1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 54,
    },
  },
  {
    .szName    = "disp_cc_mdss_rot_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSROT,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xE5657DD4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_ROT_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 18,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_rot_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSROT,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x9F34B547,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_ROT_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 64,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCMDSSVSYNC                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_mdss_rscc_vsync_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x47CD7D13,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_RSCC_VSYNC_CBCR), HWIO_PHYS(DISP_CC_MDSS_RSCC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 59,
    },
  },
  {
    .szName    = "disp_cc_mdss_vsync1_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x106D4032,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_VSYNC1_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 56,
    },
  },
  {
    .szName    = "disp_cc_mdss_vsync_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCMDSSVSYNC,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x80004355,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_VSYNC_CBCR), HWIO_PHYS(DISP_CC_MDSS_CORE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 20,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCPLLTESTMUX                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_pll_test_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCPLLTESTMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x7D7A63ED,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCSLEEP                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_sleep_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCSLEEP,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0xE16C7ED9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_SLEEP_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 69,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_DISPCC_DISPCCXO                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_xo_clk",
    .pDomain   = &ClockDomain_DISPCC_DISPCCXO,
    .pDebugMux = &ClockDebugMux_DISPCC,
    .nUniqueId = 0x9C4A81EA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_XO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 68,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_CLOCKDRIVERGENXO                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_cxo2_tx1_clkref_en1",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xD8E8FAEC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CXO2_TX1_CLKREF_EN1), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_eusb3_0_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x69DD3EB7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_EUSB3_0_CLKREF_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_0_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x106963AD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPLL0_UFS_PHY_RX_SYMBOL_0_ACGCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_rx_symbol_1_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x9A09B4DA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPLL0_UFS_PHY_RX_SYMBOL_1_ACGCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_gpll0_ufs_phy_tx_symbol_0_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x098D4A5E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPLL0_UFS_PHY_TX_SYMBOL_0_ACGCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_gpu_gpll0_clk_src",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4B1A4AC7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_GPU_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x8000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 370,
    },
  },
  {
    .szName    = "gcc_gpu_gpll0_div_clk_src",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6EEEF079,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_GPU_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x10000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 371,
    },
  },
  {
    .szName    = "gcc_gpu_memnoc_gfx_clk_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xCEE753AC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPU_MEMNOC_GFX_CLK_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x163AA536,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_AUDIO_TBU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xB541E243,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_TBU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_aggre_noc_mmu_tbu1_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x73963888,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU1_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_aggre_noc_mmu_tbu2_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x78CD70C0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU2_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_all_smmu_mmu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xF26FB3CE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_ALL_SMMU_MMU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_gpu_smmu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x4A750D50,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_GPU_SMMU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x5A23B219,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF0_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xC690F22F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF1_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_tbu_hf2_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xC8EBF87F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF2_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_tbu_hf3_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x47510045,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF3_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x998935CD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF0_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x91B7740F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF1_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_mmu_tcu_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x45B7596F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_MMU_TCU_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_turing_mmu_tbu0_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xEAAAE7E3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_TURING_MMU_TBU0_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_hlos1_vote_turing_mmu_tbu1_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x8A6A6C38,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_HLOS1_VOTE_TURING_MMU_TBU1_CLK), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_memnoc_mss_offline_clk_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x9DB3690C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_MEMNOC_MSS_OFFLINE_CLK_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_memnoc_mss_q6_clk_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x60B84B22,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_MEMNOC_MSS_Q6_CLK_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_memnoc_turing_clk_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x22927F8E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_MEMNOC_TURING_CLK_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_mmu_memnoc_tcu_clk_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x826FCA30,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_MMU_MEMNOC_TCU_CLK_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xA10632F8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_CLKREF_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_qlink_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x05E0F0E9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QLINK_CLKREF_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_ufs_0_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x2F1532D6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_0_CLKREF_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_ufs_pad_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x8D993D48,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PAD_CLKREF_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3_0_clkref_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0x220CE3DE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB3_0_CLKREF_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_wpss_axi_clk_en",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = NULL,
    .nUniqueId = 0xF79826BB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_WPSS_AXI_CLK_EN), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpu_cc_cb_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x721C91D0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CB_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 46,
    },
  },
  {
    .szName    = "gpu_cc_cx_apb_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x6E5557EC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_APB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 26,
    },
  },
  {
    .szName    = "gpu_cc_cx_qdss_tsctr_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x403CC85F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_QDSS_TSCTR_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 25,
    },
  },
  {
    .szName    = "gpu_cc_gx_qdss_tsctr_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x39A96FAC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_QDSS_TSCTR_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 16,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "disp_cc_debug_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x17181EB2,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "disp_cc_mdss_spdm_debug_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x1B862752,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(DISP_CC_MDSS_SPDM_DEBUG_CBCR), HWIO_PHYS(DISP_CC_MDSS_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_link_down_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xB6C4C692,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_0_LINK_DOWN_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_nocsr_com_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xD13C8283,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_0_NOCSR_COM_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x822A9820,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_0_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_0_phy_nocsr_com_phy_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xA7917945,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_0_PHY_NOCSR_COM_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_phy_cfg_ahb_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x5FB6DA8B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_PHY_CFG_AHB_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_pcie_phy_com_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x20D7AA6B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_PCIE_PHY_COM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3_dp_phy_prim_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x1F251390,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3_DP_PHY_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3_dp_phy_sec_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x6969477E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3_DP_PHY_SEC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3_phy_prim_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x7F6A6E8C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3_PHY_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3_phy_sec_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xA8BC18B6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3_PHY_SEC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3phy_phy_prim_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x12166FD9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3PHY_PHY_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_usb3phy_phy_sec_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x5ECE2A2C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_USB3PHY_PHY_SEC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_qusb2phy_prim_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x6969477E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_QUSB2PHY_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gcc_qusb2phy_sec_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x6969477E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GCC_QUSB2PHY_SEC_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpu_cc_memnoc_gfx_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xEAA2A911,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_MEMNOC_GFX_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 34,
    },
  },
  {
    .szName    = "gpucc_gpu_cc_ff_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x30673FAE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GPUCC_GPU_CC_FF_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpucc_gpu_cc_gmu_bcr",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0xB67BB00E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { 0, HWIO_PHYS(GPUCC_GPU_CC_GMU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "video_cc_debug_clk",
    .pDomain   = &ClockDomain_GCC_CLOCKDRIVERGENNOSOURCE,
    .pDebugMux = NULL,
    .nUniqueId = 0x9AD7014D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCAGGRENOC                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap_1_m_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x728861DF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_1_M_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x100000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 179,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCAGGRENOCPCIE                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_noc_pcie_0_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCPCIE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xAA39B376,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_AGGRE_NOC_PCIE_0_AXI_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x1000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 61,
    },
  },
  {
    .szName    = "gcc_ddrss_pcie_sf_tbu_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCPCIE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x7B6157CD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DDRSS_PCIE_SF_TBU_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x80000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 246,
    },
  },
  {
    .szName    = "gcc_pcie_0_mstr_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCAGGRENOCPCIE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6ECCBB13,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_MSTR_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 296,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCNOCPCIEQX                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_slv_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCPCIEQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9331B3EF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_SLV_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 295,
    },
  },
  {
    .szName    = "gcc_pcie_0_slv_q2a_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCPCIEQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5B161349,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_SLV_Q2A_AXI_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x20} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 294,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCNOCPERIPH                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pdm_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCPERIPH,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA6F0A072,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PDM_AHB_CBCR), HWIO_PHYS(GCC_PDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 201,
    },
  },
  {
    .szName    = "gcc_sdcc2_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCNOCPERIPH,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF7AE64AF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC2_AHB_CBCR), HWIO_PHYS(GCC_SDCC2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 162,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCCONFIGNOC                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_boot_rom_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x20C2EB7C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_BOOT_ROM_AHB_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x400} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 217,
    },
  },
  {
    .szName    = "gcc_camera_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xCB81AAEC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_AHB_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 99,
    },
  },
  {
    .szName    = "gcc_cfg_noc_pcie_anoc_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x927E2559,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CFG_NOC_PCIE_ANOC_AHB_CBCR), 0, {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x100000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 45,
    },
  },
  {
    .szName    = "gcc_disp_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xCC324D48,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DISP_AHB_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 108,
    },
  },
  {
    .szName    = "gcc_gpu_cfg_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xBDC5D904,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPU_CFG_AHB_CBCR), HWIO_PHYS(GCC_GPU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 363,
    },
  },
  {
    .szName    = "gcc_pcie_0_cfg_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xAB33D8F8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_CFG_AHB_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 297,
    },
  },
  {
    .szName    = "gcc_qmip_camera_nrt_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5508D425,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_CAMERA_NRT_AHB_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 100,
    },
  },
  {
    .szName    = "gcc_qmip_camera_rt_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x15F7C6F4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_CAMERA_RT_AHB_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 101,
    },
  },
  {
    .szName    = "gcc_qmip_disp_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x2FE1361E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_DISP_AHB_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 109,
    },
  },
  {
    .szName    = "gcc_qmip_gpu_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x428F6D35,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_GPU_AHB_CBCR), HWIO_PHYS(GCC_GPU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 364,
    },
  },
  {
    .szName    = "gcc_qmip_pcie_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x508920D5,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_PCIE_AHB_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 293,
    },
  },
  {
    .szName    = "gcc_qmip_video_cv_cpu_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x0F770842,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_VIDEO_CV_CPU_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 118,
    },
  },
  {
    .szName    = "gcc_qmip_video_cvp_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5577C832,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_VIDEO_CVP_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 115,
    },
  },
  {
    .szName    = "gcc_qmip_video_v_cpu_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x39939E99,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_VIDEO_V_CPU_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 117,
    },
  },
  {
    .szName    = "gcc_qmip_video_vcodec_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xED09B49D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QMIP_VIDEO_VCODEC_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 116,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_0_s_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB8C59FEE,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_0_S_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x80} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 168,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap_1_s_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x3428967E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_1_S_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x200000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 180,
    },
  },
  {
    .szName    = "gcc_ufs_phy_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x79B5465B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_AHB_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 315,
    },
  },
  {
    .szName    = "gcc_video_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCCONFIGNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x3DC15104,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_VIDEO_AHB_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 114,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCGP1                                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_gp1_clk",
    .pDomain   = &ClockDomain_GCC_GCCGP1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5BCD42D6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GP1_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 290,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCGP2                                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_gp2_clk",
    .pDomain   = &ClockDomain_GCC_GCCGP2,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xC0B86CC1,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GP2_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 291,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCGP3                                                */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_gp3_clk",
    .pDomain   = &ClockDomain_GCC_GCCGP3,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x81385E59,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GP3_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 292,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCGPUMEMNOCGFX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ddrss_gpu_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCGPUMEMNOCGFX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDF8E077C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DDRSS_GPU_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 245,
    },
  },
  {
    .szName    = "gcc_gpu_memnoc_gfx_clk",
    .pDomain   = &ClockDomain_GCC_GCCGPUMEMNOCGFX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x114959A4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPU_MEMNOC_GFX_CBCR), HWIO_PHYS(GCC_GPU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 367,
    },
  },
  {
    .szName    = "gcc_gpu_snoc_dvm_gfx_clk",
    .pDomain   = &ClockDomain_GCC_GCCGPUMEMNOCGFX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x22ACC42A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_GPU_SNOC_DVM_GFX_CBCR), HWIO_PHYS(GCC_GPU_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 369,
    },
  },
  {
    .szName    = "gpu_cc_cx_snoc_dvm_clk",
    .pDomain   = &ClockDomain_GCC_GCCGPUMEMNOCGFX,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xB73879BC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_SNOC_DVM_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 27,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMMNOCHFQX                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_hf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCHFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x62191536,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_HF_AXI_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 102,
    },
  },
  {
    .szName    = "gcc_disp_hf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCHFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xBF311160,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DISP_HF_AXI_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 110,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCMMNOCSFQX                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_sf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x033685A3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_SF_AXI_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 104,
    },
  },
  {
    .szName    = "gcc_disp_sf_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB96F8542,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DISP_SF_AXI_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 111,
    },
  },
  {
    .szName    = "gcc_video_axi0_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x527C9897,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_VIDEO_AXI0_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 119,
    },
  },
  {
    .szName    = "gcc_video_axi1_clk",
    .pDomain   = &ClockDomain_GCC_GCCMMNOCSFQX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4F8C5CD6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_VIDEO_AXI1_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 120,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE0AUX                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE0AUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDE4195A6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_AUX_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 298,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE0PHYRCHNG                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_phy_rchng_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE0PHYRCHNG,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x4F8DB026,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_PHY_RCHNG_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE), 0x400000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 300,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPCIE0PIPE                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pcie_0_pipe_clk",
    .pDomain   = &ClockDomain_GCC_GCCPCIE0PIPE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDCB72BF8,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PCIE_0_PIPE_CBCR), HWIO_PHYS(GCC_PCIE_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 299,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCPDM2                                               */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_pdm2_clk",
    .pDomain   = &ClockDomain_GCC_GCCPDM2,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xF8EA86EA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PDM2_CBCR), HWIO_PHYS(GCC_PDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 203,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSATBA                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc2_at_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBA,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x63F0B54C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC2_AT_CBCR), HWIO_PHYS(GCC_SDCC2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 163,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSATBB                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_qdss_at_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSATBB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x3A64CC97,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_QDSS_AT_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 24,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQDSSTRIG                                           */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_qdss_trig_clk",
    .pDomain   = &ClockDomain_GCC_GCCQDSSTRIG,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x046DFEBA,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_QDSS_TRIG_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 29,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0CORE2X                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_core_2x_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x77020808,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_CORE_2X_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x200} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 170,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap0_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x1B88DC58,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_CORE_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x100} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 169,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x56C239B6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S0_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x400} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 171,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s1_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x299AA1D4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S1_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x800} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 172,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S2                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S2,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x06533C2C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S2_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 173,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S3                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S3,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x939588DB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S3_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 174,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S4                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s4_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S4,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x62F41847,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S4_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 175,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S5                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s5_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S5,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5751B5F3,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S5_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 176,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S6                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s6_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S6,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x917A11AD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S6_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 177,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP0S7                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap0_s7_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP0S7,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x69D7DBAF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP0_S7_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x20000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 178,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1CORE2X                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_core_2x_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xD7DB82C0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_2X_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x40000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 182,
    },
  },
  {
    .szName    = "gcc_qupv3_wrap1_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1CORE2X,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x40B685B0,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_CORE_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x80000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 181,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s0_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA40B3E1C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S0_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x400000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 183,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s1_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDE8BDAAC,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S1_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x800000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 184,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S2                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s2_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S2,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x45AB34F6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S2_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x1000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 185,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S3                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s3_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S3,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6CBC20FD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S3_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x2000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 186,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S4                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s4_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S4,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x2A814B46,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S4_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x4000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 187,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S5                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s5_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S5,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x8279058C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S5_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x8000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 188,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S6                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s6_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S6,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x6FB2266A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S6_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x10000000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 189,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCQUPV3WRAP1S7                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap1_s7_clk",
    .pDomain   = &ClockDomain_GCC_GCCQUPV3WRAP1S7,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x90473589,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP1_S7_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_1_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_2), 0x40000} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 419,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSDCC2APPS                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_sdcc2_apps_clk",
    .pDomain   = &ClockDomain_GCC_GCCSDCC2APPS,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x99917219,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_SDCC2_APPS_CBCR), HWIO_PHYS(GCC_SDCC2_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 161,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSLEEP                                              */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb30_prim_sleep_clk",
    .pDomain   = &ClockDomain_GCC_GCCSLEEP,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xA3AD9ACB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB30_PRIM_SLEEP_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 149,
    },
  },
  {
    .szName    = "gpu_cc_sleep_clk",
    .pDomain   = &ClockDomain_GCC_GCCSLEEP,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xC2E1C465,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_SLEEP_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 28,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCSYSNOC                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_qupv3_wrap_0_m_ahb_clk",
    .pDomain   = &ClockDomain_GCC_GCCSYSNOC,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x79AD882E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_QUPV3_WRAP_0_M_AHB_CBCR), HWIO_PHYS(GCC_QUPV3_WRAPPER_0_BCR), {HWIO_PHYS(GCC_PROC_CLK_BRANCH_ENA_VOTE_1), 0x40} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 167,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYAXI                                          */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_ufs_phy_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYAXI,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9D270053,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_AGGRE_UFS_PHY_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 64,
    },
  },
  {
    .szName    = "gcc_ufs_phy_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYAXI,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9310F430,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_AXI_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 314,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYICECORE                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_ice_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYICECORE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xEB42CB41,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_ICE_CORE_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 321,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYPHYAUX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_phy_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYPHYAUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x224FBCE6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_PHY_AUX_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 322,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYRXSYMBOL0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_rx_symbol_0_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYRXSYMBOL0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xC250BA4B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_RX_SYMBOL_0_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 317,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYRXSYMBOL1                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_rx_symbol_1_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYRXSYMBOL1,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xB7C57145,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_RX_SYMBOL_1_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 323,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYTXSYMBOL0                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_tx_symbol_0_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYTXSYMBOL0,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xDE965215,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_TX_SYMBOL_0_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 316,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUFSPHYUNIPROCORE                                   */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_ufs_phy_unipro_core_clk",
    .pDomain   = &ClockDomain_GCC_GCCUFSPHYUNIPROCORE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x815C816D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_UFS_PHY_UNIPRO_CORE_CBCR), HWIO_PHYS(GCC_UFS_PHY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 320,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB30PRIMMASTER                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_aggre_usb3_prim_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9C0C2B41,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_AGGRE_USB3_PRIM_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 63,
    },
  },
  {
    .szName    = "gcc_cfg_noc_usb3_prim_axi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xE7023B78,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CFG_NOC_USB3_PRIM_AXI_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },
  {
    .szName    = "gcc_usb30_prim_master_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMASTER,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x91482B7C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB30_PRIM_MASTER_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 148,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI                                  */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb30_prim_mock_utmi_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB30PRIMMOCKUTMI,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xFEDF50FF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB30_PRIM_MOCK_UTMI_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 150,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB3PRIMPHYAUX                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb3_prim_phy_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x5BBF945A,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB3_PRIM_PHY_AUX_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 151,
    },
  },
  {
    .szName    = "gcc_usb3_prim_phy_com_aux_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB3PRIMPHYAUX,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x84C54E8E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB3_PRIM_PHY_COM_AUX_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 152,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCUSB3PRIMPHYPIPE                                    */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_usb3_prim_phy_pipe_clk",
    .pDomain   = &ClockDomain_GCC_GCCUSB3PRIMPHYPIPE,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x8F9EA437,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_USB3_PRIM_PHY_PIPE_CBCR), HWIO_PHYS(GCC_USB30_PRIM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 153,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCVSENSOR                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_gx_vsense_clk",
    .pDomain   = &ClockDomain_GCC_GCCVSENSOR,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x2DA8421F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_VSENSE_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 15,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GCC_GCCXO                                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gcc_camera_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0xEF993118,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_CAMERA_XO_CBCR), HWIO_PHYS(GCC_CAMERA_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 106,
    },
  },
  {
    .szName    = "gcc_disp_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x9A471C5C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_DISP_XO_CBCR), HWIO_PHYS(GCC_DISPLAY_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 112,
    },
  },
  {
    .szName    = "gcc_pdm_xo4_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x1C323047,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_PDM_XO4_CBCR), HWIO_PHYS(GCC_PDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 202,
    },
  },
  {
    .szName    = "gcc_video_xo_clk",
    .pDomain   = &ClockDomain_GCC_GCCXO,
    .pDebugMux = &ClockDebugMux_GCC,
    .nUniqueId = 0x79581D18,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GCC_VIDEO_XO_CBCR), HWIO_PHYS(GCC_VIDEO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 121,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCDEBUGMUX                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_debug_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCDEBUGMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x2D49728D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_DEBUG_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },
  {
    .szName    = "gpu_cc_debug_measure_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCDEBUGMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x61D27566,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_DEBUG_MEASURE_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCFF                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_ff_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCFF,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x276A4142,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_FF_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 33,
    },
  },
  {
    .szName    = "gpu_cc_gx_ff_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCFF,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xD12CF765,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_FF_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 19,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCGMU                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_gmu_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGMU,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x85040864,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_GMU_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 30,
    },
  },
  {
    .szName    = "gpu_cc_gx_gmu_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGMU,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xFD46B6AB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_GMU_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 18,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCGXGFX3D                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_cx_gfx3d_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x2B627FA6,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_GFX3D_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GFX3D_AON_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 37,
    },
  },
  {
    .szName    = "gpu_cc_cx_gfx3d_slv_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xD96DA83B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CX_GFX3D_SLV_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GFX3D_AON_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 38,
    },
  },
  {
    .szName    = "gpu_cc_gx_gfx3d_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x40E4E782,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_GFX3D_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 14,
    },
  },
  {
    .szName    = "gpu_cc_gx_gfx3d_rdvm_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x14588D9F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_GFX3D_RDVM_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 21,
    },
  },
  {
    .szName    = "gpu_cc_mnd1x_0_gfx3d_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x5FAAC69D,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_MND1X_0_GFX3D_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 41,
    },
  },
  {
    .szName    = "gpu_cc_mnd1x_1_gfx3d_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x999671BB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_MND1X_1_GFX3D_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 42,
    },
  },
  {
    .szName    = "gpu_cc_spdm_gx_gfx3d_div_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCGXGFX3D,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xFB0C5507,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_SPDM_GX_GFX3D_DIV_CBCR), HWIO_PHYS(GPUCC_GPU_CC_SPDM_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 43,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCHUB                                            */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_acd_ahb_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xD8CEEBD9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_ACD_AHB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_ACD_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 45,
    },
  },
  {
    .szName    = "gpu_cc_ahb_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x763BA1C4,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_AHB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 22,
    },
  },
  {
    .szName    = "gpu_cc_crc_ahb_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xACF3D523,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CRC_AHB_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 23,
    },
  },
  {
    .szName    = "gpu_cc_hub_aon_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x063271D7,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_HUB_AON_CBCR), HWIO_PHYS(GPUCC_GPU_CC_FAST_HUB_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 47,
    },
  },
  {
    .szName    = "gpu_cc_hub_cx_int_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCHUB,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xC00F7891,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_HUB_CX_INT_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 32,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCPLLTESTMUX                                     */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_pll_test_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCPLLTESTMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0x8F8278F9,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_GPUCC_GPUCCXO                                             */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "gpu_cc_acd_cxo_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xFB4F06FB,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_ACD_CXO_CBCR), HWIO_PHYS(GPUCC_GPU_CC_ACD_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 44,
    },
  },
  {
    .szName    = "gpu_cc_cxo_aon_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xA006B60F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CXO_AON_CBCR), HWIO_PHYS(GPUCC_GPU_CC_XO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 11,
    },
  },
  {
    .szName    = "gpu_cc_cxo_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x8DFA73CF,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_CXO_CBCR), HWIO_PHYS(GPUCC_GPU_CC_CX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 31,
    },
  },
  {
    .szName    = "gpu_cc_demet_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x2217FC16,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_DEMET_CBCR), HWIO_PHYS(GPUCC_GPU_CC_XO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 13,
    },
  },
  {
    .szName    = "gpu_cc_freq_measure_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0xC306597F,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_FREQ_MEASURE_CBCR), HWIO_PHYS(GPUCC_GPU_CC_XO_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 12,
    },
  },
  {
    .szName    = "gpu_cc_gx_cxo_clk",
    .pDomain   = &ClockDomain_GPUCC_GPUCCXO,
    .pDebugMux = &ClockDebugMux_GPUCC,
    .nUniqueId = 0x28DEB84B,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(GPUCC_GPU_CC_GX_CXO_CBCR), HWIO_PHYS(GPUCC_GPU_CC_GX_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 17,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCAHB                                        */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_ahb_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCAHB,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x12DABE26,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_AHB_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_INTERFACE_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 7,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCMVS0                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_mvs0_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS0,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x69F9979C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 3,
    },
  },
  {
    .szName    = "video_cc_mvs0c_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS0,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0xCC22911E,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 1,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCMVS1                                       */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_mvs1_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS1,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x770FB487,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 5,
    },
  },
  {
    .szName    = "video_cc_mvs1_div2_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS1,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x76EA694C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_DIV2_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 8,
    },
  },
  {
    .szName    = "video_cc_mvs1c_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCMVS1,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0xD3F30B66,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_CBCR), HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_BCR), {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 9,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX                                 */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_pll_test_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCPLLTESTMUX,
    .pDebugMux = NULL,
    .nUniqueId = 0xF56D61DD,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_PLL_TEST_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = HAL_CLK_NO_DEBUG_MUX_SEL,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCSLEEP                                      */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_sleep_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCSLEEP,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x2CE12181,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_SLEEP_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 12,
    },
  },

  /*-----------------------------------------------------------------------*/
  /* ClockDomain_VIDEOCC_VIDEOCCXO                                         */
  /*-----------------------------------------------------------------------*/
  {
    .szName    = "video_cc_xo_clk",
    .pDomain   = &ClockDomain_VIDEOCC_VIDEOCCXO,
    .pDebugMux = &ClockDebugMux_VIDEOCC,
    .nUniqueId = 0x3777936C,
    .nFlags    = 0x0,
    .HALClock  = {
      .mRegisters   = { HWIO_PHYS(VCODEC_VIDEO_CC_XO_CBCR), 0, {0, 0} },
      .pmControl    = &HAL_clk_GenericClockControl,
      .nDebugMuxSel = 11,
    },
  },
};


/*=========================================================================
      Power Domains
==========================================================================*/

static ClockPowerDomainNodeType aPowerDomains[] =
{
  {
    .szName         = "cam_cc_bps_gdsc",
    .nRailMask      = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_BPS_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_ife_0_gdsc",
    .nRailMask      = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_IFE_0_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_ife_1_gdsc",
    .nRailMask      = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_IFE_1_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_ife_2_gdsc",
    .nRailMask      = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_IFE_2_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_ipe_0_gdsc",
    .nRailMask      = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_IPE_0_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "cam_cc_titan_top_gdsc",
    .nRailMask      = RAIL_VDD_CAM_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(CAM_CC_TITAN_TOP_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "disp_cc_mdss_core_gdsc",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(DISP_CC_MDSS_CORE_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "disp_cc_mdss_core_int2_gdsc",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(DISP_CC_MDSS_CORE_INT2_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_AUDIO_TBU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_TBU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_aggre_noc_mmu_tbu1_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU1_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_aggre_noc_mmu_tbu2_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU2_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_all_smmu_mmu_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_ALL_SMMU_MMU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_gpu_smmu_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_GPU_SMMU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF0_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF1_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_tbu_hf2_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF2_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_tbu_hf3_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF3_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF0_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF1_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_mmu_tcu_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_MMU_TCU_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_turing_mmu_tbu0_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_TURING_MMU_TBU0_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_hlos1_vote_turing_mmu_tbu1_gds",
    .nRailMask      = RAIL_VDD_CX,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_HLOS1_VOTE_TURING_MMU_TBU1_GDS),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_pcie_0_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MXA,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_PCIE_0_GDSCR),
      .VoterRegister  = {HWIO_PHYS(GCC_PROC_GDSC_COLLAPSE_ENA_VOTE), 0x1},
      .pmControl      = &HAL_clk_PCIePowerDomainControl,
    },
  },
  {
    .szName         = "gcc_ufs_phy_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MXA,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_UFS_PHY_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gcc_usb30_prim_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MXA,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GCC_USB30_PRIM_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gpu_cc_cx_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MXA,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GPUCC_GPU_CC_CX_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "gpu_cc_gx_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_GX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(GPUCC_GPU_CC_GX_GDSCR),
      .pmControl      = &HAL_clk_GPUGxPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs0_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs0c_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS0C_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs1_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
  {
    .szName         = "video_cc_mvs1c_gdsc",
    .nRailMask      = RAIL_VDD_CX | RAIL_VDD_MXC,
    .nFlags         = 0x0,
    .HALPowerDomain = {
      .nGDSCRAddr     = HWIO_PHYS(VCODEC_VIDEO_CC_MVS1C_GDSCR),
      .pmControl      = &HAL_clk_GenericPowerDomainControl,
    },
  },
};


/*=========================================================================
      Main BSP
==========================================================================*/

ClockBSPType ClockBSP =
{
  .aBases            = aBases,
  .nNumBases         = SIZEOF_ARRAY(aBases),
  .aRails            = aRails,
  .nNumRails         = SIZEOF_ARRAY(aRails),
  .aClocks           = aClocks,
  .nNumClocks        = SIZEOF_ARRAY(aClocks),
  .aDomains          = aDomains,
  .nNumDomains       = SIZEOF_ARRAY(aDomains),
  .aSources          = aSources,
  .nNumSources       = SIZEOF_ARRAY(aSources),
  .aDividers         = aDividers,
  .nNumDividers      = SIZEOF_ARRAY(aDividers),
  .aPowerDomains     = aPowerDomains,
  .nNumPowerDomains  = SIZEOF_ARRAY(aPowerDomains),
  .aDebugMuxes       = aDebugMuxes,
  .nNumDebugMuxes    = SIZEOF_ARRAY(aDebugMuxes),
  .nFlags            = CLOCK_GLOBAL_FLAG_LOG_CLOCK_FREQ_CHANGE |
                       CLOCK_GLOBAL_FLAG_LOG_SOURCE_STATE_CHANGE,
  .SafeMuxConfig     = { 0, 2, 0, 0 },
};


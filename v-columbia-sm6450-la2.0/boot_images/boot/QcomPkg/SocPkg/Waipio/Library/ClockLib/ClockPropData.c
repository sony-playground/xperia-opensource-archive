/*
==============================================================================

FILE:         ClockPropData.c

DESCRIPTION:
  This file contains the clock driver Properties data.

==============================================================================

$Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Waipio/Library/ClockLib/ClockPropData.c#6 $

==============================================================================
  Copyright (c) 2021 QUALCOMM Technologies Incorporated.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================

*/


/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/ClockDxe/ClockBSP.h"
#include "Drivers/ClockDxe/ClockDriver.h"
#include "ClockApps.h"
#include "../HALclkLib/HALclkHWIO.h"
#include "HALhwio.h"


/*=========================================================================
      Externs
==========================================================================*/


/*=========================================================================
      Data Declarations
==========================================================================*/

/*
 * Clock Log Default Configuration.
 *
 */
ClockLogType ClockLogDefaultConfig[] =
{
  {
     .nLogSize        =  0x4096,
     .nGlobalLogFlags =  0x90ff
  }
};

ClockStubType ClockStubConfig[] =
{
  {
    .bRUMI = FALSE,
    .bVirtio = FALSE
  }
};


/*
 * Initial rail voltage BSP data.
 */
ClockRailConfigType ClockRailConfig[] =
{
  { "/vcs/mxc",      RAIL_VOLTAGE_LEVEL_NOM },
  { "/vcs/vdd_cx",   RAIL_VOLTAGE_LEVEL_NOM },
  { "/vcs/vdd_gx",   RAIL_VOLTAGE_LEVEL_NOM },
  { "/vcs/vdd_mm",   RAIL_VOLTAGE_LEVEL_NOM },
  { "/vcs/vdd_mx",   RAIL_VOLTAGE_LEVEL_NOM },
  { "/vcs/vdd_mxa",  RAIL_VOLTAGE_LEVEL_NOM },
  { "/vcs/vdd_mxc",  RAIL_VOLTAGE_LEVEL_NOM },
  { NULL }
};

/*
 * BIST dependencies
 */
ClockNameListType ClockBistDependencies[] =
{
  { "gcc_camera_xo_clk"                   },
  { "gcc_camera_ahb_clk"                  },
  { "gcc_disp_xo_clk"                     },
  { "gcc_disp_ahb_clk"                    },
  { "gcc_video_xo_clk"                    },
  { "gcc_video_ahb_clk"                   },
  { "disp_cc_mdss_rscc_ahb_clk"           },
  { NULL }
};

ClockNameListType ClockDCDEnableDependencies[] =
{
  { "gcc_camera_xo_clk"         },
  { "gcc_camera_ahb_clk"        },
  { "gcc_video_xo_clk"          },
  { "gcc_video_ahb_clk"         },
  { "disp_cc_mdss_rscc_ahb_clk" },
  { NULL },
};

ClockNameListType ClockDCDDisableDependencies[] =
{
  { "disp_cc_mdss_rscc_ahb_clk" },
  { "gcc_video_ahb_clk"         },
  { "gcc_video_xo_clk"          },
  { "gcc_camera_ahb_clk"        },
  { "gcc_camera_xo_clk"         },
  { NULL },
};

/*
 * List of clocks anticipated to fail the BIST.
 */
ClockNameListType ClockBistExceptions[] =
{
  // Internal Dividers
  { "disp_cc_mdss_spdm_dp_pixel1_clk" },
  { "disp_cc_mdss_dptx1_link_intf_clk" },
  { "disp_cc_mdss_dptx2_link_intf_clk" },
  { "disp_cc_mdss_dptx3_link_intf_clk" },
  { "disp_cc_mdss_spdm_mdp_clk" },
  { "disp_cc_mdss_spdm_pclk0_clk" },
  { "disp_cc_mdss_spdm_pclk1_clk" },
  { "disp_cc_mdss_spdm_rot_clk" },
  { "video_cc_mvs0c_clk" },
  { "video_cc_mvs1c_clk" },
  { "gpu_cc_spdm_gx_gfx3d_div_clk" },
 
  // Derived by External source 
  { "gcc_usb3_prim_phy_pipe_clk" },
  
  // b_cbcr_clk_en: False
  { "cam_cc_core_ahb_clk" },
  { "disp_cc_mdss_mdp_lut_clk" },
  { "disp_cc_mdss_mdp_lut1_clk" },
  { "disp_cc_mdss_non_gdsc_ahb_clk" },
  { "disp_cc_mdss_dptx0_crypto_clk" },
  { "disp_cc_mdss_dptx1_crypto_clk" },
  { "disp_cc_mdss_dptx2_crypto_clk" },
  { "disp_cc_mdss_dptx3_crypto_clk" },
  { "gcc_ddrss_pcie_sf_tbu_clk" },
  { "gcc_qupv3_wrap0_core_2x_clk" },
  { "gcc_qupv3_wrap0_core_clk" },
  { "gcc_qupv3_wrap1_core_2x_clk" },
  { "gcc_qupv3_wrap1_core_clk" },
  { "gcc_qupv3_wrap2_core_2x_clk" },
  { "gcc_qupv3_wrap2_core_clk" },
  { "gcc_qupv3_wrap_0_m_ahb_clk" },
  { "gcc_qupv3_wrap_1_m_ahb_clk" },
  { "gcc_qupv3_wrap_2_m_ahb_clk" },
  { "gpu_cc_ahb_clk" },
  { "gpu_cc_crc_ahb_clk" },
  { "gpu_cc_cxo_aon_clk" },
  { "video_cc_ahb_clk" },
  { "gcc_pcie_0_aux_clk" },
  { "gcc_pcie_0_cfg_ahb_clk" },
  { "gcc_pcie_0_mstr_axi_clk" },
  { "gcc_pcie_0_pipe_clk" },
  { "gcc_pcie_0_slv_axi_clk" },
  { "gcc_pcie_0_slv_q2a_axi_clk" },
  { "gcc_pcie_1_aux_clk" },
  { "gcc_pcie_1_cfg_ahb_clk" },
  { "gcc_pcie_1_mstr_axi_clk" },
  { "gcc_pcie_1_pipe_clk" },
  { "gcc_pcie_1_slv_axi_clk" },
  { "gcc_pcie_1_slv_q2a_axi_clk" },
  { "gcc_qupv3_wrap_0_s_ahb_clk" },
  { "gcc_qupv3_wrap_1_s_ahb_clk" },
  { "gcc_qupv3_wrap_2_s_ahb_clk" },
  { "gpu_cc_cx_apb_clk" },
  { "gpu_cc_cx_qdss_at_clk" },
  { "gpu_cc_cx_qdss_trig_clk" },
  { "gpu_cc_cx_qdss_tsctr_clk" },
  { "gpu_cc_cx_snoc_dvm_clk" },
  { "gpu_cc_gx_qdss_tsctr_clk" },
  { "gpu_cc_gx_vsense_clk" },
  { "gpu_cc_sleep_clk" },

  // b_daisy_chain: True
  { "disp_cc_mdss_mdp_clk" },
  { "disp_cc_mdss_mdp_lut_clk" },
  { "disp_cc_mdss_rot_clk" },
  
  // b_hw_votable: True
  { "gcc_ddrss_pcie_sf_tbu_clk" },
  { "gcc_qupv3_wrap0_core_2x_clk" },
  { "gcc_qupv3_wrap0_core_clk" },
  { "gcc_qupv3_wrap1_core_2x_clk" },
  { "gcc_qupv3_wrap1_core_clk" },
  { "gcc_qupv3_wrap2_core_2x_clk" },
  { "gcc_qupv3_wrap2_core_clk" },
  { "gcc_qupv3_wrap_0_m_ahb_clk" },
  { "gcc_qupv3_wrap_1_m_ahb_clk" },
  { "gcc_qupv3_wrap_2_m_ahb_clk" },
  { "gcc_gpu_gpll0_clk_src" },
  { "gcc_gpu_gpll0_div_clk_src" },
  { "gcc_pcie_0_aux_clk" },
  { "gcc_pcie_0_cfg_ahb_clk" },
  { "gcc_pcie_0_mstr_axi_clk" },
  { "gcc_pcie_0_pipe_clk" },
  { "gcc_pcie_0_slv_axi_clk" },
  { "gcc_pcie_0_slv_q2a_axi_clk" },
  { "gcc_pcie_1_aux_clk" },
  { "gcc_pcie_1_cfg_ahb_clk" },
  { "gcc_pcie_1_mstr_axi_clk" },
  { "gcc_pcie_1_pipe_clk" },
  { "gcc_pcie_1_slv_axi_clk" },
  { "gcc_pcie_1_slv_q2a_axi_clk" },
  { "gcc_qupv3_wrap_0_s_ahb_clk" },
  { "gcc_qupv3_wrap_1_s_ahb_clk" },
  { "gcc_qupv3_wrap_2_s_ahb_clk" },
  { "gcc_pcie_0_mstr_axi_clk" },
  { "gcc_pcie_0_slv_axi_clk" },

  // Slave Clocks
  { "gpu_cc_cxo_aon_clk" },
  { "gpu_cc_cx_apb_clk" },
  { "gpu_cc_cx_qdss_at_clk" },
  { "gpu_cc_cx_qdss_trig_clk" },
  { "gpu_cc_cx_qdss_tsctr_clk" },
  { "gpu_cc_cx_snoc_dvm_clk" },
  { "gpu_cc_cxo_clk" },
  { "gpu_cc_gx_cxo_clk" },
  { "gpu_cc_gx_qdss_tsctr_clk" },
  { "gpu_cc_gx_vsense_clk" },
  { "gpu_cc_sleep_clk" },

  // Debug Clocks
  { "disp_cc_debug_clk" },
  { "cam_cc_debug_clk" },
  { "video_cc_debug_clk" },
  { "cam_cc_pll_test_clk" },
  { "disp_cc_pll_test_clk" },
  { "gpu_cc_pll_test_clk" },
  { "video_cc_pll_test_clk" },

  {NULL}
};

/*
 * List of clocks excluded from the BIST.
 */
ClockNameListType ClockExcludeFromBist[] =
{
  // CPU clocks
  { "apcs_gold_post_acd_clk"                     },
  { "apcs_goldplus_post_acd_clk"                 },
  { "apcs_l3_post_acd_clk"                       },
  { "apcs_silver_post_acd_clk"                   },

  // Reset's
  { "gpucc_gpu_cc_gmu_bcr"                       },
  { "gcc_pcie_0_link_down_bcr"                   },
  { "gcc_pcie_0_nocsr_com_phy_bcr"               },
  { "gcc_pcie_0_phy_bcr"                         },
  { "gcc_pcie_0_phy_nocsr_com_phy_bcr"           },
  { "gcc_pcie_1_link_down_bcr"                   },
  { "gcc_pcie_1_nocsr_com_phy_bcr"               },
  { "gcc_pcie_1_phy_bcr"                         },
  { "gcc_pcie_1_phy_nocsr_com_phy_bcr"           },
  { "gcc_pcie_phy_bcr"                           },
  { "gcc_pcie_phy_cfg_ahb_bcr"                   },
  { "gcc_pcie_phy_com_bcr"                       },
  { "gcc_qusb2phy_prim_bcr"                      },
  { "gcc_qusb2phy_sec_bcr"                       },
  { "gcc_usb3_dp_phy_prim_bcr"                   },
  { "gcc_usb3_dp_phy_sec_bcr"                    },
  { "gcc_usb3_phy_prim_bcr"                      },
  { "gcc_usb3_phy_sec_bcr"                       },
  { "gcc_usb3phy_phy_prim_bcr"                   },
  { "gcc_usb3phy_phy_sec_bcr"                    },
  { "gpucc_gpu_cc_ff_bcr" },

  // Special voting register for GCC
  { "gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_clk" },
  { "gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_clk"  },
  { "gcc_hlos1_vote_aggre_noc_mmu_tbu1_clk"      },
  { "gcc_hlos1_vote_aggre_noc_mmu_tbu2_clk"      },
  { "gcc_hlos1_vote_all_smmu_mmu_clk"            },
  { "gcc_hlos1_vote_gpu_smmu_clk"                },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_clk"       },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_clk"       },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_clk"       },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_clk"       },
  { "gcc_hlos1_vote_mmu_tcu_clk"                 },
  { "gcc_hlos1_vote_turing_mmu_tbu0_clk"         },
  { "gcc_hlos1_vote_turing_mmu_tbu1_clk"         },
  
  { "gcc_memnoc_turing_clk_en"                   },
  { "gcc_mmu_memnoc_tcu_clk_en"                  },
  { "gcc_memnoc_mss_q6_clk_en"                   },
  { "gcc_memnoc_mss_offline_clk_en"              },

  // Not a real Clock Branch, just a intermediate Domain
  { "gcc_gpu_gpll0_clk_src" },
  { "gcc_gpu_gpll0_div_clk_src" },
  { NULL }
};

/*
 * List of power domain names NOT to be enabled prior to running the BIST.
 */
ClockNameListType ClockBistExcludedPowerDomainNames[] =
{
  { "gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_gds" },
  { "gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_gds"  },
  { "gcc_hlos1_vote_aggre_noc_mmu_tbu1_gds"      },
  { "gcc_hlos1_vote_aggre_noc_mmu_tbu2_gds"      },
  { "gcc_hlos1_vote_all_smmu_mmu_gds"            },
  { "gcc_hlos1_vote_gpu_smmu_gds"                },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_gds"       },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_gds"       },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_gds"       },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_gds"       },
  { "gcc_hlos1_vote_mmu_tcu_gds"                 },
  { "gcc_hlos1_vote_turing_mmu_tbu0_gds"         },
  { "gcc_hlos1_vote_turing_mmu_tbu1_gds"         },
  { NULL }
};

ClockResult  Clock_GetPropertyHandle
(
const char* str, 
void** handle  
)
{
  if (strcmp("ClockRailConfig",str) == 0)
  {
    *handle = ClockRailConfig;
  }
  else if (strcmp("BISTDependencies",str) == 0)
  {
    *handle = ClockBistDependencies;
  }
  else if (strcmp("BISTExceptions",str) == 0)
  {
    *handle = ClockBistExceptions;
  }
  else if (strcmp("ClockDCDEnableDependencies",str) == 0)
  {
    *handle = ClockDCDEnableDependencies;
  }
  else if (strcmp("ClockDCDDisableDependencies",str) == 0)
  {
    *handle = ClockDCDDisableDependencies;
  }
  else if (strcmp("ExcludeFromBist",str) == 0)
  {
    *handle = ClockExcludeFromBist;
  }
  else if (strcmp("ExcludedPowerDomains",str) == 0)
  {
    *handle = ClockBistExcludedPowerDomainNames;
  }
  else if(strcmp("ClockLogDefaults",str) == 0)
  {
    *handle = ClockLogDefaultConfig;
  }
  else
  {
    *handle = NULL;
    return CLOCK_ERROR;
  }

  return CLOCK_SUCCESS;
}



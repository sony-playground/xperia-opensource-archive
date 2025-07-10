/*
==============================================================================

FILE:         ClockPropData.c

DESCRIPTION:
  This file contains the clock driver Properties data.

==============================================================================

$Header: $

==============================================================================
  Copyright (c) 2021, 2022 QUALCOMM Technologies Incorporated.
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
     .nLogSize        =  0x8192,
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
  { "/vcs/vdd_cx",   RAIL_VOLTAGE_LEVEL_NOM },
  { "/vcs/vdd_mx",   RAIL_VOLTAGE_LEVEL_NOM },
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
  //Internal CDIV's
  { "cam_cc_spdm_bps_clk"                         },
  { "cam_cc_spdm_ope_0_clk"                       },
  { "cam_cc_spdm_tfe_0_clk"                       },
  { "cam_cc_spdm_tfe_0_csid_clk"                  },
 
  // Debug Clocks
  { "cam_cc_debug_clk"                            },
  { "cam_cc_pll_test_clk"                         },
  { "disp_cc_debug_clk"                           },
  { "disp_cc_mdss_spdm_debug_clk"                 },
  { "gpu_cc_debug_clk"                            },
  { "gpu_cc_debug_measure_clk"                    },
  { "gpu_cc_debug_measure_clk"                    },
  
  // Parent is CMUX's sourced from external PHY's
  { "gcc_gpll0_ufs_phy_rx_symbol_0_clk"           },
  { "gcc_gpll0_ufs_phy_rx_symbol_1_clk"           },
  { "gcc_gpll0_ufs_phy_tx_symbol_0_clk"           },
  { "gcc_ufs_phy_rx_symbol_0_clk"                 },
  { "gcc_ufs_phy_rx_symbol_1_clk"                 },
  { "gcc_ufs_phy_tx_symbol_0_clk"                 },
  { "gcc_ufs_phy_tx_symbol_1_clk"                 },
 
  //l_master: Slave Clocks
  { "cam_cc_icp_apb_clk"                          },
  { "cam_cc_icp_ts_clk"                           },
  { "cam_cc_sys_tmr_clk"                          },
  { "gpu_cc_cb_clk"                               },
  { "gpu_cc_cx_apb_clk"                           },
  { "gpu_cc_cx_qdss_tsctr_clk"                    },
  { "cam_cc_camnoc_atb_clk"                       },
  { "cam_cc_camnoc_axi_hf_clk"                    },
  { "cam_cc_camnoc_axi_sf_clk"                    },
  { "cam_cc_icp_atb_clk"                          },
  { "cam_cc_icp_cti_clk"                          },
  { "cam_cc_soc_ahb_clk"                          },
  { "gpu_cc_memnoc_gfx_clk"                       },
  { "gpu_cc_sleep_clk"                            },
  { "gpu_cc_cx_qdss_at_clk"                       },
  { "gpu_cc_cx_qdss_trig_clk"                     },
  { "gpu_cc_gx_vsense_clk"                        },
  { "gpu_cc_gx_vsense_clk"                        },
  
  //b_cbcr_clk_en: False
  { "gpu_cc_cx_apb_clk"                           },
  { "gpu_cc_cx_qdss_tsctr_clk"                    },
  { "gpu_cc_gx_qdss_tsctr_clk"                    },
  { "gpu_cc_sleep_clk"                            },
  { "gcc_qupv3_wrap_0_m_ahb_clk"                  },
  { "gcc_aggre_noc_pcie_0_axi_clk"                },
  { "gcc_ddrss_pcie_sf_tbu_clk"                   },
  { "gcc_pcie_0_mstr_axi_clk"                     },
  { "gcc_pcie_0_slv_axi_clk"                      },
  { "gcc_pcie_0_slv_q2a_axi_clk"                  },
  { "gcc_boot_rom_ahb_clk"                        },
  { "gcc_cfg_noc_pcie_anoc_ahb_clk"               },
  { "gcc_pcie_0_cfg_ahb_clk"                      },
  { "gcc_qupv3_wrap_0_s_ahb_clk"                  },
  { "gcc_qupv3_wrap_1_s_ahb_clk"                  },
  { "gpu_cc_cx_qdss_at_clk"                       },
  { "gpu_cc_cx_qdss_trig_clk"                     },
  { "gcc_qupv3_wrap0_core_2x_clk"                 },
  { "gcc_qupv3_wrap0_core_clk"                    },
  { "gcc_qupv3_wrap0_s0_clk"                      },
  { "gcc_qupv3_wrap0_s1_clk"                      },
  { "gcc_qupv3_wrap0_s2_clk"                      },
  { "gcc_qupv3_wrap0_s3_clk"                      },
  { "gcc_qupv3_wrap0_s4_clk"                      },
  { "gcc_qupv3_wrap1_core_clk"                    },
  { "gcc_qupv3_wrap0_s2_clk"                      },
  { "gcc_qupv3_wrap1_s0_clk"                      },
  { "gcc_qupv3_wrap1_s1_clk"                      },
  { "gcc_qupv3_wrap1_s2_clk"                      },
  { "gcc_qupv3_wrap1_s3_clk"                      },
  { "gcc_qupv3_wrap1_s4_clk"                      },
  { "gpu_cc_gx_vsense_clk"                        },
  { "gpu_cc_cx_gfx3d_slv_clk"                     },
  { "gpu_cc_cx_gfx3d_slv_clk"                     },

  //b_hw_votable: True
  { "gcc_qupv3_wrap_0_m_ahb_clk"                  },
  { "gcc_aggre_noc_pcie_0_axi_clk"                },
  { "gcc_ddrss_pcie_sf_tbu_clk"                   },
  { "gcc_pcie_0_mstr_axi_clk"                     },
  { "gcc_pcie_0_slv_axi_clk"                      },
  { "gcc_pcie_0_slv_q2a_axi_clk"                  },
  { "gcc_boot_rom_ahb_clk"                        },
  { "gcc_cfg_noc_pcie_anoc_ahb_clk"               },
  { "gcc_pcie_0_cfg_ahb_clk"                      },
  { "gcc_qupv3_wrap_0_s_ahb_clk"                  },
  { "gcc_qupv3_wrap_1_s_ahb_clk"                  },
  { "gcc_qupv3_wrap0_core_2x_clk"                 },
  { "gcc_qupv3_wrap0_core_2x_clk"                 },
  { "gcc_qupv3_wrap0_core_clk"                    },
  { "gcc_qupv3_wrap0_s1_clk"                      },
  { "gcc_qupv3_wrap0_s2_clk"                      },
  { "gcc_qupv3_wrap0_s3_clk"                      },
  { "gcc_qupv3_wrap0_s4_clk"                      },
  { "gcc_qupv3_wrap1_core_clk"                    },
  { "gcc_qupv3_wrap1_s0_clk"                      },
  { "gcc_qupv3_wrap1_s1_clk"                      },
  { "gcc_qupv3_wrap1_s2_clk"                      },
  { "gcc_qupv3_wrap1_s3_clk"                      },
  { "gcc_qupv3_wrap1_s4_clk"                      },
  {NULL},
};

/*
 * List of clocks excluded from the BIST.
 */
ClockNameListType ClockExcludeFromBist[] =
{
  
  {"apcs_silver_post_acd_clk"                     },
  
  // Reset's
  { "gcc_pcie_0_link_down_bcr"                    },
  { "gcc_pcie_0_nocsr_com_phy_bcr"                },
  { "gcc_pcie_0_phy_bcr"                          },
  { "gcc_pcie_0_phy_nocsr_com_phy_bcr"            },
  { "gcc_pcie_phy_cfg_ahb_bcr"                    },
  { "gcc_pcie_phy_com_bcr"                        },
  { "gcc_qusb2phy_prim_bcr"                       },
  { "gcc_qusb2phy_sec_bcr"                        },
  { "gcc_usb3_dp_phy_prim_bcr"                    },
  { "gcc_usb3_dp_phy_sec_bcr"                     },
  { "gcc_usb3_phy_prim_bcr"                       },
  { "gcc_usb3_phy_sec_bcr"                        },
  { "gcc_usb3phy_phy_prim_bcr"                    },
  { "gcc_usb3phy_phy_sec_bcr"                     },
  { "gpucc_gpu_cc_ff_bcr"                         },
  { "gpucc_gpu_cc_gmu_bcr"                        },
 
  // Special Votable Clocks
  { "gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_clk"  },
  { "gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_clk"   },
  { "gcc_hlos1_vote_aggre_noc_mmu_tbu1_clk"       },
  { "gcc_hlos1_vote_aggre_noc_mmu_tbu2_clk"       },
  { "gcc_hlos1_vote_all_smmu_mmu_clk"             },
  { "gcc_hlos1_vote_gpu_smmu_clk"                 },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_clk"        },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_clk"        },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_clk"        },
  { "gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_clk"        },
  { "gcc_hlos1_vote_mmu_tcu_clk"                  },
  { "gcc_hlos1_vote_turing_mmu_tbu0_clk"          },
  { "gcc_hlos1_vote_turing_mmu_tbu1_clk"          },
  
  // These are not really Clock gates, but actually a MUX
  { "gcc_eusb3_0_clkref_en"                        },
  { "gcc_gpu_memnoc_gfx_clk_en"                    },
  { "gcc_pcie_0_clkref_en"                         },
  { "gcc_qlink_clkref_en"                          },
  { "gcc_ufs_0_clkref_en"                          },
  { "gcc_ufs_pad_clkref_en"                        },
  { "gcc_usb3_0_clkref_en"                         },
  { "gcc_usb3_0_clkref_en"                         },
 
  // Not a real Clock Branch, just a intermediate Domain
  { "gcc_gpu_gpll0_clk_src"                        },
  { "gcc_gpu_gpll0_div_clk_src"                    },
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



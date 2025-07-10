#!/usr/bin/env python

CLOCK_FLAGS = {
  'gcc_sys_noc_cpuss_ahb_clk':    ['SUPPRESSIBLE', 'LEAVE_ALWAYS_ON'],
  'gcc_qupv3_wrap0_s0_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap0_s1_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap0_s2_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap0_s3_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap0_s4_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap0_s5_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap0_s6_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap0_s7_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap1_s0_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap1_s1_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap1_s2_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap1_s3_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap1_s4_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap1_s5_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap1_s6_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap2_s0_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap2_s1_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap2_s2_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap2_s3_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap2_s4_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap2_s5_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
  'gcc_qupv3_wrap2_s6_clk_src':   ['DOMAIN_WAIT_FOR_ROOT_OFF'],
}

CLOCK_FLAGS_HAL = {
  'disp_cc_mdss_mdp_clk_src':   ['DOMAIN_HW_CLK_CONTROL'],
  'gcc_pcie_0_aux_clk_src'  :   ['DOMAIN_HW_CLK_CONTROL'],
  'gcc_pcie_1_aux_clk_src'  :   ['DOMAIN_HW_CLK_CONTROL'],
}

HAL_CONTROL = {
  'gcc_pcie_0_gdsc':  'HAL_clk_PCIePowerDomainControl',
  'gcc_pcie_1_gdsc':  'HAL_clk_PCIePowerDomainControl',
  'gpu_cc_gx_gdsc' :  'HAL_clk_GPUGxPowerDomainControl',
}

def clk_from_reg(reg_name):
  return {
    'd_registers': {'cbcr_name': reg_name.upper()}, 
    'd_sw_owner': {'APCS': 'RW'}, 
    'l_master': ['bi_tcxo'],
  }

def gds_from_reg(reg_name):
    return {
        'd_registers' : {'gdscr_name': reg_name.upper()},
        'd_sw_owner'  : {'APCS': 'RW'}
    }

DB_OVERRIDE = {      
  'GCC': {
    'cbc': {
       'gcc_memnoc_turing_clk_en':      clk_from_reg('gcc_memnoc_turing_clk_en'),
       'gcc_gpu_memnoc_gfx_clk_en':     clk_from_reg('gcc_gpu_memnoc_gfx_clk_en'),
       'gcc_mmu_memnoc_tcu_clk_en':     clk_from_reg('gcc_mmu_memnoc_tcu_clk_en'),
       'gcc_memnoc_mss_q6_clk_en':      clk_from_reg('gcc_memnoc_mss_q6_clk_en'),
       'gcc_memnoc_mss_offline_clk_en': clk_from_reg('gcc_memnoc_mss_offline_clk_en'),
       'gcc_cxo2_tx1_clkref_en1':       clk_from_reg('gcc_cxo2_tx1_clkref_en1'),

       'gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_clk': clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_clk'),
       'gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_clk':  clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_clk'),
       'gcc_hlos1_vote_aggre_noc_mmu_tbu1_clk':      clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_tbu1_clk'),
       'gcc_hlos1_vote_aggre_noc_mmu_tbu2_clk':      clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_tbu2_clk'),
       'gcc_hlos1_vote_all_smmu_mmu_clk':            clk_from_reg('gcc_hlos1_vote_all_smmu_mmu_clk'),
       'gcc_hlos1_vote_gpu_smmu_clk':                clk_from_reg('gcc_hlos1_vote_gpu_smmu_clk'),
       'gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_clk'),
       'gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_clk'),
       'gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_clk'),
       'gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_clk'),
       'gcc_hlos1_vote_mmu_tcu_clk':                 clk_from_reg('gcc_hlos1_vote_mmu_tcu_clk'),
       'gcc_hlos1_vote_turing_mmu_tbu0_clk':         clk_from_reg('gcc_hlos1_vote_turing_mmu_tbu0_clk'),
       'gcc_hlos1_vote_turing_mmu_tbu1_clk':         clk_from_reg('gcc_hlos1_vote_turing_mmu_tbu1_clk'),
    },

    'sm_gdsc': {
       'gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_gds': gds_from_reg('GCC_HLOS1_VOTE_AGGRE_NOC_MMU_AUDIO_TBU_GDS'),
       'gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_gds':  gds_from_reg('GCC_HLOS1_VOTE_AGGRE_NOC_MMU_PCIE_TBU_GDS'),
       'gcc_hlos1_vote_aggre_noc_mmu_tbu1_gds':      gds_from_reg('GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU1_GDS'),
       'gcc_hlos1_vote_aggre_noc_mmu_tbu2_gds':      gds_from_reg('GCC_HLOS1_VOTE_AGGRE_NOC_MMU_TBU2_GDS'),
       'gcc_hlos1_vote_all_smmu_mmu_gds':            gds_from_reg('GCC_HLOS1_VOTE_ALL_SMMU_MMU_GDS'),
       'gcc_hlos1_vote_gpu_smmu_gds':                gds_from_reg('GCC_HLOS1_VOTE_GPU_SMMU_GDS'),
       'gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_gds':       gds_from_reg('GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF0_GDS'),
       'gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_gds':       gds_from_reg('GCC_HLOS1_VOTE_MMNOC_MMU_TBU_HF1_GDS'),
       'gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_gds':       gds_from_reg('GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF0_GDS'),
       'gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_gds':       gds_from_reg('GCC_HLOS1_VOTE_MMNOC_MMU_TBU_SF1_GDS'),
       'gcc_hlos1_vote_mmu_tcu_gds':                 gds_from_reg('GCC_HLOS1_VOTE_MMU_TCU_GDS'),
       'gcc_hlos1_vote_turing_mmu_tbu0_gds':         gds_from_reg('GCC_HLOS1_VOTE_TURING_MMU_TBU0_GDS'),
       'gcc_hlos1_vote_turing_mmu_tbu1_gds':         gds_from_reg('GCC_HLOS1_VOTE_TURING_MMU_TBU1_GDS'),
    },
  },
}


CLOCKDRIVERGEN_CONFIG = {
  'target': 'waipio',
  'filter_warning': 'sw',
  'db_override': DB_OVERRIDE,
  'generators': [{
    'type': 'dalclock',
    'output_dir': 'sm8450_output_dir',
    
    'options': {
      'env': ['apcs', 'gpuss'],
      'clock_flags': CLOCK_FLAGS,
      'clock_flags_hal': CLOCK_FLAGS_HAL,
      'hal_ctl_structs': HAL_CONTROL,
      'driver_flags': ['LOG_CLOCK_FREQ_CHANGE', 'LOG_SOURCE_STATE_CHANGE'],
      'include_HALclkPLLSettings.h': False,
      'standalone_bcrs': ['.*pcie.*', '.*usb.*'],
      'include_fmax': ['.*'],
      'include_divider': ['.*'],
      'include_source_map': ['.*'],
      'pll_disable_mode': {'disp_cc_pll0': 'NORMAL', 'disp_cc_pll1': 'NORMAL'},
      'map_bases': True,
      'multi_rail': True,
      'npa_rename': {
        '/vcs/vdd_mxa': '/vcs/vdd_mx',
        '/vcs/mxc'    : '/vcs/vdd_mxc'
      },
    },
  }],
}

if __name__ == "__main__":
  import sys, os
  from subprocess import call

  if os.name == 'nt':
    clockdrivergen_path = r'\\ben\corebsp_labdata_0001\sysdrv\clockdrivergen\bin\clockdrivergen.py'
  else:
    clockdrivergen_path = r'/net/ben/vol/eng_asw_labdata_0001/corebsp_labdata_0001/sysdrv/clockdrivergen/bin/clockdrivergen.py'

  call(['python3', clockdrivergen_path, '--cfg', __file__] + sys.argv[1:])


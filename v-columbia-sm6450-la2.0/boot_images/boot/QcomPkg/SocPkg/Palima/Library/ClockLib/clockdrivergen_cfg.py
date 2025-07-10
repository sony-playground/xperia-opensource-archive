#!/usr/bin/env python

CLOCK_FLAGS = {
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
        'd_registers' : {'cbcr_name': reg_name.upper()},
        'd_sw_owner'  : {'APCS': 'RW'},
        'l_master'    : ['bi_tcxo'],
    }

def gds_from_reg(reg_name):
    return {
        'd_registers' : {'gdscr_name': reg_name.upper()},
        'd_sw_owner'  : {'APCS': 'RW'}
    }

def bcr_from_reg(reg_name):
    return {
        'd_registers' : {'bcr_name': reg_name.upper()},
        'd_sw_owner'  : {'APCS': 'RW'},
    }

DB_OVERRIDE = {
    'GCC': {
        'cbc': {
            'gcc_ufs_0_clkref_en':           clk_from_reg('gcc_ufs_0_clkref_en'),
            'gcc_qlink_clkref_en':           clk_from_reg('gcc_qlink_clkref_en'),
            'gcc_pcie_0_clkref_en':          clk_from_reg('gcc_pcie_0_clkref_en'),
            'gcc_pcie_1_clkref_en':          clk_from_reg('gcc_pcie_1_clkref_en'),
            'gcc_usb3_0_clkref_en':          clk_from_reg('gcc_usb3_0_clkref_en'),
            'gcc_eusb3_0_clkref_en':         clk_from_reg('gcc_eusb3_0_clkref_en'),
            'gcc_cxo2_tx1_clkref_en1':       clk_from_reg('gcc_cxo2_tx1_clkref_en1'),
            'gcc_memnoc_turing_clk_en':      clk_from_reg('gcc_memnoc_turing_clk_en'),
            'gcc_memnoc_mss_q6_clk_en':      clk_from_reg('gcc_memnoc_mss_q6_clk_en'),
            'gcc_gpu_memnoc_gfx_clk_en':     clk_from_reg('gcc_gpu_memnoc_gfx_clk_en'),
            'gcc_mmu_memnoc_tcu_clk_en':     clk_from_reg('gcc_mmu_memnoc_tcu_clk_en'),
            'gcc_memnoc_mss_offline_clk_en': clk_from_reg('gcc_memnoc_mss_offline_clk_en'),
            'gcc_qusb2phy_prim_bcr':         bcr_from_reg('gcc_qusb2phy_prim_bcr'),
            'gcc_qusb2phy_sec_bcr':          bcr_from_reg('gcc_qusb2phy_sec_bcr'),

            'gcc_hlos1_vote_mmu_tcu_clk':                 clk_from_reg('gcc_hlos1_vote_mmu_tcu_clk'),
            'gcc_hlos1_vote_gpu_smmu_clk':                clk_from_reg('gcc_hlos1_vote_gpu_smmu_clk'),
            'gcc_hlos1_vote_all_smmu_mmu_clk':            clk_from_reg('gcc_hlos1_vote_all_smmu_mmu_clk'),
            'gcc_hlos1_vote_turing_mmu_tbu0_clk':         clk_from_reg('gcc_hlos1_vote_turing_mmu_tbu0_clk'),
            'gcc_hlos1_vote_turing_mmu_tbu1_clk':         clk_from_reg('gcc_hlos1_vote_turing_mmu_tbu1_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_hf2_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf2_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_hf3_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf3_clk'),
            'gcc_hlos1_vote_aggre_noc_mmu_tbu1_clk':      clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_tbu1_clk'),
            'gcc_hlos1_vote_aggre_noc_mmu_tbu2_clk':      clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_tbu2_clk'),
            'gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_clk':  clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_clk'),
            'gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_clk': clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_clk'),
        },

        'sm_gdsc': {
            'gcc_hlos1_vote_mmu_tcu_gds':                 gds_from_reg('gcc_hlos1_vote_mmu_tcu_gds'),
            'gcc_hlos1_vote_gpu_smmu_gds':                gds_from_reg('gcc_hlos1_vote_gpu_smmu_gds'),
            'gcc_hlos1_vote_all_smmu_mmu_gds':            gds_from_reg('gcc_hlos1_vote_all_smmu_mmu_gds'),
            'gcc_hlos1_vote_turing_mmu_tbu0_gds':         gds_from_reg('gcc_hlos1_vote_turing_mmu_tbu0_gds'),
            'gcc_hlos1_vote_turing_mmu_tbu1_gds':         gds_from_reg('gcc_hlos1_vote_turing_mmu_tbu1_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_gds':       gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf0_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_gds':       gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_sf0_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_gds':       gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf1_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_gds':       gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_sf1_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_hf2_gds':       gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf2_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_tbu_hf3_gds':       gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_tbu_hf3_gds'),
            'gcc_hlos1_vote_aggre_noc_mmu_tbu1_gds':      gds_from_reg('gcc_hlos1_vote_aggre_noc_mmu_tbu1_gds'),
            'gcc_hlos1_vote_aggre_noc_mmu_tbu2_gds':      gds_from_reg('gcc_hlos1_vote_aggre_noc_mmu_tbu2_gds'),
            'gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_gds':  gds_from_reg('gcc_hlos1_vote_aggre_noc_mmu_pcie_tbu_gds'),
            'gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_gds': gds_from_reg('gcc_hlos1_vote_aggre_noc_mmu_audio_tbu_gds'),
        },
    },
}


CLOCKDRIVERGEN_CONFIG = {
    'target': 'palima',
    'filter_warning': 'sw',
    'db_override': DB_OVERRIDE,
    'generators': [{
        'type': 'dalclock',
        'output_dir': r'palima_output_dir',

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




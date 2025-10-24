#!/usr/bin/env python3

CLOCK_FLAGS = {
}

CLOCK_FLAGS_HAL = {
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

HAL_CONTROL = {
  'gpu_cc_gx_gdsc' :  'HAL_clk_GPUGxPowerDomainControl',
}

DB_OVERRIDE = {
    'GCC': {
        'cbc': {
            'gcc_memnoc_turing_clk_en':      clk_from_reg('gcc_memnoc_turing_clk_en'),
            'gcc_memnoc_mss_q6_clk_en':      clk_from_reg('gcc_memnoc_mss_q6_clk_en'),
            'gcc_gpu_memnoc_gfx_clk_en':     clk_from_reg('gcc_gpu_memnoc_gfx_clk_en'),
            'gcc_mmu_memnoc_tcu_clk_en':     clk_from_reg('gcc_mmu_memnoc_tcu_clk_en'),
            'gcc_memnoc_mss_offline_clk_en': clk_from_reg('gcc_memnoc_mss_offline_clk_en'),

            'gcc_hlos1_vote_mmu_tcu_clk':                clk_from_reg('gcc_hlos1_vote_mmu_tcu_clk'),
            'gcc_hlos1_vote_gpu_smmu_clk':               clk_from_reg('gcc_hlos1_vote_gpu_smmu_clk'),
            'gcc_hlos1_vote_lpass_qtb_clk':              clk_from_reg('gcc_hlos1_vote_lpass_qtb_clk'),
            'gcc_hlos1_vote_all_smmu_mmu_clk':           clk_from_reg('gcc_hlos1_vote_all_smmu_mmu_clk'),
            'gcc_hlos1_vote_turing_mmu_qtb0_clk':        clk_from_reg('gcc_hlos1_vote_turing_mmu_qtb0_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_qtb_sf_clk':       clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_qtb_sf_clk'),
            'gcc_hlos1_vote_aggre_noc_mmu_qtb1_clk':     clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_qtb1_clk'),
            'gcc_hlos1_vote_aggre_noc_mmu_qtb2_clk':     clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_qtb2_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_qtb_hf01_clk':     clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_qtb_hf01_clk'),
            'gcc_hlos1_vote_mmnoc_mmu_qtb_hf23_clk':     clk_from_reg('gcc_hlos1_vote_mmnoc_mmu_qtb_hf23_clk'),
            'gcc_hlos1_vote_aggre_noc_mmu_pcie_qtb_clk': clk_from_reg('gcc_hlos1_vote_aggre_noc_mmu_pcie_qtb_clk'),
        },

        'sm_gdsc': {
            'gcc_hlos1_vote_mmu_tcu_gds':                gds_from_reg('gcc_hlos1_vote_mmu_tcu_gds'),
            'gcc_hlos1_vote_gpu_smmu_gds':               gds_from_reg('gcc_hlos1_vote_gpu_smmu_gds'),
            'gcc_hlos1_vote_lpass_qtb_gds':              gds_from_reg('gcc_hlos1_vote_lpass_qtb_gds'),
            'gcc_hlos1_vote_all_smmu_mmu_gds':           gds_from_reg('gcc_hlos1_vote_all_smmu_mmu_gds'),
            'gcc_hlos1_vote_turing_mmu_qtb0_gds':        gds_from_reg('gcc_hlos1_vote_turing_mmu_qtb0_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_qtb_sf_gds':       gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_qtb_sf_gds'),
            'gcc_hlos1_vote_aggre_noc_mmu_qtb1_gds':     gds_from_reg('gcc_hlos1_vote_aggre_noc_mmu_qtb1_gds'),
            'gcc_hlos1_vote_aggre_noc_mmu_qtb2_gds':     gds_from_reg('gcc_hlos1_vote_aggre_noc_mmu_qtb2_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_qtb_hf01_gds':     gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_qtb_hf01_gds'),
            'gcc_hlos1_vote_mmnoc_mmu_qtb_hf23_gds':     gds_from_reg('gcc_hlos1_vote_mmnoc_mmu_qtb_hf23_gds'),
            'gcc_hlos1_vote_aggre_noc_mmu_pcie_qtb_gds': gds_from_reg('gcc_hlos1_vote_aggre_noc_mmu_pcie_qtb_gds'),
        },
    },
}


CLOCKDRIVERGEN_CONFIG = {
    'target': 'kailua',
    'filter_warning': 'sw',
    'db_override': DB_OVERRIDE,
    'generators': [{
        'type': 'dalclock',
        'output_dir': r'kailua_output_dir',

        'options': {
            'env': ['apcs', 'gpuss'],
            'clock_flags': CLOCK_FLAGS,
            'clock_flags_hal': CLOCK_FLAGS_HAL,
            'hal_ctl_structs': HAL_CONTROL,
            'driver_flags': ['LOG_CLOCK_FREQ_CHANGE', 'LOG_SOURCE_STATE_CHANGE'],
            'include_HALclkPLLSettings.h': False,
            'standalone_bcrs': ['.*pcie.*', '.*usb.*'],
            'npa_rename': {
                '/vcs/mxc': '/vcs/vdd_mxc',
                '/vcs/vdd_mxa': '/vcs/vdd_mx',
                '/vcs/vdd_cam_cx': '/vcs/vdd_mm',
             },
            'include_fmax': ['.*'],
            'include_divider': ['.*'],
            'include_source_map': ['.*'],
            'map_bases': True,
            'multi_rail': True,
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



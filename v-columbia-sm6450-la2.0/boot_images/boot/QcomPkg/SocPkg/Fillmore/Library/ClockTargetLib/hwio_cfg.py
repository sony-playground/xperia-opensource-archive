#!/usr/bin/env python
#===========================================================================
#
#  @file hwio_cfg.py
#
#  @brief HWIO config for the Fillmore XBL Loader Clock HWIO generation.
#
#  This file can be manually invoked with "HWIOGen.py" by calling:
#
#    python \\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py --cfg=hwio_cfg.py --flat=..\..\Tools\hwio\ARM_ADDRESS_FILE.FLAT
#
#  ===========================================================================
#
#  Copyright (c) 2017,2021 Qualcomm Technologies, Inc. 
#  All rights reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/ClockTargetLib/hwio_cfg.py#7 $
#  $DateTime: 2022/02/09 09:17:48 $
#  $Author: pwbldsvc $
#
#  ===========================================================================

_header = """
#include <HALhwio.h>
#include <Fillmore/Include/msmhwiobase.h>

#define GCC_PROC_CLK_BRANCH_ENA_VOTE         GCC_APCS_CLOCK_BRANCH_ENA_VOTE
#define GCC_PROC_CLK_BRANCH_ENA_VOTE_1       GCC_APCS_CLOCK_BRANCH_ENA_VOTE_1
#define GCC_PROC_CLK_BRANCH_ENA_VOTE_2       GCC_APCS_CLOCK_BRANCH_ENA_VOTE_2
#define GCC_PROC_CLK_PLL_ENA_VOTE            GCC_APCS_PLL_BRANCH_ENA_VOTE

#define GCC_BOOT_CLK_BRANCH_ENA_VOTE         GCC_RPM_CLOCK_BRANCH_ENA_VOTE
#define GCC_BOOT_CLK_BRANCH_ENA_VOTE_1       GCC_RPM_CLOCK_BRANCH_ENA_VOTE_1
#define GCC_BOOT_CLK_BRANCH_ENA_VOTE_2       GCC_RPM_CLOCK_BRANCH_ENA_VOTE_2
#define GCC_BOOT_CLK_PLL_ENA_VOTE            GCC_RPM_PLL_BRANCH_ENA_VOTE
"""


_clock_mods = [
  'AOSS_CC_REG',
  'APSS_CC_APSS_CC_REG',
  'AOSS_CC_PLL0_CM_PLL_LUCID_EVO',
  'AOSS_CC_PLL1_CM_PLL_PONGO_EVO',
  'DISP_CC_DISP_CC_REG',
  'APSS_CC_APSS_CC_REG',
  'APSS_CC_SILVER_CM_PLL_ZONDA_EVO',
  'APSS_CC_GOLD_CM_PLL_ZONDA_EVO',
  'APSS_CC_GOLDPLUS_CM_PLL_ZONDA_EVO',
  'APSS_CC_L3_CM_PLL_ZONDA_EVO',
  'GCC_CLK_CTL_REG',
  'GCC_GPLL0_CM_PLL_LUCID_EVO',
  'GCC_GPLL1_CM_PLL_LUCID_EVO',
  'GCC_GPLL2_CM_PLL_LUCID_EVO',
  'GCC_GPLL3_CM_PLL_TAYCAN_EVO',
  'GCC_GPLL4_CM_PLL_LUCID_EVO',
  'GCC_GPLL5_CM_PLL_LUCID_EVO',
  'GCC_GPLL6_CM_PLL_LUCID_EVO',
  'GCC_GPLL7_CM_PLL_LUCID_EVO',
  'GCC_GPLL8_CM_PLL_LUCID_EVO',
  'GCC_GPLL9_CM_PLL_LUCID_EVO',
  'DISP_CC_PLL0_CM_PLL_LUCID_EVO',
  'DISP_CC_PLL1_CM_PLL_LUCID_EVO',  
  'PHY_REFGEN_0_NORTH_CM_PHY_REFGEN_NXGEN',
  'PHY_REFGEN_SOUTH_CM_PHY_REFGEN_NXGEN',
  'GPUCC_GPU_CC_GPU_CC_GPU_CC_REG',
  'RPMH_ARC_ARC_SW_OVERRIDE',
  'TCSR_TCSR_REGS',
  'LPASS_CORE_GDSC',
  'LPASS_LPASS_CORE_CC_LPASS_CORE_CC_LPASS_CORE_CC_REG',
  'DPCC_DPCC_REG',
  'QFPROM_CORR',
]


# List the modules that contain DCD registers
NOC_modules = [
  'CAM_CC_CAM_CC_REG',
  'VCODEC_VIDEO_CC_VIDEO_CC_VIDEO_CC_REG',
]

# List here the patterns for the DCD regs that are needed
#  (to keep HWIO file smaller)
dcd_regs = ['DCD']

module_filter_includes = {}
for noc in NOC_modules:
  module_filter_includes[noc] = dcd_regs

# ============================================================================
# HWIO_REGISTER_FILES
# ============================================================================

HWIO_REGISTER_FILES = [
  {
    'filename': 'inc/HALclkHWIO.h',
    'modules': _clock_mods + NOC_modules,
    'module-filter-include': module_filter_includes,
    'map-type': 'physical',
    'check-sizes': True,
    'check-for-overlaps': True,
    'header': _header
  },
]

# ============================================================================
# Main
#
# Entry point when invoking this directly.
# ============================================================================

if __name__ == "__main__":
  import sys, os
  from subprocess import call
 
  flat_path = os.path.join('..', '..', 'Tools', 'hwio', 'ARM_ADDRESS_FILE.FLAT')
  if os.name == 'nt':
    hwio_path = r'\\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py'
  else:
    hwio_path = r'/net/ben/vol/eng_asw_labdata_0001/corebsp_labdata_0001/sysdrv/hwio/HWIOGen.py'
 
  call(['python', hwio_path, '--cfg', __file__, '--flat', flat_path] + sys.argv[1:])


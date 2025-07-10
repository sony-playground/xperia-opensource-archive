#!/usr/bin/env python
#===========================================================================
#
#  @file clock_hwio_sdm855.py
#
#  @brief HWIO config for the SDM855 XBL Loader Clock HWIO generation.
#
#  This file can be manually invoked with "HWIOGen.py" by calling:
#
#    python \\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py --cfg=clock_hwio_sdm855.py --flat=..\..\Tools\hwio\ARM_ADDRESS_FILE.FLAT
#
#  ===========================================================================
#
#  Copyright (c) 2018,2021 Qualcomm Technologies, Inc. 
#  All rights reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Waipio/Library/HALclkLib/HALclkHWIO.py#2 $
#  $DateTime: 2021/02/08 09:44:49 $
#  $Author: pwbldsvc $
#
#  ===========================================================================

_header = """
#include "../../Include/msmhwiobase.h"

#define GCC_PROC_CLK_BRANCH_ENA_VOTE    GCC_APCS_CLOCK_BRANCH_ENA_VOTE
#define GCC_PROC_CLK_BRANCH_ENA_VOTE_1  GCC_APCS_CLOCK_BRANCH_ENA_VOTE_1
#define GCC_PROC_CLK_BRANCH_ENA_VOTE_2  GCC_APCS_CLOCK_BRANCH_ENA_VOTE_2
#define GCC_PROC_CLK_PLL_ENA_VOTE       GCC_APCS_PLL_BRANCH_ENA_VOTE
#define GCC_PROC_GDSC_COLLAPSE_ENA_VOTE GCC_APCS_GDSC_COLLAPSE_ENA_VOTE


"""


_clock_mods = [
    'GCC_CLK_CTL_REG',
    'CAM_CC_CAM_CC_REG',
    'CAM_CC_PLL0_CM_PLL_LUCID_EVO',
    'CAM_CC_PLL1_CM_PLL_LUCID_EVO',
    'CAM_CC_PLL2_CM_PLL_RIVIAN_EVO',
    'CAM_CC_PLL3_CM_PLL_LUCID_EVO',
    'CAM_CC_PLL4_CM_PLL_LUCID_EVO',
    'CAM_CC_PLL5_CM_PLL_LUCID_EVO',
    'CAM_CC_PLL6_CM_PLL_LUCID_EVO',
    'CAM_CC_PLL7_CM_PLL_LUCID_EVO',
    'CAM_CC_PLL8_CM_PLL_LUCID_EVO',
    'DISP_CC_DISP_CC_REG',
    'DISP_CC_PLL0_CM_PLL_LUCID_EVO',
    'DISP_CC_PLL1_CM_PLL_LUCID_EVO',
    'GPUCC_GPU_CC_GPU_CC_GPU_CC_REG',
    'GPUCC_GPU_CC_PLL0_GPU_CC_PLL0_CM_PLL_LUCID_EVO',
    'GPUCC_GPU_CC_PLL1_GPU_CC_PLL1_CM_PLL_LUCID_EVO',
    'GPUCC_GPU_CC_ACD_GPU_CC_ACD_ACD',
    'VCODEC_VIDEO_CC_PLL1_VIDEO_CC_PLL1_CM_PLL_LUCID_EVO',
    'VCODEC_VIDEO_CC_PLL0_VIDEO_CC_PLL0_CM_PLL_LUCID_EVO',
    'VCODEC_VIDEO_CC',
    'VCODEC_VIDEO_CC_VIDEO_CC_VIDEO_CC_REG',
    'L3_CPUACD',
    'SILVER_CPUACD',
    'GOLD_CPUACD',
    'GOLDPLUS_CPUACD',
    'GOLD_ISENSE_CONTROLLER',
    'GOLD_VOLTAGE_SENSOR',
    'APSS_APM_WRAP',
    'EPSSTOP_EPSS_TOP',
    'EPSSSLOW_CLKDOM0_CD0',
    'EPSSSLOW_CLKDOM1_CD1',
    'EPSSSLOW_CLKDOM2_CD2',
    'EPSSSLOW_CLKDOM3_CD3',
    'APSS_CC_APSS_CC_REG',
    'GCC_GPLL0_CM_PLL_LUCID_EVO',
    'GPUCC_GPU_CC_GPU_CC_GPU_CC_REG',
    'GCC_GPLL9_CM_PLL_LUCID_EVO',
   
   ]

# ============================================================================
# HWIO_REGISTER_FILES
# ============================================================================

HWIO_REGISTER_FILES = [
  {
    'filename': 'HALclkHWIO.h',
    'modules': _clock_mods,
    'map-type': 'physical',
    'check-sizes': True,
    'check-for-overlaps': True,
    'output-offsets': True,
    'output-phys': True,
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
 
  flat_path = '../../Tools/hwio/ARM_ADDRESS_FILE.FLAT'
  if os.name == 'nt':
    hwio_path = r'\\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py'
  else:
    hwio_path = r'/net/ben/vol/eng_asw_labdata_0001/corebsp_labdata_0001/sysdrv/hwio/HWIOGen.py'
 
  call(['python', hwio_path, '--cfg', __file__, '--flat', flat_path] + sys.argv[1:])


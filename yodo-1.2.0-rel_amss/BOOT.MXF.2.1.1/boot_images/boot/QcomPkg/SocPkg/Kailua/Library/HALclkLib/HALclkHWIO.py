#!/usr/bin/env python3
#===========================================================================
#
#  @file HALclkHWIO.py
#
#  @brief HWIO config for the Kailua XBL Core Clock HWIO generation.
#
#  This file can be manually invoked with "HWIOGen.py" by calling:
#
#    python \\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py --cfg=HALclkHWIO.py --flat=..\..\Tools\hwio\ARM_ADDRESS_FILE.FLAT
#
#  ===========================================================================
#
#  Copyright (c) 2022 Qualcomm Technologies, Inc. 
#  All rights reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: 
#  $DateTime:
#  $Author:
#
#  ===========================================================================

_header = """

#include "../../Include/msmhwiobase.h"

#define GCC_PROC_CLK_BRANCH_ENA_VOTE    GCC_APCS_CLOCK_BRANCH_ENA_VOTE
#define GCC_PROC_CLK_BRANCH_ENA_VOTE_1  GCC_APCS_CLOCK_BRANCH_ENA_VOTE_1
#define GCC_PROC_CLK_BRANCH_ENA_VOTE_2  GCC_APCS_CLOCK_BRANCH_ENA_VOTE_2
#define GCC_PROC_CLK_PLL_ENA_VOTE       GCC_APCS_PLL_BRANCH_ENA_VOTE
#define GCC_PROC_GDSC_COLLAPSE_ENA_VOTE GCC_APCS_GDSC_BRANCH_ENA_VOTE

"""

_clock_mods = [
    'GCC_CLK_CTL.*_REG',
    'CAM_CC_CAM_CC.*_REG',
    'DISP_CC_DISP_CC.*_REG',
    'GPUCC_GPU_CC.*_REG',
    'APSS_CC_APSS_CC.*_REG',
    'VCODEC_VIDEO_CC.*_REG',
    'GCC_GPLL.*',
    'CAM_CC_PLL.*',
    'DISP_CC_PLL.*',
    'GPUCC_GPU_CC_PLL.*',
    'VCODEC_VIDEO_CC_PLL.*',

    'EPSSTOP_EPSS_TOP',
    'EPSSSLOW_CLKDOM.*',
    'TCSR_TCSR_REGS.*',
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


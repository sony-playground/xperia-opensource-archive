#===========================================================================
#
#  @file LimitsHwio.py
#
#  @brief HWIO config for the Cedros HWIO generation.
#
#  This file can be manually invoked with "HWIOGen.py" by calling:
#
#    python \\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py
#      --cfg=lmh_hwio.py
#      --flat=..\..\..\..\..\api\systemdrivers\hwio\sdm855\ARM_ADDRESS_FILE.FLAT
#
#  ===========================================================================
#
#  Copyright (c) 2018, Qualcomm Technologies, Inc.
#  All rights reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/LimitsTargetLib/LimitsHWIO.py#3 $
#  $DateTime: 2021/11/16 03:42:12 $
#  $Author: pwbldsvc $
#
#  ===========================================================================

CHIPSET = 'Kodiak'

# ============================================================================
# HWIO_REGISTER_FILES
# ============================================================================

HWIO_REGISTER_FILES = [
  {
    'filename': 'LimitsHWIO.h',
    'modules': [
      'SECURITY_CONTROL_CORE',
      'GPU_ISENSE_CONTROLLER',
      'GPU_GMU_CX_BLK_DEC0',
      'GPU_GMU_GX_BLK_DEC0',
      'GPUCC_GPU_CC_GPU_CC_GPU_CC_REG',
    ],
    'module-filter-include': {
      'SECURITY_CONTROL_CORE':['CORR_PTE_ROW0_MSB',
                               'CORR_PTE_ROW2_LSB',
                               'CORR_PTE_ROW2_MSB',
                               'CORR_PTE_ROW3_LSB',
                               'CORR_PTE_ROW1_MSB',
                               'CORR_QC_SPARE_REGn_MSB'],
      'GPU_GMU_CX_BLK_DEC0':['GMU_SPTPRAC_PWR_CLK_STATUS',
                             'GMU_ISENSE_CTRL',
                             'KMD_LM_HANDSHAKE'],
      'GPU_ISENSE_CONTROLLER':['DECIMAL_ALIGN',
                               'SENSOR_PARAM_CORE_i',
                               'SW_OV_FUSE',
                               'ENDPOINT_CALIBRATION_DONE'],
      'GPU_GMU_GX_BLK_DEC0':['SPTPRAC_POWER_CONTROL'],
      'GPUCC_GPU_CC_GPU_CC_GPU_CC_REG':['GX_BCR',
                                        'GX_DOMAIN_MISC',
                                        'GX_GDSCR',
                                        'GX_GFX3D_CBCR',
                                        'GFX_HM_BHS_STRENGTH_CTRL',
                                        'SPTP_BHS_STRENGTH_CTRL',
                                        'ACD_BCR',
                                        'ACD_MISC'],
    },
    'header': '''#include "msmhwiobase.h"''',
  },
]

# ============================================================================
# Main
#
# Entry point when invoking this directly.
# ============================================================================

if __name__ == "__main__":

  from subprocess import Popen

  hwiogen = Popen([
      'python',
      r'\\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py',
      '--cfg=LimitsHwio.py',
      r"--flat=../../Tools/hwio/ARM_ADDRESS_FILE.FLAT"], shell=True)

  hwiogen.wait()


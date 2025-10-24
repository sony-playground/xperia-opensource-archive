#==============================================================================
#    Copyright (c) 2020 QUALCOMM Technologies Incorporated
#    All Rights Reserved.  Qualcomm Confidential and Proprietary.
#==============================================================================
#
#  HWIOGen.py --cfg=pcie_hwio.py --flat=/path/to/ARM_ADDRESS_FILE.FLAT
#

HWIO_REGISTER_FILES = [
  {
    'filename': 'pcie_hostrc_hwio.h',
    'modules': [
      'PCIE_GEN3X1_.*',
      'PCIE_GEN3X2_.*',
    ],
    'module-filter-exclude': {
      'PCIE_GEN3X1_.*': ['_TYPE0_'],
      'PCIE_GEN3X2_.*': ['_TYPE0_'],
    },
    'output-offsets': True,
    'output-fvals': True,
  },
]


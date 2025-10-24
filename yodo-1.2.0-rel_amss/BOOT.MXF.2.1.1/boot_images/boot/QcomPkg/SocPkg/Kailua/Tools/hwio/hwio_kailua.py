#!/usr/bin/env python
#===========================================================================
#
#  @file hwio_kailua.py
#  @brief HWIO config file for the HWIO generation scripts for Kailua.
#
#  This file can be invoked by calling:
#
#    HWIOGen.py --cfg=hwio_kailua.py --flat=ARM_ADDRESS_FILE.FLAT
#
#  ===========================================================================
#
#  Copyright (c) 2017-2021 QUALCOMM Technologies Incorporated.  
#  All Rights Reserved.
#  QUALCOMM Proprietary and Confidential.
#
#  ===========================================================================
#
#
#  ===========================================================================

CHIPSET = 'kailua'

HWIO_EXTRA_BASES = [
  ['AOP_SS_MSG_RAM_START_ADDRESS', 0x0c300000,    0x0],
  ['AOP_SS_MSG_RAM_DRV14',         0x000e0000,    0x0],
  ['AOP_SS_MSG_RAM_DRV15',         0x000f0000,    0x0],
]

# ============================================================================
# HWIO_BASE_FILES
# ============================================================================

HWIO_BASE_FILES = [
  {
    'filename': '../../Include/msmhwiobase.h',
    'bases': ['.*'],
    'modules': ['TSENS*', 'OCIMEM_MPU*'],
    'filter-exclude': [],
    'map-type': 'physical',
    'memories': ['TCM1', 'TME_MBOX_RAM_LOW', 'TME_MBOX_RAM_HIGH', 'AOP_SS_MSG_RAM'],
    'map-filename': '../../Include/msmhwiomap.h',
    'devcfg-filename': '../../Settings/HWIO/core/HWIOBaseMap.c',
    'devcfg-header':
      '#include "Drivers/HWIODxe/DalHWIO.h"',
    'check-sizes': True,
    'check-for-overlaps': False,
  }
]


# ============================================================================
# HWIO_T32VIEW_FILES
# ============================================================================

HWIO_T32VIEW_FILES = [
  {
    'symbol-filename': 'scripts/hwio.cmm',
    'limit-array-size': [ 10, 4 ],
    'per-filename': 'scripts/hwioreg',
    'filter-exclude': ['RESERVED', 'DUMMY']
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

  flat_path = 'ARM_ADDRESS_FILE.FLAT'
  if os.name == 'nt':
    hwio_path = r'\\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py'
  else:
    hwio_path = r'/net/ben/vol/eng_asw_labdata_0001/corebsp_labdata_0001/sysdrv/hwio/HWIOGen.py'

  call(['python', hwio_path, '--cfg', __file__, '--flat', flat_path] + sys.argv[1:])

HWIO_REGISTER_FILES = [
  { u'filename': u'icbcfg_hwio.h',
    u'header': u'#include "../../../Include/msmhwiobase.h"',
    u'module-filter-exclude': { },
    u'module-filter-include': { u'GEM_NOC':         [ u'GLADIATOR0',
                                                     u'GLADIATOR1',
                                                     u'DYNATTR',
                                                     u'PAYLOAD_RED',
                                                     u'POS_CTL',
                                                     u'POS_DBG',
                                                     u'QOSGEN',
                                                     u'SBM'],
                                u'MCCC_MCCC_MSTR': [ u'PERIOD'],
                                u'Q6_NOC': [ u'QOSGEN',u'DYNATTR'],
                                u'GCC_CLK_CTL_REG': [ u'QM',
                                                      u'CBCR',
                                                      u'MMNOC_GDSCR' ],
                                u'CNOC_SERVICE_NETWORK': [ u'GEMNOC_DYNATTR' ],
                                u'LPASS_AG_NOC':    [ u'DYN' ],
                                u'LLCC_BROADCAST_ANDFEAC': [ u'TCM', u'VICTIM' ],
                                u'LLCC_BROADCAST_ORFEAC': [ u'TCM', u'VICTIM' ],
                                u'LLCC_BROADCAST_ANDLLCC_BEAC0': [ u'LOCK'],
                                u'LLCC_BROADCAST_ORLLCC_BEAC0': [ u'LOCK'],
                                u'LLCC_BROADCAST_ANDTRP': [ u'OVERRIDE', u'CFLUSH', u'ALGO', u'SCID'],
                                u'LLCC_BROADCAST_ORTRP': [ u'OVERRIDE', u'CFLUSH', u'ALGO', u'SCID']},
    u'modules': [ u'QM',
                  u'APP_BWMON_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'APP_BWMON_THROTTLE_1_THROTTLE_1_THROTTLE',
                  u'GPU_BWMON_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'GPU_BWMON_THROTTLE_1_THROTTLE_1_THROTTLE',
                  u'CDSP_BWMON_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'CDSP_BWMON_THROTTLE_1_THROTTLE_1_THROTTLE',
                  u'PCIE_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'SNOC_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'GPU_TCU_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'ANOC_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'ANOC_THROTTLE_THROTTLE_1_THROTTLE_1_THROTTLE',
                  u'LPASS_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'WLAN_Q6_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'GEM_NOC',
                  u'MCCC_MCCC_MSTR',
                  u'Q6_NOC',
                  u'GCC_CLK_CTL_REG',
                  u'CNOC_SERVICE_NETWORK',
                  u'LPASS_AG_NOC',
                  u'LLCC_BROADCAST_ANDTRP',
                  u'LLCC_BROADCAST_ORTRP',
                  u'LLCC_BROADCAST_ANDFEAC',
                  u'LLCC_BROADCAST_ORFEAC',
                  u'LLCC_BROADCAST_ANDLLCC_BEAC0',
                  u'LLCC_BROADCAST_ORLLCC_BEAC0' ]},
  { u'filename': u'icbcfg_hwio_target.h',
    u'header': u'#include "../../Include/msmhwiobase.h"',
    u'module-filter-exclude': { },
    u'module-filter-include': { u'LLCC0_LLCC_BEAC0': [u'ADDR_TRANSLATOR_CFG'],
                                u'LLCC1_LLCC_BEAC0': [u'ADDR_TRANSLATOR_CFG']},
    u'modules': [u'LLCC0_LLCC_BEAC0',
                 u'LLCC1_LLCC_BEAC0']},
]

if __name__ == "__main__":
  import sys, os
  from subprocess import call

  flat_path = '../../../Tools/hwio/ARM_ADDRESS_FILE.FLAT'
  if os.name == 'nt':
    hwio_path = r'\\ben\corebsp_labdata_0001\sysdrv\hwio\HWIOGen.py'
  else:
    hwio_path = r'/net/ben/vol/eng_asw_labdata_0001/corebsp_labdata_0001/sysdrv/hwio/HWIOGen.py'

  call(['python', hwio_path, '--cfg', __file__, '--flat', flat_path] + sys.argv[1:])

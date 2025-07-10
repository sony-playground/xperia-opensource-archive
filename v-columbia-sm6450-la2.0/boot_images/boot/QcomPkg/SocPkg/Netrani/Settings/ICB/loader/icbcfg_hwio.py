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
                                u'GCC_CLK_CTL_REG': [ u'QM',
                                                      u'CBCR',
                                                      u'MMNOC_GDSCR' ],
                                u'MMSS_NOC':        [ u'CAMNOC.*?DYN' ],
                                u'LPASS_AG_NOC':    [ u'DYN' ]},
    u'modules': [ u'QM',
                  u'APP0_BWMON_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'GPU_BWMON_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'GPU_BWMON_THROTTLE_1_THROTTLE_1_THROTTLE',
                  u'CDSP_BWMON_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'CDSP_BWMON_THROTTLE_1_THROTTLE_1_THROTTLE',
                  u'PCIE_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'SNOC_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'WLAN_Q6_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'MODEM_DEMBACK_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'MODEM_DSP_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'ANOC_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'ANOC_THROTTLE_THROTTLE_1_THROTTLE_1_THROTTLE',
                  u'GPU_TCU_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'LPASS_THROTTLE_THROTTLE_0_THROTTLE_0_THROTTLE',
                  u'GEM_NOC',
                  u'MCCC_MCCC_MSTR',
                  u'GCC_CLK_CTL_REG',
                  u'MMSS_NOC',
                  u'LPASS_AG_NOC']},
  { u'filename': u'icbcfg_hwio_target.h',
    u'header': u'#include "../../Include/msmhwiobase.h"',
    u'module-filter-exclude': { },
    u'module-filter-include': { u'MC0_MC_COMMON_ISU': [u'ADDR_TRANSLATOR_CFG'],
                                u'MC1_MC_COMMON_ISU': [u'ADDR_TRANSLATOR_CFG']},
    u'modules': [u'MC0_MC_COMMON_ISU',
                 u'MC1_MC_COMMON_ISU']},
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

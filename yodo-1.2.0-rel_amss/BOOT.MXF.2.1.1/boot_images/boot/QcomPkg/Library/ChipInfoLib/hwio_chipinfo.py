'''
Generator for ChipInfoHWIO.h.

Requires ipcatalog-client to be installed. See go/ipcatclient.
'''

try:
  from ipcat_client.swi import hwio_generate_c_header
except ModuleNotFoundError as e:
  print('ipcat_client is missing. See go/ipcatclient for installation instructions.')
  exit(-1)
from collections import defaultdict, namedtuple
import argparse
import os

Register = namedtuple('Register', ['module', 'register'], defaults=[None,None])

# Registers used by most targets in this warehouse.
# If a target needs a different register as an info source, or doesn't support
# the information being reported by that register, override it as
# described in get_chipset_register_data
DEFAULT_REGISTERS = {
  'QCOM_MFG_ID':          Register('TLMM_REG', 'TLMM_HW_REVISION_NUMBER_0'),
  'JTAG_ID':              Register('TLMM_REG', 'TLMM_HW_REVISION_NUMBER_1'),
  'REVISION_NUMBER':      Register('TLMM_REG', 'TLMM_HW_REVISION_NUMBER_2'),
  'TCSR_SOC_HW_VERSION':  Register('TCSR_TCSR_REGS', 'TCSR_SOC_HW_VERSION'),
  'SERIAL_NUM':           Register('FUSE_CONTROLLER_SW_RANGE4', 'CHIP_UNIQUE_ID_0'),
  'QFPROM_CHIP_ID':       Register('FUSE_CONTROLLER_SW_RANGE4', 'CHIP_UNIQUE_ID_1'),
  'FOUNDRY_ID':           Register('QFPROM_CORR', 'QFPROM_CORR_QC_CONFIG_ROW2_LSB'),
  'SKU_ID':               Register('QFPROM_CORR', 'QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB'),
  'P_CODE':               Register('QFPROM_CORR', 'QFPROM_CORR_FEATURE_CONFIG_ROW6_LSB'),
}


def create_module_filter_includes(regs):
  '''
  Create the module_filter_includes dict for the default registers.
  `regs` is the register map dictionary for this chip, updated with
  module/register overrides. See `get_chipset_register_data`.
  '''
  d = defaultdict(list)
  for module, register in regs.values():
    if module and register:
      d[module].append(register)
  return d


def get_chipset_register_data(chip):
  '''
  Most chips have the same set of registers, so don't track one map
  for each of them. Just use a DefaultDict that maps each chip to the
  common register map instead. Use a copy of DEFAULT_REGISTERS so that
  any chipset-specific overrides below can be applied independently to
  each chip.

  If a chip has a different register name for some piece of
  chip information, override that chip's register map here.
  e.g.::

      register_map = ...
      if chip == 'chip_needing_overrides':
        register_map['sku_id'] = 'new_sku_id_fuse'

  If a register doesn't exist for a specific target and its feature won't
  be supported, map it to an empty `Register()` here. This script will add some dummy
  HWIO macros to NOP out any HWIO accesses for that target. See ``register_macros``.

  Returns:
    tuple(register_map, modules, module_filter_includes)
    for this chip

  '''
  register_map = DEFAULT_REGISTERS.copy()

  if chip == 'pinnacles':
    register_map['QCOM_MFG_ID'] = Register('TLMM_CENTRAL', 'TLMM_HW_REVISION_NUMBER')
    register_map['JTAG_ID'] = Register('TLMM_CENTRAL', 'TLMM_HW_REVISION_NUMBER')
    register_map['REVISION_NUMBER'] = Register('TLMM_CENTRAL', 'TLMM_HW_REVISION_NUMBER')
  if chip == 'aurora':
    print('Stubbing P_CODE because the fuse is split across multiple registers')
    register_map['P_CODE'] = Register()
    register_map['SKU_ID'] = Register('QFPROM_CORR', 'QFPROM_CORR_FEATURE_CONFIG_ROW5_LSB')

  modules = list({data.module for data in register_map.values() if data.module})
  module_filter_includes = create_module_filter_includes(register_map)
  return register_map, modules, module_filter_includes


def parse_args():
  parser = argparse.ArgumentParser(description='ChipInfoHWIO.h generator')
  parser.add_argument('chipset', help='chip name (case insensitive), comma-separated')
  return parser.parse_args()


def get_hwio_header_path(chip):
  script_path = os.path.realpath(__file__)
  out_path = os.path.join(script_path,
      '..', # QcomPkg/Library/ChipInfoLib
      '..', # QcomPkg/Library
      '..', # QcomPkg
      'SocPkg',
      chip.title(),
      'Include',
      'ChipInfoHWIO.h')
  return os.path.realpath(out_path)


def get_dummy_macros(reg, field):
  '''
  Create dummy HWIO macros for registers that aren't
  supported for some target.

  Returns:
    list of HWIO macros for this register, all mapped to 0x0
  '''
  fieldname = '{REG}_{FIELD}'.format(REG=reg, FIELD=field)
  return ['',
    '#define HWIO_{REG}_ADDR    0x0 /* NOP */'.format(REG=reg),
    '#define HWIO_{REG}_RMSK    0x0 /* NOP */'.format(REG=reg),
    '#define HWIO_{FIELD}_BMSK  0x0 /* NOP */'.format(FIELD=fieldname),
    '#define HWIO_{FIELD}_SHFT  0x0 /* NOP */'.format(FIELD=fieldname),
    '#define HWIO_{REG}_IN      0x0 /* NOP */'.format(REG=reg),
    '#define HWIO_{REG}_INM(m)  0x0 /* NOP */'.format(REG=reg),
  ]


def register_macros(register_map):
  fmt = '#define {INFO:36}{REGISTER}'
  macro_name = lambda x: 'CHIPINFO_' + x.upper() + '_REG'
  macros = []
  dummies = []

  for info, reg in register_map.items():
    register = reg.register
    if not register:
      register = 'CHIPINFO_DUMMY_REG_' + info
      dummies += get_dummy_macros(register, info)
    macros.append(fmt.format(
      INFO = macro_name(info.upper()),
      REGISTER = register.upper()
    ))

  # Add dummy macros below the generic ones
  macros += dummies
  return '\n'.join(macros)


def get_header_text(regs):
  return '''
#include "msmhwiobase.h"

{REGISTER_MACROS}
'''.format(REGISTER_MACROS = register_macros(regs))


def create_chipset_config(chip):
  '''
  Create the config dict that gets passed to the HWIO generator.

  Args:
    chip - single string for a single chip alias. e.g. 'waipio_1.0'

  Returns:
    config dict, with all chipset-specific registers, etc. filled in
  '''
  regs, modules, filter_includes = get_chipset_register_data(chip)
  return {
    'exclude-reserved': True,
    'filename': 'ChipInfoHWIO.h',
    'header': get_header_text(regs),
    'module-filter-exclude': {},
    'module-filter-include': filter_includes,
    'modules': modules,
  }


def main():
  args = parse_args()
  chips = args.chipset.lower()
  if ',' in chips:
    chips = chips.split(',')
  else:
    chips = [chips]

  for chip in chips:
    chip = chip.lower()
    config = create_chipset_config(chip)
    out_path = get_hwio_header_path(chip)

    # Convert the chip name to an IPCAT alias.
    # Always use v1.0; the addresses don't change between chip revisions.
    alias = chip + '_1.0'

    print('Generating HWIO for ' + alias)

    # While ipcat_client.swi optionally takes a path, it only checks if
    # the path is writeable after processing the flat file. That leads to
    # wasted time if the HWIO file hasn't been checked out on p4.
    # Instead, just get an in-memory representation and write it
    # ourselves. Open the file ourselves before calling ipcat so that we
    # fail immediately if the file isn't writeable.
    #
    # Open for binary writing since ipcat returns a BytesIO, not a
    #   TextIO like open-for-write normally expects.
    with open(out_path, 'wb') as f:
      with hwio_generate_c_header(chip=alias, config=config) as hwio:
        f.write(hwio.getbuffer())


if __name__ == '__main__':
  main()

'''
Generator for ChipInfoHWIO.h.

Requires ipcatalog-client to be installed. See go/ipcatclient.
'''

from ipcat_client.swi import hwio_generate_c_header
from collections import defaultdict
import argparse
import os

# Registers used by most targets in this warehouse.
# If a target needs a different register as an info source, or doesn't support
# the information being reported by that register, override it as
# described in get_chipset_register_data
DEFAULT_REGISTERS = {
  'QCOM_MFG_ID':          'TLMM_HW_REVISION_NUMBER_0',
  'JTAG_ID':              'TLMM_HW_REVISION_NUMBER_1',
  'REVISION_NUMBER':      'TLMM_HW_REVISION_NUMBER_2',
  'TCSR_SOC_HW_VERSION':  'TCSR_SOC_HW_VERSION',
  'FOUNDRY_ID':           'QFPROM_CORR_QC_CONFIG_ROW2_LSB',
  'SERIAL_NUM':           'CHIP_UNIQUE_ID_0',
  'QFPROM_CHIP_ID':       'CHIP_UNIQUE_ID_1',
  'SKU_ID':               'QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB',
  'P_CODE':               'QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB',
}

# Modules used by most targets in this warehouse.
# If a target puts a register in a different module, add the new
# module as described in get_chipset_register_data
DEFAULT_MODULES = [
  'TLMM_REG',
  'TCSR_TCSR_REGS',
  'QFPROM_CORR',
  'FUSE_CONTROLLER_SW_RANGE4'
]

# Module-level register filter used by most targets in this warehouse.
# If a target puts a register in a different module, or gives the
# register a different name, override this data as described in
# get_chipset_register_data
DEFAULT_MODULE_INCLUDES = {
  'FUSE_CONTROLLER_SW_RANGE4': ['CHIP_UNIQUE_ID_.*'],
  'QFPROM_CORR': [
    'QFPROM_CORR_PTE_ROW1_(MSB|LSB)',
    'QFPROM_CORR_QC_CONFIG_ROW2_LSB',
    'QFPROM_CORR_FEATURE_CONFIG_ROW5_MSB'],
  'TCSR_TCSR_REGS': ['TCSR_SOC_HW_VERSION'],
  'TLMM_REG': ['TLMM_HW_REVISION_NUM.*']
}

register_map = defaultdict(lambda: DEFAULT_REGISTERS.copy())
modules = defaultdict(lambda: DEFAULT_MODULES.copy())
module_filter_includes = defaultdict(lambda: DEFAULT_MODULE_INCLUDES.copy())


def get_chipset_register_data(chip):
  '''
  Most chips have the same set of registers, so don't track one map
  for each of them. Just use a DefaultDict that maps each chip to the
  common register map instead. Use a copy of DEFAULT_REGISTERS so that
  any chipset-specifc overrides below can be applied independently to
  each chip.

  If a chip has a different register name for some piece of
  chip information, override that chip's register map here.
  e.g.::

      register_map = ...
      if chip == 'chip_needing_overrides':
        register_map[chip]['sku_id'] = 'new_sku_id_fuse'

  Also update the modules and module_filter_includes for that chip in
  the same way, if adding a new module/register

  If a register doesn't exist for a specific target and its feature won't
  be supported, map it to `None` here. This script will add some dummy
  HWIO macros to NOP out any HWIO accesses for that target. See ``register_macros``.

  Returns:
    tuple(register_map, modules, module_filter_includes)
    for this chip

  '''
  if chip == 'waipio':
    register_map[chip]['SKU_ID'] = None
    register_map[chip]['P_CODE'] = None
  return register_map[chip], modules[chip], module_filter_includes[chip]


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


def register_macros(mapping):
  fmt = '#define {INFO:36}{REGISTER}'
  macro_name = lambda x: 'CHIPINFO_' + x.upper() + '_REG'
  mappings = []
  dummies = []

  for info, reg in mapping.items():
    if not reg:
      reg = 'CHIPINFO_DUMMY_REG_' + info
      dummies += get_dummy_macros(reg, info)
    mappings.append(fmt.format(
      INFO = macro_name(info.upper()),
      REGISTER = reg.upper()
    ))

  # Add dummy macros below the generic ones
  mappings += dummies
  return '\n'.join(mappings)


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

'''
Generator for PlatformInfoHWIO.h

Requires ipcatalog-client to be installed. See go/ipcatclient.
'''

from ipcat_client.swi import hwio_generate_c_header
import os

import argparse

parser = argparse.ArgumentParser(description='PlatformInfoHWIO.h generator')
parser.add_argument('chipset', help='chip name (case insensitive)')

args = parser.parse_args()

chip = args.chipset.lower()

# PlatformInfoHWIO.h path
script_path = os.path.realpath(__file__)
out_path = os.path.join(script_path,
    '..', # QcomPkg/Library/PlatformInfoLib
    '..', # QcomPkg/Library
    '..', # QcomPkg
    'SocPkg',
    chip.title(),
    'Include',
    'PlatformInfoHWIO.h')
out_path = os.path.realpath(out_path)

# Convert the chip name to an IPCAT alias. Always use v1.0; the addresses don't
# change between chip revisions.
alias = chip + '_1.0'

config = {
    'exclude-reserved': True,
    'filename': 'PlatformInfoHWIO.h',
    'header': '''
#include "msmhwiobase.h"

#define PLATFORMINFO_TCSR_SOC_EMULATION_TYPE    TCSR_SOC_EMULATION_TYPE
''',
    'module-filter-exclude': {},
    'module-filter-include': {
      'TCSR_TCSR_REGS': ['TCSR_SOC_EMULATION_TYPE']
    },
    'modules': [
      'TCSR_TCSR_REGS'
    ]
}

# While ipcat_client.swi optionally takes a path, it only checks if the path
# is writeable after processing the flat file. That leads to wasted time if the
# HWIO file hasn't been checked out on p4. Instead, just get an in-memory
# representation and write it ourselves. Open the file ourselves before calling
# ipcat so that we fail immediately if the file isn't writeable.
# NOTE: open for binary writing since ipcat returns a BytesIO, not a TextIO that
#     open-for-write would expect.
with open(out_path, 'wb') as f:
  with hwio_generate_c_header(chip=alias, config=config) as hwio:
    f.write(hwio.getbuffer())


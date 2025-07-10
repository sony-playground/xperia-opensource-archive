#============================================================================
#
#/** @file nand_preamble.py
#
# GENERAL DESCRIPTION
#   Creates and prepends a nand header/preamble to supplied ELF 
#
# Copyright 2020 by Qualcomm Technologies Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#**/
#
#----------------------------------------------------------------------------
#
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who       what, where, why
# --------   ---       ------------------------------------------------------
# 06/24/20   ck        Initial version
#
#============================================================================
from __future__  import print_function
import os
import sys
import mbn_tools


if len(sys.argv) != 3:
   print("Incorrect Usage: nand_preamble.py <source elf> <destination elf>")
   raise RuntimeError("Usage: nand_preamble.py <source elf> <destination elf>") 


gen_dict = {}
source_full = sys.argv[1]
target_full = sys.argv[2]
source_base = os.path.splitext(str(source_full))[0]
target_base = os.path.splitext(str(source_full))[0]


# Temp files required while constructing preamble
target_hash = target_base + ".hash"
target_hash_hd = target_base + "_hash.hd"
target_phdr_elf = target_base + "_phdr.pbn"
preamble_file_name = target_base + "_preamble.mbn"


# mbn_tools.py values
header_format = 'reg'
image_header_secflag = 'non_secure'


gen_dict['IMAGE_KEY_IMAGE_ID'] = mbn_tools.ImageType.SBL1_IMG
gen_dict['IMAGE_KEY_MBN_TYPE'] = "elf"
gen_dict['IMAGE_KEY_MAX_SIZE_OF_VERIFY_BUFFER'] = 8192
gen_dict['IMAGE_KEY_FLASH_AUTO_DETECT_MAX_PAGE'] = 8192
gen_dict['IMAGE_KEY_FLASH_AUTO_DETECT_MIN_PAGE'] = 2048
gen_dict['IMAGE_KEY_BOOT_SMALL_PREAMBLE'] = 1


# Create hash table 
rv = mbn_tools.pboot_gen_elf([],
                             source_full,
                             target_hash, 
                             elf_out_file_name = target_phdr_elf,
                             secure_type = image_header_secflag)        
if rv:
   raise RuntimeError("Failure in pboot_gen_elf") 


# Create header/preamble
rv = mbn_tools.image_header(os.environ,
                            gen_dict,
                            target_hash,
                            target_hash_hd, 
                            image_header_secflag,
                            elf_file_name = target_phdr_elf,
                            header_format = header_format,
                            requires_preamble = True,
                            preamble_file_name = preamble_file_name)
if rv:
   raise RuntimeError("Failure in image_header") 


# Prepend header/preamble
files_to_cat_in_order = [preamble_file_name, source_full]
mbn_tools.concat_files(target_full, files_to_cat_in_order)


# Append the virtual block
mbn_tools.insert_SBL1_magicCookie(os.environ,
                                  target_full)


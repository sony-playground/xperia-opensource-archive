#============================================================================
#
#/** @file create_trdata.py
#
# GENERAL DESCRIPTION
#   Creates dummy (empty) ddr training mbn header with given inputs
#
# Copyright 2017, 2020 by QUALCOMM Technologies, Incorporated.
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
# 08/20/20   ck        Ported from SBL 4.1
# 06/16/17   et        Initial version

#============================================================================
from __future__ import print_function
import os
import sys
import mbn_tools


if len(sys.argv) != 3:
   print("Incorrect Usage: create_trdata.py <DDR training data base address> <output file path>")
   raise RuntimeError("Usage: create_trdata.py <DDR training data base address> <output file path>")


trdata_address = sys.argv[1]
trdata_file_path = sys.argv[2]

    
header = mbn_tools.Boot_Hdr(init_val = int('0x0',16))
  
header.image_dest_ptr = int(trdata_address,16)
header.image_size = 0
header.image_id = 34
  
header.writePackedData(target = trdata_file_path,
                       write_full_hdr = False)
  

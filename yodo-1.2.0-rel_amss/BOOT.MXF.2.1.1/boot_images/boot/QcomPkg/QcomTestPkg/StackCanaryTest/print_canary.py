#=============================================================================
#  @file print_canary.py
#  Generate canary_values.cmm to print canary values per module
#
#  Copyright (c) 2016 Qualcomm Technologies, Inc.  All Rights Reserved. 
#  Qualcomm Technologies Proprietary and Confidential.
#
#=============================================================================
#                              EDIT HISTORY
#
#
# when       who     what, where, why
# 
# --------   ---     ---------------------------------------------------------
# 05/10/16   vk      Initial Revision
#=============================================================================

from sys import argv
import re

script, input_file = argv

out_file = 'canary_values.cmm'

out=open (out_file, 'w')
with open (input_file, 'r') as fin:
  for line in fin.readlines():
    search = re.search("D\:([A-Z0-9]*)--", line)
    if search:
      print search.group(1)
      out.write("d.v %quad 0x" + search.group(1) + "++0x7\n");

fin.close()
out.close()

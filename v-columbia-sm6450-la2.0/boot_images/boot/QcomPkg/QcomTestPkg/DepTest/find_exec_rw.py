#=============================================================================
#  @file find_exec_rw.py
#  Parser for T32 mmu.list.pt output text file to find executable
#  and writable pages
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
# 08/18/16   vk      New t32 output format
# 05/10/16   vk      Initial Revision
#=============================================================================

from sys import argv

script, input_file = argv

out_file = 'dep_violations.txt'

out=open (out_file, 'w')

with open (input_file, 'r') as fin:
  for line in fin.readlines():
    if ' P:ex' in line and 'readwrite' in line:
      print line
      out.write(line);

fin.close()
out.close()

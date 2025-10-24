#!/usr/bin/env python
#coding = utf-8

#============================================================================
#
# @file xtr_uefi_logs.py
#
# GENERAL DESCRIPTION
#   use this script to extract uefi logs from crashdumps
#
# Copyright 2022 by Qualcomm Technologies, Inc.
#                 All Rights Reserved.
#               QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#                                                                            
#                          EDIT HISTORY FOR MODULE                           
#                                                                            
# This section contains comments describing changes made to the module.      
# Notice that changes are listed in reverse chronological order.             
#                                                                            
# when       who     what, where, why                                        
# --------   ---     --------------------------------------------------------
# 04/20/22   bxr     update the script                                       
# --------   ---     --------------------------------------------------------


from __future__  import print_function
import os
import sys


##############################################################################
# main
##############################################################################
def main():

  #get current path and target name, 
  #get the qcompkg tool path which contains xtr_uefi_logs_common.py 
  cur_path = os.path.dirname(os.path.realpath(__file__))
  if "SocPkg" and "Tools" in cur_path.split(os.sep):
    target = cur_path.split(os.sep)[-2]
    qcompkg_tool_path = os.path.join(cur_path.split("SocPkg")[0], "Tools")
    sys.path.append(qcompkg_tool_path)
    import xtr_uefi_logs_common
  else:
    sys.exit("ERROR. Current path is not correct.")
    
  #step1 input dump path(mandatory), path to save log and infblk addr(optional)
  options = xtr_uefi_logs_common.parser_input()
  if not options:
    sys.exit("ERROR. Please help to check input options.")
    
  #step2 figure out dump path
  dump_path = xtr_uefi_logs_common.check_dump_path(options["dump_path"])
  if not dump_path:
    sys.exit("ERROR. dump_path is empty.")
    
  #step3 figure out path to save log
  uefilog_save_path = xtr_uefi_logs_common.get_path_to_save_log(target, options["path_to_save_log"])
  if not uefilog_save_path:
    sys.exit("ERROR. output save path is empty.")
  
  #step4 extract uefi log
  uefilog_size = xtr_uefi_logs_common.extract_uefilog_and_size(dump_path, cur_path, qcompkg_tool_path,\
                                                               uefilog_save_path, options["infoblk_addr"])
  if uefilog_size:
    print("Done. Uefilog is in %s, uefilog size is %s" % (uefilog_save_path, uefilog_size))
  else:
    sys.exit("ERROR. Get uefilog failed.")
 
  return


if __name__ == "__main__":
  main()
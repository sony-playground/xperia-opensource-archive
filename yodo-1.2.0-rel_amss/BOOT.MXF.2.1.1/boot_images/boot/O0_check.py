#!/usr/bin/env python

#============================================================================
#
# @file rpcheck.py
#
# GENERAL DESCRIPTION
#   check buildoption -O0 in INF/DSC and general report
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
# --------   ---     ----------------------------------------------------------
# 2/28/22    bxr     Initial release
# --------   ---     ----------------------------------------------------------


from __future__  import print_function
import sys
import os
import platform


def buildoption_O0_check(check_path, O0_check_threshold):
  
  #Ensure threshold is greater than or equal to 0
  if (O0_check_threshold < 0):
    sys.exit("ERROR: watchit::buildoption_O0_check: " + \
                    "Threshold supplied is invalid: %d" \
                    % O0_check_threshold)
  
  if platform.system() == "Windows":
    check_path = check_path.replace("/", os.sep, 50)
  else:
    check_path = check_path.replace("\\", os.sep, 50)
  
  
  #check buildoption -O0 in INF and DSC files under input folder recursively
  #count INF/DSC files which contain "-O0" and store them in a file for check
  offending_file_count = 0
  try:
    with open("O0_check_output.txt", 'w') as output_file:
      for (root, dirs, files) in os.walk(check_path):
        for cur_file in files:
          if cur_file.endswith(".inf") or cur_file.endswith(".dsc"):
            buildoption_section_match_flag = 0
            try:
              with open(os.path.join(root, cur_file), "r") as file_for_check:
                buildoption_section_line = ''
                cur_file_path = os.path.join(root, cur_file) + '\n'
                for cur_line in file_for_check:
                  cur_line = cur_line.lstrip()
                  if cur_line.startswith("#"):
                    continue
                  if cur_line.startswith("["):
                    if cur_line.startswith("[BuildOptions"):
                      buildoption_section_match_flag = 1
                      buildoption_section_line = cur_line
                    else:
                      buildoption_section_match_flag = 0
                  elif buildoption_section_match_flag:
                    if (r"-O0") in cur_line:
                      if(len(cur_file_path)):
                        offending_file_count += 1
                        output_file.write("\nFile" + str(offending_file_count) + '\n')
                      output_file.write(cur_file_path)
                      output_file.write(buildoption_section_line)
                      output_file.write(cur_line)
                      #need to store all satisfied buildoption section line for current INF
                      #like [BuildOptions], [BuildOptions.AARCH64] and so on
                      buildoption_section_line = ''
                      #only need to store path once for current INF, reset after used
                      cur_file_path = ''
                file_for_check.close()
            except Exception as err:
              print(err)
              sys.exit("ERROR. Read file %s failed." % (os.path.join(root, cur_file)))
      output_file.close()
  except Exception as error:
    print(error)
    sys.exit("ERROR. Write output file O0_check_output.txt failed.")
  
  #Compare total_errors against threshold
  if (offending_file_count > O0_check_threshold):
    sys.exit("ERROR: watchit::buildoption_O0_check: " + \
             "Total files %d exceeds threshold of %d"\
              % (offending_file_count, O0_check_threshold))

  return offending_file_count


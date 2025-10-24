#!/usr/bin/env python

#============================================================================
#
# @file rpcheck.py
#
# GENERAL DESCRIPTION
#   check reletive path in *.inf and general report
#
# Copyright 2021 by Qualcomm Technologies, Inc.
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
# 10/21/21   bxr     Initial release
# --------   ---     ----------------------------------------------------------

import os
import glob
import sys
import platform
import configparser
from pathlib import PurePath

#################################################################
# relative_path_check(evaluation_dir, rpcheck_threshold)
#################################################################
def relative_path_check(evaluation_dir, rpcheck_threshold):
  relative_path_match_str = ".."

  if platform.system() == "Windows":
    evaluation_dir = evaluation_dir.replace(r"/", os.sep, 100)
  else:
    evaluation_dir = evaluation_dir.replace(r"\\", os.sep, 100)

  #Ensure threshold is greater than or equal to 0
  if (rpcheck_threshold < 0):
    raise NameError("ERROR: watchit::reletive_path_check: " + \
                    "Threshold supplied is invalid: %d" \
                    % rpcheck_threshold)

  out_path = evaluation_dir + os.sep + "reletive_path_check.txt"
  out_file = open(out_path, "w+")
  #print("%s start, dir: %s" % (sys._getframe().f_code.co_name, evaluation_dir))

  offending_file_count = 0
  for (root, dirs, files) in os.walk(evaluation_dir):
    inf_section_match_flag = 0
    header_print_toggle_flag = 1
    current_line = 0
    for current_file in glob.glob(root+ os.sep + "*.inf"):
      with open(current_file, "r") as file:
        for line in file:
          current_line += 1
          if line.startswith('[') and (inf_section_match_flag == 0):
            if ("Sources") in line:
              inf_section_match_flag = 1
              src_tag = line
            else:
              inf_section_match_flag = 0
          elif not(line.startswith('[')):
            if (inf_section_match_flag == 1):
              line = line.strip()
              if (line.startswith('#') == False):
                if relative_path_match_str in (PurePath(line).parts):
                  if (header_print_toggle_flag == 1):
                    header_print_toggle_flag = 0
                    offending_file_count += 1
                    out_file.write("\rFile %d\n\t%s\n" % (offending_file_count, current_file))
                    out_file.write("\t" + src_tag)
                  out_file.write("\tline %d: %s\n" % (current_line, line))
          else:
            inf_section_match_flag = 0
        

  #Compare total_errors against threshold
  if (offending_file_count > rpcheck_threshold):
    raise NameError("ERROR: watchit::reletive_path_check: " + \
                    "Total files %d exceeds threshold of %d"\
                    % (offending_file_count, rpcheck_threshold))

  #print("%s done" % (sys._getframe().f_code.co_name))
  out_file.close() 

  return offending_file_count
  
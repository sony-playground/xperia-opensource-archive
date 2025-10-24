#!/usr/bin/env python
#============================================================================
#
# @file code_format_check.py
#
# GENERAL DESCRIPTION
#   Unified script for checking c code format
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
# 07/29/22   bxr      Initial release
# --------   ---     --------------------------------------------------------


from __future__  import print_function
from optparse import OptionParser
import os
import sys
import time
import subprocess
import re
import platform
import json

#the needed uncrustify version
request_uncrustify_version = "0.73"

#get current directory path
cur_directory_path = os.path.dirname(os.path.realpath(__file__))
if not cur_directory_path.endswith("c_code_format_check"):
  sys.exit("ERROR. Entry dir is not c_code_format_check dir.")

#globals
cur_platform = platform.system()

output_file_path = os.path.join(cur_directory_path, "output_file_" + time.strftime("%Y-%m-%d-%H-%M-%S",time.localtime()) +".txt")

uncrustify_cfg_file_path = os.path.join(cur_directory_path, "uncrustify.cfg")

ARGUMENTS = {"$CHECKINGROOT":cur_directory_path.split("boot_tools")[0]}

#figure out uncrustify tool path,
#On Linux, use default path
#On Windows, intall uncrustify by yourself
if cur_platform == "Linux":
  uncrustify_tool_path = "/pkg/qct/software/uncrustify/uncrustify-0.73/build/uncrustify"
else:
  try:
    uncrustify_tool_path = os.environ["uncrustify"]
  except Exception as err:
    print("ERROR. Please install uncrustify from https://sourceforge.net/projects/uncrustify/files/uncrustify-0.73.0/" + \
          "and set environment. For example,")
    print("On Windows (type at the prompt):")
    print(r"set uncrustify=C:\Qualcomm\uncrustify-0.73.0_f-win64\bin\uncrustify")
    sys.exit(0)


#####################################################################
# delete_file
#####################################################################
def delete_file(file_path):

  if cur_platform == "Linux":
    rm_command = ("rm" + " -rf " + file_path)
  else:
    rm_command = ("del" + " /s " + "/q " + file_path)
  
  try:
    subprocess.run(rm_command, shell=True)
  except Exception as err:
    print(err)
    sys.exit("ERROR. Failed to delete %s." % file_path)

  return


#####################################################################
# json_file_load
#####################################################################
def json_file_load(src_file):
  
  dst_json = ""
  json_load_params = {}
  try:
    #remove comments in json file
    with open(src_file, 'r') as src_json_file:
      for line in src_json_file:
        if line.lstrip().startswith("#"):
          continue
        if len(line.strip()) > 0:
          dst_json += line.split("#")[0].strip()
          dst_json += '\n'
      src_json_file.close()
  except Exception as error:
    print(error)
    sys.exit("ERROR. Failed to read %s" % src_file)
  
  try:
    #read data from json file
    json_load_params = json.loads(dst_json)
  except Exception as error:
    print(error)
    sys.exit("ERROR. Failed to load json params.")
  
  return json_load_params


#####################################################################
# verify_uncrustify_environment
#####################################################################
def verify_uncrustify_environment():

  #check uncrustify version in current system
  #limit uncrustify version to be 0.73 only
  command = uncrustify_tool_path + " --version"
  cur_uncrustify_version = subprocess.run(command, stderr=subprocess.PIPE, stdout=subprocess.PIPE, shell=True).stdout.decode("UTF-8")
  if request_uncrustify_version not in cur_uncrustify_version:
    sys.exit("Warning. The needed uncrustify version is %s, but in your system is %s" % \
             (request_uncrustify_version, cur_uncrustify_version))

  return


#####################################################################
# read_whitelist
#####################################################################
def read_whitelist():

  whitelist = {}
  
  #check if uncrustify_whitelist.json exists
  whitelist_json_path = os.path.join(cur_directory_path, "uncrustify_whitelist.json")
  if not os.path.exists(whitelist_json_path):
    sys.exit("ERROR. %s not found" % (whitelist_json_path))
  
  #figure out uncrustify_whitelist.json
  json_input_params = json_file_load(whitelist_json_path)
  if not json_input_params:
    sys.exit("ERROR. Failed to figure out whitlelist from uncrustify_whitelist.json")
  
  #figure out whitelist from uncrustify_whitelist.json
  #and replace the directory path as absolute path
  checking_folder_list = json_input_params["checkingfolder"]
  if checking_folder_list:
    for i in range(len(checking_folder_list)):
      if "$CHECKINGROOT" in checking_folder_list[i]:
        whitelist[i] = checking_folder_list[i].replace("$CHECKINGROOT/", ARGUMENTS["$CHECKINGROOT"], 1)
        if cur_platform == "Windows":
          whitelist[i] = whitelist[i].replace("/", os.sep, 50)
  else:
    sys.exit("ERROR. whitelist is null.")
  
  return whitelist


#####################################################################
# code_format_fix
#####################################################################
def code_format_fix(check_list, options):

  #delete the old output file from last time and create a new file to store unmatched files
  for file in os.listdir(cur_directory_path):
    if file.endswith(".txt"):
      delete_file(os.path.join(cur_directory_path, file))
  
  output_file = open(output_file_path, 'w')
  
  #read *.c and *.h file from whitelist one by one,
  #if unmatched with uncrustify.cfg, fix the source code or create a new file endswith ".uncrustify".
  fixed_file_num = 0
  for j in range(len(check_list)):
    for (root, dirs, files) in os.walk(check_list[j]):
      for cur_file in files:
        fixed_tag = 0
        default_file_size = 0
        changed_file_size = 0
        if cur_file.endswith('.h') or cur_file.endswith('.c'):
          file_for_check = os.path.join(root, cur_file)
          if options.force_update_code_format:
            #force updating the source code
            default_file_size = os.path.getsize(file_for_check)
            uncrustify_command = (uncrustify_tool_path + " -c " + uncrustify_cfg_file_path + " -l " + "C" + " --no-backup " + " --if-changed " + file_for_check)
            p = subprocess.run(uncrustify_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
            changed_file_size = os.path.getsize(file_for_check)
            if default_file_size != changed_file_size:
              fixed_tag = 1
          else:
            #generate a new fixed file which ends with ".uncrustify"
            uncrustify_command = (uncrustify_tool_path + " -c " + uncrustify_cfg_file_path + " -l " + "C" + " --if-changed " + file_for_check)
            p = subprocess.run(uncrustify_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
            if os.path.exists(file_for_check + ".uncrustify"):
              fixed_tag = 1
          if fixed_tag:
            if not fixed_file_num:
              print("------------------------------------------------------------------------")
            fixed_file_num += 1
            file_num_line = ("File" + str(fixed_file_num) + "\n")
            file_err_line = p.stderr.decode("UTF-8")
            print(file_err_line.strip())
            output_file.write(file_num_line)
            output_file.write(file_err_line)
  if fixed_file_num:
    print("------------------------------------------------------------------------")
  output_file.close()
  
  #if new created output file is not used, delete it
  if not os.path.getsize(output_file_path):
    delete_file(output_file_path)

  return fixed_file_num


#####################################################################
# code_format_check
#####################################################################
def code_format_check(check_list):

  #delete the old output file from last time and create a new file to store unmatched files
  for file in os.listdir(cur_directory_path):
    if file.endswith(".txt"):
      delete_file(os.path.join(cur_directory_path, file))
      
  output_file = open(output_file_path, 'w')
  
  #read *.c and *.h file from whitelist one by one, checking the code format by uncrustify command
  #if unmatched with uncrustify.cfg, print the unmatched file and write to output file.
  unmatched_file_num = 0
  for j in range(len(check_list)):
    for (root, dirs, files) in os.walk(check_list[j]):
      for cur_file in files:
        if cur_file.endswith('.h') or cur_file.endswith('.c'):
          file_for_check = os.path.join(root, cur_file)
          uncrustify_command = (uncrustify_tool_path + " -c " + uncrustify_cfg_file_path + " -l " + "C" + " --check " + file_for_check)
          p = subprocess.run(uncrustify_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
          if p.stderr:
            if not unmatched_file_num:
              print("------------------------------------------------------------------------")
            unmatched_file_num += 1
            file_num_line = ("File" + str(unmatched_file_num) + "\n")
            file_err_line = p.stderr.decode("UTF-8")
            print(file_err_line.strip())
            output_file.write(file_num_line)
            output_file.write(file_err_line)
  if unmatched_file_num:
    print("------------------------------------------------------------------------")
  output_file.close()
  
  #if new created output file is not used, delete it
  if not os.path.getsize(output_file_path):
    delete_file(output_file_path)
  
  return unmatched_file_num


#####################################################################
# main
#####################################################################
def main():

  time_start = time.time()
  parser = OptionParser()

  parser.add_option("--code-check-enable",
                    action="store_true",
                    dest="code_format_check_en",
                    default=False,
                    help="Enable code_format_check action. Ex: --code-check-enable")

  parser.add_option("--force-update",
                    action="store_true",
                    dest="force_update_code_format",
                    default=False,
                    help="Force updating source code format if unmatched with configure file. Ex: --force-update")
  
  (options, args) = parser.parse_args()
  
  #step1 check uncrustify tool path and version
  verify_uncrustify_environment()
  
  #step2 read whitelist from uncrustify_whitelist.json
  whitelist = read_whitelist()
  if not whitelist:
    sys.exit("ERROR. Failed to get whitelist from uncrustify_whitelist.json")
    
  #step3 do code format check or fix
  if (options.code_format_check_en):
    #check code format of *.c/*.h files
    unmatched_file_num = code_format_check(whitelist)
    if unmatched_file_num:
      print("Failed. Unmatched file num:[%d]. Please check output file %s" % (unmatched_file_num, output_file_path))
    else:
      print("Pass. All files match with c code format rules.")
  else:
    #fix code format of *.c/*.h files
    #if input the option --force-update,
    #source code will be forced updating when umatching with configure file
    #if not, the defaut behavior is to create a new file with suffix .uncrustify
    fixed_file_num = code_format_fix(whitelist, options)
    if fixed_file_num:
      print("Warning. Fixed file num:[%d]. Please check output file %s" % (fixed_file_num, output_file_path))
    else:
      print("Pass. All files match with c code format rules.")

  time_end = time.time()
  total_time = time_end - time_start
  print("Running time is ", int(total_time), "secs")
  
  return


if __name__ == "__main__":
  main()


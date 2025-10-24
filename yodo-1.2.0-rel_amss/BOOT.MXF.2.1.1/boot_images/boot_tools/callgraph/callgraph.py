#!/bin/sh
""":"
DIRECTORY=`dirname $0`
exec $DIRECTORY/../../Tools/callgraph/callgraph_utils.py "$0" "$@"  #sets up env before executing this script
" """
#============================================================================
#
# @file callgraph.py
#
# GENERAL DESCRIPTION
#   Target-specific top-level script for analyzing a component build 
#   to generate call and flow graphs using SciTools Understand.
#
# NOTES
#   - should work on all platforms (tested on Windows and Linux)
#   - written in python3 syntax
#
# MAINTAINENCE
#   Any time this script is migrated to a new target, or there is a change
#   in variant names, or certain sourcefile paths change, you will have to 
#   check the section of this file "EVERYTHING BELOW THIS LINE IS TARGET-SPECIFIC"
#
# Copyright (c) 2018, 2022 Qualcomm Technologies, Inc. All rights reserved.
#
#----------------------------------------------------------------------------
#
#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 08/25/22   rama    Moved file to boot_tools
# 09/07/18   msa     Initial file for 8250

import sys
import os
import argparse
import shutil
import time
import json
import platform
from typing import OrderedDict

def remove_json_comments(source_json_file,dest_json_file):
  dest_json = ""
  source_file_handle = open(source_json_file,"r")
  for line in source_file_handle:
    if line.lstrip().startswith("#"):
        dest_json += "\n"
        continue
    temp=line.split()
    if len(temp)==0:
        dest_json += "\n"
        continue
    else:
        dest_json += line.split("#")[0].strip("\n")
        dest_json += "\n"
  source_file_handle.close()
  return dest_json

def get_compiler_name(build_cfg_json_path):

  # COMPILER TOOLCHAIN NAME
  TOOL_NAME_STARTS_WITH = "CLANG"

  #Find Tool Chain from build config
  build_cfg_json = remove_json_comments(build_cfg_json_path, None)
  build_cfg_data = json.loads(build_cfg_json)

  for component in build_cfg_data["Components"]:
    # print(component)
    for process in component["Process"]:
      if process["ToolChain"] and TOOL_NAME_STARTS_WITH in process["ToolChain"]:
        print(process["ToolChain"])
        return process["ToolChain"]

def get_compiler_path(toolchain_cfg_json_path, compiler_name):
  
  toolchain_cfg_json = remove_json_comments(toolchain_cfg_json_path, None)
  toolchain_cfg_data = json.loads(toolchain_cfg_json)

  return toolchain_cfg_data["ToolChain"][compiler_name][platform.system()]["Path"]




def main():

  callgraph_start_time = time.time()
  parser = argparse.ArgumentParser(description='')
  parser.add_argument('-a', '--auto',
      action='store_true',
      help="do not prompt user for input", )
  parser.add_argument('-e', '--verbose',
      action='store_true',
      help="verbose output", )
  parser.add_argument('-t', "--target",
    required=True,
    default=None,
    help="which target to build")
  parser.add_argument('-v', '--variant',
    required=True,
    default=None,
    help="which variant to build for this target. Example: LA", )
  parser.add_argument('-d', '--depth',
    required=False,
    default='3',
    help="depth of the callgraph to be generated, supported values are 1,2,3,4,5,all")

  args = parser.parse_args()

  if(args.target):
    TARGET = args.target
  else: 
    raise Exception(TARGET+' is not a valid target')
  
  sys.path.insert(1, os.path.dirname(os.path.realpath(__file__)))
  import callgraph_utils as u
  import und_static_analysis
  import flatten_config_table
  import draw_function_graph


  AUTOMATED = args.auto
  VERBOSE = args.verbose
  VARIANT = args.variant
  DEPTH = args.depth

  BOOT_DIR = os.path.join(u.BUILD_ROOT_DIR, 'boot')
  TARGET_DIR = os.path.join(BOOT_DIR, 'QcomPkg', 'SocPkg', TARGET)
  OUTPUTPATH = os.path.join(TARGET_DIR, VARIANT)
  RELEASE = 'DEBUG'

  if not os.path.isdir(OUTPUTPATH):
    raise Exception(VARIANT+' is not a valid variant for this target')
  
  # # Delete existing Build folder
  if(os.path.exists(os.path.join(u.BUILD_ROOT_DIR, "Build"))):
    shutil.rmtree(os.path.join(u.BUILD_ROOT_DIR,'Build'))

  # EVERYTHING BELOW THIS LINE IS TARGET-SPECIFIC
  #----------------------------------------------
  PATH_BOOT_CONFIG_H = os.path.join(u.BUILD_ROOT_DIR, 'boot', 'QcomPkg', 'LoaderFramework', 'Include', 'boot_config.h')
  PATH_SM_SBL1_CONFIG_C = os.path.join(u.BUILD_ROOT_DIR, 'boot', 'QcomPkg', 'SocPkg', 'Library', 'XBLLoaderLib', 'SM', 'sbl1_config.c')
  PATH_SM_SBL1_CONFIG_TABLE_FLATTENED = flatten_config_table.main(path_boot_config_h=PATH_BOOT_CONFIG_H,
                                                              path_c_code=PATH_SM_SBL1_CONFIG_C,
                                                              table_name='sbl1_config_table',
                                                              outputdir=u.WORK_DIR,
                                                              outputfilename='sbl1_sm_config_table')
  PATH_SDX_SBL1_CONFIG_C = os.path.join(u.BUILD_ROOT_DIR, 'boot', 'QcomPkg', 'SocPkg', 'Library', 'XBLLoaderLib', 'SDX', 'sbl1_config.c')
  PATH_SDX_SBL1_CONFIG_TABLE_FLATTENED = flatten_config_table.main(path_boot_config_h=PATH_BOOT_CONFIG_H,
                                                              path_c_code=PATH_SDX_SBL1_CONFIG_C,
                                                              table_name='sbl1_config_table',
                                                              outputdir=u.WORK_DIR,
                                                              outputfilename='sbl1_sdx_config_table')
  PATH_CSM_SBL1_CONFIG_C = os.path.join(u.BUILD_ROOT_DIR, 'boot', 'QcomPkg', 'SocPkg', 'Library', 'XBLLoaderLib', 'CSM', 'sbl1_config.c')
  PATH_CSM_SBL1_CONFIG_TABLE_FLATTENED = flatten_config_table.main(path_boot_config_h=PATH_BOOT_CONFIG_H,
                                                              path_c_code=PATH_CSM_SBL1_CONFIG_C,
                                                              table_name='sbl1_config_table',
                                                              outputdir=u.WORK_DIR,
                                                              outputfilename='sbl1_csm_config_table')

  BUILDCONFIG_JSON_PATH = os.path.join(TARGET_DIR, VARIANT, 'buildconfig_internal.json')
  TOOLCHAIN_CONFIG_JSON_PATH = os.path.join(u.BUILD_ROOT_DIR, 'boot', 'toolchainconfig.json')

  compiler_name = get_compiler_name(BUILDCONFIG_JSON_PATH)
  compiler_path = get_compiler_path(TOOLCHAIN_CONFIG_JSON_PATH, compiler_name)

  SBL1_CONFIG_TABLE_FLATTENED_LIST = [PATH_SM_SBL1_CONFIG_TABLE_FLATTENED, PATH_SDX_SBL1_CONFIG_TABLE_FLATTENED, PATH_CSM_SBL1_CONFIG_TABLE_FLATTENED]
      

  print()
  print()     #### XBL_Loader ####

  database = und_static_analysis.main(verbose=VERBOSE,
                target=TARGET, variant=VARIANT, release=RELEASE, component='XBL_S',
                addfile=SBL1_CONFIG_TABLE_FLATTENED_LIST,
                compiler=compiler_path)
                
  draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
                func_name='sbl1_main_ctl', 
                outputpath=OUTPUTPATH, 
                depth=DEPTH)
                
  draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
                func_name='sbl1_sm_config_table', 
                outputpath=OUTPUTPATH, 
                depth=DEPTH)
  
  draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
                func_name='sbl1_sdx_config_table', 
                outputpath=OUTPUTPATH, 
                depth=DEPTH)
  draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
                func_name='sbl1_csm_config_table', 
                outputpath=OUTPUTPATH, 
                depth=DEPTH)
                
  draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
                func_name='boot_config_process_entry', 
                outputpath=OUTPUTPATH)
  
  draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
                func_name='sbl1_hand_control_to_devprog_ddr', 
                outputpath=OUTPUTPATH, 
                depth=DEPTH)
                
  draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
                func_name='sbl1_hand_control_to_devprog_ddr', 
                outputpath=OUTPUTPATH)
                
  print()
  print()     #### XBL_Ramdump ####

  database = und_static_analysis.main(verbose=VERBOSE,
                target=TARGET, variant=VARIANT, release=RELEASE, component='XBL_Ramdump',
                compiler=compiler_path)
                
  draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
                func_name='XBLRamDumpMain', 
                outputpath=OUTPUTPATH, 
                depth=DEPTH)
                
  draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
                func_name='XBLRamDumpMain', 
                outputpath=OUTPUTPATH)
                

  # TODO: currently doing buildex with -C DevPrg_xxx -b cleanall
  #       then buildex with -C DevPrg_xxx causes an instant merge failure 
  #       such that the compiler is never called, so need to fix builex before
  #       uncommenting these lines. Doing the same with -C XBL_xxxxxx also causes
  #       a merge failure but only after all the compiler commands were executed,
  #       so for those components the script will work fine, although not ideal.
  
  # print()
  # print()     #### DevPrg_lite ####

  # database = und_static_analysis.main(verbose=VERBOSE,
  #               target=TARGET, variant=VARIANT, release=RELEASE, component='XBL_S_DEVPRG_NS',
  #               compiler=compiler_path)
                
  # draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
  #               func_name='sbl1_hand_control_to_devprog_ddr', 
  #               outputpath=OUTPUTPATH, 
  #               depth=DEPTH)
                
  # draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
  #               func_name='sbl1_hand_control_to_devprog_ddr', 
  #               outputpath=OUTPUTPATH)
                
  # print()
  # print()     #### DevPrg_ddr ####

  # database = und_static_analysis.main(verbose=VERBOSE,
  #               target=TARGET, variant=VARIANT, release=RELEASE, component='DevPrg_ddr'
  #               compiler=compiler_path)
                
  # draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
  #               func_name='boot_hand_control_to_deviceprogrammer_ddr_main', 
  #               outputpath=OUTPUTPATH, 
  #               depth=DEPTH)
                
  # draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
  #               func_name='boot_hand_control_to_deviceprogrammer_ddr_main', 
  #               outputpath=OUTPUTPATH)

  # Cleanup Build folder once done
  # if(os.path.exists(os.path.join(u.BUILD_ROOT_DIR, "Build"))):
  #   shutil.rmtree(os.path.join(u.BUILD_ROOT_DIR,'Build'))

  callgraph_end_time = time.time()

  callgraph_delta = callgraph_end_time - callgraph_start_time
  minutes = callgraph_delta//60
  seconds = callgraph_delta - 60*minutes
  print("Callgraph completed successfully in {}:{}mins".format(int(minutes),int(seconds)))




if __name__ == "__main__":
  main()


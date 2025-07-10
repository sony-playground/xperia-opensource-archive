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
# Copyright (c) 2018, Qualcomm Technologies, Inc. All rights reserved.
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
# 09/07/18   msa     Initial file for 8250

import sys
import os
import argparse

parser = argparse.ArgumentParser(description='')
parser.add_argument('-a', '--auto',
    action='store_true',
    help="do not prompt user for input", )
parser.add_argument('-e', '--verbose',
    action='store_true',
    help="verbose output", )
parser.add_argument('-v', '--variant',
  required=True,
  default=None,
  help="which variant to build for this target. Example: LA", )
args = parser.parse_args()

TARGET_DIR = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(1, os.path.join(os.path.dirname(os.path.dirname(TARGET_DIR)), 'Tools', 'callgraph'))
import callgraph_utils as u
import und_static_analysis
import flatten_config_table
import draw_function_graph

AUTOMATED = args.auto
VERBOSE = args.verbose
VARIANT = args.variant
OUTPUTPATH = os.path.join(TARGET_DIR, VARIANT)
RELEASE = 'DEBUG'

if not os.path.isdir(OUTPUTPATH):
  raise Exception(VARIANT+' is not a valid variant for this target')

# EVERYTHING BELOW THIS LINE IS TARGET-SPECIFIC
#----------------------------------------------
TARGET = 'Lahaina'
PATH_BOOT_SHARED_FUNCTIONS_PRODUCER_C = os.path.join(u.QCOMPKG_DIR,'XBLLoader','boot_shared_functions_producer.c')
PATH_BOOT_CONFIG_H = os.path.join(u.QCOMPKG_DIR, 'XBLLoader', 'boot_config.h')
PATH_SBL1_CONFIG_C = os.path.join(u.QCOMPKG_DIR, 'SocPkg', 'Library', 'XBLLoaderLib', 'sbl1_config.c')
PATH_SBL1_CONFIG_TABLE_FLATTENED = flatten_config_table.main(path_boot_config_h=PATH_BOOT_CONFIG_H,
                                                             path_c_code=PATH_SBL1_CONFIG_C,
                                                             table_name='sbl1_config_table',
                                                             outputdir=u.WORK_DIR)
print()
print()     #### XBL_Loader ####

database = und_static_analysis.main(verbose=VERBOSE,
              target=TARGET, variant=VARIANT, release=RELEASE, component='XBL_Loader',
              addfile=PATH_SBL1_CONFIG_TABLE_FLATTENED,
              removefile=PATH_BOOT_SHARED_FUNCTIONS_PRODUCER_C)
              
draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
              func_name='sbl1_main_ctl', 
              outputpath=OUTPUTPATH, 
              depth='3')
              
draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
              func_name='sbl1_config_table', 
              outputpath=OUTPUTPATH, 
              depth='3')
              
draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
              func_name='boot_config_process_entry', 
              outputpath=OUTPUTPATH)
              
print()
print()     #### XBL_Ramdump ####

database = und_static_analysis.main(verbose=VERBOSE,
              target=TARGET, variant=VARIANT, release=RELEASE, component='XBL_Ramdump')
              
draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
              func_name='XBLRamDumpMain', 
              outputpath=OUTPUTPATH, 
              depth='3')
              
draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
              func_name='XBLRamDumpMain', 
              outputpath=OUTPUTPATH)
              

# TODO: currently doing buildex with -C DevPrg_xxx -b cleanall
#       then buildex with -C DevPrg_xxx causes an instant merge failure 
#       such that the compiler is never called, so need to fix builex before
#       uncommenting these lines. Doing the same with -C XBL_xxxxxx also causes
#       a merge failure but only after all the compiler commands were executed,
#       so for those components the script will work fine, although not ideal.
#
# print()
# print()     #### DevPrg_lite ####

# database = und_static_analysis.main(verbose=VERBOSE,
              # target=TARGET, variant=VARIANT, release=RELEASE, component='DevPrg_lite')
              
# draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
              # func_name='boot_hand_control_to_deviceprogrammer_lite_main', 
              # outputpath=OUTPUTPATH, 
              # depth='3')
              
# draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
              # func_name='boot_hand_control_to_deviceprogrammer_lite_main', 
              # outputpath=OUTPUTPATH)
              
# print()
# print()     #### DevPrg_ddr ####

# database = und_static_analysis.main(verbose=VERBOSE,
              # target=TARGET, variant=VARIANT, release=RELEASE, component='DevPrg_ddr')
              
# draw_function_graph.drawCallGraph(database=database, automated=AUTOMATED, 
              # func_name='boot_hand_control_to_deviceprogrammer_ddr_main', 
              # outputpath=OUTPUTPATH, 
              # depth='3')
              
# draw_function_graph.drawFlowGraph(database=database, automated=AUTOMATED, 
              # func_name='boot_hand_control_to_deviceprogrammer_ddr_main', 
              # outputpath=OUTPUTPATH)

#!/bin/sh
""":"
exec 'dirname $0'/callgraph_utils.py "$0" "$@"  #sets up env before executing this script
" """
#============================================================================
#
# @file draw_function_graph.py
#
# GENERAL DESCRIPTION
#   Script to generate call and flow graphs from an existing
#   SciTools Understand 5.0 database for any funcion in that
#   database.
#
# NOTES
#   - expects SciTools Understand to already be licensed
#     (if on Linux and it is not licensed, run "callgraph.py")
#     (if on Windows, see QcomPkg/Docs/callflowgraphReadme.txt)
#   - should work on all platforms (tested on Windows and Linux)
#   - can be used as a python import, or run directly on command line
#     using arguments
#   - "understand" only supports python3
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
# 08/25/22   rama    Update for finding compiler from buildconfig
# 09/07/18   msantos written for SciTools Understand 5.0.955 python3 API

import callgraph_utils as u # must import before understand
import understand
import argparse
import platform
import sys
import os
import subprocess
import time
from random import randint

XVFB_PATH = '/pkg/qct/software/Xvfb/bin/Xvfb'
XFNTS_PATH = '/pkg/qct/software/Xvfb/lib/X11/fonts/misc'

#####################################################################
# start a virtual display instance and set up environment
#####################################################################
def start_Xvfb():
  original = os.getenv('DISPLAY')
  display = ':'+str(randint(200000, 2000000000))
  process = subprocess.Popen([XVFB_PATH, '-fp', XFNTS_PATH, display, '-screen', '0', '1920x1080x24'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  time.sleep(0.5)
  if process.poll():
    raise RuntimeError('Failed to start Xvfb')
  os.environ['DISPLAY'] = display
  return (original, process)

#####################################################################
# stop a virtual display process and revert environment
#####################################################################
def stop_Xvfb(original, process):
  if original is None:
    del os.environ['DISPLAY']
  else:
    os.environ['DISPLAY'] = original
  try:
    process.terminate()
  except Exception:
    pass
            
#####################################################################
# generate call tree graph
#####################################################################
def drawCallGraph(database, func_name, outputpath, automated, depth):
  drawGraph(database, func_name, "calltree_", "Calls", outputpath, automated, option='Level='+depth)

#####################################################################
# generate control flow graph
#####################################################################
def drawFlowGraph(database, func_name, outputpath, automated):
  drawGraph(database, func_name, "flowgraph_", "Control Flow", outputpath, automated)

#####################################################################
# generate graph in png format
#####################################################################
def drawGraph(database, func_name, file_prefix, graph_type, outputpath, automated, option=''):
  db = understand.open(database)
  func_list = db.lookup(func_name, "function,method,procedure")
  if len(func_list) == 0:
    raise Exception('Could not find entity with name: "'+func_name+'"')
    
  num = 0
  func = func_list[0]
  if len(func_list) > 1:
    print(u.color.YELLOW+'FOUND '+str(len(func_list))+' ENTITIES WITH NAME '+func_name+' :'+u.color.END)
    for func in func_list:
      print('   '+str(num)+'.  '+func.uniquename())
      num += 1
    if automated:
      func = func_list[0]
      print("Defaulting to option 0...")
    else:
      num = int(input(u.color.BOLD+"Enter a number: "+u.color.END), 10)
      if num < len(func_list):
        func = func_list[num]
      else:
        func = func_list[0]
        print("Defaulting to option 0...")
        
  if not os.path.isdir(outputpath):
    outputpath = '.'
    print('Output directory '+outputpath+' does not exist. Defaulting to current directory.')
  
  file = os.path.join(outputpath, file_prefix + func.name() + ".png")
  
  if platform.system() != 'Windows':
    (original, process) = start_Xvfb()
  
  try:
    func.draw(graph_type,file,option)
    print(u.color.GREEN+'--- Generated "'+file+'"'+u.color.END)
  except Exception as e:
    print('ERROR: Failed to draw "'+graph_type+'" graph for function "'+func_name+'" from database "'+str(db)+'" to output file "'+file+'"')
    raise e
  finally:
    if platform.system() != 'Windows':
      stop_Xvfb(original, process)

#####################################################################
# entry function when invoked from command line
#####################################################################
if __name__ == "__main__":
  parser = argparse.ArgumentParser(description='')
  parser.add_argument('-d', '--database',
    required=True,
    help="path to SciTools Understand database. Example: -d /usr/name/und.udb", )
  parser.add_argument('-o', '--outputpath',
    default='.',
    help="path to save output files. Example: -o /usr/name/output", )
  parser.add_argument('-f', '--flow',
    default=None,
    help="names of functions to generate control flow graphs. Example: -f sbl1_main_ctl,boot_config_process_entry", )
  parser.add_argument('-c', '--call',
    default=None,
    help="names of functions to generate call graphs. Example: -c sbl1_main_ctl,boot_config_process_entry", )
  parser.add_argument('-p', '--depth',
    default='3',
    help="how many levels deep to show calls in call graphs",
    choices=['1', '2', '3', '4', '5', 'all'], )
  args = parser.parse_args()
  if args.flow:
    for func_name in args.flow.split(','):
      drawFlowGraph(args.database, func_name, args.outputpath, False)
  if args.call:
    for func_name in args.call.split(','):
      drawCallGraph(args.database, func_name, args.outputpath, False, 
                    args.depth if args.depth != 'all' else 'All Levels')

#============================================================================
#
# @file und_static_analysis.py
#
# GENERAL DESCRIPTION
#   Script use SciTools Understand 5.0 to statically analyze a 
#   single component (i.e. XBL_Loader) boot.xf build 
#
# NOTES
#   - On Windows, expects SciTools to already be installed and licensed.
#     (Open Understand.exe, go to Help, Legacy Licensing, Add a License,
#      Specify License Server, Server Name: license-wan-21-sd1 or license-wan-21-sd2, 
#      Port: 9000)
#   - should work on all platforms (tested on Windows and Linux)
#   - written in python3 syntax
#
# MAINTAINENCE
#   - update the variable COMPILER_NAME
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
# 08/25/22   rama    Update for finding compiler from buildconfig
# 09/07/18   msantos written for SciTools Understand 5.0.955

import callgraph_utils as u
import sys
import logging
import os
import platform
import subprocess
import argparse
import re
import time
import stat

LOGGER = logging.getLogger()
LOG_FILE_PATH = ''

# set up platform-dependent global variables
if platform.system() == 'Windows':
  COMPILER_NAME = 'clang.exe'
  BUILDEX_BASE_CMD = ['python', os.path.join(u.BUILD_ROOT_DIR,'boot_tools','spy_buildex.py')]
  BUILDSPY_CMD_SCRIPT = os.path.join(u.WORK_DIR,'buildspy_cmd.bat')
  BUILDSPY_COMPILER = os.path.join(u.PATH_SCITOOLS, 'buildspy', 'gccwrapper.exe')
else: # Linux
  COMPILER_NAME = 'clang'
  BUILDEX_BASE_CMD = [os.path.join(u.BUILD_ROOT_DIR,'boot_tools','spy_buildex.py')]
  BUILDSPY_CMD_SCRIPT = os.path.join(u.WORK_DIR,'buildspy_cmd')
  BUILDSPY_COMPILER = os.path.join(u.WORK_DIR,'buildspy_compiler')
  
#####################################################################
# add logger handlers for stdout and file
#####################################################################
def init_logger(verbose, log_file_path):
  LOGGER.handlers = []
  LOGGER.setLevel(logging.DEBUG)
  formatter = logging.Formatter('[%(levelname)8s] %(message)s')
  sh = logging.StreamHandler()
  sh.setLevel(logging.INFO)
  if verbose:
    sh.setLevel(logging.DEBUG)
  else:
    sh.setLevel(logging.INFO)
  sh.setFormatter(formatter)
  LOGGER.addHandler(sh)
  fh = logging.FileHandler(log_file_path, 'w')
  fh.setLevel(logging.DEBUG)
  fh.setFormatter(formatter)
  LOGGER.addHandler(fh)
  
#####################################################################
# prints live stdout from a subprocess and handles error conditions
#####################################################################
def run_command_with_stdout(cmd, verbose, ignore_exit_code, yes_print):
  LOGGER.info('Running Command: '+" ".join(cmd))
  error_string = ''
  last_line = ''
  process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True, shell=(platform.system()=='Windows'))
  try:
    for stdout_line in iter(process.stdout.readline, ""):
      if "error" in stdout_line.lower():
        error_string += stdout_line
        
      stripped_line = re.sub(r'\s+', ' ', stdout_line.strip().replace('\n',''))
      if len(stripped_line) > 0:
        last_line = stripped_line
        
      if not yes_print:
        LOGGER.debug(stripped_line)
        
        if not verbose and len(stripped_line) > 0:
          if len(last_line) <= 45:
            print('{0:<45s}\r'.format(last_line),end='')
          else:
            print('{0:<20s} ... {1:>20s}\r'.format(last_line[:20],last_line[-20:]),end='')
            
      else:
        LOGGER.info(stdout_line.rstrip())
  except KeyboardInterrupt as e:
    print(last_line)
    raise e
    
  if process.wait(): # returned error code
    print(error_string)
    if not ignore_exit_code:
      print('################################')
      print('# ERROR: check log for context #')
      print('################################')
      print('Log file location: '+LOG_FILE_PATH)
      raise subprocess.CalledProcessError(process.wait(), cmd)
  else:
    LOGGER.info('{0:<45s}'.format('Command finished successfully (exit code 0).'))
    
  return last_line
  
#####################################################################
# make a new symbolic link to file even if link already exists
#####################################################################
def force_symlink(file, link, verbose=False):
  if os.path.islink(link):
    os.unlink(link)
  os.symlink(file, link)
  
#####################################################################
# perform builds and set up so buildspy can capture compiler commands
#####################################################################
def buildspy(verbose, database, buildex_comp_cmd, compiler):
  real_toolchain_path = compiler
  real_toolchain_path = real_toolchain_path.strip().replace('\n','')
  real_cc = os.path.join(real_toolchain_path,COMPILER_NAME)
  # real_cc = compiler
  if os.path.isfile(real_cc):
    LOGGER.info('Found compiler path "'+real_cc+'"')
  else:
    raise IOError('spy_buildex.py returned a compiler path that does not exist: "'+real_cc+'"')

  # symlink all toolchain binaries
  all_tools = os.listdir(real_toolchain_path)
  for tool in all_tools:
    real_tool_path = os.path.join(real_toolchain_path, tool)
    fake_tool_path = os.path.join(u.WORK_DIR,tool)
    force_symlink(real_tool_path, fake_tool_path, verbose)

  # create execution script for gccwrapper.bin on linux
  if platform.system() != 'Windows':
    with open(BUILDSPY_COMPILER, 'w') as buildspy_compiler_file:
      buildspy_compiler_file.write('#!/bin/bash\n')
      buildspy_compiler_file.write('export LD_LIBRARY_PATH='+u.PATH_SCITOOLS+'\n')
      buildspy_compiler_file.write('unset QT_PLUGIN_PATH\n')
      buildspy_compiler_file.write(os.path.join(u.PATH_SCITOOLS,'buildspy','gccwrapper.bin')+' "$@"')
      buildspy_compiler_file.close()
      
  # symlink COMPILER_NAME to BUILDSPY_COMPILER
  fake_cc = os.path.join(u.WORK_DIR,COMPILER_NAME)
  force_symlink(BUILDSPY_COMPILER, fake_cc, verbose)
  os.chmod(fake_cc, 0o777)

  # generate buildspy command script (buildspy has problems being executed from subprocess directly)
  buildspy = os.path.join(u.PATH_SCITOOLS,'buildspy','buildspy')
  if platform.system() == 'Windows':
    buildspy = '"'+buildspy+'"' # to deal with spaces in the path
  buildspy_cmd = [buildspy, '-db', database, '-cc', real_cc, '-cmd', '"'+" ".join(buildex_comp_cmd + ['BUILDSPY,'+u.WORK_DIR+os.sep])+'"']
  if os.path.isfile(database):
    os.remove(database)
  with open(BUILDSPY_CMD_SCRIPT, 'w') as buildspy_cmd_file:
    if platform.system() != 'Windows':
      buildspy_cmd_file.write("#!/bin/bash\n")
    buildspy_cmd_file.write(" ".join(buildspy_cmd)+"\n")
    buildspy_cmd_file.close()
    os.chmod(BUILDSPY_CMD_SCRIPT, 0o777)
    LOGGER.debug('starting buildspy')
    LOGGER.info("Buildspy Command: " + " ".join(buildspy_cmd))
    run_command_with_stdout([BUILDSPY_CMD_SCRIPT], verbose, ignore_exit_code=False, yes_print=False)

#####################################################################
# analyze a SciTools Understand database file, and add and/or remove
# files from the database
#####################################################################
def analyze_database(database, verbose, addfile=None, removefile=None):
  LOGGER.debug('starting static analysis')
  und_base_cmd = [os.path.join(u.PATH_SCITOOLS,'und'), '-db', database]
  add_cmd = und_base_cmd
  remove_cmd = und_base_cmd
  analyze_changed_cmd = und_base_cmd + ['analyze', '-changed']
  analyze_cmd = und_base_cmd + ['analyze']
  run_command_with_stdout(analyze_cmd, verbose, ignore_exit_code=False, yes_print=False)

  if addfile:
    for file in addfile:
      add_cmd = add_cmd + ['add', '-file', file]
    run_command_with_stdout(add_cmd, verbose, ignore_exit_code=False, yes_print=False)

  if removefile:
    for file in removefile:
      remove_cmd = und_base_cmd + ['remove', removefile]
    run_command_with_stdout(remove_cmd, verbose, ignore_exit_code=False, yes_print=False)
    # removefile = None
  if addfile or removefile:
    run_command_with_stdout(analyze_changed_cmd, verbose, ignore_exit_code=False, yes_print=False)

#####################################################################
# main function
#####################################################################
def main(verbose,
         target, variant, release, component, 
         addfile=[], removefile=[], compiler=None):
  start_time = time.time()
  if not os.path.isdir(u.WORK_DIR):
    os.makedirs(u.WORK_DIR)
  
  global LOG_FILE_PATH
  LOG_FILE_PATH = os.path.join(u.WORK_DIR,'LOG_'+target+'_'+variant+'_'+component+'.log')
  init_logger(verbose, LOG_FILE_PATH)
  
  database_path = os.path.join(u.WORK_DIR,'DATABASE_'+target+'_'+variant+'_'+component+'.udb')
  
  buildex_full_cmd = BUILDEX_BASE_CMD + ['--target', target, '--variant', variant, '--release', release]
  buildex_comp_cmd = buildex_full_cmd + ['--image', component]
  try:
    buildspy(verbose, database_path, buildex_comp_cmd, compiler)
  finally:
    LOGGER.info('BUILDSPY complete')
    
  analyze_database(database_path, verbose, addfile, removefile)
  
  LOGGER.info('Analysis completed in '+str(int((time.time()-start_time)))+' seconds.')
  print('Log file location: '+LOG_FILE_PATH)
  return database_path

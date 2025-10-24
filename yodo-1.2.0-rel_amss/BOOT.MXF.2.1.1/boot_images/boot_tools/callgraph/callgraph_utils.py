#!/bin/sh
""":"
export LD_LIBRARY_PATH=/pkg/qct/software/scitools/5.0.955/bin/linux64:/pkg/qct/software/scitools/5.0.955_alternate/bin/linux64 #TODO update '5.0.955_alternate' with path from IT
exec /pkg/python/3.2/bin/python3 "$@"
" """
#============================================================================
#
# @file callgraph_utils.py
#
# GENERAL DESCRIPTION
#   Contains all shared setup, checks, and variables for callgraph scripts
#
# NOTES
#   - intended for use as a python import
#   - written in python3 syntax
#   - should work on all platforms (tested on Windows and Linux)
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
# 09/11/18	 msantos added is_admin check for windows
# 09/07/18   msantos Initial creation

import os
import sys
import platform
import subprocess
import getpass
from distutils.spawn import find_executable
import ctypes

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
BUILD_ROOT_DIR = os.path.dirname(os.path.dirname(SCRIPT_DIR))
WORK_DIR = os.path.join(os.path.dirname(BUILD_ROOT_DIR), 'boot_images', 'Build', 'callgraph')
PATH_SCITOOLS = ''

#####################################################################
# 
#####################################################################
def check_path_scitools(path):
  print('Checking path', path)
  if platform.system() == 'Windows':
    if not os.path.isfile(os.path.join(path,'und.exe')) or not os.path.isfile(os.path.join(path,'buildspy','buildspy.exe')) or not os.path.isfile(os.path.join(path, 'buildspy', 'gccwrapper.exe')):
      return False
  else: # Linux
    if not os.path.isfile(os.path.join(path,'und')) or not os.path.isfile(os.path.join(path,'buildspy','buildspy')) or not os.path.isfile(os.path.join(path, 'buildspy', 'gccwrapper.bin')):
      return False
  return True

#####################################################################
# overwrite license configuration file in user home directory (linux only)
#####################################################################
def license_und():
  if platform.system() != 'Windows':
    path_license_conf = os.path.join(os.path.expanduser('~'),'.config','SciTools','License.conf')
    if not os.path.isdir(os.path.dirname(path_license_conf)):
      os.makedirs(os.path.dirname(path_license_conf))
    locallicense_dat = open(path_license_conf, 'w')
    locallicense_dat.write('[license]\nlegacylicensing=true')
    locallicense_dat.close()
  
#####################################################################
# check for admin privileges
#####################################################################
def is_admin():
  try:
    is_admin = (os.getuid() == 0)
  except AttributeError:
    is_admin = ctypes.windll.shell32.IsUserAnAdmin() != 0
  return is_admin
  

# platform specific checks and setup
# ----------------------------------
if platform.system() == 'Windows':
  class color:
    PINK = ''
    BLUE = ''
    GREEN = ''
    YELLOW = ''
    RED = ''
    END = ''
    BOLD = ''
    UNDERLINE = ''
  # check for admin rights on Windows
  if not is_admin():
    raise OSError('MUST RUN AS ADMINISTRATOR')
    
  if find_executable('und'): # try to get the location from search path
    PATH_SCITOOLS = os.path.dirname(find_executable('und'))
  if not check_path_scitools(PATH_SCITOOLS):
    paths = [os.path.join('C:',os.sep,'Users',getpass.getuser(),'Documents','SciTools','bin','pc-win64'),
             os.path.join('C:',os.sep,'Program Files','SciTools','bin','pc-win64'),
             os.path.join('C:',os.sep,'Program Files (x86)','SciTools','bin','pc-win64'),
             os.path.join('C:',os.sep,'Users',getpass.getuser(),'Documents','SciTools','bin','pc-win32'),
             os.path.join('C:',os.sep,'Program Files','SciTools','bin','pc-win32'),
             os.path.join('C:',os.sep,'Program Files (x86)','SciTools','bin','pc-win32')]
    for path in paths: # try other common paths
      PATH_SCITOOLS = path
      if check_path_scitools(PATH_SCITOOLS):
        break
    while not check_path_scitools(PATH_SCITOOLS): # ask user for path
      print('ERROR: Could not find SciTools Understand executables.')
      PATH_SCITOOLS = input('Please enter the installation path (i.e. C:\\Users\\'+getpass.getuser()+'\\Documents\\SciTools\\bin\\pc-win64): ')
      print('You entered: ', PATH_SCITOOLS)
  license_test_process = subprocess.Popen([os.path.join(PATH_SCITOOLS,'und.exe'),'help'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=True)
  result = license_test_process.communicate()
  if result[1]:
    print(result[0])
    print(result[1])
    print('#################################')
    print('# SCITOOLS LICENSE SERVER ERROR #')
    print('#################################')
    print('Server choices: license-wan-21-sd1, license-wan-21-sd2.')
    print('Open understand.exe, go to Help, Legacy Licensing, Add a License,' 
          'Specify License Server, Server Name: <Server>, Port: 9000')
    raise EnvironmentError('Check Unserstand license server')

else: # Linux
  class color:
    PINK = '\033[95m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    END = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
  sys.setdlopenflags(sys.getdlopenflags() | ctypes.RTLD_GLOBAL) # line must execute before importing understand on Linux
  paths = ['/pkg/qct/software/scitools/5.0.955/bin/linux64',
           '/pkg/qct/software/scitools/5.0.955_alternate/bin/linux64'] #TODO: need IT to create alternate
  count = 0
  for path in paths:
    count += 1
    PATH_SCITOOLS = path
    if not check_path_scitools(PATH_SCITOOLS):
      if not count == len(paths):
        continue
      print(color.RED+'################################')
      print('#  ERROR: SciTools not found   #')
      print('################################')
      print('Must use a Qualcomm-networked linux machine to access licensed linux executables'+color.END)
      raise EnvironmentError(PATH_SCITOOLS)
    license_und()
    license_test_process = subprocess.Popen([os.path.join(PATH_SCITOOLS,'und'),'help'], stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True, shell=False)
    result = license_test_process.communicate()
    if result[1]:
      if not count == len(paths):
        continue
      print(result[0])
      print(result[1])
      print(color.RED+'#################################')
      print('# SCITOOLS LICENSE SERVER ERROR #')
      print('#################################'+color.END)
      raise EnvironmentError('Both servers license-wan-21-sd1 and license-wan-21-sd2 are down.')
    else:
      break
  if os.environ.get('LD_LIBRARY_PATH') is None or PATH_SCITOOLS not in os.environ['LD_LIBRARY_PATH'].split(os.pathsep):
   print(color.RED+'##################################')
   print('# ERROR: missing LD_LIBRARY_PATH #')
   print('##################################')
   print('Try running again but like this: ./<filename>.py'+color.END)
   raise EnvironmentError('LD_LIBRARY_PATH')
   
# scitools understand import check
# --------------------------------
sys.path.insert(1,os.path.join(PATH_SCITOOLS,'Python'))
try:
  import understand
except Exception as e:
  print(color.RED+'################################')
  print('#     PYTHON IMPORT ERROR      #')
  print('################################')
  print('Problem importing python module "understand" from '+sys.path[1]+color.END)
  raise e
  

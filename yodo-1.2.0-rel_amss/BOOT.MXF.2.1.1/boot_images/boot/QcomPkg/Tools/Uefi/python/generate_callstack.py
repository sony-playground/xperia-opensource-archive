#!/usr/bin/env python
#coding = utf-8

#============================================================================
#
# @file generate_callstack.py
#
# GENERAL DESCRIPTION
#   use this script to generate call stack from uart log
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
# 05/25/22   bxr     Initial revision                                        
# --------   ---     --------------------------------------------------------

from __future__  import print_function
from optparse import OptionParser
import os
import sys
import re
import subprocess
import platform
import threading
import time
import glob

#*.map and *.dll file flag
MAPPING_MAP_FILE = 1
REPEAT_MAPPING_MAP_FILE = 2
MAPPING_DLL_FILE = 3
REPEAT_MAPPING_DLL_FILE= 4

#"UEFI start" and "Stack frame" flag in uart log
PROCESS_DRIVER_LOADS = 1
PROCESS_STACK_FRAME = 2

#text section flag in map file
TEXT_SECTION = 1

#regex to get target in uart log, Ex: "UEFI Ver      : 6.0.220519.BOOT.MXF.2.1-00247-KAILUA-1"
target_re = re.compile(r'^UEFI\sVer\s+:\s(.+)-([A-Z]+)-[0-9]$')

#regex to get build variant in uart log, Ex: "CONF File     : uefiplatLA.cfg"
variant_re = re.compile(r'^CONF\sFile\s+:\suefiplat([a-zA-Z]+)[.]cfg$')

#regex to get architecture in uart log, Ex: "Build Info    : 64b Jun 29 2022 17:43:31"
architecture_re = re.compile(r'^Build\sInfo\s+:\s(32|64)(.+)$')

#regex to get prod mode in uart log, Ex: "PROD Mode     : FALSE"
prod_mode_re = re.compile(r'^PROD\sMode\s+[:]\s([A-Z]+)$')

#regex to driver name and address in uart log, Ex: "- 0x0A7001000 [24379] Sec.efi"
driver_log_re = re.compile(r'^-\s0x([0-9a-fA-F]+)\s\[\s*(\d+)\]\s(\S*)[.]efi$')

#regex to get stack frame in uart log, Ex: "C519B504"
stack_frame_re = re.compile(r'^([0-9a-fA-F]+)$')

#regex to get text offset in map file, Ex: ".text 0x0 0xe100 # Offset: 0x1000, LMA: 0x0, Alignment: 0x1000"
text_offset_in_map_re = re.compile(r'^[.]text(.)+Offset:\s0x([0-9a-fA-F]+),(.+)$')

#regex to get function name and addr in map file, Ex: "0x0    _QCModuleEntry"
func_in_map_re = re.compile(r'^0x([0-9a-fA-F]+)\s+(\w+)$')

#regex to get text offset in dll file
#Ex: "[ 1] .text             PROGBITS        0000000000000000 001000 00e100 00  AX  0   0 4096"
text_off_in_dll_re = re.compile(r'^\[\s(\d+)\]\s[.]text\s+[A-Z]+\s+[0-9a-f]+\s([0-9a-f]+)\s([0-9a-zA-Z]+\s*)+$')

#regex to get function name and addr in dll file, Ex: "0000000000000154 00000000000000e8 T _ModuleEntryPoint"
func_in_dll_re = re.compile(r'^([0-9a-fA-F]+)\s(([0-9a-fA-F]+\s[A-Za-z])|[^a])\s(\w+)$')

#figure out "Build" directory path for checking *.map/*.dll files
cur_path = os.path.dirname(os.path.realpath(__file__))
if "boot_images" not in cur_path.split(os.sep):
  sys.exit("ERROR. Current path is not correct.")

#globals
cur_platform = platform.system()
build_path = os.path.join(cur_path.split("boot_images")[0], "boot_images", "Build")
driver_table = {}
table_of_closest_driver_to_stack_frame_addr = {}
release_mode = " "
readelf_and_nm_tool_valid_flag = 0
nmdump_path = ""
readelf_path = ""


############################################################################################
#get_closest_driver_to_stack_frame_address
#INPUT: stack frame addr, global variable - driver table and table_of_closest_driver_to_stack_frame_addr
#Ex: 
#stack_frame_addr: 3343046792
#driver_table: {'Sec': 2801799168, 'DxeCore': 3343441920, 'EnvDxe': 3343036416}
#table_of_closest_driver_to_stack_frame_addr is Null defaultly
#INSTRUCTION: store the closest driver name and stack frame offset to every stack frame entry
#Format: {stack_frame_addr: [driver name, (stack frame entry - driver addr)]}
#Ex: {3343046792: ['EnvDxe', 10376]}
############################################################################################
def get_closest_driver_to_stack_frame_address(stack_frame_addr):

  min_addr_offset = (0xFFFFFFFF)
  candidate_driver_name = ''
  closest_driver_to_current_stack_frame_addr = []
  #figure out the closest driver info for each entry in the stack frame,
  #use current stack frame addr to minus driver base addr one by one,
  #when get the minimum address offset, it's the closest driver for current stack frame
  for (driver_name, driver_addr) in driver_table.items():
    if stack_frame_addr >= driver_addr:
      if (stack_frame_addr - driver_addr) < min_addr_offset:
        min_addr_offset = (stack_frame_addr - driver_addr)
        candidate_driver_name = driver_name
  #update the table of closest driver name and addr offset
  if not candidate_driver_name:
    print(hex(stack_frame_addr), "ERROR")
    return False
  closest_driver_to_current_stack_frame_addr.append(candidate_driver_name)
  closest_driver_to_current_stack_frame_addr.append(min_addr_offset)
  table_of_closest_driver_to_stack_frame_addr[stack_frame_addr] = closest_driver_to_current_stack_frame_addr
  
  return


############################################################################################
#populate_driver_table_to_stack_frame_addr
#INPUT: uart log path Ex: <.../boot_images/uefi_log.txt>
#OUTPUT: driver table to every stack frame entry,{stack_frame_addr: [driver name, (stack frame entry - driver addr)]}
#Ex: {3343046792: ['EnvDxe', 10376], 3343041044: ['EnvDxe', 4628], 3343470660: ['DxeCore', 28740], 
#    3343538348: ['DxeCore', 96428], 3343454176: ['DxeCore', 12256], 3343446308: ['DxeCore', 4388],
#    2801887340: ['Sec', 88172], 2801887488: ['Sec', 88320], 2801857320: ['Sec', 58152], 2801817560: ['Sec', 18392],
#    2801807428: ['Sec', 8260], 2801807384: ['Sec', 8216]}
############################################################################################
def populate_driver_table_to_stack_frame_addr(uart_log_path):
  
  global release_mode
  process_state = 0
  #step1: extract target, variant, architecture, release mode, driver name and addr, stack frame addr from uart log
  try:
    with open(uart_log_path, "r") as uartlog:
      for line in uartlog:
        line = line.strip()
        #match uefi log part in uart log, Ex: "UEFI Start     [24372]"
        if line.startswith("UEFI Start"):
          target = ''
          build_variant = ''
          architecture = ''
          prod_mode = ''
          driver_name = ''
          driver_addr = 0
          stack_frame_addr = 0
          entry_list_of_stack_frame = []
          process_state = PROCESS_DRIVER_LOADS
          continue
        if process_state == PROCESS_DRIVER_LOADS:
          #match driver name and addr
          driver_log_match = driver_log_re.search(line)
          if driver_log_match:
            driver_addr = int(driver_log_match.group(1), 16)
            driver_name = driver_log_match.group(3)
            driver_table[driver_name] = driver_addr
          #match the target in uart log
          elif target_re.search(line):
            target_match = target_re.search(line)
            target = (target_match.group(2)).capitalize()
          #match the variant in uart log
          elif variant_re.search(line):
            variant_match = variant_re.search(line)
            build_variant = variant_match.group(1)
          #match the architecture
          elif architecture_re.search(line):
            architecture_match = architecture_re.search(line)
            architecture = architecture_match.group(1)
          #match the release mode
          elif prod_mode_re.search(line):
            prod_mode_match = prod_mode_re.search(line)
            prod_mode = prod_mode_match.group(1)
          #match stack frame line in uart log
          elif line.startswith("Stack frame"):
            process_state = PROCESS_STACK_FRAME
        #match stack frame entry in uart log
        elif process_state == PROCESS_STACK_FRAME:
          stack_frame_match = stack_frame_re.match(line)
          if stack_frame_match:
            stack_frame_addr = int(stack_frame_match.group(1), 16)
            entry_list_of_stack_frame.append(stack_frame_addr)
      uartlog.close()
  except Exception as err:
    print(err)
    sys.exit("ERROR. Read uart log failed.")

  if not driver_table or not entry_list_of_stack_frame or not target \
     or not build_variant or not architecture or not prod_mode:
    sys.exit("ERROR. Failed to construct driver table and stack frame entry list.")

  #check the prod mode, if TRUE, it's release build which is not supported.
  if prod_mode == "FALSE":
    release_mode = "DEBUG"
  elif prod_mode == "TRUE":
    release_mode = "RELEASE"
    sys.exit("ERROR. The build mode is release. Only support debug build for now.")
 
  #step2 figure out which driver has the largest number which is lesser than the stack frame address
  for i in range(len(entry_list_of_stack_frame)):
    stack_frame_addr = entry_list_of_stack_frame[i]
    t = threading.Thread(target = get_closest_driver_to_stack_frame_address, args = (stack_frame_addr,))
    t.start()
    t.join()
  if not table_of_closest_driver_to_stack_frame_addr:
    sys.exit("ERROR. Construct driver table to stack frame addr failed.")
  
  table_of_closest_driver_to_stack_frame_addr["target"] = target
  table_of_closest_driver_to_stack_frame_addr["variant"] = build_variant
  table_of_closest_driver_to_stack_frame_addr["architecture"] = architecture

  return


############################################################################################
#generate_func_table_of_map_file
#INPUT: driver map file path
#EX: <.../boot_images/Build/KailuaLAA/Core/DEBUG_CLANG140LINUX/AARCH64/QcomPkg/Drivers/EnvDxe/EnvDxe/DEBUG/EnvDxe.map>
#OUTPUT: function table {function name: function addr} with text section offset
#EX: {'_QCModuleEntry': 0, 'DxeStage': 68, 'DxeStageOver': 76, 'ReadNextGuid': 92, 'StackCanaryGuidNotFound': 132,
#     'JumpToEntryPoint': 172, 'EntryPoint': 188, '__stack_chk_fail': 216, 'InitStackCanary': 244, 'GetRandomStackCanary': 272,
#     '_DriverUnloadHandler': 280, '_ModuleEntryPoint': 340,...}
############################################################################################
def generate_func_table_of_map_file(driver_map_file_path):

  checking_state = 0
  function_state = 0
  function_table_of_map_file = {}
  try:
    with open(driver_map_file_path, 'r') as map_file:
      for line in map_file:
        function_addr = 0
        function_name = ''
        line = line.strip()
        text_offset_match = text_offset_in_map_re.match(line)
        #match text offset line in map file
        if text_offset_match:
          text_offset = text_offset_match.group(2)
          text_offset = int(text_offset, 16)
          checking_state = TEXT_SECTION
          continue
        #construct table of function name to function address, <function name> + <function addr>
        if checking_state == TEXT_SECTION:
          #match function in map file
          function_math = func_in_map_re.match(line)
          if function_math:
            function_name = function_math.group(2)
            function_addr = int(function_math.group(1), 16)
            if not function_name:
              sys.exit("ERROR. function name or address is NULL.")
            function_table_of_map_file[function_name] = function_addr
        #check if text section ends
        if line.startswith("*(.rodata"):
          break
      map_file.close()
  except Exception as err:
    print(err)
    sys.exit("ERROR. Read %s failed." % driver_map_file_path)
  
  if not function_table_of_map_file:
    sys.exit("ERROR. Not found function infor from map file.")
  function_table_of_map_file["text_offset"] = text_offset

  return function_table_of_map_file


############################################################################################
#generate_func_table_of_dll_file
#INPUT: driver name, driver dll file path
#EX: driver name: EnvDxe
#    dll path: <.../boot_images/Build/KailuaLAA/Core/DEBUG_CLANG140LINUX/AARCH64/QcomPkg/Drivers/EnvDxe/EnvDxe/DEBUG/EnvDxe.map>
#OUTPUT: function table {function name: function addr}
#EX: {'_QCModuleEntry': 0, 'DxeStage': 68, 'DxeStageOver': 76, 'ReadNextGuid': 92, 'StackCanaryGuidNotFound': 132,
#     'JumpToEntryPoint': 172, 'EntryPoint': 188, '__stack_chk_fail': 216, 'InitStackCanary': 244, 'GetRandomStackCanary': 272,
#     '_DriverUnloadHandler': 280, '_ModuleEntryPoint': 340,...}
############################################################################################
def generate_func_table_of_dll_file(driver_name, driver_dll_file_path):

  #create temporary folder "DLL_file" in Build directory to store disassembly files
  #Ex: <.../boot_images/Build/DLL_file>
  disassembly_file_path = build_path + os.sep + "DLL_file"
  if "DLL_file" not in os.listdir(build_path):
    mkdir_command = "mkdir " + build_path + os.sep + "DLL_file"
    try:
      subprocess.run(mkdir_command, shell=True)
    except Exception as err:
      print(err)

  function_table_of_dll_file = {}
  dll_header_file = (disassembly_file_path + os.sep + driver_name + "_header.txt")
  dll_text_file = (disassembly_file_path + os.sep + driver_name + "_text.txt")
  #step1 figure out text section offset value
  try:
    if (driver_name + "_header.txt") not in os.listdir(disassembly_file_path):
      header_info = subprocess.check_output([readelf_path, "-eW", driver_dll_file_path])
      header_file = open(dll_header_file, "w")
      header_file.write(header_info.decode())
    header_file = open(dll_header_file, "r")
    for line in header_file:
      line = line.strip()
      text_offset_match = text_off_in_dll_re.match(line)
      #match text offset line in file,
      #Ex: "[ 1] .text             PROGBITS        0000000000000000 001000 00e100 00  AX  0   0 4096"
      if text_offset_match:
        text_offset = text_offset_match.group(2)
        text_offset = int(text_offset, 16)
        break
    header_file.close()
  except Exception as err:
    print(err)
    sys.exit("ERROR. Read %s failed." % dll_header_file)
  
  #step2 construct table of function name to function address, <function name> + <function addr>
  try:
    if (driver_name + "_text.txt") not in os.listdir(disassembly_file_path): 
      text_info = subprocess.check_output([nmdump_path, "--print-size", "--numeric-sort", driver_dll_file_path])
      text_file = open(dll_text_file, "w")
      text_file.write(text_info.decode())
    text_file = open(dll_text_file, "r")
    for line in text_file:
      function_name = ''
      function_addr = 0
      line = line.strip()
      #match function in dll file
      function_match = func_in_dll_re.match(line)
      if function_match:
        function_name = function_match.group(4)
        function_addr = int(function_match.group(1), 16)
        if not function_name:
          sys.exit("ERROR. function name or address is NULL.")
        function_table_of_dll_file[function_name] = function_addr
    text_file.close()
  except Exception as err:
    print(err)
    sys.exit("ERROR. Read %s failed." % dll_text_file)

  if not function_table_of_dll_file:
    sys.exit("ERROR. Not found function infor from map file.")
  function_table_of_dll_file["text_offset"] = text_offset

  return function_table_of_dll_file


############################################################################################
#reconstruct_call_stack
#INPUT: driver name, driver function table, stack frame offset, mapping state
#Ex: 
#driver name: EnvDxe
#driver function table: {'_QCModuleEntry': 0, 'DxeStage': 68, 'DxeStageOver': 76, 'ReadNextGuid': 92,
#    'StackCanaryGuidNotFound': 132, 'JumpToEntryPoint': 172, 'EntryPoint': 188, '__stack_chk_fail': 216,
#    'InitStackCanary': 244, 'GetRandomStackCanary': 272, '_DriverUnloadHandler': 280, '_ModuleEntryPoint': 340,...}
#stack frame offset(stack fram entry - driver addr): 5380
#mapping state: 1
#OUTPUT PRINT: <stack_frame_addr><driver>::<function> + <offset> or <stack_frame_addr><driver> + <offset>(packed out driver) 
#Ex: 0xa70057d8 Sec :: uefi_thread_entry + 0x50
#    0xc519c504 TzDxeLA + 0x1214
############################################################################################
def reconstruct_call_stack(stack_frame_addr, driver_name, stack_frame_offset, function_dic, mapping_state):

  output = []
  
  #get text section offset value
  if function_dic:
    text_offset = function_dic["text_offset"]

  #check mapping_state,
  #if mapping_state != 0, it means we already collected function information from map or dll file,
  #print <stack_frame_addr><driver>::<function> + <offset>
  #if mapping_state == 0, it means this driver is packed out, no map or dll file,
  #print <stack_frame_addr><driver> + <offset>
  if mapping_state:
    candidate_func_name = ''
    min_addr_offset = (0xFFFFFFFF)
    addr_offset = (stack_frame_offset - text_offset)
    #figure out which function has the largest number which is lesser than the stack frame address
    for (func_name, func_addr) in function_dic.items():
      if addr_offset >= func_addr:
        if (addr_offset - func_addr) < min_addr_offset:
          min_addr_offset = (addr_offset - func_addr)
          candidate_func_name = func_name
    if not candidate_func_name:
      sys.exit("ERROR. Not found func name.")
    output.append(driver_name + "::" + candidate_func_name + "+" + hex(min_addr_offset))
    print(hex(stack_frame_addr), driver_name, "::", candidate_func_name, "+", hex(min_addr_offset))
  else:
    output.append(driver_name + "+" + hex(stack_frame_offset))
    print(hex(stack_frame_addr), driver_name, "+", hex(stack_frame_offset))
  
  return output


############################################################################################
#check_readelf_and_nm_tool
############################################################################################
def check_readelf_and_nm_tool():

  global readelf_and_nm_tool_valid_flag
  global nmdump_path
  global readelf_path
  #check readelf and nmdump version to do validation test
  try:
    nmdump_path = os.environ["nmtool"]
    readelf_path = os.environ["readelf"]
    subprocess.check_output([nmdump_path, "--version"])
    subprocess.check_output([readelf_path, "--version"])
    readelf_and_nm_tool_valid_flag = 1
  except Exception as err:
    readelf_and_nm_tool_valid_flag = 0

  return


############################################################################################
#print_warning
############################################################################################
def print_warning(driver_dll_files):

  print("Warning: can not figure out function name from %s, due to not found readelf and nm tool." % driver_dll_files)
  print("Please set the environment for readelf and nm tool and make sure they are valid. For example,")
  print("On linux (type at the prompt):")
  print(r"export readelf=/pkg/qct/software/llvm/release/arm/14.0.0/tools/bin/arm-readelf")
  print(r"export nmtool=/pkg/qct/software/arm/linaro-toolchain/aarch64-none-elf/4.9-2014.07/bin/aarch64-none-elf-nm")
  print("On Windows (type at the prompt):")
  print(r"set readelf=C:\\Apps\\LLVM\\14.0.0\\tools\\bin\\arm-readelf")
  print(r"set nmtool=C:\\Apps\\LLVM\\14.0.0\\tools\\bin\\arm-nm")
  
  return


############################################################################################
#generate_call_stack
#INPUT: glocal variable - release mode and table of driver to each stack frame
#Ex:
#release mode : debug
#driver table to every stack frame entry,{stack_frame_addr: [driver name, (stack frame entry - driver addr)]}
#  {3343046792: ['EnvDxe', 10376], 3343041044: ['EnvDxe', 4628], 3343470660: ['DxeCore', 28740], 
#   3343538348: ['DxeCore', 96428], 3343454176: ['DxeCore', 12256], 3343446308: ['DxeCore', 4388],
#   2801887340: ['Sec', 88172], 2801887488: ['Sec', 88320], 2801857320: ['Sec', 58152], 2801817560: ['Sec', 18392],
#   2801807428: ['Sec', 8260], 2801807384: ['Sec', 8216]}
#OUTPUT PRINT: <stack_frame_addr><driver>::<function> + <offset> or <stack_frame_addr><driver> + <offset>(packed out driver)
#Ex: 0xa70057d8 Sec :: uefi_thread_entry + 0x50
#    0xc519c504 TzDxeLA + 0x1214
############################################################################################
def generate_call_stack():

  #get target, build variant and architecture
  if table_of_closest_driver_to_stack_frame_addr:
    target = table_of_closest_driver_to_stack_frame_addr["target"]
    table_of_closest_driver_to_stack_frame_addr.pop("target")
    variant = table_of_closest_driver_to_stack_frame_addr["variant"]
    table_of_closest_driver_to_stack_frame_addr.pop("variant")
    architecture = table_of_closest_driver_to_stack_frame_addr["architecture"]
    table_of_closest_driver_to_stack_frame_addr.pop("architecture")
    if architecture == "64":
      arch = "AARCH64"
    elif architecture == "32":
      arch = "ARM"

  #limit driver checking path to be in like "<.../Build/KailuaLAA/Core/DEBUG_CLANG140LINUX/AARCH64/...>"
  for (root, dirs, files) in os.walk(build_path):
    if ("Build" + os.sep + target + variant) in root:
      if (os.sep + "Core" + os.sep + release_mode) and (os.sep + arch) in root:
        driver_checking_path = root
        break

  #step1 construct table of function name to addr
  #first check existing map file, if the map file doesn't exist then check dll file
  disassembly_tool_checking_flag = 0
  driver_table_of_be_used = {}
  driver_dll_list = []
  for stack_frame_addr, stack_frame_offset_table in table_of_closest_driver_to_stack_frame_addr.items():
    driver_name = stack_frame_offset_table[0]
    stack_frame_offset = stack_frame_offset_table[1]
    function_table = {}
    mapping_state = 0
    map_file_list = []
    #match the map file,
    #Ex: <.../boot_images/Build/KailuaLAA/Core/DEBUG_CLANG140LINUX/AARCH64/QcomPkg/Drivers/EnvDxe/EnvDxe/DEBUG/EnvDxe.map>
    driver_map_file = driver_name + ".map"
    if driver_name not in driver_table_of_be_used.keys():
      if cur_platform == "Linux":
        find_command_line = "find " + driver_checking_path + " -path " + "*/DEBUG/*" + " -name " + driver_map_file
      else:
        find_command_line = "where" + " /R " + driver_checking_path + " " + driver_map_file
      map_file_list = subprocess.run(find_command_line, stderr=subprocess.PIPE, stdout=subprocess.PIPE, shell=True).stdout.decode("UTF-8")
      if map_file_list:
        mapping_state = MAPPING_MAP_FILE
        driver_map_file_path = map_file_list.split()[0]
        function_table = generate_func_table_of_map_file(driver_map_file_path)
        driver_table_of_be_used[driver_name] = function_table
        #print("driver_map_file_path = ", driver_map_file_path)
    else:
      mapping_state = REPEAT_MAPPING_MAP_FILE
      function_table = driver_table_of_be_used[driver_name]
    #if not found map file, will go on checking dll file
    if (mapping_state == 0):
      #match the dll file,
      #Ex: <.../boot_images/Build/KailuaLAA/Core/DEBUG_CLANG140LINUX/AARCH64/QcomPkg/Drivers/EnvDxe/EnvDxe/DEBUG/EnvDxe.dll>
      driver_dll_file = driver_name + ".dll"
      if driver_name not in driver_table_of_be_used.keys():
        if cur_platform == "Linux":
          find_command_line = "find " + driver_checking_path + " -path " + "*/DEBUG/*" + " -name " + driver_dll_file
        else:
          find_command_line = "where" + " /R " + driver_checking_path + " " + driver_dll_file
        map_file_list = subprocess.run(find_command_line, stderr=subprocess.PIPE, stdout=subprocess.PIPE, shell=True).stdout.decode("UTF-8")
        if map_file_list:
          if driver_dll_file not in driver_dll_list:
            driver_dll_list.append(driver_dll_file)
          if (readelf_and_nm_tool_valid_flag == 0):
            check_readelf_and_nm_tool()
          if (readelf_and_nm_tool_valid_flag == 1):
            mapping_state = MAPPING_DLL_FILE
            driver_dll_file_path = map_file_list.split()[0]
            function_table = generate_func_table_of_dll_file(driver_name, driver_dll_file_path)
            driver_table_of_be_used[driver_name] = function_table
            #print("driver_dll_file_path = ", driver_dll_file_path)
      else:
        mapping_state = REPEAT_MAPPING_DLL_FILE
        function_table = driver_table_of_be_used[driver_name]
    #step2 reconstruct call stack
    reconstruct_call_stack(stack_frame_addr, driver_name, stack_frame_offset, function_table, mapping_state)

  #delete temporary folder "DLL_file" for disassembly files
  if "DLL_file" in os.listdir(build_path):
    if cur_platform == "Linux":
      rm_command = "rm" + " -rf " + build_path + os.sep + "DLL_file"
    else:
      rm_command = "rd" + " /s " + "/q " + build_path + os.sep + "DLL_file"
    try:
      subprocess.run(rm_command, shell=True)
    except Exception as err:
      print(err)
      sys.exit("ERROR. Delete temporary folder - DLL_file failed.")
  
  return driver_dll_list


############################################################################################
#main
############################################################################################
def main():

  time_start = time.time()
  
  parser = OptionParser()
  
  parser.add_option("-p", "--uart-log-path",
                    action = "store",
                    dest = "uart_log_path",
                    default = "",
                    help = "The uart log path, Ex: ./boot_images/uefi_log.txt")

  (options,args) = parser.parse_args()

  #step1 figure out the input uart log path and prepare environment
  if not options.uart_log_path:
    sys.exit("ERROR. Please input uart log path")

  uart_log_path = options.uart_log_path
  
  #step2 figure out the closest driver name and offset to every stack frame addr in uart log
  #This will update the global variable - table_of_closest_driver_to_stack_frame_addr
  populate_driver_table_to_stack_frame_addr(uart_log_path)
  if not table_of_closest_driver_to_stack_frame_addr:
    sys.exit("ERROR. Not found driver and stack frame info.")
  
  #step3 generate call stack of stack frame entry
  driver_dll_files = generate_call_stack()
  if driver_dll_files and (readelf_and_nm_tool_valid_flag == 0):
    print_warning(driver_dll_files)
  
  time_end = time.time()
  print("whole time = %d s" % int(time_end - time_start))

  return


if __name__ == "__main__":
  main()

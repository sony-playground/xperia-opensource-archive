#!/usr/bin/env python
#coding = utf-8

#============================================================================
#
# @file xtr_uefi_logs_common.py
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
from optparse import OptionParser
import platform
import struct
import os
import sys
import re

initoffset_cmm = "InitOffsets.cmm"
cfg_target_cmm = "configure_target.cmm"
dumpinfo_txt = "dump_info.txt"

##############################################################################
# get_ddr_baseaddr_and_filename
##############################################################################
def get_ddr_baseaddr_and_filename(dump_path, infoblk_base_addr):
  
  ddr_file_info = []
  if dumpinfo_txt in os.listdir(dump_path):
    dumpinfo_path = os.path.join(dump_path, dumpinfo_txt)
    try:
      #read dump_info.txt from dump path
      with open(dumpinfo_path) as dumpinfo_file:
        length = 0
        base_addr = 0
        ddr_base_addr = 0
        for cur_line in dumpinfo_file:
          cur_line = cur_line.strip()
          file_name = cur_line.split()[-1]
          #capture those lines which include the filename of "DDRCS*.BIN and
          #figure out its base addr and length
          if re.match("^(DDRCS)(\S+)(BIN)$", file_name):
            base_addr = int(cur_line.split()[1], 16)
            length = int(cur_line.split()[2], 16)
            infoblk_base_addr = int(infoblk_base_addr, 16)
            #match infoblk base addr with correct ddr region
            if (infoblk_base_addr >= base_addr) and (infoblk_base_addr < (base_addr + length)):
              ddr_base_addr = base_addr
              ddr_file_info.append(file_name)
              ddr_file_info.append(ddr_base_addr)
              break
        dumpinfo_file.close()
        if ddr_base_addr == 0:
          sys.exit("ERROR. infoblk base addr does not exist in current dump bin.")
    except Exception as err:
      print(err)
      sys.exit("ERROR. Read dump_info.txt failed.")
  else:
    sys.exit("ERROR. %s not found in %s" % (dumpinfo_txt, dump_path))
  
  return ddr_file_info


##############################################################################
# get_infoblk_addr_and_arch
##############################################################################
def get_infoblk_addr_and_arch(target_tool_path):
  
  return_list = []
  if target_tool_path:
    if cfg_target_cmm in os.listdir(target_tool_path):
      cfg_target_cmm_path = os.path.join(target_tool_path, cfg_target_cmm)
      try:
        #read configure_target.cmm from "Tools" folder under target folder
        with open(cfg_target_cmm_path, 'r') as cfg_target_cmm_file:
          arch = 0
          UefiRamEntryAddr = 0
          InfoBlkPtrOffset = 0
          #figure out the hardcode info of arch and infoblk addr
          for cur_line in cfg_target_cmm_file:
            cur_line = cur_line.strip()
            if cur_line.startswith("&gUefiRamEntryAddr"):
              UefiRamEntryAddr = cur_line.split("=")[1]
            elif cur_line.startswith("&gInfoBlkPtrOffset"):
              InfoBlkPtrOffset = cur_line.split("=")[1]
            elif cur_line.startswith("&gArch"):
              arch = cur_line.split("=")[1]
          #base addr and arch should never be zero
          if UefiRamEntryAddr and arch:
            infoblk_addr = hex(int(UefiRamEntryAddr, 16) + int(InfoBlkPtrOffset, 16))
            return_list.append(infoblk_addr)
            return_list.append(arch)
          else:
            sys.exit("ERROR. Do not get UefiRamEntryAddr and arch string.")
          cfg_target_cmm_file.close()
      except Exception as err:
        print(err)
        print("ERROR. Read %s failed." % cfg_target_cmm)
    else:
      sys.exit("ERROR. %s not found in current dir %s" %(cfg_target_cmm, target_tool_path))

  return(return_list)


##############################################################################
# get_uartlogbuf_offset
##############################################################################
def get_uartlogbuf_offset(qcompkg_tool_path, arch_string):
  
  uartlogbufptr_offset = 0
  if qcompkg_tool_path:
    if initoffset_cmm in os.listdir(qcompkg_tool_path):
      initoffset_cmm_path = os.path.join(qcompkg_tool_path, initoffset_cmm)
      try:
        #read InitOffsets.cmm from "Tools" folder under QcomPkg folder and 
        #get unarlogbuf offset according to the input arch 32bit/64bit
        with open(initoffset_cmm_path, 'r') as initoffset_cmm_file:
          arch_flag = 0
          for cur_line in initoffset_cmm_file:
            cur_line = cur_line.strip()
            if cur_line.startswith("Set"):
              if arch_string in cur_line:
                arch_flag = 1
                continue
            if arch_flag:
             if cur_line.startswith("&IBlkUartLogBufferPtr"):
               uartlogbufptr_offset = cur_line.split("=")[1]
               break
          initoffset_cmm_file.close()
      except Exception as err:
        print(err)
        print("ERROR. Read %s failed" % (initoffset_cmm))
    else:
      sys.exit("ERROR. %s not found in current dir %s" %(initoffset_cmm, qcompkg_tool_path))

  return uartlogbufptr_offset


##############################################################################
# wrie_uefilog
##############################################################################
def wrie_uefilog(logbuf_info, ddr_base_addr, ddr_dump_file, path_to_save_log):
  
  # read uefilog with its length from binary and store in a new created file
  uefilog_size = 0
  logbufaddr_offset = 0
  if logbuf_info and ddr_base_addr and path_to_save_log:
    logbufaddr = logbuf_info[0]
    logbuflen = logbuf_info[1]
    logbufaddr_offset = (logbufaddr - ddr_base_addr)
    if logbufaddr_offset:
      ddr_dump_file.seek(0x0)
      ddr_dump_file.seek(logbufaddr_offset)
      uart_log = ddr_dump_file.read(logbuflen)
      uefilog_file = open(path_to_save_log, "wb")
      uefilog_file.write(uart_log)
      uefilog_file.close()
      ddr_dump_file.close()
      uefilog_size = os.path.getsize(path_to_save_log)
    else:
      sys.exit("ERROR. Please help to check logbufaddr and ddr_base_addr.")
  
  return uefilog_size


##############################################################################
# get_logbuf_addr_and_length
##############################################################################
def get_logbuf_addr_and_length(ddr_dump_file, arch_string):
  
  logbuf_inf = []
  logbufaddr = 0
  logbuflen = 0
  #get uart log buffer addr and size from its uefi infoblk addr
  if (arch_string == "64"):
    data = ddr_dump_file.read(0x10)
    (logbufaddr, logbuflen) = struct.unpack('qq', data)
  elif (arch_string == "32"):
    data = ddr_dump_file.read(0x8)
    (logbufaddr, logbuflen) = struct.unpack('q', data)
  else:
    sys.exit("ERROR. Input arch_string is not 32 or 64.")
  if logbufaddr and logbuflen:
    logbuf_inf.append(logbufaddr)
    logbuf_inf.append(logbuflen)
  else:
    sys.exit("ERROR. Get no value of logbufaddr and logbuflen.")

  return logbuf_inf


##############################################################################
# get_uefi_log
##############################################################################
def get_uefi_log(uefi_dump_file, infoblk_base_addr, infoblk_uartlogbuf_offset,\
                     arch_string, ddr_base_addr, path_to_save_log):
                     
  uartlogbufptraddr_offset = 0
  if uefi_dump_file and infoblk_base_addr and infoblk_uartlogbuf_offset\
     and arch_string and path_to_save_log and ddr_base_addr:
    #calculate relative uartlogbufptr offset in current ddr region
    uartlogbufptraddr_offset = int(infoblk_base_addr, 16) + int(infoblk_uartlogbuf_offset, 16) -\
                               ddr_base_addr
    if uartlogbufptraddr_offset:
      #open the bin file which contains uefilog and point to the location of uartlogbuf offset
      ddr_binary_file = open(uefi_dump_file, "rb")
      ddr_binary_file.seek(uartlogbufptraddr_offset)
    else:
      sys.exit("ERROR. Please check infoblk_base_addr and infoblk_uartlogbuf_offset.")
    #get logbuf addr and length from ddr region
    logbuf_info = get_logbuf_addr_and_length(ddr_binary_file, arch_string)
    if not logbuf_info:
      sys.exit("ERROR. logbuf addr and lenght are not got.")
    #read from uefilog region in ddr and store uefilog
    uefilog_size = wrie_uefilog(logbuf_info, ddr_base_addr, ddr_binary_file, path_to_save_log)
  else:
    sys.exit("ERROR. Input params are not right.")
    
  return (hex(uefilog_size))


##############################################################################
# parser_input
##############################################################################
def parser_input():
  
  options_dic = {}
  parser = OptionParser()
  
  parser.add_option("-d", "--dump-path",
                    action="store",
                    dest="dump_path",
                    default="",
                    help="The location where you get dump file." +\
                         "Ex: -d C:\ProgramData\Qualcomm\PCAT\AddOns\\\
                          CrashCollection\MemoryDumps\79DA3572\20220309-161116")
  
  parser.add_option("-i", "--infoblk-addr",
                    action="store",
                    dest="infoblk_addr",
                    default="",
                    help="If you have changed Info Blk addr in uefiplat.cfg," +\
                          "please input updated infoblk base addr.")
  
  parser.add_option("-p", "--path-to-save-log",
                    action="store",
                    dest="path_to_save_log",
                    default="",
                    help="Store output uefi log under this path," +\
                         "Ex: -p C:\Temp")
  
  (options,args) = parser.parse_args()
  
  options_dic["dump_path"] = options.dump_path
  options_dic["infoblk_addr"] = options.infoblk_addr
  options_dic["path_to_save_log"] = options.path_to_save_log

  return options_dic


##############################################################################
# check_dump_path
##############################################################################
def check_dump_path(dump_path):
  
  #check the dump_path which is mandatory
  if dump_path:
    if os.sep not in dump_path:
      print("Notice: current platform is", cur_platform, ", please give correct dump path!")
      sys.exit(0)
  else:
    sys.exit("ERROR. Please input dump path.")

  return dump_path


##############################################################################
# get_path_to_save_log
##############################################################################
def get_path_to_save_log(target, path_to_save_log):
  
  #check input path_to_save_log, if it's null, give default value
  cur_platform = platform.system()
  uefilog_file = ("uefilog" + "_" + target + ".txt")
  uefilog_save_path = ""
  if path_to_save_log:
    uefilog_save_path = os.path.join(path_to_save_log, uefilog_file)
  else:
    if cur_platform == "Windows":
      uefilog_save_path = os.path.join(r"C:\Temp", uefilog_file)
    else:
      uefilog_save_path = os.path.join(uefilog_file)
      
  return uefilog_save_path


##############################################################################
# extract_uefilog_and_size
##############################################################################
def extract_uefilog_and_size(dump_path, target_tool_path, qcompkg_tool_path,\
                     path_to_save_log, infoblk_addr):

  #step1 check configure_target.cmm and get arch and uefi infoblk base addr
  infoblk_list = get_infoblk_addr_and_arch(target_tool_path)
  if infoblk_list:
    infoblk_base_addr = infoblk_list[0]
    arch_string = infoblk_list[1]
    if infoblk_addr:
      infoblk_base_addr = infoblk_addr
  else:
    sys.exit("ERROR. Get nothing of arch and uefi infoblk base addr.")
      
  #step2 check InitOffsets.cmm and get uartlogbuf_offset
  uartlogbuf_offset = get_uartlogbuf_offset(qcompkg_tool_path, arch_string)
  if uartlogbuf_offset == 0:
    sys.exit("ERROR. Get no value of uartlogbuf offset.")
  
  #step3 get ddr_base_addr and its file name from dump_info.txt
  ddr_file_info = get_ddr_baseaddr_and_filename(dump_path, infoblk_base_addr)
  if ddr_file_info:
    bin_name = ddr_file_info[0]
    ddr_base_addr = ddr_file_info[1]
  else:
    sys.exit("ERROR. Get nothing of ddr file information.")
  
  #step4 extract dump with all needed input params
  uefi_dump_path = os.path.join(dump_path, bin_name)
  uefilog_size = get_uefi_log(uefi_dump_path, infoblk_base_addr, uartlogbuf_offset,\
                              arch_string, ddr_base_addr, path_to_save_log)
  
  return uefilog_size



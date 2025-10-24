#!/usr/bin/env python

#============================================================================
#
# @file uefi_dtsi_gen.py
#
# GENERAL DESCRIPTION
#   This Script autogenerates dtsi from Uefi Config Files
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
# 06/1/22    rbv     Initial revision                                       
# --------   ---     --------------------------------------------------------

import os
import sys
import filecmp
import tempfile


cfg_node = """FILETYPE {
                size = <FILESIZE>;
                payload = [FILECONTENT];                    
         };
"""

##############################################################################
# Creates hexdump for file passed as param
##############################################################################
def create_hexdump(file):
    file_ptr = open(file, 'r')    
    hexdump = file_ptr.read().encode("utf-8").hex()
    file_ptr.close()
    return hexdump

    
##############################################################################
# Returns filesize for file being passed
##############################################################################
def get_filesize(file):
    filesize = os.path.getsize(file)
    return filesize


##############################################################################
# Compares two files and returns true if same
##############################################################################
def compare_files(file1,file2):
    result = filecmp.cmp(file1,file2)
    return result


##############################################################################
# Returns DT node string out of config file being passed 
##############################################################################
def create_node(cfg_file):   
    myhex = create_hexdump(cfg_file)
    file_length = get_filesize(cfg_file)
    file_name = os.path.basename(cfg_file)
    file_name = file_name.replace(".cfg","")
    node = cfg_node
    node = node.replace("FILETYPE",file_name)
    node = node.replace("FILESIZE",str(file_length))
    node = node.replace("FILECONTENT",myhex)
    return node


##############################################################################
# Returns a dtsi file string for list of nodes passed
##############################################################################
def create_dtsi(node_list,template_file):
    temp_file = open(template_file,'r')
    temp_filebuf = temp_file.read()
    all_nodes = ""
    for each_node in node_list:
        all_nodes = all_nodes + each_node + "         "
    temp_filebuf = temp_filebuf.replace("//CONFIGFILENODE",all_nodes)
    temp_file.close()
    return temp_filebuf


##############################################################################
# Updates dtsi file based on list of cfg_files passed
##############################################################################    
def update_cfg_dtsi(cfg_file_list,template_file,dtsi_file):
    #create a list of dtsi node for list of cfg files
    cfg_node_list = []
    for each_cfg in cfg_file_list:
        cfg_node_list.append(create_node(each_cfg))     
    #create an updated dtsi buffer
    new_dtsi = create_dtsi(cfg_node_list,template_file)
    #store it in temporary file
    temp = tempfile.NamedTemporaryFile()
    temp.write(new_dtsi.encode())
    #compare with exisiting dtsi file 
    no_diff = compare_files(dtsi_file,temp.name)
    if(no_diff):
        return
    else:
        os.chmod(dtsi_file, 0o660)
        file_ptr = open(dtsi_file, 'w')
        file_ptr.write(new_dtsi)
        os.chmod(dtsi_file, 0o440)
        file_ptr.close()
    return
    
##############################################################################
# Main method, parses argument and updates config dtsi
##############################################################################        
def main():
    template_file = sys.argv[1]
    dtsi_file = sys.argv[2]
    cfg_file_list = []
    for i in range(3,len(sys.argv)):
        cfg_file_list.append(sys.argv[i])
    update_cfg_dtsi(cfg_file_list,template_file,dtsi_file)
    return

if __name__=="__main__":    
    main()
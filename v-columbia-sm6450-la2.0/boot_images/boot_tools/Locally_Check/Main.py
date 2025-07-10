#! /usr/bin/env python
# -*- coding: utf-8 -*-
from distutils.command.build import build
import sys, subprocess
import os
import json
import re
import struct
import Non_Ascii_Check
import Copyright_Check

from datetime import datetime

BOOTINT_SERVICE = "bootintsvc"
datetimeid = datetime.now().strftime('%Y%m%d%H%M%S')
FILE_EXTENSION_WHITELIST = ["C","c","s","S","asm","inf","dsc","dec","h"]

# Setting up environment for perforce login
my_env = os.environ.copy()
message = ""
a=""
b=""





def my_popen(cmd):
    #print("Running {}".format(cmd))
    cmd_in = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=my_env, shell=True)
    stdout, stderr = cmd_in.communicate()
    if stderr:
        print(stderr)
        sys.exit(stderr)
    elif stdout:
        return [l.decode('utf-8') for l in stdout.splitlines()]
        
def p4_get_cls(path):
    """
    This function retrieves all the CLs given a path.
    """
    # eventually, this should be changed to the developer's branch path to see their CLs.
    p4cmd = "p4 changes {}/...".format(path)
    output = my_popen(p4cmd)
    return [line.split()[1] for line in output[:-1]] # skip the last one for dev branch creation

def skip_file_by_extension(fname):
    if not fname.rsplit(".",1)[1] in FILE_EXTENSION_WHITELIST:
        #print("skipping file: {}".format(fname))
        return True
    return False
dev_branch = ''     
if __name__ == "__main__":
    
    print("  \nLocal Scan Started....!\n")
    cwd = os.getcwd()
    unique_client = datetimeid
    file_path = os.path.join(cwd,'boot_images/boot/QcomPkg/perforce.txt')
    with open(file_path,"r") as file:
        lines = file.readlines()
        for line in lines:
            if ("$Header" in line):
                dev_path = line.split('//')
                list_of_path = dev_path[1].split('/')[0:5]
                dev_branch += os.path.join('//', os.path.join(*list_of_path))
               
    
    if dev_branch != '' and len(dev_branch)>0:
        
        dev_branch = dev_branch
        unique_client+=dev_branch.rsplit('/',1)[1]
        p4cmd = "p4 --field \"Root={}\" --field \"View+={}/... //{}/{}/...\" client -o {}| p4 client -i".format(cwd,dev_branch,unique_client,dev_branch.split('//')[1],unique_client)
        cl_list = p4_get_cls(dev_branch)
        output = my_popen(p4cmd)
        #print("client updated to {}".format(unique_client))

        p4cmd = "p4 set P4CLIENT={}".format(unique_client)
        output = my_popen(p4cmd)
        #print("client set to {}".format(unique_client))
        
        if (cl_list):
            p4cmd = "p4 sync \"{}/...@>={}\"".format(dev_branch, cl_list[-1])
            
            output = my_popen(p4cmd)
            for file_o in [f for f in output]:
                if not "added as" in file_o:
                    continue            
                file_o = file_o.rsplit("added as ",1)[1]
                if skip_file_by_extension(file_o):
                    continue
                #print(file_o)
                try:
                    file_fp = open(file_o, "rb")
                    file_contents = file_fp.read()                                             
                    a = Non_Ascii_Check.parse_illegal_character(file_o, file_fp)                          
                    b = Copyright_Check.find_copy_right_error(file_o)

                   
                except Exception as err:
                    print(err)            
                file_fp.close()
        else:
            print("No Change List Found...! Please Submit Changes and retry ....!\n")
            sys.exit(0)
    message += a + b

with open(os.path.join(os.getcwd(), 'Copyright_Errors_logs.txt'), 'w') as f:
    f.writelines(message) 

if(message):
    print(f"Scan Completed... Find ERROR logs in path {cwd}/Copyright_Errors_logs.txt\n")
else:
    print("Scan Completed. No ERROR's found\n")
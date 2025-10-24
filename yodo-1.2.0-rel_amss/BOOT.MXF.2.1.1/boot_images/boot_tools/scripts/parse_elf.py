##############################################################
#
##############################################################
#!/usr/bin/python
#============================================================================
#
#/** @file parse_elf.py
#
# GENERAL DESCRIPTION
#   Python Script to find the path in text form of XBL.elf
#     
#
#
#  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
#  Qualcomm Technologies Proprietary and Confidential.
#
#**/
#
#----------------------------------------------------------------------------
#
#  $Change: 34097264 $
#
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who       what, where, why
# --------   ---       ------------------------------------------------------
# 03/27/2020   rakhi       initial version
#============================================================================
import os, shutil, time, logging, importlib, tempfile, subprocess, re, traceback,sys, codecs
from optparse import OptionParser

def get_string(text_file,image_type):
    #Read the elf content
    f=open(text_file, "r")
    contents = f.read()
    contents=contents.replace(" ","").replace("\n","")
    hex_xbl = []       #list contains hex form of dll file name
    hex_load = []      #list contains hex form of starting symbol of dll_path i.e *XBLLoader* or *XBLRamdump*
    k= image_type + ".dll"
    l= "*"+image_type+"*"
    
	#Convert the string into hex
    if sys.version_info < (3, 0):
        k = bytes(k) 
        l=  bytes(l)
    else:
        k = bytes(k, 'utf-8') 
        l=  bytes(l, 'utf-8')
    
    search_xbl=codecs.encode(k, 'hex').decode('ascii')
    search_load=codecs.encode(l, 'hex').decode('ascii')
   
    #Search starting symbol  of dll_path i.e *loader* or *ramdump*
    start_load=contents.find(search_load.upper())
    if (start_load==-1):
        print("File not found...........")
        sys.exit()
	
    start_path = start_load + (len(l))*2
    #Search end point of dll path 
    start_xbl=contents.index(search_xbl.upper(),0,len(contents))
    end_path=start_xbl + (len(k)) * 2
	

    loader_path = []
    for i in range(start_path,end_path):
        loader_path.append(contents[i])
		
		
    final_loader_path=''.join(loader_path)

    #Convert the hex path into string 
    bytes_object = bytearray.fromhex(final_loader_path)
    ascii_string = bytes_object.decode("ASCII")
	
	
    return ascii_string

if __name__ == "__main__":
	argparser = OptionParser(usage = 'parse_elf.py -f textfile -o res_file -i image_type', version='%prog 1.0')
	argparser.add_option("-f", "--textfile",dest="text_file", default= None,help="text file for dumping memory data ") 
	argparser.add_option('-o', '--dest', dest='dest',   help='Destination text file', default=None)
	argparser.add_option('-i', '--imagetype', dest='image_type',   help=' image needs to find', default=None)
	(options, args) = argparser.parse_args()
	#Get the dll path 
	path = get_string(options.text_file,options.image_type)
	
	#Write the dll path in a text file
	f2=open(options.dest,"w")
	f2.write(path)
	print(path)
	
	
	






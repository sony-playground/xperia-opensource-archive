#!/usr/bin/python
#============================================================================
#
#/** @file dll_path_save_builder.py
#
# GENERAL DESCRIPTION
#   Generate image version output files : dll_path_save.c  
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
# 10/28/2020   gteeger     convert to python3
# 03/27/2020   rakhi       initial version
#============================================================================
from __future__  import print_function
import os
import sys
import re
import socket
import uuid
from datetime import datetime
from xml.etree import ElementTree as et
from optparse import OptionParser
import string
import platform

##-------------------------------------------------------------------------
##create_file_banner
##creates a string that can be use as a banner for auto generated files
##-------------------------------------------------------------------------'''
def CreateFileBanner(fname, description="None", start_comment="#",

   
   #The standard Qualcomm header 
   end_comment="", start_block="", end_block="", style='none'):
   banner_str = \
'''$SB$SCM============================================================================$ECM
$SCM  Name:                                                                     $ECM
$SCM    $FILE_NAME $ECM
$SCM
$SCM  Description:                                                              $ECM
$SCM    $DESCRIPTION $ECM
$SCM                                                                            $ECM
$SCM Copyright (c) $YEAR by Qualcomm Technologies, Incorporated.  All Rights Reserved.        $ECM
$SCM============================================================================$ECM
$SCM                                                                            $ECM
$SCM *** AUTO GENERATED FILE - DO NOT EDIT                                      $ECM
$SCM                                                                            $ECM
$SCM GENERATED: $DATE $ECM
$SCM============================================================================$ECM$EB
'''
   if style == 'C':
       start_comment = "#"
       end_comment = ""
       start_block = "/*\n"
       end_block = "\n*/"
   elif style == 'C++':
       start_comment = "//"
       end_comment = ""
       start_block = ""
       end_block = ""

   elif style == 'asm':
       start_comment = ";"
       end_comment = ""
       start_block = ""
       end_block = ""

   elif style == 'make' or style == 'shell':
       start_comment = "#"
       end_comment = ""
       start_block = ""
       end_block = ""

   elif style == 'dos':
       start_comment = "REM "
       end_comment = ""
       start_block = ""
       end_block = ""

   banner_str = banner_str.replace('$SCM', start_comment)
   banner_str = banner_str.replace('$ECM', end_comment)
   banner_str = banner_str.replace('$SB', start_block)
   banner_str = banner_str.replace('$EB', end_block)
   banner_str = banner_str.replace('$YEAR', str(datetime.now().strftime('%Y')))
   banner_str = banner_str.replace('$DATE', str(datetime.now().ctime()))
   banner_str = banner_str.replace('$FILE_NAME', fname)
   banner_str = banner_str.replace('$DESCRIPTION', description)

   return banner_str

def dll_loader_builder(target,loader_path,image_name):
   '''-------------------------------------------------------------------------
  DLL Path builder action
   This is the actual builder that generates dll_path_save.c. target is the
   location of the *.c file 
  -------------------------------------------------------------------------'''
  # The array design is ported from SCons system 
  # targets and sources are ALWAYS arrays (is a builder standard interface)
  # this builder needs to know if it deals with multiple targes and sources
  # or singles, or mix (common use case: one target multiple sources).
   target_full = str(target[0])
   #source_full = str(source[0])
   # crete version string
   # embedd the Build ID and limit the Build ID to 72 characters
   dll_loader_str = "".join([
	   "const char dll_path_init[]__attribute__((section(\".dll_path_section\"))) =\"","*",image_name,"*",loader_path, "\";\n"]) 
    

   # create QC version file
   banner = CreateFileBanner(os.path.split(target_full)[1], style='C')
   qc_version_file = open (target_full, "w")
   qc_version_file.write(banner)
   qc_version_file.write(dll_loader_str)
   qc_version_file.close()


###########################################################  
# Provide Comma Separated Arguements 
###########################################################
def get_comma_separated_args(option, opt, value, parser):
  setattr(parser.values, option.dest, value.split(','))



def main():
   
	parser = OptionParser()


 
	parser.add_option("-t", "--target-dir",
			action="store", type="string", dest="targetdir",
		    default="Library/VersionBuilderLib",
		    help="Target directory name. Default is 'Library/VersionBuilderLib' ")

	parser.add_option('-d', "--dll_paths",
            action="store", default="", type = "string", dest = "dll_paths",
		    help="Specify dll_path. Example: -d dll_path")
	parser.add_option('-m', "--image_name",
                    action="store", default="", type = "string", dest = "image_name",
		    help="Specify image_name. Example: -m image_name") 
  
	(options, args) = parser.parse_args()


  
	print(options.dll_paths)
	options.dll_paths=options.dll_paths.replace('\\','/')
	# Convert target dir path to OS.  I.E. / vs \
	options.targetdir = options.targetdir.replace('/', os.sep)
	options.targetdir = options.targetdir.replace('\\', os.sep)
	if not os.path.isdir(options.targetdir):
  		print(options.targetdir)
  		try:
  			os.makedirs(options.targetdir)
  		except:
  			print("Error encountered while creating directory " + options.targetdir)
  			print("Error info: ", sys.exc_info()[0])
  			sys.exit(1)
	dll_version_path = os.path.join(options.targetdir, "dll_path_save"+options.image_name+".c")
	print("Generating " + dll_version_path)
	dll_loader_builder([os.path.join(options.targetdir,
								   'dll_path_save'+'.c')],
                                    options.dll_paths,options.image_name)


if __name__ == "__main__":
   main()

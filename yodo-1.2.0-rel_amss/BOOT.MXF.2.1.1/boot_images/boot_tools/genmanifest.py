#!/usr/bin/env python

#============================================================================
#
# @file genmanifest.xml
#
# GENERAL DESCRIPTION
#   Automatically generate ./build_images/Build/Manifest.xml for production 
#   signing of elf images ./build_images/Build/Manifest.xml is to be 
#	submitted in Tiberium
#
# Copyright 2020,2022 by Qualcomm Technologies, Inc.
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
# --------   ---     ----------------------------------------------------------
# 04/28/22   ds      fix for python3
# 08/06/20   gt      Initial release


import os
import sys
import fileinput
import argparse

PATH = os.getcwd()
HEADER = '<?xml version="1.0" encoding="UTF-8"?>\n\
<tns:signing_manifest xmlns:tns="http://www.qualcomm.com/sectools"\r\
                      xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"\r\
                      schema_version="1.0"\r\
                      xsi:schemaLocation="http://www.qualcomm.com/sectools ../signing_manifest/signing_manifest.xsd">\n'

FOOTER = '</tns:signing_manifest>'
CMD_HEAD = '\t<secure_image_command>\n'
CMD_FOOT = '\t</secure_image_command>\n'
PLACEHOLDER = '$CMD\n'


parser = argparse.ArgumentParser()
parser.add_argument("--directory","-d", required = True, help = "Output location for signing_manifest.xml")
args, _ = parser.parse_known_args()
FILE_NAME = args.directory

def write_cmd(file_desc, cmd):
	file_desc.seek(0)
	file = file_desc.readlines()
	file_desc.truncate(0)
	for i,line in enumerate(file):
		if PLACEHOLDER in line:
			line = '\t\t' + cmd + '\n'
		file_desc.write(line)

# Write to manifest.xml
def write_to_file():
	cmd = " ".join(sys.argv[3:])
	with open(FILE_NAME,'a+') as f:
		f.seek(0)
		lines = f.readlines()
		for line in lines:
			if cmd in line:
				return
		if not lines:
			f.write(HEADER)
		else:
			f.seek(f.tell() - len(lines[-1]))
			f.truncate()
		f.write(CMD_HEAD)
		f.write(PLACEHOLDER)
		write_cmd(f,cmd)
		f.write(CMD_FOOT)
		f.write(FOOTER)
		f.flush()


def main():
	write_to_file()

if __name__ == "__main__":
	main()




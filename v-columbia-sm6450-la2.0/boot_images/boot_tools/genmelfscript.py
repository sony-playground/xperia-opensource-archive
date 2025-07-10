#!/usr/bin/env python

#============================================================================
#
# @file genmelfscript.py
#
# GENERAL DESCRIPTION
#   Automatically generate genmelf.py for creating multi-elf images
#   Genmelf.py will be located in ./build_images/Build/ and called
#   after production signing to append production signed elfs.
#
# Copyright 2020 by Qualcomm Technologies, Inc.
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
# 12/21/20   ds      fix path for create_multielf
# 08/06/20   gt      Initial release

import os
import sys
import argparse

COPY_IMPORT = "#start copying\n"

HEADER = "\
#!/usr/bin/env python\n\
#============================================================================\n\
#\n\
# @file genmelf.py\n\
#\n\
# GENERAL DESCRIPTION\n\
#   Automatically generated script called after production signing \n\
#   to append production signed elfs and copy specified files.\n\
#\n\
# Copyright 2020 by Qualcomm Technologies, Inc.\n\
#                 All Rights Reserved.\n\
#               QUALCOMM Proprietary/GTDR\n\
\n\
from __future__  import print_function\n\
import os\n\
import shutil\n\
def copy(src,dest):\n\
  if os.path.isdir(src):\n\
     if os.path.exists(dest):\n\
       try:\n\
        shutil.rmtree(dest)\n\
        print(\"{} is deleted!\".format(dest))\n\
       except Exception as error:\n\
        print(\"Error info:%s\", error)\n\
        sys.exit()\n\
     try:\n\
        shutil.copytree(src, dest)\n\
        print(\"Copy {} to {} successfully!\".format(src, dest))\n\
     except Exception as error:\n\
        print(\"Error info:%s\", error)\n\
        sys.exit()\n"



parser = argparse.ArgumentParser()
parser.add_argument("--directory","-d", required = True, 
	help = "Output location for genmelf.py")
parser.add_argument("--copy_from", nargs = '+', required = False, 
	help = "(optional) Files to copy")
parser.add_argument("--copy_to", nargs = '+', required = False, 
	help = "(optional) Copy destination")
parser.add_argument("--in_elfs","-f", nargs = '+', required = False, 
	help = "input elf files")
parser.add_argument("--out_melf","-o", required = False, 
	help = "output multi-elf file")
args, _ = parser.parse_known_args()

FILE_NAME = "".join(args.directory)
# Generate the command from parameters in buildconfig.json to be 
# written to genmelf.py
def generate_command():
	cmd = "python boot_images/boot_tools/create_multielf.py"
	cmd += " -f "
	cmd += "".join(args.in_elfs)
	cmd += " -o "
	cmd += "".join(args.out_melf)
	print(cmd)
	return cmd

#Write to genmelf.py
def write_file(cmd):
	if not os.path.isfile(FILE_NAME):
		with open(FILE_NAME,'w') as f:
			f.write(HEADER)
	with open(FILE_NAME,'r+') as f:
		lines = f.readlines()
		found = False
		for line in lines:
			if cmd in line:
				found = True
		if found is False:
			f.write("os.system('")
			f.write(cmd)
			f.write("')\n")
		f.flush()

def copy_files_command():
	COPY_CMD = ''
	with open(FILE_NAME,'a+') as f:
		found = False
		lines = f.readlines()
		for line in lines:
			if COPY_IMPORT in line:
				found = True
				break
		if found is False:
			f.write(COPY_IMPORT)
		for i in args.copy_from:
			for j in args.copy_to:
				found = False
				print("copying " + i + " to " + j)
				if os.path.isdir(i):
				 COPY_CMD =  "copy(\"{}\",\"{}\")\n".format(i,j)
				else:
				 COPY_CMD = "shutil.copy2(\"{}\", \"{}\")\n".format(i,j)
				COPY_CMD = COPY_CMD.replace("\\\\","/")
				COPY_CMD = COPY_CMD.replace("\\","/")
				for line in lines:
					if COPY_CMD in line:
						found = True
						break
				if found is False:
					f.write(COPY_CMD)

		f.flush()


def main():
	if args.in_elfs is not None or args.out_melf is not None:
		if args.in_elfs is None or args.out_melf is None:
			print("Source elf or Target Melf is missing")
			sys.exit(1)
		else:
			cmd = generate_command()
			cmd = cmd.replace("\\\\","/")
			cmd = cmd.replace("\\","/")
			write_file(cmd)
	if args.copy_from is not None or args.copy_to is not None:
		if args.copy_from is None or args.copy_to is None:
			print("Copy source or target is missing")
			sys.exit(1)
		else:
			copy_files_command()

if __name__ == "__main__":
	main()

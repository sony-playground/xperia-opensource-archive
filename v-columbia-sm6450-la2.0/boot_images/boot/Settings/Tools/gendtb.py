#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2020 - 2021 Qualcomm Technologies, Inc.  All Rights Reserved.

import argparse
import os
import sys

# Do not change these
CPP_ARGS="-P -x assembler-with-cpp"		# override with --cpparg
DTC_ARGS="-@ -O dtb -o"					# override with --dtcarg

CPP="clang-cpp"
DTC="dtc"

##############################################################################
# FindTheTools
##############################################################################
def FindTheTools():
	global args
	global CPP
	global DTC
	global Extension

	# Looking for CPP
	if args.arch == "hexagon":
		CPP = "hexagon-clang-cpp"
	CPP += Extension
	if args.cpppath:
		CPP = os.path.join(os.path.abspath(args.cpppath), CPP)

	print("\n#### gendtb.py Looking for CPP ####")
	cmd = "%s --version" % (CPP)
	return_code = os.system(cmd)
	if return_code:
		print("\nCPP is required for DeviceTree Blob (DTB) generation.")
		print("--cpppath can be used to specify its install location.")
		print("CPP[" + CPP +"] tool cannot be found, goodbye!")
		sys.exit(1)		

	# Looking for DTC
	DTC += Extension
	if args.dtcpath:
		DTC = os.path.join(os.path.abspath(args.dtcpath), DTC)

	print("\n#### gendtb.py Looking for DTC ####")
	cmd = "%s --version" % (DTC)
	return_code = os.system(cmd)
	if return_code:
		print("\nDTC is required for DeviceTree Blob (DTB) generation.")
		print("--dtcpath can be used to specify its install location.")
		print("DTC[" + DTC +"] tool cannot be found, goodbye!")
		print("DTC (for Windows) can be installed via QPM.")
		sys.exit(1)
		
	print("\n#### DTC & CPP Available ####")
	print("DTC[%s]" % (DTC))
	print("CPP[%s]\n" % (CPP))

##############################################################################
# HandleFileName
##############################################################################
def HandleFileName(FileName):
	global dtsFile
	global dtbFile
	global cppFile
	global oPath
	global args

	if FileName.endswith(".dts"):
		dtsFile = FileName
		cppFile = oPath + os.path.basename(FileName) + ".pp"
		dtbFile = oPath + os.path.basename(FileName)[:-1] + "b"
	elif FileName.endswith(".dtsi"):
		if args.nodtc:
			dtsFile = FileName
			cppFile = oPath + os.path.basename(FileName) + ".pp"
			dtbFile = ""
		else:
			sys.exit(".dtsi(%s) file only allowed with --nodtc flag" % (dtsFile))
	else:
		dtsFile = FileName + ".dts"
		cppFile = oPath + os.path.basename(dtsFile) + ".pp"
		dtbFile = oPath + os.path.basename(FileName) + ".dtb"

	if args.verbose:
		print("dtsFile[%s]..cppFile[%s]..dtbFile[%s]" % (dtsFile, cppFile, dtbFile))

##############################################################################
# main
##############################################################################
def main():
	global dtsFile
	global dtbFile
	global cppFile
	global oPath
	global args
	global Extension

	parser = argparse.ArgumentParser(description='Command-Line Tool to Generate XBL/UEFI DTB Files')
	parser.add_argument("-v", "--verbose", action='store_true', help="Enable Verbose Output")
	parser.add_argument("-p", "--cpparg", help="Override CPP argument string")
	parser.add_argument("-t", "--dtcarg", help="Override DTC argument string")
	parser.add_argument("-o", "--output", help="Output folder for generated files")
	parser.add_argument("-c", "--cpppath", help="Path for CPP (C Pre-Processor)")
	parser.add_argument("-d", "--dtcpath", help="Path for DTC (DeviceTree Compiler)")
	parser.add_argument("-i", "--include", help="Include Path(s) for DTSI files (include -I)")
	parser.add_argument("-f", "--file", help="DTS Source File")
	parser.add_argument("-n", "--nodtc", action='store_true', help="Stop after CPP, partial build")
	parser.add_argument("-a", "--arch", action='store', help="Architecture can be arm|hexagon")
	args = parser.parse_args()

	if sys.platform == 'win32':
		Extension = '.exe'
	else:
		Extension = ''
	Separator = os.sep

	# Step 1: Handle Command-Line Arguments
	#######################################
	if args.output:
		if not args.output.endswith(Separator):
			args.output += Separator
		oPath = args.output
	else:
		oPath = '.' + Separator

	if args.cpppath:
		cPath = args.cpppath
	else:
		cPath = ''

	if args.dtcpath:
		dPath = args.dtcpath
	else:
		dPath = ''

	if args.cpparg:
		cArg = args.cpparg
	else:
		cArg = CPP_ARGS

	if args.dtcarg:
		dArg = args.dtcarg
	else:
		dArg = DTC_ARGS
	
	if args.include:
		iArg = args.include
	else:
		iArg = ''

	FindTheTools()

	# Step 2: Parse (& Fixup) FileName Parameter
	############################################
	if not args.file:
		sys.exit("DTS Source File must be specified with [-f|--file] command-line parameter")
	else:
		HandleFileName(args.file)

	# Step 3: Run dtsFile through C Pre-Processor
	#############################################
	command="%s %s %s %s > %s" % (CPP, cArg, iArg, dtsFile, cppFile)
	if args.verbose:
		print("Running [%s]" % (command))

	return_code = os.system(command)
	if return_code != 0:
		sys.exit("CPP could not pre-process [%s]" % (dtsFile))

	# Step 4: Run cppFile through DTC
	#################################
	if not args.nodtc:
		command="%s %s %s %s" % (DTC, dArg, dtbFile, cppFile)
		if args.verbose:
			print("Running [%s]" % (command))

		return_code = os.system(command)
		if return_code != 0:
			sys.exit("DTC could not generate [%s]" % (dtbFile))

main()

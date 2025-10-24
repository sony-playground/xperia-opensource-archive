#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2020 - 2022 Qualcomm Technologies, Inc.  All Rights Reserved.

import argparse
import os
import sys
import subprocess

# Do not change these
CPP_ARGS="-P -x assembler-with-cpp"		# override with --cpparg
DTC_ARGS="-@ -O dtb -o"					# override with --dtcarg

DTC="dtc"
AdjustedIPath=""						# add -I to each path specified

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
	else:
		CPP = "clang-cpp"
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
def HandleFileName():
	global dtsFile
	global dtbFile
	global cppFile
	global oPath
	global args
	FileName = args.file
	if FileName.endswith(".dts"):
		dtsFile = FileName
		cppFile = oPath + os.path.basename(FileName) + ".pp"
		dtbFile = oPath + os.path.basename(FileName)[:-3] + args.extension
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
		dtbFile = oPath + os.path.basename(FileName) + "." + args.extension

	# Confirm input file exists
	if not os.path.isfile(dtsFile):
		print("\nSpecified dts file (%s) does not exist, goodbye" % (dtsFile))
		sys.exit(1)

	if args.verbose:
		print("dtsFile[%s]..cppFile[%s]..dtbFile[%s]" % (dtsFile, cppFile, dtbFile))

##############################################################################
# checkIncludePath
##############################################################################
def checkIncludePath(includePath):
	global AdjustedIPath
	Paths = includePath.split()
	for p in Paths:
		if not os.path.isdir(p):
			print("Path [%s] does not exist" % (p))
			return False
		else:
			AdjustedIPath += "-I%s " % p

	return True

##############################################################################
# formMacroParameters
##############################################################################
def formMacroParameters():
	global cppArg
	global args
	Macros = args.macro.split()
	for m in Macros:
		cppArg += " -D%s" % m

##############################################################################
# main
##############################################################################
def main():
	global dtsFile
	global dtbFile
	global cppFile
	global cppArg
	global oPath
	global args
	global Extension
	global AdjustedIPath

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
	parser.add_argument("-m", "--macro", help="CPP macro defintion, -D<macro>")
	parser.add_argument("-a", "--arch", action='store', help="Architecture can be arm|hexagon")
	parser.add_argument("-e", "--extension", default= "dtb" , help="output file extension, it could be dtb or dtbo")
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
		if os.path.isdir(args.output):
			oPath = args.output
		else:
			print("\nERROR: Specified output path (%s) does not exist, goodbye" % (args.output))
			sys.exit(1)
	else:
		oPath = '.' + Separator

	if args.cpppath:
		if os.path.isdir(args.cpppath):
			cPath = args.cpppath
		else:
			print("\nSpecified cpp path (%s) does not exist, goodbye" % (args.cpppath))
			sys.exit(1)
	else:
		cPath = ''

	if args.dtcpath:
		if os.path.isdir(args.dtcpath):
			dPath = args.dtcpath
		else:
			print("\nERROR: Specified dtc path (%s) does not exist, goodbye" % (args.dtcpath))
			sys.exit(1)
	else:
		dPath = ''

	if args.cpparg:
		cppArg = args.cpparg
	else:
		cppArg = CPP_ARGS
	if args.macro:
		formMacroParameters()

	if args.dtcarg:
		dArg = args.dtcarg
	else:
		dArg = DTC_ARGS
	
	if args.include:
		if checkIncludePath(args.include):
			iArg = AdjustedIPath
		else:
			print("\nERROR: Specified include path (%s) does not exist, goodbye" % (args.include))
			sys.exit(1)
	else:
		iArg = ''

	if args.extension != "dtb" and args.extension != "dtbo":
		print("\nERROR: output file extension %s is not correct, it should be dtb or dtbo" % (args.extension))
		sys.exit(1)
	FindTheTools()

	# Step 2: Parse (& Fixup) FileName Parameter
	############################################
	if not args.file:
		sys.exit("DTS Source File must be specified with [-f|--file] command-line parameter")
	else:
		HandleFileName()

	# Step 3: Run dtsFile through C Pre-Processor
	#############################################
	command="%s %s %s %s > %s" % (CPP, cppArg, iArg, dtsFile, cppFile)
	if args.verbose:
		print("Running [%s]" % (command))

	return_code = os.system(command)
	if return_code != 0:
		sys.exit("CPP could not pre-process [%s]" % (dtsFile))

	# Step 4: Run cppFile through DTC
	#################################
	if not args.nodtc:
		command="%s %s %s %s" % (DTC, dArg, dtbFile, cppFile)
		error_code = 0
		if args.verbose:
			print("Running [%s]" % (command))

		lcommand = command.split()

		try:
			return_code = subprocess.check_output(lcommand, stderr=subprocess.STDOUT)

		except subprocess.CalledProcessError as error:
			#Get the returncode and output that are stored in error from subprocess.CalledProcessError
			error_code = error.returncode
			return_code = error.output

		Sstderr = return_code.decode()
		Swarning = Sstderr.find("Warning")
		Serror  = Sstderr.find("ERROR")
		if Swarning != -1 or Serror != -1:
			print("stderr:\n{}".format(Sstderr))
			error_code = 1
		if error_code != 0:
			sys.exit("DTC could not generate [%s]" % (dtbFile))

main()

#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.

# -n : PYTHONPATH environment path
# -o : Output Path(folder) for all output files
# -d : Path to DTC
# -p : Path to CPP
# -u : Path to DTS.PP file location
# -r : Path to project-schema.yaml file
# -a : Override CPP argument string
# -s : Override dtc argument string
# -t : Path to DT-Schema tools
# -i : Append all include files
# -w : Override any Issue in tool into Warnings
# -v : Verbose

import argparse
import os
import sys
import platform
from qc_dt_schema_common_tool  import 	Handle_DT_VALIDATE, \
										Handle_DT_EXIT, \
										Get_tools_path, \
										Exec_command, \
										Create_log_file, \
										Clean_log_file

RETURN_SUCCESS = 0

# Do not change these
CPP_ARGS="-P -x assembler-with-cpp"		# override with --cpparg
DTC_ARGS="-O yaml"						# override with --dtcarg

CPP_LINUX = "clang-cpp"

CPP_WINDOWS = "clang-cpp.exe"

DTC_LINUX = "dtc"
DTC_WINDOWS = "dtc.exe"

PYTHON = "python"

LINUX_DELETE = "rm"
WINDOWS_DELETE = "del"

# Default DT verification tools
DT_DOC_VALIDATE_EXEC="dt-doc-validate"
DT_EXTRACT_EXAMPLE_EXEC="dt-extract-example"
DT_MK_SCHEMA_EXEC="dt-mk-schema"
DT_VALIDATE_EXEC="dt-validate"

# Default extensions
DTS_EXTN = ".dts"
DTS_PP_EXTN = ".dts.pp"
DT_YAML_EXTN = ".dt.yaml"

# Default project file name to be generated and verified
PROJECT_SCHEMA_FILE_NAME = "project-schema"

# Default include paths if --include isn't specified
INCLUDE_OPTION = "-I"

STRING_TO_DISPLAY = "DTS/DTSI File Validation against Project Schema File"

VALIDATE_COMPATIBLE_STRING_FROM_DT_VALIDATE = 1

QC_DT_SCHEMA_CHECK_TOOL = "qc_dt_schema_check_tool.log"
##############################################################################
# Get_list_dts_files
##############################################################################
def Get_list_dts_files(dtsfilespath):

	# Generate list of *.dts files
	list_dts_files = []
	for file in os.listdir(dtsfilespath):
		if(file.endswith(DTS_PP_EXTN)):
			filename = os.path.join(os.path.abspath(dtsfilespath), file)
			filename = filename.replace(DTS_PP_EXTN, "")
			list_dts_files.append(filename)
	return list_dts_files

##############################################################################
# Handle_Clean
##############################################################################
def Handle_Clean(delete_file_list):
	
	print("====== Start of Clean ======")
	
	# Step 1: Delete all collected files
	####################################
	for files in delete_file_list:
		if platform.system() == "Windows":
			delete_command = WINDOWS_DELETE
		else:
			delete_command = LINUX_DELETE
		
		input_filename = "\"" + files + "\""
		command="%s %s" % (delete_command, input_filename)
		
		if args.verbose:
			print("Removing: ", input_filename)
			print("Running [%s]\n" % (command))
		
		if os.path.exists(files) != True:
			if args.verbose:
				error_msg = "Filename " + input_filename + " already removed\n"
				print(error_msg)
				continue
		
		# Run command
		return_code = Exec_command(command)
		if return_code != 0:
			error_msg = "dt-doc-validate failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
	
	print("====== End of clean ======\n")


def Validate_compatible_string_defined(pspath, compatible_string_in_dts):
	# compatible_string_in_dts is a set. Script #1 has stored compatible string in a log
	# file where project_schema.yaml file exists
	
	compatible_string_in_yaml = set()
	compatible_string_undefined = []
	pspath = os.path.dirname(pspath)
	compatible_read_filename = os.path.join(pspath, QC_DT_SCHEMA_CHECK_TOOL)
	
	if os.path.exists(compatible_read_filename) != True:
		error_msg = "File [" + compatible_read_filename + "] does not exist"
		Handle_DT_EXIT(error_msg, args.warning)
	
	try:
		# store YAML file's compatible string in a Set
		open_file = open(compatible_read_filename, "r")
		
		for line in open_file:
			line = line.rstrip('\n')
			
			if len(line):
				compatible_string_in_yaml.add(line)
		
		open_file.close()
		
	except:
		error_msg = compatible_read_filename + " file open/read failed"
		Handle_DT_EXIT(error_msg, args.warning)
	
	# compatible_string_in_dts agains compatible_string_in_yaml
	for cs_in_dts in compatible_string_in_dts:
		
		if len(cs_in_dts) and cs_in_dts not in compatible_string_in_yaml:
			compatible_string_undefined.append(cs_in_dts)
			if args.verbose:
				print("Validating for \"%s\" : Found" % (cs_in_dts))
		else:
			if args.verbose:
				print("Validating for \"%s\" : Not Found" % (cs_in_dts))
	
	return compatible_string_undefined

##############################################################################
# Handle_validate_extracted_example
##############################################################################
def Handle_compile_dts_files(	list_dts_files, output_directory_path, 
								cpp_command, dtc_command):
	
	global cArg
	global dArg
	global includeArg
	
	print("====== Start DTC on DTS files ======")
	input_filename = ""
	
	# list_dts_files contains list of absoulute path for yaml files
	for files in list_dts_files:
	
		# Step 1: Compile extracted examples
		#######################################################################
		
		# Commenting this section for now. When gendtb is available for YAML output,
		# the below section will be removed.
		
		## Input extracted example file
		#input_filename = files + DTS_EXTN
		#delete_filename = input_filename
		#
		#if os.path.isfile(input_filename) != True:
		#	error_msg = "Error: Filename " + input_filename + " does not exist"
		#	sys.exit(error_msg)
		#
		## Output file
		#output_filename = files + DTS_PP_EXTN
		#
		#command="%s %s %s -o %s %s\n" % (cpp_command, cArg, input_filename, output_filename, includeArg)
		#
		#if args.verbose:
		#	print("\nRunning [%s]" % (command))
		#
		## Run command
		#return_code = Exec_command(command)
		#if return_code != 0:
		#	sys.exit("Error: CPP failed for [%s]" % (input_filename))
		#
		# Step 2: Run DTC on compiled files above
		#######################################################################
		
		input_filename = files + DTS_PP_EXTN
		
		output_filename = os.path.basename(files) + DT_YAML_EXTN
		output_filename = os.path.join(output_directory_path, output_filename)
		
		command="%s %s -o %s %s" % (dtc_command, dArg, output_filename, input_filename)
		
		if args.verbose:
			print("Running [%s]" % (command))
		
		# Run command
		return_code = Exec_command(command)
		if return_code != 0:
			error_msg = "DTC failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)

	print("====== End DTC on DTS files ======\n")	




##############################################################################
# main
##############################################################################
def main():
	global dtsFile
	global dtbFile
	global cppFile
	global oPath
	global args
	global cArg
	global dArg
	global includeArg
	global delete_file_list
	global Platform
	
	iArg = ""
	includeArg = ""
	compatible_string_set = set()
	
	parser = argparse.ArgumentParser(description='Command-Line Tool to Validate DeviceTree files to Project schema')
	parser.add_argument("-n", "--pythonpath", help="Path for PYTHONPATH Environment variable")
	parser.add_argument("-d", "--dtcpath", help="Path for DTC (DeviceTree Compiler)")
	parser.add_argument("-o", "--output", help="Output Path(folder) for all output files")
	parser.add_argument("-p", "--cpppath", help="Path for CPP (C Pre-Processor)")
	parser.add_argument("-u", "--dtsfilespath", help="Include Path(s) for all .yaml files")
	parser.add_argument("-r", "--projectschemapath", help="Include Path(s) for all .yaml files")
	parser.add_argument("-a", "--cpparg", help="Override CPP argument string")
	parser.add_argument("-s", "--dtcarg", help="Override DTC argument string")
	parser.add_argument("-t", "--dtschematoolspath", help="Include Path(s) for all dt-schema tools")
	parser.add_argument("-w", "--warning", action='store_true', help="Override any Error into Warnings")
	parser.add_argument("-i", "--include", help="Include Path(s) for DTSI files (include -I)", nargs='+')
	parser.add_argument("-v", "--verbose", action='store_true', help="Enable Verbose Output")
	
	args = parser.parse_args()

	# Step 1: Handle Command-Line Arguments
	#######################################################################
	
	if args.warning:
		print("\nNote: Warning override initiated! Any error will be overriden to Warnings.\n")
		
	pythonpath = ""
	if args.pythonpath and args.pythonpath != "":
		pythonpath = os.path.abspath(args.pythonpath)
		if os.path.exists(pythonpath) == True:
			sys.path.append(pythonpath)
		else:
			pythonpath = ""
	
	if pythonpath == "":
		error_msg = "Note: Environment variable PYTHONPATH not updated. PYTHONPATH path can be specified using [-n] command-line parameter"
	
	if args.dtcarg:
		dArg = args.dtcarg
	else:
		dArg = DTC_ARGS
	
	if args.output:
		output_directory_path = args.output
		if os.path.exists(output_directory_path) != True:
			error_msg = "Output Path path is required/must exist"
			Handle_DT_EXIT(error_msg, args.warning)
			
		output_directory_path = os.path.abspath(output_directory_path)
	else:
		error_msg = "Output path required using [-o] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if args.cpparg:
		cArg = args.cpparg
	else:
		cArg = CPP_ARGS

	dtschema_tools_path = ""
	if args.dtschematoolspath:
		dtschema_tools_path = args.dtschematoolspath
		
		if os.path.exists(dtschema_tools_path) != True:
			error_msg = "Pathname [" + dtschema_tools_path + "] does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
	else:
		error_msg = "DT-Schema Tools path can be specified using [-t] command-line parameter"
	
	if args.dtcpath:
		dtc_path = args.dtcpath
	else:
		error_msg = "Include DTC path using [-d] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if args.cpppath:
		cpp_path = args.cpppath
	else:
		error_msg = "Include CPP path using [-p] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if args.dtsfilespath:
		dtsfilespath = os.path.abspath(args.dtsfilespath)
	else:
		error_msg = "Schema File path must be specified using [-u] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if os.path.exists(dtsfilespath) != True:
		error_msg = "Pathname [" + dtsfilespath + "] does not exist"
		Handle_DT_EXIT(error_msg, args.warning)
	
	print("DTS files are located in: [%s]\n" % (dtsfilespath))
			
	# Append any include path along with DTS path Include folders
	if args.include:
		for includePath in args.include:
			iArg = os.path.abspath(includePath)
			if os.path.exists(iArg) != True:
				error_msg = "Pathname [" + iArg + "] does not exist"
				Handle_DT_EXIT(error_msg, args.warning)
			
			if args.verbose:
				print("Include for CPP [%s]"%(iArg))
			includeArg = includeArg + INCLUDE_OPTION + " " + iArg + " "
	
	if args.projectschemapath:
		pspath = args.projectschemapath
	else:
		error_msg = "Project Schema File path must be specified using [-r] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
		
	if os.path.exists(pspath) != True:
		error_msg = "Pathname [" + pspath + "] does not exist"
		Handle_DT_EXIT(error_msg, args.warning)
	
	print_buffer = "Python Version: " + platform.python_version()
	print(print_buffer)
	python_installed_scripts_path = ""
	
	if platform.system() == "Windows":
		python_installed_scripts_path = os.path.abspath(os.path.join(sys.executable, '..'))
		python_installed_scripts_path = os.path.join(python_installed_scripts_path, 'Scripts')
	
	# Step 2: Set the DT-schema tools path in Windows and Linux
	#######################################################################
	dt_validate_exec_command = os.path.join(dtschema_tools_path, DT_VALIDATE_EXEC)
	if os.path.exists(dt_validate_exec_command) != True:
		error_msg = "Filename [" + dt_validate_exec_command + "] does not exist"
		dt_validate_exec_command = DT_VALIDATE_EXEC

		if platform.system() == "Windows":
			dt_validate_exec_command = PYTHON + " " + Get_tools_path(args, python_installed_scripts_path, dt_validate_exec_command)
	else:
		dt_validate_exec_command = PYTHON + " " + dt_validate_exec_command
	
	print("Scripts are :")
	print(dt_validate_exec_command)
	print("\n\n")
	# Step 3: Set up CPP & DTC Compilers
	#######################################################################
	if platform.system() == "Windows":
		cpp_command = os.path.join(cpp_path, CPP_WINDOWS)
		dtc_command = os.path.join(dtc_path, DTC_WINDOWS)
	else:
		cpp_command = os.path.join(cpp_path, CPP_LINUX)
		dtc_command = os.path.join(dtc_path, DTC_LINUX)
	
	if os.path.exists(cpp_command) != True:
		error_msg = "Compiler [" + cpp_command + "] does not exist"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if os.path.exists(dtc_command) != True:
		error_msg = "Compiler [" + dtc_command + "] does not exist"
		Handle_DT_EXIT(error_msg, args.warning)
	
	# Step 4: Make list of all *.dts files and a delete file list
	#######################################################################
	list_dts_files = Get_list_dts_files(dtsfilespath)
	
	# Step 5: Remove all stale log files
	#######################################################################
	Clean_log_file(output_directory_path, os.path.splitext(os.path.basename(__file__))[0], args)

	# Step 6: Validate the extracted examples
	#######################################################################
	Handle_compile_dts_files(list_dts_files, output_directory_path,
								cpp_command, dtc_command)

	# Step 7: Validate extracted examples against pre-processed Project Schema file
	#################################################################################
	
	# Modified dt-validate return a Set of compatbile strings. Compare the returned 
	# Set with compatible string against compatible string generated in a log file by
	# qc_dt_schema_common_tool (script #1).
	# VALIDATE_COMPATIBLE_STRING_FROM_DT_VALIDATE has been set to 0x1. 
	compatible_string_in_dts = Handle_DT_VALIDATE(	list_dts_files, output_directory_path,
												dt_validate_exec_command, pspath, 
												DT_YAML_EXTN, 
												args, STRING_TO_DISPLAY,
												VALIDATE_COMPATIBLE_STRING_FROM_DT_VALIDATE)
	
	# Step 8: Open compatible string file created by qc_dt_schema_check_tool (script #1).
	#         The file is stored where project_schema.yaml file exist.
	#         Compare against compatbile string returned by dt-validate.
	#######################################################################
	compatible_string_undefined = Validate_compatible_string_defined(pspath, compatible_string_in_dts)
	
	# TODO: When all the YAML/DTSI files are up-to-date, move this to error
	# message (error_msg) and use HANDLE_DT_EXIT(). Handle this as an error.
	# The below section should throw  error in future.
	if len(compatible_string_undefined):
		error_msg = ("\n\n**** WARNING: %s Discrepancies found ****" % (str(len(compatible_string_undefined))))
		error_msg += ("\nDTSI files with following compatible string has missing/undefined YAML file:\n")
		for csu in compatible_string_undefined:
			error_msg += (" - \"%s\"\n" % (csu))
			
		# todo: remove print and uncomment (HANDLE_DT_EXIT) in future
		print(error_msg)
		#HANDLE_DT_EXIT(error_msg, args.warning)
	
	# Step 9: Create an output text file
	#######################################################################
	try:
		Create_log_file(list_dts_files, 
						output_directory_path, 
						os.path.splitext(os.path.basename(__file__))[0], 
						DTS_PP_EXTN, 
						"",
						args)
	except:
		error_msg = "Error in final Log file creation"
		Handle_DT_EXIT(error_msg, args.warning)
	
	sys.exit(RETURN_SUCCESS)
	
	#print("****** End of qc_dt_check ******\n")

main()
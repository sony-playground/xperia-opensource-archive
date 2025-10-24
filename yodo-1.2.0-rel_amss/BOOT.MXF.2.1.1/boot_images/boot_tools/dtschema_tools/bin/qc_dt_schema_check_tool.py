#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.

# -n : PYTHONPATH environment path
# -o : Output Path(folder) for all output files
# -r : Name for project-schema file
# -d : Path to DTC
# -p : Path to CPP
# -y : Path to YAML Tree
# -a : Override CPP argument
# -s : Override DTC argument
# -t : Path to DT-Schema tools
# -w : Override any Issue in tool into Warnings
# -v : Verbose	
# -c : Clean build

import argparse
import os
import sys
import platform
from qc_dt_schema_common_tool import 	Handle_DT_VALIDATE, \
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
YAMLFILE_EXTN = ".yaml"
EXAMPLE_DTS_EXTN = ".example.dts"
VALIDATE_EXAMPLE_TEMP_EXTN = ".example.dt.yaml.dts.tmp"
EXAMPLE_DT_YAML_EXTN = ".example.dt.yaml"
CLEAN_EXTENSION=".example.dt"

STRING_TO_DISPLAY = "YAML File Validation"

PROJECT_SCHEMA_FILE_NAME = "project-schema"
VALIDATE_COMPATIBLE_STRING_FROM_DT_VALIDATE = 0

##############################################################################
# Get_list_yaml_files
##############################################################################
def Get_list_yaml_files(sfpath):
	
	global delete_file_list
	
	# Generate list of *.yaml files
	list_yaml_files = []
	
	#delete all lingering output files in source location
	delete_file_list = []
	
	for root, dirs, files in os.walk(sfpath):
		for file in files:
			if(CLEAN_EXTENSION in file):
				delete_file_list.append(os.path.join(root, file))
			elif(file.endswith(YAMLFILE_EXTN)):
				list_yaml_files.append(os.path.splitext(os.path.join(root,file))[0]+'')
	
	return list_yaml_files

##############################################################################
# Handle_Clean
##############################################################################
def Handle_Clean(output_directory_path, pspath, sfpath):
	
	global Platform
	global delete_file_list
	
	print("====== Start of clean ======")
	
	if platform.system() == "Windows":
		delete_command = WINDOWS_DELETE
	else:
		delete_command = LINUX_DELETE
	
	# Step 1: Delete all "output" files
	##########################################
	
	# Delete list ending with: 
	#		*.example.dts or
	#		*.example.dt.yaml.dts.tmp or
	#		*.example.dt.yaml files
	##########################################
	
	files = os.listdir(output_directory_path)
	for file in files:
		if(CLEAN_EXTENSION in file):
			input_filename = "\"" + os.path.join(output_directory_path,file) + "\""
			command="%s %s" % (delete_command, input_filename)
		
			if args.verbose:
				print("Removing: ", input_filename)
				print("Running [%s]\n" % (command))
			
			# Run command
			return_code = Exec_command(command)
			if return_code != 0:
				error_msg = "Remove failed for [" + input_filename + "]"
				Handle_DT_EXIT(error_msg, args.warning)
	
	# Step 2: Delete project schema yaml file
	####################################
	input_filename = "\"" + pspath + "\""
	if os.path.isfile(input_filename) == True:
		command="%s %s" % (delete_command, input_filename)
		
		if args.verbose:
			print("Removing: ", input_filename)
			print("Running [%s]\n" % (command))
	
		# Run command
		return_code = Exec_command(command)
		if return_code != 0:
			error_msg = "Remove failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
	
	#delete all lingering project schema files in source location
	project_schema_yaml_abs_path = os.path.join(sfpath,'..')
	input_filename = os.path.join(project_schema_yaml_abs_path, PROJECT_SCHEMA_FILE_NAME + YAMLFILE_EXTN)
	
	# Append to delete file list
	if os.path.isfile(input_filename) == 1:
		delete_file_list.append(input_filename)
	
	#delete all lingering output files in source location
	for file in delete_file_list:
		input_filename = "\"" + file + "\""
		
		command="%s %s" % (delete_command, input_filename)
		
		if args.verbose:
			print("Removing: ", input_filename)
			print("Running [%s]\n" % (command))
	
		# Run command
		return_code = Exec_command(command)
		if return_code != 0:
			error_msg = "Remove failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
	
	print("====== End of clean ======\n")


##############################################################################
# Handle_DT_DOC_VALIDATE
##############################################################################
def Handle_DT_DOC_VALIDATE(list_yaml_files, dt_doc_validate_exec_command, output_directory_path):
	
	print("====== Start of dt-doc-validate ======")
	
	compatible_defined_list = []
	compatible_undefined_file = []
	
	import ruamel.yaml
	
	# list_yaml_files contains list of absoulute path for yaml files
	for files in list_yaml_files:
		# Input Yaml file
		input_filename = files + YAMLFILE_EXTN
		
		if os.path.isfile(input_filename) != True:
			error_msg = "Filename " + input_filename + " does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
		
		command="%s %s" % (dt_doc_validate_exec_command, input_filename)
		
		if args.verbose:
			print("Running [%s]\n" % (command))
		
		# Run command
		return_code = Exec_command(command)
		if return_code != 0:
			error_msg = "dt-doc-validate failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
		
		with open(input_filename) as f:
			result =  ruamel.yaml.safe_load(f)
		
		store_compatible = None
		try:
			store_compatible = result.get('properties').get('compatible').get('const')
		except:
			store_compatible = None
		
		if store_compatible == None:
			try:
				store_compatible = result.get('properties').get('compatible').get('enum')
			except:
				store_compatible = None
		
		if store_compatible == None:
			compatible_undefined_file.append(input_filename)
		else:
			if type(store_compatible) == str:
				compatible_defined_list.append(store_compatible)
			elif type(store_compatible) == list:
				compatible_defined_list.extend(store_compatible)
		
	print("====== End of dt-doc-validate ======\n")
	return compatible_defined_list, compatible_undefined_file


##############################################################################
# Handle_DT_EXTRACT_EXAMPLE
##############################################################################
def Handle_DT_EXTRACT_EXAMPLE(list_yaml_files, output_directory_path, dt_extract_example_exec_command):
	
	print("====== Start of dt-extract-example ======")
	
	# list_yaml_files contains list of absoulute path for yaml files
	for files in list_yaml_files:
		# Input Yaml file
		input_filename = files + YAMLFILE_EXTN
		
		if os.path.isfile(input_filename) != True:
			error_msg = "Filename " + input_filename + " does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
		
		# Output example file name
		output_filename = os.path.basename(files) + EXAMPLE_DTS_EXTN
		output_filename = os.path.join(output_directory_path, output_filename)
		output_filename = "\"" + output_filename + "\""
		
		command="%s %s > %s" % (dt_extract_example_exec_command, input_filename, output_filename)
	
		if args.verbose:
			print("Running [%s]\n" % (command))
		
		# Run command
		return_code = Exec_command(command)
		if return_code != 0:
			error_msg = "dt-extract-example failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
		
	print("====== End of dt-extract-example ======\n")


##############################################################################
# Handle_DT_MK_SCHEMA
##############################################################################
def Handle_DT_MK_SCHEMA(list_yaml_files, pspath, dt_mk_schema_exec_command):
	
	print("====== Start of dt-mk-schema ======")
	
	# Output example file name
	output_filename = pspath
	
	input_filename = ""
	
	# list_yaml_files contains list of absoulute path for yaml files
	for files in list_yaml_files:
		# Check input Yaml file
		check_input_filename = files + YAMLFILE_EXTN
		
		if os.path.isfile(check_input_filename) != True:
			error_msg = "Filename " + check_input_filename + " does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
		
		# Append all input filename
		input_filename = input_filename + " " + check_input_filename
	
	command="%s -o %s %s" % (dt_mk_schema_exec_command, output_filename, input_filename)
	
	if args.verbose:
		print("Running [%s]\n" % (command))
	
	# Run command
	return_code = Exec_command(command)
	if return_code != 0:
		error_msg = "dt-mk-schema failed for [" + input_filename + "]"
		Handle_DT_EXIT(error_msg, args.warning)
	
	print("====== End of dt-mk-schema ======\n")


##############################################################################
# Handle_validate_extracted_example
##############################################################################
def Handle_validate_extracted_example(list_yaml_files, output_directory_path, cpp_command, dtc_command):
	
	global cArg
	global dArg
	
	print("====== Start validation of extracted example ======")
	input_filename = ""
	
	# list_yaml_files contains list of absoulute path for yaml files
	for files in list_yaml_files:
	
		# Step 1: Compile extracted examples
		#######################################################################
		
		# Input extracted example file
		input_filename = os.path.basename(files) + EXAMPLE_DTS_EXTN
		input_filename = os.path.join(output_directory_path, input_filename)
		
		if os.path.isfile(input_filename) != True:
			error_msg = "Error: Filename " + input_filename + " does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
		
		# Output file
		output_filename = os.path.basename(files) + VALIDATE_EXAMPLE_TEMP_EXTN
		output_filename = os.path.join(output_directory_path, output_filename)
		
		command="%s %s -o %s %s" % (cpp_command, cArg, output_filename, input_filename)
	
		if args.verbose:
			print("\nRunning [%s]" % (command))
		
		# Run command
		return_code = Exec_command(command)
		if return_code != 0:
			error_msg = "CPP failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
		
		# Step 2: Run DTC on compiled files above
		#######################################################################
		
		# Get output from cpp
		input_filename = output_filename
		
		output_filename = os.path.basename(files) + EXAMPLE_DT_YAML_EXTN
		output_filename = os.path.join(output_directory_path, output_filename)
		
		command="%s %s -o %s %s" % (dtc_command, dArg, output_filename, input_filename)
		
		if args.verbose:
			print("Running [%s]" % (command))
		
		# Run command
		return_code = Exec_command(command)
		if return_code != 0:
			error_msg = "DTC failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
		
	print("====== End validation of extracted example ======\n")	


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
	global Platform
	
	compatible_defined_list = []
	compatible_undefined_file = []
	
	parser = argparse.ArgumentParser(description='Command-Line Tool to Generate XBL/UEFI DTB Files')
	
	parser.add_argument("-n", "--pythonpath", help="Path for PYTHONPATH Environment variable")
	parser.add_argument("-o", "--output", help="Output Path(folder) for all output and project-schema.yaml files")
	parser.add_argument("-r", "--outfilename", help="Include Name for project-schema file")
	parser.add_argument("-d", "--dtcpath", help="Path for DTC (DeviceTree Compiler) [end with /]")
	parser.add_argument("-p", "--cpppath", help="Path for CPP (C Pre-Processor) [end with /]")
	parser.add_argument("-y", "--schemafilespath", help="Include Path(s) for all .yaml files")
	parser.add_argument("-a", "--cpparg", help="Override CPP argument string")
	parser.add_argument("-s", "--dtcarg", help="Override DTC argument string")
	parser.add_argument("-t", "--dtschematoolspath", help="Include Path(s) for all dt-schema tools")
	parser.add_argument("-w", "--warning", action='store_true', help="Override any Error into Warnings")
	parser.add_argument("-v", "--verbose", action='store_true', help="Enable Verbose Output")
	parser.add_argument("-c", "--cleanbuild", action='store_true', help="Enable Clean build")
	
	args = parser.parse_args()

	Platform = sys.platform

	# Step 1: Handle Command-Line Arguments
	#######################################################################
	
	# Errors can be overriden by Warnings using -w option.
	if args.warning:
		print("\nNote: Warning override initiated! Any error will be overriden to Warnings\n")
	
	# Change the PYTHONPATH environment variable
	pythonpath = ""
	if args.pythonpath and args.pythonpath != "":
		pythonpath = os.path.abspath(args.pythonpath)
		if os.path.exists(pythonpath) == True:
			sys.path.append(pythonpath)
			os.environ["PYTHONPATH"] = pythonpath
		else:
			pythonpath = ""
	
	if pythonpath == "":
		error_msg = "\nNote: Environment variable PYTHONPATH not updated in this execution. PYTHONPATH path can be specified using [-n] command-line parameter"
		print(error_msg)
	
	if args.dtcarg:
		dArg = args.dtcarg
	else:
		dArg = DTC_ARGS
	
	if args.output:
		#output_directory_path, project_schema_basename = os.path.split(args.output)
		output_directory_path = args.output
		if os.path.exists(output_directory_path) != True:
			error_msg = "Output Path path is required/must exist"
			Handle_DT_EXIT(error_msg, args.warning)
			
		output_directory_path = os.path.abspath(output_directory_path)
	else:
		error_msg = "Output (project-schema.yaml) path required using [-o] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if args.outfilename:
		project_schema_basename = args.outfilename
	else:
		error_msg = "Project schema filename (for eg.\"project-schema.yaml\") required using [-r] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
	
	#filename, file_extension = os.path.splitext(project_schema_basename)
	#if file_extension != '.yaml':
	#	error_msg = "*.yaml extension is required for output file [-o]. For example: \"project-schema.yaml\""
	#	Handle_DT_EXIT(error_msg, args.warning)
	
	if args.dtcpath:
		dtc_path = args.dtcpath
	else:
		error_msg = "Include DTC path using [-d] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if args.cpparg:
		cArg = args.cpparg
	else:
		cArg = CPP_ARGS
	
	if args.cpppath:
		cpp_path = args.cpppath
	else:
		error_msg = "Include CPP path using [-p] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
			
	if args.cleanbuild:
		clean_build = 1
	else:
		clean_build = 0
	
	dtschema_tools_path = ""
	if args.dtschematoolspath:
		dtschema_tools_path = args.dtschematoolspath
		
		if os.path.exists(dtschema_tools_path) != True:
			error_msg = "Pathname [" + dtschema_tools_path + "] does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
	else:
		error_msg = "DT-Schema Tools path can be specified using [-t] command-line parameter"
	
	if args.schemafilespath:
		sfpath = os.path.abspath(args.schemafilespath)
	else:
		error_msg = "Schema File path must be specified using [-y] command-line parameter"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if os.path.exists(sfpath) != True:
		error_msg = "Pathname [" + sfpath + "] does not exist"
		Handle_DT_EXIT(error_msg, args.warning)
	
	print("\nSchema files are located in: [%s]\n" % (sfpath))
	
	# Step 2: Create Project-schema.yaml's absoulute path
	#######################################################################
	pspath = os.path.join(output_directory_path, project_schema_basename)
	
	# Step 3: Set the DT-schema tools path in Windows and Linux
	#######################################################################
	dt_doc_validate_exec_command = os.path.join(dtschema_tools_path, DT_DOC_VALIDATE_EXEC)
	dt_extract_example_exec_command = os.path.join(dtschema_tools_path, DT_EXTRACT_EXAMPLE_EXEC)
	dt_mk_schema_exec_command = os.path.join(dtschema_tools_path, DT_MK_SCHEMA_EXEC)
	dt_validate_exec_command = os.path.join(dtschema_tools_path, DT_VALIDATE_EXEC)
	
	print_buffer = "Python Version: " + platform.python_version()
	print(print_buffer)
	python_installed_scripts_path = ""
	
	if platform.system() == "Windows":
		python_installed_scripts_path = os.path.abspath(os.path.join(sys.executable, '..'))
		python_installed_scripts_path = os.path.join(python_installed_scripts_path, 'Scripts')
	
	if os.path.exists(dt_doc_validate_exec_command) != True:
		error_msg = "Filename [" + dt_doc_validate_exec_command + "] does not exist"
		dt_doc_validate_exec_command = DT_DOC_VALIDATE_EXEC
		if platform.system() == "Windows":
			dt_doc_validate_exec_command = PYTHON + " " + Get_tools_path(args, python_installed_scripts_path, dt_doc_validate_exec_command)
	else:
		dt_doc_validate_exec_command = PYTHON +" " + dt_doc_validate_exec_command
	
	if os.path.exists(dt_extract_example_exec_command) != True:
		error_msg = "Filename [" + dt_extract_example_exec_command + "] does not exist"
		dt_extract_example_exec_command = DT_EXTRACT_EXAMPLE_EXEC
		if platform.system() == "Windows":
			dt_extract_example_exec_command = PYTHON + " " + Get_tools_path(args, python_installed_scripts_path, dt_extract_example_exec_command)
	else:
		dt_extract_example_exec_command = PYTHON + " " + dt_extract_example_exec_command
	
	if os.path.exists(dt_mk_schema_exec_command) != True:
		error_msg = "Filename [" + dt_mk_schema_exec_command + "] does not exist"
		dt_mk_schema_exec_command = DT_MK_SCHEMA_EXEC
		if platform.system() == "Windows":
			dt_mk_schema_exec_command = PYTHON + " " + Get_tools_path(args, python_installed_scripts_path, dt_mk_schema_exec_command)
	else:
		dt_mk_schema_exec_command = PYTHON + " " + dt_mk_schema_exec_command
	
	if os.path.exists(dt_validate_exec_command) != True:
		error_msg = "Filename [" + dt_validate_exec_command + "] does not exist"
		dt_validate_exec_command = DT_VALIDATE_EXEC
		if platform.system() == "Windows":
			dt_validate_exec_command = PYTHON + " " + Get_tools_path(args, python_installed_scripts_path, dt_validate_exec_command)
	else:
		dt_validate_exec_command = PYTHON + " " + dt_validate_exec_command

	# Step 4: Set up CPP & DTC Compilers
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
	
	
	# Step 5: Make list of all yaml files '.yaml' extension
	#######################################################################
	list_yaml_files = Get_list_yaml_files(sfpath)
	
	# Step 6: Initiate a clean build. Remove all stale generated files
	#######################################################################
	if clean_build:
		Handle_Clean(output_directory_path, pspath, sfpath)
	
	# Step 7: Remove all stale log files
	#######################################################################
	Clean_log_file(output_directory_path, os.path.splitext(os.path.basename(__file__))[0], args)
	
	# Step 8: Call dt-doc-validate for all yaml files and store compatbile
	#         string in a file at a location (where project-schema.yaml is 
	#         also present)
	#######################################################################
	compatible_defined_list, compatible_undefined_file = Handle_DT_DOC_VALIDATE(list_yaml_files, 
															dt_doc_validate_exec_command, 
															output_directory_path)
	
	# Step 9: Extract examples using dt-extract-example from all yaml files
	#######################################################################
	Handle_DT_EXTRACT_EXAMPLE(list_yaml_files, output_directory_path, dt_extract_example_exec_command)
	
	# Step 10: Generate pre-processes Project Schema file
	#######################################################################
	Handle_DT_MK_SCHEMA(list_yaml_files, pspath, dt_mk_schema_exec_command)
	
	# Step 11: Validate the extracted examples
	#######################################################################
	Handle_validate_extracted_example(list_yaml_files, output_directory_path, cpp_command, dtc_command)
	
	# Step 12: Validate extracted examples against pre-processed Project Schema file
	#################################################################################
	
	# Modified dt-validate return list of compatbile strings. Ignore the returned list
	# for qc_dt_schema_check_tool (this file). Thus, VALIDATE_COMPATIBLE_STRING_FROM_DT_VALIDATE
	# has been set to 0x0
	# Ignore the returned set for the script #1 (i.e. current file).
	Handle_DT_VALIDATE(list_yaml_files, output_directory_path,
						dt_validate_exec_command,
						pspath, EXAMPLE_DT_YAML_EXTN, 
						args, STRING_TO_DISPLAY,
						VALIDATE_COMPATIBLE_STRING_FROM_DT_VALIDATE)
	
	# TODO: When all the YAML files are up-to-date, move this to error
	# message (error_msg) and use HANDLE_DT_EXIT(). Handle this error
	# in Handle_DT_DOC_VALIDATE(). The below section should throw  error
	# in future.
	if len(compatible_undefined_file):
		error_msg = ("\n**** WARNING: %s Discrepancies found ****" % (len(compatible_undefined_file)))
		error_msg += "\nFollowing YAML files are not defined properly or has compatible string missing:\n"
		for cuf in compatible_undefined_file:
			error_msg += (" - ...%s\n" %(cuf[cuf.find("boot_images"):]))
		
		# todo: remove print and uncomment (HANDLE_DT_EXIT) in future
		print(error_msg)
		#HANDLE_DT_EXIT(error_msg, args.warning)
	
	# Step 13: Store the compatible string in log file for qc_dt_check (script #2) to access it
	#################################################################################
	
	store_compatible_string = ""
	for cdl in compatible_defined_list:
		store_compatible_string += cdl + "\n"
	
	# Step 14: Create an output text file
	#######################################################################
	try:
		Create_log_file(list_yaml_files, 
						output_directory_path, 
						os.path.splitext(os.path.basename(__file__))[0], 
						YAMLFILE_EXTN,
						store_compatible_string,
						args)
	except:
		error_msg = "Error in final Log file creation"
		Handle_DT_EXIT(error_msg, args.warning)
	
	sys.exit(RETURN_SUCCESS)
	
	#print("\n****** End of qc_dt_schema_check ******\n")

main()
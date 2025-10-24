#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.

import argparse
import os
import sys
import platform
import subprocess as sp
import imp

RETURN_SUCCESS = 0
RETURN_ERROR = -1

#Log file name extension
LOG_EXTENSION = ".log"

LINUX_DELETE = "rm"
WINDOWS_DELETE = "del"

##############################################################################
# Handle_DT_VALIDATE
##############################################################################
def Handle_DT_VALIDATE(list_dts_files,
						output_directory_path,
						dt_validate_exec_command, 
						pspath, 
						find_file_extn, 
						args, 
						string_to_display,
						store_returned_compatible_list):
	
	print("\n\n########## Start of %s ##########\n\n" %(string_to_display))
	
	current_directory = os.path.dirname(os.path.abspath(__file__))
	
	# import the modified dt-validate script
	DTV = imp.load_source('dt-validate', os.path.join(current_directory,'dt-validate'))
	
	compatible_string_set = set()
	
	if os.path.isfile(pspath) != True:
		error_msg = "Filename " + pspath + " does not exist"
		Handle_DT_EXIT(error_msg, args.warning)
			
	# list_dts_files contains list of absoulute path for yaml files
	for files in list_dts_files:
		# Input Yaml file
		input_filename = os.path.basename(files) + find_file_extn
		input_filename = os.path.join(output_directory_path, input_filename)
		
		if os.path.isfile(input_filename) != True:
			error_msg = "Filename " + input_filename + " does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
		
		list_args = []
		list_args.append("-p")
		list_args.append(pspath)
		list_args.append(input_filename)
		
		return_code, compatible_string_list_return = DTV.main(list_args)
		
		if return_code != 0:
			error_msg = "dt-validate failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
		
		# ignore storing compatible string in file if it is set to 0x0
		# Storing the compatbile string in a set and return it
		if store_returned_compatible_list != 0:
			# remove the first compatible string for root node
			compatible_string_list_return.pop(0)
			for cslr in compatible_string_list_return:
				compatible_string_set.add(cslr)
	
	print("\n########## End of Validation ##########\n\n")
	return compatible_string_set

##############################################################################
# Get_tools_path
##############################################################################
def Get_tools_path(args, python_installed_scripts_path, tool_exec_command):
	python_installed_scripts_path = os.path.join(python_installed_scripts_path, tool_exec_command)
	if platform.system() == "Windows":
		if os.path.exists(python_installed_scripts_path) != True:
			error_msg = "Tool [" + tool_exec_command + "] does not exist. Need to install DTSchema requirements [pip3 install -r requirements.txt]"
			Handle_DT_EXIT(error_msg, args.warning)
	return python_installed_scripts_path
	
##############################################################################
# Handle_DT_EXIT
##############################################################################
def Handle_DT_EXIT(error_msg, warning):
	
	if warning:
		error_msg = "Warning: " + error_msg
		print(error_msg)
	else:
		error_msg = "Error: " + error_msg
		sys.exit("%s\n" % (error_msg))

	sys.exit()

##############################################################################
# Create_log_file
##############################################################################
def Create_log_file(list_files, output_directory_path, output_filename, file_extn, store_message, args):
	print_msg = ""
	for list_file in list_files:
		print_msg = print_msg + str(list_file) + file_extn + "\n"
	
	print_msg = print_msg +  "\nFiles above have been validated"
	output_filename = output_filename + LOG_EXTENSION
	output_filename = os.path.join(output_directory_path, output_filename)
	if platform.system() == "Windows":
		#output_filename = output_filename + '+'
		command = "copy nul " + output_filename
	else:
		command = "touch " + output_filename
	
	if args.verbose:
		print("\nRunning [%s]\n" % (command))
	
	return_code = Exec_command(command)
	if return_code:
		error_msg = "error generating log file [" + output_filename + "]"
		Handle_DT_EXIT(error_msg, args.warning)
	
	try:
		f = open(output_filename, "w")
		f.write("%s\n" % (store_message))
		f.close()
	except:
		error_msg = "error writing to log file [" + output_filename + "]"
		Handle_DT_EXIT(error_msg, args.warning)
	
	if args.verbose:
		print("\nOutput Log file generated \n")

##############################################################################
# Create_log_file
##############################################################################
def Clean_log_file(output_directory_path, output_filename, args):
	
	output_filename = output_filename + LOG_EXTENSION
	output_filename = os.path.join(output_directory_path, output_filename)
	
	if os.path.exists(output_filename) == True:
		if platform.system() == "Windows":
			delete_command = WINDOWS_DELETE
		else:
			delete_command = LINUX_DELETE
		
		command="%s %s" % (delete_command, output_filename)
		
		if args.verbose:
			print("\nRunning [%s]\n" % (command))

		# Run command
		return_code = Exec_command(command)
		
		if return_code != 0:
			error_msg = "Cleaning Log file failed [" + output_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
	else:
		if args.verbose:
			print("\nLog file does not exists. Continuing \n")
	
##############################################################################
# Exec_command
##############################################################################
def Exec_command(command):
	return sp.call(command, shell=True)

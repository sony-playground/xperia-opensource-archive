#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.

import argparse
import os
import sys
import platform
import subprocess as sp

RETURN_SUCCESS = 0
RETURN_ERROR = -1

##############################################################################
# Handle_DT_VALIDATE
##############################################################################
def Handle_DT_VALIDATE(list_dts_files, 
						dt_validate_exec_command, 
						pspath, 
						find_file_extn, 
						args, 
						string_to_display):
	
	print("\n\n########## Start of %s ##########\n\n" %(string_to_display))
	
	if os.path.isfile(pspath) != True:
		error_msg = "Filename " + pspath + " does not exist"
		Handle_DT_EXIT(error_msg, args.warning)
			
	# list_dts_files contains list of absoulute path for yaml files
	for files in list_dts_files:
		# Input Yaml file
		input_filename = files + find_file_extn
		
		
		if os.path.isfile(input_filename) != True:
			error_msg = "Filename " + input_filename + " does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
		
		command="%s -p %s %s" % (dt_validate_exec_command, pspath, input_filename)
		
		if args.verbose:
			print("\nRunning [%s]\n" % (command))

		# Run command
		return_code = Exec_command(command)
		
		if return_code != 0:
			error_msg = "dt-validate failed for [" + input_filename + "]"
			Handle_DT_EXIT(error_msg, args.warning)
		
	print("\n########## End of Validation ##########\n\n")

##############################################################################
# Get_tools_path
##############################################################################
def Get_tools_path(python_installed_scripts_path, tool_exec_command):
	python_installed_scripts_path = os.path.join(python_installed_scripts_path, tool_exec_command)
	if platform.system() == "Windows":
		if os.path.exists(python_installed_scripts_path) != True:
			error_msg = "Tool [" + tool_exec_command + "] does not exist"
			Handle_DT_EXIT(error_msg, args.warning)
	return python_installed_scripts_path
	
##############################################################################
# Handle_DT_EXIT
##############################################################################
def Handle_DT_EXIT(error_msg, warning):
	
	if warning:
		error_msg = "Warning: " + error_msg
		exit_code = RETURN_SUCCESS
	else:
		error_msg = "Error: " + error_msg
		exit_code = RETURN_ERROR
	
	print(error_msg)
	sys.exit(exit_code)

##############################################################################
# Exec_command
##############################################################################
def Exec_command(command):
	return sp.call(command, shell=True)

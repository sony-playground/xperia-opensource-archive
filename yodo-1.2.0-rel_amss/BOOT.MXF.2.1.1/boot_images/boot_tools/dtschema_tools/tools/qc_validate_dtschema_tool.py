#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.

# -z : Workspace path
# -y : Path to your YAML tree
# -u : DTS file path
# -f : force output

"""Dt-schema interactive script.

This script is used to validate both YAML and DTS/DTSI files.

This script has two required arguments that are needed for the script to execute:
	* -s <target>. This argument is required for the script to determine which target's DTS files need to be validated.
	* -w <workspace>. This argument is required for the script to differentiate between different families. The supported values are: "boot" (for core.boot) and "Q6" (for core.qdsp, core.mpss)

There is an optional argument for Q6 as well:
	* -c <config>. This argument is used when running the script in Q6 families to allow the engineer to specify which config tree of DTS files they wish to validate. If the argument isn't given,
	then every DTS file is processed. The values for this argument are: "adsp", "cdsp", "gpdsp", "mpss".

"""

import argparse
import json
import os
import sys
import platform
from pathlib import Path
from qc_get_paths import PATH_DICT, print_paths


PROJECT_SCHEMA_FILE_NAME = "project-schema"
YAMLFILE_EXTN = ".yaml"
DTS_EXTN = ".dts"
INCLUDE_OPTION = "-I"
VERBOSE_OPTION = "-v"

RETURN_SUCCESS = 0
RETURN_ERROR = 1
INCLUDE_DIRECTORY = "include"

OUTPUT_GENDTB_FOLDER = "gendtb_output_dtb"
OUTPUT_TOOL_FOLDER = "OUTPUT_TOOL"
OUTPUT_QC_DT_SCHEMA_CHECK_FOLDER = "qc_dt_schema_check"
OUTPUT_QC_DT_CHECK_FOLDER = "qc_dt_check"


def update_workspace_path(dict, path_key, pathname_string):
	input_path = input("Enter the path for %s: " % (pathname_string))
	if os.path.exists(input_path) != True:
		error_msg = "WARNING: Workspace path [" + input_path + "] does not exist"
		print(error_msg)
	else:
		print("Updating %s" % (pathname_string))
		dict[path_key] = input_path


def common_path_define(dict):
	global toolchain_data
	retval = RETURN_ERROR
	
	qcdtschemacheckpath = PATH_DICT['qc_dt_schema_check_path']
	qcdtcheckpath = PATH_DICT['qc_dt_check_path']
	dtcpath = PATH_DICT['dtcpath']
	dtschematoolspath = PATH_DICT['dt_schema_tools_path']
	cpppath = PATH_DICT['cpppath']
	gendtbpath = PATH_DICT['gendtbpath']
		
	if os.path.exists(dict['workspacepath']) != True:
		error_msg = "Error: Workspace Path [" + dict['workspacepath'] + "] does not exist"
		print(error_msg)
	elif os.path.exists(qcdtschemacheckpath) != True:
		error_msg = "Error: Tool qc_dt_schema_check Path [" + qcdtschemacheckpath + "] does not exist"
		print(error_msg)
	elif os.path.exists(qcdtcheckpath) != True:
		error_msg = "Error: Tool qc_dt_check Path [" + qcdtcheckpath + "] does not exist"
		print(error_msg)
	elif os.path.exists(dtcpath) != True:
		error_msg = "Error: DTC tool Path [" + dtcpath + "] does not exist"
		print(error_msg)
	elif os.path.exists(dtschematoolspath) != True:
		error_msg = "Error: DTSchematools Path [" + dtschematoolspath + "] does not exist"
		print(error_msg)
	elif os.path.exists(cpppath) != True:
		error_msg = "Error: CPP tool Path [" + cpppath + "] does not exist"
		print(error_msg)
	elif os.path.exists(gendtbpath) != True:
		error_msg = "Error: gendtb tool Path [" + gendtbpath + "] does not exist"
		print(error_msg)
	else:
		retval = RETURN_SUCCESS
		dict['qcdtschemacheckpath'] = qcdtschemacheckpath
		dict['qcdtcheckpath'] = qcdtcheckpath
		dict['dtcpath'] = dtcpath
		dict['dtschematoolspath'] = dtschematoolspath
		dict['cpppath'] = cpppath
		dict['gendtbpath'] = gendtbpath

	
	
	return retval


def exec_qc_dt_schema_check(dict):
	

	if common_path_define(dict) == RETURN_ERROR:
		return
	
	output_qc_dt_schema_check_directory = os.path.join(dict['output_directory'], OUTPUT_QC_DT_SCHEMA_CHECK_FOLDER)
	
	if os.path.exists(output_qc_dt_schema_check_directory) != True:
		print(" Creating qc_dt_check OUTPUT directory %s" % (output_qc_dt_schema_check_directory))
		os.mkdir(output_qc_dt_schema_check_directory)
	else:
		print(" qc_dt_check OUTPUT Directory exists: %s" % (output_qc_dt_schema_check_directory))
	command_qcdtschemacheck = ""
	
	if platform.system() == "Windows":
		command_qcdtschemacheck="python %s -d %s -y %s -t %s -p %s -o %s -r %s -w -c" % (dict['qcdtschemacheckpath'],
																				dict['dtcpath'], 
																				dict['yamlpath'], 
																				dict['dtschematoolspath'], 
																				dict['cpppath'],
																				output_qc_dt_schema_check_directory,
																				PROJECT_SCHEMA_FILE_NAME + YAMLFILE_EXTN)
		if dict['workspace'] == "boot":
			command_qcdtschemacheck += append_all_params_json(
													toolchain_data['ToolChain']['qc_dt_schema_check']['Windows'], 
													"Params")
	
	else:
		command_qcdtschemacheck="chmod +x %s && python %s -d %s -y %s -t %s -p %s -o %s -r %s -c -w" % (dict['qcdtschemacheckpath'],
																								dict['qcdtschemacheckpath'], 
																								dict['dtcpath'], 
																								dict['yamlpath'], 
																								dict['dtschematoolspath'], 
																								dict['cpppath'],
																								output_qc_dt_schema_check_directory,
																								PROJECT_SCHEMA_FILE_NAME + YAMLFILE_EXTN)
		
	if dict['verbose']:
		command_qcdtschemacheck = command_qcdtschemacheck + " " + VERBOSE_OPTION

	print ("\n\n========================================================")
	print ("========================================================")
	print ("\t   SCRIPT 1 : RUNNING QC_DT_SCHEMA_CHECK")
	print ("========================================================")
	print ("========================================================\n\n\n")
	print ("Running ", command_qcdtschemacheck)
	
	return_code = os.system(command_qcdtschemacheck)
	
	if return_code != 0:
		print("\nError : SCRIPT 1 failed for [%s]" % (command_qcdtschemacheck))
		print("YAML File validation FAILED")
	
	print ("\n\n========================================================")
	print ("========================================================")
	print ("\t   END OF QC_DT_SCHEMA_CHECK")
	print ("========================================================")
	print ("========================================================\n\n\n")


def exec_qc_dt_check(dict):
	
	if common_path_define(dict) == RETURN_ERROR:
		return
	
	output_gendtb_directory = os.path.join(dict['output_directory'], OUTPUT_GENDTB_FOLDER)
	output_qc_dt_check_directory = os.path.join(dict['output_directory'], OUTPUT_QC_DT_CHECK_FOLDER)

	if os.path.exists(output_gendtb_directory) != True:
		print("\nCreating GENDTB OUTPUT directory %s" % (output_gendtb_directory))
		os.mkdir(output_gendtb_directory)
	else:
		print("\nGENDTB OUTPUT Directory exists: %s" % (output_gendtb_directory))
	
	if os.path.exists(output_qc_dt_check_directory) != True:
		print("\nCreating qc_dt_check OUTPUT directory %s" % (output_qc_dt_check_directory))
		os.mkdir(output_qc_dt_check_directory)
	else:
		print("\nqc_dt_check OUTPUT Directory exists: %s" % (output_qc_dt_check_directory))

	output_gendtb_directory_set, output_qc_dt_check_directory_set = set(), set()

	
	# print("\nRunning Gendtb on DTS FILES in %s" % (dict['dtsfilespath']))
	if dts_files_paths_lst:
		files = dts_files_paths_lst
	else:	
		# no dts files are found, exit out
		return
	# move mkdirs to for loop
	# check for config
	for file in files:
		if(file.endswith(DTS_EXTN)):
			if dict['workspace'] == "boot":
				output_gendtb_directory_set.add(output_gendtb_directory)
				output_qc_dt_check_directory_set.add(output_qc_dt_check_directory)
				output_gendtb_path = output_gendtb_directory
			elif dict['workspace'] == "Q6":
				if config_arg:
					config = config_arg
				else:
					config = Path(file).parent.name
				output_gendtb_path = os.path.join(output_gendtb_directory, config)
				output_qc_dt_check_path = os.path.join(output_qc_dt_check_directory, config)
				if not os.path.exists(output_gendtb_path):
					os.mkdir(output_gendtb_path)
				else:
					print("\nGENDTB OUTPUT Directory exists: %s" % (output_gendtb_directory))

				if not os.path.exists(output_qc_dt_check_path):
					os.mkdir(output_qc_dt_check_path)
				else:
					print("\nqc_dt_check OUTPUT Directory exists: %s" % (output_qc_dt_check_directory))
				output_gendtb_directory_set.add(output_gendtb_path)
				output_qc_dt_check_directory_set.add(output_qc_dt_check_path)
		
			#use gendtb before qc_dt_check.py
			command_gendtb = "python %s -f %s -o %s -c %s -d %s -i %s" % \
				(	dict['gendtbpath'], 
					file, 
					output_gendtb_path, 
					dict['cpppath'], 
					dict['dtcpath'], 
					dict['includeArg']
				)
			# if string is not null add -a argument to command_gendtb
			if PATH_DICT["arch"]:
				command_gendtb += " -a " + PATH_DICT["arch"]
			print ("\nRunning [%s]\n" % (command_gendtb))
			return_code = os.system(command_gendtb)
			
			if return_code != 0:
				print("Error : GENDTB Failed [%s]" % (command_gendtb))
				return
	
	projectschemapath = os.path.join(dict['output_directory'], OUTPUT_QC_DT_SCHEMA_CHECK_FOLDER)	
	projectschemapath = os.path.join(projectschemapath, PROJECT_SCHEMA_FILE_NAME + YAMLFILE_EXTN)	
	
	if os.path.exists(projectschemapath) != True:
		error_msg = "Error: Project_schema.yaml Path [" + projectschemapath + "] does not exist"
		print(error_msg)

	command_qcdtcheck = ""
# FOR LOOP START
	for output_gendtb_directory, output_qc_dt_check_directory in zip(output_gendtb_directory_set, output_qc_dt_check_directory_set):

		if platform.system() == "Windows":
			command_qcdtcheck="python %s -d %s -u %s -r %s -t %s -p %s -o %s -w" % (dict['qcdtcheckpath'], 
																					dict['dtcpath'], 
																					output_gendtb_directory, 
																					projectschemapath, 
																					dict['dtschematoolspath'], 
																					dict['cpppath'],
																					output_qc_dt_check_directory)
			if dict['workspace'] == "boot":
				command_qcdtcheck += append_all_params_json(
														toolchain_data['ToolChain']['qc_dt_check']['Windows'], 
														"Params")
		else:
			command_qcdtcheck="chmod +x %s && python %s -d %s -u %s -r %s -t %s -p %s -o %s -w" % (dict['qcdtcheckpath'], 
																									dict['qcdtcheckpath'],
																									dict['dtcpath'], 
																									output_gendtb_directory, 
																									projectschemapath,
																									dict['dtschematoolspath'], 
																									dict['cpppath'],
																									output_qc_dt_check_directory)
	
		if dict['verbose']:
			command_qcdtcheck = command_qcdtcheck + " " + VERBOSE_OPTION
		
		print ("\n\n========================================================")
		print ("========================================================")
		print ("\t   SCRIPT 2 : RUNNING QC_DT_CHECK")
		print ("========================================================")
		print ("========================================================\n\n\n")
		print ("Running ", command_qcdtcheck)
		
		return_code = os.system(command_qcdtcheck)

		if return_code != 0:
			print("Error : SCRIPT 2 failed for [%s]" % (command_qcdtcheck))


# FOR LOOP END


	print ("\n\n========================================================")
	print ("========================================================")
	print ("\t   END OF QC_DT_CHECK")
	print ("========================================================")
	print ("========================================================\n\n\n")

##############################################################################
# remove_json_comments
##############################################################################
def remove_json_comments(source_json_file,dest_json_file):
	dest_json = ""
	source_file_handle = open(source_json_file,"r")
	for line in source_file_handle:
		if line.lstrip().startswith("#"):
			dest_json += "\n"
			continue
		temp=line.split()
		if len(temp)==0:
			dest_json += "\n"
			continue
		else:
			dest_json += line.split("#")[0].strip("\n")
			dest_json += "\n"
	source_file_handle.close()
	return dest_json

def append_all_params_json(loaded_json_data, check_for):
	append_string = " "
	
	
	if check_for in loaded_json_data:
		for f in loaded_json_data[check_for]:
			append_string += f + " "
	
	return append_string
	

##############################################################################
# main
##############################################################################
def main():
	global Platform
	global toolchain_data
	Platform = sys.platform
	
	parser = argparse.ArgumentParser(description='Command-Line Tool to validate YAML and DT files')
	
	parser.add_argument("-s", "--target", help="SOC/Target name.")
	parser.add_argument("-i", "--include", help="Include Path(s) for DTSI files (include -I).", nargs='+')
	parser.add_argument("-v", "--verbose", action='store_true', help="Enable Verbose Output. Will print out paths.")
	# for future options
	parser.add_argument("-f", "--forceoutput", action='store_true', help="Print the forced output")
	parser.add_argument("-c", "--config", help="Optional filter to filter specific trees of dts/dtsi files", choices={"adsp", "cdsp", "gpdsp", "mpss"})
	# choices here as an array, for config
	
	args = parser.parse_args()
	# Create a dictionary
	#######################################################################
	dict = {'workspacepath' : '',
			'yamlpath' : '',
			'dtsfilespath' : '',
			'verbose' : '',
			'target' : '',
			'workspace': ''}
	
	print ("\n")
	
	dict['workspacepath'] = PATH_DICT["workspacepath"]		
	
	# Step 1: Handle Command-Line Arguments
	#######################################################################

	if args.target:
		dict['target'] = args.target
	else:
		error_msg = "Error: TARGET/SOC required using -s option. Exiting"
		sys.exit(error_msg)
	
	if PATH_DICT["arch"] == "arm":
		dict['workspace'] = "boot"
	elif PATH_DICT["arch"] == "hexagon":
		dict['workspace'] = "Q6"

	if dict['workspace'] == "boot":
		toolchain_json_file = PATH_DICT["toolchainpath"]

		if os.path.exists(toolchain_json_file) != True:
			error_msg = "WARNING: JSON [" + toolchain_json_file + "] does not exist"
			print(error_msg)

		toolchain_data = json.loads(remove_json_comments(toolchain_json_file, None))

	
	#######################################################################

	yamlpath = PATH_DICT["yamlpath"]

	if os.path.exists(yamlpath) != True:
		error_msg = "WARNING: YAML path [" + yamlpath + "] does not exist"
		print(error_msg)
		yamlpath = ""
	
	dict['yamlpath'] = yamlpath
	dts_path = Path(PATH_DICT['dtspath'])
	target = Path(dict['target'])
	global dts_files_paths_lst, config_arg
	dts_files_paths_lst = []
	config_arg = ""
	if args.config:
		config_arg = args.config
		dtsfilespath = os.path.join(dict['workspacepath'], dts_path, target, config_arg)
		for file in os.listdir(dtsfilespath):
			dts_files_paths_lst.append(os.path.join(dtsfilespath, file))
	else:
		dtsfilespath = os.path.join(dict['workspacepath'], dts_path, target)
		if dict['workspace'] == "Q6":
			for root, dirs, files in os.walk(dtsfilespath):
				for file in files:
					if file.endswith(DTS_EXTN) and OUTPUT_TOOL_FOLDER not in root:
						dts_files_paths_lst.append(os.path.join(root, file))
		else:
			for file in os.listdir(dtsfilespath):
				if(file.endswith(DTS_EXTN)):
					dts_files_paths_lst.append(os.path.join(dtsfilespath, file))

	# else then we need to look through all the folders for dts files
		
	#######################################################################
	
	if os.path.exists(dtsfilespath) != True:
		error_msg = "WARNING: Device tree path [" + dtsfilespath + "] does not exist"
		sys.exit(error_msg)
		
	dict['dtsfilespath'] = dtsfilespath
		
	if args.forceoutput:
		forceoutput = 1
	else:
		forceoutput = 0
	
	verbose = args.verbose
	
	dict['verbose'] = verbose
	if dict['verbose']:
		print_paths()
	includeArg = ""
	
	dict['output_directory'] = os.path.join(dict['dtsfilespath'], OUTPUT_TOOL_FOLDER)
	
	if os.path.exists(dict['output_directory']) != True:
		print("\nCreating OUTPUT Tool directory %s" % (dict['output_directory']))
		os.mkdir(dict['output_directory'])
	else:
		print("\nOUTPUT Tool  Directory exists: %s" % (dict['output_directory']))
	

	if dict['workspacepath'] != "":
		global INCLUDE_DIRECTORY
		common_include_path = PATH_DICT["dtspath"]
		if dict['workspace'] == "boot":
			INCLUDE_DIRECTORY = INCLUDE_DIRECTORY.capitalize()
		if args.include:
			includeArg = args.include
		else:
			includeArg = os.path.join(dict['workspacepath'], common_include_path, dict['target'], INCLUDE_DIRECTORY)
			includeArg = includeArg + " " + os.path.join(dict['workspacepath'], common_include_path, INCLUDE_DIRECTORY)
			includeArg = includeArg + " " + os.path.join(dict['workspacepath'], common_include_path, dict['target'])

	dict['includeArg'] = "\"" + includeArg + "\""
	
	while True:
		print("\n========================================")
		print("\nCURRENT CONFIGURATION:")
		print("- TARGET/SOC: \t\t%s" %(dict['target']))
		print("- WORKSPACE: \t\t%s" % (dict['workspacepath']))
		print("- YAML FILE PATH: \t%s" % (dict['yamlpath']))
		print("- DTS FILE PATH: \t%s" % (dict['dtsfilespath']))
		print("- VERBOSE: \t\t%s" % (dict['verbose']))
		
		print("\n\n  ****** MENU ****** ")
		print("  1. Validate YAML file (create project-schema file)")
		print("  2. Validate DTSI file against project-schema (created in #1)")
		print("  0. Exit")
		try:
			choice = int(input("  Enter your choice: "))
		except ValueError:
			print("\n  Wrong Option. Enter Again")
			continue
		
		if choice == 1:
			exec_qc_dt_schema_check(dict)
		elif choice == 2:
			exec_qc_dt_check(dict)
		elif choice == 0:
			break
		else:
			print("\n  Invalid choice")
	
	print("\n\n****** End of qc_run_qc_dt_schema_check ******\n")

main()
#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.

# -z : Workspace path
# -y : Path to your YAML tree
# -u : DTS file path
# -f : force output

import argparse
import os
import sys
import platform


DEFAULT_WINDOWS_YAML_PATH = "\\boot_images\\boot\\Settings\\dtschema\\Common\\Core"
DEFAULT_LINUX_YAML_PATH = "/boot_images/boot/Settings/dtschema/Common/Core"

DEFAULT_WINDOWS_DTS_PATH = "\\boot_images\\boot\\Settings\\"
DEFAULT_LINUX_DTS_PATH = "/boot_images/boot/Settings/"

PYTHONPATH_WINDOWS_PATH = "\\boot_images\\boot_tools\\dtschema_tools\\Linux\\site_packages"
PYTHONPATH_LINUX_PATH = "/boot_images/boot_tools/dtschema_tools/Linux/site_packages"

QC_DT_SCHEMA_CHECK_WINDOWS_PATH = "\\boot_images\\boot_tools\\dtschema_tools\\bin\\qc_dt_schema_check.py"
QC_DT_SCHEMA_CHECK_LINUX_PATH = "/boot_images/boot_tools/dtschema_tools/bin/qc_dt_schema_check.py"

QC_DT_CHECK_WINDOWS_PATH = "\\boot_images\\boot_tools\\dtschema_tools\\bin\\qc_dt_check.py"
QC_DT_CHECK_LINUX_PATH = "/boot_images/boot_tools/dtschema_tools/bin/qc_dt_check.py"

DTC_WINDOWS_PATH = "C:\\Apps\\DTC"
DTC_LINUX_PATH = "/pkg/qct/software/boottools"

DTSCHEMA_TOOLS_WINDOWS_PATH = "\\boot_images\\boot_tools\\dtschema_tools\\bin"
DTSCHEMA_TOOLS_LINUX_PATH = "/boot_images/boot_tools/dtschema_tools/bin"

CPP_WINDOWS_PATH = "C:\\Apps\\LLVM\\12.0.3\\bin"
CPP_LINUX_PATH = "/pkg/qct/software/llvm/release/arm/12.0.3/bin"

DEFAULT_INCLUDE_PATH_WINDOWS = "\\boot_images\\boot\\Settings\\"

DEFAULT_INCLUDE_PATH_LINUX = "/boot_images/boot/Settings/"

GENDTB_PATH_WINDOWS = "\\boot_images\\boot\\Settings\\Tools\\gendtb.py"
GENDTB_PATH_LINUX =   "/boot_images/boot/Settings/Tools/gendtb.py"

PROJECT_SCHEMA_FILE_NAME = "project-schema"
YAMLFILE_EXTN = ".yaml"
DTS_EXTN = ".dts"
INCLUDE_OPTION = "-I"
VERBOSE_OPTION = "-v"

RETURN_SUCCESS = 0
RETURN_ERROR = 1
INCLUDE_DIRECTORY = "Include"

OUTPUT_DTB_FOLDER = "OUTPUT_DTB"


def update_workspace_path(dict, path_key, pathname_string):
	input_path = input("Enter the path for %s: " % (pathname_string))
	if os.path.exists(input_path) != True:
		error_msg = "WARNING: Workspace path [" + input_path + "] does not exist"
		print(error_msg)
	else:
		print("Updating %s" % (pathname_string))
		dict[path_key] = input_path


def common_path_define(dict):
	retval = RETURN_ERROR
	
	if platform.system() == "Windows":
		qcdtschemacheckpath = os.path.join(dict['workspacepath'] + QC_DT_SCHEMA_CHECK_WINDOWS_PATH)
		qcdtcheckpath = os.path.join(dict['workspacepath'] + QC_DT_CHECK_LINUX_PATH)
		pythonpathenv = os.path.join(dict['workspacepath'] + PYTHONPATH_WINDOWS_PATH)
		dtcpath = os.path.abspath(DTC_WINDOWS_PATH)
		dtschematoolspath = os.path.join(dict['workspacepath'] + DTSCHEMA_TOOLS_WINDOWS_PATH)
		cpppath = os.path.abspath(CPP_WINDOWS_PATH)
		gendtbpath = os.path.join(dict['workspacepath'] + GENDTB_PATH_WINDOWS)
	else:
		qcdtschemacheckpath = os.path.join(dict['workspacepath'] + QC_DT_SCHEMA_CHECK_LINUX_PATH)
		qcdtcheckpath = os.path.join(dict['workspacepath'] + QC_DT_CHECK_LINUX_PATH)
		pythonpathenv = os.path.join(dict['workspacepath'] + PYTHONPATH_LINUX_PATH)
		dtcpath = os.path.abspath(DTC_LINUX_PATH)
		dtschematoolspath = os.path.join(dict['workspacepath'] + DTSCHEMA_TOOLS_LINUX_PATH)
		cpppath = os.path.abspath(CPP_LINUX_PATH)
		gendtbpath = os.path.join(dict['workspacepath'] + GENDTB_PATH_LINUX)
	
	if os.path.exists(pythonpathenv) != True:
		pythonpathenv = ""
		
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
		error_msg = "Error: CPP tool Path [" + gendtbpath + "] does not exist"
		print(error_msg)
	else:
		retval = RETURN_SUCCESS
		dict['qcdtschemacheckpath'] = qcdtschemacheckpath
		dict['qcdtcheckpath'] = qcdtcheckpath
		dict['pythonpathenv'] = pythonpathenv
		dict['dtcpath'] = dtcpath
		dict['dtschematoolspath'] = dtschematoolspath
		dict['cpppath'] = cpppath
		dict['gendtbpath'] = gendtbpath
	
	return retval


def exec_qc_dt_schema_check(dict):

	if common_path_define(dict) == RETURN_ERROR:
		return
	
	if platform.system() == "Windows":
		command_qcdtschemacheck="python %s -n %s -d %s -y %s -t %s -p %s -c -w" % (dict['qcdtschemacheckpath'], 
																				dict['pythonpathenv'], 
																				dict['dtcpath'], 
																				dict['yamlpath'], 
																				dict['dtschematoolspath'], 
																				dict['cpppath'])
	else:
		command_qcdtschemacheck="chmod +x %s && python %s -n %s -d %s -y %s -t %s -p %s -c -w" % (dict['qcdtschemacheckpath'],
																								dict['qcdtschemacheckpath'], 
																								dict['pythonpathenv'], 
																								dict['dtcpath'], 
																								dict['yamlpath'], 
																								dict['dtschematoolspath'], 
																								dict['cpppath'])
	
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
	output_directory = os.path.join(dict['dtsfilespath'], OUTPUT_DTB_FOLDER)
	if os.path.exists(output_directory) != True:
		print(" Creating OUTPUT directory %s" % (output_directory))
		os.mkdir(output_directory)
	else:
		print(" OUTPUT Directory exists: %s" % (output_directory))
	
	if platform.system() == "Windows":
		output_directory += "\\"
	else:
		output_directory += "/"
	
	print("Running Gendtb on DTS FILES in %s" % (dict['dtsfilespath']))
	files = os.listdir(dict['dtsfilespath'])
	for file in files:
		if(file.endswith(DTS_EXTN)):
			input_filename = os.path.join(dict['dtsfilespath'], file)
			
			#use gendtb before qc_dt_check.py
			command_gendtb = "python %s -f %s -o %s -c %s -d %s -i %s " % \
				(	dict['gendtbpath'], 
					input_filename, 
					output_directory, 
					dict['cpppath'], 
					dict['dtcpath'], 
					dict['includeArg'] 
				)
			print ("\nRunning [%s]\n" % (command_gendtb))
			return_code = os.system(command_gendtb)
			
			if return_code != 0:
				print("Error : GENDTB Failed [%s]" % (command_gendtb))
				return
		
	projectschemapath = os.path.join(dict['yamlpath'],'..')
	if os.path.exists(projectschemapath) != True:
		error_msg = "Error: Project_schema.yaml Path [" + projectschemapath + "] does not exist"
		print(error_msg)
		
	projectschemapath = os.path.join(projectschemapath, PROJECT_SCHEMA_FILE_NAME + YAMLFILE_EXTN)
	if os.path.exists(projectschemapath) != True:
		error_msg = "Error: Project_schema.yaml file [" + projectschemapath + "] does not exist"
		print(error_msg)
	
	if platform.system() == "Windows":
		command_qcdtcheck="python %s -n %s -d %s -u %s -r %s -t %s -p %s -c -w" % (dict['qcdtcheckpath'], 
																				dict['pythonpathenv'], 
																				dict['dtcpath'], 
																				output_directory, 
																				projectschemapath, 
																				dict['dtschematoolspath'], 
																				dict['cpppath'])
	else:
		command_qcdtcheck="chmod +x %s && python %s -n %s -d %s -u %s -r %s -t %s -p %s -c -w" % (dict['qcdtcheckpath'], 
																								dict['qcdtcheckpath'], 
																								dict['pythonpathenv'], 
																								dict['dtcpath'], 
																								output_directory, 
																								projectschemapath,
																								dict['dtschematoolspath'], 
																								dict['cpppath'])

	
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
	
	print ("\n\n========================================================")
	print ("========================================================")
	print ("\t   END OF QC_DT_CHECK")
	print ("========================================================")
	print ("========================================================\n\n\n")


##############################################################################
# main
##############################################################################
def main():
	global Platform
	global includeArg_flag
	includeArg_flag = 0
	Platform = sys.platform
	
	parser = argparse.ArgumentParser(description='Command-Line Tool to validate YAML and DT files')
	
	parser.add_argument("-z", "--workspacepath", help="PATH to workspace. Required for tools at <workspace>/boot_images/boot_tools/dtschema_tools/tools/*")
	parser.add_argument("-s", "--target", help="SOC/Target name.")
	parser.add_argument("-y", "--yamlpath", help="PATH to customized YAML Tree. Default: <workspace>/boot_images/boot/Settings/dtschema/Common/Core")
	parser.add_argument("-u", "--dtsfilespath", help="Include Path(s) for (Tempplate) .dts/dtsi files. Default: <workspace>/boot_images/boot/Settings/<SOC>/Core")
	parser.add_argument("-i", "--include", help="Include Path(s) for DTSI files (include -I). Default: <workspace>/boot_images/boot/Settings/<SOC>/Include,\
	                                                                                           ...Settings/Include, ...<SOC>/Include", nargs='+')
	parser.add_argument("-v", "--verbose", action='store_true', help="Enable Verbose Output")
	# for future options
	parser.add_argument("-f", "--forceoutput", action='store_true', help="Print the forced output")
	
	args = parser.parse_args()
	# Create a dictionary
	#######################################################################
	dict = {'workspacepath' : '',
			'yamlpath' : '',
			'dtsfilespath' : '',
			'verbose' : '',
			'target' : ''}
	
	print ("\n")
	# Step 1: Handle Command-Line Arguments
	#######################################################################
	if args.workspacepath:
		workspacepath = os.path.abspath(args.workspacepath)
		if os.path.exists(workspacepath) != True:
			error_msg = "WARNING: Workspace path [" + workspacepath + "] does not exist. Defaulting to empty"
			print(error_msg)
			workspacepath = ""
	else:
		error_msg = "Error: Workspace path not included (for DTSchema tools) with -z option. Exiting"
		sys.exit(error_msg)
	
	dict['workspacepath'] = workspacepath
	
	#######################################################################
	if args.target:
		dict['target'] = args.target
	else:
		error_msg = "Error: TARGET/SOC required using -s option. Exiting"
		sys.exit(error_msg)
	
	#######################################################################
	
	if args.yamlpath:
		yamlpath = os.path.abspath(args.yamlpath)
	else:
		print ("WARNING: YAML path not included with -y option. Defaulting to workspace's YAML path")
		if dict['workspacepath'] != "":
			if platform.system() == "Windows":
				yamlpath = os.path.abspath(dict['workspacepath'] + DEFAULT_WINDOWS_YAML_PATH)
			else:
				yamlpath = os.path.abspath(dict['workspacepath'] + DEFAULT_LINUX_YAML_PATH)
		else:
			yamlpath = ""
	
	if os.path.exists(yamlpath) != True:
		error_msg = "WARNING: YAML path [" + yamlpath + "] does not exist"
		print(error_msg)
		yamlpath = ""
	
	dict['yamlpath'] = yamlpath
		
	#######################################################################
	
	
	if args.dtsfilespath:
		dtsfilespath = os.path.abspath(args.dtsfilespath)
	else:
		print ("\nWARNING: Device tree path not included with -u option. Defaulting to workspace's DTS file path")
		if dict['workspacepath'] != "":
			if platform.system() == "Windows":
				dtsfilespath = os.path.abspath(dict['workspacepath'] + DEFAULT_WINDOWS_DTS_PATH + dict['target'])
			else:
				dtsfilespath = os.path.abspath(dict['workspacepath'] + DEFAULT_LINUX_DTS_PATH + dict['target'])
		else:
			dtsfilespath = ""
	
	if os.path.exists(dtsfilespath) != True:
		error_msg = "WARNING: Device tree path [" + dtsfilespath + "] does not exist"
		sys.exit(error_msg)
		
	dict['dtsfilespath'] = dtsfilespath
		
	if args.forceoutput:
		forceoutput = 1
	else:
		forceoutput = 0
	
	if args.verbose:
		verbose = True
	else:
		verbose = False
	
	dict['verbose'] = verbose
	includeArg = ""
	
	# include Path only if Another DTS file path is provided
	# else go for default
	if args.dtsfilespath:
		if args.include:
			includeArg_flag = 1
			for includePath in args.include:
				iArg = os.path.abspath(includePath)
				if os.path.exists(iArg) != True:
					error_msg = "Error: Pathname [" + iArg + "] does not exist"
					sys.exit(error_msg)
				
				if args.verbose:
					print("Include for CPP [%s]"%(iArg))
				includeArg = includeArg + INCLUDE_OPTION + " " + iArg + " "
	
	if includeArg_flag == 0:
		if dict['workspacepath'] != "":
			includeArg_flag = 1
			common_include_path = ""
			if platform.system() == "Windows":
				common_include_path = DEFAULT_INCLUDE_PATH_WINDOWS
				includeArg = includeArg + INCLUDE_OPTION + os.path.abspath(dict['workspacepath'] + common_include_path + dict['target'] + "\\" + INCLUDE_DIRECTORY) + " "
				includeArg = includeArg + INCLUDE_OPTION + os.path.abspath(dict['workspacepath'] + common_include_path + INCLUDE_DIRECTORY) + " "
				includeArg = includeArg + INCLUDE_OPTION + os.path.abspath(dict['workspacepath'] + common_include_path + dict['target']) + " "
			else:
				common_include_path = DEFAULT_INCLUDE_PATH_LINUX
				includeArg = includeArg + INCLUDE_OPTION + os.path.abspath(dict['workspacepath'] + common_include_path + dict['target'] + "/" + INCLUDE_DIRECTORY) + " "
				includeArg = includeArg + INCLUDE_OPTION + os.path.abspath(dict['workspacepath'] + common_include_path + INCLUDE_DIRECTORY) + " "
				includeArg = includeArg + INCLUDE_OPTION + os.path.abspath(dict['workspacepath'] + common_include_path + dict['target']) + " "
	
	dict['includeArg'] = "\"" + includeArg + "\""
	print("\n\n\n %s" %(dict['includeArg']))
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
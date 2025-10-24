#!/usr/bin/env python3
#============================================================================

# Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
# Author: Adrian Ong, Boot Summer Intern

"""Path Extraction Tool from Configuration File (Q6 Specific).

This script extracts several paths from config.json that 
are needed to run qc_validate_dtschema_tool.py. Similar paths 
are divided into their own subgroups to easily distinguish between them.

This script contains the following functions:
All the paths returned from the functions below are stored as keys in the PATH_DICT dictionary to be used
in qc_validate_dschema_tool.py.
	* get_workspace_path() - returns the workspace path.
	* get_dts_path() - returns the path to dts files.
	* get_yaml_path() - returns the path to the yaml files.
	* get_gendtb_path() - returns the path to the gendtb tool.
	* get_qc_dt_schema_check_path() - returns the path to the qc_dt_schema_check tool.
	* get_qc_dt_check_path() - returns the path to the qc_dt_check tool.
	* get_dtc_path() - returns the path to the DTC compiler.
	* get_cpp_path() - returns the path to the CPP compiler.
	* pretty_print_json() - prints config.json in a readble format.
	* print_paths() - prints all the extracted paths by looping through each key-value pair in PATH_DICT.

	The functions below will only work if the build command has been run on the current workspace.
	* Q6_get_crmenv() - Locates the CRMEnv.py script and uses it to set environment variables.
	* get_build_cfg_path() - returns the path to the build_cfg.xml file.
	* get_rtos_version() - returns the hexagon_rtos version number to complete the toolchain (hexagon) path.
	* get_image_info() - returns the path to image_info.json, which contains environment variables such as DTC and HEXAGON_ROOT.
	* print_env_vars() - prints the values of the environment variables in the system.
	

config.json documentation:
	All of the paths below are relative to the path of the root of the workspace (starting point for all the paths).
	* root_folder - name of the root folder in given workspace. For Q6, it's *_proc.
	All of the paths below are also relative to the root_folder.
	* dts_path - contains path to the DTS files in the workspace.
	* yaml_path - contains path to the YAML files in the workspace. This path is relative to the dts_path.
	* gendtb - contains the path to the gendtb path. This path is relative to the dts_path.
	* toolspath - contains the path to the dtschema tools.
	* qc_dt_schema_check_path - contains the path to the qc_dt_schema_check tool. This path is relative to the toolspath.
	* qc_dt_check_path - contains the path to the qc_dt_check tool. This path is relative to the toolspath.
	* image_info - contains the path to the image_info.json file created after running build on current workspace. Used to retrieve environment variables for HEXAGON_ROOT and DTC_PATH.
	* build_cfg - contains the path to the build_cfg.xml file created after running build on current workspace. Used to retrieve CPP version number to complete toolchain (hexagon) path.
	and the path to the gendtb tool.

	* arch - string to determine CPP architecture.
"""

import json
import os
import platform
from pathlib import Path, PosixPath
import sys
import xml.etree.ElementTree as ET


PATH_DICT, JSON_DICT = {}, {}
CONFIG, PW_VARIANT = "", ""


def get_workspace_path(dirs: list) -> PosixPath:
	"""
	This function retrieves the path to the user's workspace root directory 
	and returns it as a PosixPath object.
	"""
	for dir in reversed(dirs):
		dir_str = str(dir.stem)
		if ROOT in dir_str:
			return os.path.dirname(dir)


def Q6_get_dts_path() -> Path:
	"""
	This function retrieves the path to the DTSI tree in
	the user's workspace.

	This function indexes the JSON file based on PW_VARIANT and
	the configuration (if applicable)
	"""
	# join the targets and config in the main script
	for path in os.listdir(PATH_DICT['workspacepath']):
		if ROOT in path:
			dtspath = Path(JSON_DICT["PW"]["dts_path"])
			dtsfilespath = os.path.join(PATH_DICT['workspacepath'], Path(path), dtspath)
	return dtsfilespath


def Q6_get_yaml_path() -> Path:
	"""
	This function retrieves the path to the YAML tree in
	the user's workspace.
	"""
	yamlpath = Path(JSON_DICT["PW"]["yaml_path"])
	yamlfilespath = os.path.join(PATH_DICT["dtspath"], yamlpath)
	return yamlfilespath


def Q6_get_gendtb_path() -> Path:
	"""
	This function retrieves the path to the gendtb tool.
	"""
	gendtbpath = Path(JSON_DICT["PW"]["gendtb"])
	final_path = os.path.join(PATH_DICT["dtspath"], gendtbpath)
	return final_path


def Q6_get_tools_path() -> Path:
	"""
	This function retrieves the path to the dtschema tools.
	"""
	for path in os.listdir(PATH_DICT['workspacepath']):
		if ROOT in path:
			toolpath = Path(JSON_DICT["PW"]["tools_path"])
			final_path = os.path.join(PATH_DICT['workspacepath'], Path(path), toolpath)
	return final_path


def Q6_get_qc_dt_schema_check_path() -> Path:
	"""
	This function retrieves the path to the qc_dt_schema_check_path script.
	"""
	toolpath = Path(JSON_DICT["PW"]["qc_dt_schema_check_path"])
	final_path = os.path.join(PATH_DICT["dt_schema_tools_path"], toolpath)
	return final_path


def Q6_get_qc_dt_check_path() -> Path:
	"""
	This function retrieves the path to the qc_dt_check_path script.
	"""
	toolpath = Path(JSON_DICT["PW"]["qc_dt_check_path"])
	final_path = os.path.join(PATH_DICT["dt_schema_tools_path"], toolpath)
	return final_path


def Q6_get_cpp_path() -> Path:
	"""
	This function retrieves the path to the CPP compiler.
	"""
	tools_bin = Path("Tools/bin")
	hexagon = Path(os.environ["HEXAGON_ROOT"])
	cpppath = os.path.join(hexagon, PATH_DICT["rtosversion"], tools_bin)
	return cpppath


def get_arch() -> str:
	"""
	This function retrieves the architecture used for the CPP compiler
	"""
	return JSON_DICT["PW"]["arch"]


def Q6_get_crmenv(tools, env_vars, logger=None) -> None:
	"""
	This function searches for the CRMEnv.py script and uses it to set
	environment variables.

	Code taken from setenv.py, Q6 specific.
	"""
	path_sep = os.pathsep
	crmenv_location = None

	if sys.platform.startswith('win'):
		ntbin_folder = r'\\qcdfs\prj\qct\asw\qctss\windows\bin'
	elif sys.platform.startswith('lin'):
		ntbin_folder = '/pkg/qct/qctss/linux/bin'
	if os.path.isfile(os.path.join('.', 'CRMEnv.py')):
		crmenv_location = '.'
	elif os.path.isfile(os.path.join(ntbin_folder, 'CRMEnv.py')):
		crmenv_location = ntbin_folder
	else:
		path_list = [x.strip() for x in os.environ['PATH'].split(path_sep)]
		for path in path_list:
			if os.path.isfile(os.path.join(path, 'CRMEnv.py')):
				crmenv_location = path
				break

	if crmenv_location:
		sys.path.append(crmenv_location)
	else:
		print("Unable to find CRMEnv.py")
		return
	
	from CRMEnv import CRMEnvironment
	global crmenv_load_path
	crm_environment = CRMEnvironment(tools, env_vars, logger)
	crm_environment.set_env()
	crmenv_load_path = crm_environment.get_load_path()


def Q6_get_build_cfg_path() -> Path:
	"""
	This function gets the path to the build_cfg.xml 
	file that contains the hexagon_rtos_release value.
	"""
	for path in os.listdir(PATH_DICT['workspacepath']):
		if ROOT in path:
			build_cfg_path = JSON_DICT["PW"]["build_cfg"]
			final_path = os.path.join(PATH_DICT["workspacepath"], Path(path), build_cfg_path)
	return final_path


def Q6_get_rtos_version() -> int:
	"""
	This is a helper function that retrieves the most recently overwritten valie
	of the hexagon_rtos_release version number from build_cfg.xml.
	"""
	tree = ET.parse(PATH_DICT["build_cfg"])
	root = tree.getroot()
	rtos_version = [h.text for h in root.findall(".//*hexagon_rtos_release")]

	if rtos_version[-1].lower().find("alpha") >= 0 or rtos_version[-1].lower().find("beta") >= 0 and platform.system() == "Linux":
		os.environ["HEXAGON_ROOT"] = "/pkg/qct/software/hexagon/earlyaccess/volume2"
	return rtos_version[-1].strip()


def Q6_get_image_info(image_info: str) -> Path:
	"""
	This is a helper function that returns the path to the image info json file.
	"""
	for path in os.listdir(PATH_DICT['workspacepath']):
		if ROOT in path:
			image_path = Path(JSON_DICT["PW"]["dts_path"])
			image_path = os.path.join(PATH_DICT['workspacepath'], Path(path), Path(image_info))
	return image_path


def Q6_print_env_vars(env: dict) -> None:
	"""
	This is a helper function that prints out all the environment variables.
	"""
	for e in env:
		print(f"{e}: {env[e]}")


def arm_get_dts_path() -> Path:
	"""
	This function retrieves the path to the DTSI tree in
	the user's workspace.
	"""
	dtspath = Path(JSON_DICT["PW"]["dts_path"])
	dtsfilespath = os.path.join(PATH_DICT['workspacepath'], ROOT, dtspath)
	return dtsfilespath


def arm_get_yaml_path() -> Path:
	"""
	This function retrieves the path to the YAML tree in
	the user's workspace.
	"""
	yamlpath = Path(JSON_DICT["PW"]["yaml_path"])
	yamlfilespath = os.path.join(PATH_DICT["dtspath"], yamlpath)
	return yamlfilespath


def arm_get_toolchain_path() -> Path:
	"""
	This is a helper function to retrieve the path to the
	toolchainconfig json file.
	"""
	toolchain_path = os.path.join(PATH_DICT["workspacepath"], ROOT, Path(JSON_DICT["PW"]["tool_chain_config"]))
	return toolchain_path


def arm_remove_build_root(path: str) -> Path:
	"""
	This function replaces the $BUILDROOT found in various paths in toolchainconfig with the ROOT.
	"""
	return path.replace("$BUILDROOT", ROOT)


def arm_get_gendtb_path() -> Path:
	"""
	This function retrieves the path to the gendtb tool.
	"""
	if platform.system() == "Windows":
		gendtbpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["Gendtb"]["Windows"]["Path"]))
	else:
		gendtbpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["Gendtb"]["Linux"]["Path"]))
	final_path = os.path.join(PATH_DICT["workspacepath"], gendtbpath)
	return final_path


def arm_get_tools_path() -> Path:
	"""
	This function retrieves the path to the qc_dt_schema_check_path script.
	"""
	if platform.system() == "Windows":
		toolpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["qc_dt_schema_check"]["Windows"]["Path"]))
	else:
		toolpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["qc_dt_schema_check"]["Linux"]["Path"]))
	final_path = os.path.join(PATH_DICT["workspacepath"], toolpath)
	return os.path.dirname(final_path)


def arm_get_qc_dt_schema_check_path() -> Path:
	"""
	This function retrieves the path to the qc_dt_schema_check_path script.
	"""
	if platform.system() == "Windows":
		toolpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["qc_dt_schema_check"]["Windows"]["Path"]))
	else:
		toolpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["qc_dt_schema_check"]["Linux"]["Path"]))
	final_path = os.path.join(PATH_DICT["workspacepath"], toolpath)
	return final_path


def arm_get_qc_dt_check_path() -> Path:
	"""
	This function retrieves the path to the qc_dt_check_path script.
	"""
	if platform.system() == "Windows":
		toolpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["qc_dt_check"]["Windows"]["Path"]))
	else:
		toolpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["qc_dt_check"]["Linux"]["Path"]))
	final_path = os.path.join(PATH_DICT["workspacepath"], toolpath)
	return final_path


def arm_get_dtc_path() -> Path:
	"""
	This function retrieves the path to DTC.
	"""
	if platform.system() == "Windows":
		dtcpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["DTC"]["Windows"]["Path"]))
	else:
		dtcpath = Path(arm_remove_build_root(TOOLCHAIN_DICT["ToolChain"]["DTC"]["Linux"]["Path"]))
	final_path = os.path.join(PATH_DICT["workspacepath"], dtcpath)
	return final_path


def arm_get_cpp_path() -> Path:
	"""
	This function retrieves the path to the CPP compiler.
	"""
	if platform.system() == "Windows":
		cpppath = Path(TOOLCHAIN_DICT["ToolChain"]["CLANG140"]["Windows"]["Path"])
	else:
		cpppath = Path(TOOLCHAIN_DICT["ToolChain"]["CLANG140"]["Linux"]["Path"])
	final_path = os.path.join(PATH_DICT["workspacepath"], cpppath)
	return final_path


def pretty_print_json(json_dict: object, sort_keys=True, indent=2) -> None:
	"""
	This function prints the JSON dictionary in a readable format.
	To be used for debugging purposes if needed.
	"""
	print(json.dumps(json_dict, indent=indent, sort_keys=sort_keys))


def print_paths() -> None:
	"""
	This is a helper function that prints all paths found in PATH_DICT
	for debugging purposes.
	"""
	print(f"\n{'=' * 75}\n")
	for path in PATH_DICT:
		if PATH_DICT[path]:
			print(f"{path}: {PATH_DICT[path]}")

	print(f"\n{'=' * 75}\n")


def remove_json_comments(source_json_file):
	"""
	This is a helper function that removes comments
	from the given json file.
	"""
	dest_json = ""
	source_file_handle = open(source_json_file, "r")
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


def pretty_print_json(json_dict: object, sort_keys=True, indent=2) -> None:
	"""
	This function prints the JSON dictionary in a readable format.
	To be used for debugging purposes if needed.
	"""
	print(json.dumps(json_dict, indent=indent, sort_keys=sort_keys))


def print_paths() -> None:
	"""
	This is a helper function that prints all paths found in PATH_DICT
	for debugging purposes.
	"""
	print(f"\nDUMPING PATHS")
	print(f"\n{'=' * 75}\n")
	for path in PATH_DICT:
		if PATH_DICT[path]:
			print(f"{path}: {PATH_DICT[path]}")

	print(f"\n{'=' * 75}\n")


def main():
	global PATH_DICT, JSON_DICT, IMAGE_DICT, TOOLCHAIN_DICT, ROOT
	config_path = os.path.join(Path(__file__).parent, Path("config.json"))
	# load the json config file here, then we can get the PW names from the json file. This prevents any hardcoding
	with open(config_path, 'r') as j:
		JSON_DICT = json.load(j)

	ROOT = JSON_DICT["PW"]["root_folder"]
	
	# uncomment to print config.json
	# pretty_print_json(JSON_DICT)

	# what resolve does here is get the absolute path
	ABS_DIR = Path(__file__).resolve().parents

	PATH_DICT["workspacepath"] = get_workspace_path(ABS_DIR)
	PATH_DICT["arch"] = get_arch()

	if PATH_DICT["arch"] == "hexagon":
		# run hexagon specific functions
		image_info_path = JSON_DICT["PW"]["image_info"]
		PATH_DICT["imageinfopath"] = Q6_get_image_info(image_info_path)

		with open(PATH_DICT["imageinfopath"]) as i:
			IMAGE_DICT = json.load(i)

		env_vars = IMAGE_DICT["environment"]
		tools = {}
		for tool in IMAGE_DICT["tools"]:
			tools[tool["name"]] = tool["version"]

		Q6_get_crmenv(tools, env_vars)

		PATH_DICT["dtspath"] = Q6_get_dts_path()
		PATH_DICT["yamlpath"] = Q6_get_yaml_path()
		PATH_DICT["gendtbpath"] = Q6_get_gendtb_path()

		PATH_DICT["dt_schema_tools_path"] = Q6_get_tools_path()
		PATH_DICT["qc_dt_schema_check_path"] = Q6_get_qc_dt_schema_check_path()
		PATH_DICT["qc_dt_check_path"] = Q6_get_qc_dt_check_path()

		PATH_DICT["dtcpath"] = os.environ["DTC_PATH"]
		PATH_DICT["build_cfg"] = Q6_get_build_cfg_path()
		PATH_DICT["rtosversion"] = Q6_get_rtos_version()
		PATH_DICT["cpppath"] = Q6_get_cpp_path()
	elif PATH_DICT["arch"] == "arm":
		# run arm specific functions
		PATH_DICT["toolchainpath"] = arm_get_toolchain_path()
		TOOLCHAIN_DICT = json.loads(remove_json_comments(PATH_DICT["toolchainpath"]))

		PATH_DICT["dtspath"] = arm_get_dts_path()
		PATH_DICT["yamlpath"] = arm_get_yaml_path()
		PATH_DICT["gendtbpath"] = arm_get_gendtb_path()

		PATH_DICT["dt_schema_tools_path"] = arm_get_tools_path()
		PATH_DICT["qc_dt_schema_check_path"] = arm_get_qc_dt_schema_check_path()
		PATH_DICT["qc_dt_check_path"] = arm_get_qc_dt_check_path()

		PATH_DICT["dtcpath"] = arm_get_dtc_path()
		PATH_DICT["cpppath"] = arm_get_cpp_path()
	else:
		error_msg = f"\nUnknown architecture detected: {PATH_DICT['arch']}\nExiting..."
		sys.exit(error_msg)


main()


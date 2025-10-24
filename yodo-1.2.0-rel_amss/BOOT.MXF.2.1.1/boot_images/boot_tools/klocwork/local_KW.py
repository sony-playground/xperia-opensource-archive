#!/usr/bin/env python
# ============================================================================
#
# @file local_KW.py
#
# GENERAL DESCRIPTION
#   This script allows for "Connected" Klocwork static analysis to be run locally.
#   on Windows or Linux
#	Supported targets: Lahaina, Makena, Olympic, Waipio
#
# Copyright (c) 2020-2021 Qualcomm Technologies, Inc. All rights reserved.
#
# ----------------------------------------------------------------------------
#
#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 10/12/20   gt     Initial revision

import os
import subprocess
import sys
from argparse import ArgumentParser
import shutil
import json

LINUX_KW_PATH = "/prj/qct/asw/SABin/Linux/Klocwork/User/bin"
WINDOWS_KW_PATH = r'\\qctdfsrt\prj\qct\asw\SABin\Windows\Klocwork\User\bin'
parser = ArgumentParser()
parser.add_argument('--target', '-t', required = True, 
	help="Please specify target(s). Example: Lahaina,Cedros,QcomToolsPkg")
parser.add_argument('--variant', '-v', required = False, 
	help="Please specify a Variant. Example: LAA, WP, AU")
parser.add_argument('--flavor', '-r', required = False,
	help="Please specify flavor. Example: DEBUG, RELEASE") 
parser.add_argument('--kw_project', '-p', required = False, 
	help="Please specify a KW project. Example: CRM_BOOT_MXF_1_0_LAHAINA")
args = parser.parse_args()
buildspec = " KW_buildspec.out "
REPORT_NAME = "P1_report.log"
cmds = dict()
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
BOOT_DIR = os.path.dirname(SCRIPT_DIR)

def prepare_env():
	global KW_server_num
	global KW_project
	global TARGET_IMG
	global VARIANT
	global FLAVOR
	VARIANT = args.variant
	FLAVOR = args.flavor
	target = "".join(args.target)
	target_list = target.split(',')
	json_target_list = []
	with open('KWconfig.json', 'r') as f:
		data = json.load(f) 
	# Looks thru JSON file to find a matching target.
	# If no matching target is found, default parameters are used.
	# Default parmeters are the last entry in the JSON file.
	# This allows users to do connected SA on specfic Pkg (example: QcomCatePkg) 
	for i in data['target']:
		TARGET_IMG = i['Name']
		KW_project =  i['KW_Project']
		KW_server_num = i['KW_Server']
		if i['Name'] in target_list:
			KW_server_num = i['KW_Server']
			KW_project =  i['KW_Project']
			TARGET_IMG = i['Name'] 
			break
	print("Preparing Environment...")
	if os.path.isfile(buildspec):
		print('saving previous buildspec...')
		shutil.copy2(buildspec, 'old_'+ buildspec)
		os.remove(buildspec)
	if os.path.isfile(REPORT_NAME):
		print('saving previous report...')
		shutil.copy2(REPORT_NAME, 'old_'+ REPORT_NAME)
		os.remove(REPORT_NAME)
	BIN_DIR = os.path.join(BOOT_DIR, 'boot','QcomPkg','SocPkg')
	# Due to permissions issues, different commands are required to remove
	# directories in Linux and Windows
	if sys.platform == "win32":
		cmds['kwcheck'] = WINDOWS_KW_PATH + r"\kwcheck.exe"
		cmds['kwinject'] = WINDOWS_KW_PATH + r"\kwinject.exe"
		cmds['kwauth'] = WINDOWS_KW_PATH + r"\kwauth.exe"
		if os.path.isdir(os.path.join(BOOT_DIR, 'Build')):
			os.system('rmdir /S /Q "{}"'.format(os.path.join(BOOT_DIR, 'Build')))
		if os.path.isdir('.kwps'):
			os.system('rmdir /S /Q "{}"'.format('.kwps'))
		if os.path.isdir('.kwlp'):
			os.system('rmdir /S /Q "{}"'.format('.kwlp'))
		if TARGET_IMG is not None:
			if os.path.isdir(os.path.join(BIN_DIR, TARGET_IMG ,'Bin')):
				os.system('rmdir /S /Q "{}"'.format(os.path.join(BIN_DIR, TARGET_IMG ,'Bin')))
			if os.path.isdir(os.path.join(BIN_DIR,TARGET_IMG,'Bin_ext')):
				os.system('rmdir /S /Q "{}"'.format(os.path.join(BIN_DIR, TARGET_IMG ,'Bin_ext')))
	else:
		cmds['kwcheck'] = LINUX_KW_PATH+"/kwcheck"
		cmds['kwinject'] = LINUX_KW_PATH+"/kwinject"
		cmds['kwauth'] = LINUX_KW_PATH+"/kwauth"
		if os.path.isdir(os.path.join(BOOT_DIR, 'Build')):
			shutil.rmtree(os.path.join(BOOT_DIR, 'Build'))
		if os.path.isdir('.kwps'):
			shutil.rmtree('.kwps')
		if os.path.isdir('.kwlp'):
			shutil.rmtree('.kwlp')
		if TARGET_IMG is not None:
			if os.path.isdir(os.path.join(BIN_DIR, TARGET_IMG ,'Bin')):
				shutil.rmtree(os.path.join(BIN_DIR, TARGET_IMG ,'Bin'))
			if os.path.isdir(os.path.join(BIN_DIR,TARGET_IMG,'Bin_ext')):
				shutil.rmtree(os.path.join(BIN_DIR,TARGET_IMG,'Bin_ext'))
	if not os.path.isfile(cmds['kwcheck']):
		sys.exit("kwcheck binary not found")
	if not os.path.isfile(cmds['kwinject']):
		sys.exit("kwinject binary not found")
	if not os.path.isfile(cmds['kwauth']):
		sys.exit("kwauth binary not found")
	print("Preparing Environment Complete")
	
def main():
	prepare_env()
	BUILDEX = os.path.join(os.path.dirname(SCRIPT_DIR),"buildex.py")
	if VARIANT is None:
		#Variant does not need to be specified in command line
		COMMAND = 'python -u ' + BUILDEX + ' -t {}'.format(args.target, VARIANT)
	else:
		COMMAND = 'python -u ' + BUILDEX + ' -t {} -v {} -r {}'.format(args.target, VARIANT, FLAVOR)
	print('Build Command {}'.format(COMMAND))
	try:
		os.system("{} --url https://kwdbprod{}.qualcomm.com:8070".format(cmds['kwauth'], KW_server_num))
	except Exception as e:
		print(e)
		sys.exit("Connection to Klocwork failed")
	try:
		os.system("{} create --url https://kwdbprod{}.qualcomm.com:8070/{}".format(cmds['kwcheck'], KW_server_num, KW_project))
	except Exception as e:
		print(e)
		sys.exit("Connection to Klocwork failed")
	build_command = "{} -o ".format(cmds['kwinject']) + " " + buildspec + COMMAND
	print(build_command)
	os.system(build_command)
	os.system("{} import".format(cmds['kwcheck']) + buildspec)
	os.system('{} run'.format(cmds['kwcheck']))
	os.system('{} list --system --severity 1 --status "Analyze","Fix","Fix in Next Release","Defer" --report P1_report.log'.format(cmds['kwcheck']))

if __name__ == "__main__":
	main()

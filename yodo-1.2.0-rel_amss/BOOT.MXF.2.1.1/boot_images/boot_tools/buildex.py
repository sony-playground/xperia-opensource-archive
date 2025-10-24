#!/usr/bin/env python

#============================================================================
#
# @file buildex.py
#
# GENERAL DESCRIPTION
#   Unified script for building any/all targets available
#
# Copyright 2017 - 2022 by Qualcomm Technologies, Inc.
#                 All Rights Reserved.
#               QUALCOMM Proprietary/GTDR
#
#----------------------------------------------------------------------------
#
#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     ----------------------------------------------------------
# 08/24/22   yps      Print all sub python scripts' logs
# 06/14/22   yps      Unified the buildex error log.
# 06/01/22   yps      Enahncement exception handler and buildex log
# 11/25/21   yps      Support python version 3.8.2 or later only
# 04/13/21   yps      Make -t option as mandatory option
# 01/12/21   yps      Support multi tool path and set Macro definition dynamically
# 08/26/20   yps      Added export item in buildex Macro
# 06/30/20   yps      Support python3.8.3
# 06/17/20   kpa      More robust exception handling while launching build.py
# 06/15/20   kpa      Fix error logging, edksetup launch
# 06/10/20   yps      Support build.py on windows compilation
# 04/30/20   yps      Support binary component
# 04/14/20   yps      Update sectools path
# 02/27/20   yps      Make scripts compatible with python2 and python3
# 02/18/20   yps      Migrate some python scripts to boot_tools folder
# 02/14/20   am       Handle multi-line env variables in parse_and_set_edk_env
# 12/02/19   yps      Fix buildex bug for linux enviornment
# 10/10/19   yps      Support multipkgs and remove buildex path dependency
# 06/20/19   yps      Prevent duplicate compilation of the same component with the same build command
# 04/24/19   ds       changes to support variant buildconfig json
# 03/13/19   yps      Support multi-dependency other pkgs in current pkg build
# 09/17/18   yps      Support Macro for output path
# 04/10/18   ska      Added -O --oem_environ flag
# 19/09/17   mt       Added support for -V and -b flags with alias flag
# 07/07/17   c_vkuppa Build time statistic for the whole process
# 05/16/17   vk       Fix typo in filename
# 03/17/17   yps      Fixed buildex deploy issues
# 03/13/17   yps      remove case sensitive for input arguments,added -C components compile
# 02/21/17   yps      Optimized process flow
# 01/26/17   yps      Initial release

from __future__  import print_function
import shutil
import stat
import subprocess
import glob
import re
from optparse import OptionParser
from collections import defaultdict
import platform
import os
import sys
import fnmatch
import json
import time
import logging


DEVDEBUG = False
MINIMUM_PYTHON_VERSION = (3,8,2)
DEFAULT_RELEASE_MODES = "DEBUG,RELEASE"
GENERAL_ERROR_CODE = 1
ENVIRONMENT_SETUP_ERROR_CODE = 2
EDK_TOOL_ERROR_CODE = 3
SEARCH_ALL_TARGET_PATH_ERROR_CODE = 4
SEARCH_BUILD_JSONS_PATH_ERROR_CODE = 5
MATCH_IMAGES_ERROR_CODE = 6
FIND_COMPONENTS_ERROR_CODE = 7
Tool_chain_json_config = ""
DEFAULT_ARM_LICENSE_FILE = "7117@license-wan-arm1"
DEFAULT_TARGET_REGEX = "^([a-zA-Z]{3,9})(\d*)Pkg$"
DEFAULT_SHAREDPKG_REGEX = "SocPkg"
DEFAULT_VARIANT_REGEX = '^[A-Z][A-Z][A-Z0-9]?$'
CHIP_NUM_REGEX = "\d.*\d"
BUILDIT_BUILDINFO_TAG = "UserExtensions.Buildit.BuildInfo"
BOOT_IMAGES_DIR = "boot_images"
QCOM_DIR = "QcomPkg"
SHAREDPKG_DIR = "SocPkg"
DEFAULT_COMPILER_ARCH = "AARCH64"
COPY_IMAGES_AS_IS = ["jtagprogrammer"]

ARGUMENTS = {"$BUILDROOT":"" ,
             "$BOOTROOT" :"" ,
             "$REL":"" ,
             "$PRODMODE":"" ,
             "$VAR":"",
             "$COMPLIER":"",
             "$FIRSTDLL":"",
             "$SECONDDLL":"",
             "$XBLSEC":"",
             "$TARGETROOT":"",
             "$TARGETID":"",
             "$TARGETPKG":"",
             "$QCOMDIR":""}
components_status = {}

conf_files = ["build_rule", "target", "tools_def"]

logging.basicConfig(filename=os.path.join(os.path.dirname(__file__),"buildex.log"),filemode='w',format='%(message)s',level = logging.DEBUG)

logger = logging.getLogger(__name__)
console = logging.StreamHandler(stream=sys.stdout)
logger.addHandler(console)


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

# merge_book - Acts as a wrapper around a dictionary of merge_entry's
class merge_book:
  def __init__(self):
    self.merges = dict()
  def add_merge_item(self, dll_path):
    # create merge_entry if it doesn't exist
    if merge_name not in self.merges:
      new_merge = merge_entry(merge_name, sign_type, xbl_sec)
      self.merges[merge_name] = new_merge
    # add the dll to merge_entry
    self.merges[merge_name].add_merge_item(dll_path, xbl_sec)

  # Same as above, but with a base to merge
  def add_merge_base(self, merge_name, base_dll_path, sign_type, xbl_sec=""):
    if merge_name not in self.merges:
      new_merge = merge_entry(merge_name, sign_type, xbl_sec)
      self.merges[merge_name] = new_merge
    self.merges[merge_name].set_merge_base_dll(base_dll_path, xbl_sec)

class merge_entry:
  def __init__(self, output_name, sign_type, xbl_sec=""):
    self.output_name = output_name
    self.sign_type = sign_type
    self.xbl_sec = xbl_sec
    self.dll_list = []
    self.merge_base_dll = ""

    if output_name == "":
      logger.debug( "Error: # MERGE value is invalid")
      sys.exit(GENERAL_ERROR_CODE)

  def add_merge_item(self, dll_path):
    self.dll_list.append(dll_path)


  def set_merge_base_dll(self, base_dll_path, xbl_sec=""):
    if self.merge_base_dll:
      logger.debug( "Error: Multiple MERGE_BASE tags found for " + self.output_name)
      sys.exit(GENERAL_ERROR_CODE)
    self.merge_base_dll = base_dll_path
    if xbl_sec:
      self.xbl_sec = xbl_sec

  def modify_merge_entry_xbl_sec(self, xbl_sec):
    self.xbl_sec = xbl_sec

  def modify_merge_entry_dll_list(self, dll_list):
    self.dll_list = dll_list

  def print_merge_entry(self):
    logger.info( "[buildex.py] [MERGE DETAILS] output name: {0}".format(self.output_name))
    logger.info( "[buildex.py] [MERGE DETAILS] sign_type: {0}".format(self.sign_type))
    logger.info( "[buildex.py] [MERGE DETAILS] xbl sec: {0}".format(self.xbl_sec))
    logger.info( "[buildex.py] [MERGE DETAILS] dll list: {0}".format(self.dll_list))
    logger.info( "[buildex.py] [MERGE DETAILS] merge base dll: {0}".format(self.merge_base_dll))


class build_flavor:
  def __init__(self, target,image = "",variant="", release_mode="",aarch="",compiler="",merged_output_elf="",output_name=""):
    self.target = target
    self.image = image
    self.variant = variant
    self.release_mode = release_mode
    self.aarch = aarch
    self.compiler = compiler
    self.merged_output_elf = merged_output_elf
    self.output_name = output_name

  def to_string(self):
    desc = "Target: " + self.target + "\t"
    desc += " Variant: " + self.variant if self.variant else " Variant: ---"
    desc += " Release: " + self.release_mode + "\t"
    desc += " Image: " + self.image
    return desc

##############################################################################
# display_build_summary
##############################################################################
def display_build_summary(all_flavors):
  if all_flavors:
    logger.info( ("\n[buildex.py] Successfully built following flavors:\n"+
         "###################################################"))
    for flavor in all_flavors:
      logger.info( flavor.to_string())
  else:
    logger.info( "\n[buildex.py] Nothing built\n")

def merge_build_config_files(build_config_json1, build_config_json2):

  # if both buildconfig json are present
  if len(build_config_json1) and len(build_config_json2):
      # Polling the first object layer
      for k in list(build_config_json2.keys()):
          if k in list(build_config_json1.keys()):
              for i in range(len(build_config_json2[k])):
                item_merged = False
                for j in range(len(build_config_json1[k])):
                    #if they are the same set, merger them all
                    if build_config_json1[k][j]["Name"]==build_config_json2[k][i]["Name"]:
                        for config_k in list(build_config_json2[k][i].keys()):
                            if config_k == 'Name':
                                continue
                            if config_k != "Process" and config_k in build_config_json1[k][j].keys():
                                logger.error("[buildex.py] ERROR: object [{}] has confilict item [{}] in json files".format(build_config_json1[k][j]["Name"],config_k))
                                logger.error("[buildex.py] The same item of object can't exsit in two json files, please resolve it.")
                                sys.exit(-1)
                            elif config_k not in  build_config_json1[k][j].keys():
                                build_config_json1[k][j][config_k]=build_config_json2[k][i][config_k]
                                item_merged = True
                                break
                            elif config_k == "Process":
                                build_config_json1[k][j][config_k].extend(build_config_json2[k][i][config_k])
                                item_merged = True
                                break
                        if item_merged == True:
                            break
                #if there is no the same item, append the item to target dict directlly.
                if item_merged == False:
                  build_config_json1[k].append(build_config_json2[k][i])
          else:
            build_config_json1[k]=build_config_json2[k]


  if len(build_config_json1)==0 and len(build_config_json2):
    build_config_json1=build_config_json2
  return build_config_json1

##############################################################################
# gen_build_process
##############################################################################

def gen_build_config(options,target_path,variant):
  # Find buildconfig.json in target folder
  buildconfig_json_files = {}
  if options.firehose == "":
    json_path = search_build_json_path(target_path,"buildconfig.json")
  else:
    json_path = search_build_json_path(target_path,"firehose.json")

  if json_path == "":
    logger.error("[buildex.py] ERROR:Can't find buildconfig.json in target folder!!")
    sys.exit(-1)
  buildconfig_json_files[os.environ["TARGETMSM"]+"buildconfig.json"]=json_path

  # Find internal_buildconfig.json
  internl_json_path = search_build_json_path(target_path,"buildconfig_internal.json")
  if internl_json_path != "":
    buildconfig_json_files[os.environ["TARGETMSM"]+"buildconfig_internal.json"]= internl_json_path

  # find variant buildconfig json eg: buildconfig_LAA.json
  var_json_path = search_build_json_path(os.path.join(target_path,variant),"buildconfig_"+variant+".json")
  if var_json_path != "":
    buildconfig_json_files["buildconfig_"+variant+".json"] = var_json_path

  # find internal_buildconfig.json in variant folder
  internal_var_json_path = search_build_json_path(os.path.join(target_path,variant),"buildconfig_internal.json")
  if internal_var_json_path != "":
    buildconfig_json_files[variant+"buildconfig_internal.json"] = internal_var_json_path

  # Merge all build json files. Eg:buildconfig.json , internal_buildconfig.json, buildconfig_LAA.json
  build_config={}
  for key in list(buildconfig_json_files.keys()):
    if os.path.exists(buildconfig_json_files[key]):
      build_config_temp = pre_parser_json_file(buildconfig_json_files[key])
      build_config = merge_build_config_files(build_config, build_config_temp)
    else:
      logger.error("[buildex.py] ERROR: {} is not exist!!!".format(buildconfig_json_files[key]))
      sys.exit(-1)

  return build_config


def main():
  target_paths= []
  variants = []
  all_flavors = []
  images = []
  build_config = {}
  tools_config = {}
  build_start_time = time.time()

  if sys.version_info < MINIMUM_PYTHON_VERSION:
      logger.error( "\n[buildex.py] ERROR: Incorrect version of Python detected: {}".format(sys.version))
      logger.error( "[buildex.py]        Requires use of Python 3.7.4 or later.")
      sys.exit(GENERAL_ERROR_CODE)
  if re.search("\.[sS]", os.getcwd()):
      logger.error( "\n[buildit.py] ERROR: Directory name containing \".[sS]\" detected: {}".format(os.getcwd()))
      logger.error( "[buildit.py]        Please rename directory or use a different vce workspace name")
      logger.error( "[buildit.py]        that does not start with an 's' or 'S'.")
      sys.exit(GENERAL_ERROR_CODE)

  desc = "python buildex.py [options]\n" \
         "\nExample invocations:\n" \
         "  python buildex.py -t Lahaina\n" \
         "  python buildex.py -t Lahaina --variant LAA\n" \
         "  python buildex.py -t Lahaina --variant LAA,LAB -r DEBUG\n" \
         "  python buildex.py -p D:\workspace\boot_images -t Lahaina --variant LAA,LAB -r DEBUG\n"

  parser = OptionParser(usage=desc)

  parser.add_option('-i', '--image', default="",
                    help="image(s) that will be built, separated by comma. " + \
                         "Example: \n" + \
                         "python buildex.py -i XBL  # that will build all components like XBL, XBL_loader, DDI ...\n" + \
                         "python buildex.py -i DEV_PROG\n" + \
                         "python buildex.py -i XBL_Loader\n" + \
                         "If not specified, all targets will be built", )

  parser.add_option('-t', '--target', default="",
                    help="Target(s) that will be built, separated by comma. " + \
                         "Example: -t Waipio. " + \
                         "If not specified,build will be broken", )

  parser.add_option('-a', "--alias",
                    action="store", default="",
                    help="Specify argument alias from config file QcomPkg/aliasconfig.json " + \
                         "Example: -a 98ladbg",)

  parser.add_option('-V', "--version",
                    action="store", default="0",
                    help="Specify build version. Default is 0. Example: -v 123.")

  parser.add_option('-v', '--variant', default="",
                    help="Variant(s) that will be built, separated by comma. " + \
                         "Example: -v la,wp " + \
                         "If not specified, all variants will be built per target")

  parser.add_option('-f', '--firehose', default="",
                    help="Firehose version that will be built." + \
                         "Example: -f 0001. " + \
                         "If not specified, \"local_build\" will be used")

  parser.add_option('-b', '--build_flags',
                      action="store", default="",
                      help="Flags to be passed to the build invocation. " + \
                            "Specify multiple arguments separated by a comma or enclosed in double quotes. " + \
                            'Example: -b -v,-n,1')

  parser.add_option('-c', '--compiler_flags', default="",
                      help="Extra flags to be passed to the build compiler directly. " + \
                            "Specify multiple arguments enclosed in double quotes. " + \
                            'Example: "-c -DPRE_SIL -DANOTHER_FLAG",')

  parser.add_option('-C', '--components', default="",
                      help="Will only compile the components input from this option " + \
                            "Example: -C XBL_Loader,XBL_Ramdump",)

  parser.add_option('-r', "--release",
                    action="store", default=DEFAULT_RELEASE_MODES,
                    help="Release mode for building, default is 'DEBUG,RELEASE'." \
                         " Both modes will be built.")
  parser.add_option('-O', "--oem_environ",
                    action="store", default="NULL",
                    help="Specify OEM_IMAGE_VERSION_STRING. Example: -O BUILD_OEM_VERSION")

  parser.add_option('-p', '--imgrootpath',
                    action="store",default="",
                      help="boot_image path " + \
                            "Example: -p D:\workspace\boot_images",)
  (options, args) = parser.parse_args()
  init_work_path(options.imgrootpath)
  init_conf_folder(os.environ["BUILDROOT"])

  if options.target == "":
    logger.error("[buildex.py] ERROR: Buildex.py requires -t option, please input target name, like Waipio")
    sys.exit(0)
  try:
     tools_config = setup_environment(os.environ["BUILDROOT"])
  except Exception as error:
      logger.error( "[buildex.py] ERROR: {}".format(error))
      sys.exit(ENVIRONMENT_SETUP_ERROR_CODE)

  if options.alias :
    Alias_file =  remove_json_comments(os.path.join(os.environ["WORKSPACE"],
                                               QCOM_DIR,"aliasconfig.json"),None)
    Alias_config =  json.loads(Alias_file)
    alias_args = options.alias.lower()
    if alias_args in Alias_config:
      version = options.version
      build_flags = options.build_flags
      (options, args) = parser.parse_args(Alias_config[alias_args])
      options.version = version
      options.build_flags = build_flags
    else:
      logger.error("[buildex.py] Error: Alias arguments %s is not correct.",options.alias)
      sys.exit(-1)


  # make sure release_mode is valid
  options.release  = options.release.upper()
  for mode in options.release.split(','):
      if mode not in DEFAULT_RELEASE_MODES:
          logger.error(( '[buildex.py] Error: Release mode {} is invalid. Please see --help for more information'.format(mode)))
          sys.exit(-1)

  create_build_version(options.version)

  # Creates FirehoseVersion.h if Firehose version is provided
  create_firehose_version(options.firehose)

  # Check that tools exist, otherwise make them
  try:
    make_edk_tools()
  except Exception as error:
    logger.error( error)
    sys.exit(EDK_TOOL_ERROR_CODE)
  # Delete old build products file
  build_products_file = os.path.join(os.environ["WORKSPACE"],
                         "..","..", "BuildProducts.txt")
  if os.path.isfile(build_products_file):
    os.remove(build_products_file)

  # find all the targets
  try:
    target_paths=search_all_target_path(options.target)
  except Exception as error:
    logger.error( "[buildex.py] ERROR: {}".format(error))
    sys.exit(SEARCH_ALL_TARGET_PATH_ERROR_CODE)

  for target_path in target_paths:
    ##ds## target_temp = os.path.basename(target_path)
    qcompkg_path = (os.path.join(os.environ["WORKSPACE"],QCOM_DIR))
    path_for_target = str(os.path.relpath(target_path,qcompkg_path))
    target = path_for_target #ds#
    if len(path_for_target.split(os.sep))==2:
        os.environ["SHAREDTARGETPKG"] = path_for_target.split(os.sep)[0]
        os.environ["TARGETPKG"]  = os.environ["SHAREDTARGETPKG"]
        os.environ['TARGETROOT'] = os.path.join(QCOM_DIR, path_for_target)
        os.environ["TARGETMSM"]  = (os.environ["TARGETPKG"]).split("Pkg")[0] + (target.split(os.sep)[1])
    else :
        os.environ["TARGETPKG"]  = target
        os.environ['TARGETROOT'] = os.path.join(QCOM_DIR, os.environ["TARGETPKG"])
        os.environ["TARGETMSM"]  = target.split("Pkg")[0]
    variants = []
    try:
      variants = match_variants(target_path,options.variant)
    except Exception as e:
      logger.error("[buildex.py] ERROR: {}".format(e))
      sys.exit(-1)
    matches = re.search(DEFAULT_TARGET_REGEX, target)
    if matches:
      if matches.group(2) != "":
        # Handle legacy case of QcomPkg/SDM<#num>Pkg/ eg QcomPkg/SDM845Pkg
        os.environ["TARGETID"] = matches.group(2)
      else:
        # Handles other packages (e.g. QcomToolsPkg)
        os.environ["TARGETID"] = os.environ["TARGETMSM"]
    else:
      # Handles app packages (e.g. QcomToolsPkg)
      os.environ["TARGETID"] = os.environ["TARGETMSM"]

    ARGUMENTS["$TARGETROOT"] = os.environ["TARGETROOT"]
    ARGUMENTS["$TARGETID"] = os.environ["TARGETID"]
    ARGUMENTS["$TARGETPKG"] = os.environ["TARGETPKG"]
    ARGUMENTS['$BOOTROOT'] = os.environ["WORKSPACE"]
    index = 0
    while (index < len(variants) ) or (index == 0):
      if variants:
        variant = variants[index].upper()
      else:
        variant = ""
      image_version_setup(os.environ["TARGETMSM"],variant,options.oem_environ)
      ARGUMENTS['$VAR'] = variant
      os.environ["VAR"] = ARGUMENTS['$VAR']
      #initialize build_config
      build_config.clear()
      build_config = gen_build_config(options,target_path,variant)

      # find the image which we should process for the variant
      try:
         images = match_images(options.image,build_config )
      except Exception as error:
          logger.error("[buildex.py] ERROR: {}".format(error))
          sys.exit(MATCH_IMAGES_ERROR_CODE)

      for release_mode in options.release.split(','):
        if release_mode.upper() == "RELEASE":
            ARGUMENTS['$REL'] = 'RELEASE'
            ARGUMENTS['$PRODMODE'] = 'PRODMODE'
        elif release_mode.upper() == "DEBUG":
            ARGUMENTS['$REL'] = 'DEBUG'
            ARGUMENTS['$PRODMODE'] = 'DEBUGMODE'
        else:
            logger.error("[buildex.py] ERROR:: Opiton -r \"{}\" does not support !!!".format(release_mode))
            sys.exit(-1)

        # loop to process images
        for image in images:
          variant_flavor = build_flavor(str(os.environ["TARGETMSM"]),
                                        image,
                                        variant.upper(),
                                        release_mode.upper(),
                                        "",
                                        "",
                                        "",
                                        "")
          all_flavors.append(variant_flavor)
          create_image(options,variant_flavor,build_config,tools_config)
      index+=1
  if "clean" in options.build_flags:
     logger.info( "[buildex.py] Clean successfully.")
  else:
     build_end_time = time.time()
     delta = build_end_time - build_start_time
     minutes = delta//60
     seconds = delta - 60*minutes
     logger.info( "\n[buildex.py] Successfully built following flavors in {}:{}mins".format(int(minutes),int(seconds)))
     display_build_summary(all_flavors)
  logger.info( "\n[buildex.py] Now exiting...\n")
  return

def match_variants(target_path,option_variants):
  variant_dirs = []
  available_variants = []
  if option_variants:
    for variant in option_variants.split(","):
      regex = variant.upper()
      if re.search(DEFAULT_VARIANT_REGEX,regex):
         variant_dirs += search_dir(target_path,regex)
         if SHAREDPKG_DIR in target_path and variant_dirs == []:
           raise Exception("Error:: {} variant can't be found in {}".format(variant,target_path))
      else:
         raise Exception("Error:: Variant: \""+ \
                               variant + \
                               "\" does not support!!!!\n"  + \
                               "Please refer -h to get help.")

  else:
    regex = DEFAULT_VARIANT_REGEX
    variant_dirs =(search_valid_dirs(target_path,regex))

  if variant_dirs:
    for variant_dir in variant_dirs:
      if os.path.isdir(variant_dir):
        available_variants.append(os.path.basename(variant_dir))
  return available_variants

def find_tool_config(tools_config,tool_name):
  if tool_name in tools_config['ToolChain']:
    if platform.system() == "Windows":
      if 'Windows' in tools_config['ToolChain'][tool_name]:
        return tools_config['ToolChain'][tool_name]['Windows']
      else:
        return tools_config['ToolChain'][tool_name]
    else:
      if 'Linux' in tools_config['ToolChain'][tool_name]:
        return tools_config['ToolChain'][tool_name]['Linux']
      else:
        return tools_config['ToolChain'][tool_name]

  else:
    return ""

def create_dirs(dir_lists):
 for dir_path in dir_lists:
   dir_path = replace_arguments (dir_path)
   if not os.path.isdir(dir_path):
     os.makedirs(dir_path)

#####################################################################
# perform create image
#####################################################################
def create_image(options,variant_flavor,build_config,tools_config):
  tool_cmds = []
  cmd_params = []
  for i in range(len(build_config['CreateImages'])):
    if build_config['CreateImages'][i]['Name'] == str(variant_flavor.image):
      merge_dict = merge_book()
      for j in range(len(build_config['CreateImages'][i]['Process'])):
        process_action = build_config['CreateImages'][i]['Process'][j]
        if "Createfolders" in process_action:
          create_dirs(process_action["Createfolders"])
        if "Components" in process_action:
          dll_paths=[]
          dll_paths=process_components(options,variant_flavor,process_action,build_config,tools_config,merge_dict)
        if "clean" in options.build_flags:
          continue
        if process_action['ToolChain'] == "Merge":
          # and collect the items(elfs) that were created
          merge_tool_config = find_tool_config(tools_config,"Merge")
          built_items = []
          build_product = perform_merges(options,
                                         dll_paths,
                                         variant_flavor,
                                         process_action,
                                         merge_tool_config)
          if build_product:
             built_items.append(build_product)

          # Write out after merging for nicer looking output
          try:
            append_build_products(built_items)
          except Exception as error:
            raise Exception("{}{}{}".format("ERROR: buildex::append_build_products: ",error, "Failed to append to build products file."))
          continue

        tool_config = find_tool_config(tools_config,process_action['ToolChain'])
        tool_cmds = get_tool_cmd(tool_config)
        cmd_params = get_cmd_params(options,variant_flavor,process_action,tool_config)
        if process_action['ToolChain'] == "Copy":
           shutil.copy2(cmd_params[0],cmd_params[1])
           continue

        try:
          logger.info(''.join(tool_cmds+cmd_params))
          subprocess.check_call(tool_cmds + cmd_params)
        except Exception as error:
          logger.info (error)
          raise Exception("{}{}{}{}".format("ERROR: buildex::excute command:",tool_cmds ,cmd_params,"failed with error: \n"))
        except KeyboardInterrupt:
          sys.exit(-1)

  return
#####################################################################
# Check_components_status
#####################################################################
def check_components_status(build_cmd):
  buildcmd=','.join(build_cmd)
  if buildcmd in components_status:
    if  components_status[buildcmd] == "processed":
        return 1
  return 0

#####################################################################
# set_components_status
#####################################################################
def set_components_status(build_cmd):
  buildcmd=','.join(build_cmd)
  components_status[buildcmd] = "processed"
  return 1
#####################################################################
# Check dependency. it supports multi-level PKG dependencies. But
# these Pkgs can't depnede on each other.
#####################################################################
def component_dependency_check(up_level_dependency, dependencies):
  dependency_pkg_path = (os.path.join(os.environ["WORKSPACE"],QCOM_DIR,up_level_dependency['Pkg']))
  if not os.path.exists(dependency_pkg_path):
    logger.error( "[buildex.py] ERROR: Dependency pkg path ",dependency_pkg_path, " does not exist!!!")
    sys.exit(-1)
  dependency_pkg_buildconfig_path = os.path.join(dependency_pkg_path,"buildconfig.json")
  if not os.path.exists(dependency_pkg_buildconfig_path):
    logger.error( "[buildex.py] ERROR: Dependency pkg ",dependency_pkg_buildconfig_path, " does not exist!!!")
    sys.exit(-1)
  cur_dep_pkg_buildconfig = remove_json_comments(dependency_pkg_buildconfig_path, None)
  cur_dep_pkg_buildconfigconfig = json.loads(cur_dep_pkg_buildconfig)
  for component in cur_dep_pkg_buildconfigconfig['Components']:
   if "Dependency" in component:
     if component["Dependency"]['Pkg'] in dependencies:
       logger.error( "[buildex.py] ERROR:{} and {} depend on each other!!! Please check these two pkg buildconfig.json files".format(component["Dependency"]['Pkg'], up_level_dependency['Pkg']))
       logger.error( "Note:PKG can't depend on each other!!!")
       sys.exit(-1)
     else:
       dependencies.update({up_level_dependency['Pkg'],component["Dependency"]['Pkg']})
       component_dependency_check(component["Dependency"],dependencies)


#####################################################################
# process_components
#####################################################################
def process_components(options,variant_flavor,process_config,build_config,tools_config,merge_dict):
  dll_paths=[]
  for component in process_config['Components']:

    bin_path=process_component(options,variant_flavor,component,process_config,build_config,tools_config,merge_dict)
    # Determine what to merge
    if bin_path:
      dll_paths.append(bin_path)
  return dll_paths

#####################################################################
# build component
#####################################################################
def process_component(options,variant_flavor,component,process_config,build_config,tools_config,merge_dict):
  component_config = None
  build_cmd = []
  tool_cmd = []
  dependencies = {}
  dsc_path = None
  bin_path = None
  needs_compile = True
  output=None
  for i in range(len(build_config['Components'])):
    if build_config['Components'][i]['Name'] == str(component):
      component_config = build_config['Components'][i]
      break
  if component_config is None:
    logger.error("[buildex.py] ERROR: build_component: can't find {} Please ensure it exist.".format(component))
    sys.exit(-1)
  if "Binary" in component_config and "Process" not in component_config:
    Binary_path = replace_arguments(component_config["Binary"])
    if os.path.exists(Binary_path):
      bin_path = Binary_path
      needs_compile = False
    else:
      logger.error( ("[buildex.py] ERROR: Component {}\'s binary:{} doesn't exist!!!".format(component_config['Name'],Binary_path)))
      sys.exit(-1)

  if "Dependency" in component_config:
    dependencies={ARGUMENTS["$TARGETPKG"],component_config['Dependency']['Pkg']}
   # for dependency incomponent_config['Dependency']:
    component_dependency_check(component_config['Dependency'],dependencies)
    if not os.path.exists(replace_arguments(component_config['Dependency']['ImagePath'])):
      needs_compile = True
    else:
      needs_compile = False

  if needs_compile:
    for i in range(len(component_config['Process'])):
      cprocess_config = component_config['Process'][i]
      if "Createfolders" in cprocess_config:
        logger.info("creating folders: {}".format([replace_arguments(folder) for folder in cprocess_config["Createfolders"]]) )
        try:
          create_dirs(cprocess_config["Createfolders"])
        except Exception as e:
          logger.error("[buildex.py] ERROR: {}".format(e))
          sys.exit(-1)
      tool_config = find_tool_config(tools_config,component_config['Process'][i]['ToolChain'])
      build_cmd = get_cmd_params(options,variant_flavor,cprocess_config,tool_config)

      if build_cmd[0] == "build" or "build.py" in list(build_cmd[0].split(os.sep)) or "build.py" == build_cmd[0]:
        # Make a full flavor; Requried for finding all merge dependencies
        dsc_path = find_dsc_path_from_configuration(build_cmd)
        variant_flavor.aarch = component_config['Process'][i]['AArch']
        ARGUMENTS['$AARCH']= variant_flavor.aarch
        if options.build_flags:
            build_cmd += options.build_flags.strip('"').split(',')

        if ((options.components and component_config['Name'].upper() in options.components.upper()) or options.components == "") and not check_components_status(build_cmd):
          set_compiler_path(tool_config,component_config['Process'][i]['ToolChain'])
          set_components_status(build_cmd)
          #define Macros for EDK build system acoordeing to ARGUMENTS
          for key, value in ARGUMENTS.items():
            build_cmd.append('-D')
            build_cmd.append(key.lstrip('$')+'='+value)

          logger.info( "[buildex.py] Building with arguments...\n {}\n".format(build_cmd))
          if "py" in build_cmd[0].split('.'):
            build_cmd.insert(0,'python')
          try:
             subprocess.check_call(build_cmd)
          except subprocess.CalledProcessError as cperror:
             logger.error("[buildex.py] ERROR: Run {} Build Subprocess failed with error... ".format(build_cmd))
             logger.error(cperror.output)
             sys.exit(-1)
          except KeyboardInterrupt:
             sys.exit(-1)


        else:
           break

        if "clean" in options.build_flags:
          break
      elif cprocess_config['ToolChain'] == "Copy":
         shutil.copy2(build_cmd[0],build_cmd[1])
         continue
      else:
        if tool_config != "":
          tool_cmd = get_tool_cmd(tool_config)
        else:
          tool_cmd.append(cprocess_config['ToolChain'])
        cmd = tool_cmd + build_cmd
        try:
            logger.info("[buildex.py] Execute cmd:{}".format(cmd))
            proc = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                                  stderr=subprocess.STDOUT,
                                  universal_newlines=True,bufsize=1)
            hit_error = False
            while proc.poll() is None:
                  line = proc.stdout.readline().strip()
                  if(len(line)):
                     logger.info(line)
                  if line!='':
                      if 'Error:' in line or 'ERROR:' in line or 'error:' in line or 'Errno' in line:
                          hit_error = True
            if hit_error:
                logger.info("[buildex.py] Failed execute cmd:{}".format(" ".join(tool_cmd + build_cmd)))
                sys.exit(-1)
        except Exception as e:
          logger.err("[buildex.py] ERROR: Failed excute cmd:{} with error {}".format(cmd,e))
          sys.exit(-1)

      logger.info("[buildex.py] Succesfully execute cmd:{}".format(" ".join(tool_cmd + build_cmd)))
  # Determine what to merge
  if dsc_path:
    bin_path = re.sub('[()]', '',generate_merge_item(merge_dict,dsc_path,variant_flavor,process_config))
  return bin_path

def replace_arguments(string):
  arg_regex = "(\$[A-Z\(\)0-9]+)"
  macro_regex = "(%[A-Za-s0-9_]+%)"
  url_regex = "(http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+)"
  matches = []
  str1 = string
  # if the format of string is bytes, convert it to string by decode()
  if isinstance(str1,bytes):
      str1=str1.decode()
  # match local macro definitions
  matches = re.findall(arg_regex, str1)

  if matches:
    for match in matches:
      arg=match.replace(r'(','')
      arg=arg.replace(r')','')
      if arg in ARGUMENTS:
        if isinstance(ARGUMENTS[arg], bytes):
          value=ARGUMENTS[arg].decode()
        else:
          value=ARGUMENTS[arg]
        str1=str1.replace(match,value)
      else:
        logger.error("[buildex.py] ERROR: argument {} doesn't exist!!!".format(arg) )
        sys.exit(-1)
  if platform.system() == 'Windows':
      #check for url, if matches, skip the replace
      matched_url = re.findall(url_regex,str1)
      if not matched_url:
          str1 = str1.replace(r"/",os.sep,100)

      # if matched_url:
      #     return
      # else:
      #     str1 = str1.replace(r"/",os.sep,100)

      # str1 = str1.replace(r"/",os.sep,100)
  else:
      str1 = str1.replace(r"\\",os.sep,100)
  # match environment variables
  matches = re.findall(macro_regex, str1)
  if matches:
      for match in matches:
        env_var =  match.replace(r'%','')
        if env_var in os.environ:
            str1=str1.replace(match,os.environ[env_var])
        else:
            #if the environment variable doesn't exist return none
            str1=None
  return str1
#####################################################################
# get build cmd params
#####################################################################
def get_cmd_params(options,variant_flavor,cprocess_config,tool_config):
  build_cmd = []
  #find component params
  for i in range(len(cprocess_config['Params'])):
    str1 = cprocess_config['Params'][i]
    str1 = replace_arguments(str1)
    build_cmd.append(str1)

  if 'Params' in tool_config and tool_config:
    for i in range(len(tool_config['Params'])):
      str1 = replace_arguments(tool_config['Params'][i])
      build_cmd.append(str1)
      if tool_config['Params'][i] == "-t":
        variant_flavor.compiler = tool_config['Params'][i+1]
        ARGUMENTS['$COMPILER'] = variant_flavor.compiler

   # Set FEATURE_FLAGS environment variable, dsc will pass to compiler
  if options.compiler_flags:
     os.environ["FEATURE_FLAGS"] = options.compiler_flags
  return build_cmd

#####################################################################
# get tool path
#####################################################################
def get_tool_cmd(tool_config):
  tool_cmd = []
  str1=None
  #find tool path
  if 'Path' in tool_config:
      #parser tool path item ,if there are multi tool paths, find the first available tool path
      if isinstance(tool_config['Path'],type([])):
        for tool_path in tool_config['Path']:
            tool_path = replace_arguments(tool_path)
            if tool_path != None and os.path.exists(tool_path):
                str1 = tool_path
                break
      else:
        if 'arm-elfcopy' in tool_config['Path']:
          tool_config['Path'] = os.getenv("CLANG1400LINUX_ELFCOPY")
        str1=( tool_config['Path'].encode('ascii'))
        str1 = replace_arguments(str1)

      if str1!= None and  os.path.exists( str1 ):
        # append the tools to the command line
        tool_cmd.append(str1)
        # if 'SetMacro' item exists, set local Macro definitions.
        # if the Macro value is @Path, that means available tool path will set to the Macro
        if 'SetMacro' in tool_config:
            for key in tool_config['SetMacro']:
               if re.findall("@Path", tool_config['SetMacro'][key]):
                  if os.path.isdir(str1):
                    ARGUMENTS[key] = str1
                  else:
                    ARGUMENTS[key] = os.path.dirname(str1)
               else:
                   ARGUMENTS[key] = tool_config['SetMacro'][key]
      else:
        logger.error ("[buildex.py] ERROR: tool path: {} doesn't exist".format(str1))
        sys.exit(-1)
      #if tool is py script add python to the command line
      if os.path.splitext(tool_cmd[0])[1]  == ".py":
        tool_cmd.insert(0,"python")
  return tool_cmd

#####################################################################
# get xbl_sec path
#####################################################################
def get_xbl_sec_path(process_action):
  xbl_sec_path = ""
  #find tool path
  if 'SecImage' in process_action:
      str1 = ( process_action['SecImage'])
      str1 = replace_arguments(str1)
      xbl_sec_path=str1
  return xbl_sec_path

#####################################################################
# pre parser json file
# remove comments from json file
#####################################################################
def pre_parser_json_file(json_file):
  json_content = remove_json_comments(json_file,None)
  try:
    json_config = json.loads(json_content)
  except Exception as error:
    logger.error("[buildex.py] ERROR: pre_parser_json_file::paser: " + \
                            json_file + str(error))
    sys.exit(-1)
  return json_config

##############################################################################
# search_valid_dirs with regex
##############################################################################
def search_valid_dirs(search_path, regex):
  valid_dirs = []
  for f in os.listdir(search_path):
    if re.search(regex, f):
      valid_dirs += [os.path.join(search_path, f)]
  return valid_dirs

##############################################################################
# search_dir
##############################################################################
def search_dir(search_path, target):
  valid_dirs = []
  for f in os.listdir(search_path):
    if target.upper()== f.upper():
      valid_dirs += [os.path.join(search_path, f)]
  return valid_dirs

##############################################################################
# compare_files(file1_path,file2_path)
##############################################################################
def compare_files(file1_path,file2_path):
  f1, f2 = None, None
  file_compare = 0
  try:
    size1 = os.path.getsize(file1_path)
  except Exception as err:
    logger.error("[buildex.py] ERROR: {}".format(err))
    sys.exit(-1)

  try:
    size2 = os.path.getsize(file2_path)
  except Exception as err:
    logger.error("[buildex.py] ERROR: {}".format(err))
    sys.exit(-1)

  if size1 != size2:
    file_compare = -1

  if file_compare == 0:
    try:
      f1 = open(file1_path,"r")
    except IOError:
      logger.error( "[buildex.py] ERROR: {} does not exist!".format(file1_path))
      sys.exit(-1)
    try:
      f2 = open(file2_path,"r")
    except IOError:
      f1.close()
      logger.error( "[buildex.py] ERROR: {} does not exist!".format(file2_path))
      sys.exit()
    while 1:
      line1 = f1.readline()
      line2 = f2.readline()
      if line1 != line2:
         file_compare = -1
         break
      if not line1 or not line2:
         break
    f1.close()
    f2.close()
  return file_compare

##############################################################################
# merge_json_cfgs(json1,json2)
##############################################################################
def merge_json_cfgs(json1,json2):
  # if both json are present
  if len(json1) and len(json2):
    # add json2 objest and images along with the process to original build_config
    for k in list(json1.keys()):
      if k in list(json2.keys()):
        json1[k].extend(json2[k])

    # check if same object are present after merging json
    for k in list(json1.keys()):
      json1 =[]
      for dict_v in jons1[k]:
        dict_list.append(dict_v['Name'])
      if len(dict_list) != len(set(dict_list)):
        sys.exit("duplicate entry in "+k+" found")
  # if only json2 is present
  elif len(json2) and len(json1)==0:
    json1 = json2

  return json1
##############################################################################
# init_work_path
##############################################################################
def init_work_path(imgrootpath):
  build_root_path = ""
  curpath = imgrootpath
  packages_paths=""
  if imgrootpath == "":
    curpath=os.path.dirname(os.path.realpath(__file__))
  else:
    if os.path.split(imgrootpath)[1]!="boot_images":
      logger.error( "[buildex.py] ERROR: imgrootpath is not boot_images path")
      sys.exit(0)

  # traversing the folders in current path
  for i in range(2):
    #traversing the folders in curpath
    if os.path.split(curpath)[1]=="boot_images":
      build_root_path = curpath
      break
    dirs = os.listdir(curpath)
    if "boot_images" in dirs:
      if dirs.count('boot_images') > 1:
         logger.error( "[buildex.py] ERROR: There are more then one boot_images folder under current path")
         sys.exit(1)
      else:
         build_root_path = os.path.join(curpath,'boot_images');

         break;
    else:
    # traversing the folders in upper path
      curpath = os.path.split(curpath)[0]
  if build_root_path == "":
    logger.error( "[buildex.py] ERROR: Can't find image root path")
    sys.exit(-1)

  os.environ["WORKSPACE"] = os.path.join(build_root_path,'boot')
  dirs = os.listdir(build_root_path)


  for dir in dirs:
    dirpath = build_root_path+os.sep+dir
    if os.path.isdir(dirpath):
      if packages_paths=='':
        packages_paths+=dirpath
      else:
        if platform.system()=='Windows':
          packages_paths+=";"+dirpath
        else:
          packages_paths+=":"+dirpath

  os.environ["PACKAGES_PATH"]=packages_paths
  os.environ["BUILDROOT"]=build_root_path
  ARGUMENTS["$BUILDROOT"]=build_root_path
  ARGUMENTS["$BOOTTOOLS"]=os.path.join(build_root_path,'boot_tools')
  os.environ["BOOTTOOLS"]=os.path.join(build_root_path,'boot_tools')
##############################################################################
# init_conf
##############################################################################
def init_conf_folder(imgrootpath):
  Conf_def_path=''
  Conf_path=''
  #for old boot code structure. Conf folder is under boot_image folder
  for root,directories, files in os.walk(imgrootpath):
      if 'BaseTools' in directories:
          Conf_def_path = os.path.join(root,'BaseTools','Conf')
          Conf_path = os.path.join(root,'Conf')
          ARGUMENTS["$EDK2ROOT"]= root
          os.environ["EDK2ROOT"]= root
          break;
  if Conf_def_path != '':
    for conf_file in conf_files:
      if os.path.exists(os.path.join(Conf_path,conf_file+".txt") ):
        if compare_files(os.path.join(Conf_path,conf_file+".txt"),os.path.join(Conf_def_path,conf_file+".template")) != 0:
          logger.info( "Buildex:: delete file {}".format(os.path.join(Conf_path,conf_file+".txt")))
          os.remove(os.path.join(Conf_path,conf_file+".txt"))
  else:
     logger.error( "[buildex.py] ERROR: can't find BaseTools!!!")
     sys.exit(-1)

##############################################################################
# setup_environment
##############################################################################
def setup_environment(imgrootpath):

  logger.info(( "[buildex.py] Building on {}".format(platform.system())))
  make_name = ""
  edksetuppath = ''
  tools_config={}
  operation_name = ''
  env_var_value = ''
  line = None
  #For old boot code structure, search edksetup.bat in image root folder
  #For new boot code structure, check it in EDK2 folder.
  for root,directories,files in os.walk(imgrootpath):
    if 'edksetup.bat' in files:
      edksetuppath = root
      break;

  #If it doesn't exist, report ERROR and exit
  if edksetuppath =='':
    logger.error( "[buildex.py] ERROR: can't find edksetup.bat")
    sys.exit(-1)

  if platform.system() == "Windows":
    make_name = "nmake.exe"
    EDK_ENV_FLAG = 'EDK_ENV_STARTS_HERE'
    os.chdir(edksetuppath)
    try:

      edk_output = subprocess.check_output('edksetup.bat && echo ' + EDK_ENV_FLAG + ' && set', shell=True)
    except Exception as error:
      logger.error("[buildex.py]  ERROR: {}".format(str(error)))
      sys.exit(-1)
    parse_and_set_edk_env(edk_output, EDK_ENV_FLAG)

  else:
    make_name = "make"
    os.environ["ARMLMD_LICENSE_FILE"] = DEFAULT_ARM_LICENSE_FILE
    curr_dir = os.getcwd()
    os.chdir(edksetuppath)
    edk_command = ['bash', '-c', 'source edksetup.sh BaseTools && env']
    try:
      proc = subprocess.Popen(  edk_command, stdout=subprocess.PIPE)
      for line in proc.stdout:
        if isinstance(line,bytes):
          line = line.decode()
        (key, _, value) = line.partition("=")
        os.environ[key] = value.strip()
      proc.communicate()
      os.chdir(curr_dir)
    except Exception as e:
      logger.error("[buildex.py] ERROR: Runing {} with error {}",edk_command,e)
      sys.exit(-1)
    # Check if nmake.exe/make.exe is in PATH
    make_found = False
    for path in os.environ["PATH"].split(os.pathsep):
      if os.path.exists(os.path.join(path, make_name)):
        make_found = True
        break
    if not make_found:
      logger.error("[buildex.py] ERROR: setup_environment: " + make_name +\
                      " not found in PATH")
      sys.exit(-1)

  if "WORKSPACE" not in os.environ:
    logger.error("[buildex.py] ERROR: setup_environment: " + \
                    "Failed to setup environment variable WORKSPACE.")
    sys.exit(-1)

  # Check that boot_images folder exists, there are dependencies on this
  if BOOT_IMAGES_DIR not in os.environ["WORKSPACE"]:
    logger.error("[buildex.py] ERROR: setup_environment: " + \
                    "Build root folder 'boot_images' is missing. Please ensure this folder exist.")
    sys.exit(-1)

  # Each component can has its own toolchainconfig.json
  # Merger all the tool chain json configs
  build_root_path = os.environ['BUILDROOT']

  dirs = os.listdir(build_root_path)
  for dir in dirs:
    if os.path.isdir(os.path.join(build_root_path,dir)):

      if os.path.exists(os.path.join(build_root_path,dir,"toolchainconfig.json")):
         #delete comments from toolchainconfig.json file
        tool_chian_json_config=remove_json_comments(os.path.join(build_root_path,dir,"toolchainconfig.json"),None)
        tools_config2 = json.loads(tool_chian_json_config)
        tools_config=merge_json_cfgs(tools_config,tools_config2)

  if len(tools_config)==0:
    sys.exit("[buildex.py] ERROR: Can't find toolchainconfig.json in all components folder!!!")

  # Export the OS environment variables
  operation_name = platform.system()

  for key in list(tools_config['ToolChain'].keys()):
   tool_config={}
   if operation_name in tools_config['ToolChain'][key]:
     tool_config=tools_config['ToolChain'][key][operation_name]
   else:
     tool_config=tools_config['ToolChain'][key]
   if "Export" in list(tool_config.keys()):
     for env_key in list(tool_config['Export'].keys()):
       env_var_value = tool_config['Export'][env_key]
       if tool_config['Export'][env_key] == '@Path':
          tool_cmd=get_tool_cmd(tool_config)
          if len(tool_cmd) == 1:
            env_var_value = tool_cmd[0]
       if os.environ.get(env_key)==None:
         os.environ[env_key]=tool_config['Export'][env_key]
         macro_name='${}'.format(env_key)
         ARGUMENTS[macro_name] = tool_config['Export'][env_key]
       elif env_key == "PATH":
         os.environ["PATH"]+=tool_config['Export'][env_key]

  # Enable sectools and set sectools_policy
  os.environ["USE_SECTOOLS"] = "1"
  os.environ["SECTOOLS_POLICY"] = "USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN"
  os.environ["USES_PLATFORM_IMAGE_INTEGRITY_CHECK"] = "1"
  os.environ[os.environ["SECTOOLS_POLICY"]] = "1"

  if "$SECTOOLSROOT" not in ARGUMENTS:
    ARGUMENTS["$SECTOOLSROOT"]= os.environ["SECTOOLS_DIR"]

  # Disable to generate __pycache__ folder under python3
  os.environ["PYTHONDONTWRITEBYTECODE"] = '1'


  if DEVDEBUG:
    logger.debug(( "[buildex.py] WORKSPACE:" + os.environ["WORKSPACE"]))
    logger.debug( "[buildex.py] Environment\n")
    logger.debug(os.environ)
  return tools_config

#####################################################################
# set compiler path
#####################################################################
def set_compiler_path(tool_config,tool_name):
   COMPILER_NAME = tool_name;
   COMPILER_BIN_NAME = '{}_BIN'.format(COMPILER_NAME)
   COMPILER_PREFIX  = '{}_ARM_PREFIX'.format(COMPILER_NAME)
   if os.path.exists(os.getenv("CLANG1400LINUX_BIN")):
     os.environ[COMPILER_BIN_NAME] = os.getenv("CLANG1400LINUX_BIN") + "/"
   else:
     logger.error("[buildex.py] ERROR: Tool path {} does not exist!".format( os.getenv("CLANG1400LINUX_BIN")))
     logger.error("[buildex.py] ERROR: build_single_flavor: " + \
                        "Missing LLVM tool chain." + \
                        "Expected location " + os.environ[COMPILER_BIN_NAME])
     sys.exit(-1)
     
   if os.path.exists(os.getenv("CLANG1400LINUX_TOOLS_BIN")):
     os.environ[COMPILER_PREFIX] = os.getenv("CLANG1400LINUX_TOOLS_BIN") + "/"
   else:
     logger.error("[buildex.py] ERROR: {} does not exist".format(os.getenv("CLANG1400LINUX_TOOLS_BIN")))
     logger.error("[buildex.py] ERROR: build_single_flavor: " + \
                        "Missing LLVM tool chain." + \
                        "Expected location " + os.environ[COMPILER_PREFIX])
     sys.exit(-1)
   if platform.system() == "Windows":
     os.environ["MAKE_PATH"] = "nmake"
     os.environ["MAKE_FLAGS"] = "/C"
   else:
     os.environ["MAKE_PATH"] = "make"
     os.environ["MAKE_FLAGS"] = ""

   is_bin_exist = False
   for path in os.environ["PATH"].split(os.pathsep):
      if path == os.getenv(COMPILER_BIN_NAME):
        is_bin_exist = True
        break
   if not is_bin_exist:
      os.environ["PATH"] = os.environ[COMPILER_BIN_NAME]+ os.pathsep + os.environ["PATH"]

##############################################################################
# parse_and_set_edk_env
##############################################################################
def parse_and_set_edk_env(edk_output, EDK_ENV_FLAG):

  # Go through every line
  # Skip until 'ENDFLAG'
  # Then add everything in env to current env
  # Note: Multi-line env variables are not supported, each
  # multi-line variable will be skipped in this processing
  skipping = True
  line = None
  for line in edk_output.splitlines():
    if isinstance(line,bytes):
        line = line.decode()
    if not skipping:
      try:
        if line.find('=') != -1:
          envvar = line[0:line.index('=')]
          envval = line[line.index('=')+1:]
          os.environ[envvar] = envval
        else:
          envvat=line
          envval = envval + envvat
          if envvar != NULL:
            os.environ[envvar] = envval
      except ValueError:
        logger.warn( "[buildex.py] WARNING: failed to parse line {}".format(line))
    elif re.search(EDK_ENV_FLAG, line):
      skipping = False
  return

##############################################################################
# create_build_version
##############################################################################
def create_build_version(build_version):
  build_version_file = os.path.join(os.environ["WORKSPACE"],
                                               QCOM_DIR,
                                               "Include",
                                               "BuildVersion.h" )

  if os.path.isfile(build_version_file) and build_version == "0":
    logger.info( "[buildex.py] QcomPkg\Include\BuildVersion.h already exists.")
    logger.info( "[buildex.py] No build version specified. Will use existing version.")
    return

  logger.info(( "[buildex.py] Creating QcomPkg\Include\BuildVersion.h with version: " + build_version))
  try:
    with open(build_version_file, 'w') as vf:
      vf.write("/* DO NOT EDIT: This file is autogenerated */\n")
      vf.write("#ifndef __BUILDVERSION_H__\n")
      vf.write("#define __BUILDVERSION_H__\n\n")
      vf.write("#ifndef UEFI_BUILD_VERSION\n")
      vf.write("  #define UEFI_BUILD_VERSION        \"" + build_version + "\"\n")
      vf.write("#endif\n\n")
      vf.write("#endif /* __BUILDVERSION_H__ */\n")
  except Exception as e:
    logger.error("{}{}{}".format("[buildex.py] ERROR: create_build_version ",e,"Unable to build version file"))

##############################################################################
# create_firehose_version
##############################################################################
def create_firehose_version(firehose_version):
  firehose_version_file = os.path.join(os.environ["WORKSPACE"],
                                               QCOM_DIR,
                                               "Library",
                                               "DevPrgSomcLib",
                                               "FirehoseVersion.h")

  if os.path.isfile(firehose_version_file) and firehose_version == "":
    logger.info( "[buildex.py] QcomPkg/Library/DevPrgSomcLib/FirehoseVersion.h already exists.")
    logger.info( "[buildex.py] No firehose version specified. Will use existing version.")
    return

  logger.info(( "[buildex.py] Creating QcomPkg/Library/DevPrgSomcLib/FirehoseVersion.h with version: " + firehose_version))
  try:
    with open(firehose_version_file, 'w') as vf:
      vf.write("/* DO NOT EDIT: This file is autogenerated */\n")
      vf.write("#ifndef __FIREHOSEVERSION_H__\n")
      vf.write("#define __FIREHOSEVERSION_H__\n\n")
      vf.write("#ifndef FIREHOSE_REV_STR\n")
      vf.write("  #define FIREHOSE_REV_STR        \"" + firehose_version + "\"\n")
      vf.write("#endif\n\n")
      vf.write("#endif /* __FIREHOSEVERSION_H__ */\n")
  except Exception as e:
    logger.error("{}{}{}".format("[buildex.py] ERROR: create_firehose_version ",e,"Unable to build firehose version file"))

##############################################################################
# make_edk_tools
##############################################################################
def make_edk_tools():
  if os.path.exists(os.path.join(os.environ["EDK2ROOT"], "BaseTools")):
    if os.path.exists(os.path.join(os.environ["EDK2ROOT"], "BaseTools","Source","Python")):
      os.environ['PYTHONPATH']=os.path.join(os.environ["EDK2ROOT"], "BaseTools","Source","Python")

  if platform.system() == "Windows":
    return

  workspace_file = os.path.join(os.environ["EDK2ROOT"], "BaseTools", "workspace.txt")

  # Skip building if file exists and current workspace matches
  if os.path.isfile(workspace_file) and \
     os.environ["EDK2ROOT"] == open(workspace_file).read().strip():
    logger.info( "[buildex.py] Using prebuilt tools")
    return

  tools_path = os.path.join(os.environ["EDK2ROOT"], "BaseTools")

  # Clean build tools if it already exists
  if not os.path.isdir(os.path.join(os.environ["EDK2ROOT"],"BaseTools","Source","C", "bin")):
    subprocess.call(["make", "-C", tools_path, "clean"])

  logger.info( "[buildex.py] Building tools...")
  subprocess.call(["make", "-C", tools_path])
  # write workspace to file
  with open(workspace_file, 'w') as wsf:
    wsf.write(os.environ["EDK2ROOT"])


##############################################################################
# image_version_setup
##############################################################################
def image_version_setup(target, variant, oem_environ):
  image_version_dir = os.path.join(os.environ['WORKSPACE'], 'QcomPkg', 'Library', 'ImageVersionLib')
  image_version_builder = os.path.join(os.environ['BOOTTOOLS'],'scripts', 'version_builder.py')

  version_files = [os.path.join(image_version_dir, 'oem_version.c'),
                   os.path.join(image_version_dir, 'oem_uuid.c'),
                   os.path.join(image_version_dir, 'qc_version.c')]

  for vf in version_files:
    if os.path.isfile(vf): os.remove(vf)

  version_build_cmd = ['python', image_version_builder,
                       '-t', image_version_dir,
                       '-b', target + variant,
                       '-O', oem_environ]
  curr_dir = os.getcwd()
  os.chdir(os.environ["WORKSPACE"])
  logger.info( "[buildex.py] Generating image version file...")

  if platform.system() == "Windows":
    logger.info( "\tPlease be patient. This step may take a while on Windows machines...")

  try:
    subprocess.check_call(version_build_cmd)
  except Exception as error:
    if error.returncode == 1:
      logger.error("[buildex.py] ERROR: image_version_setup:" + \
                      "image version setup failed.")
    elif error.returncode == 2:
      logger.error("[buildex.py] ERROR: image_version_setup:" + \
                      "image version setup failed with following error: " + \
                      "manifest.xml not found!")
    sys.exit(-1)

  for vf in version_files:
    if not os.path.isfile(vf):
      logger.error( "\n[buildex.py] ERROR: Image Version File not generated")
      logger.error("[buildex.py] ERROR:image_version_setup:" + \
                      "image version setup failed to genearte file: " + vf)
      sys.exit(-1)
  logger.info( "Image Version File is generated")

#####################################################################
# search all target path
# if option_target == None, it will return all the folders matched regex "*pkg"
#####################################################################
def search_all_target_path(option_target = None):
  target_paths = []
  boot_dir = os.environ["WORKSPACE"]
  search_path = os.path.join(boot_dir, QCOM_DIR)
  search_soc_path = os.path.join(search_path, SHAREDPKG_DIR)
  # Set Target regex
  if option_target:
    for target in option_target.split(","):
      target_regex = target
      target_match = search_dir(search_path, target_regex)
      if target_match:
        target_paths.append(target_match[0])
      else:
        target_match = search_dir(search_soc_path, target_regex)
        if target_match:
          target_paths.append(target_match[0])
        else:
          logger.error("[buildex.py] ERROR: buildex::search_all_target_path: {} was not found in".format( target ,search_path))
          sys.exit(-1)
  else:
    target_regex = DEFAULT_TARGET_REGEX
    for target_match in search_valid_dirs(search_path, target_regex):
      if os.path.basename(target_match)==SHAREDPKG_DIR: ############### added for socpkg
          for target_num_match in search_valid_dirs(target_match, target_regex):
              target_paths.append(target_num_match)
      else:
          target_paths.append(target_match)

    if len(target_paths) == 0:
      logger.error("[buildex.py] ERROR:search_all_target_path: "\
                      " not found *pkg folder in PATH")
      sys.exit(-1)

  return target_paths

#####################################################################
# find components
#####################################################################
def find_components(image,json_file):
  components = []
  build_json = remove_json_comments(json_file,None)
  build_obj=json.loads(build_json)
  if image:
    for i in range(len(build_obj['CreateImages'])):
      if build_obj['CreateImages'][i]['Name']== str(image):
        components =  build_obj['CreateImages'][i]['Process'][0]['Components']
        break
  else:
    for i in range(len(build_obj['CreateImages'])):
      components.extend( build_obj['CreateImages'][i]['Process'][0]['Components'])
  if len(components) == 0:
    logger.error("[buildex.py] ERROR: find_components: "\
                      " not found components in build_json file")
    sys.exit(-1)
  return components


#####################################################################
# find components
#####################################################################
def find_dsc_path_from_configuration(cmd):
  components = []
  for i in range(len(cmd)):
    if cmd[i] == "-p":
      return (cmd[i+1])

#####################################################################
# match images
# find all the images
#####################################################################
def match_images(matchimages,json_libs):
  images = []
  if matchimages:
    for matchimage in matchimages.split(","):
      for i in range(len(json_libs['CreateImages'])):
        if json_libs['CreateImages'][i]['Name'].upper() == str(matchimage).upper():
          images.append(json_libs['CreateImages'][i]['Name'])
  else:
    for i in range(len(json_libs['CreateImages'])):
      images.append(json_libs['CreateImages'][i]['Name'])
  if len(images) == 0:
    logger.error("[buildex.py] ERROR: buildex::match_images: "\
                      " not found images in build_json file")
    sys.exit(-1)
  return images

#####################################################################
# search all build json path
#####################################################################
def search_all_build_json_path(target_paths):
  build_json_paths = []
  build_json_regex = "buildconfig.json"

  for target_path in target_paths:
    current_build_json_paths = search_valid_dirs(target_path,build_json_regex)
    if len(current_build_json_paths):
      build_json_paths.append(current_build_json_paths[0])
    else:
      logger.error(( "[buildex.py] ERROR: There is no build json file "+target_path+ " in this path"))

  if len(build_json_paths) == 0:
   logger.error( "!!!!!!!!!!!!!!!no build json file found!!!!!!!!!!!!")
   logger.error("[buildex.py] ERROR: buildex::search_all_build_json_path: "\
                      " not json file found in PATH")
   sys.exit(-1)
  return build_json_paths

#####################################################################
# search build json path
#####################################################################
def search_build_json_path(target_path,build_json_regex):
  current_build_json_paths = search_valid_dirs(target_path,build_json_regex)
  if len(current_build_json_paths) == 0:
    return ""
  else:
    return (current_build_json_paths)[0]
##############################################################################
# find_tag_in_descriptor_file
##############################################################################
def find_tag_in_descriptor_file(dsc, section, tag):
  with open(os.path.join(os.environ["WORKSPACE"], dsc), 'r') as f:

    if section:
      in_desired_section = False
    else:
      in_desired_section = True

    for line in f.readlines():
      # Check if entering new section, only if section is provided
      if section:
        section_search = re.search("\[(\S+)\]", line)
        if section_search:
          # Check if entering desired section
          if section_search.group(1) == section:
            in_desired_section = True
          elif in_desired_section:
            # Hit new section, and already hit desired
            # No tag was found, return early
            return ""

      if in_desired_section or not section:
        expr = tag + "\s*=\s*(\S+)"
        tag_search = re.search(expr, line)
        if tag_search:
          return tag_search.group(1)

  # Not found anywhere
  return ""

def find_next_param_from_list(parms_list,param_name):
  if param_name in parms_list :
    index = parms_list.index(param_name)
    return parms_list[index+1]
  else:
    return ""
##############################################################################
# perform_merges
##############################################################################
def perform_merges(options,dll_paths, variant_flavor,process_action,merge_tool_config):
  xbl_sec = ""
  dlls = dll_paths
  cxbl_cmd = []
  output_name = os.path.basename(find_next_param_from_list(process_action['Params'],'-o'))
  if 'SecImage' in process_action:
    xbl_sec = process_action['SecImage']

  if merge_tool_config:
   cxbl_tool_cmd = get_tool_cmd(merge_tool_config)

  #
  # createxbl single
  #
  single_dll =""
  if len(dlls) == 1:
    single_dll = replace_arguments(dlls[0])

  if single_dll:
    # Skip createxbl step to avoid stripping symbols
    if output_name.split('.')[0].lower() in COPY_IMAGES_AS_IS:
      merged_output_elf = replace_arguments(dlls[0])
    else:
      # Single merge
      ARGUMENTS['$FIRSTDLL']= single_dll
      ARGUMENTS['$SECONDDLL']= ""
      ARGUMENTS['$XBLSEC']= get_xbl_sec_path(process_action)

      cxbl_cmd = get_cmd_params(options,variant_flavor,process_action,merge_tool_config)

      # Run merge command
      try:
        subprocess.check_output( cxbl_tool_cmd + cxbl_cmd)
      except Exception as error:
        logger.error("[buildex.py] ERROR: perform_merges: " + \
                        "Failed to merge with error: " + str(error))
        sys.exit(-1)

  #
  # createxbl multiple merge
  #
  else:

    first_dll = replace_arguments(dlls[0])
    num_dlls = len(dlls)
    ARGUMENTS['$FIRSTDLL'] = first_dll
    ARGUMENTS['$XBLSEC']= get_xbl_sec_path(process_action)
    for x in range(1,num_dlls):
      # grab the next dll
      second_dll = replace_arguments(dlls[x])
      ARGUMENTS['$SECONDDLL'] = second_dll

      # Everything is always merged into 64-bit elfs
      cxbl_cmd = get_cmd_params(options,variant_flavor,process_action,merge_tool_config)
      # if not final merge
      if x < (num_dlls - 1):
        cxbl_cmd.append('-n')
      cmd = cxbl_tool_cmd + cxbl_cmd
      # Run merge command
      try:
        cmd_output = subprocess.check_output( cmd_output)
      except Exception as error:
        logger.error("[buildex.py] ERROR: Runing {} with error:{}".format(cmd, error))
        sys.exit(-1)
      first_dll = find_next_param_from_list(cxbl_cmd,"-o")
      ARGUMENTS['$FIRSTDLL'] = first_dll
      ARGUMENTS['$XBLSEC']= ""
  variant_flavor.merged_output_elf = output_name
  variant_flavor.output_name = output_name
  output_dir_root = os.path.dirname(find_next_param_from_list(cxbl_cmd,'-o'))
  return [output_dir_root, output_name]




##############################################################################
# generate_merge_items
#   merge_dict= merge_book()
##############################################################################
def generate_merge_item(merge_dict,dsc_path,variant_flavor,process_config):
  # Check for normal merges of images inside dsc
  # check for fdf
  #dsc=[dsc_path,variant_flavor.aarch]
  fdf_file = find_tag_in_descriptor_file(dsc_path, "Defines", "FLASH_DEFINITION")
  if fdf_file:
    build_dir = find_tag_in_descriptor_file(dsc_path, "Defines", "OUTPUT_DIRECTORY")
    if not build_dir:
      build_dir = find_tag_in_descriptor_file(dsc_path, "Defines." + variant_flavor.aarch, "OUTPUT_DIRECTORY")
      if not build_dir:
        logger.error("[buildex.py] ERROR: buildex::handle_fdf_file: " + \
                      "Unable to find OUTPUT_DIRECTORY tag in dsc: " + dsc_path)
        sys.exit(-1)
    build_dir=replace_arguments(build_dir)
    if os.path.exists(build_dir):
      FVMAIN_COMPACT_path = os.path.join(
                          build_dir,
                          variant_flavor.release_mode + "_" + variant_flavor.compiler,
                          "FV","FVMAIN_COMPACT.elf")
    else:
      FVMAIN_COMPACT_path =  os.path.join(os.environ["WORKSPACE"],
                          build_dir,
                          variant_flavor.release_mode + "_" + variant_flavor.compiler,
                          "FV","FVMAIN_COMPACT.elf")
    return FVMAIN_COMPACT_path

  #Check for any merge entries inside DSC
  with open(os.path.join(os.environ["WORKSPACE"],dsc_path), 'r') as d:
    # skip to [Components.common]
    while not re.search('\[Components.common\]', d.readline()):
      pass

    # Search for infs now
    inf =  ""
    bracket_count = 0

    for line in d.readlines():

      # 0 implies not inside inf block yet
      if bracket_count == 0:

        # skip commented lines if outside of an inf block
        if line.lstrip().find("#") == 0:
          continue

        # look for open bracket, start of inf block
        if line.find(".inf") != -1 and line.find("{") != -1:
          bracket_count = 1
          inf = re.search("(\S+.inf)", line).group(1)

      elif bracket_count > 0:
        #Inside INF
        if line.find("{") != -1:
          bracket_count = bracket_count + 1
        elif line.find("}") != -1:
          bracket_count = bracket_count - 1
          # Upon closing brackets, validate and add merge item


        if bracket_count < 0:
          logger.error("[buildex.py] ERROR: buildex::generate_merge_items: " + \
                          "Malformed dsc file: " + dsc_path)
          sys.exit(-1)

      if bracket_count == 0 and inf:
        return get_dll_from_dsc_inf(variant_flavor,dsc_path,inf)

##############################################################################
# get_dll_from_dsc_inf
##############################################################################
def get_dll_from_dsc_inf(variant_flavor,dsc_path,inf):
  arch = variant_flavor.aarch
  output_dir = ""
  for section in ["Defines", "Defines." + arch]:
    result = find_tag_in_descriptor_file(dsc_path, section, "OUTPUT_DIRECTORY")
    if result:
      output_dir = result
  if not output_dir:
    logger.error("[buildex.py] ERROR: get_dll_from_dsc_inf: " + \
                    "Missing OUTPUT_DIRECTORY tag in dsc: {}".format(dsc_path))
    sys.exit(-1)

  output_dir = replace_arguments(output_dir)

  if os.path.exists(output_dir)==True:
    dll_path = os.path.join(
                              output_dir,
                              variant_flavor.release_mode + "_" + variant_flavor.compiler,
                              arch,
                              inf.split(".inf")[0],
                              "DEBUG",
                              find_tag_in_descriptor_file(inf, "Defines", "BASE_NAME") + ".dll")
  else:
    dll_path = os.path.join(os.environ["WORKSPACE"],
                              output_dir,
                              variant_flavor.release_mode + "_" + variant_flavor.compiler,
                              arch,
                              inf.split(".inf")[0],
                              "DEBUG",
                              find_tag_in_descriptor_file(inf, "Defines", "BASE_NAME") + ".dll")
  return dll_path


##############################################################################
# append_build_products
##############################################################################
def append_build_products(built_items):
  for item in built_items:
    output_dir = item[0]
    file_name = item[1]
    bp_cmd = ['python', os.path.join(os.environ['BOOTTOOLS'],'scripts','buildproducts_builder.py'),
            '-t', os.path.join(os.environ["WORKSPACE"],'..','..'),
            '-s', output_dir,
            '-i', file_name]
    if isinstance(bp_cmd,bytes):
       bp_cmd=bp_cmd.decode()
    try:
      subprocess.check_output(bp_cmd)
    except Exception as err:
      logger.error("[buildex.py] ERROR: Running {} with error:{}".format(bp_cmd,err))
      sys.exit(-1)

if __name__ == "__main__":
  main()

#!/usr/bin/env python


#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 01/13/22   yps      Added correct_case_of_path function
# 11/16/21   yps      Fix SPF pack issue
# 03/18/21   yps      Fix packit issue for tme component
# 12/17/20   yps      Initial release


from optparse import OptionParser
import shutil
import os
import sys
import locale
import stat
import re
import json
import platform
import multiprocessing
import logging
import fnmatch
import subprocess
import time
from delcomments import *

logging.basicConfig(filename='packit_logger.log',level=logging.INFO, format='%(asctime)s - %(levelname)s - line%(lineno)s - %(message)s',filemode='w')
logger = logging.getLogger(__name__)
#filehandler = logging.FileHandler("packit_log.txt")
formatter = logging.Formatter('%(asctime)s - %(levelname)s - line%(lineno)s - %(message)s')
#filehandler.setFormatter(formatter)

console = logging.StreamHandler()
console.setFormatter(formatter)

#logger.addHandler(filehandler)
logger.addHandler(console)


def correct_path_sep(path):
  if platform.system() == "Windows":
    path = path.replace("\\\\", '\\', 100)
    path = path.replace('/', '\\', 100)
  else:
    path = path.replace("\\\\", '/')
    path = path.replace('\\', '/')
  return path

def clear_readonly(func , path, _):
    os.chmod(path, stat.S_IWRITE)
    func(path)

def check_target_folder(targets,walk_top_dir):
  target_folders_exist = {}
  logger.debug("walk top dir is %s for targets:%s",walk_top_dir, targets)
  logger.debug(os.getcwd())
  if targets != []:
    for i in range(len(targets)):
      target_folders_exist[targets[i].upper()] = 0;
    for root, dirs, files in os.walk(walk_top_dir):
      if 0 in target_folders_exist.values():
        for i in range(len(targets)):
          if (target_folders_exist[targets[i].upper()] == 0):
            current_other_folder = targets[i].upper()
            for dir in dirs:
              if dir.upper() == current_other_folder:
                targets[i] = dir
                target_folders_exist[targets[i].upper()] = 1
      break
    for key in target_folders_exist:
      if target_folders_exist[key] == 0:
        logger.error("ERROR: %s target folder doesn't exist!", key)
        sys.exit(-1)
  return targets

def find_other_pkgs(targets,walk_top_dir):
   other_pkgs = []
   for target in targets.split(','):
     m=re.search('[A-Z,a-z]+[pkg]$',target,re.IGNORECASE)
     if m:
        other_pkgs.append(target)

   if other_pkgs != []:
     other_pkgs = check_target_folder(other_pkgs,walk_top_dir)
   logger.debug("other pkgs:%s", other_pkgs)
   return other_pkgs

def find_chipset_pkgs(targets,chip_set_regex,walk_top_dir):
   chipset_pkgs = []
   for target in targets.split(','):
     m=re.search(chip_set_regex,target,re.IGNORECASE)
     if m:
        chipset_pkgs.append(target)
   if chipset_pkgs != []:
     chipset_pkgs = check_target_folder(chipset_pkgs,walk_top_dir)
   logger.debug("chipset pkgs:%s", chipset_pkgs)
   return chipset_pkgs

def check_other_pkgs_build_path(build_directory,other_pkgs):
   other_pkgs_path = []
   for other_pkg in other_pkgs:
     if os.path.isdir(os.path.join(build_directory,other_pkg.split("Pkg")[0])):
        other_pkgs_path.append(os.path.join(build_directory,other_pkg.split("Pkg")[0]))
     else:
        logger.info("[main task] %s is not compiled",other_pkg)
        sys.exit(-1)
   return other_pkgs_path
##############################################################################
# copytree_ignore
##############################################################################
def copytree_ignore(exclude_path, patterns):
  def copytree_ignore_evaluation(eval_directory, names):
    eval_directory
   # logger.debug("ignore eval_directory:%s",eval_directory)
    if eval_directory in exclude_path:
      logger.debug("Bingo %s is in %s",eval_directory,exclude_path)
      ignore = set(name for pattern in patterns for name in fnmatch.filter(names,pattern))
      logger.debug("ignore %s", ignore)
      return ignore
    return []
  return copytree_ignore_evaluation

class packit(object):

  def __init__(self, task_name,options, commonconfig, target_names, variants,other_pkgs,other_pkgs_path):
    self.task_name = task_name
    self.options = options
    self.target_names = target_names
    self.variants = variants
    self.commondirts = json.loads(commonconfig)
    self.release_list = []
    self.packout_list = []
    self.packin_list = []
    self.packlist={}
    self.backlist = []
    self.chipsets = []
    self.ARGUMENTS = {"$TARGET":"",
                      "$VAR":"",
                      "$PACKDIR":"" ,
                      "$PACKBINDIR":"",
                      "$SHAREDTARGETNAME":"",
                      "$CHIPSET":""
                     }
    #Initialize the MACRO $CHIPSET as first Target name
    self.ARGUMENTS['$TARGET'] = self.target_names[0]
    self.ARGUMENTS['$VARS'] = "_".join(self.variants).upper()
    self.max_directory_layer = 0
    #find all chipsets' name
    for target_name in target_names:
      CHIPSET=re.sub("\D","",target_name)  #search chipset number
      if CHIPSET=='':
        m=re.search('[A-Z,a-z]+Pkg$',target_name)
        if m == None:
          self.chipsets.append(target_name)
    
    #Initialize the MACRO $CHIPSET as first chipset name
    self.ARGUMENTS['$CHIPSET'] = self.chipsets[0]
    #Initialize the MACRO $CHIPSET as first variant name
    self.ARGUMENTS['$VAR'] = self.variants[0].upper()
    #Initialize the packdir_name according to the item of 'PACKDIR' in packitcommon.json file
    #If 'PACKDIR' is SRC_$CHIPSET_$VAR , pack dir name will be SRC with first chipset name 
    #and first variant name.
    #For example: "python packit.py -t Lahaina,Cedros -v LAA",pack dir will be SRC_LAHAINA_LAA
    #
    #IF 'PACKDIR' is SRC_$CHIPSET_$VARS, pack dir name will be SRC with first chipset name
    #and all variants name.
    #For example: "python packit.py -t Olympic -v LE,MN",pack dir will be SRC_OLYMPIC_LE_MN
    #NOTE:binarydir_name will follow the same rule
    self.options.packdir_name = self.replace_arguments(self.commondirts['PACKDIR'])
    self.options.binarydir_name = self.replace_arguments(self.commondirts['PACKBINDIR'])
    self.ARGUMENTS['$PACKDIR'] = self.options.packdir_name
    self.ARGUMENTS['$PACKBINDIR'] = self.options.binarydir_name
    
    self.ARGUMENTS['$SHAREDTARGETNAME'] = self.commondirts['shared_target_folder']
    
    self.other_pkgs_path = other_pkgs_path
    self.other_pkgs = other_pkgs
    
    if 'packout_list' in self.commondirts:
      for packout_object in self.commondirts['packout_list']:
        self.packout_list.append(self.replace_arguments(packout_object))
   # if self.other_pkgs != []:
   #   self.target_names.extend(self.other_pkgs)
    logger.info("[%s] Packit start",self.task_name)
    logger.info("[%s] targets name: %s",self.task_name,",".join(self.target_names))
    logger.info("[%s] variants name: %s",self.task_name,",".join(self.variants))
    logger.info("[%s] chipsets name: %s",self.task_name,",".join(self.chipsets))
    logger.info("[%s] packout name is %s",self.task_name, self.options.packdir_name)
  ##############################################################################
  # replace_arguments
  ##############################################################################
  def replace_arguments(self,string):
    arg_regex = "(\$[A-Z]+)"
    if type(string) == type([]):
      return_str = []
      for str in string:
        matches = []
        matches = re.findall(arg_regex, str)
        str1 = str.encode('ascii')
        if isinstance(str1,bytes):
          str1=str1.decode()          
        if matches:
           for match in matches:
            if match in self.ARGUMENTS:
              str1=str1.replace(match,self.ARGUMENTS[match])
            else:
              logger.info("[%s] ERROR::argument %s doesn't exist!!!",self.task_name,match)
              sys.exit(-1)
        return_str.append(correct_path_sep(str1))
      return return_str
    else:
       return_str = ''
       matches = []
       matches = re.findall(arg_regex, string)
       str1 = string.encode('ascii')
       if isinstance(str1,bytes):
         str1 = str1.decode()
       if matches:
          for match in matches:
           if match in self.ARGUMENTS:
             str1=str1.replace(match,self.ARGUMENTS[match])
           else:
             logger.info("ERROR::packit: argument %s doesn't exist!!!",match)
             sys.exit(-1)
       return_str = correct_path_sep(str1)
    return return_str

  ##############################################################################
  # is_target_folder_existing
  ##############################################################################
  def is_target_folder_existing(self):
    if self.commondirts['shared_target_folder']:
      target_root_path = self.replace_arguments(os.path.join(self.options.evaldir_name,self.commondirts['shared_target_folder']))
    else:
      target_root_path = self.replace_arguments(self.options.evaldir_name)
      
    for target_name in self.target_names:
        target_folder_path = os.path.join(target_root_path,target_name)
        if not os.path.isdir(target_folder_path):
          logger.info("[%s] Error target folder %s is not exist under %s",self.task_name,self.options.target_name,target_root_path)
          sys.exit(-1)

  ##############################################################################
  # cleanse_existing_inf_files
  ##############################################################################
  def cleanse_existing_inf_files(self, base_directory):
    logger.info("[%s] Removing PackIt rules from .inf files",self.task_name)
    for root, directories, files in os.walk(base_directory):
      for file_name in files:
        if file_name.lower().endswith(".inf"):
          file_path = os.path.join(root, file_name)
          if '.packit.' in open(file_path).read().lower():
            self.remove_packit_rules(file_path)


  ##############################################################################
  # remove_packit_rules
  ##############################################################################
  def remove_packit_rules(self, file_path):
    new_file_lines = []
    inf_lines = [x.replace('\r','').replace('\n','') \
                 for x in open(file_path).readlines()]
    delete = False
    for line in inf_lines:
      # if the line has [] brackets, it is a section header
      # non-PackIt sections need to be preserved
      if '[' in line and ']' in line:
        if '.packit.' in line.lower():
          # Don't remove the post-build packing instructions
          if 'postbuildpackout' in line.lower():
            delete=False
            new_file_lines.append(line)
          else:
            delete=True
        else:
          delete=False
          new_file_lines.append(line)
      else:
        if delete:
          continue
        else:
          new_file_lines.append(line)

    # Save contents of stripped .inf to new .inf file
    new_file_path = file_path.replace(".inf", "_new.inf")
    f1 = open(new_file_path, 'w+')
    for line in new_file_lines:
      f1.write(line+"\r\n")
    f1.close()

    # Remove previous original .inf file
    if os.path.exists(file_path):
      try:
        os.chmod(file_path, stat.S_IWRITE)
        os.remove(file_path)
        logger.debug("remove_packit_rules: delete %s",file_path)
      except:
        logger.info("[%s] Error encountered while deleting %s",self.task_name,file_path)
        logger.info("[%s] Error info:%s",self.task_name, sys.exc_info()[0])
        sys.exit(-1)
    # Rename newly stripped .inf file as original .inf
    try:
      os.rename(new_file_path, file_path)
    except:
      logger.info("[%s] Error encountered while renaming %s to %s",self.task_name,new_file_path,file_path)
      logger.info("[%s] Error info:%s",self.task_name, sys.exc_info()[0])
      sys.exit(-1)

    return

  ##############################################################################
  # copy_to_pack_dir
  ##############################################################################
  def copy_to_pack_dir(self,destination_directory,
                       source_directory):
    copytree_exclude_path_list = []
    copytree_ignore_list = []
    # Delete old destination directory if it exists
    if os.path.isdir(destination_directory):
      logger.info("[%s] Directory %s exists. Deleting!",self.task_name,destination_directory)

      try:
        shutil.rmtree(destination_directory, onerror=clear_readonly)
      except:
        logger.info("[%s] Error encountered while deleting directory %s",self.task_name,destination_directory)
        logger.info("[%s] Error info:%s",self.task_name, sys.exc_info()[0])
        sys.exit(-1)

    # Verify source directory exists.  Error out if it doesn't.
    if not os.path.isdir(source_directory):
      logger.info("[%s] ERROR: Directory %s does not exist...exiting",self.task_name,source_directory)
      sys.exit(-1)
    temp_chipset = self.ARGUMENTS["$CHIPSET"]
    temp_var = self.ARGUMENTS["$VAR"]
    for chipset in self.chipsets:
      self.ARGUMENTS["$CHIPSET"] = chipset
      for var in self.variants:
        self.ARGUMENTS["$VAR"] = var
        copytree_exclude_path_list.extend(self.replace_arguments(self.commondirts['copytree_exclude_path_list']))
        copytree_ignore_list.extend(self.replace_arguments(self.commondirts['copytree_ignore_list']))
    copytree_exclude_path_list = list(set(copytree_exclude_path_list))
    copytree_ignore_list = list(set(copytree_ignore_list))
    self.ARGUMENTS["$CHIPSET"] = temp_chipset
    self.ARGUMENTS["$VAR"] = temp_var
    
    # Recursively copy source directory to destination
    # Do not include the Build or pack directories
    logger.info("[%s] Copying %s to %s",self.task_name, source_directory , destination_directory)

    try:
      shutil.copytree(source_directory,
                      os.path.join(destination_directory, os.path.basename(source_directory)),
                      ignore=copytree_ignore(copytree_exclude_path_list,
                                           copytree_ignore_list))
    except Exception as error:
      logger.info("[%s] Error encountered while copying %s to %s",self.task_name,source_directory,destination_directory)
      logger.info("[%s] %s",self.task_name,error)
      raise NameError(error)
      sys.exit(-1)
    return

  ##############################################################################
  # change_pack_dir_permissions
  ##############################################################################
  def change_pack_dir_permissions(self, destination_directory):

    # Attempt to change the file permissions of destination_directory
    # to read write.
    logger.info("[%s] Attempting to change file permissions of %s",self.task_name,destination_directory)

    # shutil does not have a recursive option.  Walk the directory.
    try:
      for root, directories, files in os.walk(destination_directory):
        for current_directory in directories:
          os.chmod(os.path.join(root,
                                current_directory),
                   stat.S_IREAD | stat.S_IWRITE)

        for current_file in files:
          os.chmod(os.path.join(root,
                                current_file),
                   stat.S_IREAD | stat.S_IWRITE)
    except:
      logger.info("[%s] Error while changing file permissions.",self.task_name)
      logger.info("[%s] Error info:%s",self.task_name, sys.exc_info()[0])
      sys.exit(-1)
    return


  ########################################################################
  # delete directory and its sub-directories
  ########################################################################
  def delete_dirs(self, path):
    try:
      shutil.rmtree(path, onerror=clear_readonly)
      return
    except:
      logger.info("[%s] Error encountered while deleting:%s",self.task_name,path)
      logger.info("[%s] Error info:",self.task_name, sys.exc_info()[0])
      sys.exit(-1)

  ########################################################################
  # delete all empty dirs
  ########################################################################
  def delete_empty_dirs(self, path):
      if os.path.isdir(path):
          for dir in os.listdir(path):
            self.delete_empty_dirs(os.path.join(path,dir))
          if not os.listdir(path):
            try:
                os.rmdir(path)
                logger.debug("deleted folder:%s",path)
                return
            except:
                logger.info("[%s] Error encountered while deleting:%s", self.task_name, path)
                logger.info("[%s] Error info:", self.task_name, sys.exc_info()[0])
                sys.exit(-1)


  ###############################################################################
  # prepare_release_inf_files
  ###############################################################################
  def prepare_release_inf_files(self, base_directory):
    
    DEFINE_LIST=[]
    logger.info("[%s] Preparing release inf files",self.task_name)

    # Recursively scan directories starting from base_directory looking
    # for "*release.inf" files.  If one is found then delete the non release
    # inf file (*.inf) and replace with release version.
    for root, directories, files in os.walk(base_directory):
      for file_name in files:
        if file_name.lower().endswith("release.inf"):
          # Get module name.  -11 is release.inf
          module_name = file_name[:-11]
          release_inf_path = os.path.join(root, file_name)
          original_inf_path = os.path.join(root, module_name + ".inf")
          # Delete original inf
          if os.path.exists(original_inf_path):
            # Read file line by line looking for sources or binaries
            try:
                packout_entry = False
                with open(original_inf_path) as inf_file:
                    del DEFINE_LIST[:]
                    for line in inf_file:
                        # Ignore lines that begin with #
                        if line.strip().startswith("#"):
                            continue
                        m = re.search('^(\s?DEFINE\s?)([a-zA-Z0-9_]+)(\s?=\s?)([a-zA-Z0-9_./]+)',line)
                        if m!=None:
                          self.ARGUMENTS["{}{}{}".format('$(',m.group(2),')')]= m.group(4)
                          DEFINE_LIST.append("{}{}{}".format('$(',m.group(2),')'))
                        if packout_entry == True:
                            if line == "" or "[" in line:
                                packout_entry = False
                            else:
                                # Line needs to be parsed and assembled
                                assembled_line = self.list_entry_assembler(line,
                                                                           root)
                                if len(assembled_line) > 0:
                                    if packout_entry == True and not assembled_line.endswith('.h'):
                                        self.packout_list.append(self.replace_arguments(assembled_line))
                                        logger.debug("add packout_list:%s according %s , line :%s",assembled_line,original_inf_path, line)
                        if "[sources]" in line.lower() or \
                                "[sources.common]" in line.lower() or \
                                "[binaries]" in line.lower() or \
                                "[binaries.common]" in line.lower():
                            packout_entry = True
                        if self.options.architectures:
                            for architecture in self.options.architectures:
                                if "[sources." + architecture.lower() in line.lower() or \
                                        "[binaries." + architecture.lower() in line.lower():
                                    packout_entry = True
                    for key in DEFINE_LIST:
                      del self.ARGUMENTS[key]

            except:
                logger.info("[%s] Error encountered while reading %s", self.task_name, original_inf_path)
                logger.info("[%s] Error info:%s", self.task_name, sys.exc_info()[0])
                sys.exit(-1)

            try:
              os.chmod(original_inf_path,stat.S_IWRITE)
              os.remove(original_inf_path)
              logger.debug("prepare_release_inf_files: delete %s",original_inf_path)
            except:
              logger.info("[%s] Error encountered while deleting %s",self.task_name,original_inf_path)
              logger.info("[%s] Error info:%s",self.task_name, sys.exc_info()[0])
              sys.exit(-1)

          # Rename release inf to original name
          try:
            os.rename(release_inf_path,
            original_inf_path)
          except:
            logger.info("[%s] Error encountered while renaming %s to %s",self.task_name,release_inf_path,original_info_path)
            logger.info("[%s] Error info:%s",self.task_name,sys.exc_info()[0])
            sys.exit(-1)

    return


  ###############################################################################
  # sanity_check_inf_files
  ###############################################################################
  def sanity_check_inf_files(self,
                             base_directory,
                             architecture_list):

    logger.info("[%s] Sanity checking inf files",self.task_name)

    # Recursively scan directories starting from base_directory looking
    # for ".inf" files.  If one is found then ensure it contains a Sources
    # section or Binaries section but not both.  If architecture is specified
    # then only look at Sources, Sources.common, Sources.<architecture>,
    # Binaries, Binaries.common and Binaries.<architecture>
    for root, directories, files in os.walk(base_directory):
      for file_name in files:
        if file_name.lower().endswith(".inf"):
          source_exists = False
          binary_exists = False

          file_path = os.path.join(root, file_name)

          try:
            if "[sources]" in open(file_path).read().lower():
              source_exists = True

            if "[sources.common]" in open(file_path).read().lower():
              source_exists = True

            if architecture_list:
              for architecture in architecture_list:
                if "[sources." + architecture.lower() in open(file_path).read().lower():
                  source_exists = True

            if "[binaries]" in open(file_path).read().lower():
              binary_exists = True

            if "[binaries.common]" in open(file_path).read().lower():
              binary_exists = True

            if architecture_list:
              for architecture in architecture_list:
                if "[binaries." + architecture.lower() in open(file_path).read().lower():
                  binary_exists = True

          except:
            logger.info("[%s] Error encountered while reading %s",self.task_name,file_path)
            logger.info("[%s] Error info:%s",self.task_name, sys.exc_info()[0])
            sys.exit(-1)

          # Ensure one section or the other exists, but not both
          if source_exists == False and binary_exists == False:
            logger.info("[%s] ERROR: Invalid .inf file %s does not contain a valid Sources or Binaries section.",self.task_name,file_path)
            sys.exit(-1)

          # If the binary from same sources are included in the same inf, would result into linker failure.
          #if source_exists == True and binary_exists == True:
          #  print "ERROR: Invalid .inf file.  " + file_path + " contains a " + \
          #        "Sources and Binaries section."
          #  sys.exit(-1)
    return


  ###############################################################################
  # generate_release_list
  # generate release list depend on source and binaryies item in inf files
  ###############################################################################
  def generate_release_list(self,
                            release_list,
                            base_directory,
                            architecture_list
                            ):

    logger.info("[%s] Parsing source/binaries to generate release list",self.task_name)

    # Recursively scan directories starting from base_directory looking
    # for ".inf" files.  If one is found then add the paths under source,
    # source.common, source.<architecture>,  binaries, binaries.common,
    # binaries.<architecture>, or UserExtensions.PackIt.PackIn to the release
    # list.
    for root, directories, files in os.walk(base_directory):
      for file_name in files:
        if file_name.lower().endswith(".inf"):
          file_path = os.path.join(root, file_name)

          # Read file line by line looking for sources or binaries
          try:
            release_entry = False

            with open(file_path) as inf_file:
              for line in inf_file:
                # Ignore lines that begin with #
                if line.strip().startswith("#"):
                  continue

                if release_entry == True:
                  if line == "" or "[" in line:
                    release_entry = False
                  else:
                    # Line needs to be parsed and assembled
                    assembled_line = self.list_entry_assembler(line,
                                                          root)
                    if len(assembled_line) > 0:
                      if release_entry == True:
                        release_list.append(assembled_line)
                        logger.debug("Release list add:%s  according %s line %s",assembled_line,file_path,line)

                #check if it is source/binary tag line
                if "[sources]" in line.lower() or \
                   "[sources.common]" in line.lower() or \
                   "[binaries]" in line.lower() or \
                   "[binaries.common]" in line.lower():
                  release_entry = True

                if architecture_list:
                  for architecture in architecture_list:
                    if "sources." + architecture.lower() in line.lower() or \
                       "binaries." + architecture.lower() in line.lower():
                      release_entry = True
          except:
            logger.info("[%s] Error encountered while reading %s",self.task_name, file_path)
            logger.info("[%s] Error info:%s",self.task_name,sys.exc_info()[0])
            sys.exit(-1)

    return

  def add_file_into_pack_list(self,
                              file_path,
                              pack_attr,
                              dir_level,
                              debug_inf=""
                              ):
      packfile = file_path
      if pack_attr not in self.packlist:
          self.packlist[pack_attr] = {}
      if dir_level not in self.packlist[pack_attr]:
          self.packlist[pack_attr][dir_level]=[]
          
      pacefile_layers = packfile.split(os.sep)
      if r'*' in pacefile_layers[-1]:
          file_path = os.path.dirname(packfile)
          logger.debug("remove %s from %s",pacefile_layers[-1], packfile)
            
          if os.path.isdir(file_path):
            for file_name in fnmatch.filter(os.listdir(file_path),pacefile_layers[-1]):
              packfile = os.path.join(file_path, file_name)
              self.packlist[pack_attr][dir_level].append(packfile)
              logger.debug("Add packlist[%s][%s]:%s . according inf:%s",
                           pack_attr, dir_level, packfile, debug_inf)
      else:
          self.packlist[pack_attr][dir_level].append(packfile)
          logger.debug("Add packlist[%s][%s]:%s . according inf:%s",
                       pack_attr, dir_level, packfile,debug_inf)
      return
  ###############################################################################
  # generate_packit_list
  ###############################################################################
  def generate_packit_list(self,
                           black_list,
                           packout_list,
                           packin_list,
                           directory,
                           targets,
                           architecture_list,
                           variants,
                           boot_flow,
                           dir_level):

    logger.info("[%s] Parsing PackIt rules from %s",self.task_name,directory)
    packout_list_set={}
    packin_list_set={}
    packout_ignore_list_set={}
    packin_ignore_list_set={}
    current_level = str(dir_level)
    inf_files_list = []
    dirs_list = []
    files_list = []
    # Recursively scan directories starting from base_directory looking
    # for ".inf" files.  If one is found then add the paths under source,
    # source.common, source.<architecture>,  binaries, binaries.common,
    # binaries.<architecture>, or UserExtensions.PackIt.PackIn to the release
    # list.  Also look for UserExtensions.PackIt.Packout and add entries to
    # packout_list.  Pruning of entires might be necessary.
    for file in os.listdir(directory):
      file_path = os.path.join(directory,file)
      if os.path.isdir(file_path):
          dirs_list.append(file_path)
      else:
          files_list.append(file_path)

    for file_name in files_list:
      if file_name.lower().endswith(".inf"):
        file_path = file_name
        # Read file line by line looking for sources or binaries
        try:
          packout_entry = False
          packin_entry = False
          packout_ignore_entry = False
          packin_ignore_entry = False
          with open(file_path) as inf_file:
            for line in inf_file:
             # Ignore lines that begin with #
              if line.startswith("#"):
                continue
              if packout_entry == True or packin_entry == True or packout_ignore_entry == True or packin_ignore_entry == True:
                if line == "" or "[" in line:
                  packout_entry = False
                  packin_entry = False
                  packout_ignore_entry = False
                  packin_ignore_entry = False
                else:
                  # Line needs to be parsed and assembled
                  assembled_line = self.list_entry_assembler(line, directory)
                  if len(assembled_line) > 0:

                    if packout_entry == True:
                        self.add_file_into_pack_list(assembled_line,'packout',current_level,"{}{}{}".format(file_path,"  Line:",line))
                        continue

                    if packout_ignore_entry == True:
                        self.add_file_into_pack_list(assembled_line, 'packout_ignore', current_level,"{}{}{}".format(file_path, "  Line:", line))
                        continue

                    if packin_entry == True:
                        self.add_file_into_pack_list(assembled_line, 'packin', current_level, "{}{}{}".format(file_path, "  Line:", line))
                        continue

                    if packin_ignore_entry == True:
                        self.add_file_into_pack_list(assembled_line, 'packin_ignore', current_level,"{}{}{}".format(file_path, "  Line:", line))
                        continue
              #Find PackIt tags
              for i in range(1):
                if "[userextensions.packit.packout.ignore]" in line.lower():
                  packout_ignore_entry = True
                  break;
                if "[userextensions.packit.packin.ignore]" in line.lower():
                  packin_ignore_entry = True
                  break;
                # Boot flow only
                if "[userextensions.packit.packout." + boot_flow.lower() + "]" in line.lower():
                  packout_entry = True
                  break;
                if "[userextensions.packit.packin." + boot_flow.lower() + "]" in line.lower():
                  packin_entry = True
                  break;
                # Architecture entry can be solely Architecture or Architecture with boot flow appended
                for current_architecture in architecture_list:
                  if "[userextensions.packit.packout."+current_architecture.lower()+"]" in line.lower().lstrip().rstrip() or \
                     "[userextensions.packit.packout."+current_architecture.lower()+"."+boot_flow.lower() in line.lower().lstrip().rstrip():
                    packout_entry = True
                    break;
                  if "[userextensions.packit.packin."+current_architecture.lower()+"]" == line.lower().lstrip().rstrip() or \
                     "[userextensions.packit.packin."+current_architecture.lower()+"."+boot_flow.lower() == line.lower().lstrip().rstrip():
                    packin_entry = True
                    break;

                #Targets_list = targets
                #Targets_list.extend(self.other_pkgs)
                for target in targets:
                  for variant in list(variants):

                      if "[userextensions.packit.packout]".lower() in line.lower():
                          packout_entry = True
                          break
                      if "[userextensions.packit.packout." + target.lower() + "]" in line.lower():
                          packout_entry = True
                          break
                      if "[userextensions.packit.packout." + variant.lower() + "]".lower() in line.lower():
                          packout_entry = True
                          break
                      if "[userextensions.packit.packout." + target.lower() +'.'+ variant.lower() + "]".lower() in line.lower():
                          packout_entry = True
                          break
                      if "[userextensions.packit.packin]" in line.lower():
                          packin_entry = True
                          break
                      if ("[userextensions.packit.packin." + target + "]").lower() in line.lower():
                          packin_entry = True
                          break
                      if ("[userextensions.packit.packin." + variant + "]").lower() in line.lower():
                          packin_entry = True
                          break
                      if ("[userextensions.packit.packin." + target +'.'+ variant + "]").lower() in line.lower():
                          packin_entry = True
                          break

              if packout_entry == True or packin_entry == True or packout_ignore_entry == True or packin_ignore_entry == True:
                 logger.debug("bingo find %s in %s", line, file_path)
        except Exception as error:
          logger.info("[%s] Error encountered while reading %s",self.task_name, file_path)
          logger.info("[%s] Error info:%s",self.task_name, sys.exc_info()[0])
          logger.info("[%s] %s",self.task_name,error)
          sys.exit(-1)
    # generate  final pack out list
    if 'packout' in self.packlist:
        if current_level in self.packlist['packout']:
            if 'packout_ignore' in self.packlist:
                if current_level in self.packlist['packout_ignore']:
                    self.packlist['packout'][current_level]=list(set(self.packlist['packout'][current_level]) - set(self.packlist['packout_ignore'][current_level]))
                    logger.debug("removed ignore packout list, packout_list_set[%s]:%s ", current_level, self.packlist['packout_ignore'][current_level])
            self.packout_list = list(set(self.packout_list)| set(self.packlist["packout"][current_level]))


    if 'packin' in self.packlist:
        if current_level in self.packlist['packin']:
            if 'packin_ignore' in self.packlist:
                if current_level in self.packlist['packin_ignore']:
                    self.packlist['packin'][current_level] = list(set(self.packlist['packin'][current_level]) -set(self.packlist['packin_ignore'][current_level]))
                    logger.debug("removed ignore packin list, packin_list_set[%s]:%s",current_level,self.packlist['packin_ignore'][current_level])
            self.packin_list.extend(self.packlist['packin'][current_level])
            self.packin_list = list(set(self.packin_list))
            self.packout_list = list(set(self.packout_list) - set(self.packlist['packin'][current_level]))



    logger.debug("packout_list[%s]:%s", current_level, self.packout_list)

    for dir_path in dirs_list:
        tick = time.time()
        if dir_path not in self.packout_list:
            logger.debug("search %s not in packout_list time is %.10f, packout_list length is %d",dir_path,time.time()-tick,len(self.packout_list))
            self.generate_packit_list(
                self.backlist,
                self.packout_list,
                self.packin_list,
                dir_path,
                targets,
                architecture_list,
                variants,
                boot_flow,
                dir_level+1)
        else:
          logger.debug("search %s in packout_list time is %.10f, packout_list length is %d",dir_path,time.time()-tick,len(self.packout_list))
        
    logger.debug("return directory level  %s",current_level)
    return


  ###############################################################################
  # list_entry_assembler
  ###############################################################################
  def list_entry_assembler(self,
                           line,
                           path_prefix):

    # Line is raw data from inf file.  It must be parsed as it can contain
    # extra data seperated by |.  Extract file name/path and trim it.
    # The parsed data can contain ".."'s.  This must be taken off the end
    # of path_prefix before final assembly.
    split_line = line.split("|")

    raw_data = ""
    for entry in split_line:
      # Look for "..", or ".c", etc
      if "." in entry or "*" in entry:
        raw_data = entry
        break

    if len(raw_data) == 0:
      # Valid data was not found.
      return raw_data


    # Strip raw_data of leading and training spaces
    raw_data = raw_data.strip()

    # Convert "/" and "\" to proper os specific delimiter.  Do this for not only
    # raw_data but path_prefix.
    raw_data = raw_data.replace("/", os.sep)
    raw_data = raw_data.replace("\\", os.sep)
    path_prefix = path_prefix.replace("/", os.sep)
    path_prefix = path_prefix.replace("\\", os.sep)

    # Join path_prefix and raw_data.  raw_data can have ".." so normalize the path
    release_entry = os.path.normpath(os.path.join(path_prefix, raw_data))
    #logger.debug("assembler line is %s",release_entry)
    return release_entry


  ###############################################################################
  # copy_release_binaries
  ###############################################################################
  def copy_release_binaries(self,
                            build_directory,
                            target_directory,
                            release_list):

    logger.info("[%s] Copying Release Binaries",self.task_name)
    #logger.debug("release_list is %s",release_list)
    walk_list = []


    # Search the release_list looking for .efi, .lib, and .obj files.
    # These files must be copied from the build directory and placed in the
    # source tree so post pack compilations succeed.

    for release_list_file in release_list:
      if ".c" in release_list_file.lower() or \
         ".s" in release_list_file.lower():
          original_file =  release_list_file.lstrip(release_list_file.split(os.sep)[0]+os.sep)
          if os.path.exists(original_file):
            if not os.path.exists(release_list_file):
              if not os.path.exists(os.path.dirname(release_list_file)):
                  os.makedirs(os.path.dirname(release_list_file))
                  logger.debug("create dir %s",os.path.dirname(release_list_file))
              shutil.copyfile(original_file,release_list_file)
              logger.info("copy %s to %s",original_file,release_list_file)
              continue
          else:
              logger.error("release file %s is not exsit",original_file)

      if ".efi" in release_list_file.lower() or \
         ".lib" in release_list_file.lower() or \
         ".obj" in release_list_file.lower():
        logger.info("\nfind release efi,lib or obj file %s", release_list_file)
        binary_split = release_list_file.split(os.sep)
        binary_file = binary_split[len(binary_split) - 1]
        binary_directory = binary_split[len(binary_split) - 2]
        logger.debug("bin file:{} ;bin path:{}".format(binary_file,binary_directory))
        # Find file in build.  If the path contains the proper target,
        # release, and parent folder name then copy the file to the source tree.
        walk_list = []
        logger.debug("self target_name is %s", self.target_names)
        for target_name in self.target_names:
          logger.debug("find binary file from %s build folder",target_name)
          logger.debug("release file path is %s",release_list_file[len(release_list_file.split(os.sep)[0]):])
          
          if re.search(target_name,release_list_file[len(release_list_file.split(os.sep)[0])]) != None:
            logger.debug("bingo %s in release list ",target_name)
            for variant in self.variants:
              logger.debug("check if varaint[%s] in release list",variant)
              regex='('+target_name+r').*('+variant.upper()+')'
              if re.search(regex,release_list_file) != None:
                walk_list.append(os.path.join(build_directory,target_name+variant.upper()))
                break;
            walk_list.append(os.path.join(build_directory,target_name+self.variants[0].upper()))
            break;


        if walk_list == []:
          for target_name in self.target_names:
            for variant in self.variants:
              walk_list.append(os.path.join(build_directory,target_name+variant.upper()))

        if self.other_pkgs_path != []:
          walk_list.extend(self.other_pkgs_path)
          for other_pkg_directory in self.other_pkgs:
            if other_pkg_directory.find("Pkg") !=-1:
               target_directory.append(other_pkg_directory.split("Pkg")[0])
            else:
               target_directory.append(other_pkg_directory)
          target_directory = list(set(target_directory))
        logger.debug("Find binary from %s build folders",walk_list)
        for build_folder in  walk_list:
          logger.debug("build_directory is %s", build_folder)
          for root, directories, files in os.walk(build_folder):
            for possible_file in files:
              if binary_file.lower() == possible_file.lower():
                logger.debug("bingo find binary in %s", root)
                logger.debug("Check binary_directory %s",binary_directory)
                # Check binary_directory
                if binary_directory.lower() in root.lower():
                  logger.debug("Check binary_directory dir successful")
                  logger.debug("root is %s",root)
                  logger.debug("target_directory is %s",target_directory)
                  # Make sure this is right target
                  if any(target_dir.lower() in root.lower() for target_dir in target_directory):
                    logger.debug("Check target dir successful")
                    # Make sure this is a RELEASE build
                    if "RELEASE" in root:
                      logger.debug("Check release folder")
                      try:
                        # release_list_file can contain a path.  Add the missing
                        # directories if needed before copying.
                        if not os.path.isdir(os.path.dirname(release_list_file)):
                          os.makedirs(os.path.dirname(release_list_file))
                        if not os.path.exists(release_list_file):
                          logger.info("bingo copy release file  %s to %s",os.path.join(root, possible_file),release_list_file)
                          shutil.copyfile(os.path.join(root, possible_file),
                                        release_list_file)
                          logger.info("%s has been copied successfully!!\n",release_list_file)
                          break
            
                      except:
                        logger.error("[%s] Error encountered while copying %s",self.task_name,\
                          os.path.join(root, possible_file))
                        logger.error("[%s] Error info: %s",self.task_name, sys.exc_info()[0])
                        sys.exit(-1)
            else:
              continue
            break
          else:
            logger.debug("continue find binary in next build folder")
            continue
          break
         

    return

  def copytree(self,src, dst, symlinks=False, ignore=None):
      if not os.path.exists(dst):
          os.makedirs(dst)
          logger.debug("create dst %s",dst)
      for item in os.listdir(src):
          s = os.path.join(src, item)
          d = os.path.join(dst, item)
          if os.path.isdir(s):
              self.copytree(s, d, symlinks, ignore)
          else:
              if not os.path.exists(d) or os.stat(s).st_mtime - os.stat(d).st_mtime > 1:
                  logger.debug("copytree copy %s to %d",s,d)
                  shutil.copy2(s, d)
  ###############################################################################
  # cleanse_pack_dir
  ###############################################################################
  def cleanse_pack_dir(self,
                       base_directory,
                       packout_list):

    logger.info("[%s] Cleansing pack directory",self.task_name)
    DestDirectorypath = ''
    # Recursively scan directories in base_directory starting from highest
    # inspecting each file.  If the file exists in the release list then keep it.
    # If not then delete it.  Exception is made for files listed in
    # the release_exceptions list.  If a directory is empty then
    # delete it too.

    # New feature added where entries in release list can be a directory instead
    # of an individual file.  After file check is done then compare directory
    # for entry in release list.
    logger.debug("packout list is %s",packout_list)
    # Iterate through the packout list and remove files or directories
    try:
      for packout_entry in packout_list:
        # Check and see if the entry is a file or a directory.  If file just
        # delete it.  If directory delete it and everything underneath it.
        if os.path.isfile(packout_entry):
          os.chmod(packout_entry, stat.S_IWRITE)
          os.remove(packout_entry)
          logger.debug("deleted file %s",packout_entry)
        elif os.path.isdir(packout_entry):
          shutil.rmtree(packout_entry, onerror=clear_readonly)
          logger.debug("deleted folder %s", packout_entry)
    except:
      logger.info("[%s] Error encountered",self.task_name)
      logger.info("[%s] Error info: %s",self.task_name,sys.exc_info()[0])
      sys.exit(-1)

    # check if packin things are in deliverable folders. If it's not in deliverable folder,
    # copy it to deliverable folder
    try:
      for packin_entry in self.packin_list:
        DestDirectorypath =''
        logger.debug("check release file or folder %s",packin_entry)
        # Check and see if the entry is a file or a directory.  If file just
        # delete it.  If directory delete it and everything underneath it.
        if not os.path.exists(packin_entry):
          Source = packin_entry.lstrip(packin_entry.split(os.sep)[0]+os.sep)
          logger.debug("Source path: %s",Source)
          if os.path.exists(Source):

            DestDirectorypath = os.path.dirname(packin_entry)
           #   logger.debug("file path is %d",DestDirectorypath)
            logger.debug ("dest folder path: %s", DestDirectorypath)

            if os.path.isfile(Source):
              if not os.path.exists(DestDirectorypath):
                os.makedirs(DestDirectorypath)
                logger.debug("create dest directory: %s", DestDirectorypath)
              shutil.copyfile(Source,packin_entry)
              logger.debug("Copy packin file:%s",packin_entry)

            else: #copy folders
              logger.debug("Copy %s to %s",Source,DestDirectorypath)
              #os.chmod(DestDirectorypath, stat.S_IWRITE)
              self.copytree(Source, packin_entry)
              logger.debug("Copy packin folder:%s", packin_entry)
          else:
            logger.error("Source %s does not exist",Source)
    except:
      logger.info("[%s] Error info: %s",self.task_name,sys.exc_info())
      sys.exit(-1)
      
    # remove empty folders
    self.delete_empty_dirs(base_directory)
    return

  ###############################################################################
  # post_cleanse_pack_dir
  # clean the source files ('.c', '.cpp', '.s', '.S', '.asm')
  # which are not in release list
  ###############################################################################
  def post_cleanse_pack_dir(self,base_directory):
      release_list = []
      release_list.extend(self.release_list)
      release_list.extend(self.packin_list)
      release_list = list(set(release_list))
      try:
          for root, directories, files in os.walk(base_directory,
                                                  topdown=False):
              for current_file in files:
                  # If file does not exist in release list or exceptions list, delete it.
                  current_file_path = os.path.join(root, current_file)
                  if current_file_path not in release_list:
                      # Check if it is source file
                      if current_file_path.endswith(('.c', '.cpp', '.s', '.S', '.asm')):
                          try:
                              os.chmod(current_file_path, stat.S_IWRITE)
                              os.remove(current_file_path)
                              logger.debug("Cleanse to delete %s", current_file_path)
                          except:
                              logger.info("[%s] Error encountered while deleting %s", self.task_name, \
                                          os.path.join(root, current_file))
                              logger.info("[%s] Error info:", self.task_name, sys.exc_info()[0])
                              sys.exit(-1)

              # All files have been evaluated.  Check to see if directory is empty
              # and delete it if it is.
              if not os.listdir(root):
                  try:
                      os.rmdir(root)
                  except:
                      logger.info("[%s] Error encountered while deleting directory %s", self.task_name, root)
                      logger.info("[%s] Error info:%s", self.task_name, sys.exc_info()[0])
                      sys.exit(-1)
      except:
          logger.info("[%s] Error encountered while reading folder %s", self.task_name, root)
          logger.info("[%s] Error info:%s", self.task_name, sys.exc_info()[0])
          sys.exit(-1)
  ###############################################################################
  # restore_full_directories
  ###############################################################################
  def restore_full_directories(self,
                               pack_directory,
                               branch_directory):

    logger.info("[%s] Restoring full ship directories",self.task_name)

    # Recopy the directories specified by release_directory_recopy.  These are
    # directories that are to be shipped in their entirety.
    for recopy_directory in self.commondirts['release_directory_recopy']:
      # Change path seperator for proper os
      recopy_directory = recopy_directory.replace("/", os.sep)
      recopy_directory = recopy_directory.replace("\\", os.sep)

      self.copy_to_pack_dir(os.path.join(pack_directory, recopy_directory),
                            os.path.join(branch_directory, recopy_directory))

    return
  ##############################################################################
  # generate_paths
  # according path rule generate all the paths with all targets and variants
  ##############################################################################
  def generate_paths(self,path_rules):
    path_list = []
    path_rules_list = []
    if isinstance(path_rules,type([])):
      path_rules_list = path_rules
    else:
      path_rules_list.append(path_rules)
    # generate all the paths base on the path rule for all targets and variants
    for path_rule in path_rules_list:
      for target_name in self.target_names:
        self.ARGUMENTS['$TARGET'] = target_name
        for chipset in self.chipsets:
          self.ARGUMENTS['$CHIPSET'] = chipset
          for var in self.variants:
            self.ARGUMENTS['$VAR'] = var.upper()
            path_list.append(self.replace_arguments(path_rule))
    return list(set(path_list))
  
  ##############################################################################
  # correct_case_of_path
  # if there is case sensitive of path, correct the path. 
  # If the path is not existed, return None
  # Note: path can't contain Macro
  ##############################################################################
  def correct_case_of_path(self,path):
    logger.debug("correct path:%s",path)
    if os.path.isdir(path):
       logger.debug("return path:%s",path)
       return path
    else:
       fpath,fname = os.path.split(path)
       if fpath=='':
          fpath = r'./'
       fpath=self.correct_case_of_path(fpath)
       if(fpath!=None):
         dirs = os.listdir(fpath)
         for dir_name in dirs:
           if dir_name.lower()==fname.lower():
             logger.debug("find correct name:%s",dir_name)
             logger.debug("return correct path with name:%s",os.path.join(fpath,dir_name))
             return os.path.join(fpath,dir_name)
         logger.debug("can't find correct path")
         return None
         
       
  ##############################################################################
  # create_binary_deliverable
  ##############################################################################
  def create_binary_deliverable(self,
                                base_directory,
                                pack_directory,
                                binary_directory,
                                target_names):

    # Delete old destination directory if it exists
    if os.path.isdir(binary_directory):
      logger.info("[%s] Directory %s exists.  Deleting.",self.task_name, binary_directory)
      try:
        shutil.rmtree(binary_directory, onerror=clear_readonly)
      except:
        logger.info("[%s] Error encountered while deleting directory %s",self.task_name, \
              binary_directory)
        logger.info("[%s] Error info:",self.task_name,sys.exc_info()[0])
        sys.exit(-1)

    logger.info("[%s] Creating %s binary directory.",self.task_name, binary_directory)

    # Copy all target binary directories
    # generate all binaray paths
    bin_paths = self.generate_paths(self.commondirts['PACKBINPATH'])
    # generate other pkgs binary paths
    other_pkg_bin_paths = []
    for other_pkg in self.other_pkgs:
      other_pkg_bin_paths.append(os.path.join(self.replace_arguments(self.commondirts['evaldir']),other_pkg,'Bin'))
    if other_pkg_bin_paths != []:
      bin_paths.extend(other_pkg_bin_paths)
    logger.debug("bin_paths:%s",bin_paths)
    for bin_path in bin_paths:
      if os.path.isdir(bin_path):
        try:
          shutil.copytree(bin_path, os.path.join(binary_directory, bin_path))
          logger.info("copy binary folder %s to %s",bin_path,os.path.join(binary_directory, bin_path))

        except:
          logger.error("[%s] Error encountered while copying target binaries from %s to %s.",self.task_name,
          bin_path,os.path.join(binary_directory, bin_path))
          logger.error("[%s] Error info:",self.task_name,sys.exc_info()[0])
          sys.exit(-1)

    # Copy tools to binary directories
    # generate tools paths
    logger.info("start to copy tools folders")
    tools_paths = self.generate_paths(self.commondirts['tools_path_list'])
    logger.debug("Tools_paths:%s",tools_paths)
    for path in tools_paths:
      tool_path = self.replace_arguments(path)
      ctool_path = self.correct_case_of_path(tool_path)
      source_tool_path = self.replace_arguments(os.path.join(pack_directory,ctool_path))
      dest_tool_path  = self.replace_arguments (os.path.join(binary_directory,ctool_path))

      if ctool_path != None:
        try:
          shutil.copytree(source_tool_path,dest_tool_path)
          logger.info("[%s] Copying %s to %s.",self.task_name,source_tool_path,dest_tool_path)
        except:
          logger.info("[%s] Error encountered while copying tools from %s to %s.", self.task_name,source_tool_path,dest_tool_path)
          logger.info("[%s] Error info:%s", self.task_name, sys.exc_info()[0])
          sys.exit(-1)
      else:
        logger.info("[%s] Error tool path %s doesn't exist!!!",self.task_name,tool_path)
        sys.exit(-1)
    return

  ##############################################################################
  # clean_pack_dir_post_build
  ##############################################################################
  def clean_pack_dir_post_build(self, packdir, variant):

    logger.info("[%s] Running post-build PackIt rules.",self.task_name)

    if not os.path.isdir(packdir):
      logger.info("[%s] Error finding packed directory!\nPlease ensure packit.py has been\
             run prior to calling the post-build clean procedure",self.task_name)
      sys.exit(-1)

    build_dir = os.path.join(packdir, "boot_images", "boot", "Build")
    if not os.path.isdir(build_dir):
      logger.info("[%s]Packed directory not built!\nPlease ensure the directory has been \
             built prior to calling the post-build clean procedure",self.task_name)
      sys.exit(-1)

    postbuild_packout_list = []

    for root, directories, files in os.walk(packdir):
      logger.info("[%s] clean_pack_dir_post_build",self.task_name)
      for file_name in files:
        if file_name.lower().endswith(".inf"):
          file_path = os.path.join(root, file_name)

          # Read file line by line looking for sources or binaries
          try:
            packout_entry = False
            with open(file_path, 'r') as inf_file:
              for line in inf_file:

                # Ignore lines that begin with #
                if line.startswith("#"):
                  continue

                if packout_entry == True:
                  if line == "" or "[" in line:
                    packout_entry = False
                  else:
                    # Line needs to be parsed and assembled
                    assembled_line = self.list_entry_assembler(line,
                                                               root)
                    if len(assembled_line) > 0:
                      if packout_entry == True:
                        postbuild_packout_list.append(assembled_line)

                #Parse common/variant-specific PackIt rules
                if "[userextensions.packit.postbuildpackout]" in line.lower():
                  packout_entry = True

                if variant != "none":
                  if "[userextensions.packit.postbuildpackout."+variant+"]" in line.lower():
                    packout_entry = True


          except:
            logger.info("[%s] Error encountered while reading %s",self.task_name,file_path)
            logger.info("[%s] Error info:%s",self.task_name,sys.exc_info()[0])
            sys.exit(-1)



    # Iterate through the packout list and remove files or directories
    try:
      for packout_entry in postbuild_packout_list:
        # Check and see if the entry is a file or a directory.  If file just
        # delete it.  If directory delete it and everything underneath it.
        if os.path.isfile(packout_entry):
          os.chmod(packout_entry, stat.S_IWRITE)
          os.remove(packout_entry)
        elif os.path.isdir(packout_entry):
          shutil.rmtree(packout_entry, onerror=clear_readonly)
    except:
      logger.info("[%s] Error encountered",self.task_name)
      logger.info("[%s] Error info:%s",self.task_name, sys.exc_info()[0])
      sys.exit(-1)


    logger.info("[%s]Packed out %d files",self.task_name,len(postbuild_packout_list))

    sys.exit(-1)
  def check_released_files(self):
    for file in self.release_list:
        if not os.path.exists(file):
          logger.error("%s is not released to pack dir",file)

  def run_scripts(self):
      options = self.options
      command = []
      if 'run_scripts' in self.commondirts:
          for i in range(len(self.commondirts['run_scripts'])):
              command = []
              for chipset in self.chipsets:
                  self.ARGUMENTS["$CHIPSET"] = chipset
                  for variant in self.variants:
                      self.ARGUMENTS["$VAR"] = variant.upper()
                      self.ARGUMENTS["$PACKBINPATH"] = self.replace_arguments(self.commondirts["PACKBINPATH"])
                      for j in range(len(self.commondirts['run_scripts'][i])):
                          command.append(self.replace_arguments(self.commondirts['run_scripts'][i][j]))
                      try:
                          subprocess.check_call(self.replace_arguments(command))
                      except Exception as error:
                          print (error)
                          raise NameError("ERROR: Packit::excute command:", self.replace_arguments(command),
                                          "failed with error: \n")
  def process (self):
    options = self.options

    output_folder_name = self.replace_arguments(self.commondirts['OUTPUT_FOLDER_NAME'])
    
    # Check wheather the target folder is existing
    self.is_target_folder_existing()
  
    #Clean generated files in pack directory post-build
    if (options.post_build_clean):
        self.clean_pack_dir_post_build(self.packdir_name,
                             options.variant.lower())
  
    # Copy branch to pack directory
    self.copy_to_pack_dir(options.packdir_name,self.replace_arguments(options.branchdir_name))
  
    # If read-write option was supplied change file permissions of pack dir
    if (options.read_write):
      self.change_pack_dir_permissions(options.packdir_name)
  
    # Generate a list of files to include in release based on .inf file entries.
    targets = []
    targets.extend(self.target_names)
    targets.extend(self.other_pkgs)
    targets = list(set(targets))
    logger.debug("targets is %s",targets)
    tick = time.time()
    self.generate_packit_list(
                         self.backlist,
                         self.packout_list,
                         self.packin_list,
                         options.packdir_name,
                         targets,
                         options.architectures,
                         self.variants,
                         options.boot_flow,
                         0)
    logger.debug("generate_packit_list cost about %f",time.time()-tick)
    if self.options.debug_level != '':
      logger.debug("Total packout files")
      for packout_file in self.packout_list:
          logger.debug("packout list:%s",packout_file)
      logger.debug("Total packin files")
      for packin_file in self.packin_list:
          logger.debug("packin list:%s",packin_file)
    # Recursively scan pack dir for module .inf files.  Replace module .inf with
    # release version if found and add release module source files in  packout list
    self.prepare_release_inf_files(options.packdir_name)
  
    # Traverse pack directories deleting files which are in packout_list
    self.cleanse_pack_dir(options.packdir_name,
                          self.packout_list)
  
    # Generate a list of files to pack out based on .inf file entries
    self.generate_release_list(self.release_list,
                          options.packdir_name,
                          options.architectures)


    # Remove source files which are not in release list
    self.post_cleanse_pack_dir(options.packdir_name)

    # Evaluate the release_list and copy binaries to source tree.
    # I.E. .efi, .lib, .obj files listed in .inf files
    # This can only be done if the target name and build dir are specified
    if (options.target_name) and (options.build_directory):
      self.copy_release_binaries(options.build_directory,
                            self.target_names,
                            self.release_list)
  
    # check if all the release files exist.
    # if the release file doesn't exist it will report warning message
    self.check_released_files();

    # Create binary deliverable directory and copy bin folder to binary deliverable directory
    self.create_binary_deliverable(options.branchdir_name,
                               options.packdir_name,
                              options.binarydir_name,
                              self.target_names)

    # Remove UserExtensions.PackIt rule lines from .inf files in pack folder
    self.cleanse_existing_inf_files(os.path.join(options.packdir_name,
                                            options.evaldir_name))

    # Recopied files can have read only attributes.
    # Execute change_pack_dir_permissions if applicable
    if (options.read_write):
      self.change_pack_dir_permissions(options.packdir_name)

    # if additional scripts exists in "run_scripts" item in packitcommon.json file
    # run these scripts
    self.run_scripts()
    logger.info("[%s] packit successfully",self.task_name)


##############################################################################
# architecture_parser_callback
##############################################################################
def architecture_parser_callback(option, opt, value, parser):
  setattr(parser.values, option.dest, value.split(','))

##############################################################################
# main
##############################################################################
def main():
  log_levels = {'CRITICAL' : 50,
    'ERROR' : 40,
    'WARNING' : 30,
    'INFO' : 20,
    'DEBUG' : 10
    }
  parser = OptionParser()

  parser.add_option("-b", "--branch-dir",
                action="store", type="string", dest="branchdir_name",
            default="boot_images",
            help="Branch directory name.  Default is '.'")

  parser.add_option("-p", "--pack-dir",
                    action="store", type="string", dest="packdir_name",
            default="",
            help="Pack directory name.")

  parser.add_option("-r", "--read-write",
                action="store_true", dest="read_write",
                    default=False,
            help="Changes file permissions of pack directory to rw.")

  parser.add_option('-a', '--architectures',
                    type='string',
                    action='callback',
                    callback=architecture_parser_callback,
                    default=["aarch64","ipf"],
                    help="Architecture(s).  Comma seperated.  I.E. ARM,AARCH64" + \
                    "Default is AARCH64,IPF")

  parser.add_option("-t", "--target",
                action="store", type="string", dest="target_name",
            help="Target to pack.  I.E. 8250,")

  parser.add_option("--boot-flow",
                    type="string",
                    action="store",
                    dest="boot_flow",
                    default="SM",
                    help="Boot Flow.  I.E. SM or SDX" + \
                    "Default is SM")

  parser.add_option("--build-dir",
                action="store", type="string", dest="build_directory",
            default="",
            help="Build directory.  Default is './boot_images/boot/Build'")

  parser.add_option("-e", "--eval-dir",
                    action="store", type="string", dest="evaldir_name",
            default="",
            help="Base directory of where to start pack evaluation.  " + \
                         "It's Qualcomm folder. It should be boot_images/boot/QcomPkg")

  parser.add_option("--binary-dir",
                    action="store", type="string", dest="binarydir_name",
            default="HK11",
            help="Binary pack directory name.  Default is HK11")

  parser.add_option("-v","--variant",
                     action="store", type="string", dest="variant", default="none",
                     help = "Variant to pack, I.E. LAA, LAB")

  parser.add_option("--post-build",
                     action="store_true", dest="post_build_clean", default=False)

  parser.add_option("-d","--debug_level",
                     action="store", type="string",dest="debug_level", default="",
                     help = "log print level ,. I.E. CRITICAL, ERROR, WARNING, INFO ,DEBUG")

  (options, args) = parser.parse_args()
  
  if options.debug_level != '':
    if options.debug_level.upper() in log_levels:
       logger.setLevel(log_levels[options.debug_level.upper()])
      # filehandler.setLevel(log_levels[options.debug_level.upper()])
       console.setLevel(log_levels[options.debug_level.upper()])
    else:
       logger.error("Opiton -d debug level input error. Please input CRITICAL/ ERROR/ WARNING/ INFO /DEBUG ")
  
  if not options.target_name:
    logger.error("Please input target!!!")
    sys.exit(-1)

  if len(options.architectures) <= 0:
    logger.error("Please input architecture(s)!!!")
    sys.exit(-1)

  if not options.boot_flow:
    logger.info("Please input boot flow!!!")
    sys.exit(-1)
    
  if options.variant == "none":
    logger.error("Please input variant or use -c option to combine variants in single package!!!")
    sys.exit(-1)
   
  if len(options.target_name.split(',')) > 1 and len(options.variant.split(','))>1:
    logger.error("Packit can't support multi-targets[%s] and multi-variants[%s]",options.target_name,options.variant)
    sys.exit(-1)
  
  packit_common_config =  remove_json_comments(os.path.join(os.path.dirname(os.path.realpath(__file__)),"../boot/packitcommon.json"),"")
  packit_common_config_dirts = json.loads(packit_common_config)
  # Build dir and eval dir defaults need to be OS agnostic.
  if options.build_directory == '':
    options.build_directory = packit_common_config_dirts["BUILDROOTPATH"]
  options.build_directory = options.build_directory.replace("/", os.sep)
  options.build_directory = options.build_directory.replace("\\", os.sep)
  if options.evaldir_name =='':
    options.evaldir_name = packit_common_config_dirts["evaldir"]
  else:
    packit_common_config_dirts["evaldir"] = options.evaldir_name
  options.evaldir_name = options.evaldir_name.replace("/", os.sep)
  options.evaldir_name = options.evaldir_name.replace("\\", os.sep)
 
  packittasklist = []
  i = 0
  other_pkgs = []
  Chipset_pkgs = []
  other_pkg_dir=packit_common_config_dirts['evaldir']
  other_pkgs = find_other_pkgs(options.target_name,correct_path_sep(other_pkg_dir))
  logger.debug("other_pkgs is %s",other_pkgs)
  other_pkgs_path = []
  if other_pkgs != None:
    other_pkgs_path = check_other_pkgs_build_path(options.build_directory,other_pkgs)
    logger.debug("other_pkgs_path %s",other_pkgs_path)
  target_dir=os.path.join(packit_common_config_dirts['evaldir'],packit_common_config_dirts['shared_target_folder'])
  Chipset_pkgs = find_chipset_pkgs(options.target_name,packit_common_config_dirts['CHIP_SET_REGEX'],correct_path_sep(target_dir))

  if Chipset_pkgs == []:
     logger.error("[main task]Can't find targets!!!")
     sys.exit(-1)

  variant_list = options.variant.split(",")
  logger.debug("variants are %s",variant_list)

  new_packit=packit("packit ",options,packit_common_config,Chipset_pkgs,variant_list,other_pkgs,other_pkgs_path)
  new_packit.process()
  return

if __name__ == '__main__':
  main()

#! /usr/bin/python
#===============================================================================
#
# Clean_HY11
#
# GENERAL DESCRIPTION
#    Clean the HY11 directory of unwanted .o, .pyc, and packed out files (cleanpack).
#
# Copyright (c) 2011-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/pack/clean_hy11.py#1 $
#  $DateTime: 2021/10/26 22:03:12 $
#  $Change: 33677139 $
#
#===============================================================================
'''
clean_hy11.py

Description:

   This script is run at the end of the pack process to do some cleanup
   on the HY11 directory.  It does the following:

      * Runs a clean build (with the --cleanpack option) on the HY11 directory
        to remove unneeded object files and source files
      * Removes *.pyc that were generated from the clean build
      * Removes other files that are never shipped to customers:
         *.strip
         *.pack
         *.cspec
         setenv.cmd
         setenv.sh

   This script is intended to be runnable on either Linux or Windows without
   having to change the parameters.  Any slashes in the path to the build
   command are converted to the appropriate format for the current environment.
   Likewise, the '.cmd' or '.sh' at the end of the build command is converted
   to the appropariate value for the current environment, regardless of what
   is specified on the command line.

   This script relies on finding a setenv.cmd or .sh somewhere in the build.
   The two places that are searched are in the build directory and in
   <image_dir>/tools/build/scons/build.  The setenv.cmd or .sh must echo the
   environment to STDOUT after all environment variables have been set
   so that this script may read them.

   For setenv.cmd, this can be done with the 'set' command.  For setenv.sh,
   this can be done with the 'env' command.

Return Value:

   This script follows the standard shell return code policy where a 0 return
   value indicates success, and a non-0 return value indicates failure.

Parameters:

   Parameters are order dependant, and must all be present:

      * Optional --no_cleanpack parameter to bypass the cleanpack operation.
      * Command separated list of build IDs to build.
      * This script now supports a "*" option instead of specifying separate
        build ID's. This auto-detects the build ID's
      * Build command, with or without the leading path.
          * The leading path, if present, should be relative to the root of
            the HY11_1 directory.
          * If a leading path is not specified, the build path will default
            to "modem_proc/build/ms".
      * Remaining build parameters, with a '%s' where the build ID should be
        inserted.

Examples:

   clean_hy11.py AAAAAGAZ,AAAAATAZ boot_images/build/ms/build.sh boot jsdcc emmcbld BUILD_ID=%s USES_FLAGS=USES_NO_STRIP_NO_ODM
   pack/clean_hy11.py * build.cmd mpss BUILD_ID=%s
'''
import sys
import os
import stat
import subprocess
import time
import traceback
import re
from fnmatch import fnmatch
from xml.etree import ElementTree as et

#Import the logger tool from QC-SCons
import logger

def call_setenv (lg, image_dir, build_dir, image_cfg):
   # The setenv.* scripts don't exist in the HY11 directory, so we need to
   # run them from the main directory to setup our build environment before
   # running the build.
   if (sys.platform) == 'win32':
      setenv = 'setenv.cmd'
   else:
      setenv = 'setenv.sh'
   old_setenv = os.path.realpath(os.path.join(build_dir, setenv))
   new_setenv = os.path.realpath(os.path.join(image_dir, 'tools/build/scons/build', setenv))
   startDirectory = os.getcwd()
   if os.path.exists(old_setenv):
      lg.log("Using setenv from build directory")
      setenv_path, setenv_cmd = os.path.split(old_setenv)
      setenv_cmd=old_setenv
      os.chdir(setenv_path)
      res, env = lg.log_exec([setenv_cmd], capture_output = True)
      os.chdir(startDirectory)
   elif os.path.exists(new_setenv):
      lg.log("Using setenv from QC-SCons directory")

# image_cfg.xml is going away, and everyone is using the same compiler ID
# right now anyway, so let's just hard-code it.
#      if os.path.exists(image_cfg):
#         # Read data from config file:
#         lg.log("Reading Image Config")
#         XmlImageCfg = et.ElementTree(file = image_cfg).getroot()
#
#         # Get the compiler ID
#         build_flags_el = XmlImageCfg.find('build_flags')
#         if build_flags_el:
#            compiler_id_el = build_flags_el.find('compiler_id')
#            # For some reason, compiler_id_el is evaluating to False, even when
#            # it's there, so I'm going to always assume that it's there.
#            #     if compiler_id_el and compiler_id_el.text:
#            if compiler_id_el.text:
#               compiler_id = compiler_id_el.text.strip()
#            else:
#               lg.log("Image Config file is missing a compiler ID")
#               sys.exit(1)
#         else:
#            lg.log("Image Config file is missing build_flags")
#            sys.exit(1)
#      else:
#         lg.log("Couldn't find image_cfg.xml")
#         sys.exit(1)

      compiler_id = 'RVCT221P593'
      setenv_path, setenv_cmd = os.path.split(new_setenv)
      os.chdir(setenv_path)
      res, env = lg.log_exec([setenv_cmd, compiler_id], capture_output = True)
      os.chdir(startDirectory)

   else:
      lg.log("Error: Can't find setenv")
      sys.exit(1)

   if res == 0:
      lg.log("Setting Up Environment")
      for setting in env.split('\n'):
         if '=' in setting:
            var, value = setting.split('=', 1)
            os.environ[var.strip()] = value.strip()

   return res

# End of call_setenv()

def main():
   try:
      lg = logger.Logger('clean_hy11')
      startDirectory = os.getcwd()
      lg.log("Start directory is: " + startDirectory)
      lg.log("Python Version is: " + sys.version)
      lg.log("Platform is: " + sys.platform)
      lg.log("Parameters:")
      params = list(sys.argv)
      no_cleanpack = False
      for arg in sys.argv:
         lg.log("   " + arg)
         if arg == '--no_cleanpack':
            no_cleanpack = True
            params.remove(arg)

      # Parse parameters
      targetID    = params[1].split(',')
      buildCmd       = params[2]
      buildCmdParams = params[3:]

      # Default values
      buildDir = 'aop_proc/build/ms'
      imageDir = 'aop_proc'
      imageCfg = "./aop_proc/build/ms/image_cfg.xml"
      buildsInCurrentRoot = []
      HY11_specified = "HY11_1" #This is the variable we will be using as root HY11 directory
      lg.log(" bUILD COMMAND IS: "+ buildCmd)

      if(re.search("HY11_*",buildCmd)):
           if(re.search(buildCmd.split('\\',1)[0],buildCmd)):
                 buildCmd=buildCmd.replace('\\','/')
           HY11_specified = buildCmd.split('/',1)[0]
           buildCmd=buildCmd.split('/',1)[1];
      #Check if user provided full path to HY11_1 folder
      if (buildCmd.count("/") or buildCmd.count("\\") ):
         lg.log("Calculating path elements from build path.")
         (buildDir, filename) = os.path.split(buildCmd)
         imageDir = buildDir.split('/',1)[0].split('\\',1)[0]
         get_HY11_path=os.path.join(HY11_specified,buildDir)
      else:
         lg.log("Using default (aop) path elements.")
         filename=params[2]
         get_HY11_path='HY11_1/aop_proc/build/'

      # begin
      binDir=buildDir
      if(sys.platform) == 'win32':
         binDir = binDir.replace("/", "\\")
      else:
         binDir = binDir.replace("\\", "/")

#     binDir = os.path.join("..",binDir,"bin")
      binDir = os.path.join(binDir,"bin")
      if (targetID[0] == "*"):
         #Found our special flag in the arguments
         lg.log("Auto detecting Strip build ids")
         lg.log("Bin Dir is: "+binDir)
         #Find the IDs in the given root
         try:
            for binDirfilename in os.listdir(binDir):
               #Redundant if condition for documentation, make sure it holds for future
               if (binDirfilename != "PIL_IMAGES"):
                  buildsInCurrentRoot.append(binDirfilename)
                  lg.log("Auto detect Folder name is : "+binDirfilename)
         except Exception, e:
            lg.log("Something went wrong, could not find build IDs in the root")
            raise
         lg.log("Auto detected Strip IDs are as follows: " + str(buildsInCurrentRoot))
         targetID = buildsInCurrentRoot
      # end

      # Check if build command specifies an alternate image config fiile.
      for param in buildCmdParams:
         if param.startswith("IMAGE_CFG"):
            imageCfg = param.split('=',1)[1]
            path, file = os.path.split(imageCfg)
            imageCfg = os.path.realpath(os.path.join(buildDir, path, file))

      filenamebase = filename.rsplit(".",1)[0]
      if(sys.platform) == 'win32':
         get_HY11_path = get_HY11_path.replace("/", "\\")
         filename=filenamebase+".bat"
      else:
         get_HY11_path = get_HY11_path.replace("\\", "/")
         filename=filenamebase+".sh"

      # Call setenv to setup the build environment
      res = call_setenv(lg, imageDir, buildDir, imageCfg)
      if res != 0:
         # An error happened, so return the error to the shell
         lg.log("Setenv failed, returned" + str(res))
         sys.exit(res)

      # argv[1] is a possible comma-delimited list with build IDs
      # for all those build IDs, run clean in the build\ms folder

      os.chdir(get_HY11_path)
      lg.log("Changed directory to: " + os.getcwd())
      for buildID in targetID:
         lg.log("Cleaning HY11_1 "+ buildID)
         lg.log("Cleaning HY11_1 "+ filename)
         lg.log("Cleaning HY11_1 "+ str(buildCmdParams))
         buildCmd = filename +" --clean"
         buildCmd = buildCmd.split()
         if not no_cleanpack:
            buildCmd.append('--cleanpack')
         #buildCmd = './build_24.sh --clean --cleanpack'
         lg.log("This is the build command " + " ".join([str(i) for i in buildCmd]))
         buildcmd_str = "".lstrip(" ".join([str(i) for i in buildCmd]))
         res = lg.log_exec(buildcmd_str)
         if res != 0:
            # An error happened, so return the error to the shell
            lg.log("Clean command failed, returned " + str(res))
            sys.exit(res)

      #cd back to top directory
      os.chdir(startDirectory)

      #delete pyc files in HY
      os.chdir(HY11_specified)
      lg.log("Removing select files from "+os.getcwd())
      for dirpath, dirnames, filenames in os.walk(os.getcwd()):
         for each_file in filenames:
            if (each_file.endswith('.pyc') or
                each_file.endswith('.strip') or
                each_file.endswith('.pack') or
                each_file.endswith('.cspec') or
                each_file.endswith('.md5') or
                each_file.endswith('.cleanpack.py') or
                each_file.endswith('.sconsign_*.dblite') or
                fnmatch(each_file, 'build*.log') or
                fnmatch(each_file, 'build-log*.txt') or
				#(each_file.endswith('.target.builds') and not each_file.startswith(targetID[0]) ) or
                each_file == 'setenv.cmd' or
                each_file == 'setenv.sh'):
               file = os.path.join(dirpath, each_file)
               lg.log("Removing " + file)
               try:
                  os.chmod(file, stat.S_IWRITE)
                  os.remove(file)
               except:
                  lg.log("Exception received while trying to remove " + file)
                  lg.log_crash()
                  traceback.print_exc()

      # cd back to start directory to be safe
      os.chdir(startDirectory)
      print "Finished build clean and deleting select files"

      print "Deleting all empty folders under "+'HY11_1'
      os.chdir(HY11_specified)
              # removing empty dirs in HY11_1
      for root, dirs, files in os.walk(os.curdir,topdown=False):
         for name in dirs:
            fname = os.path.join(root,name)
            if os.path.exists(fname):
               if not os.listdir(fname): #to check wither the dir is empty
                  lg.log("Deleting " + fname + " as it is empty")
                  os.removedirs(fname)

      # cd back to start directory to be safe
      os.chdir(startDirectory)

   except:
      if lg:
         lg.log_exception()
      raise
   finally:
      # Close the log file.
      if lg:
         del lg
      else:
         print "Error: Couldn't open log file"

if __name__ == '__main__':
    main()







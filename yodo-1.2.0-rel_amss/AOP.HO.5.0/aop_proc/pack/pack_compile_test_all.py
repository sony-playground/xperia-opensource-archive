#===============================================================================
#
# Pack Compile Test All
#
# GENERAL DESCRIPTION
#    Script for compiling all Pack CompileTest Builds
#
# Copyright (c) 2011-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/pack/pack_compile_test_all.py#1 $
#  $DateTime: 2021/10/26 22:03:12 $
#  $Change: 33677139 $
#
#===============================================================================

'''
pack_compile_test_all.py

   This script does a test build on all builds in the HY11_CompileTest directory.
   It reads the required build info from a file to let it know which builds need
   to be compiled, and what build commands to use in compiling them.  The input
   file defaults to "pack_compile_test_build_cmds.txt" in the current directory,
   but this can be overridden on the command line.  A sample file is:

         HY11_CompileTest modem_proc/build/ms build mpss BUILD_ID=AAAAANAZ -k
         HD11_CompileTest modem_proc/build/ms build mpss BUILD_ID=AAAAAKAZ -k
         HY31_CompileTest modem_proc/build/ms build mpss BUILD_ID=AAAAANAZ -k

   The name of the directory is given first, followed by the path to the build,
   followed by the build command.

   The HY11_CompiletTest directory is assumed to be the current directory.  All
   others are assumed to be directories under the current directory.

   This script can be run on either Windows or Linux.  The first word of the
   command is expected to be either a .cmd or .sh command file.  This script
   will add the appropriate suffix for the current build environment.

  This script will report a warning in the following cases:

      - A build directory is listed in the pack_compile_test_build_cmds.txt file
        that doesn't exist under the current directory.

      - A build directory with the signiture *_CompileTest exists in the current
        directory, but is not listed in pack_compile_test_build_cmds.txt.'''

import sys
import os
from glob import glob
from xml.etree import ElementTree as et

sys.path.append("../pack")
import logger

#######################################################################
# Local Print function.
# Prefix all output statements with the name of this script, so that
# they can be easily grepped in the log file.
#######################################################################
def my_print (*args):
   lg.log("pack_compile_test_all.py: " + ' '.join([str(x) for x in args]))


#######################################################################
# Exception for handling input errors.
#######################################################################
class InputError(Exception):
   def __init__(self, value):
      self.value = "pack_compile_test_all.py: Input Error: " + value
   def __str__(self):
      return repr(self.value)
# End of class InputError


#######################################################################
# Exception for handling input errors.
#######################################################################
class BuildError(Exception):
   def __init__(self, build, retcode):
      self.value = "pack_compile_test_all.py: Build Error: " + build + ' returned ' + str(retcode)
   def __str__(self):
      return repr(self.value)
# End of class InputError


#######################################################################
# Exception for handling input errors.
#######################################################################
class ValidationError(Exception):
   def __init__(self):
      self.value = "pack_compile_test_all.py: Validation Error"
   def __str__(self):
      return repr(self.value)
# End of class InputError


#######################################################################
# Build Info Class
#######################################################################

class build_info:
   '''Structure to contain information on a single build.'''

   def __init__ (self, root_dir, build_dir, build_cmd, validate):
      self.name = root_dir
      if root_dir == "HY11_CompileTest":
         self.root = '.'
      else:
         self.root = root_dir

      self.bld_dir = build_dir
      self.img_dir = build_dir.split('/')[0].split('\\')[0]

      self.cmd     = build_cmd.split()
      cmd = self.cmd[0].rsplit('.',1)[0]  # Strip any file suffix, e.g. .cmd or .sh
      if on_linux:
         self.cmd[0] = cmd + '.sh'
      else:
         self.cmd[0] = cmd + '.cmd'

      self.validate = validate

      self.result  = None
      self.not_compiled=set()               # the lsit of files which did not get compiled  in the restricted build
      self.compile_restricted_result=True   #flag to set the result of successful restricted src compilation : Note this is true when not_compiled is []

   # End of __init__()

   #######################################################################
   # build - Function for doing a build.
   #######################################################################
   def build (self):
      my_print ("Building", self.name)
      cur_dir = os.getcwd()
      if os.path.exists(self.root):
         build_dir = os.path.join(self.root, self.bld_dir)
         if os.path.exists(build_dir):

            # Remove .cmd and .sh from the end of the base command,
            # then re-add the appropriate suffix later.  This will
            # enable the same input file to be used on both Windows
            # and Linux.
            base_cmd = self.cmd[0]
            base_cmd = base_cmd.split('.cmd')[0].split('.sh')[0]

            if sys.platform == 'win32':
               # Some differences here are Windows/Linux differences,
               # some are due to differences in how our build servers
               # execute the build commands under Linux or Windows.
               os.chdir(build_dir)
               base_cmd = base_cmd + '.cmd'
               use_cmd   = [base_cmd] + self.cmd[1:]
               clean_cmd = use_cmd + ['--clean']
               use_shell = False
            else:
               base_cmd = base_cmd + '.sh'
               base_cmd = os.path.join(build_dir, base_cmd)
               use_cmd   = base_cmd + ' ' + ' '.join(self.cmd[1:])
               clean_cmd = use_cmd + ' --clean'
               use_shell = True

            # Do a clean build first
            my_print ("Clean Build:", clean_cmd)
            self.result = lg.log_exec(clean_cmd, shell=use_shell)
            my_print ("Clean Build", self.root, "returned", self.result)
            if self.result != 0:
               raise BuildError(self.root, self.result)
            # Now do a regular build
            my_print ("Regular Build:", use_cmd)
            self.result = lg.log_exec(use_cmd, shell=use_shell)
            my_print ("Regular Build", self.root, "returned", self.result)
            if self.result != 0:
               raise BuildError(self.root, self.result)
         else:
            my_print ("Build", self.name + ':', "Build directory is missing:", self.bld_dir)
      else:
         my_print ("Build", self.name, "doesn't exist")
      os.chdir(cur_dir)

   # End of build()

   #######################################################################
   # build - Function for doing a build.
   #######################################################################
   def merge_build_products (self):
      build_products_fn     = "BuildProducts.txt"
      sub_build_products_fn = os.path.join(self.root, build_products_fn)

      if os.path.exists(sub_build_products_fn):
         sub_build_products = open(sub_build_products_fn, 'r')
         build_products = open(build_products_fn, 'a')

         for line in sub_build_products.readlines():
            parts = line.split(self.img_dir, 1)
            new_line = os.path.join(parts[0], self.root, self.img_dir, parts[1][1:])
            build_products.write(new_line)

         sub_build_products.close()
         build_products.close()

   # End of merge_build_products()


   #######################################################################
   # build - Function for verifying restricted source build.
   #######################################################################
   def verify_compilation (self):
      '''
      TO VERIFY THE RESTRICTED SOURCE
      For each file that was copied over from the Restricted Source directory,
      if it was compiled in the main directory, make sure it is also compiled
      in the Restricted Source CompileTest directory.
      '''
      if self.validate:
         my_print ("Verfiying ", self.name)

         # Collect the list of files that were copied from the Restricted Source directory
         rs_copy_flist_fn = os.path.join(build.root,'restricted_list.txt')
         rs_copy_flist_f  = open(rs_copy_flist_fn, 'r')
         rs_copy_flist    = set([x.strip() for x in rs_copy_flist_f.readlines()])

         # Collect the list of files built main build
         def get_flist_from_log_files (build_dir):
            log_files_wc = os.path.join(build_dir, 'build-log*.txt')
            log_files_fn = glob(log_files_wc)
            if not log_files_fn:
               # The build log filename changed in newer builds
               log_files_wc = os.path.join(build_dir, 'build*.log')
               log_files_fn = glob(log_files_wc)
            file_list = set()
            for log_file_fn in log_files_fn:
               log_file = open(log_file_fn, 'r')
               for line in log_file.readlines():
                  line = line.strip()
                  # Lines can come in the following forms:
                  #    '=== Compiling  pm_boot_chg.cpp ==> /local/mnt/workspace/CRMBuilds/.../protected/pm_boot_chg.o ...'
                  #    '=== Compiling  sbl1/arm7/AAABQNBY/boot_loader.c ...'
                  #    '=== Compiling  sbl3/scorpion/AAABQNBY/boot.cpp'
                  if line.startswith("=== Compiling"):
                     if line.count('==>'):
                        file_name = line.split()[2]
                     else:
                        file_name = line.split()[2].rsplit('/', 1)[1]
                     file_list.add(file_name)
            return file_list
         # End of get_flist_from_log_files()

         main_build_dir = os.path.join('..', self.bld_dir)
         main_build_flist = get_flist_from_log_files(main_build_dir)

         rs_build_dir = os.path.join(self.root, self.bld_dir)
         rs_build_flist = get_flist_from_log_files(rs_build_dir)

         # All lists should have something in them
         if rs_copy_flist and main_build_flist and rs_build_flist:
            # Any files that are in the rs_copy_flist, and in the main_build_flist,
            # but not in the rs_build_flist, indicate an error.
            should_build_flist = main_build_flist & rs_copy_flist    # Intersection
            build.not_compiled = should_build_flist - rs_build_flist # Difference
            if build.not_compiled:
               build.compile_restricted_result = False
               my_print("  The following files were not compiled:")
               for file_not_compiled in build.not_compiled:
                  my_print("verify_compilation: Error: Did not compile", file_not_compiled)
         else:
            my_print("Couldn't find necessary log files to verify Restricted Source Compilation.")
            build.compile_restricted_result = False

      else:
         my_print ("Skipping verification for ", self.name)

   # End of verify_compilation()

# End of class build_info

lg = None
startDirectory = None
try:
   #######################################################################
   # Global variables
   #######################################################################

   pack_builds = list()   # List of builds to compile
   on_linux = sys.platform.startswith("linux")

   #######################################################################
   # Initialize Logger
   #######################################################################

   lg = logger.Logger('pack_compile_test_all')
   startDirectory = os.getcwd()
   lg.log("Start directory is: " + startDirectory)
   lg.log("Python Version is: " + sys.version)
   lg.log("Platform is: " + sys.platform)

   #######################################################################
   # Read Parameters
   #######################################################################

   if len(sys.argv) == 2:
      build_cmds_file = sys.argv[1]
   else:
      build_cmds_file = "pack_compile_test_build_cmds.txt"
   lg.log("Build Commands File: " + build_cmds_file)

   #######################################################################
   # Read the pack_compile_test_build_cmds.txt file and create a dictionary
   # mapping build directories to
   #######################################################################

   if build_cmds_file.endswith('.xml'):
      # Newer builds should use an xml file to hold this data.
      XmlBuildCmds = et.ElementTree(file = build_cmds_file).getroot()
      for build in XmlBuildCmds.findall('build_cmd'):
         try:
            root_dir  = build.find('root_dir').text.strip()
         except:
            raise InputError("Can't find validate_rs_files element for build in " + build_cmds_file)
         try:
            build_dir = build.find('build_dir').text.strip()
         except:
            raise InputError("Can't find build_dir element for build in " + build_cmds_file)
         try:
            build_cmd = build.find('build_cmd').text.strip()
         except:
            raise InputError("Can't find build_cmd element for build in " + build_cmds_file)
         try:
            # Interpret all unrecognized values as True
            validate  = build.find('validate_rs_files').text.strip() not in ['False', 'false', 'FALSE']
         except:
            raise InputError("Can't find validate_rs_files element for build in " + build_cmds_file)

         pack_builds.append(build_info(root_dir, build_dir, build_cmd, validate))

   else:
      # Legacy build use a .txt file to hold this data.
      my_print("Warning: Deprecated use of .txt file for build commands data.",
               "Please convert this file to an xml file.  The format is documented at",
               "http://qwiki.qualcomm.com/qct-target/Restricted_Source_Packages#Image_Level_.pack_File_Changes")
      pctbc_file = open(build_cmds_file, 'r')
      for line in pctbc_file.readlines():
         line = line.strip()
         if not line.startswith('#') and len(line) > 1:
            root_dir, bld_dir, cmd = [x.strip() for x in line.split(None, 2)]
            pack_builds.append(build_info(root_dir, bld_dir, cmd, True))
      pctbc_file.close()

   #######################################################################
   # Build each directory for which we have a command.
   #######################################################################

   failed_builds=[]  # list of all builds failed because of an incomplete compilation fof restricted source

   for build in pack_builds:

      build.build()
      build.merge_build_products()

      # now verify the restricted build's source compilation
      if build.root != '.':                     # do the verifictaion for only ./.. builds
         build.verify_compilation()

         if False==build.compile_restricted_result: # if the build did not compile the restricted source
            failed_builds.append(build.root)


   # final summary of the restricted builds

   if failed_builds != []:                 # if there are failed builds

      os.remove("BuildProducts.txt")  # This will cause Tiberium to fail the build.
      for build_name in failed_builds:
          my_print("failed to compile "+build_name)      # print each build that failed
      my_print("pack build failed")
      raise ValidationError()
   else:
      my_print("=========== verify_compilation: All restricted source builds compiled =============")

except:
   if startDirectory:
      os.chdir(startDirectory)
      if os.path.exists("BuildProducts.txt"):
         os.remove("BuildProducts.txt")  # This will cause Tiberium to fail the build.
   if lg:
      lg.log_exception()
   raise
finally:
   if startDirectory:
      if lg:
         my_print("Changing directory back to start directory: " + startDirectory)
      os.chdir(startDirectory)
   if lg:
      del lg


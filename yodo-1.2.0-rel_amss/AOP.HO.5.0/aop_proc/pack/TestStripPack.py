#===============================================================================
#
# Test Strip/Pack
#
# GENERAL DESCRIPTION
#    Test script for testing Strip/Pack Files
#
# Copyright (c) 2011-2012 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/pack/TestStripPack.py#1 $
#  $DateTime: 2021/10/26 22:03:12 $
#  $Change: 33677139 $
#
#===============================================================================

'''
   TestStripPack.py
   
   This script tests the validity of the .strip and .pack files.  It is intended to be
   used by both integration and development teams.
   
   One of the main requirements of this script is that it be able to test only a
   subset of .strip and/or .pack files, so that these files can be verified even if
   errors exist in other .strip or .pack files.  The user should only see errors if
   his/her .strip or .pack files are in error.
   
   This script must be run from the root directory of a build.
   
   Usage:
   
      TestStripPack.py -r=<strip/pack response file>
   
   Parameters:
   
      -r=<response_file>
   
            The -r parameter allows you to specify a response file with default parameters.
            Response files typically have a .rsp suffix.
   
            This parameter can be specified multiple times.  For example, if you have one
            .rsp file for testing strip, and another for testing pack, you can specify
            both to test both strip and pack consecutively.
   
            Response files can also be nested by using the -r parameter from withing
            the response file.
   
      -s=<strip_files>
      -s
   
            The -s parameter allows the user to specify a comma-separated list of .strip
            files to validate.  Spaces are not allowed in this list.  The list may either
            have a path, or not, e.g. -s=strip/core.strip,strip/modem.strip or
            -s=core.strip,modem.strip.  The script assumes that all .strip files are in
            the strip directory.
   
            If no -s parameter is specified, the script will skip the strip process.  If
            you just want to use the default .strip file, please use "-s" by itself, without
            naming a .strip file explicitly.
   
            The default .strip file is named "top_level_strip.strip"
   
      -ifs=<.ifs_base_file_name>
   
            This parameter specifies the base file name for both the .ifs file and .rsp
            file used in the strip process.  The parameter is optional, and, if not specified
            on the command line, will default to "strip.ifs" and "strip.rsp".
   
            Note that the .ifs and .rsp files must have the same base file name.  That is
            why only one parameter is required.
   
      -p=<pack_files>
      -p
   
            The -p parameter allows the user to specify a comma-separated list of .pack
            files to validate.  Spaces are not allowed in this list.  The list may either
            have a path, or not, e.g. -p=pack/core.pack,pack/modem.pack or
            -s=core.pack,modem.pack.  The script assumes that all .pack files are in
            the pack directory.
   
            If no -p parameter is specified, the script will skip the pack process.  If
            you just want to use the default .pack file, please use "-p" by itself, without
            naming a .pack file explicitly.
   
            The default .pack file is named "top_level_pack.pack"
            
      -d=<dir_list>
   
            The -d parameter works in conjunction with the -p parameter to specify the
            directories used by the .pack files listed in the -p parameter.
   
            The test script will do a complete copy of all directories not listed with the -d
            parameter before running the pack utility.  The pack utility will then be used
            to copy the specified directories.
   
      -i=<image_dir>
   
            Specify the name of the image directory.  This is required for both strip and
            pack builds.
   
      -pl=<pl_name>
   
            The -pl parameter specifies the PL name to use.
   
      -set:<flag_list>
   
            This parameter takes a comma separated list of flag=value pairs
            and adds 'set' statements for these flags in the pack file.
   
            e.g.:
   
               -set:PRODUCT_ROOT=modem_proc,BUILD_ID=AAAAANAZ
   
      -bdir=<build_dir>
   
            Deprecated, and maintained only for backwards compatibility.
            For future development, please use -sbdir and -pbdir.
   
            Specifies the directory for the build.
   
      -sbdir=<build_dir>
   
            Specifies the directory for the strip build.
   
      -pbdir=<build_dir>
   
            Specifies the directory for the pack build.
   
      -sbcmd=<build_command>
   
            Specifies the build command to be used for the strip operation.
   
            Defaults to:
   
               build.cmd mpss -k USES_FLAGS=USES_NO_STRIP_NO_ODM,USES_NO_DEBUG
   
      -pbcmd=<build_command>
   
            Specifies the build command to be used for the pack operation.
   
            Defaults to:
   
               build.cmd mpss -k
   
            Must be able to have a "--clean" option appended to it.
   
      -bimg=<build_image>
   
            Specifies the image name used on the build command line.
   
      -bid=<build_id>
   
            The -bid parameter is used to specify the build ID that is used in the build
            commands for the test builds.
   
      -bver=<build_version>
   
            The -bv parameter is used to specify the build version, which is used in the
            build commands for the test builds.
   
      -clean_opt=<clean option>
   
            The -clean_opt parameter is used to specify the a clean option for the pack
            command.
   
            When the pack is done to test tech-team pack files, a large portion of the
            build is copied, and only the relevant modules are packed with the packit
            tool.  During this copy, a lot of .o and .lib files are copied, and a clean
            build must be done before the regular build.
   
            This option defaults to "--clean", to be compatible with SCons builds.
            However, make builds can override this using this parameter.
   
            When specifying a top-level pack file to test, the clean option isn't
            needed, and can be disabled by specifying "-clean_opt=" (with no value).
   
      -def=<symbol>:<value>[,<symbol>:<value>]

      -strict
   
            The -strict option will cause the build to fail if certain integrity checks fail.
            Without this option, only warnings are written to the log file, or perhaps
            and e-mail might be sent.
   
            The main check that this applies to is checking to see if certain files are in
            the pack directory that shouldn't be there.  Since this check applies to the
            entire HY11 directory, this option should only be turned on when testing strip/
            pack for an entire build.  It shouldn't be turned on by tech teams who just
            want to test their strip/pack files.
   
      -update_ifs_only
      
            This parameter modifies the strip operation to only update the intermediate
            files (*.ifs and *pack.txt), and not actually perform the strip or pack
            operations, or doing any compiles.
            
      -skip_pack_compile
   
            This parameter can be used to skip both the generation of the pack CompileTest
            directory, and the test compile itself.  It's intended for Test SBAs, where
            there is a separate test compile of the SBA code, so the one performed by
            this script isn't necessary.
   
      -skip_ifs

            Currently only supported for pack.  This option causes TestStripPack.py to
            call packit directly with the .pack file, skipping the need to generate a
            *pack*.txt file.
   
      -v
   
            This parameter will cause TestStripPack.py to print out it's version information
            (bascially just the Perforce $Header: //components/rel/aop.ho/5.0/aop_proc/pack/TestStripPack.py#1 $ line), and exit.
   
   Note that parameters are parsed in the order that they are encountered.  Later parameters
   may overwrite previous parameters.  For example, to overwrite a parameter specified in a
   response file, make sure you specify the parameter on the command line after specifying
   the response file.

   Return Code:

   TestStripPack.py will return the following error codes to the shell:

      0: Success
      1: File not found
      2: Invalid Parameters
      3: Strip/Pack Validation Failure
      4: BuildProducts.txt Validation Failure

'''

import sys
import os
import subprocess
import time
import shutil
from glob import glob
import fnmatch
import stat
import smtplib     #For sending email
import getpass
import socket
import traceback

#================================================================
# Define local functions
#================================================================
def delta_time (start, end):
   delta = end - start
   minutes = delta / 60
   seconds = delta % 60
   delta_str = "%d minutes, %d seconds" % (minutes, seconds)
   return delta_str

def open_log_file (base_name):
   log_file_name = base_name + '.log'
   if os.path.exists(log_file_name):
      i = 1
      while os.path.exists(base_name + '_%.2d.log' % (i)):
         i += 1
      os.rename(log_file_name, base_name + '_%.2d.log' % (i))

   return open(log_file_name, 'w')

def log_exec (cmd, shell=False):
   global log_file
   start_time = time.time()
   log('In ' + os.getcwd())
   log(' '.join(cmd))
   task = subprocess.Popen(cmd, shell=shell, stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
   c = task.stdout.read(1)
   while c:
      log_file.write(c)
      sys.stdout.write(c)
      c = task.stdout.read(1)
   task.wait()  # Wait for the task to really complete
   end_time = time.time()
   log("Elapsed time for " + cmd[0] + " was " + delta_time(start_time, end_time))
   if task.returncode != 0:
      log(cmd[0] + " command returned error: " + str(task.returncode))
      sys.exit(task.returncode)

def log (str):
   global log_file
   str = 'TestStripPack.py: ' + str + '\n'
   log_file.write(str)
   sys.stdout.write(str)

def glob_list (file_list, opt_prefixes=None, chop_prefixes=False):
   '''glob_list takes a list of filenames/directories that may contain
   wildcards, and runs glob on each item in the list, returning the
   concatenated list of all matching files/directories.'''
   if type(opt_prefixes) is not list:
      opt_prefixes = [opt_prefixes]
   retval = []
   if '*' in file_list:
      # Special case:
      # Do '*' for all prefixes, but ignore everything else in the root directory
      file_list = []
      for prefix in opt_prefixes:
         file_list.append(prefix + '/*')
   for file in file_list:
      temp = glob(file)
      for prefix in opt_prefixes:
         if prefix:
            temp.extend(glob(os.path.join(prefix, file)))
      if not temp:
         log("Error: file not found: " + file)
         sys.exit(ret_file_not_found)
      retval.extend(temp)
   if opt_prefixes and chop_prefixes:
      # We want to return the list of files/dirs without the prefix
      temp = []
      for file in retval:
         for prefix in opt_prefixes:
            if (prefix+'/') in file:
               temp.append(file.split(prefix + '/')[1])
            elif (prefix+'\\') in file:
               temp.append(file.split(prefix + '\\')[1])
      retval = temp
   return retval

def parse_arg (arg, indent=0):
   '''parse_arg: Function to parse command line parameters.'''
   global StripFiles
   global PackFiles
   global PackDirs
   global IFS_BFN
   global StripIfsFn
   global StripRspFn
   global ImageDirs
   global PL
   global SetFlags
   global BuildDir
   global StripBuildDir
   global PackBuildDir
   global StripBuildCmd
   global PackBuildCmd
   global BuildVer
   global CleanOpt
   global PackDefines
   global Strict
   global UpdateIfsOnly
   global SkipIfs
   global SkipPackCompile
   global TestStripPackVersionInfo

   log("Parsing Arg: " + indent*"  " + arg)

   if arg.startswith('-s='):
      StripFiles = arg.split('-s=')[1].split(',')
      StripFiles = glob_list(StripFiles, 'strip', True)
   elif arg.startswith('-ifs='):
      IFS_BFN = arg.split('-ifs=')[1]
   elif arg.startswith('-p='):
      PackFiles = arg.split('-p=')[1].split(',')
      if arg.count('/') or arg.count('\\'):
         # This indicates they specified the full path in the name of the
         # pack files, so we don't need to prepend the path.
         PackFiles = glob_list(PackFiles)
      else:
         PackFiles = glob_list(PackFiles, 'pack')
   elif arg.startswith('-d='):
      PackDirs = arg.split('-d=')[1].split(',')
      # glob_list must be called after ImageDir is available.
   elif arg.startswith('-i='):
      ImageDirs = arg.split('-i=')[1].split(',')
   elif arg.startswith('-pl='):
      PL = arg.split('-pl=')[1]
   elif arg.startswith('-bdir='):
      BuildDir = arg.split('-bdir=')[1]
   elif arg.startswith('-sbdir='):
      StripBuildDir = arg.split('-sbdir=')[1]
   elif arg.startswith('-pbdir='):
      PackBuildDir = arg.split('-pbdir=')[1]
   elif arg.startswith('-sbcmd='):
      StripBuildCmd = arg.split('-sbcmd=')[1].strip('"').split()
   elif arg.startswith('-pbcmd='):
      PackBuildCmd = arg.split('-pbcmd=')[1].strip('"').split()
   elif arg.startswith('-bver='):
      BuildVer = arg.split('-bver=')[1]
   elif arg.startswith('-r='):
      rsp_file = arg.split('-r=')[1]
      rsp = open(rsp_file, 'r')
      for arg in rsp.readlines():
         arg = arg.strip()
         if arg:  # Ignore blank lines
            parse_arg(arg.strip(), indent=indent+1)
      rsp.close()
   elif arg.startswith('-set:'):
      SetFlags = arg.split('-set:')[1].split(',')
   elif arg.startswith('-clean_opt='):
      CleanOpt = arg.split('-clean_opt=')[1]
   elif arg.startswith('-def='):
      PackDefines = arg.split('-def=')[1]
      PackDefines = PackDefines.split(',')
      PackDefines = ['-def=' + x for x in PackDefines]
   elif arg.startswith('-strict'):
      Strict = True
   elif arg.startswith('-update_ifs_only'):
      UpdateIfsOnly = True
   elif arg.startswith('-skip_ifs'):
      SkipIfs = True
   elif arg.startswith('-skip_pack_compile'):
      SkipPackCompile = True
   # Parse shorter options last so that they don't match longer ones accidentally,
   # e.g. "-p" matching the start of "-pl"
   elif arg.startswith('-h'):
      log(__doc__)
      sys.exit(ret_success)
   elif arg.startswith('-p'):
      # Do pack, but with the default pack file
      PackFiles    = [DefaultPackFile]
   elif arg.startswith('-s'):
      # Do strip, but with the default strip file
      StripFiles = [DefaultStripFile]
   elif arg.startswith('-v'):
      # Print version info and exit
      log(TestStripPackVersionInfo)
      sys.exit(ret_success)
   else:
      log("Error: Invalid Parameter: " + arg)
      log(__doc__)
      sys.exit(ret_invalid_parameters)

def make_writeable (function, path, excinfo):
   '''This is a callback function for shutil.rmtree that gets called
   when shutil.rmtree receives an error while trying to delete a file.
   This function assumes that the problem is that the file is read-only,
   so it marks the file as writable, and then deletes it.'''
   try:
      os.chmod(path, stat.S_IWRITE | stat.S_IREAD)
   except:
      pass   # Ignore error and try to delete anyway.
   try:
      os.remove(path)
   except:
      try:
         os.rmdir(path)
      except:
         pass
            
def pack_pre_copy_filter (path, names):
   '''pack_pre_copy_filter is the callback function passed to 
   shutil.copytree to not copy the directories specified with
   the -d parameter on the command line.'''
   if path in PackDirs:
      # Skip copying this directory.  Return all names to ignore.
      log("Pack Pre-Copy: Skipping " + path)
      return names
   else:
      # Ignore nothing, copy everything.
      # print "Pack Pre-Copy: Copying", path, "     \r",
      return []

def CopyDir(src, dst):
   '''Copy a directory tree onto a pre-existing tree.'''
   for root, dirs, files in os.walk(src):
      dest = root.replace(src, dst, 1)
      if not os.path.exists(dest):
         os.mkdir(dest)
      for file in files:
         shutil.copy(os.path.join(root, file), dest)

def SendMail (to_list, subject, body):
   fromAddr = "ProductIntegration.Team@qualcomm.com"
   if type(to_list) != list:
      to_list = [to_list]
   msg = """\
From: %s
To: %s
Subject: %s

%s
""" % (fromAddr, ", ".join(to_list), subject, body)
      
   server = smtplib.SMTP('smtphost.qualcomm.com')
   server.sendmail(fromAddr, to_list, msg)
   server.quit()

# End of SendMail()

class ErrorInfo:

   def __init__(self):
      self.error_count = 0
      self.error_list  = {}
   # End of ErrorInfo.__init__()

   def AddErrorList (self, list_name, error_list):
      if type(error_list) is not list:
         error_list = [error_list]
      if list_name not in self.error_list:
         self.error_list[list_name] = []
      self.error_list[list_name] += error_list
      self.error_count += len(error_list)


   def ReportErrors(self, pl):
      # Bad files were found, send an e-mail
      machine_name = socket.gethostbyaddr(socket.gethostname())[0]
      build_directory = os.getcwd()
      user = getpass.getuser()

      bad_file_text = ""
      for package in self.error_list.keys():
         if self.error_list[package]:
            bad_file_text += package + ":\n"
            for file in self.error_list[package]:
               bad_file_text += 6*' ' + file + "\n"

      message = '''
The following build contains strip/pack violations:

Product Line:    %s
Machine:         %s
Build Directory: %s
User:            %s

%s
''' % (pl, machine_name, build_directory, user, bad_file_text)

      subject = ("TestStripPack Error Report for %s, %d errors found" %
                 (pl, self.error_count))

      log("Sending error report: " + subject)
      SendMail ([user, "donb@qualcomm.com"], subject, message)

   # End of ReportErrors()

# End of class ErrorInfo

def GatherStripPackFiles (SkipIfs):
   # Gather all .strip/.pack files from throughout the build
   log("  Gather all .strip/.pack files from throughout the build")
   start_time = time.time()
   strip_dest = os.path.join(RootDir, "strip")
   pack_dest  = os.path.join(RootDir, "pack")
   for image_dir in ImageDirs:
      for root, dirs, files in os.walk(image_dir):
         for file in [f for f in files if f.endswith('.strip')]:
            file_pfn = os.path.join(root, file)
            if not os.path.exists(os.path.join(strip_dest, file)):
               shutil.copy(file_pfn, strip_dest)
         if not SkipIfs:
            for file in [f for f in files if f.endswith('.pack')]:
               file_pfn = os.path.join(root, file)
               if not os.path.exists(os.path.join(pack_dest, file)):
                  shutil.copy(file_pfn, pack_dest)
   log("      Elapsed time: " + delta_time(start_time, time.time()))

# End of GatherStripPackFiles()


def ValidateBuildProducts ():
   '''Verify that all files listed in BuildProducts.txt have been created.'''
   if os.path.exists("BuildProducts.txt"):
      try:
         build_products = open("BuildProducts.txt", 'r')
         for file in build_products.readlines():
            file = file.strip()  # Remove newline character.
            if not os.path.exists(file):
               log("Error: Essential build product not found: " + file)
               return False
      finally:
         build_products.close()
   else:
      return False

   log("BuildProducts.txt has been verified")
   return True

# End of ValidateBuildProducts()


def SanityCheckStripBuild (err_info):
   '''Sanity check the strip build for potential errors that could
block strip approval.'''

   # Read the .ifs file and look for CONFIG_JUMASS_READ_GEOMETRY.  If it's
   # there, make sure it's stripped.  If it's not there, that means it's
   # not in the build.

   # This script uses a state machine to keep track of what it's seen in
   # the .ifs file.  It starts in state 'start'.  When it sees a symbol
   # that must be stripped, it moves to state 'need_strip'.  In this
   # state, it's looking for the end of the #if block.  If it sees the
   # 'strip' keyword before reaching the end of the #if block, it changes
   # the state to 'stripped'.  However, if it reaches the end of the #if
   # block while still in the 'need_strip' state, then it reports an error.
   # Once it sees the end of the #if block, the state goes back to 'start.

   global StripIfsFn

   must_strip_symbols = [
      'CONFIG_JUMASS_READ_GEOMETRY',
      ]

   ifs = open(StripIfsFn, 'r')
   state = 'start'
   line_number = 0
   for line in ifs.readlines():
      line_number += 1
      if state == 'start':
         for symbol in must_strip_symbols:
            if line.count(symbol):
               state = 'need_strip'
               line_found = line_number
      elif state == 'need_strip':
         if line.startswith('#else') or line.startswith('#elseif') or line.startswith('#endif'):
            # This means we reached the end of this block without seeing the 'strip' keyword.
            # If this happens, we have an error.
            err_info.AddErrorList('Strip Errors', symbol + ' not stripped on line ' + str(line_found) + ' of ' + StripIfsFn)
            state == 'start'
         elif line.startswith('strip'):
            state = 'stripped'
      elif state == 'stripped':
         if line.startswith('#else') or line.startswith('#elseif') or line.startswith('#endif'):
            state == 'start'

# End of SanityCheckStripBuild

def SanityCheckPackBuild (build, proprietary_file_list):
   '''Sanity check specified build (e.g. HY11_1) for the specified files.  Return list of illegal files.'''
   bad_file_list = []
   if os.path.exists(build):
      log("Sanity Pack Checking " + build + " build")
      for root, dirs, files in os.walk(build):
         # Get intersection of files in this directory, and those in the
         # proprietary list
         # Old version that didn't support wild-cards in proprietary_file_list
         #      intersection = [val for val in files if val in proprietary_file_list]
         intersection = [os.path.join(root, val) for val in files if [bad_match for bad_match in proprietary_file_list if fnmatch.filter([val], bad_match)]]
         if intersection:
            for file in intersection:
               bad_file_list.append(file)

   if bad_file_list:
      log(build + " contains the following proprietary files:")
      for file in bad_file_list:
         log("   " + file)

   return bad_file_list

# End of SanityCheckPackBuild()

def SanityCheckPackBuilds (err_info):
   '''Quick check of pack dirs for common files we never ship'''
   common_hy11_no_pack_files = (
      [
         # Build Files that should never be shipped.  These files contain
         # internal build server information.
         'setenv.sh',
         'setenv.cmd',

         # Register files that should never ship.  These files contain
         # information about proprietary registers.  (Can I just put msmhwio*p.h
         # here?)
         'msmhwioregp.h',
         'msmshadowp.h',
         'msmhwioreg_procp.h',

         # LTE files that should never ship.  This list came from Amir El-Ghoroury
         "lte_ml1_bplmn_log.h",
         "lte_ml1_dlm_log.h",
         "lte_ml1_gm_log.h",
         "lte_ml1_common_log.h",
         "lte_ml1_md_log.h",
         "lte_ml1_sm_log.h",
         "lte_ml1_ulm_log.h",

         # The following are shipped for 9K customers, but not for 
         # other PLs
         #"lte_mac_log.h",
         #"lte_pdcp_dl_if.h",
         #"lte_pdcp_ul_if.h",
         #"lte_rlc_log.h",
         #"lte_rrc_log.h",

         # Security files
         "ce_sha1_sw.c",   # From e-mails from Jade Xu, Dan Carolin and Rochelle Kline-Casey
         # From e-mails from Jeff O'Brien and Rochelle Kline-Casey
         "adodbapi.py",
#         "license.txt",    # These file names are too common and also match files in
#         "readme.txt",     # other modules (e.g. SCons) that do need to ship.
         "adodbapitest.py",
#         "LICENSE.txt",
#         "README.txt",
         "builtins.py",
         # From e-mail from Rochelle Kline-Casey
         "main.js",
         "prettify.js",
         "main.css",

         # My own additions
         "*.pack",
         "*.strip",
         "*.cspec"
      ])
   common_hd11_no_pack_files = common_hy11_no_pack_files
   common_hy31_no_pack_files = ['setenv.sh', 'setenv.cmd', '*.pack', '*.strip', '*.cspec']

   err_info.AddErrorList('HY11 Pack Errors', SanityCheckPackBuild("HY11_1", common_hy11_no_pack_files))
   err_info.AddErrorList('HD11 Pack Errors', SanityCheckPackBuild("HD11_1", common_hd11_no_pack_files))
   err_info.AddErrorList('HY31 Pack Errors', SanityCheckPackBuild("HY31_1", common_hy31_no_pack_files))

# End of SanityCheckPackBuilds()

#================================================================
# Main code begins here
#================================================================

# Start Logging
log_file = None
try:
   log_file = open_log_file("TestStripPack")
   log("Version $Header: //components/rel/aop.ho/5.0/aop_proc/pack/TestStripPack.py#1 $")
   
   # Record start time
   all_start_time = time.time()
   
   #================================================================
   # Define return codes
   #================================================================

   ret_success                      = 0
   ret_file_not_found               = 1
   ret_invalid_parameters           = 2
   ret_strip_pack_validation_errors = 3
   ret_buildproducts_error          = 4

   #================================================================
   # Record Usage Info
   #================================================================
   # Disable this for now until we can get it working again.
   #try:
   #   if hasattr(sys, 'frozen'):
   #      location = sys.executable
   #   else:
   #      location = __file__
   #   path, source = os.path.split(location)
   #   if sys.platform.startswith("win32"):
   #      options = ' '.join(sys.argv[1:])
   #      cmd = ["psw_tool_usage_logger.py",
   #                "--source", source,
   #                "--version", "$Header: //components/rel/aop.ho/5.0/aop_proc/pack/TestStripPack.py#1 $".split('#')[1].split()[0],
   #                "--path", path,]
   #      if options:
   #         cmd += ["--options", "'" + options + "'"]
   #      log_exec(cmd)
   #except:
   #   log("Couldn't write to usage logger")

   #================================================================
   # Initialize Parameters
   #================================================================
   
   DefaultStripFile     = 'top_level_strip.strip'
   DefaultStripIfsBfn   = 'strip'
   DefaultPackFile      = 'top_level_pack.pack'
   DefaultPackTextFile  = 'pack.txt'
   DefaultPL            = 'MPSS.NI.1.0'
   DefaultBuildDir      = 'modem_proc/build/ms'
   DefaultStripBuildCmd = ['build.cmd', 'mpss', '-k', 'USES_FLAGS=USES_NO_STRIP_NO_ODM,USES_NO_DEBUG']
   DefaultPackBuildCmd  = ['build.cmd', 'mpss', '-k']
   DefaultBuildVer      = '1004'
   DefaultCleanOpt      = None
   
   StripFiles      = None   # List of Strip files to include
   IFS_BFN         = DefaultStripIfsBfn
   PackFiles       = None   # List of Pack files to include
   PackTextFile    = None
   PackDirs        = ['*']  # Wildcard for all directories under image directory
   ImageDirs       = None
   PL              = DefaultPL
   SetFlags        = []
   BuildDir        = DefaultBuildDir
   StripBuildDir   = None
   PackBuildDir    = None
   StripBuildCmd   = DefaultStripBuildCmd
   PackBuildCmd    = DefaultPackBuildCmd
   BuildVer        = DefaultBuildVer
   CleanOpt        = DefaultCleanOpt
   PackDefines     = []
   Strict          = False
   UpdateIfsOnly   = False
   SkipIfs         = False
   SkipPackCompile = False
   Incremental     = False
   TestStripPackVersionInfo = "TestStripPack.py Version Info: $Header: //components/rel/aop.ho/5.0/aop_proc/pack/TestStripPack.py#1 $"
   err_info = ErrorInfo()

   if len(sys.argv) <= 1:
      log(__doc__)
      sys.exit(ret_success)
   
   # Read command line parameters
   for arg in sys.argv[1:]:
      parse_arg(arg)
   
   StripIfsFn = IFS_BFN + ".ifs"
   StripRspFn = IFS_BFN + ".rsp"
   
   if StripBuildDir is None:
      StripBuildDir = BuildDir
   if PackBuildDir is None:
      PackBuildDir = BuildDir
   
   # Pack Dirs must be processed after the ImageDirs is known
   if PackFiles: # if doing pack
      if ImageDirs and PackDirs:
         PackDirs = glob_list(PackDirs, ImageDirs)
      else:
         log("Error: Pack and Image directories must be specified for pack")
         log(__doc__)
         sys.exit(ret_invalid_parameters)
   
   RootDir = os.getcwd()

   #================================================================
   # Gather strip/pack files from throughout the build, and put in
   # strip/pack directories.
   #================================================================

   GatherStripPackFiles(SkipIfs)

   #================================================================
   # Start Strip/Pack
   #================================================================
   
   if StripFiles:
      log("Starting Strip Process for " + ', '.join(StripFiles))
   
      # Create temp strip file
      StripFile = 'TempStrip.strip'
      sf = open('strip/' + StripFile, 'w')
      for file in StripFiles:
         sf.write("#include " + file + '\n')
      sf.close()

      # Make .ifs file writable
      os.chmod(StripIfsFn, stat.S_IWRITE)
   
      # Run FindNewFeatures script (reads source code to update .ifs file with new features found):
      # (-v parameter should contain Build ID version for the CRM build)
      log("Running FindNewFeatures.exe")
      log_exec(["FindNewFeatures", "-i=" + StripIfsFn, "-r=" + StripRspFn, "-v=" + BuildVer, '-debug'], shell=True)
      
      # Run UpdateIFS script (updates .ifs file from .strip files):
      log("Running UpdateIFS")
      log_exec(["UpdateIFS", "-i=" + StripIfsFn, "-sl=" + StripFile, "-dir=strip", "-PL=" + PL], shell=True)
      
      if not UpdateIfsOnly:

         # Set all files to writeable, so that the strip tool can modify them.
         log("Setting all files to read-only")
         log_exec(["attrib", "/S", "-r", "*.*"], shell=True)

         #================================================================
         # Checking for cust*.h files and deleting them before starting 
         # test process
         #================================================================
         relpath = "build/ms/cust*.h"
         for imageDir in ImageDirs :
            log("Cleaning cust*.h files from"+imageDir+"\build\ms Directory")
            filepath = os.path.join(imageDir,relpath)
            for file in glob(filepath):
               os.remove(file)

         # Run stripsrc to strip the code:
         # (tech.fil is created by FindNewFeatures)
         log("Running stripsrc")
         log_exec(["stripsrc", "@" + StripRspFn, "-lis=tech.fil", "*.c", "*.cpp", "*.cxx", "*.hpp", "*.h", "*.s", "-verb"], shell=True)
         
         # Validate .ifs file after running stripsrc
         SanityCheckStripBuild(err_info)

         if not Strict or err_info.error_count == 0:
            # Only proceed if no errors were found during the sanity check.
            # Compile build to test:
            log("Compiling Strip Build")
            if StripBuildDir:
               os.chdir(StripBuildDir)
            log_exec(StripBuildCmd)
            os.chdir(RootDir)
         
            if not ValidateBuildProducts():
               sys.exit(ret_buildproducts_error)

      # end: if not UpdateIfsOnly
   
      log("Total Elapsed time for Strip: " + delta_time(all_start_time, time.time()))

   # end: if StripFiles
      
   if PackFiles:
      log("Starting Pack Process for " + ', '.join(PackFiles))
      pack_start_time = time.time()
   
      if not SkipIfs:
         # UpdateIfs requires all pack files to be in the pack directory,
         # so if we're not skipping creating the intermediate files, then
         # then we will have copied all .pack files to the pack directory,
         # and now we need to change the path of the specified pack files
         # to the pack directory.
         PackFiles = [os.path.split(x)[1] for x in PackFiles]
   
      # Create temp pack file, if needed.
      if (len(PackFiles)>1 or len(SetFlags)>0):
         PackFile = 'pack/TempPack.pack'
         pf = open(PackFile, 'w')
         for flag in SetFlags:
            pf.write("set " + flag + '\n')
         for file in PackFiles:
            pf.write("#include " + file + '\n')
         pf.close()
      else:
         PackFile = PackFiles[0]

      if not SkipIfs:
         PackTextFile = os.path.splitext(os.path.basename(PackFile))[0] + '.txt' #TempPack.txt or mdm9x15pack.txt file

         # Make pack.txt file writable
         if os.path.exists(PackTextFile):
            os.chmod(PackTextFile, stat.S_IWRITE)

         # If .pack file is in pack directory, remove the directory from the path.
         PackFilePath, PackFileFn = os.path.split(PackFile)
         if PackFilePath.startswith('pack'):
            PackFile = PackFileFn

         # Run UpdatePackTxt on specified .pack files
         log("  Running UpdatePackTxt")
         log_exec(["updatepacktxt", "-pack=" + PackFile, "-PL=" + PL, "-dir=pack"])
   
      if not UpdateIfsOnly:

         if SkipIfs:
            if not os.path.exists(PackFile):
               # Assume it's in the pack directory
               PackFile = os.path.join('pack', PackFile)

         # Clean up after any previous runs
         if Incremental:
            # Just remove the specified sub-dirs
            pass
         else:
            # Delete everything
            log("Deleting old pack directories")
            pack_dirs_wc = ['HK11*',
                            'HM11*',
                            'HY11*',
                            'HD11*',
                            'HY31*',
                            'HD31*',
                            'no_lte_workspace',
                            'TEST0000']
            for pack_dir_wc in pack_dirs_wc:
               for pack_dir in glob(pack_dir_wc):
                  if os.path.isdir(pack_dir):
                     shutil.rmtree(pack_dir, ignore_errors=False, onerror=make_writeable)

         log("Doing Pack")
         # Copy base build into HY11
         log("   Copying not-under-test directories to HY11 folder")
         for ImageDir in ImageDirs:
            shutil.copytree(ImageDir, 'HY11_1/' + ImageDir, ignore=pack_pre_copy_filter)

         # Run packit
         log("  Running packit")
         if SkipIfs:
            log_exec(["packit.exe", "-b=t", "-s2=" + PackFile, "-eng", "-PL=" + PL] + PackDefines)
         else:
            log_exec(["packit.exe", "-b=t", "-f=" + PackTextFile, "-eng"] + PackDefines)
   
         SanityCheckPackBuilds(err_info)

         if not SkipPackCompile and (not Strict or err_info.error_count == 0):
            # Copy files from HY11_1 to HY11_CompileTest
            log("Test Compiling HY11 directory:")
            log("   Copying HY11_1 to HY11_CompileTest")
            shutil.copytree('HY11_1', 'HY11_CompileTest')
      
            # Copy TEST0000 directory over HY11_CompileTest, if present.
            if os.path.isdir('TEST0000'):
               log("   Copying TEST0000 to HY11_CompileTest")
               CopyDir("TEST0000", "HY11_CompileTest")
   
            # Copy BuildProducts.txt (from the strip build) into HY11_CompileTest
            log("   Copying BuildProducts.txt to HY11_CompileTest")
            shutil.copy("BuildProducts.txt", "HY11_CompileTest")

            # Change directory to HY11_CompileTest
            log("   Changing directory to HY11_CompileTest/" + PackBuildDir)
            os.chdir("HY11_CompileTest/" + PackBuildDir)
      
            # Do clean build first to remove binaries from first copy
            if CleanOpt:
               log("   Cleaning Pack Build")
               log_exec(PackBuildCmd + [CleanOpt])
      
            # Build result
            log("   Compiling Pack Build")
            log_exec(PackBuildCmd)
            os.chdir(RootDir)
   
            if not ValidateBuildProducts():
               sys.exit(ret_buildproducts_error)

         # end: if not SkipPackCompile

      # end: if not UpdateIfsOnly

      log("Total Elapsed time for Pack: " + delta_time(pack_start_time, time.time()))

   # end: if PackFiles
   
   if err_info.error_count:
      err_info.ReportErrors (PL) 
      if Strict:
         sys.exit(ret_strip_pack_validation_errors)
   
   log("Total Elapsed time for all: " + delta_time(all_start_time, time.time()))

except:
   # Log any crashes to the log file
   if log_file:
      traceback.print_exc(None, log_file)
   raise
finally:
   # Close the log file.
   if log_file:
      log_file.flush()
      log_file.close()
   else:
      print "Error: Couldn't open log file"

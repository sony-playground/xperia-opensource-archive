#===============================================================================
#
# Generate Compile Test
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
#  $Header: //components/rel/aop.ho/5.0/aop_proc/pack/gen_compile_test.py#1 $
#  $DateTime: 2021/10/26 22:03:12 $
#  $Change: 33677139 $
#
#===============================================================================

'''
gen_compile_test.py

   This script generates a CompileTest directory from the specified parameters.

   The first parameter is expected to be the name of the "recompile" directory.
   This is the directory that [] evaluates to in the pack.txt file.

   The second parameter is expected to be the base name of the Compile Test
   directory.  For example, if this parameter is "HY31_PMIC", the script would
   create an HY31_PMIC_CompileTest directory in the recompile directory.

   The remaining parameters are expected to be items to copy into the Compile
   Test directory.

   For example:

      gen_compile_test.py [] HY31_PMIC HY11_1 HY31_PMIC modem_proc\build\ms\setenv.cmd modem_proc\build\ms\setenv.sh

   When executed from TestStripPack.py, where [] evaluates to TEST0000, this
   command would create a TEST0000\HY31_PMIC_CompileTest directory, and then would copy
   the remaining parameters into the directory in the order specified.

   If the Compile Test directory already exists, the new contents will be copied over
   the old contents, without first deleting the old contents.  This allows this
   script to be run multiple times.  For example, the following commands will produce
   the same result as the single command above:

      gen_compile_test.py [] HY31_PMIC HY11_1 HY31_PMIC
      gen_compile_test.py [] HY31_PMIC modem_proc\build\ms\setenv.cmd
      gen_compile_test.py [] HY31_PMIC modem_proc\build\ms\setenv.sh

-verify option

    <pavan's change> : while generating , if the -verify flag is used , the files are modified bya dding two lines at the end and are added , so the restricted source files are actaully built
'''



import sys
import os
import stat
import shutil


#######################################################################
# Setup Logger.
#######################################################################
import logger as lg
lg=lg.Logger('gen_compile_test', 'gen_compile_test.py: ')
on_linux = sys.platform.startswith("linux")
lg.log("Platform is: " + sys.platform,verbose=0)
lg.log("Python Version is: " + sys.version,verbose=0)
lg.log("Current directory is: " + os.getcwd(),verbose=0)

#######################################################################
# Local functions.
#######################################################################

#log = open("gen_compile_test.log", 'a')
def my_print (*args):
   '''Prefix all output statements with the name of this script, so that
they can be easily grepped in the log file.'''
   lg.log(' '.join([str(x) for x in args]))

# End of my_print()


def CopyDir(src, dst, verify=False):
   '''Copy a directory tree onto a pre-existing tree.'''
   global dict_file_len
   global restricted_list
   global base_name
   global err_found

   for root, dirs, files in os.walk(src):
      dest = root.replace(src, dst, 1)
      my_print("CopyDir: Copying", root, 'to', dst)

      file_path = os.path.join(os.getcwd(), dest)
      if (len(file_path) > 256):
         dict_file_len[file_path] = len(file_path)
         err_found = True

      if err_found == False:
         if not os.path.exists(dest):
            os.mkdir(dest)

      for file in files:
         file_path = os.path.join(os.getcwd(), dest, file)
         if (len(file_path) > 256):
            dict_file_len[file_path] = len(file_path)
            err_found = True               

         if err_found == False:
            try:
               shutil.copy(os.path.join(root, file), dest)
               #now modify the file
               if (verify==True) and (root.split('\\')[0] == base_name):
                  dest_fn = os.path.join(dest, file)
                  my_print("......Adding 3 spaces and Copying", dest_fn)
                  os.chmod(dest_fn, stat.S_IWRITE)
                  file_obj=open(dest_fn,'a')
                  file_obj.write("\n\n\n")
                  file_obj.close()
                  if file.endswith(".c") or file.endswith(".cpp"):
                      restricted_list.add(file+'\n')
            except IOError:
               # We get this a lot when running under packet, and when
               # clean_hy11 removes empty directories.  For some reason,
               # the directories are still seen in gen_compile_test when
               # using os.walk(), but when we actually try to copy them,
               # we get an IOError permissions error.  The directory then
               # finally disappears for real when Packit ends.
               #
               # However, since the directory should really be deleted anyway,
               # it's okay if we just print a warning and keep on going.
               my_print("Warning: IOError, Permissions denied, when trying to copy " +
                        os.path.join(root, file))

# End of CopyDir()


def CopyFile(src, dst,verify=False):
   '''Copy a file onto a pre-existing tree.'''
   global restricted_list
   global dict_file_len
   global base_name
   global err_found

   dest = os.path.join(dst, src)
   my_print("CopyFile: Copying", src, 'to', dest)
   
   file_path = os.path.join(os.getcwd(), dest)
   if (len(file_path) > 256): 
        dict_file_len[file_path] = len(file_path)
        err_found = True
   
   if err_found == False:
      shutil.copy(src, dest)
      #now modify the file copied
      if (verify==True) and (src.split('\\')[0] == base_name):
         my_print("......Adding 3 spaces and Copying", dest)
         file_obj=open(dest,'a')
         file_obj.write("\n\n\n")
         file_obj.close()
         file_name=dest.split('\\')[-1]
         if file_name.endswith(".c") or file_name.endswith(".cpp"):
            restricted_list.add(file_name+'\n')

# End of CopyFile()


#######################################################################
# Main Code
#######################################################################

try:
   my_print("\ngen_compile_test.py: Log Start")
   my_print("  params: " + ' '.join(sys.argv[1:]))
   restricted_list=list()
   dict_file_len = {}
   restricted_log=None
   err_found = False

   if len(sys.argv) >= 4:
      recompile_dir = sys.argv[1]
      base_name     = sys.argv[2]
      copy_items    = sys.argv[3:]
   else:
      my_print("Error: Invalid Parameters")
      my_print(__doc__)
      sys.exit(1)

   dest = os.path.join(recompile_dir, base_name + "_CompileTest")

   # Create the folder before hand as OPEN cannot be able to create intermdiate folders/links
   if not os.path.exists(dest):
      os.makedirs(dest)
   restricted_log= open(os.path.join(dest,'restricted_list.txt'),'w')

   for item in copy_items:
      my_print("Copying", item)
      restricted_list = set()
      if os.path.isdir(item):
         # If item contains subdirectories, add those to the destination.
         # This will allow copying sub-trees, such as []/modem_proc
         item = item.replace('\\', '/')  # Convert to posix style separators
         if item.count('/'):
            item_root, item_subdirs = item.split('/',1)
            new_dest = os.path.join(dest, item_subdirs)
         else:
            new_dest = dest
         CopyDir(item, new_dest, True)
      elif os.path.isfile(item):
         CopyFile(item, dest, True)
      else:
         my_print("Item", item, "doesn't exist")
      my_print("Logging the restricted source files into " ,os.path.join(dest,'restricted_list.txt') )
      restricted_log.writelines(restricted_list)

   if len(dict_file_len) > 0:
      max_file_path_len = max([dict_file_len[file] for file in dict_file_len.keys()])
      my_print("gen_compile_test.py: Error: Max file path length of " + str(max_file_path_len) + " exceeds 256 maximum. Please consider shorting the path to the root of the build by " + str(max_file_path_len-256) + " characters.")
      my_print("gen_compile_test.py: File paths exceeding max limit are:")
      for key, value in dict_file_len.items(): 
         my_print("   file " + key + ": ", value)
      sys.exit("gen_compile_test.py: Error: File path length exceeded - stop program execution")

   my_print("gen_compile_test.py: Exiting with no errors.")

except: 
   if lg:
      lg.log_exception()
   raise
finally:
   if lg:
      del lg
   if restricted_log:
      restricted_log.close()


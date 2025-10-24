#!/usr/bin/env python


#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 03/05/20   ck      Initial release


from optparse import OptionParser
import shutil
import os
import sys
import locale
import stat
import re
import platform


# Valid source file extensions
source_file_extensions = [".C", ".c", ".s", ".S"]


##############################################################################
# main
##############################################################################
def main():
   parser = OptionParser()

   parser.add_option("-s", "--start-path",
                     action="store",
                     type="string",
                     dest="start_path",
                     default=".",
                     help="Path to start searching from.  Default is current directory.")

   parser.add_option("-r", "--results-file",
                     action="store",
                     type="string",
                     dest="results_file_path",
                     default="SourceFileCheckResults.txt",
                     help="File to save results to")

   parser.add_option("--silent",
                     action="store_true",
                     dest="silent",
                     help="Execution runs with no terminal messages.")

   (options, args) = parser.parse_args()

  
   # Generate absolute start path
   absolute_start_path = os.path.abspath(options.start_path)

 
   # Open results file
   results_file = open(options.results_file_path,
                       "w")


   # Verify start path exists
   if not os.path.exists(absolute_start_path):
      logger("\nStart path does not exist....exiting",
             False,
             results_file,
             options.silent)
      
      exit()

      
   # Generate list of all source files under start path
   logger("\nGenerating list of all source files...",
          True,
          results_file,
          options.silent)
   source_files_list = generate_source_files_list(absolute_start_path)
   logger("Done",
          False,
          results_file,
          options.silent)

   
   # Generate compilation list
   logger("Generating list of all files being compiled...",
          True,
          results_file,
          options.silent)
   compilation_list = generate_compilation_list(absolute_start_path)
   logger("Done",
          False,
          results_file,
          options.silent)


   # Generate uncompiled file list by discarding files that exist in compilation and
   # discovered source files list
   logger("Generating list of all files not being compiled...",
          True,
          results_file,
          options.silent)
   uncompiled_file_list = generate_uncompiled_file_list(source_files_list,
                                                        compilation_list)
   logger("Done",
          False,
          results_file,
          options.silent)


   # Report discovered sources files that are not being compiled
   logger("Below are files found that are not being compiled:",
          False,
          results_file,
          options.silent)
   for current_uncompiled_file in uncompiled_file_list:
      logger(current_uncompiled_file,
             False,
             results_file,
             options.silent)


   # Close results file
   results_file.close()


   return


##############################################################################
# logger
##############################################################################
def logger(entry,
           skip_newline,
           results_file_path,
           silent):

   # Write entry to results file
   results_file_path.write(entry)
   if not skip_newline:
      results_file_path.write("\n")


   # If silent is not enabled then write entry to terminal
   if not silent:
      # Write entry to terminal and include or exclude new line
      if skip_newline:
         print entry,
      else:
         print entry


##############################################################################
# generate_source_files_list
##############################################################################
def generate_source_files_list(start_path):
   source_files_list = []
   
   # Walk all directories at and below start_path looking for source files
   for root, dir, files in os.walk(start_path):
      for current_file in files:
         # Check if current file ends with any valid source file extension
         for current_extension in source_file_extensions:
            if current_file.endswith(current_extension):
               # Add path to source files list
               source_files_list.append(os.path.join(root,
                                                     current_file))
               break

   return source_files_list


##############################################################################
# generate_compilation_list
##############################################################################
def generate_compilation_list(start_path):
   compilation_list = []

   # Walk all directories at and below start_path looking for .inf files
   for root, dir, files in os.walk(start_path):
      for current_file in files:
         if current_file.endswith(".inf"):
            # Get list of files this inf will compile and add to compilation list
            for current_entry in extract_compilation_list_from_inf(os.path.join(root,
                                                                                current_file)):
               # Assembly files can have "| GCC" or other compiler suffixes.  Remove them before
               # adding to compilation list
               compilation_list.append(current_entry.split("|")[0].rstrip())

   return compilation_list


##############################################################################
# extract_compilation_list_from_inf
##############################################################################
def extract_compilation_list_from_inf(inf_path):
   inf_compilation_list = []
   source_tag_found = False


   # Store directory path .inf file is in
   inf_directory = os.path.dirname(inf_path)
  

   # Open .inf file
   with open(inf_path, 'r') as inf_file:
      for current_line in inf_file:
         # If source tag has been found then check if this line is an opening for another tag
         # DO THIS FIRST
         if source_tag_found == True:
            if current_line.lstrip().startswith("["):
               source_tag_found = False

         # If source tag has not been found check if this is the opening
         if source_tag_found == False:
            if current_line.lstrip().lower().startswith("[source"):
               source_tag_found = True
               continue

         # If source tag is still found then this is a valid line.
         # Make sure line is not blank and is not commented out
         if source_tag_found == True and len(current_line) > 1 and not current_line.lstrip().startswith("#"):
            inf_compilation_list.append(os.path.abspath(os.path.join(inf_directory,
                                                                     current_line.lstrip().rstrip())))
               
   return inf_compilation_list

 
##############################################################################
# generate_uncompiled_file_list
##############################################################################
def generate_uncompiled_file_list(source_files_list,
                                  compilation_list):
   uncompiled_file_list = []
   
   # Go through source files list and if entry does not exist in compilation_list then add to
   # uncompiled file list
   for current_source_file in source_files_list:
      if current_source_file not in compilation_list:
         uncompiled_file_list.append(current_source_file)

   return uncompiled_file_list


if __name__ == '__main__':
  main()

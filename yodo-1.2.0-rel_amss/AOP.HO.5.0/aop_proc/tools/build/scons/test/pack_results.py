#!/usr/bin/env python
# =========================================================================
#
# pack_results.py
#
# GENERAL DESCRIPTION
#    Wrapper for pack lists used to validate pack builds.
#
# Copyright (c) 2011-2013 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
# -------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/tools/build/scons/test/pack_results.py#1 $
#  $DateTime: 2021/10/26 22:03:12 $
#  $Change: 33677139 $
#
# =========================================================================
'''%prog [options]

   This script can either be run from the command line to generate pack lists results
   in a json format, or imported to load and do operations on these pack lists.

   When called from the command line, the resulting json data is written to a file
   called 'pack_lists.json'.  The name of this file is hard-coded since this is the
   name of the file expected from test_pack_results.py.

   Typcally a user would run this script on a PW reference build to:

     * Generate a pack list file containing a list of all files packed in each format.
     * Check the resulting json file into Perforce.
     * Use the Package Warehouse Live Reference feature to sync the pack list file
       into a promote build.
     * Edit the promote build's settings to modify the build command line to run
       the test_pack_results.py script to validate the pack results of the pack build
       against the results recorded in the pack list file.
'''

#===============================================================================
#
# Class to represent the results of a pack operation.
#
#===============================================================================

import sys
import os
import json
from fnmatch import fnmatch

format_prefixes = [
        "HY11",
        "HK11",
        "HD11",
        "HY31",
        "HD31",
        "SRC",
        "RSRC",
        "BIN",
        "FEAT"
    ]

class PackResults(object):

    def __init__(self):

        self.formats = None

    # End of PackList.__init__()

    def InitFromBuild(self, target_root = '.'):

        "Generate new pack results given the target root of a build and\n"
        "return them in a dictionary mapping the format name to a list of\n"
        "files."

        # Find all of the format directories in the build

        self.formats = {}

        for fob in sorted(os.listdir(target_root)):
            fob_path = os.path.join(target_root, fob)
            for prefix in format_prefixes:
                if (fob != "HY11_CompileTest" and
                    fob.startswith(prefix) and
                    os.path.isdir(fob_path)):
                    self.formats[os.path.basename(fob)] = []

        print("Found the following formats: " + self.formats.keys())

        # Build the file list for each format

        for format in self.formats.keys():
            print("Processing: " + format)
            file_list = []
            format_dir = os.path.join(target_root, format)
            for dirpath, dirnames, filenames in os.walk(format_dir):
                for name in filenames:
                    abs_path = os.path.join(dirpath, name)
                    rel_path = os.path.relpath(abs_path, format_dir)
                    file_list.append(rel_path.replace('\\', '/'))
            self.formats[format] = sorted(file_list)

    # End of PackResults.InitFromBuild()

    def InitFromJson(self, json_file_path):

        with open(json_file_path, 'r') as f:
            self.formats = json.load(f)

    # End of PackResults.InitFromJson()

    def __fnmatch_diff(self, first, second):
        '''
        Return a list of file paths in first that are not in second, allowing
        for fnmatch type wildcards in elements of either list, but not both.
        '''

        result = []

        for f in first:
            if f not in second:
                # If not a direct match, there might still be a wildcard match
                match_found = False
                for s in second:
                    if fnmatch(f, s) or fnmatch(s, f):
                        match_found = True
                        break
                if not match_found:
                    result.append(f)

        return result

    # End of PackResults.__fnmatch_diff()

    def __eq__(self, other):

        added_format_count = 0
        removed_format_count = 0
        added_file_count = 0
        removed_file_count = 0

        if self.formats != other.formats:
            # Print out which areas are different
            common_formats = [x for x in self.formats.keys()
                                if x in other.formats.keys()]
            added_formats = [x for x in self.formats.keys()
                               if x not in other.formats.keys()]
            removed_formats = [x for x in other.formats.keys()
                                 if x not in self.formats.keys()]
            if added_formats:
                print("Added formats: " + added_formats)
                added_format_count += len(added_formats)
            if removed_formats:
                print("Removed formats: " + removed_formats)
                removed_format_count += len(removed_formats)
            for format in common_formats:
                if self.formats[format] != other.formats[format]:
                    added_files = self.__fnmatch_diff(self.formats[format], other.formats[format])
                    removed_files = self.__fnmatch_diff(other.formats[format], self.formats[format])
                    if added_files:
                        print("Added files for " + format + ":")
                        for file in added_files:
                            print("    " + file)
                        added_file_count += len(added_files)
                    if removed_files:
                        print("Removed files for " + format + ":")
                        for file in removed_files:
                            print("    " + file)
                        removed_file_count += len(removed_files)

        if added_format_count > 0:
            print("Added Formats: " + added_format_count)

        if removed_format_count > 0:
            print("Removed Formats: " + removed_format_count)

        if added_file_count > 0:
            print("Added Files: " + added_file_count)

        if removed_file_count > 0:
            print("Removed Files: " + removed_file_count)

        return (added_format_count + removed_format_count +
                added_file_count + removed_file_count)

    # End of PackResults.__eq__()

    def __repr__(self):

        return json.dumps(self.formats, sort_keys=True, indent=4)

    # End of PackResults.__repr__()

# End of class PackResults

#######################################################################
# Initial Script Execution
#######################################################################

# ======================================================================
# This script can be generate a pack list file suitable for use in the
# PW pack list verification tools
# ======================================================================

if __name__ == "__main__":

    print("Python version: " + sys.version)

    from argparse import ArgumentParser

    result = 0

    arg_parser = ArgumentParser(description=__doc__,
                                version="$Header: //components/rel/aop.ho/5.0/aop_proc/tools/build/scons/test/pack_results.py#1 $")

    arg_parser.add_argument("command", choices=['generate', 'compare'],
                            help="Command for script to perform.")
    arg_parser.add_argument("-rp", "--reference_path", dest="ref_path", default='.',
                            help="Path to reference build.")
    arg_parser.add_argument("-pr", "--prev_results", dest="prev_results", default='pack_results.json',
                            help="Previously generated results to compare against.")

    args = arg_parser.parse_args()
    print("Parameters are: " + args)

    pack_list_1 = PackResults()
    pack_list_1.InitFromBuild(args.ref_path)
    pack_list_2 = None

    if args.command == 'compare':

        pack_list_2 = PackResults()
        pack_list_2.InitFromJson(args.prev_results)

        result = pack_list_1 == pack_list_2
        if result == 0:
            print("Pack results are the same.")
        else:
            print("Pack results are different.")

    elif args.command == 'generate':

        with open('pack_results.json', 'w') as f:
            f.write(str(pack_list_1))

    sys.exit(result)

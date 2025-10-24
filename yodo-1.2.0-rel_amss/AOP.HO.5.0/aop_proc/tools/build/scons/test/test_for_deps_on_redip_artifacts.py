
import sys
import os.path
import argparse
import cPickle
from glob import glob
from datetime import datetime
import json


def print_elapsed_time(start_time):

    print "(Elapsed time: " + str(datetime.now() - start_time) + "secs)"

# End of print_elapsed_time()


class ComponentDetails(object):

    def __init__(self, location):

        self.comp_details = {}

        comp_details_fn = glob(os.path.join(location, "*/build/component_details.json"))
        if len(comp_details_fn) == 0:
            raise Exception("Can't find any component_details.json files.")
        comp_details_fn = comp_details_fn[0]

        with open(comp_details_fn, 'r') as f:
            self.comp_details = json.load(f)

        self.hidden_dirs = set()
        for comp in self.comp_details.values():
            if (comp['access_type'] == 'red'
                    and len(comp['artifact_directory']) > 0
                    and os.path.isdir(os.path.join(location, comp['sync_directory']))):
                # Ignore artifact directories if the sync directory is present
                self.hidden_dirs.add(comp['artifact_directory'])

    # End of ComponentDetails.__init__()

# End of class ComponentDetails


class SConsDBLiteFile(object):

    def __init__(self, location, file_name, gen_dblite_txt=False, ignore_files=False):

        self.location       = location
        self.file_name      = file_name
        self.gen_dblite_txt = gen_dblite_txt
        self.ignore_files   = ignore_files

        self.file_deps = {}
        self.data_deps = {}
        self.scons_dir = self.findSConsDir()
        print "Found SCons at:", self.scons_dir
        self.image_dir = self.findImageDir()
        self.build_dir = os.path.join(self.image_dir, 'build/ms')
        print "Image directory is:", self.image_dir
        self.build_id = os.path.basename(location)
        self.variant = None
        self.ignore_deps = []

        self.readDblite()

    # End of DepErrors.__init__()


    def findSConsDir(self):

        scons_dir_wildcard = os.path.join(self.location, '*/tools/build/scons')
        scons_dir = glob(scons_dir_wildcard)[0]
        if scons_dir is None:
            print "Error: Couldn't find SCons dir at:", scons_dir_wildcard
            sys.exit(1)

        if os.path.exists(os.path.join(scons_dir, "SCons/QC_README.txt")):
            # This is scons.qc.3.0, so add a lib directory
            scons_dir = os.path.join(scons_dir, 'SCons/lib')

        return scons_dir

    # End of DepErrors.findSConsDir()


    def findImageDir(self):

        build_ms_dir = glob(os.path.join(self.location, '*/build/ms'))
        if len(build_ms_dir) == 1:
            build_ms_dir = build_ms_dir[0]
        else:
            raise Exception("Can't find build/ms directory.")
        image_dir = build_ms_dir[len(self.location):-9]
        return image_dir

    # End of DepErrors.findImageDir()


    def readDblite(self):

        class SconsDBLiteAccessor(object):
            def __init__(self, db_name):
                dbm = SCons.dblite
                self._db_lite_db = dbm.open(db_name, "r")

            def __getitem__(self, key):
                return cPickle.loads(self._db_lite_db[key])

            def keys(self):
                return self._db_lite_db.keys()

        # End of class SconsDBLiteAccessor

        def make_relative_to_targ_root(self, filepath, cur_dir):
            if filepath == '.':
                # It's the build directory, so add a fake build directory
                filepath = self.build_dir
            elif filepath[0] == '/' or filepath[1] == ':':
                # It's an absolute path.
                if '/' + self.image_dir + '/' in filepath:
                    # It's in the build tree, so make it a relative path.
                    # It's an absolute CRM build path, so remove everything
                    # through the 'b' directory.  Note that this won't
                    # work for non-CRM builds.
                    filepath = filepath[filepath.find(self.image_dir):]
                else:
                    # It's outside of the build tree, so return None
                    return None
            elif '/' in filepath or '\\' in filepath:
                # It's already a relative path, so leave it alone
                pass
            else:
                # It's either a file in the current directory, or it's
                # a directory off of the build\ms directory.
                filepath = cur_dir + '/' + filepath
            # Convert all '\\' to '/' for consistency
            if filepath is not None:
                filepath = filepath.replace('\\', '/')
            return filepath
        # End of make_relative_to_targ_root()

        # Find and import SCons
        sys.path.insert(0, self.scons_dir)
        import SCons.compat
        import SCons.dblite

        # Read the dblite files
        dblite = self.file_name
        print "Reading dblite file:", dblite
        start_time = datetime.now()
        self.variant = dblite.split('.sconsign_')[1][:-7]
        if self.ignore_files:
            self.ignore_deps = [
                "targ" + self.variant + "q.h",
                "cust" + self.variant + "q.h"
                ]

        if self.gen_dblite_txt:
            dblite_txt_fn = self.variant + '_dblite.txt'
            dblite_txt = open(dblite_txt_fn, 'w')

        db_accessor = SconsDBLiteAccessor(dblite)

        # Go through the directories listed in the DBLite file
        for directory in sorted(db_accessor.keys()):

            contents = db_accessor[directory]
            rel_path = make_relative_to_targ_root(self, directory, self.build_dir)

            if rel_path is not None:

                if self.gen_dblite_txt:
                    dblite_txt.write("=== " + rel_path + ":\n")

                for target in sorted(contents.keys()):

                    rel_targ = make_relative_to_targ_root(self, target, rel_path)
                    if rel_targ:
                        deps = set()
                        file_deps_list = []
                        data_deps_list = []
                        targ_info = contents[target].binfo

                        if self.gen_dblite_txt:
                            dblite_txt.write(rel_targ + ":\n")

                        if (hasattr(targ_info, 'bsources') and targ_info.bsources):
                            deps |= set(targ_info.bsources)

                        if (hasattr(targ_info, 'bdepends') and targ_info.bdepends):
                            deps |= set(targ_info.bdepends)

                        if (hasattr(targ_info, 'bimplicit') and targ_info.bimplicit):
                            deps |= set(targ_info.bimplicit)

                        for dep in deps:
                            if ('[' in dep
                                or '{' in dep
                                or '=' in dep
                                or '(' in dep
                                or ',' in dep
                                or '<' in dep):
                                # Source is data, so add it to the data_deps_list
                                data_deps_list.append(dep)
                            else:
                                # It's a file, so add it to file_deps_list as a relative
                                # path if it's in the build directory tree.
                                dep = make_relative_to_targ_root(self, dep, self.build_dir)
                                if dep:
                                    file_deps_list.append(dep)

                            if self.gen_dblite_txt and dep is not None:
                                dblite_txt.write("    " + dep + "\n")

                        # End of for each dep

                        if len(file_deps_list) > 0:
                            self.file_deps[rel_targ] = file_deps_list
                        if len(data_deps_list) > 0:
                            self.data_deps[rel_targ] = data_deps_list

                    # End of if rel_targ
                # End of for each target
            # End of if rel_path is not None
        # End of for each directory

        if self.gen_dblite_txt:
            dblite_txt.close()
        print_elapsed_time(start_time)

    # End of DepErrors.readDblite()

# End of class SConsDBLiteFile


def main(location, gen_dblite_txt, ignore_files):

    start_time = datetime.now()

    result = 0
    error_list = {}

    # Read the component details
    comp_details = ComponentDetails(location)

    # Find the dblite files
    dblite_files = glob(os.path.join(location, "*/build/ms/.sconsign*.dblite"))
    if len(dblite_files) == 0:
        raise Exception("Can't find any .dblite files.")

    # Read the dblite file
    for dblite_file in dblite_files:
        error_list[dblite_file] = []
        obj = SConsDBLiteFile(location, dblite_file, gen_dblite_txt, ignore_files)
        for targ in obj.file_deps.keys():
            # Don't test targets since the declassify step creates targets in the
            # declassified folders.

            # if any([targ.startswith(x) for x in comp_details.hidden_dirs]):
            #     error_list[dblite_file].append(targ)

            for dep in obj.file_deps[targ]:
                if any([dep.startswith(x) for x in comp_details.hidden_dirs]):
                    error_list[dblite_file].append(dep)

    # Report errors found
    if any([len(x) > 0 for x in error_list.values()]):
        print("Errors found:")
        for file, errors in error_list.items():
            if len(errors) > 0:
                print("   " + file + ':')
                for error in errors:
                    print("      " + error)
        print("Summary:")
        for file, errors in error_list.items():
            short_file_name = os.path.basename(file)
            print("   " + short_file_name + " had: " + str(len(errors)) + " errors.")
            result += len(errors)
    else:
        print("No errors found")

    print_elapsed_time(start_time)

    return result

# End of main()

if __name__ == '__main__':

    parser = argparse.ArgumentParser(description='Find dependency errors')
    parser.add_argument('location', help='Location of build, needed to find format directories.  Required for type 3 errors')
    parser.add_argument('-gd', '--gen_dblite_txt', action='store_true',
                        help='Generate intermediate dblite output files.')
    parser.add_argument('-i', '--ignore_files', action='store_true',
                        help='Ignore certain files, e.g. cust*.h and targ*.h.')

    args = parser.parse_args()
    print "Arguments are: ", vars(args)

    result = main(args.location, args.gen_dblite_txt, args.ignore_files)
    sys.exit(result)



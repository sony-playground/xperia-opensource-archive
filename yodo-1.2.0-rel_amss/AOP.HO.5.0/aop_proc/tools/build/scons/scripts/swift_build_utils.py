'''
   swift_build_info_generator

   GENERAL DESCRIPTION
      swift_build_info_generator used to capture the details of each and every scons node
      when main build happens, and then later on uses this info which is stored in
      swift_details_<variant_name>.json while doing the swift build ...
'''
#==============================================================================
#
# swift_build_info_generator
#
# GENERAL DESCRIPTION
#    swift_build_info_generator used to capture the details of each and every scons node
#    when main build happens, and then later on uses this info which is stored in
#    swift_details_<variant_name>.json while doing the swift build ...
#
# Copyright (c) 2009-2021 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/tools/build/scons/scripts/swift_build_utils.py#1 $
#  $DateTime: 2021/10/26 22:03:12 $
#  $Author: pwbldsvc $
#  $Change: 33677139 $
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 05/02/21   svadaval      Create
#
#==============================================================================
import os
import json
import sys
sys.path.append(os.path.realpath(os.path.join(os.path.dirname(__file__), "../SCons/lib")))
from SCons.Node import FS
from SCons import Subst
from SCons import Action


def exists(env):
    """
    Used by SCons to make sure scripts are not allowed to be
    loaded multiple times per environment.
    """
    return env.Detect('swift_build_utils')


def generate(env):
    """
        This is the entry point called by SCons when loading this script.
        This should call other generate functions as a script might define
        multiple builders or methods.
    """
    # CollectSwiftDetails Method
    env.AddMethod(CollectSwiftDetails, "CollectSwiftDetails")
    env.AddMethod(WriteSwiftDetailsToFile, "WriteSwiftDetailsToFile")

    env.AddMethod(CheckImplictDependencyChanges, "CheckImplictDependencyChanges")
    env.AddMethod(CacheSwiftDetails, "CacheSwiftDetails")
    env.AddMethod(OnExit, "OnExit")


node_action_details = []
node_action_list_details = []


def CollectSwiftDetails(env, node, node_instance=FS.File):
    """
    It captures the required node info for all the eligible actions, so that the same will be used later on
    while running Swift incremental builds .
    :param env: Current SCons Environment
    :param node: Current SCons Node
    :param node_instance:
    :return:
    """
    debuginfo_type = 'time-actions'
    is_action_eligible = True
    if isinstance(node, node_instance):
        if node.executor is not None:
            try:
                # Python calls are stored as FunctionActions. We want to
                # filter these actions out. See SCons.Action doc:
                # https://scons.org/doc/3.1.1/HTML/scons-api/SCons.Action-module.html
                if (node.executor.action_list and not isinstance(node.executor.action_list[0],
                                                                 Action.FunctionAction)) or \
                        (isinstance(node.executor.action_list[0],Action.FunctionAction) and
                         node.executor.action_list[0].function_name() == 'list_file_extractor'):
                    # Check if atleast one action in given ListAction contains a FunctionAction and filter out such
                    # ListActions because we dont know how to run FunctionActions during Swift build.
                    if isinstance(node.executor.action_list[0], Action.ListAction):
                        is_action_eligible = is_all_list_actions_supported(node.executor.action_list[0])
                    if is_action_eligible:
                        na = NodeAction(env, node)
                        node_action_details.append(na)
                        if node.executor.action_list[0] not in node_action_list_details:
                            node_action_list_details.append(node.executor.action_list[0])
                        env.PrintInfo("Length of node_action_details is: {}".format(len(node_action_details)))
                    else:
                        env.PrintDebugInfo(debuginfo_type,
                                           "Not recording the node info, as it contains FunctionAction " + str(node))
                else:
                    env.PrintDebugInfo(debuginfo_type, "STA: node.executor.action_list not exists at node:" + str(node))
            except Exception as e:
                env.PrintInfo("Exception Occurred while recording the scons node info for node : "
                              " [%s] [%s]" %(str(node.get_path()), str(e)))

def is_all_list_actions_supported(node_list_action):
    """
    Takes in a ListAction and checks if atleast on element if that ListAction is a FunctionAction.
    :param node_list_action: Contains lists of other actions
    :return: Returns True in none of the actions in the given list action is a function action
    """
    return not any(isinstance(each_action, Action.FunctionAction) for each_action in node_list_action.list)

class NodeAction:
    """
    Class definition for saving filenode information from the on_action
    function. Intended use is to use this data and save it to a file
    in on_exit() so that the info in that file is used while running Swift Builds .
    """

    def __init__(self, env, node, node_instance=FS.File):
        if not isinstance(node, node_instance):
            self.node_sources = []
            self.node_targets = []
            self.node_dependencies = []
            self.node_action_command = ''
            self.node_path = ''
            self.node_scanner = ""
            self.node_cpppaths = []
            return

        self.node_targets = [str(x) for x in node.executor.get_all_targets()][0]
        self.node_sources = list(map(str, node.sources))
        self.node_dependencies = [str(x) for x in node.children()]
        if node.sources:
            self.node_scanner = str(node.get_source_scanner((node.sources[0])))
        else:
            self.node_scanner = ""
        self.node_cpppaths = node.env.subst("${CPPPATH}").split(' ')
        # Filtering out all the dependencies that are outside TARGET_ROOT
        for each_dependency in self.node_dependencies[:]:
            if not each_dependency.startswith(env['TARGET_ROOT']) and each_dependency.startswith("/"):
                self.node_dependencies.remove(each_dependency)

        self.node_action_command = ''
        self.node_path = node.get_path()

        if node.executor.action_list:
            action_node = node.executor.action_list[0]
            # The Action commands that we get at this point from genstring() are still raw commands
            # with all '$' symbols in it, and further needs to be processed to get the proper command line
            # by calling get_node_action_command()
            self.action_command = action_node.genstring(self.node_targets, self.node_sources, node.env)
            action_command_from_scons = self.get_node_action_command(node, env)
            self.node_action_command = action_command_from_scons

    def get_node_action_command(self, node, env):
        """

        :param node: Current SCons Node
        :param env: Current SCons Environment
        :return: Action command string for a given SCons Node
        """
        try:
            action_command_from_scons = ""
            if node.executor:
                result = node.env.subst_list(self.action_command, 0, executor=node.executor)
            else:
                result = node.env.subst_list(self.cmd_list, 0, target, source)
            escape = env.get('ESCAPE', lambda x: x)

            for cmd_line in filter(len, result):
                escape_list = Subst.escape_list
                action_command_from_scons = escape_list(result[0], escape)
                action_command_from_scons = ' '.join(action_command_from_scons)
            return action_command_from_scons
        except Exception as e:
            env.PrintInfo("Exception Occurred while generating the action command for node : "
                          " [%s] [%s]" %(str(node.get_path()), str(e)))
            return action_command_from_scons

def WriteSwiftDetailsToFile(env, swift_details_file):
    """

    :param swift_details_file: Takes in the name of the json file in which the nodes info gets saved .
    :return:
    """
    if os.path.exists(swift_details_file):
        swift_details_file_path, swift_details_file_name = os.path.split(swift_details_file)
        temp_swift_details_file = os.path.join(swift_details_file_path,
                                               "temp_" + swift_details_file_name)
        env.WriteSwiftDetailsToFile(temp_swift_details_file)
        CompareAndUpdateSwiftDetails(swift_details_file, temp_swift_details_file)
        os.remove(temp_swift_details_file)

    supported_src_extensions = [".c", ".cpp", ".cc", ".C", ".cxx", ".c++", ".S", ".s",".spp", ".SPP"]
    node_dependency_tree = {}
    node_two_way_dependency_tree = {}
    with open(swift_details_file, "w") as swift_details:
        swift_details_dict = {}
        for node in node_action_details:
            # Filtering out unsupported source file extensions
            for each_node_source in node.node_sources:
                filename, file_extension = os.path.splitext(each_node_source)
                if file_extension in supported_src_extensions:
                    swift_details_dict[each_node_source] = {"dependents": [node.node_path]}
            try:
                node_dependency_tree[node.node_targets] = node.node_dependencies
                swift_details_dict[node.node_targets]={"commands":[node.node_action_command],
                                          "sources":node.node_sources, "targets":[node.node_targets],
                                          "dependencies":node.node_dependencies, "dependents":[],
                                                       "cpppaths": node.node_cpppaths,
                                                       "scanner":node.node_scanner}
            except Exception as e:
                print("Exception Occurred while creating Dependency tree ...")
                print(e)
        for key in node_dependency_tree.keys():
            values = node_dependency_tree[key]
            node_two_way_dependency_tree[key] = {'dependents': [], 'dependencies': values}
        for key in node_dependency_tree.keys():
            values = node_dependency_tree[key]
            for value in values[:]:
                if node_two_way_dependency_tree.__contains__(value):
                    node_two_way_dependency_tree[value]['dependents'].append(key)
            try:
               swift_details_dict[key]["dependents"] = node_two_way_dependency_tree[key]['dependents']
            except Exception as e:
               print("Exception Occurred while updating the reverse dependency info ...")
               print(e)
        json.dump(swift_details_dict, swift_details,  sort_keys=True, indent=4)


def CompareAndUpdateSwiftDetails( swift_details, temp_swift_details):
    """
    checks if there are any changes in the data for a given node between the previous build and the current build .
    And updates the swift_details<variant>.json file with the updated info for a given node .
    :param swift_details: swift_details_<variant>.json that got created during main build .
    :param temp_swift_details: temp_swift_details_<variant>.json that got created during incremental build .
    :return:
    """
    is_updation_needed = False

    with open(swift_details) as main_swift_details_handler:
        main_swift_details_dict= json.load(main_swift_details_handler)

    with open(temp_swift_details) as temp_swift_details_handler:
        temp_swift_details_dict= json.load(temp_swift_details_handler)

    for each_temp_swift_details_dict_key in temp_swift_details_dict.keys():
        if not each_temp_swift_details_dict_key in main_swift_details_dict:
            print("INFO: Found new Node {0} in {1}, that is not present in {2}, "
                  "hence adding it ..".format(each_temp_swift_details_dict_key, temp_swift_details, swift_details))
            is_updation_needed = True
            main_swift_details_dict[each_temp_swift_details_dict_key] = \
                temp_swift_details_dict[each_temp_swift_details_dict_key]

        elif each_temp_swift_details_dict_key in main_swift_details_dict:
            for each_key in temp_swift_details_dict[each_temp_swift_details_dict_key].keys():
                if not temp_swift_details_dict[each_temp_swift_details_dict_key][each_key] \
                       == main_swift_details_dict[each_temp_swift_details_dict_key][each_key]:
                    is_updation_needed = True
                    print("WARNING : A change in {0} has been detected "
                          "for {1} in temp_swift_details : {2} "
                          "when compared with original swift_details: {3}, hence updating with new info".
                          format(each_key, each_temp_swift_details_dict_key, temp_swift_details, swift_details))
                    main_swift_details_dict[each_temp_swift_details_dict_key][each_key] = \
                        temp_swift_details_dict[each_temp_swift_details_dict_key][each_key]

    if is_updation_needed:
        with open(swift_details, 'w') as main_swift_details_handler:
            json.dump(main_swift_details_dict, main_swift_details_handler, sort_keys=True, indent=4)


def GenerateSwiftSconsFile(changed_files_json, swift_details_json, variant_name):
    """

    :param changed_files_json: A file that contains the list of changed files since last successful build.
    :param variant_name: Name of the variant that is being built
    :return: Returns True upon successful creation of swift*.scons file.
    """

    changed_files_list = []
    all_related_dependents = []
    dblite_filename = ".sconsign_" + variant_name + '.dblite'
    qcscons_build_dir = os.path.dirname(swift_details_json)
    qcscons_scripts = os.path.join(qcscons_build_dir, "../scripts")
    swift_variant_scons_file = os.path.join(qcscons_build_dir,"swift_" + variant_name + ".scons")
    target_root = os.path.realpath(os.path.join(os.path.dirname(__file__), "../../../../../"))
    current_dir = os.getcwd()

    os.chdir(target_root)
    with open(changed_files_json) as changed_files_json_handler:
        changed_files_dict = json.load(changed_files_json_handler)
        for changed_file in changed_files_dict['changes_since_last_successful_build']:
            changed_files_list.append(os.path.abspath(changed_file))
    os.chdir(current_dir)

    with open(swift_details_json) as swift_details_file_handler:
        swift_details_variant_dict = json.load(swift_details_file_handler)
        for changed_file in changed_files_list:
            if not changed_file in swift_details_variant_dict and not changed_file.endswith('.h'):
                print("Didn't find the required info for the given changed_file: {0}, "
                      " that is needed for running swift_build, "
                      "hence treating this build as not eligible for swift build.. ".format(changed_file))
                return False
            all_related_dependents+= get_all_related_dependents(changed_file, swift_details_variant_dict)

    all_related_dependents = set(all_related_dependents)

    print("Total no.of Actions going to be performed for current incremental build are : ", \
          len(all_related_dependents))
    sorted_all_related_dependents = sort_by_extn(all_related_dependents)

    with open(swift_variant_scons_file, "w") as swift_scons:
        swift_scons.write("import atexit\n")
        swift_scons.write("from SCons.Script import *\n")

        swift_scons.write("\nenv = Environment()\n")
        swift_scons.write("variant_name = '{variant_name}'\n".format(variant_name=variant_name))
        swift_scons.write("qcscons_build_dir = '{qcscons_build}'\n".format(qcscons_build=qcscons_build_dir))
        swift_scons.write("SCons.SConsign.File('{dblite_filename}')\n".format(dblite_filename=dblite_filename))

        swift_scons.write("env.Tool('swift_build_utils', toolpath=['{qc_scons_scripts}'])\n".
                          format(qc_scons_scripts=qcscons_scripts))
        swift_scons.write("env.CacheSwiftDetails('{swift_details_json_file}')\n".
                          format(swift_details_json_file=swift_details_json))
        swift_scons.write("targets = []\n".format(db_name=dblite_filename))

        env_counter = 0
        for each_dependency in sorted_all_related_dependents:
            env_counter+=1
            each_dependency_name_env = "env_" + str(env_counter)
            swift_scons.write("\n{env} = env.Clone()\n".format(env=each_dependency_name_env))
            swift_scons.write("{env}.Replace(CPPPATH={cpppaths})\n".format(
                cpppaths=swift_details_variant_dict[each_dependency]['cpppaths'], env=each_dependency_name_env))

            dep_sources = swift_details_variant_dict[each_dependency]['sources'] + \
                          swift_details_variant_dict[each_dependency]['dependencies']

            #Extracting the dependencies from .lf files if any, to maintain the proper dependency chain
            lf_file_deps = [each_dep for each_dep in swift_details_variant_dict[each_dependency]['dependencies']
                           if each_dep.endswith('.lf')]
            if lf_file_deps:
                for lf_file_dep in lf_file_deps:
                    if lf_file_dep in swift_details_variant_dict:
                        dep_sources+=swift_details_variant_dict[lf_file_dep]['dependencies']

            if swift_details_variant_dict[each_dependency]['commands'][0].endswith('"'):
                cmd = "targets.append({env}.Command({targs}, {sources}, r\'\'\'{action}\'\'\', " \
                      "source_scanner={scanner}))".format(
                    targs=swift_details_variant_dict[each_dependency]['targets'],
                    sources=dep_sources,
                    action=swift_details_variant_dict[each_dependency]['commands'][0],
                    scanner=swift_details_variant_dict[each_dependency]['scanner'],
                    env=each_dependency_name_env)
            else:
                cmd = "targets.append({env}.Command({targs}, {sources}, r\"\"\"{action}\"\"\", " \
                      "source_scanner={scanner}))".format(
                    targs=swift_details_variant_dict[each_dependency]['targets'],
                    sources=dep_sources,
                    action=swift_details_variant_dict[each_dependency]['commands'][0],
                    scanner=swift_details_variant_dict[each_dependency]['scanner'],
                    env=each_dependency_name_env)
            swift_scons.write("{cmd}\n".format(cmd=cmd))

        swift_scons.write("env.Alias('swift_build', targets)\n")
        swift_scons.write("Progress(env.CheckImplictDependencyChanges)\n")
        swift_scons.write("atexit.register(env.OnExit)\n")
        return True

supported_header_file_ext = [".h", ".hpp", ".hxx", ".hh"]

def get_all_related_dependents(changed_file, swift_details_variant_dict, all_related_dependents = []):
    """

    :param changed_file: File that was changed since last successful build.
    :param swift_details_variant_dict: Dict that contains the info of swift_details of a given variant.
    :param all_related_dependents: List of dependencies for a given file in changed_files.
    :return: Returns list of all related dependents for a given changed file.
    """
    dependent_files=[]
    changed_file_name, changed_file_extn = os.path.splitext(changed_file)
    if changed_file_extn in supported_header_file_ext:
        header_included_source_files = []
        for each_key in swift_details_variant_dict.keys():
            if swift_details_variant_dict[each_key].__contains__('dependencies') and\
                    swift_details_variant_dict[each_key]['dependencies'] \
                    and changed_file in swift_details_variant_dict[each_key]['dependencies']:
                header_included_source_file = swift_details_variant_dict[each_key]['targets']
                header_included_source_files+=header_included_source_file
                get_all_related_dependents(header_included_source_file[0],
                                           swift_details_variant_dict, all_related_dependents)

        print("The total no.of source files in which {header} included are :"
              " {number_of_sources} ".format(header=changed_file, number_of_sources=len(header_included_source_files)))
        all_related_dependents+=header_included_source_files

    else:
        if swift_details_variant_dict.__contains__(changed_file) and \
                swift_details_variant_dict[changed_file]['dependents']:
            dependent_files = swift_details_variant_dict[changed_file]['dependents']
            for each_dependent_file in dependent_files:
                if not each_dependent_file.endswith('.lf'):
                    all_related_dependents += dependent_files

        for dependent_file in dependent_files:
            get_all_related_dependents(dependent_file, swift_details_variant_dict, all_related_dependents)
    return all_related_dependents

def is_swift_eligible(changed_files_json, swift_details_json, variant):
    """
    Checks whether the current running incremental build is eligible for swift_build or not
    based on the files that got changed in changed_files.json provided
    :param swift_details_json: swift_details_<variant>.json that contains all info needed for swift build
    :param variant: Name of variant for which this validation is being done.
    :param changed_files_json: Json file that contains list of all files that got changed
    :return:
    """
    if not os.path.exists(changed_files_json):
        return False
    swift_build_supported_file_ext = [".c", ".C", ".cxx", ".cpp", ".c++", ".cc",
             ".h", ".hxx", ".hpp", ".hh",
             ".S", ".s", ".spp", ".SPP"]
    with open(changed_files_json) as changed_files_json_handler:
        changed_files_dict = json.load(changed_files_json_handler)
    for changed_file in changed_files_dict['changes_since_last_successful_build']:
        changed_file_name, changed_file_extn = os.path.splitext(changed_file)
        if changed_file_extn not in swift_build_supported_file_ext:
            print("WARNING : Detected an unsupported file extension {file_ext} hence not running swift"
                  " build".format(file_ext=changed_file_extn))
            return False
    if os.path.exists(swift_details_json):
        if not GenerateSwiftSconsFile(changed_files_json, swift_details_json, variant):
            return False
        return True
    else:
        return False

def CacheSwiftDetails(env, swift_details_json_file):
    """
    Reads the swift_details_json_file provided and stores it in a global dict object that can be used by other process
    while running swift build .
    :param env:
    :param swift_details_json_file: The swift details files for which the info has to be cached.
    :return:
    """
    global variant_swift_details_dict
    global swift_details_json
    global target_root
    swift_details_json = swift_details_json_file
    target_root = os.path.realpath(os.path.join(os.path.dirname(__file__), "../../../../../"))
    with open(swift_details_json_file) as swift_details_file_handler:
        variant_swift_details_dict = json.load(swift_details_file_handler)

is_swift_update_needed = False
def CheckImplictDependencyChanges(env, node):
    """
    Checks if there are any changes in implicit dependencies while running swift incremental builds
    :param env:
    :param node:Node that has to be analyzed for implicit dependencies changes
    :return:
    """

    changed_implicit_dependencies = []
    global is_swift_update_needed
    try:
        if isinstance(node, FS.File) and node.sources and [str(x) for x in node.children()]:
            old_implicit_dependencies = variant_swift_details_dict[node.get_path()]['dependencies']
            new_implicit_dependencies =[str(x) for x in node.children()]
            implicit_dependencies_diff = list(set(new_implicit_dependencies).difference(old_implicit_dependencies))

            for each_implicit_dependencies_diff in implicit_dependencies_diff:
                if not each_implicit_dependencies_diff in list(map(str, node.sources)):
                    if each_implicit_dependencies_diff.startswith(target_root):
                        changed_implicit_dependencies.append(each_implicit_dependencies_diff)

            if changed_implicit_dependencies:
                is_swift_update_needed = True
                print("WARNING : A change in implicit dependencies has been detected for {source} , "
                      "hence swift_details will be updated with new info".format(source=str(node.sources[0])))
                print("The new Implicit dependencies are {new_deps}".format(new_deps=changed_implicit_dependencies))
                sys.stdout.flush()
                variant_swift_details_dict[node.get_path()]['dependencies'].extend(changed_implicit_dependencies)

    except:
        print("Unexpected error:", sys.exc_info()[0])

def sort_by_extn(files_list):
    """

    :param files: List of files.
    :return: Returns the given list of files in sorted order based on its file extensions.
    """
    ref = ['c', 'cpp', 'h', 'o', 'lib', 'elf']
    keys = {k: v for v, k in enumerate(ref)}
    return sorted(files_list, key=lambda x: keys.get(os.path.splitext(x)[1].strip('.'), float('inf')))


def OnExit(env):
    """
    Updates the swift_details<variant_name>.json with new implict dependencies if it finds any for given changed files
    :param env:
    :return:
    """
    global is_swift_update_needed
    if is_swift_update_needed:
        print("Info: Updating swift_details*.json file....")
        with open(swift_details_json, 'w') as swift_json_handler:
            json.dump(variant_swift_details_dict, swift_json_handler, sort_keys=True, indent=4)
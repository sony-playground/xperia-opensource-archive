#==============================================================================
# GENERAL DESCRIPTION
#   Scons build to check cmd_db validity.
#
#   As of now it simply verifies ARC data. The cmd_db data is checked against
#   both HSR and Voltage plan. If needed, functionality can be extended for
#   other components in cmd_db like BCM.
#
# Copyright (c) 2019 by QUALCOMM Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#==============================================================================

import os
import sys
import subprocess
from SCons.Script import *

#------------------------------------------------------------------------------
# Globals
#------------------------------------------------------------------------------
CMD_DB_CHECK_DESC = 'CMD_DB_CHECK'
CMD_DB_CHECK_USES_FLAG = 'USES_CMD_DB_CHECK'

LOG_TAG = 'cmd_db_check'

# Various info needed by builder
check_params = {
    'target' : None,
    'voltage_plan': None,
    'arc_cmd_db': [],
    'arc_hsr': [],
    'ip_files': [],
}


#------------------------------------------------------------------------------
# Utility functions
#------------------------------------------------------------------------------

def cmd_db_check_err(env, err_msg):
    env.PrintError(err_msg)
    raise Exception('%s: %s' %(LOG_TAG,err_msg))

def real_path(env, p):
    if not env.PathExists(p):
        cmd_db_check_err(env, 'Path ' + str(p) + ' not found')
    return env.RealPath(p)


def add_version_file(env, ver_files, ver, f):
    for e in ver_files:
        ev, ef = e[0], e[1]
        if (ev == ver) and (ef != f):
            cmd_db_check_err(env, 'Error: Version conflict (ver: %s, old: %s, new: %s)'\
                             %(ev, ef, f))
        elif (ev == ver) and (ef == f):
            return

    env.PrintDebugInfo(LOG_TAG, 'Adding file (ver: %s) (file: %s)' %(ver, f))
    ver_files.append((ver, f))


def env_add_version_files(env, target, ver_files, param):
    avail = check_params.get(param, None)
    if avail is None:
        return

    for e in ver_files:
        ev, ef = e[0], e[1]
        ef = real_path(env, ef)
        add_version_file(env, avail, ev, ef)
        env.Depends(target, ef)
        check_params['ip_files'].append(ef)

    return


def write_ip_params(fh):
    for k in sorted(check_params):
        v = check_params[k]
        if type(v) is not list:
            v = str(v)
        elif type(v[0]) is tuple:
            v = '\n\t'.join(['%s (ver: %s)' %(e[1], e[0]) for e in v])
        else:
            v = '\n\t'.join([str(e) for e in v])
        fh.write(k + ':\n\t' + v + '\n')
    fh.write('\n')
    return

#------------------------------------------------------------------------------
# Scons framework plugins
#------------------------------------------------------------------------------
def exists(env):
    return True


def generate(env):
    '''
    Sets up an interface for the custom CMD_DB checker/builder for clients
    to pass files and environment to perform ops
    '''
    env.PrintDebugInfo(LOG_TAG, 'Constructing cmd_db checker')

    # Adding a usage flag to the environment
    env.AddUsesFlags(CMD_DB_CHECK_USES_FLAG, from_builds_file = True)

    # Adding a named field in Env for storing information
    rootenv = env.get('IMAGE_ENV')
    rootenv[CMD_DB_CHECK_DESC] = check_params

    # Adding a method for clients to pass files (CPR and CMD_DB)
    rootenv.AddMethod(cmd_db_check_files, 'AddCmdDBCheck')

    # Constructing a custom builder
    cmd_db_action = env.GetBuilderAction(cmd_db_checker, action_source = None)
    cmd_db_scanner = env.Scanner(cmd_db_scanner_fn, name = 'CmdDBScanner')
    cmd_db_check = env.Builder(action = cmd_db_action, emitter = cmd_db_emitter,
                               target_scanner = cmd_db_scanner)

    # Adding the above builder to environment
    rootenv.Append(BUILDERS = {'CmdDBChecker' : cmd_db_check})

    # Other setup for the builder
    target = env['MSM_ID']
    check_params['target'] = target
   

    return


def cmd_db_check_files(env, target, ip_dict):
    '''
    Invoked by clients to pass files to consider for cmd_db checks
    '''
    rootenv = env.get('IMAGE_ENV')
    if rootenv.GetUsesFlag(CMD_DB_CHECK_USES_FLAG) is False or \
       not env.IsTargetEnable(target):
        env.PrintWarning(LOG_TAG, 'Unsupported environment for CMD_DB check')
        return

    ip_valid = False
    entry = ip_dict.get('arc_cmd_db', [])
    if len(entry) > 0:
        ip_valid = True
        env_add_version_files(env, target, entry, 'arc_cmd_db')

    entry = ip_dict.get('arc_hsr', [])
    if len(entry) > 0:
        ip_valid = True
        env_add_version_files(env, target, entry, 'arc_hsr')

    entry = ip_dict.get('voltage_plan', None)
    if entry is not None:
        ip_valid = True
        new_vpf = real_path(env, entry)
        avail_vpf = check_params['voltage_plan']
        if (avail_vpf is not None) and (avail_vpf != new_vpf):
            cmd_db_check_err(env, 'Multiple Voltage Plans (old: %s) (new: %s)' \
                             %(avail_vpf, new_vpf))
        check_params['voltage_plan'] = new_vpf

        env.Depends(target, new_vpf)
        check_params['ip_files'].append(new_vpf)

    if not ip_valid:
        cmd_db_check_err(env, 'No valid input field was specified')

    return


def cmd_db_emitter(target, source, env):
    '''
    Puts dependency on target for each source file passed to this builder, so
    if any of them changes, the builder gets called
    '''
    rootenv = env.get('IMAGE_ENV')
    if rootenv.GetUsesFlag(CMD_DB_CHECK_USES_FLAG) is False:
        return

    file_list = rootenv[CMD_DB_CHECK_DESC]['ip_files']
    source.append(env.Value(file_list))
    return (target, source)


def cmd_db_scanner_fn(node, env, path):
    '''
    This function will be called once all input files are added to build
    env. Put dependency on each of them
    '''
    rootenv = env.get('IMAGE_ENV')
    if rootenv.GetUsesFlag(CMD_DB_CHECK_USES_FLAG) is False:
        return

    params = rootenv[CMD_DB_CHECK_DESC]

    # Need to create a new list otherwise it will be updated in our global
    # dictionary and somehow ends up triggering builder everytime
    file_nodes = list(params['ip_files'])
    file_nodes.extend([node])

    return file_nodes


def cmd_db_checker(target, source, env):
    '''
    Actual checking for cmd_db
    '''
    rootenv = env.get('IMAGE_ENV')
    if rootenv.GetUsesFlag(CMD_DB_CHECK_USES_FLAG) is False:
        return

    # Calling CMD_DB checker 
    #
    # NOTE: 
    # Ideally we want to import cmd_db_verify and call the exposed routine 
    # directly. However, that relies underneath on VoltagePlanParser which
    # imports Pandas/pickle modules. 
    #
    # Unfortunately, SCONS framework during initialization mucks 'pickle'
    # 'cPickle' modules for some performance reason(*). While that works on
    # Linux based environment, for Windows it leads to an exception if we
    # directly import 'pandas' on WITHIN scons process itself. So instead
    # of calling the exposed routine, we are creating a separate  process
    # and call cmd_db_verify.py directly which performs the verification.
    #
    # *Ref: http://four.pairlist.net/pipermail/scons-users/2016-March/004715.html
    
    if env['MSM_ID'] not in ['bitra', 'cedros']:                      #bitra_TODO: Enable check once proper changes are in #cedros_TODO: Enable check once proper changes are in
        checker_path = env.RealPath('${BUILD_ROOT}/core/power/cmd_db/scripts/cmd_db_verify.py')
        checker_cmd = 'python %s %s' %(checker_path, check_params['target'])

        so, se, rv = env.ExecCmds(cmds=checker_cmd, target=target, shell=True)
    else :
        rv = 0
	

    # Write output file
    op_file = env.RealPath(target[0].path)
    fh = open(op_file, 'w')
    write_ip_params(fh)

    if rv == 0:
        fh.write('Success: CMD_DB data matched')
        fh.close()
    else:
        fh.write('stdout: \n\t%s\n' %(str(so)))
        fh.write('stderr: \n\t%s\n' %(str(se)))
        fh.write('Error: \n\tCMD_DB data mismatched')
        fh.close()
        cmd_db_check_err(env, 'CMD_DB consistency failed')

    return


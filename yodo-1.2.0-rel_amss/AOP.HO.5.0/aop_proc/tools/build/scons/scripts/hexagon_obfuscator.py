'''
   Symbol Obfuscator

   GENERAL DESCRIPTION
      Symbol Obfuscator used to turn ON/OFF symbols
      by updating the CCFLAGS, ASFLAGS and LFLAGS
'''
#==============================================================================
#
# Symbol Obfuscator
#
# GENERAL DESCRIPTION
#    Symbol Obfuscator used to turn ON/OFF the symbols
#    by updating the CCFLAGS, ASFLAGS and LFLAGS
#
# Copyright (c) 2009-2020 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/tools/build/scons/scripts/hexagon_obfuscator.py#1 $
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
# 05/10/20   svadaval      Create
#
#==============================================================================
import os
import re
from SCons import Util


def exists(env):
    """
    Used by SCons to make sure scripts are not allowed to be
    loaded multiple times per environment.
    """
    return env.Detect('hexagon_obfuscator')


def generate(env):
    """
        This is the entry point called by SCons when loading this script.
        This should call other generate functions as a script might define
        multiple builders or methods.
    """
    # Obfuscation Methods
    env.AddMethod(EnableSymbolObfuscation, "EnableSymbolObfuscation")
    env.AddMethod(DisableSymbolObfuscation, "DisableSymbolObfuscation")


def get_encoded_salt_string(env):
    """
    :param env: Current SCons Environment
    :return: MD5 Encoded form of salt string for the given build
    """
    component_json_data = env.GetParsedComponentJsonData()
    if component_json_data:
        build_id = component_json_data['build_id']
        salt_string = build_id
        component_info = component_json_data['component_info']
        component_label_list = []
        component_list = component_info[0]['wcf_info']['Components']
        for each_component_info in component_list:
            component_label_list.append(each_component_info['Labels'][0]['LabelName'])
        component_label_list.sort()
        salt_string = salt_string + ";" + ";".join(component_label_list)
        return Util.MD5signature(salt_string)
    else:
        raise Exception("No component.json data found for creating symbol obfuscation salt string ...")


def EnableSymbolObfuscation(env, obfuscation_prefix="_obf_"):
    """
    :param env: Current SCons Environment
    :param obfuscation_prefix: prefixes the obfuscated symbol name with the provided value
    :return:
    """
    if "SCONS_SYMBOL_OBFUSCATION_SALT_OVERRIDE" in os.environ:
        encoded_salt_string = os.environ["SCONS_SYMBOL_OBFUSCATION_SALT_OVERRIDE"]
    else:
        encoded_salt_string = get_encoded_salt_string(env)

    if encoded_salt_string:
        if 'CONFIG_ENV' in env:
            env['CONFIG_ENV']['IS_OBFUSCATION_ENABLED'] = True
        env.Append(CCFLAGS=" -fobfuscate" + " -fobfuscation-salt=" +
                            encoded_salt_string + " -fobfuscation-prefix=" + obfuscation_prefix + " ")
                            
        env.Append(CXXFLAGS=" -fobfuscate" + " -fobfuscation-salt=" +
                            encoded_salt_string + " -fobfuscation-prefix=" + obfuscation_prefix + " ")

        env.Append(ASFLAGS=" -fobfuscate" + " -fobfuscation-salt=" +
                            encoded_salt_string + " -fobfuscation-prefix=" + obfuscation_prefix + " ")

    else:
        raise Exception("Couldn't get the encoded salt string for updating CCFLAGS with obfuscation related Options"
                        "and hence terminating...")


def DisableSymbolObfuscation(env):
    """
    :param env: Current SCons Environment
    :return:
    """

    if 'CCFLAGS' in env and type(env['CCFLAGS']) is str and "-fobfuscate" in env['CCFLAGS']:
        ccflags_without_obfuscation = re.sub(r' -fobfuscate.*fobfuscation-prefix=.*?(?=\s|$)', '', env['CCFLAGS'])
        env.Replace(CCFLAGS=ccflags_without_obfuscation)
    elif 'CCFLAGS' in env and type(env['CCFLAGS']) is Util.CLVar:
        for eachccflag in list(env['CCFLAGS']):
            if eachccflag.startswith("-fobfuscate"):
                env['CCFLAGS'].remove(eachccflag)
                
    if 'CXXFLAGS' in env and type(env['CXXFLAGS']) is str and "-fobfuscate" in env['CXXFLAGS']:
        cxxflags_without_obfuscation = re.sub(r' -fobfuscate.*fobfuscation-prefix=.*?(?=\s|$)', '', env['CXXFLAGS'])
        env.Replace(CXXFLAGS=cxxflags_without_obfuscation)
    elif 'CXXFLAGS' in env and type(env['CXXFLAGS']) is Util.CLVar:
        for eachcxxflag in list(env['CXXFLAGS']):
            if eachcxxflag.startswith("-fobfuscat"):
                env['CXXFLAGS'].remove(eachcxxflag)

    if 'ASFLAGS' in env and type(env['ASFLAGS']) is str and "-fobfuscate" in env['ASFLAGS']:
        asflags_without_obfuscation = re.sub(r' -fobfuscate.*fobfuscation-prefix=.*?(?=\s|$)', '', env['ASFLAGS'])
        env.Replace(ASFLAGS=asflags_without_obfuscation)
    elif 'ASFLAGS' in env and type(env['ASFLAGS']) is Util.CLVar:
        for eachasflag in list(env['ASFLAGS']):
            if eachasflag.startswith("-fobfuscate"):
                env['ASFLAGS'].remove(eachasflag)

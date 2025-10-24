#============================================================================
#
# @file flatten_config_table.py
#
# GENERAL DESCRIPTION
#   Custom python module that uses a header file containing the 
#   typedef for a boot_configuration_table_entry (i.e. boot_config.h) 
#   and using it to parse a c file containing a config table 
#   (i.e. sbl1_config_table in sbl1_config.c) or a single 
#   config table entry and create a flattened version of the c file
#   with no function pointers for the purpose of static analysis.
#
# NOTES
#   - intended for use as a python import
#   - should work on all platforms (tested on Windows and Linux)
#   - written in python3 syntax
#
# MAINTAINENCE
#   - should only require rework if there are major changes to the
#     format of boot_configuration_table_entry typedef
#
# Copyright (c) 2018, 2022 Qualcomm Technologies, Inc. All rights reserved.
#
#----------------------------------------------------------------------------
#
#                          EDIT HISTORY FOR MODULE
#
# This section contains comments describing changes made to the module.
# Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     -----------------------------------------------------------
# 08/25/22   rama    Update for finding compiler from buildconfig
# 09/07/18   msantos Initially written for boot.xf.3.0/3.2

import os
import re

#####################################################################
# parse the struct boot_configuration_table_entry
# to determine the indexes of function lists
# and generate a new c file with calls to those functions
#####################################################################
def main(path_boot_config_h, path_c_code, table_name, outputdir, outputfilename):
  print('Looking for typedef "boot_configuration_table_entry" in header file "'+path_boot_config_h+'"')
  
  if not os.path.isdir(outputdir):
    os.makedirs(outputdir)
    
  boot_config_h = remove_c_comments(open(path_boot_config_h).read())

  # use typedef struct in boot_config.h to determine the relevant indexes within a table entry
  matchobj = re.search(
      r'typedef\s*struct\s*{\s*([^}]*)\s*}\s*boot_configuration_table_entry\s*;',
      boot_config_h, re.DOTALL | re.MULTILINE)
  if not matchobj:
    raise Exception('could not find struct boot_configuration_table_entry in '
                 +path_boot_config_h)
  struct_members = matchobj.group(1).split(';')
  exec_index = get_struct_member_index(struct_members, r'boot_boolean\s*exec')
  jump_index = get_struct_member_index(struct_members, r'boot_boolean\s*jump')
  execfunc_index = get_struct_member_index(struct_members, r'boot_procedure_func_type\s*exec_func')
  jumpfunc_index = get_struct_member_index(struct_members, r'boot_procedure_func_type\s*jump_func')
  preprocs_index = get_struct_member_index(struct_members, r'boot_function_table_type\s*\*\s*pre_procs')
  postprocs_index = get_struct_member_index(struct_members, r'boot_function_table_type\s*\*\s*post_procs')
  loadcancel_index = get_struct_member_index(struct_members, r'boot_logical_func_type\s*load_cancel_func')
  targetimgstr_index = get_struct_member_index(struct_members, r'uint8\s*\*\s*target_img_str')

  print('Looking for config table "'+table_name+'" in c file "'+path_c_code+'"')

  c_code = remove_c_comments(open(path_c_code).read())
  
  # find config table in c_code
  table = get_config_table(table_name, c_code)
  if table is None:
    return None

  # generate c file that can be parsed by static analyzer
  list = get_list_from_table(table, exec_index, jump_index,
                             execfunc_index, jumpfunc_index,
                             preprocs_index, postprocs_index,
                             loadcancel_index, targetimgstr_index)

  newfile = create_flattened_c_file(c_code, list, table_name,
                                    outputfilename,
                                    outputdir,
                                    outputfilename)
  print('Successfully flattened "'+table_name+'" into "'+newfile+'"')
  return newfile

#####################################################################
# remove c-style comments from a string
#####################################################################
def remove_c_comments(code):
  def replacer(match):
    s = match.group(0)
    if s.startswith('/'):
      return " " # note: a space and not an empty string
    else:
      return s
  pattern = re.compile(r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"', re.DOTALL | re.MULTILINE)
  return re.sub(pattern, replacer, code)

#####################################################################
# determine the index of a regex in a struct
#####################################################################
def get_struct_member_index(struct_members, regex):
  index = 0
  for member in struct_members:
    matchobj = re.search(regex, member, re.DOTALL | re.MULTILINE)
    if matchobj:
      break
    index += 1
  if index >= len(struct_members):
    raise Exception('get_struct_member_index(): could not find struct member matching regex "'+regex+'"')
  return index
  
#####################################################################
# get the table from code and return as a list of each entry
#####################################################################
def get_config_table(table_name, code):
  # try to find a table of entries
  matchobj = re.search(r'boot_configuration_table_entry\s*'+table_name+'\s*\[\s*\]\s*=\s*{\s*((?:(?!}\s*;).)*)\s*}\s*;',
                       code, re.DOTALL | re.MULTILINE)
  if not matchobj: # try to find a single entry
    matchobj = re.search(r'boot_configuration_table_entry\s*'+table_name+'\s*=\s*{\s*((?:(?!}\s*;).)*)\s*}\s*;',
                         code, re.DOTALL | re.MULTILINE)
  if matchobj:
    table = re.sub(r'\s','',matchobj.group(1))
    # if there are any strings in the table, remove non-alphanumerics from string
    clean_table = re.sub(r'"[^"]*"', lambda m: re.sub(r'[^0-9a-zA-Z"]+','',m.group()), table)
    return clean_table.split('},')
  else:
    raise Exception('get_config_table(): could not find table "'+table_name+'"')


#####################################################################
# parse the table to return a list of img strings, procs arrays, and funcs
# formatted as a tuple (type, element)
#####################################################################
def get_list_from_table(table, exec_index, jump_index,
                        execfunc_index, jumpfunc_index,
                        preprocs_index, postprocs_index,
                        loadcancel_index, targetimgstr_index):
  list = []
  for entry in table:
    entry = entry.replace('}','').replace('{','').split(',')
    if entry[0] != 'MEDIA_TYPE_MAX':
      #MUST DO IN THIS ORDER TO MAINTAIN EXECUTION ORDER
      if entry[targetimgstr_index] != 'NULL':
        list.append(('img',entry[targetimgstr_index]))
      if entry[preprocs_index] != 'NULL':
        list.append(('procs',entry[preprocs_index]))
      if entry[loadcancel_index] != 'NULL':
        list.append(('func',entry[loadcancel_index]))
      if entry[exec_index] == 'TRUE' and entry[execfunc_index] != 'NULL':
        list.append(('func',entry[execfunc_index]))
      if entry[postprocs_index] != 'NULL':
        list.append(('procs',entry[postprocs_index]))
      if entry[jump_index] == 'TRUE' and entry[jumpfunc_index] != 'NULL':
        list.append(('func',entry[jumpfunc_index]))
  return list

#####################################################################
# create a c file that has static-analyzable function calls
#####################################################################
def create_flattened_c_file(code, list, table_name, root_func_name, outputdir, outputfilename):
  #convert array to function
  proc_list = []
  for (type,arrayname) in list:
    if type == 'procs':
      oldcode = code
      if arrayname in proc_list:
        continue
      contents = find_and_convert_procs_array(code, arrayname)
      code = re.sub(r'boot_function_table_type\s*'+arrayname+'*[^;]*',
             r'static void '+arrayname+'(boot_handle config_context_handle)\n{\n'
             +contents+'}\n',
             code, flags=re.DOTALL | re.MULTILINE)
      proc_list.append(arrayname)
      if oldcode == code:
        raise Exception('create_flattened_c_file(): failed to replace procs array "'+arrayname+'"')


  # generate function for each image
  func = ''
  single_img_additional_code = ''
  multi_img_additional_code = ''
  contents = ''
  imgcount = 0
  same_img = False
  for (type,name) in list:
    if same_img:
      if type == 'img':
        same_img = False
        func += '\n}\n'
        multi_img_additional_code += func
      else: # 'procs' or 'func'
        func += '\t'+name+'(config_context_handle);\n'
        single_img_additional_code += '\t'+name+'(config_context_handle);\n'
    if type == 'img':
      parentfuncname = find_and_convert_img_name(code, name)
      contents += parentfuncname+'(config_context_handle);\n'
      imgcount += 1
      func = 'static void '+parentfuncname+'(boot_handle *config_context_handle)\n{\n'
      same_img = True
  func += '\n}\n'
  multi_img_additional_code += func

  filepath = os.path.join(outputdir, outputfilename+'.c')
  new_c_file = open(filepath, 'w')
  oldcode = code
  if imgcount > 1:
    # replace table in code with generated root function
    code = re.sub(r'boot_configuration_table_entry\s*'+table_name+'\s*\[\s*\]\s*=\s*{\s*((?:(?!}\s*;).)*)\s*}\s*;',
                  r'static void '+root_func_name+'(boot_handle *config_context_handle)\n{\n'+contents+'}\n',
                  code, flags=re.DOTALL | re.MULTILINE)
    new_c_file.write(code)
    new_c_file.write(multi_img_additional_code)
  else:
    # replace single entry in code with generated root function
    code = re.sub(r'boot_configuration_table_entry\s*'+table_name+'\s*=\s*{\s*((?:(?!}\s*;).)*)\s*}\s*;',
                  r'static void '+root_func_name+'(boot_handle *config_context_handle)\n{\n'+single_img_additional_code+'}\n',
                  code, flags=re.DOTALL | re.MULTILINE)
    new_c_file.write(code)
  new_c_file.close()
  if oldcode == code:
    raise Exception('create_flattened_c_file(): failed to replace table "'+table_name+'"')
  return filepath

#####################################################################
# convert a target_img_str into a function name
#####################################################################
def find_and_convert_img_name(code, name):
  # try to find a define string
  matchobj = re.search(r'#define\s*'+name+'[^"]*"\s*([^"]*)\s*"\s*', code)
  if not matchobj: # try to find an inline string
    matchobj = re.search(r'"([^"]*)"', name)
  if matchobj:
    return matchobj.group(1).replace(' ','_')
  else:
    raise Exception('find_and_convert_img_name(): could not find valid target_img_str for "'+name+'"')

#####################################################################
# convert a boot_function_table_type array into a function
#####################################################################
def find_and_convert_procs_array(code, name):
  matchobj = re.search(r'boot_function_table_type\s*'+name+'\s*\[\s*\]\s*=\s*{\s*([^;]*)', code, re.DOTALL | re.MULTILINE)
  if matchobj:
    return re.sub(r'\"(.*?)\"','(config_context_handle);',matchobj.group(1).replace('NULL','').replace(',','').replace('}','').replace('{',''))
  else:
    raise Exception('find_and_convert_procs_array(): could not find procs array "'+name+'"')
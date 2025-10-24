import os
import subprocess
import string
import re
import shutil
import struct
import sys
import os, string, xml.etree.ElementTree as ET
#from mako.template import Template
import binascii
import ctypes
#------------------------------------------------------------------------------
# Globals
#------------------------------------------------------------------------------
DEVCFG_USES_FLAG = 'USES_DEVCFG'
DEVCFG_ENV_DESC = 'AOP_DEVCFG'
DEVCFG_C_FILE_TAG = 'c_files'
DEVCFG_XML_TAG = 'xml_files'
DEVCFG_LOG_TAG = 'DEVCFG_ERR'
DEVCFG_AUTOGEN_FILEPATH = '${BUILD_ROOT}/core/bsp/aop/build/aop_settings_autogen.c'

#XML parser globals
ROOT_TAG_NAME = 'driver'
device_tags = ['device']
property_tags = ['props', 'property']
device_list = []
'''
device_list is populated as:
[{'id': 2260696055L, 'name': 'test_driver', 'property_list': {'foo_name': {'id': 450215437L, 'val': '2'}, 
                                                              'test_struct': {'id': 3188011298L, 'val': 'TestStruct_instance'}}}, 
{'id': 965371593L, 'name': 'test_driver2', 'property_list': {'foo_bar_name': {'id': 2212294583L, 'val': '1'},
                                                             'test_struct': {'id': 3473668824L, 'val': 'TestStruct_instance2'}}}]
'''
include_list = []
#------------------------------------------------------------------------------
# Error handlers
#------------------------------------------------------------------------------
def fatal_devcfg_err(env, err_msg):
  env.PrintError(err_msg)
  raise Exception('%s: %s' %(DEVCFG_LOG_TAG,err_msg))

def xml_parser_error(env, err_str):
  env.PrintError(err_str)
  raise Exception('%s: %s' %('DEVCFG XML PARSER ERROR:', err_str))
#------------------------------------------------------------------------------
# xml parser and settings file generator
#------------------------------------------------------------------------------
def include_interfaces_for_an_xml(env, xml_file):
  #account for target specific path
  target = env['MSM_ID']
  #only pick till config, no internal dirs needed and look for interface dir
  interface_path = env.RealPath(os.path.relpath(os.path.join(os.path.dirname(xml_file), '../../interface')))
  if os.path.isdir(env.RealPath(os.path.relpath(os.path.join(interface_path, target)))):
    #interface too has target specific folder, pick only for cur target
    interface_path = env.RealPath(os.path.relpath(os.path.join(interface_path, '${MSM_ID}')))
  if os.path.isdir(interface_path):
    #if an interface path present include .h found there.
    for file in [f for f in os.listdir(interface_path) if f.endswith('.h')]:
      print 'including..', os.path.join(interface_path, file)
      include_list.append(os.path.join(interface_path, file))

def parse_devcfg_xml(env, xml_file):
  include_interfaces_for_an_xml(env, xml_file)
  tree = ET.parse(env.RealPath(xml_file))
  root = tree.getroot()
  if root.tag != ROOT_TAG_NAME:
    #check if xml had valid root tag
    xml_parser_error(env, 'XML root tag driver not found. Was expecting %s, but found %s in %s'%(ROOT_TAG_NAME,
                                                                                                 root.tag,
                                                                                                 str(env.RealPath(xml_file))))
  #looks like a valid xml
  driver_xml_node = root
  for device_node in driver_xml_node:
    if device_node.tag not in device_tags:
      #dont read from unknown tags
      xml_parser_warn(env, 'XML had unknown tags: '+device_node.tag+'. Continuing..')
      continue
    #print 'device tag: ', device_node.tag
    #print 'device attr: ', device_node.attrib
    #print 'device text: ', device_node.text

    device = {}
    device['name'] = device_node.attrib['name'].strip()
    device['id'] = ctypes.c_uint32(binascii.crc32(device['name'])).value
    device['property_list'] = {}
    for property in device_node:
      if property.tag not in property_tags:
        #dont read from unknown tags
        xml_parser_warn(env, 'XML had unknown tags: '+property.tag+'. Continuing..')
        continue
      #print 'property tag: ', property.tag
      #print 'property attr: ', property.attrib
      #print 'property text: ', property.text
      device['property_list'][property.attrib['name']] = {'val' : property.text.strip(), 
                                                          'id' : ctypes.c_uint32(binascii.crc32(property.attrib['name'].strip())).value}
      if property.attrib['type'] == 'AOPPROP_ATTR_TYPE_STRUCT_PTR':
        device['property_list'][property.attrib['name']]['val'] = '(uint32_t)&'+property.text.strip()
    device_list.append(device)



#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return True

def generate(env):
  #sets up an interface to generate aop devcfg image
  target = env['MSM_ID']
  env.PrintDebugInfo('generate', target)
  aop_devcfg_generate(env)

def aop_devcfg_emitter(target, source, env):
   # here one can also add dependencies for say aexe.exe (if it needs to be build)
   # env.Depends(target, propgen_tool)
   # so when we clean this target, we would know what else to clean.
   return (target, source)

def aop_devcfg_generate (env):
  #global files map
  rootenv = env.get('IMAGE_ENV')
  rootenv[DEVCFG_ENV_DESC] = []

  #method to get files to be added in devcfg bin
  env.AddMethod(aop_devcfg_add_files, "AddDevCfgInfo")
  #wrapper method for builder
  env.AddMethod(aop_devcfg_build_wrap, "AOPDevCfgGen")
  #wrapper method for getting list of src files
  env.AddMethod(aop_devcfg_get_files, "GetDevCfgFiles")
  return

def aop_devcfg_build_wrap(env, target):
  aop_devcfg_obj = env.GetDevCfgFiles(target)
  aop_devcfg_elf = env.Program(target, aop_devcfg_obj)
  return aop_devcfg_elf

def get_settings_driver_sources(env, target):
  imports = ['import sys, os, time']
  variables = {'include_list' : include_list,
               'device_list' : device_list}
  #open the template file
  mako_egg = env.RealPath('${BUILD_ROOT}/core/settings/src/templates/Mako-1.1.3-py2.7.egg')
  print 'mako egg path: ', mako_egg
  sys.path.append(mako_egg)
  from mako.template import Template
  source_template = Template(filename=env.RealPath('${BUILD_ROOT}/core/settings/src/devcfg_tmpl'), 
                             output_encoding='utf-8',
                             input_encoding='utf-8')
  c_file = open(env.RealPath(DEVCFG_AUTOGEN_FILEPATH), 'w')
  c_file.write(source_template.render(**variables))
  c_file.close()
  env.Depends(target, DEVCFG_AUTOGEN_FILEPATH)
  return [DEVCFG_AUTOGEN_FILEPATH]

def aop_devcfg_get_files(env, target):
  rootenv = env.get('IMAGE_ENV')
  user_added_c_sources = rootenv[DEVCFG_ENV_DESC]
  auto_gen_sources = get_settings_driver_sources(env, target)
  return user_added_c_sources + auto_gen_sources

def aop_devcfg_add_files(env, target, input_dict):
  '''
  This function gets called when client invokes AddDevCfgInfo
  '''
  rootenv = env.get('IMAGE_ENV')
  if rootenv.GetUsesFlag(DEVCFG_USES_FLAG) is False or \
     not env.IsTargetEnable(target):
      env.PrintWarning('Adding devcfg file for unsupported environemnt')
      return

  # Input validation
  xml_file_paths = input_dict.get(DEVCFG_XML_TAG, None)
  if xml_file_paths is not None:
    for xml_path in xml_file_paths:
      parse_devcfg_xml(env, xml_path)

  c_file_paths = input_dict.get(DEVCFG_C_FILE_TAG, None)
  if c_file_paths is not None:
    if type(c_file_paths) is not list:
      c_file_paths = [c_file_paths]

    #add this to the global list of sources
    for ip_path in c_file_paths:
      if not env.PathExists(ip_path):
        fatal_devcfg_err(env, 'Path ' + str(ip_path) + ' not found')

      #get full path
      full_path = env.RealPath(ip_path)
      if not os.path.isfile(full_path):
        fatal_devcfg_err(env, str(ip_path) + ' needs to be a .c or .h source')
      #see if its a file, for now, dir scanning for .xml and .c isn't supported
      env.Depends(target, full_path)
      print 'Adding to devcfg image ', full_path
      rootenv[DEVCFG_ENV_DESC].append(full_path)



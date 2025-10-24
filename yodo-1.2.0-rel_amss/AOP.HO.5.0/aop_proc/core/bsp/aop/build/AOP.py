#===============================================================================
#
# AOP image build script
#
# GENERAL DESCRIPTION
#    build script
#
# Copyright (c) 2016-2019 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# Proprietary and Confidential - Qualcomm Technologies, Inc
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/core/bsp/aop/build/AOP.py#10 $
#  $DateTime: 2022/10/06 12:32:03 $
#  $Author: pwbldsvc $
#  $Change: 40143744 $
#
#===============================================================================
import os
import glob
import imp
import string
from SCons.Script import *

#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
   return env.Detect('AOP Image')

def generate(env):
  #------------------------------------------------------------------------------
  # Decide build steps
  #------------------------------------------------------------------------------
  # That is, if the user has asked for a filtered build, don't try to link.
  filter_opt = env.get('FILTER_OPT')
  do_link = False if filter_opt is not None else True
  do_local_files = False if not do_link and not env.FilterMatch(os.getcwd()) else True

  #-------------------------------------------------------------------------
  # Libs/Objs
  #-------------------------------------------------------------------------
  aop_libs_path = env.get('INSTALL_LIBPATH')
  aop_libs = env.get('AOP_LIBS')
  aop_objs = env.get('AOP_OBJS')

  aop_units_list = []

  if do_local_files:
    #---------------------------------------------------------------------------
    # AOP image-level sources
    #---------------------------------------------------------------------------
    env = env.Clone()

    AOP_SRC = "../src"
    env.VariantDir("${BUILD_PATH}", AOP_SRC, duplicate=0)
    env.Append(CFLAGS = '${ARMCC_STDC99_CMD}')
    env.Append(CCFLAGS = '${ARMCC_DOLLAR_CMD}')

    if env['BUILD_VER'].isdigit():
      build_id = str(int(env['BUILD_VER']))
    else:
      build_id = str(zlib.adler32(env['BUILD_VER']) & 0xFFFFFFFF)
    env.Append(CPPDEFINES = [('AOP_BUILD_ID', build_id)])

    if env['MSM_ID'] == 'waipio':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'WAIPIO_STUBS')
      env.Append(CPPDEFINES = 'WAIPIO_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')
    elif env['MSM_ID'] == 'kailua':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'KAILUA_STUBS')
      env.Append(CPPDEFINES = 'KAILUA_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')
    elif env['MSM_ID'] == 'fillmore':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'FILLMORE_STUBS')
      env.Append(CPPDEFINES = 'FILLMORE_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')      #FILLMORE_TODO
    elif env['MSM_ID'] == 'aurora':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'AURORA_STUBS')
      env.Append(CPPDEFINES = 'AURORA_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')      #AURORA_TODO
    elif env['MSM_ID'] == 'lassen':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'LASSEN_STUBS')
      env.Append(CPPDEFINES = 'LASSEN_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')      #LASSEN_TODO
    elif env['MSM_ID'] == 'netrani':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'NETRANI_STUBS')
      env.Append(CPPDEFINES = 'NETRANI_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')      #NETRANI_TODO
    elif env['MSM_ID'] == 'lanai':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'LANAI_STUBS')
      env.Append(CPPDEFINES = 'LANAI_TARGET_CONFIG')
      env.Append(CPPDEFINES = 'SVE_NEEDS')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')
    elif env['MSM_ID'] == 'kapiti':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'KAPITI_STUBS')
      env.Append(CPPDEFINES = 'KAPITI_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')      #KAPITI TODO
    elif env['MSM_ID'] == 'pinnacle':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'PINNACLE_STUBS')
      env.Append(CPPDEFINES = 'PINNACLE_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')
    elif env['MSM_ID'] == 'kuno':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'KUNO_STUBS')
      env.Append(CPPDEFINES = 'KUNO_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')
    elif env['MSM_ID'] == 'hamoa':
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'HAMOA_STUBS')
      env.Append(CPPDEFINES = 'HAMOA_TARGET_CONFIG')
      env.Append(CCFLAGS    = ' -mlong-calls')
      env.AddUsesFlags('USES_REMOTE_QTI_SIGN')
    else:
      env.Append(CPPDEFINES = 'NO_STACK_CHECK')
      env.Append(CPPDEFINES = 'UNKNOWN_TARGET_STUBS')
      env.Append(CCFLAGS    = ' -mlong-calls')

    #----------------------------------------------------------------------------
    # Dependencies on CoreBSP code
    #----------------------------------------------------------------------------
    CBSP_API = [
       'BOOT',
       'BUSES',
       'DAL',
       'DEBUGTOOLS',
       'MPROC',
       'PMIC',
       'POWER',
       'SYSTEMDRIVERS',
       'DEBUGTRACE',
       'PrngCL',
       'SERVICES',
       'KERNEL',
       'SYSTEMDEBUG',
       'AOP_SETTINGS',
       'PMIC_SETTINGS',
       'DBGINFOLIB',
    ]

    env.RequirePublicApi(CBSP_API)
    env.RequireRestrictedApi(CBSP_API)

    #----------------------------------------------------------------------------
    # Sources, libraries
    #----------------------------------------------------------------------------

    # stubs and other qcore app files
    AOP_SOURCES = [
       'main.c',
       './target/${MSM_ID}/target_main.c',
    ]
    AOP_SPECIAL_SOURCES = [
       #'datetime.c'
    ]
    AOP_STARTUP_SOURCES = [
       #'startup.s',
    ]

    DEVCFG_C_SOURCES = [
      '${BUILD_ROOT}/core/bsp/aop/src/devcfg_main.c',
    ]
    # add sources to devcfg
    env.AddDevCfgInfo(['CORE_AOP'], {'c_files': DEVCFG_C_SOURCES})

    aop_special_objs = env.Object(AOP_SPECIAL_SOURCES)
    aop_startup_objs = env.Object(AOP_STARTUP_SOURCES)
    for so in aop_special_objs:
      so.set_always_build ()
    aop_objs.extend(env.Object(AOP_SOURCES))
    aop_objs.extend(aop_special_objs)
    if env['MSM_ID'] in ['55', '8250', 'Saipan', '8350', 'bitra', 'Chitwan', 'makena', 'cedros', 'Olympic','kodiak','makenaau']:
      aop_objs.extend(aop_startup_objs)

    # Add CMM Scripts to the menu
    if env['IMAGE_NAME'] in ['AOP']:
      SRCPATHSCRIPTS = env['BUILD_ROOT']+'/core/bsp/aop/scripts'
      env.AddCMMScripts ('AOP', [SRCPATHSCRIPTS], { 'aop_dump.cmm' : 'AOP Core Dump'}, 'Kernel')

    if do_link:
      if('GENERATE_DEVCFG_MBN_ONLY' not in os.environ):
        target_scl = env.SclBuilder('${TARGET_NAME}', [
        #'../src/aop.scl',
        '${BUILD_ROOT}/core/kernel/rex/target/${MSM_ID}/aop.scl',])

        aop_elf = env.Program('${TARGET_NAME}', aop_objs, LIBS=aop_libs, LIBPATH=aop_libs_path)
        aop_elf_system_view = env.AopElfBuilder ('${TARGET_NAME}' + '_aop', aop_elf)

        if('USES_REMOTE_QTI_SIGN' in env):
		  if env['MSM_ID'] in ['waipio']:
			chipset_pmic = os.environ['CHIPSET_PMIC']
			aop_mbn = env.AOPImageSigner('${TARGET_NAME}', aop_elf_system_view,
										OUTPATH='${BUILD_ROOT}/build/aop/bf/build/'+chipset_pmic+'/')
		  else:
			aop_mbn = env.AOPImageSigner('${TARGET_NAME}', aop_elf_system_view,
										OUTPATH='${BUILD_ROOT}/build/aop/bf/build/'+env['MSM_ID']+'/')
        else:
          env.Append(USE_MBN_TOOLS = 'True')
          env.AddUsesFlags('USES_MBNTOOLS')

          if env['MSM_ID'] in ['55', '8250', 'Saipan', '8350', 'bitra', 'Chitwan', 'makena', 'cedros', 'Olympic','kodiak','makenaau']:
            env.AddUsesFlags('USES_PLATFORM_IMAGE_INTEGRITY_CHECK')

          env.Replace(GLOBAL_DICT = {'IMAGE_KEY_AOP_IMG_DEST_ADDR' : 0xFC100080})
          aop_mbn = env.MbnBuilder(
                            '${TARGET_NAME}',
                            aop_elf_system_view,
                            IMAGE_TYPE="aop",
                            FLASH_TYPE="sdcc",
                            MBN_TYPE="elf"
                        )

        env.Depends(aop_elf, target_scl)
        env.Requires(aop_elf, target_scl)

        env.Clean(aop_elf, env.subst('${TARGET_NAME}.map'))
        env.Clean(aop_elf, env.subst('${TARGET_NAME}.sym'))

        aop_units_list += [aop_elf, aop_elf_system_view, aop_mbn,]
      else:
        print '***************************************'
        print 'Building only aop devcfg image'
        print '***************************************'

      if env.GetUsesFlag('USES_DEVCFG') is True:
        devcfg_target_scl = env.SclBuilder('${TARGET_NAME}'+'_devcfg',
                                           ['${BUILD_ROOT}/core/kernel/rex/target/${MSM_ID}/aop_devcfg.scl',])
        aop_devcfg_elf = env.AOPDevCfgGen('${TARGET_NAME}'+'_devcfg')
        if env['MSM_ID'] in ['waipio']:
          chipset_pmic = os.environ['CHIPSET_PMIC']
          aop_devcfg_mbn = env.AOPDevCfgSigner('${TARGET_NAME}'+'_devcfg', aop_devcfg_elf,
                                               OUTPATH='${BUILD_ROOT}/build/aop/bf/build/'+chipset_pmic+'/')
        else:
          aop_devcfg_mbn = env.AOPDevCfgSigner('${TARGET_NAME}'+'_devcfg', aop_devcfg_elf,
                                               OUTPATH='${BUILD_ROOT}/build/aop/bf/build/'+env['MSM_ID']+'/')

        env.Depends(aop_devcfg_elf, devcfg_target_scl)
        env.Requires(aop_devcfg_elf, devcfg_target_scl)
        env.Clean(aop_devcfg_elf, env.subst('${TARGET_NAME}_devcfg.map'))
        env.Clean(aop_devcfg_elf, env.subst('${TARGET_NAME}_devcfg.sym'))

        aop_units_list += [aop_devcfg_elf, aop_devcfg_mbn]

      aop_units = env.Alias('aop_units', aop_units_list)

      # add aliases
      aliases = env.get('IMAGE_ALIASES')
      for alias in aliases:
        env.Alias(alias, aop_units)

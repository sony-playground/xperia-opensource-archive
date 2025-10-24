'''
   CoreBSP SINGLE proc tool rules
'''
#===============================================================================
#
# CoreBSP SINGLE proc tool rules
#
# GENERAL DESCRIPTION
#    rules build script
#
# Copyright (c) 2009-2009 by Qualcomm Technologies, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/tools/build/scons/scripts/single_defs.py#1 $
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
#
#===============================================================================
#import sys
#import os

# Assembly compile flags (note first pass is through armcc using -E option
# then passed to armas, see build rule below
asm_dflags = ''

# standard MODEM compile flags
single_dflags = '-DAEE_STATIC'
   
#------------------------------------------------------------------------------
# Hooks for Scons
#------------------------------------------------------------------------------
def exists(env):
    '''
       exists
    '''
    return env.Detect('modemtools_defs')

def generate(env):
    '''
       generate
    '''
    # Assembly common flags
    env.Replace(ASM_DFLAGS = asm_dflags)
   
    # CC (apps) common compile flags
    env.Replace(CC_DFLAGS = single_dflags)
   
    if 'BUILD_TOOL_CHAIN' not in env:
        env.Append(ASM_DFLAGS = ' -DQC_MODIFIED -Dinline=__inline')
        env.Append(CC_DFLAGS = \
            ' -DASSERT=ASSERT_FATAL -DQC_MODIFIED -Dinline=__inline')

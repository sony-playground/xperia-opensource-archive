#===============================================================================
#
# Crypto Driver Chipset Library
#
# GENERAL DESCRIPTION
#    build script
#
# Copyright (c) 2021 by QUALCOMM, Incorporated.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
#
#-------------------------------------------------------------------------------
#
#  $Header: //components/rel/aop.ho/5.0/aop_proc/core/securemsm/cryptodrivers/prng/chipset/build/kailua.SConscript#1 $
#  $DateTime: 2021/11/15 13:45:01 $
#  $Author: pwbldsvc $
#  $Change: 33995916 $
#                      EDIT HISTORY FOR FILE
#
#  This section contains comments describing changes made to the module.
#  Notice that changes are listed in reverse chronological order.
#
# when       who     what, where, why
# --------   ---     ---------------------------------------------------------
# 07/29/21    nk     Initial version
#
#===============================================================================
import os
Import('env')
env = env.Clone()

# kailua interface redirection
CHIPSETREDIRECTION = 'kailua'

script_sconfname = None
if os.path.exists('../' + CHIPSETREDIRECTION + '/build/SConscript') :
   script_sconfname = '../' + CHIPSETREDIRECTION + '/build/SConscript'
else :
   print "Directory: [%s] doesnot exist"%script_sconfname
   raise RuntimeError, "kailua  [%s] does not exist"%script_sconfname

#-------------------------------------------------------------------------------
# Load sub scripts
#-------------------------------------------------------------------------------
script_scon = None
script_scon = '../' + CHIPSETREDIRECTION + '/build'

env.SConscript(dirs=[script_scon], exports='env')

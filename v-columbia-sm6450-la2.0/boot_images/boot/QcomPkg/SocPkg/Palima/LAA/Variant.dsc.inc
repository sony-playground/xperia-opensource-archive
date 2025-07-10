#==============================================================================
# @file Variant.dscinc
# Palima LAA Variant Libraries
#
# Copyright (c) 2017, 2020 Qualcomm Technologies, Inc. All rights reserved.
# Portions Copyright (c) 2009 - 2010, Apple Inc. All rights reserved.
# This program and the acompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#==============================================================================

[BuildOptions]
  GCC:*_*_*_CC_FLAGS = -DBLOCKDEV_ENABLED

[LibraryClasses.common]
 DDRTargetLib|QcomPkg/SocPkg/Palima/Library/DDRTargetLib/DDRTargetLib.inf
 DSFTargetLib|QcomPkg/SocPkg/Palima/Library/DSFTargetLib/DSFTargetLib.inf
 DDITargetLib|QcomPkg/SocPkg/Palima/Library/DDITargetLib/DDITargetLib.inf
 DDRSdiLib|QcomPkg/SocPkg/Palima/Library/DDRTargetLib/DDRSdiLib.inf
 DDRFwLib|QcomPkg/SocPkg/Palima/Library/DSFTargetLib/DDRFwLib.inf
 DDRFwSdiLib|QcomPkg/SocPkg/Palima/Library/DSFTargetLib/DDRFwSdiLib.inf
 

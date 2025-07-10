#==============================================================================
# @file Core.dsc
# Palima Core package.
#
# Copyright (c) 2019 Qualcomm Technologies, Inc. All rights reserved.
# Portions Copyright (c) 2009 - 2010, Apple Inc. All rights reserved.
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = PalimaPkg
  PLATFORM_GUID                  = 74ED6F00-C570-4D61-8952-0EE3863CFE1B
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = QcomPkg/SocPkg/Palima/LAA/Core.fdf

[Defines.ARM]
  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Palima$(VAR)/Core_32

[Defines.AARCH64]
  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Palima$(VAR)/Core

!include QcomPkg/SocPkg/Palima/Common/Core.dsc.inc

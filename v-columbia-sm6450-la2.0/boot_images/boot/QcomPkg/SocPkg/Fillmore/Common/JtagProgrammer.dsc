#==============================================================================
# @file JtagProgrammer.dsc
# Fillmore JtagProgrammer
#
# Copyright (c) 2017-2021 Qualcomm Technologies, Inc. All rights reserved.
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = FillmorePkg
  PLATFORM_GUID                  = AA99686E-4D75-3829-5220-F4874BA2F216
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Fillmore$(VAR)/JtagProgrammer

!include QcomPkg/SocPkg/Fillmore/Common/TargetCommon.dsc.inc

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  QcomPkg/Library/JtagProgrammerLib/JtagProgrammer.inf {
      <LibraryClasses>
      ClockTargetLib|QcomPkg/SocPkg/Fillmore/Library/ClockTargetLib/ClockTargetLib.inf
	    ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
#    PmicLoaderLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLoaderLibNull.inf
#	  PmicLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLibNull.inf
      PmicLib|QcomPkg/SocPkg/Fillmore/Library/PmicLib/PmicLib.inf
      PmicLoaderLib|QcomPkg/SocPkg/Fillmore/Library/PmicLib/loader/PmicLoaderNoChgrLib.inf
       SdccTargetLib|QcomPkg/SocPkg/Fillmore/Library/SdccTargetLib/SdccJtagTargetLib.inf
       SPILib|QcomPkg/Library/NullLibs/SPILibNull/SPILibNull.inf
       StorageProfileLib|QcomPkg/Library/StorageCommonLib/StorageProfileStub.inf
      
      <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.PcdBuildType|0x4
   }

[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DFEATURE_DISABLE_DT_LOGGING 


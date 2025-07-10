#==============================================================================
# @file JtagProgrammer.dsc
# Clarence JtagProgrammer
#
# Copyright (c) 2017-2022 Qualcomm Technologies, Inc. All rights reserved.
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = ClarencePkg
  PLATFORM_GUID                  = AA99686E-4D75-3829-5220-F4874BA2F216
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Clarence$(VAR)/JtagProgrammer

!include QcomPkg/SocPkg/Clarence/Common/TargetCommon.dsc.inc

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  QcomPkg/Library/JtagProgrammerLib/JtagProgrammer.inf {
      <LibraryClasses>
      ClockTargetLib|QcomPkg/SocPkg/Clarence/Library/ClockTargetLib/ClockTargetLib.inf
	    ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
	    PmicLib|QcomPkg/SocPkg/Clarence/Library/PmicLib/PmicLib.inf
        PmicLoaderLib|QcomPkg/SocPkg/Clarence/Library/PmicLib/loader/PmicLoaderNoChgrLib.inf
		SdccTargetLib|QcomPkg/SocPkg/Clarence/Library/SdccTargetLib/SdccJtagTargetLib.inf
	    SPILib|QcomPkg/Library/NullLibs/SPILibNull/SPILibNull.inf
	    StorageProfileLib|QcomPkg/Library/StorageCommonLib/StorageProfileStub.inf

	  <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.PcdBuildType|0x4
   }

[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DFEATURE_DISABLE_DT_LOGGING

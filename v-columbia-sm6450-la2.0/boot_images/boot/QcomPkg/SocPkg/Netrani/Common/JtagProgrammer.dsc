#==============================================================================
# @file JtagProgrammer.dsc
# Netrani JtagProgrammer
#
# Copyright (c) 2017-2021, 2023 Qualcomm Technologies, Inc. All rights reserved.
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = NetraniPkg
  PLATFORM_GUID                  = AA99686E-4D75-3829-5220-F4874BA2F216
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Netrani$(VAR)/JtagProgrammer

!include QcomPkg/SocPkg/Netrani/Common/TargetCommon.dsc.inc

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  QcomPkg/Library/JtagProgrammerLib/JtagProgrammer.inf {
      <LibraryClasses>
      ClockTargetLib|QcomPkg/SocPkg/Netrani/Library/ClockTargetLib/ClockTargetLib.inf
      ChipInfoTargetLib|QcomPkg/Library/NullLibs/ChipInfoTargetLibNull/ChipInfoTargetLibNull.inf
	    ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
			PmicLib|QcomPkg/SocPkg/Netrani/Library/PmicLib/PmicLib.inf
            #PmicLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLibNull.inf
            PmicLoaderLib|QcomPkg/SocPkg/Netrani/Library/PmicLib/loader/PmicLoaderNoChgrLib.inf
            #PmicLoaderLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLoaderLibNull.inf
		SdccTargetLib|QcomPkg/SocPkg/Netrani/Library/SdccTargetLib/SdccJtagTargetLib.inf
	    SPILib|QcomPkg/Library/NullLibs/SPILibNull/SPILibNull.inf
	    StorageProfileLib|QcomPkg/Library/StorageCommonLib/StorageProfileStub.inf

	  <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.PcdBuildType|0x4
   }

[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DFEATURE_DISABLE_DT_LOGGING

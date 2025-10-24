#==============================================================================
# @file JtagProgrammer.dsc
# Kailua JtagProgrammer
#
# Copyright (c) 2017-2022 Qualcomm Technologies, Inc. All rights reserved.
#==============================================================================

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = KailuaPkg
  PLATFORM_GUID                  = AA99686E-4D75-3829-5220-F4874BA2F216
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Kailua$(VAR)/JtagProgrammer

!include QcomPkg/SocPkg/Kailua/Common/TargetCommon.dsc.inc

################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  QcomPkg/Library/JtagProgrammerLib/JtagProgrammer.inf {
      <LibraryClasses>
      ChipInfoImageLib|QcomPkg/Library/ChipInfoLib/ChipInfoLoader.inf
      #ClockTargetLib|QcomPkg/SocPkg/Kailua/Library/ClockTargetLib/ClockTargetLib.inf
      ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
      #PmicLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/PmicLib.inf
      #PmicLoaderLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/loader/PmicLoaderNoChgrLib.inf
      PmicLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLibNull.inf
      PmicLoaderLib|QcomPkg//Library/NullLibs/PmicLibNull/PmicLoaderLibNull.inf
      SPILib|QcomPkg/Library/NullLibs/SPILibNull/SPILibNull.inf
	  SdccTargetLib|QcomPkg/SocPkg/Kailua/Library/SdccTargetLib/SdccJtagTargetLib.inf
      StorageProfileLib|QcomPkg/Library/StorageCommonLib/StorageProfileStub.inf
      UCLib|SecPkg/Library/UCLib_ramdump/UCLib_ramdump.inf
	  UsbSharedLib|QcomPkg/SocPkg/Kailua/Library/UsbSharedLib/UsbSharedLibCore.inf
      #UsbSharedLib|QcomPkg/Library/NullLibs/UsbSharedLibNull/UsbSharedLibLoaderNull.inf

	  <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.PcdBuildType|0x4
   }

[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DFEATURE_DISABLE_DT_LOGGING


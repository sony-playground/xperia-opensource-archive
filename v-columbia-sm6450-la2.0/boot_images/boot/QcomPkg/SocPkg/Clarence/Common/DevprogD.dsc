#==============================================================================
# @file DevprogD.dsc
# Clarence Device Programmer
#
# Copyright (c) 2017-2022, 2023 Qualcomm Technologies, Inc. All rights reserved.
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

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Clarence$(VAR)/DevprogD

!include QcomPkg/SocPkg/Clarence/Common/TargetCommon.dsc.inc
[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DBOOT_RAMDUMP_ENABLE
################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
  QcomPkg/DevPrg/DevPrgD.inf {
     <LibraryClasses>
      BootMemMapLib|QcomPkg/SocPkg/Library/BootMemMapLib/RamdumpMemMapLib.inf
      XBLLoaderArchLib|QcomPkg/SocPkg/Library/XBLLoaderArchLib/XBLLoaderArchNonSecureLib.inf
      ConfigContextLib|QcomPkg/LoaderFramework/ConfigContext/ConfigContext.inf
      ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
      ExtDriversNonSecureLib|QcomPkg/XBLLoader/ExtDrivers/ExtDriversNonSecure.inf
      LoggerLib|QcomPkg/LoaderFramework/Logger/Logger.inf
      PmicLib|QcomPkg/SocPkg/Clarence/Library/PmicLib/PmicLib.inf
      PmicLoaderLib|QcomPkg/SocPkg/Clarence/Library/PmicLib/loader/PmicDevprgLib.inf
      QusbLdrLib|QcomPkg/SocPkg/Clarence/Library/QusbLdrLib/QusbLdrLib.inf
      HashLib|QcomPkg/Library/HashLib_loader/HashLibHw_loader.inf
      UCLib|SecPkg/Library/UCLib_devprog/UCLib_devprog.inf
	  CryptoLib|QcomPkg/Library/CryptoLib/CryptoLib.inf
      RamdumpheapLib|QcomPkg/Library/HeapLib/ramdumpheap.inf
      ErrorHandlerLib|QcomPkg/Library/ErrorHandlerLib/ErrorHandlerEl1Lib.inf
      CpuInitLib|QcomPkg/SocPkg/Library/CpuInitLib/EL1CpuInitLib.inf
      VectorTable|QcomPkg/SocPkg/Library/VectorTable/VectorTableEL1.inf
      XBLConfigLib|QcomPkg/XBLLoader/XBLConfig/XBLConfigLib.inf
      LoggerUartLib|QcomPkg/XBLLoader/LoggerUart/LoggerUart.inf
      DevPrgLib|QcomPkg/Library/DevPrgLib/DevPrgLib.inf
      DevPrgBuffersDDRLib|QcomPkg/Library/DevPrgLib/DevPrgBuffersDDRLib.inf
      PCIeInitLib|QcomPkg/SocPkg/Library/PCIeInitLib/PCIeInitLib.inf
      ChipInfoTargetLib|QcomPkg/Library/NullLibs/ChipInfoTargetLibNull/ChipInfoTargetLibNull.inf

      <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.SDCCDmaEnabled|TRUE
        gQcomTokenSpaceGuid.SDCCSdhciEnable|TRUE
	    # SDCCEmmcSpeedMode = 3 to indicate HS mode for SD card
        gQcomTokenSpaceGuid.SDCCEmmcSpeedMode|3
   }

[BuildOptions]
  GCC:*_*_AARCH64_ARCHCC_FLAGS  = -DFEATURE_DEVICEPROGRAMMER_IMAGE
  GCC:*_*_AARCH64_ARCHPP_FLAGS  = -DFEATURE_DEVICEPROGRAMMER_IMAGE


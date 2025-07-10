#==============================================================================
# @file Loader.dsc
# Clarence Loader package.
#
# Copyright (c) 2017 - 2022, 2023 Qualcomm Technologies, Inc. All rights reserved.
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

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Clarence$(VAR)/RamDump

!include QcomPkg/SocPkg/Clarence/Common/TargetCommon.dsc.inc
[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DBOOT_PBL_H=\"pbl_sbl_shared.h\" -DBOOT_RAMDUMP_ENABLE 
################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
#
# SEC
#
  QcomPkg/XBLRamDump/XBLRamDump.inf {
    <LibraryClasses>
      BootMemMapLib|QcomPkg/SocPkg/Library/BootMemMapLib/RamdumpMemMapLib.inf
      XBLRamDumpLib|QcomPkg/SocPkg/Library/XBLRamDumpLib/XBLRamDumpLib.inf
      XBLLoaderArchLib|QcomPkg/SocPkg/Library/XBLLoaderArchLib/XBLLoaderArchNonSecureLib.inf
      IpaTargetLib|QcomPkg/Library/NullLibs/IpaTargetLibNull/IpaTargetLibNull.inf
      SdccCommonLib|QcomPkg/Library/SdccCommonLib/SdccCommonRamdumpLib.inf
      SdccTargetLib|QcomPkg/SocPkg/Clarence/Library/SdccTargetLib/SdccRamDumpTargetLib.inf
      ClockTargetLib|QcomPkg/SocPkg/Clarence/Library/ClockTargetLib/ClockRamDumpLib.inf
      ChipInfoLoaderLib|QcomPkg/Library/ChipInfoLib/ChipInfoRamdump.inf
      ConfigContextLib|QcomPkg/LoaderFramework/ConfigContext/ConfigContext.inf
      ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
      TlmmLib|QcomPkg/Library/TlmmLib/TlmmLib.inf
      IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
      DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
      ClockTargetLib|QcomPkg/SocPkg/Clarence/Library/ClockTargetLib/ClockRamDumpLib.inf
      PlatformInfoLoaderLib|QcomPkg/Library/PlatformInfoLib/PlatformInfoRamDump.inf

      DisplayLib|QcomPkg/Library/DisplayLib/DisplayLib.inf
      DevPrgDLib|QcomPkg/Library/NullLibs/DevPrgDLibNull/DevPrgDLibNull.inf
      DevPrgLLib|QcomPkg/Library/NullLibs/DevPrgLLibNull/DevPrgLLibNull.inf
      HALDSILib|QcomPkg/Library/HALDSILib/HALDSILib.inf
      HALDPLibStub|QcomPkg/Library/HALDPLib/HALDPLibStub.inf
      ExternalDisplayLib|QcomPkg/Library/ExternalDisplayLib/ExternalDisplayLibStub.inf
      ExtDriversNonSecureLib|QcomPkg/XBLLoader/ExtDrivers/ExtDriversNonSecure.inf
      HALMDSSLib|QcomPkg/Library/HALMDSSLib/HALMDSS86x.inf
      LoggerLib|QcomPkg/LoaderFramework/Logger/Logger.inf
      MDPLibBoot|QcomPkg/Library/MDPLib/MDPLibBoot.inf
      MDPPlatformLibBoot|QcomPkg/SocPkg/Clarence/Library/MDPPlatformLibBoot/MDPPlatformLibBoot.inf
      PmicLib|QcomPkg/SocPkg/Clarence/Library/PmicLib/PmicLib.inf
      PmicLoaderLib|QcomPkg/SocPkg/Clarence/Library/PmicLib/loader/PmicRamDump.inf
      PmicPsiLib|QcomPkg/SocPkg/Clarence/Library/PmicLib/loader/PmicPsiLib.inf
      QusbLdrLib|QcomPkg/SocPkg/Clarence/Library/QusbLdrLib/QusbLdrLib.inf
      RamInit|QcomPkg/XBLLoader/RamInit/RamInit.inf
      RNGLib|QcomPkg/SocPkg/Library/RNGLoaderLib/RNGLibHw.inf
      UCLib|SecPkg/Library/UCLib_ramdump/UCLib_ramdump.inf
      HashLib|QcomPkg/Library/HashLib_loader/HashLibHw_loader.inf 
      CryptoLib|QcomPkg/Library/CryptoLib/CryptoLib.inf
      RamdumpheapLib|QcomPkg/Library/HeapLib/ramdumpheap.inf
      I2CLib|QcomPkg/Library/I2CLib/I2CLibLoader.inf
      SPILib|QcomPkg/Library/SPILib/SPILibLoader.inf	  

      PCIeInitLib|QcomPkg/SocPkg/Library/PCIeInitLib/PCIeInitLib.inf
      HfatDevLib|QcomPkg/XBLLoader/HfatDev/HfatDev.inf
      SaharaDispatchTableLib|QcomPkg/XBLLoader/SaharaDispatchTable/SaharaDispatchTable.inf
      SaharaCommandHandlerLib|QcomPkg/XBLLoader/SaharaCommandHandler/SaharaCommandHandler.inf
      MinidumpLib|QcomPkg/Library/MinidumpLib/MinidumpLib.inf
      RamdumpTableLib|QcomPkg/XBLLoader/RamdumpTable/RamdumpTable.inf
      RamdumpTableTarget|QcomPkg/SocPkg/Library/RamdumpTableTargetLib/RamdumpTableSM.inf
      CryptoRDILib|QcomPkg/Library/CryptoInterfaceLib/CryptoRDILib.inf

      ErrorHandlerLib|QcomPkg/Library/ErrorHandlerLib/ErrorHandlerEl1Lib.inf
      CpuInitLib|QcomPkg/SocPkg/Library/CpuInitLib/EL1CpuInitLib.inf
      VectorTable|QcomPkg/SocPkg/Library/VectorTable/VectorTableEL1.inf
      XBLConfigLib|QcomPkg/XBLLoader/XBLConfig/XBLConfigLib.inf
      LoggerUartLib|QcomPkg/XBLLoader/LoggerUart/LoggerUart.inf
      <PcdsFixedAtBuild>
        gQcomTokenSpaceGuid.SDCCDmaEnabled|TRUE
        gQcomTokenSpaceGuid.SDCCSdhciEnable|TRUE
        gQcomTokenSpaceGuid.SDCCEmmcSpeedMode|0
  }


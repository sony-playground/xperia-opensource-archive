#==============================================================================
# @file Loader.dsc
# Kailua Loader package.
#
# Copyright (c) 2017 - 2022 Qualcomm Technologies, Inc. All rights reserved.
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

  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Kailua$(VAR)/RamDump

!include QcomPkg/SocPkg/Kailua/Common/TargetCommon.dsc.inc
[BuildOptions]
   GCC:*_*_*_CC_FLAGS = -DBOOT_RAMDUMP_ENABLE -DENABLE_LOGS_TO_MEDIA
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
      ChipInfoImageLib|QcomPkg/Library/ChipInfoLib/ChipInfoLoader.inf
      ChipInfoSKULib|QcomPkg/Library/NullLibs/ChipInfoSKULibNull/ChipInfoSKULibNull.inf
      ConfigContextLib|QcomPkg/LoaderFramework/ConfigContext/ConfigContext.inf
      ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
      TlmmLib|QcomPkg/Library/TlmmLib/TlmmLib.inf
      IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
      DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
      ClockTargetLib|QcomPkg/SocPkg/Kailua/Library/ClockTargetLib/ClockRamDumpLib.inf
      WhitelistLib|QcomPkg/XBLLoader/WhitelistLib/WhitelistLib.inf

      DisplayLib|QcomPkg/Library/DisplayLib/DisplayLib.inf
      DevPrgDLib|QcomPkg/Library/NullLibs/DevPrgDLibNull/DevPrgDLibNull.inf
      DevPrgLLib|QcomPkg/Library/NullLibs/DevPrgLLibNull/DevPrgLLibNull.inf
      HALDSILib|QcomPkg/Library/HALDSILib/HALDSIMDSS9xxLib.inf
      HALDPLibStub|QcomPkg/Library/HALDPLib/HALDPLibStub.inf
      ExternalDisplayLib|QcomPkg/Library/ExternalDisplayLib/ExternalDisplayLibStub.inf
      ExtDriversNonSecureLib|QcomPkg/XBLLoader/ExtDrivers/ExtDriversNonSecure.inf
      HALMDSSLib|QcomPkg/Library/HALMDSSLib/HALMDSS9xx.inf
      LoggerLib|QcomPkg/LoaderFramework/Logger/Logger.inf
      MDPLibBoot|QcomPkg/Library/MDPLib/MDPLibBoot.inf
      MDPPlatformLibBoot|QcomPkg/SocPkg/Kailua/Library/MDPPlatformLibBoot/MDPPlatformLibBoot.inf
      DTBExtnLib|QcomPkg/Library/DTBExtnLib/DTBExtnLib.inf

      PlatformInfoLoaderLib|QcomPkg/Library/PlatformInfoLib/PlatformInfoRamDump.inf

      CPRTargetLib|QcomPkg/Library/NullLibs/PowerLibNull/CprLibNull.inf
      RailwayTargetLib|QcomPkg/Library/NullLibs/RailwayLibNull/RailwayLibNull.inf

      PmicLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/PmicLib.inf
      PmicLoaderLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/loader/PmicRamDump.inf
      PmicPsiLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/loader/PmicPsiLib.inf
      #PmicLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLibNull.inf
      #PmicLoaderLib|QcomPkg//Library/NullLibs/PmicLibNull/PmicLoaderLibNull.inf

      QusbLdrLib|QcomPkg/SocPkg/Kailua/Library/QusbLdrLib/QusbLdrLib.inf
      #QusbLdrLib|QcomPkg/Library/NullLibs/QusbLdrLibNull/QusbLdrLibNull.inf
      QusbTargetLib|QcomPkg/SocPkg/Kailua/Library/QusbTargetLib/QusbTargetLib.inf
      #QusbTargetLib|QcomPkg/Library/NullLibs/QusbTargetLibNull/QusbTargetLibNull.inf
      QusbDciCommonLib|QcomPkg/SocPkg/Kailua/Library/QusbDciCommonLib/QusbDciCommonLib.inf
      #QusbDciCommonLib|QcomPkg/Library/NullLibs/QusbDciCommonLibNull/QusbDciCommonLibNull.inf

      UsbSharedLib|QcomPkg/SocPkg/Kailua/Library/UsbSharedLib/UsbSharedLibRamdump.inf
      #UsbSharedLib|QcomPkg/Library/NullLibs/UsbSharedLibNull/UsbSharedLibLoaderNull.inf
      PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
      UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
      UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
      DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
      UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
      #I2CApiLib|QcomPkg/Library/I2CApiLib/I2CApiLib.inf
      I2CLib|QcomPkg/Library/I2CLib/I2CLibLoader.inf
      I2CFWImageLib|QcomPkg/SocPkg/Kailua/Settings/I2C/I2CFWImageLib.inf


      RamInit|QcomPkg/XBLLoader/RamInit/RamInit.inf
      UCLib|SecPkg/Library/UCLib_ramdump/UCLib_ramdump.inf
      HashLib|QcomPkg/Library/HashLib_loader/HashLibHw_loader.inf
      RamdumpheapLib|QcomPkg/Library/HeapLib/ramdumpheap.inf
      I2CLib|QcomPkg/Library/I2CLib/I2CLibLoader.inf
      PCIeInitLib|QcomPkg/SocPkg/Library/PCIeInitLib/PCIeInitLib.inf
      HfatDevLib|QcomPkg/XBLLoader/HfatDev/HfatDev.inf
      SaharaDispatchTableLib|QcomPkg/XBLLoader/SaharaDispatchTable/SaharaDispatchTable.inf
      SaharaCommandHandlerLib|QcomPkg/XBLLoader/SaharaCommandHandler/SaharaCommandHandler.inf
      MinidumpLib|QcomPkg/Library/MinidumpLib/MinidumpLibLoader.inf
      RamdumpTableLib|QcomPkg/XBLLoader/RamdumpTable/RamdumpTable.inf
      RamdumpTableTarget|QcomPkg/SocPkg/Library/RamdumpTableTargetLib/RamdumpTableSM.inf
      BlacklistLib|QcomPkg/XBLLoader/BlacklistLib/BlacklistLib.inf

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


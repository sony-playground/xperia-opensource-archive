#==============================================================================
# @file Core.dsc
# Kailua Core package.
#
# Copyright (c) 2015 - 2018, 2019 - 2022 Qualcomm Technologies, Inc. All rights reserved.
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

[LibraryClasses.common]
  #
  # EDK2 Libraries
  #
  !include MdePkg/MdeLibs.dsc.inc
  NULL|ArmPkg/Library/CompilerIntrinsicsLib/CompilerIntrinsicsLib.inf
  NULL|QcomPkg/Library/QcomBaseLib/QcomBaseLib.inf
  NULL|QcomPkg/Library/StackCanaryBaseLib/StackCanaryBaseLibCore.inf
  NULL|QcomPkg/Library/MuslLib/MuslLib.inf


  ArmDisassemblerLib|ArmPkg/Library/ArmDisassemblerLib/ArmDisassemblerLib.inf
  ArmGenericTimerCounterLib|ArmPkg/Library/ArmGenericTimerVirtCounterLib/ArmGenericTimerVirtCounterLib.inf
  ArmGicArchLib|ArmPkg/Library/ArmGicArchLib/ArmGicArchLib.inf
  ArmGicLib|ArmPkg/Drivers/ArmGic/ArmGicLib.inf
# --PRESIL--
  ArmMmuLib|ArmPkg/Library/ArmMmuLib/ArmMmuBaseLib.inf
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|MdePkg/Library/BaseMemoryLibOptDxe/BaseMemoryLibOptDxe.inf
  #BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  BaseSynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  SynchronizationLib|MdePkg/Library/BaseSynchronizationLib/BaseSynchronizationLib.inf
  CacheMaintenanceLib|ArmPkg/Library/ArmCacheMaintenanceLib/ArmCacheMaintenanceLib.inf
  ChipInfoImageLib|QcomPkg/Library/ChipInfoLib/ChipInfoCore.inf
  CpuExceptionHandlerLib|ArmPkg/Library/ArmExceptionLib/ArmRelocateExceptionLib.inf
  CpuLib|MdePkg/Library/BaseCpuLib/BaseCpuLib.inf
  DebugAgentLib|MdeModulePkg/Library/DebugAgentLibNull/DebugAgentLibNull.inf
  DebugLib|QcomPkg/Library/DebugLib/DebugLib.inf
  DefaultExceptionHandlerLib|ArmPkg/Library/DefaultExceptionHandlerLib/DefaultExceptionHandlerLib.inf
  DevicePathLib|MdePkg/Library/UefiDevicePathLib/UefiDevicePathLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  DxeServicesTableLib|MdePkg/Library/DxeServicesTableLib/DxeServicesTableLib.inf
  ReportStatusCodeLib|MdeModulePkg/Library/DxeReportStatusCodeLib/DxeReportStatusCodeLib.inf
  DebugPrintErrorLevelLib|MdePkg/Library/BaseDebugPrintErrorLevelLib/BaseDebugPrintErrorLevelLib.inf
  DTBExtnLib|QcomPkg/Library/DTBExtnUEFILib/DTBExtnUEFILib.inf
  EblAddExternalCommandLib|EmbeddedPkg/Library/EblAddExternalCommandLib/EblAddExternalCommandLib.inf
  EblNetworkLib|EmbeddedPkg/Library/EblNetworkLib/EblNetworkLib.inf
  EfiFileLib|EmbeddedPkg/Library/EfiFileLib/EfiFileLib.inf
  FdtLib|EmbeddedPkg/Library/FdtLib/FdtLib.inf
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  LzmaDecompressLib|MdeModulePkg/Library/LzmaCustomDecompressLib/LzmaCustomDecompressLib.inf
  ZlibDecompressLib|QcomPkg/Library/ZlibDecompressLib/ZlibDecompressLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  PeCoffGetEntryPointLib|MdePkg/Library/BasePeCoffGetEntryPointLib/BasePeCoffGetEntryPointLib.inf
  PerformanceLib|MdePkg/Library/BasePerformanceLibNull/BasePerformanceLibNull.inf
  PowerSleepTargetLib|QcomPkg/SocPkg/Kailua/Library/PowerSleepTargetLib/PowerSleepTargetLib.inf
  PrePiLib|EmbeddedPkg/Library/PrePiLib/PrePiLib.inf
  SecurityManagementLib|MdeModulePkg/Library/DxeSecurityManagementLib/DxeSecurityManagementLib.inf
  SortLib|MdeModulePkg/Library/UefiSortLib/UefiSortLib.inf
  TimeBaseLib|EmbeddedPkg/Library/TimeBaseLib/TimeBaseLib.inf
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf
  UefiDriverEntryPoint|MdePkg/Library/UefiDriverEntryPoint/UefiDriverEntryPoint.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  UefiRuntimeLib|MdePkg/Library/UefiRuntimeLib/UefiRuntimeLib.inf
  UefiUsbLib|MdePkg/Library/UefiUsbLib/UefiUsbLib.inf
  UefiRuntimeServicesTableLib|MdePkg/Library/UefiRuntimeServicesTableLib/UefiRuntimeServicesTableLib.inf
  UncachedMemoryAllocationLib|QcomPkg/Library/UncachedMemoryAllocationLib/UncachedMemoryAllocationLib.inf
  UsbSharedLib|QcomPkg/SocPkg/Kailua/Library/UsbSharedLib/UsbSharedLibCore.inf
  UsbConfigLib|QcomPkg/SocPkg/Kailua/Library/UsbConfigLib/UsbConfigLib.inf
  LockBoxLib|MdeModulePkg/Library/LockBoxNullLib/LockBoxNullLib.inf
  UefiBootManagerLib|MdeModulePkg/Library/UefiBootManagerLib/UefiBootManagerLib.inf
  IPCCLib|QcomPkg/Library/IPCCLib/IPCCLib.inf
  KernelLib|QcomPkg/Library/KernelLib/KernelLib.inf
# --SINGLE_THREAD--
#  LockLib|QcomPkg/Library/LockLib/LockLibNull.inf
  LockLib|QcomPkg/Library/LockLib/LockLib.inf
# --SINGLE_THREAD--
#  WatchDogLib|QcomPkg/SocPkg/Library/WatchDogLib/WatchDogLib.inf
  WatchDogLib|QcomPkg/Library/KernelLib/KernWDogLib.inf
  AslrLib|QcomPkg/Library/AslrLib/AslrLib.inf
  DbiDumpLib|QcomPkg/Library/DbiDumpLib/DbiDumpLib.inf
  MuslLib|QcomPkg/Library/MuslLib/MuslLib.inf
  UefiCfgLib|QcomPkg/Library/UefiConfigLib/UefiCfgLib.inf
  ShLib|QcomPkg/Library/ShLib/ShLib.inf
  RamPartitionTableLib|QcomPkg/Library/RamPartitionTableLib/RamPartitionTableLib.inf
  DDRInfoPartitionLib|QcomPkg/Library/DDRInfoPartitionLib/DDRInfoPartitionLib.inf
  PeCoffExtraActionLib|QcomPkg/Library/DebugPeCoffExtraActionLib/DebugPeCoffExtraActionLib.inf
  CookieLib|QcomPkg/Library/CookieLib/CookieLib.inf
  SDILib|QcomPkg/Library/SDILib/SDILib.inf

  UefiFeatureEnablerLoaderLib|QcomPkg/Library/UefiFeatureEnablerLoaderLib/UefiFeatureEnablerLoaderLib.inf
  AptLib|QcomPkg/Library/NullLibs/AptLibNull/AptLibNull.inf
# --PRESIL--
# BootConfigLib|QcomPkg/Library/NullLibs/BootConfigLibNull/BootConfigLibNull.inf
  BootConfigLib|QcomPkg/Library/BootConfigLib/BootConfigLib.inf
  BdsInputLib|QcomPkg/Library/BdsInputLib/BdsInputLib.inf
  BusyWaitLib|QcomPkg/Library/BusyWaitLib/BusyWaitCoreLib.inf
  ChargerLib|QcomPkg/SocPkg/Kailua/Library/ChargerLib/ChargerLibLa.inf
  UsbPwrCtrlLib|QcomPkg/Library/UsbPwrCtrlLib/UsbPwrCtrlLib.inf
  ChipInfoDalFwkLib|QcomPkg/Library/ChipInfoLib/ChipInfoDalFwk.inf
  ChipInfoCommonLib|QcomPkg/Library/ChipInfoLib/ChipInfoCommon.inf
  ChipInfoCoreLib|QcomPkg/Library/ChipInfoLib/ChipInfoCore.inf
  DDRTargetLib|QcomPkg/Library/NullLibs/DDRTargetLibNull/DDRTargetLibNull.inf
  EblCmdLib|QcomPkg/Library/EblCmdLib/EblCmdLib.inf
# ChargerPdLib|QcomPkg/Library/ChargerPdLib/ChargerPdLib.inf
  ChargerPdLib|QcomPkg/Library/NullLibs/ChargerPdLibNull/ChargerPdLibNull.inf
# --PRESIL--
# EfiResetSystemLib|QcomPkg/Library/ResetSystemLib/Null/ResetSystemLib.inf
  EfiResetSystemLib|QcomPkg/Library/ResetSystemLib/LA/ResetSystemLib.inf
  FuseControlLib|QcomPkg/Library/FuseControlLib/FuseControlLib.inf
  FwCommonLib|QcomPkg/Library/NullLibs/FwCommonLibNull/FwCommonLibNull.inf
  FwProvisionLib|QcomPkg/Library/NullLibs/FwCommonLibNull/FwCommonLibNull.inf
  FwUpdateLib|QcomPkg/Library/NullLibs/FwCommonLibNull/FwCommonLibNull.inf
  GuidedFvLib|QcomPkg/Library/GuidedFvLib/GuidedFvLib.inf
  HALclkSharedLib|QcomPkg/Library/HALclkSharedLib/HALclkSharedLibUEFI.inf
  VcsSharedLib|QcomPkg/Library/VcsSharedLib/VcsSharedLib.inf
  HFATLib|QcomPkg/Library/HFATLib/HFATLib.inf
  ColdplugLib|QcomPkg/Library/ColdplugLib/ColdplugLib.inf
  IcbCfgLib|QcomPkg/Library/NullLibs/BusesLibNull/IcbCfgLibNull.inf
  ImageVersionLib|QcomPkg/Library/ImageVersionLib/ImageVersionLib.inf
  ImagePathUtilsLib|QcomPkg/Library/ImagePathUtilsLib/ImagePathUtilsLib.inf
  IORTLib|QcomPkg/Library/IORTLib/IORTLib.inf
  ParserLib|QcomPkg/Library/ParserLib/ParserLib.inf
  PeHashLib|QcomPkg/Library/PeHashLib/PeHashLib.inf
  PlatformInfoCoreLib|QcomPkg/Library/PlatformInfoLib/PlatformInfoCore.inf
  #PrintLib|QcomPkg/Library/PrintShLib/PrintShLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
  QcomBaseLib|QcomPkg/Library/QcomBaseLib/QcomBaseLib.inf
  QcomLib|QcomPkg/Library/QcomLib/QcomLib.inf
  MountFvLib|QcomPkg/Library/MountFvLib/MountFvLib.inf
  FvParserLib|QcomPkg/Library/FvParserLib/FvParserLib.inf
  FvDecompressLib|QcomPkg/Library/FvDecompressLib/FvDecompressLib.inf
  BMPLib|QcomPkg/Library/BMPLib/BMPLib.inf
  QcomUtilsLib|QcomPkg/Library/QcomUtilsLib/QcomUtilsLib.inf
  QusbLib|QcomPkg/Library/QusbLib/QusbLib.inf
  RFSLib|QcomPkg/Library/RFSLib/RFSLib.inf
  ROMFSLib|QcomPkg/Library/EfsLib/ROMFSLib.inf
  RandomStackCanaryLib|QcomPkg/Library/RandomStackCanaryLib/RandomStackCanaryLib.inf
#  RandomStackCanaryLib|QcomPkg/Library/NullLibs/RandomStackCanaryLibNull/RandomStackCanaryLibNull.inf
  RealTimeClockLib|QcomPkg/Library/RealTimeClockLibLegacy/RealTimeClockLib.inf
  RpmbLib|QcomPkg/Library/RpmbLib/RpmbLib.inf
  RpmbListenerLib|QcomPkg/Library/RpmbLib/RpmbListenerLib.inf
  ScmCmdLib|QcomPkg/Library/ScmCmdLib/ScmCmdLib.inf
  SdccCommonLib|QcomPkg/Library/SdccCommonLib/SdccCommonLib.inf
  SdccHalLib|QcomPkg/Library/SdccCommonLib/SdccHalLib/SdccHalLib.inf
  SecBootBaseLib|QcomPkg/Library/SecBootBaseLib/SecBootBaseLib.inf
  SecBootLib|QcomPkg/Library/SecBootLib/SecBootLib.inf
  SecBootSigLib|QcomPkg/Library/SecBootSigLib/SecBootSigLib.inf
  SecHwTestLib|QcomPkg/Library/SecHwTestLib/SecHwTestLib.inf
  SerialPortLib|QcomPkg/Library/SerialPortLib/SerialPortShLib.inf
  ICBArbLib|QcomPkg/Library/ICBArbLib/ICBArbLib.inf
  CoreInitTargetLib|QcomPkg/SocPkg/Kailua/Library/CoreInitTargetLib/CoreInitTargetLib.inf
  ServicesUtilsLib|QcomPkg/Library/ServicesLib/ServicesUtilsLib.inf
  SmBiosLib|QcomPkg/Library/SmBiosLib/SmBiosLib.inf
  SmemLib|QcomPkg/Library/SmemLib/build/SmemLibXBLCore.inf
# SpiNorCommonLib|QcomPkg/Library/NullLibs/SpiNorCommonLibNull/SpiNorCommonNullLib.inf
  TargetResetLib|QcomPkg/Library/TargetResetLib/TargetResetLib.inf
  TestInterfaceLib|QcomPkg/Library/TestInterfaceLib/TestInterfaceLib.inf
  TimerLib|ArmPkg/Library/ArmArchTimerLib/ArmArchTimerLib.inf
  TimetickLib|QcomPkg/Library/TimetickLibB/TimetickLib.inf
  TimetickRunTimeLib|QcomPkg/Library/TimetickLibB/TimetickRunTimeLib.inf
  TlmmLib|QcomPkg/Library/TlmmLib/TlmmLib.inf
  ToolSupportLib|QcomPkg/Library/ToolSupportLib/ToolSupportLib.inf
  TzRngLib|QcomPkg/Library/TzRngLib/TzRngLib.inf
  TzRuntimeLib|QcomPkg/Library/TzRuntimeLib/TzRuntimeLib.inf
  UfsCommonLib|QcomPkg/Library/UfsCommonLib/UfsCommonLib.inf
  StorageProfileLib|QcomPkg/Library/StorageCommonLib/StorageProfile.inf
  StorageBootCommonLib|QcomPkg/Library/StorageCommonLib/StorageCoreCommon.inf
  ShmBridgeLib|QcomPkg/Library/ShmBridgeLib/ShmBridgeLib.inf
  BamLib|QcomPkg/Library/BamLib/BamCoreLib.inf
  SPMIApiLib|QcomPkg/Library/SPMIApiLib/SPMIApiLib.inf
  ULogApiLib|QcomPkg/Library/ULogApiLib/ULogApiLib.inf
  CoreUtilsLib|QcomPkg/Library/CoreUtilsLib/CoreUtilsLib.inf
  DALModEnvLib|QcomPkg/Library/DALModEnvLib/DALModEnvLib.inf
  DALCommonDxeLib|QcomPkg/Library/DALCommonLib/DALCommonDxeLib.inf
  DALFwkLib|QcomPkg/Library/DALFwkLib/DALFwkLib.inf
  MDPLib|QcomPkg/Library/MDPLib/MDPLib.inf
  HALMDSSLib|QcomPkg/Library/HALMDSSLib/HALMDSS9xx.inf
  HALDSILib|QcomPkg/Library/HALDSILib/HALDSIMDSS9xxLib.inf
  ExternalDisplayLib|QcomPkg/Library/ExternalDisplayLib/ExternalDisplayLib.inf
  GpiLib|QcomPkg/Library/GpiLib/GpiLib.inf
  GpiDrvLib|QcomPkg/SocPkg/Library/GpiDrvLib/GpiDrvLib.inf
  I2CLib|QcomPkg/Library/I2CLib/I2CLib.inf
  I2CApiLib|QcomPkg/Library/I2CApiLib/I2CApiLib.inf
  I2CFWImageLib|QcomPkg/SocPkg/Kailua/Settings/I2C/I2CFWImageLib.inf
  #I2CFWImageLib|QcomPkg/Library/NullLibs/I2CFWImageLibNull/I2CFWImageLib.inf
  SPILib|QcomPkg/Library/SPILib/SPILib.inf
  SPIFWImageLib|QcomPkg/SocPkg/Kailua/Settings/SPI/SPIFWImageLib.inf
  #SPIFWImageLib|QcomPkg/Library/NullLibs/SPIFWImageLibNull/SPIFWImageLibNull.inf
  NpaApiLib|QcomPkg/Library/NpaApiLib/NpaApiLib.inf
  ClockApiLib|QcomPkg/Library/ClockApiLib/ClockApiLib.inf
  GPIOApiLib|QcomPkg/Library/GPIOApiLib/GPIOApiLib.inf
  CmdDbApiLib|QcomPkg/Library/CmdDbApiLib/CmdDbApiLib.inf
  PwrUtilsApiLib|QcomPkg/Library/PwrUtilsApiLib/PwrUtilsApiLib.inf
  RpmhApiLib|QcomPkg/Library/RpmhApiLib/RpmhApiLib.inf
  QdssLib|QcomPkg/Library/QdssLib/QdssLib.inf
  AdcDxeWrapperLib|QcomPkg/Library/PmicLib/adc/build/AdcDxeWrapperLib.inf
  HWConfigLib|QcomPkg/Library/HWConfigLib/HWConfigLib.inf
  UCLib|SecPkg/Library/UCLib_core/UCLib_core.inf
  PmicLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/PmicLib.inf
# PmicLib|QcomPkg/Library/NullLibs/PmicLibNull/PmicLibNull.inf
#QdssStmTargetLib|QcomPkg/SocPkg/Library/QdssStmTargetLib/QdssStmTargetLib.inf
#QdssTFunnelTargetLib|QcomPkg/SocPkg/Library/QdssTmcTargetLib/QdssTmcTargetLib.inf
#QdssTmcTargetLib|QcomPkg/SocPkg/Library/QdssTFunnelTargetLib/QdssTFunnelTargetLib.inf
#QusbDciCommonLib|QcomPkg/SocPkg/Library/QusbDciCommonLib/QusbDciCommonLib.inf
#QusbLdrLib|QcomPkg/SocPkg/Library/QusbLdrLib/QusbLdrLib.inf
#QusbTargetLib|QcomPkg/SocPkg/Library/QusbTargetLib/QusbTargetLib.inf
  SdccClockLib|QcomPkg/SocPkg/Kailua/Library/SdccClockLib/SdccCoreClockLib.inf
  SdccTargetLib|QcomPkg/SocPkg/Kailua/Library/SdccTargetLib/SdccCoreTargetLib.inf
  UfsTargetUefiLib|QcomPkg/SocPkg/Kailua/Library/UfsTargetLib/UfsTargetUefiLib.inf
#UsbWrapperLayerLib|QcomPkg/SocPkg/Library/UsbWrapperLayerLib/UsbWrapperLayerLib.inf
  HALclkLib|QcomPkg/SocPkg/Kailua/Library/HALclkLib/HALclkLib.inf
#PmicShutdownLibBoot|QcomPkg/SocPkg/Kailua/Library/PmicLib/core/shutdown/pm_shutdown.inf
  PmicShutdownLibBoot|QcomPkg/Library/NullLibs/PmicShutdownLibNull/pm_shutdown_Null.inf
  SmemTargetLib|QcomPkg/SocPkg/Library/SmemTargetLib/SmemTargetLib.inf
  DALGenLibCore|QcomPkg/SocPkg/Kailua/Settings/DALConfig/DALGenLibCore_LA.inf
  DALGenLibTools|QcomPkg/SocPkg/Kailua/Settings/DALConfig/DALGenLibTools.inf
  DALConfigLib|QcomPkg/SocPkg/Kailua/Settings/DALConfig/DALConfigCoreLib_LA.inf
  MDPPlatformLib|QcomPkg/SocPkg/Kailua/Library/MDPPlatformLib/MDPPlatformLib.inf
  BamTargetLib|QcomPkg/SocPkg/Library/BamTargetLib/BamTargetLib.inf
  SPMILib|QcomPkg/SocPkg/Kailua/Library/SPMILib/SPMILib.inf
  SPMIDebugLib|QcomPkg/SocPkg/Kailua/Library/SPMILib/SPMIDebugLib.inf
  BlkCryptoLib|QcomPkg/Library/BlkCryptoLib/BlkCryptoLib.inf

  TargetInitLib|QcomPkg/SocPkg/Library/TargetInitLib/TargetInitLib.inf

  TzDiagLib|QcomPkg/Library/TzDiagLib/TzDiag.inf

  # Variables Helper
  VariablesHelperLib|QcomPkg/Library/VariablesHelperLib/VariablesHelperLibLA.inf

  BootRecoverySmem|QcomPkg/Library/NullLibs/BootRecoverySmemLibNull/BootRecoverySmemLibNull.inf  
[LibraryClasses.Arm]
  ArmLib|ArmPkg/Library/ArmLib/ArmBaseLib.inf
  #ArmLib|QcomPkg/SocPkg/Waipio/Library/ArmLibTemp/ArmBaseLib.inf

[LibraryClasses.AARCH64]
  ArmLib|ArmPkg/Library/ArmLib/ArmBaseLib.inf
  #ArmLib|QcomPkg/SocPkg/Waipio/Library/ArmLibTemp/ArmBaseLib.inf

[LibraryClasses.common.SEC]
  BaseMemoryLib|MdePkg/Library/BaseMemoryLib/BaseMemoryLib.inf
  DefaultExceptionHandlerLib|QcomPkg/Library/DefaultExceptionHandlerLib/DefaultExceptionHandlerLibBase.inf
  ExtractGuidedSectionLib|EmbeddedPkg/Library/PrePiExtractGuidedSectionLib/PrePiExtractGuidedSectionLib.inf
  HobLib|EmbeddedPkg/Library/PrePiHobLib/PrePiHobLib.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
  PeCoffLib|MdePkg/Library/BasePeCoffLib/BasePeCoffLib.inf
  PerformanceLib|MdeModulePkg/Library/PeiPerformanceLib/PeiPerformanceLib.inf
  PrePiHobListPointerLib|EmbeddedPkg/Library/PrePiHobListPointerLib/PrePiHobListPointerLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  ReportStatusCodeLib|MdePkg/Library/BaseReportStatusCodeLibNull/BaseReportStatusCodeLibNull.inf
  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf
  BootConfigLib|QcomPkg/Library/BootConfigLib/BootConfigLibSec.inf
  DebugLib|QcomPkg/Library/DebugLib/DebugLib.inf
  PrintHostLib|QcomPkg/Library/PrintHostLib/PrintHostLib.inf
  ProcLib|QcomPkg/Library/ProcLib/ProcLib.inf
  MinidumpLib|QcomPkg/Library/MinidumpLib/MinidumpLibCore.inf
  DTBExtnSecLib|QcomPkg/Library/DTBExtnLib/DTBExtnSecLib.inf
# --PRESIL--
# SecFuseLib|QcomPkg/Library/NullLibs/SecFuseLibNull/SecFuseLibNull.inf
  SecFuseLib|QcomPkg/Library/SecFuseLib/SecFuseLib.inf
  TzAsmLib|QcomPkg/Library/TzAsmLib/TzAsmLib.inf
# --PRESIL--
# SerialPortLib|QcomPkg/Library/SerialPortLibT32/SerialPortLib.inf
  SerialPortLib|QcomPkg/Library/SerialPortLib/SerialPortLib.inf
  UartLib|QcomPkg/Library/UartQupv3Lib/UartCoreLib.inf
  UartSettingsLib|QcomPkg/SocPkg/Kailua/Settings/UART/UartSettingsLib.inf
  ShLib|QcomPkg/Library/ShLib/ShLibMgr.inf
  DepLib|QcomPkg/Library/DepLib/DepLib.inf
  PrePiMemoryAllocationLib|QcomPkg/Library/PrePiMemoryAllocationLib/PrePiMemoryAllocationLib.inf
  MemoryAllocationLib|QcomPkg/Library/PrePiMemoryAllocationLib/PrePiMemoryAllocationLib.inf
  AllocPagePoolLib|QcomPkg/Library/AllocPagePoolLib/AllocPagePoolLib.inf
  TargetInitLib|QcomPkg/SocPkg/Library/TargetInitLib/TargetInitLib.inf
# --SINGLE_THREAD--
#  SystemSleepLib|QcomPkg/Library/SystemSleepLib/SystemSleepNullLib.inf
  SystemSleepLib|QcomPkg/Library/SystemSleepLib/SystemSleepLib.inf
# --SINGLE_THREAD--
#  SplitBootLib|QcomPkg/Library/SplitBootLib/SplitBootNullLib.inf
  SplitBootLib|QcomPkg/Library/SplitBootLib/SplitBootLib.inf
#  WatchDogLib|QcomPkg/SocPkg/Library/WatchDogLib/WatchDogLib.inf
  WatchDogLib|QcomPkg/SocPkg/Library/VirtualWatchDogLib/VirtualWatchDogLib.inf

[LibraryClasses.ARM.SEC]
  ArmLib|ArmPkg/Library/ArmLib/ArmBaseLib.inf
  #ArmLib|QcomPkg/SocPkg/Waipio/Library/ArmLibTemp/ArmBaseLib.inf

[LibraryClasses.AARCH64.SEC]
  ArmLib|ArmPkg/Library/ArmLib/ArmBaseLib.inf
  #ArmLib|QcomPkg/SocPkg/Waipio/Library/ArmLibTemp/ArmBaseLib.inf

[LibraryClasses.common.PEI_CORE]
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf

[LibraryClasses.common.DXE_CORE]
  PeCoffExtraActionLib|ArmPkg/Library/DebugPeCoffExtraActionLib/DebugPeCoffExtraActionLib.inf
  PeCoffLib|EmbeddedPkg/Library/DxeHobPeCoffLib/DxeHobPeCoffLib.inf
  HobLib|MdePkg/Library/DxeCoreHobLib/DxeCoreHobLib.inf
  MemoryAllocationLib|MdeModulePkg/Library/DxeCoreMemoryAllocationLib/DxeCoreMemoryAllocationLib.inf
  DxeCoreEntryPoint|MdePkg/Library/DxeCoreEntryPoint/DxeCoreEntryPoint.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  UefiDecompressLib|MdePkg/Library/BaseUefiDecompressLib/BaseUefiDecompressLib.inf
  PerformanceLib|MdeModulePkg/Library/DxeCorePerformanceLib/DxeCorePerformanceLib.inf
  CpuExceptionHandlerLib|MdeModulePkg/Library/CpuExceptionHandlerLibNull/CpuExceptionHandlerLibNull.inf
  DebugLib|QcomPkg/Library/DebugLib/DebugLib.inf

[LibraryClasses.common.DXE_DRIVER]
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  GenericBdsLib|QcomPkg/Library/GenericBdsLib/GenericBdsLib.inf
  PlatformBdsLib|QcomPkg/Library/PlatformBdsLib/PlatformBdsLib.inf
  BdsTargetLib|QcomPkg/SocPkg/Library/BdsTargetLib/BdsTargetLib.inf
  QcomBdsLib|QcomPkg/Library/QcomBdsLib/QcomBdsLib.inf
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibNull/DxeCapsuleLibNull.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  OfflineCrashDumpLib|QcomPkg/Library/OfflineCrashDumpLib/OfflineCrashDumpDxeLib.inf
# --SINGLE_THREAD--
#  VirtCpuLib|QcomPkg/Library/VirtCpuLib/VirtCpuNullLib.inf
  VirtCpuLib|QcomPkg/Library/VirtCpuLib/VirtCpuLib.inf
  DefaultExceptionHandlerLib|ArmPkg/Library/DefaultExceptionHandlerLib/DefaultExceptionHandlerLib.inf
  ArmDisassemblerLib|ArmPkg/Library/ArmDisassemblerLib/ArmDisassemblerLib.inf

[LibraryClasses.common.UEFI_APPLICATION]
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  OfflineCrashDumpLib|QcomPkg/Library/OfflineCrashDumpLib/OfflineCrashDumpDxeLib.inf

[LibraryClasses.common.UEFI_DRIVER]
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  PerformanceLib|MdeModulePkg/Library/DxePerformanceLib/DxePerformanceLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf

[LibraryClasses.common.DXE_RUNTIME_DRIVER]
  HobLib|MdePkg/Library/DxeHobLib/DxeHobLib.inf
  MemoryAllocationLib|MdePkg/Library/UefiMemoryAllocationLib/UefiMemoryAllocationLib.inf
  ExtractGuidedSectionLib|MdePkg/Library/DxeExtractGuidedSectionLib/DxeExtractGuidedSectionLib.inf
  CapsuleLib|MdeModulePkg/Library/DxeCapsuleLibNull/DxeCapsuleLibNull.inf
  PeCoffLib|EmbeddedPkg/Library/DxeHobPeCoffLib/DxeHobPeCoffLib.inf
  OfflineCrashDumpLib|QcomPkg/Library/OfflineCrashDumpLib/OfflineCrashDumpDxeLib.inf
  HiiLib|MdeModulePkg/Library/UefiHiiLib/UefiHiiLib.inf
  UefiHiiServicesLib|MdeModulePkg/Library/UefiHiiServicesLib/UefiHiiServicesLib.inf
  DxeServicesLib|MdePkg/Library/DxeServicesLib/DxeServicesLib.inf
  PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  ReportStatusCodeLib|MdeModulePkg/Library/RuntimeDxeReportStatusCodeLib/RuntimeDxeReportStatusCodeLib.inf

[BuildOptions.ARM]
  # to enable thumb we need to evaluate if size is more advantage or speed
  RVCT:*_*_ARM_ARCHCC_FLAGS  == --cpu Cortex-A53 --thumb --fpu vfpv3
  RVCT:*_*_ARM_ARCHASM_FLAGS == --cpu Cortex-A53

[BuildOptions.AARCH64]
# --PRESIL-- Disable ASLR
# GCC:*_*_AARCH64_ARCHCC_FLAGS  == -fno-common -mtune=cortex-a53 -I$(WORKSPACE)/QcomPkg/SocPkg/Include -I$(WORKSPACE)/QcomPkg/SocPkg/Kailua/Include -include $(WORKSPACE)/QcomPkg/Include/Library/DebugLib.h -DQCOM_EDK2_PATCH -DDISABLE_DEP $(FEATURE_FLAGS) -DENABLE_XN -DENABLE_DEP_64 -DDISABLE_ASLR -DENABLE_EXEC_CODE_READY_TO_BOOT
# GCC:*_*_AARCH64_ARCHPP_FLAGS  == -I$(WORKSPACE)/QcomPkg/SocPkg/Include -I$(WORKSPACE)/QcomPkg/SocPkg/Kailua/Include -include $(WORKSPACE)/QcomPkg/Include/Library/DebugLib.h -DQCOM_EDK2_PATCH -DDISABLE_DEP $(FEATURE_FLAGS) -DENABLE_XN -DENABLE_DEP_64 -DDISABLE_ASLR -DENABLE_EXEC_CODE_READY_TO_BOOT

  GCC:*_*_AARCH64_ARCHCC_FLAGS  == -fno-common -mtune=cortex-a53 -I$(WORKSPACE)/QcomPkg/SocPkg/Include -I$(WORKSPACE)/QcomPkg/SocPkg/Kailua/Include -include $(WORKSPACE)/QcomPkg/Include/Library/DebugLib.h -DQCOM_EDK2_PATCH -DDISABLE_DEP $(FEATURE_FLAGS) -DENABLE_XN -DENABLE_DEP_64 -DENABLE_ASLR -DENABLE_EXEC_CODE_READY_TO_BOOT
  GCC:*_*_AARCH64_ARCHPP_FLAGS  == -I$(WORKSPACE)/QcomPkg/SocPkg/Include -I$(WORKSPACE)/QcomPkg/SocPkg/Kailua/Include -include $(WORKSPACE)/QcomPkg/Include/Library/DebugLib.h -DQCOM_EDK2_PATCH -DDISABLE_DEP $(FEATURE_FLAGS) -DENABLE_XN -DENABLE_DEP_64 -DENABLE_ASLR -DENABLE_EXEC_CODE_READY_TO_BOOT

!if $(PRODMODE) == "PRODMODE"
  RVCT:*_*_*_CC_FLAGS = -DPRODMODE
  GCC:*_*_*_CC_FLAGS = -DPRODMODE
!endif

!ifdef $(PRE_SIL)
  GCC:*_*_*_CC_FLAGS = -DPRE_SIL
!endif

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################

[PcdsFeatureFlag.common]
  gEfiMdePkgTokenSpaceGuid.PcdComponentNameDisable|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdDriverDiagnosticsDisable|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdComponentName2Disable|TRUE
  gEfiMdePkgTokenSpaceGuid.PcdDriverDiagnostics2Disable|TRUE
  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwarePerformanceDataTableS3Support|FALSE

  #
  # Control what commands are supported from the UI
  # Turn these on and off to add features or save size
  #
  gEmbeddedTokenSpaceGuid.PcdEmbeddedDirCmd|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedHobCmd|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedHwDebugCmd|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedPciDebugCmd|TRUE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedIoEnable|FALSE
  gEmbeddedTokenSpaceGuid.PcdEmbeddedScriptCmd|FALSE

  gEmbeddedTokenSpaceGuid.PcdCacheEnable|TRUE

  gEmbeddedTokenSpaceGuid.PcdPrePiProduceMemoryTypeInformationHob|TRUE

  gEfiMdeModulePkgTokenSpaceGuid.PcdTurnOffUsbLegacySupport|TRUE

  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutGopSupport|TRUE

  gEfiMdeModulePkgTokenSpaceGuid.PcdSupportUpdateCapsuleReset|TRUE

  ## Indicates if PEI phase StatusCode will be replayed in DXE phase.
  #   TRUE  - Replays PEI phase StatusCode in DXE phased.
  #   FALSE - Does not replay PEI phase StatusCode in DXE phase.
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeReplayIn|FALSE

  # HW Watchdog
  #gQcomTokenSpaceGuid.ForceEnableHWWdog|TRUE

  # proxy unvote timeout
#--PRESIL--
#  gQcomTokenSpaceGuid.ProxyUnvoteTimeout|50000000

  #
  # Target board Specific PCDs
  #

# TIANOCORE UPDATE: ShellPkg Disabled
#  gEfiShellPkgTokenSpaceGuid.PcdShellForceNoMapNoStartup|TRUE

  gArmTokenSpaceGuid.PcdArmGicV3WithV2Legacy|FALSE

[PcdsFixedAtBuild.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVendor|L"Qualcomm Technologies, Inc."
  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVersionString|L"6.0"

  gEmbeddedTokenSpaceGuid.PcdEmbeddedPrompt|"EBL"
  gEmbeddedTokenSpaceGuid.PcdPrePiCpuMemorySize|48
  gEmbeddedTokenSpaceGuid.PcdPrePiCpuIoSize|0
  gEfiMdePkgTokenSpaceGuid.PcdMaximumUnicodeStringLength|1000000
  gEfiMdePkgTokenSpaceGuid.PcdMaximumAsciiStringLength|1000000
  gEfiMdePkgTokenSpaceGuid.PcdMaximumLinkedListLength|1000000
  gEfiMdePkgTokenSpaceGuid.PcdSpinLockTimeout|10000000
  gEfiMdePkgTokenSpaceGuid.PcdDebugClearMemoryValue|0xAF

  # Disable perf
  gEfiMdePkgTokenSpaceGuid.PcdPerformanceLibraryPropertyMask|0
  gEfiMdePkgTokenSpaceGuid.PcdPostCodePropertyMask|0
  gEfiMdePkgTokenSpaceGuid.PcdUefiLibMaxPrintBufferSize|320

  # PcdDebugPropertyMask - From DebugLib.h:
  #   DEBUG_ASSERT_ENABLED       0x01
  #   DEBUG_PRINT_ENABLED        0x02
  #   DEBUG_CODE_ENABLED         0x04
  #   CLEAR_MEMORY_ENABLED       0x08
  #   ASSERT_BREAKPOINT_ENABLED  0x10
  #   ASSERT_DEADLOOP_ENABLED    0x20
!if $(PRODMODE) == "PRODMODE"
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2b
!else
  gEfiMdePkgTokenSpaceGuid.PcdDebugPropertyMask|0x2f
!endif

  # Pcd{Fixed}DebugPrintErrorLevel - From DebugLib.h:
  #   DEBUG_INIT      0x00000001  // Initialization
  #   DEBUG_WARN      0x00000002  // Warnings
  #   DEBUG_LOAD      0x00000004  // Load events
  #   DEBUG_FS        0x00000008  // EFI File system
  #   DEBUG_POOL      0x00000010  // Alloc & Free's
  #   DEBUG_PAGE      0x00000020  // Alloc & Free's
  #   DEBUG_INFO      0x00000040  // Verbose
  #   DEBUG_DISPATCH  0x00000080  // PEI/DXE Dispatchers
  #   DEBUG_VARIABLE  0x00000100  // Variable
  #   DEBUG_BM        0x00000400  // Boot Manager
  #   DEBUG_BLKIO     0x00001000  // BlkIo Driver
  #   DEBUG_NET       0x00004000  // SNI Driver
  #   DEBUG_UNDI      0x00010000  // UNDI Driver
  #   DEBUG_LOADFILE  0x00020000  // UNDI Driver
  #   DEBUG_EVENT     0x00080000  // Event messages
  #   DEBUG_GCD       0x00100000  // Global Coherency Database changes
  #   DEBUG_CACHE     0x00200000  // Memory range cachability changes
  #   DEBUG_VERBOSE   0x00400000  // Detailed debug messages that may significantly impact boot performance
  #   DEBUG_ERROR     0x80000000  // Error
!if $(PRODMODE) == "PRODMODE"
  # Only enable Errors and Boot Manager if Production Mode Flag is set
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x80000400
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel|0x80000400
!else
  gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0x800fee0f
  gEfiMdePkgTokenSpaceGuid.PcdFixedDebugPrintErrorLevel|0x800fee0f
!endif

  # PcdReportStatusCodePropertyMask - From ReportStatusCodeLib.h:
  #   REPORT_STATUS_CODE_PROPERTY_PROGRESS_CODE_ENABLED   0x00000001
  #   REPORT_STATUS_CODE_PROPERTY_ERROR_CODE_ENABLED      0x00000002
  #   REPORT_STATUS_CODE_PROPERTY_DEBUG_CODE_ENABLED      0x00000004
  gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x06

  gEmbeddedTokenSpaceGuid.PcdEmbeddedAutomaticBootCommand|""
  gEmbeddedTokenSpaceGuid.PcdEmbeddedDefaultTextColor|0x07
  gEmbeddedTokenSpaceGuid.PcdEmbeddedMemVariableStoreSize|0x10000

  gEmbeddedTokenSpaceGuid.PcdFlashFvMainBase|0
  gEmbeddedTokenSpaceGuid.PcdFlashFvMainSize|0

# Disable UEFI DEP
  gEfiMdeModulePkgTokenSpaceGuid.PcdImageProtectionPolicy|0x0

#
# Optional feature to help prevent EFI memory map fragments
# Turned on and off via: PcdPrePiProduceMemoryTypeInformationHob
# Values are in EFI Pages (4K). DXE Core will make sure that
# at least this much of each type of memory can be allocated
# from a single memory range. This way you only end up with
# maximum of two fragements for each type in the memory map
# (the memory used, and the free memory that was prereserved
# but not used).
#
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiACPIReclaimMemory|0
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiACPIMemoryNVS|0
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiReservedMemoryType|0
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiRuntimeServicesData|80
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiRuntimeServicesCode|40
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiBootServicesCode|400
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiBootServicesData|800
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiLoaderCode|10
  gEmbeddedTokenSpaceGuid.PcdMemoryTypeEfiLoaderData|0

#
# SMBIOS related
#
  # OEM's can set their product info here
  gQcomTokenSpaceGuid.PcdSystemMfrStr|"Qualcomm"
  gQcomTokenSpaceGuid.PcdSystemProductNameStr|""
  gQcomTokenSpaceGuid.PcdSystemProductFamilyStr|""

#
# ACPI related
#
  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiExposedTableVersions|0xC
  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemId|"QCOM  "
  #Signature_64('Q','C','O','M','E','D','K','2') = 0x324B44454D4F4351 = '2','K','D','E','M','O','C','Q'
  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemTableId|0x324B44454D4F4351
  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemRevision|0x00000001
  #Signature_32('Q', 'C', 'O', 'M') = 0x4D4F4351
  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultCreatorId|0x4D4F4351
  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultCreatorRevision|0x00000001
  gQcomTokenSpaceGuid.DisableWriteProtect|TRUE


#
# Display PCDs
# Read QcomPkg/Docs/DisplayConfiguration.txt for PCDs configuration details.
#
  gQcomTokenSpaceGuid.PcdDisplayForceSwRenderer|FALSE
  # gFBResLimit Table 0: 5k, 1: 4k, 2: UHD, 3: WQHD, 4: WUXGA, 5: FHD, 6: HD
  gQcomTokenSpaceGuid.PcdFrameBufMaxRes|0
  # External display type:  0: No external display, 1: DisplayPort.
  gQcomTokenSpaceGuid.PcdExtDisplayType|0
  gQcomTokenSpaceGuid.PcdBacklightLevel|50
  gQcomTokenSpaceGuid.PcdPresentationMode|0
  # No charger policy used for display
  gQcomTokenSpaceGuid.PcdDisplayChargerPolicy|0
  # Enable PFS for display
  gQcomTokenSpaceGuid.PcdPrimaryFlags|0x10000000
  # PcdBGRTRotation:  0: no rotation, 1: 90 degree CW Rotation, 2: 180 rotation, 3: 270 CW rotation.
  gQcomTokenSpaceGuid.PcdBGRTRotation|0


#
# LPM PCDs
#

 gQcomTokenSpaceGuid.PcdLpm|0x030580A5


#
# Target Specific PCDs
#

  #########################################################################
  #                               Memory Map
  #########################################################################

  gQcomTokenSpaceGuid.PcdMaxMemory|0x0

  #################################
  ## Presilicon definitions.
  #################################
  gQcomTokenSpaceGuid.PcdMemoryBase|0x80000000    # Starting address
  gQcomTokenSpaceGuid.PcdMemorySize|0x60000000    # 1.5 GB

  #################################
  ## HLOS Base Offset and size.
  #################################
  gQcomTokenSpaceGuid.PcdHLOSMemoryBaseOffset|0x98200000 # remaining memory after this is HLOS

  #################################
  ## UEFI Memory Base Offset and Size.
  #################################
  gQcomTokenSpaceGuid.PcdUefiMemPoolBaseOffset|0x94E00000
  gQcomTokenSpaceGuid.PcdUefiMemPoolSize|0x03300000     # 51 MB

  # The HOB list will start here.
  # NOTE: Hob.c is still referencing PcdPrePiHobBase
  gQcomTokenSpaceGuid.PcdPrePiHobBase|0x94E00000

  # Offset to UEFI memory
  gQcomTokenSpaceGuid.PcdPreAllocatedMemorySize|0x00000000


  #################################
  ## FD Base offset (refer to .fdf for FD size)
  #################################
  gQcomTokenSpaceGuid.PcdEmbeddedFdBaseAddress|0xA7000000

  #################################
  ## Shared Memory Base offset and size.
  ## TODO: PcdSmemBaseAddress is currently used by smem library
  #################################
  gQcomTokenSpaceGuid.PcdSmemBaseAddress|0x81D00000  #64-bit smem addr
  gQcomTokenSpaceGuid.PcdSmemSize|0x00200000     # 2MB
  ## Generic SMEM information that SMEM lib might need
  ## LSB represents chip family, other bytes are unused for now.
  gQcomTokenSpaceGuid.PcdSmemInformation|0x00000005  # 5 = Nazgul

  # Maximum number of memory regions defined in the above memory map
  gQcomTokenSpaceGuid.PcdMaxMemRegions|64

  #################################
  ## IMem Base Address and size.
  #################################

  gQcomTokenSpaceGuid.PcdIMemCookiesBase|0x146AA000
  gQcomTokenSpaceGuid.PcdIMemCookiesSize|0x00001000
  gQcomTokenSpaceGuid.PcdDBIDumpTableInfoDeRegisterDisable|FALSE

  # Cookie (memory capture mode) Address for crash dump support
  gQcomTokenSpaceGuid.PcdHLOSCrashCookieAddr|0x146BF018

  # Uefi Debug Cookie Address and value
  gQcomTokenSpaceGuid.PcdUefiDebugCookieOffset|0x944
  gQcomTokenSpaceGuid.PcdUefiDebugCookie|0x55444247

  gArmTokenSpaceGuid.PcdCpuResetAddress|0x08000000    # warm reset should use this

  gArmPlatformTokenSpaceGuid.PcdCoreCount|8

  # Secure boot efuse register address
  gQcomTokenSpaceGuid.PcdSecbootRegAddr|0x0005E030
  gQcomTokenSpaceGuid.PcdSecbootAuthEnMask|0x20


  # Timer Debug
  gQcomTokenSpaceGuid.PcdTimerDxeDebug|FALSE

  # Timers
  gEmbeddedTokenSpaceGuid.PcdInterruptBaseAddress|0x9BC0000

  # Timers
#--PRESIL--
  #gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|400000
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|19200000
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|29
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|30

  gArmTokenSpaceGuid.PcdGicDistributorBase|0x17100000       # APSS_GICD_CTLR
  gArmTokenSpaceGuid.PcdGicRedistributorsBase|0x17180000    # APSS_ALIAS0_GICR_CTLR

  gQcomTokenSpaceGuid.PcdInterruptTimerIndex|3
  gQcomTokenSpaceGuid.PcdInterruptTimerPeriod|100000
  gQcomTokenSpaceGuid.PcdTimer1IRQ|0x28
  gQcomTokenSpaceGuid.PcdTimerTestClockFreq|918000000 # Pcycles runs at 918 MHz
  gQcomTokenSpaceGuid.PcdTimerTestClockFreqDiv|64 # Pcycles divided by value
  gQcomTokenSpaceGuid.PcdQTimerAC_BasePhys|0x17420000      # APSS_QTMR0_QTMR_AC
  gQcomTokenSpaceGuid.PcdQTimerV1BasePhys|0x17421000       # APSS_QTMR0_F0V1_QTMR_V1
  gQcomTokenSpaceGuid.PcdQTimerV2BasePhys|0x17422000       # APSS_QTMR0_F0V2_QTMR_V2
  gQcomTokenSpaceGuid.PcdQTimerFrame|0
  gQcomTokenSpaceGuid.PcdQTimerEnabled|1
  gQcomTokenSpaceGuid.PcdPerfomanceCounterEnd|0xFFFFFFFF
  gQcomTokenSpaceGuid.PcdPerfomanceCounterStart|0x00000000
  gQcomTokenSpaceGuid.PcdPerformanceCounterIndex|3
  gQcomTokenSpaceGuid.PcdRealTimeClockResolution|1
  gQcomTokenSpaceGuid.PcdRealTimeClockAccuracy|200000000
  gQcomTokenSpaceGuid.PcdRealTimeClockSetToZero|1

  #TODO: Need to correct based on frequency plan
  gQcomTokenSpaceGuid.PcdAppsProcFrequencyMhz|1190

  #MPM_SLEEP_TIMETICK_COUNT_VAL for time from power on
  gQcomTokenSpaceGuid.PcdTimeTickClkAddress|0x0C221000

  gQcomTokenSpaceGuid.PcdPsHoldAddress|0xC264000

  #IPCC
  gQcomTokenSpaceGuid.PcdIPCCLibProtocol|0
  gQcomTokenSpaceGuid.PcdIPCCLibLocalClient|8
  gQcomTokenSpaceGuid.PcdIPCCLibTotalSignals|4

 #Default target Panic behavior - Shutdown
  gQcomTokenSpaceGuid.PcdTargetPanic|0x0

  #I2C
  gQcomTokenSpaceGuid.EEPROMI2CCore|15
  gQcomTokenSpaceGuid.EEPROMSlaveAddress|0x52

  # SPI Loopback
  gQcomTokenSpaceGuid.SPILoopbackCore|10


  # SDCC
  gQcomTokenSpaceGuid.SDCCExtSlotNumber|1
  gQcomTokenSpaceGuid.SDCCEmmcSlotNumber|0
  gQcomTokenSpaceGuid.SDCCRpmbKey|{0x20, 0xAA, 0x9C, 0xF4, 0x99, 0x4D, 0xD4, 0xFE, 0xA5, 0x85, 0xBE, 0x96, 0x6, 0x1, 0xD1, 0xA9, 0xC3, 0x3, 0x4F, 0x91, 0x62, 0x7C, 0x64, 0x53, 0x38, 0xC1, 0x1F, 0xF2, 0x76, 0x4D, 0x2E, 0xC4}
  gQcomTokenSpaceGuid.SDCCEventBasedSDDetectEnabled|TRUE
  gQcomTokenSpaceGuid.SDCCDmaEnabled|TRUE
  gQcomTokenSpaceGuid.SDCCEmmcHwResetEnabled|TRUE
  gQcomTokenSpaceGuid.SDCCMaxSlotNumber|2
  gQcomTokenSpaceGuid.SDCCSdhciEnable|TRUE
  ## SDCC eMMC speed mode - DDR50: 0, HS200: 1, HS400: 2 SDR: 3 ##
  gQcomTokenSpaceGuid.SDCCEmmcSpeedMode|1
  gQcomTokenSpaceGuid.SDCCRegBase|"+PERIPH_SS_SDC2_SDCC_SDCC5_HC"

  #
  # ARM Pcds
  #
  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0xA7600000

  # Timer sync not required
  gQcomTokenSpaceGuid.PcdSyncTimerToMPP|FALSE

  # UART
  gQcomTokenSpaceGuid.UartPlatform|"SDM855"

  # USB
  gQcomTokenSpaceGuid.InitUsbControllerOnBoot|FALSE
  gQcomTokenSpaceGuid.HostModeSupported|FALSE
  gQcomTokenSpaceGuid.USBSmmuStage1Supported|TRUE
  # U1U2 enablement results in SS and SSP instability
  gQcomTokenSpaceGuid.USBU1U2Supported|FALSE
  gQcomTokenSpaceGuid.USBPriHighSpeedOnlySupported|FALSE
  gQcomTokenSpaceGuid.USBPriDPBonded|FALSE

  #set UsbNoPmic flag to TRUE if PMIC Charger is not being used
  gQcomTokenSpaceGuid.UsbNoPmic|FALSE
  #Secondary Port Flag
  #gQcomTokenSpaceGuid.USBSecHighSpeedOnlySupported|FALSE
  #gQcomTokenSpaceGuid.FastbootSecPort|FALSE
  #gQcomTokenSpaceGuid.USBSecDPBonded|FALSE    #Enable only for TypeC Secondary port
  #Multi port FLAG
  #gQcomTokenSpaceGuid.USBMultiPortSupported|FALSE
  #gQcomTokenSpaceGuid.USBMPHighSpeedOnlySupported|FALSE

!if $(PRODMODE) == "PRODMODE"
  # Version info needed on LCD Display
  gQcomTokenSpaceGuid.VersionDisplay|FALSE
!else
  # Version info needed on debug port
  gQcomTokenSpaceGuid.VersionDisplay|TRUE
!endif

  # offset to 4KB shared memory in System IMEM             : 0x8603F000
  # offset to 200 bytes HLOS region within this 4KB memory : 0x658
  # offset 0  : 4 byte physical address for DebugLog Override
  gQcomTokenSpaceGuid.PcdDebugLogOverrideAddress|0x08642658

  # Magic signature value that is used to indicate DebugLog Override
  # capability in DebugLib of DXE
  gQcomTokenSpaceGuid.PcdDebugLogOverrideMagic|0x534B4950

  # Hard/Warm Reset
  gQcomTokenSpaceGuid.PcdUefiHardResetConfigure|TRUE
  gQcomTokenSpaceGuid.PcdUefiWarmResetConfigure|TRUE
  gQcomTokenSpaceGuid.PcdUefiHardResetEnabled|TRUE
  gQcomTokenSpaceGuid.PcdUefiWarmResetEnabled|TRUE

  # PON Debounce
  gQcomTokenSpaceGuid.PcdPONDebounce|0x00000001 # max value 0x07

  gEfiMdeModulePkgTokenSpaceGuid.PcdProgressCodeOsLoaderLoad | 0x03058000
  gEfiMdeModulePkgTokenSpaceGuid.PcdProgressCodeOsLoaderStart| 0x03058001

  # ChargerTaskSupported
  gQcomTokenSpaceGuid.PcdChargerTaskSupported|FALSE

  # Default to EL1
  gQcomTokenSpaceGuid.PcdSwitchToEL1|TRUE

  # HeapGuard for Page and Pool for memory Type BsData
  #gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPropertyMask | 0x3
  #gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPoolType | 0x10
  #gEfiMdeModulePkgTokenSpaceGuid.PcdHeapGuardPageType | 0x10

[PcdsPatchableInModule]
  ## This PCD defines the Console output column and the default value is 25 according to UEFI spec
  #gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|53

  ## This PCD defines the Console output row and the default value is 80 according to UEFI spec
  #gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|75

  # This PCD should be set to 0 then video resolution could be at highest resolution.
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|0
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|0

  ## Indicates if StatusCode is reported via Serial port.
  #   TRUE  - Reports StatusCode via Serial port.
  #   FALSE - Does not report StatusCode via Serial port.
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseSerial|TRUE

  ## Indicates if StatusCode is stored in memory.
  #  The memory is boot time memory in PEI Phase and is runtime memory in DXE Phase.
  #   TRUE  - Stores StatusCode in memory.
  #   FALSE - Does not store StatusCode in memory.
  gEfiMdeModulePkgTokenSpaceGuid.PcdStatusCodeUseMemory|FALSE


[LibraryClasses.common]

  # External Display Interface Common Libraries
!if ( gQcomTokenSpaceGuid.PcdExtDisplayType == 1 )
  HALDPLib|QcomPkg/Library/HALDPLib/HALDPLib.inf
!else
  HALDPLib|QcomPkg/Library/HALDPLib/HALDPLibStub.inf
!endif


################################################################################
#
# Components Section - list of all EDK II Modules needed by this Platform
#
################################################################################
[Components.common]
#
# SEC
#
  QcomPkg/XBLCore/XBLCore.inf {
    <LibraryClasses>
      SchedulerLib|QcomPkg/Library/SchedulerLib/SchedulerLib.inf
      FvDecompressLib|QcomPkg/Library/FvDecompressLib/PrePiFvDecompressLib.inf
      KernelLib|QcomPkg/Library/KernelLib/PrePiKernelLib.inf
  }

#
# PEI - not used on QC platform
#

#
# DXE
#
  MdeModulePkg/Core/Dxe/DxeMain.inf {
    <LibraryClasses>
      PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf
      DebugLib|QcomPkg/Library/DebugLib/DebugLib.inf
      NULL|MdeModulePkg/Library/DxeCrc32GuidedSectionExtractLib/DxeCrc32GuidedSectionExtractLib.inf
      NULL|EmbeddedPkg/Library/LzmaHobCustomDecompressLib/LzmaHobCustomDecompressLib.inf
  }
  ArmPkg/Drivers/CpuDxe/CpuDxe.inf
  MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/RscRtDxe.inf
  MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/SCHandlerRtDxe.inf
  MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
  MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
  QcomPkg/Drivers/SecRSADxe/SecRSADxe.inf
  QcomPkg/Drivers/ASN1X509Dxe/ASN1X509Dxe.inf
  QcomPkg/Drivers/VerifiedBootDxe/VerifiedBootDxe.inf
#  QcomPkg/Drivers/VerifiedBootNullDxe/VerifiedBootNullDxe.inf
  QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxeLA.inf
# QcomPkg/Drivers/TzDxe/ScmDxeLA.inf
  QcomPkg/Drivers/TzDxe/ScmDxeLA_Kailua.inf{
    <LibraryClasses>
      TzAsmLib|QcomPkg/Library/TzAsmLib/TzAsmLib.inf
  }
  QcomPkg/Drivers/TzDxe/TzDxeLA.inf
  QcomPkg/Drivers/PsStateDxe/PsStateDxe.inf
  MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
  MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
# QcomPkg/Drivers/VariableDxe/EmuRuntimeDxe/EmuVariableRuntimeDxe.inf
  QcomPkg/Drivers/VariableDxe/VariableDxe.inf
  QcomPkg/Drivers/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
  QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
  QcomPkg/Drivers/ResetRuntimeDxe/ResetRuntimeDxe.inf
  EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
  EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
  MdeModulePkg/Universal/PrintDxe/PrintDxe.inf{
    <LibraryClasses>
      PrintLib|MdePkg/Library/BasePrintLib/BasePrintLib.inf
  }
  MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
  MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
  MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
  MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
  MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
  QcomPkg/Drivers/FontDxe/FontDxe.inf
  QcomPkg/Drivers/TLMMDxe/TLMMDxe.inf{
    <LibraryClasses>
      TLMMTargetLib|QcomPkg/SocPkg/Kailua/Library/TLMMTargetLib/TLMMTargetLibCore.inf
  }
  QcomPkg/Drivers/EnvDxe/EnvDxe.inf {
  <LibraryClasses>
    DebugLib|QcomPkg/Library/DebugLib/DebugLib.inf
    EnvTempLib|QcomPkg/Library/EnvTempLib/EnvTempLibNull.inf
  }
  QcomPkg/Drivers/ParserDxe/ParserDxe.inf
  QcomPkg/Drivers/SerialPortDxe/SerialPortDxe.inf
  QcomPkg/Drivers/QcomWDogDxe/QcomWDogDxe.inf
#  QcomPkg/Drivers/OSConfigDxe/OSConfigDxe.inf
  QcomPkg/Drivers/SmemDxe/SmemDxe.inf
  QcomPkg/Drivers/IPCCDxe/IPCCDxe.inf {
  <LibraryClasses>
  IPCCTargetLib|QcomPkg/SocPkg/Kailua/Library/IPCCTargetLib/IPCCTargetLib.inf
  IPCCLib|QcomPkg/Library/IPCCLib/IPCCLib.inf
  }
  QcomPkg/Drivers/GLinkDxe/GLinkDxe.inf {
  <LibraryClasses>
  SmdLib|QcomPkg/Library/SmdLib/SmdLib.inf
  GLinkLib|QcomPkg/Library/GLinkLib/GLinkLib.inf
  }
  MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
  MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
  FatPkg/EnhancedFatDxe/Fat.inf
  MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
  MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf
  QcomPkg/Drivers/DDRInfoDxe/DDRInfoDxe.inf
  QcomPkg/Drivers/UsbfnDwc3Dxe/UsbfnDwc3Dxe.inf {
    #<PcdsFixedAtBuild>
    #gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0xFFFFFFFF
    <LibraryClasses>
    UsbfnDwc3Lib|QcomPkg/SocPkg/Kailua/Library/UsbfnDwc3Lib/UsbfnDwc3Lib.inf
  }
  QcomPkg/Drivers/XhciPciEmulationDxe/XhciPciEmulationDxe.inf
  QcomPkg/Drivers/XhciDxe/XhciDxe.inf
  QcomPkg/Drivers/UsbBusDxe/UsbBusDxe.inf
  QcomPkg/Drivers/UsbKbDxe/UsbKbDxe.inf
  QcomPkg/Drivers/UsbMassStorageDxe/UsbMassStorageDxe.inf
  QcomPkg/Drivers/UsbMsdDxe/UsbMsdDxe.inf
  QcomPkg/Drivers/UsbDeviceDxe/UsbDeviceDxe.inf
  QcomPkg/Drivers/UsbConfigDxe/UsbConfigDxe.inf  {
    #<PcdsFixedAtBuild>
      #gEfiMdePkgTokenSpaceGuid.PcdDebugPrintErrorLevel|0xFFFFFFFF
    <LibraryClasses>
      UsbConfigLib|QcomPkg/SocPkg/Kailua/Library/UsbConfigLib/UsbConfigLib.inf
      #UsbConfigLib|QcomPkg/Library/NullLibs/UsbConfigLibNull/UsbConfigLibNull.inf
  }
  QcomPkg/Drivers/UsbInitDxe/UsbInitDxe.inf
  QcomPkg/Drivers/DALSYSDxe/DALSYSDxe.inf
  QcomPkg/Drivers/ICBDxe/ICBDxe.inf
  QcomPkg/Drivers/ClockDxe/ClockDxe.inf {
      <LibraryClasses>
      ClockLib|QcomPkg/SocPkg/Kailua/Library/ClockLib/ClockLib.inf
  }
#  QcomPkg/Drivers/NULLClockDxe/NULLClockDxe.inf
#  QcomPkg/Drivers/ClockDxe/ClockDriverTestInterface/ClockTestInterface.inf
  QcomPkg/Drivers/VcsDxe/VcsDxe.inf {
    <LibraryClasses>
      VcsLib|QcomPkg/SocPkg/Kailua/Library/VcsLib/VcsLib.inf
  }
  QcomPkg/Drivers/HALIOMMUDxe/HALIOMMUDxe.inf
  QcomPkg/Drivers/HWIODxe/HWIODxe.inf
  QcomPkg/Drivers/UCDxe/UCDxe.inf
  QcomPkg/Drivers/RNGDxe/RngDxe.inf
  QcomPkg/Drivers/FeatureEnablerDxe/FeatureEnablerDxe.inf
  QcomPkg/Drivers/DisplayDxe/DisplayDxe.inf
  QcomPkg/Drivers/QRKSDxe/QRKSDxe.inf
  ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
  ArmPkg/Drivers/TimerDxe/TimerDxe.inf
  QcomPkg/Drivers/ChipInfoDxe/ChipInfoDxe.inf
  #
  # GPI Driver
  #
  QcomPkg/Drivers/GpiDxe/GpiDxe.inf

  #
  # I2C Driver
  #
  QcomPkg/Drivers/I2CDxe/I2CDxe.inf

  #
  # SPI Driver
  #
  QcomPkg/Drivers/SPIDxe/SPIDxe.inf
  
  QcomPkg/Drivers/NpaDxe/NpaDxe.inf {
    <LibraryClasses>
#      #RpmLib|QcomPkg/Library/RpmLib/RpmLib.inf
#      #SmdLib|QcomPkg/Library/SmdLib/SmdLib.inf
     NpaLib|QcomPkg/Library/NpaLib/NpaLib.inf
  }
  QcomPkg/Drivers/ULogDxe/ULogDxe.inf {
    <LibraryClasses>
      ULogLib|QcomPkg/Library/ULogLib/ULogLib.inf
  }
  QcomPkg/Drivers/CmdDbDxe/CmdDbDxe.inf {
    <LibraryClasses>
      CmdDbLib|QcomPkg/Library/CmdDbLib/CmdDbLib.inf
      CmdDbTargetLib|QcomPkg/SocPkg/Kailua/Library/CmdDbTargetLib/CmdDbTargetLib.inf
  }
  QcomPkg/Drivers/PwrUtilsDxe/PwrUtilsDxe.inf {
    <LibraryClasses>
      PwrUtilsLib|QcomPkg/Library/PwrUtilsLib/PwrUtilsLib.inf
  }
  QcomPkg/Drivers/RpmhDxe/RpmhDxe.inf {
    <LibraryClasses>
     RpmhLib|QcomPkg/SocPkg/Kailua/Library/RpmhTargetLib/RpmhLib.inf
  }
  QcomPkg/Drivers/CPRDxe/CPRDxe.inf {
    <LibraryClasses>
      CPRLib|QcomPkg/SocPkg/Kailua/Library/CPRTargetLib/Core/CPRTargetLib.inf
  }
  QcomPkg/Drivers/SPMIDxe/SPMIDxe.inf
  QcomPkg/Drivers/PlatformInfoDxe/PlatformInfoDxe.inf
  QcomPkg/Drivers/ButtonsDxe/ButtonsDxe.inf {
   <LibraryClasses>
     ButtonsLib|QcomPkg/SocPkg/Kailua/Library/ButtonsTargetLib/ButtonsLib.inf
  }
  QcomPkg/Drivers/RscDxe/RscDxe.inf {
     <LibraryClasses>
       RscTargetLib|QcomPkg/SocPkg/Kailua/Library/RscTargetLib/RscTargetLib.inf
  }
# --PRESIL--
# QcomPkg/Drivers/PmicDxe/NullLib/PmicDxeNull.inf
  QcomPkg/Drivers/PmicDxe/PmicDxeLa.inf {
   <LibraryClasses>
    PmicCoreLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/core/la/PmicCoreLib.inf
    AdcCoreLib|QcomPkg/Library/PmicLib/adc/build/AdcCoreLib.inf
   }
  # Pmic GLink Driver
  QcomPkg/Drivers/PmicGlinkDxe/PmicGlinkDxe.inf
# --PRESIL--
#  QcomPkg/Drivers/ChargerExDxe/NullLib/ChargerExDxeNull.inf
   QcomPkg/Drivers/ChargerExDxe/ChargerExDxe.inf
   QcomPkg/Drivers/QcomChargerDxe/QcomChargerDxeLA.inf
   QcomPkg/Drivers/UsbPwrCtrlDxe/UsbPwrCtrlDxe.inf
# --PRESIL--
  QcomPkg/Drivers/TsensDxe/TsensDxe.inf {
     <LibraryClasses>
       TsensCoreLib|QcomPkg/Library/TsensLib/TsensCoreLib.inf
       TsensTargetLib|QcomPkg/SocPkg/Kailua/Library/TsensTargetLib/TsensTargetLib.inf
   }
 QcomPkg/Drivers/LimitsDxe/LimitsDxe.inf {
    <LibraryClasses>
    LimitsTargetLib|QcomPkg/SocPkg/Kailua/Library/LimitsTargetLib/LimitsTargetLib.inf
  }
# --PRESIL--
  QcomPkg/Drivers/SdccDxe/SdccDxe.inf
  QcomPkg/Drivers/UFSDxe/UFSDxe.inf
  QcomPkg/Drivers/SerialDxe/SerialDxe.inf {
    <LibraryClasses>
      SerialPortLib|QcomPkg/Library/SerialPortLib/SerialPortLib.inf
      UartLib|QcomPkg/Library/UartQupv3Lib/UartCoreLib.inf
      UartSettingsLib|QcomPkg/SocPkg/Kailua/Settings/UART/UartSettingsLib.inf
!ifdef FEATURE_XBOOT
      XLogLibCust|SomcPkg/Platform/SomcQcomCmnPkg/Library/XLogLib/XLogCustLib.inf
      XLogLibHook|SomcPkg/Platform/SomcQcomCmnPkg/Library/XLogLib/XLogHookLib.inf
!endif # FEATURE_XBOOT
  }
  QcomPkg/Drivers/PILDxe/PILDxe.inf
  QcomPkg/Drivers/PILProxyDxe/PILProxyDxe.inf
  QcomPkg/Drivers/QcomBds/QcomBds.inf {
    <LibraryClasses>
      NULL|QcomPkg/Library/XnWrapperLib/XnWrapperLib.inf
  }

  QcomPkg/Application/QcomChargerApp/QcomChargerApp.inf {
    <PcdsFixedAtBuild>
      gEfiMdePkgTokenSpaceGuid.PcdReportStatusCodePropertyMask|0x07
  }
  QcomPkg/Drivers/SPSSDxe/SPSSDxe.inf
  EmbeddedPkg/Ebl/Ebl.inf

  #
  # FV Utils Driver
  #
  QcomPkg/Drivers/FvUtilsDxe/FvUtilsDxe.inf

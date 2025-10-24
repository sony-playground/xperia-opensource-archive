#==============================================================================
# @file Common.dsc.inc
# Target independent loader libraries
#
# Copyright (c) 2017 - 2022 Qualcomm Technologies, Inc. All rights reserved.
# Portions Copyright (c) 2009 - 2010, Apple Inc. All rights reserved.
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#==============================================================================
[LibraryClasses.common]
  # EDK2 Libraries
  !include MdePkg/MdeLibs.dsc.inc
  NULL|ArmPkg/Library/CompilerIntrinsicsLib/CompilerIntrinsicsLib.inf
  BaseLib|MdePkg/Library/BaseLib/BaseLib.inf
  BaseMemoryLib|QcomPkg/Library/BaseMemoryLibStm/BaseMemoryLibStm.inf
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf
  PcdLib|MdePkg/Library/BasePcdLibNull/BasePcdLibNull.inf

  #EDK2 ARM MMU/Cache libs
  ArmLib|ArmPkg/Library/ArmLib/ArmBaseLib.inf
  ArmMmuLib|ArmPkg/Library/ArmMmuLib/ArmMmuBaseLib.inf
  CacheMaintenanceLib|ArmPkg/Library/ArmCacheMaintenanceLib/ArmCacheMaintenanceLib.inf

  # Qcom Generic Libraries

  #Bam Lib
  BamLoaderLib|QcomPkg/Library/BamLib/BamLoaderLib.inf
  BamTargetLib|QcomPkg/SocPkg/Library/BamTargetLib/BamTargetLib.inf

  AdcLoaderLib|QcomPkg/Library/PmicLib/adc/build/AdcLoaderLib.inf
  EepromLib|QcomPkg/Library/NullLibs/EepromLibNull/EepromLibNull.inf
  EepromCommonLib|QcomPkg/Library/NullLibs/EepromLibNull/EepromLibNull.inf
  BootDisplayLib|QcomPkg/Library/BootDisplayLib/BootDisplayLib.inf
  BusyWaitLib|QcomPkg/Library/BusyWaitLib/BusyWaitLoaderLib.inf
  ChipInfoDalFwkLib|QcomPkg/Library/ChipInfoLib/ChipInfoDalFwk.inf
  ChipInfoCommonLib|QcomPkg/Library/ChipInfoLib/ChipInfoCommon.inf
  ChipInfoSKULib|QcomPkg/Library/ChipInfoLib/ChipInfoSKULib.inf
  CoreUtilsLib|QcomPkg/Library/CoreUtilsLib/CoreUtilsLib.inf
  DALCommonLoaderLib|QcomPkg/Library/DALCommonLib/DALCommonLoaderLib.inf
  DALFwkLib|QcomPkg/Library/DALFwkLib/DALFwkLib.inf
  FontLib|QcomPkg/Library/FontLib/FontLib.inf
  HFATLib|QcomPkg/Library/HFATLib/HFATLib.inf
  ColdplugLib|QcomPkg/Library/ColdplugLib/ColdplugSpiNorLib.inf
  DbgInfoLib|SecPkg/Library/dbginfolib/build/DbgInfoLib.inf
  LogsToMediaLib|QcomPkg/XBLLoader/LogsToMediaLib/LogsToMediaLib.inf

  ImageVersionLib|QcomPkg/Library/ImageVersionLib/ImageVersionLib.inf
  MuslLib|QcomPkg/Library/MuslLib/MuslLib.inf
  NULL|QcomPkg/Library/MuslLib/MuslLib.inf
  NULL|QcomPkg/Library/StackCanaryBaseLib/StackCanaryBaseLibLoader.inf
  PlatformInfoLoaderLib|QcomPkg/Library/PlatformInfoLib/PlatformInfoLoader.inf
  QusbLib|QcomPkg/Library/QusbLib/QusbLib.inf
  ROMFSLib|QcomPkg/Library/EfsLib/ROMFSLib.inf
  RailwayLib|QcomPkg/Library/RailwayLib/RailwayLib.inf
  SPILib|QcomPkg/Library/SPILib/SPILibLoader.inf
  SPMIApiLib|QcomPkg/Library/SPMIApiLib/SPMIApiLib.inf
  SdccCommonLib|QcomPkg/Library/SdccCommonLib/SdccCommonLib.inf
  SdccHalLib|QcomPkg/Library/SdccCommonLib/SdccHalLib/SdccHalLib.inf
  StackCanaryBaseLib|QcomPkg/Library/StackCanaryBaseLib/StackCanaryBaseLibLoader.inf
  TrialBootInfoLib|QcomPkg/Library/NullLibs/TrialBootInfoLibNull/TrialBootInfoLibNull.inf
  UartLib|QcomPkg/Library/UartQupv3Lib/UartLoaderLib.inf
  I2CLib |QcomPkg/Library/I2CLib/I2CLibLoader.inf
  ServicesUtilsLib|QcomPkg/Library/ServicesLib/ServicesUtilsLib.inf
#  SmemLib|QcomPkg/Library/SmemLib/build/SmemLibXBLLoader.inf
  SpiNorCommonLib|QcomPkg/Library/SpiNorCommonLib/SpiNorCommonLib.inf
  TimetickLib|QcomPkg/Library/TimetickLibB/TimetickLib.inf
  UfsJtagLib|QcomPkg/Library/UfsCommonLib/UfsJtagLib.inf
  UfsLoaderLib|QcomPkg/Library/UfsCommonLib/UfsLoaderLib.inf
  SlvcomLib|QcomPkg/Library/NullLibs/SlvcomLibNull/SlvcomLibNull.inf
  XRCLib|QcomPkg/Library/NullLibs/XRCLibNull/XRCLibNull.inf
  AptLib|QcomPkg/Library/NullLibs/AptLibNull/AptLibNull.inf

  BootSlvcomLib|QcomPkg/Library/NullLibs/BootSlvcomLibNull/boot_slvcomlib_null.inf
  BootXRCLib|QcomPkg/Library/NullLibs/BootXRCLibNull/boot_xrc_null.inf

  # Target Libraries
  BootUtilLib|QcomPkg/XBLLoader/BootUtil/BootUtil.inf

  #DSFTargetLib|QcomPkg/SocPkg/Library/DSFTargetLib/DSFTargetLib.inf
  SpinorCoreTargetLib|QcomPkg/SocPkg/Library/SpinorTargetLib/SpinorCoreTargetLib.inf
  PartitionRWLib|QcomPkg/XBLLoader/PartitionRWLib/PartitionRW.inf
  BootResetLib|QcomPkg/XBLLoader/BootResetLib/BootResetLib.inf
  BootHashLib|QcomPkg/XBLLoader/BootHashLib/BootHashLib.inf

  RamInit|QcomPkg/XBLLoader/RamInit/RamInit.inf
  TimerLib|QcomPkg/LoaderFramework/Timer/Timer.inf
  #ChipInfoLoaderLib|QcomPkg/Library/ChipInfoLib/ChipInfoLoader.inf
  ClockBaseLib|QcomPkg/SocPkg/Library/ClockBaseLib/ClockBaseLib.inf
  #ColdplugLib|QcomPkg/Library/ColdplugLib/ColdplugLib.inf
  VSenseTargetLib|QcomPkg/Library/NullLibs/VSenseTargetLibNull/VSenseTargetLibNull.inf
  XcfgRamLib|QcomPkg/XBLLoader/XBLConfig/XcfgRamLib.inf
  LoaderAptLib|QcomPkg/Library/NullLibs/LoaderAptLibNull/LoaderAptLibNull.inf
  DloadDumpLib|QcomPkg/XBLLoader/DloadDump/DloadDump.inf
  MemoryMgrLib|QcomPkg/XBLLoader/MemoryMgr/MemoryMgr.inf
  RamPartitionLib|QcomPkg/XBLLoader/RamPartition/RamPartition.inf
  MediaInterfaceLib|QcomPkg/XBLLoader/MediaInterface/MediaInterface.inf
  BlockDevLib|QcomPkg/XBLLoader/BlockDev/BlockDev.inf
  EepromDevLib|QcomPkg/XBLLoader/EepromDev/EepromDev.inf
  PageDevLib|QcomPkg/XBLLoader/PageDev/PageDev.inf
  FlashlessSaharaLib|QcomPkg/XBLLoader/FlashlessSahara/FlashlessSahara.inf
  SaharaLogging|QcomPkg/Library/NullLibs/FlashlessSaharaLibNull/SaharaLoggingLibNull.inf
  #SaharaLogging|QcomPkg/XBLLoader/FlashlessSahara/SaharaLogging.inf
  SmcLib|QcomPkg/XBLLoader/SmcLib/Smc.inf
  StorageProfileLib|QcomPkg/Library/StorageCommonLib/StorageProfileStub.inf

  SaharaStatusMapLib|QcomPkg/XBLLoader/SaharaStatusMap/SaharaStatusMap.inf

  TlmmLib|QcomPkg/Library/TlmmLib/TlmmLib.inf
  SmemTargetLib|QcomPkg/SocPkg/Library/SmemTargetLib/SmemTargetLib.inf
  DisplayLib|QcomPkg/Library/NullLibs/DisplayLibNull/DisplayLibNull.inf
  UsbWrapperLayerLib|QcomPkg/SocPkg/Library/UsbWrapperLayerLib/UsbWrapperLayerLib.inf

  BootStatisticsLib|QcomPkg/XBLLoader/BootStatistics/BootStatistics.inf

  LockLib|QcomPkg/Library/LockLib/LockLibNullLoader.inf

  #NULL Target Reset
  TargetResetLib|QcomPkg/Library/NullLibs/TargetResetLibNull/TargetResetLib.inf
  QcomBaseLib|QcomPkg/Library/NullLibs/QcomBaseLibNull/QcomBaseLib.inf
  IoLib|MdePkg/Library/BaseIoLibIntrinsic/BaseIoLibIntrinsic.inf
  #NvmeInterfaceLib|QcomPkg/XBLLoader/NvmeInterface/NvmeInterface.inf
  NvmeLoaderLib|QcomPkg/Library/NullLibs/NvmeLoaderLibNull/NvmeLoaderLibNull.inf

  MhiDeviceLib|QcomPkg/Library/NullLibs/MHILibNull/MHILibNull.inf
  PcieEndpointLib|QcomPkg/Library/NullLibs/PcieEndpointLibNull/PcieEndpointLibNull.inf
  RamdumpTableLib|QcomPkg/XBLLoader/RamdumpTable/RamdumpTable.inf
  RamdumpTableTarget|QcomPkg/SocPkg/Library/RamdumpTableTargetLib/RamdumpTableSM.inf
  BootRecoveryPartitionLib|QcomPkg/Library/NullLibs/BootRecoveryPartitionLibNull/BootRecoveryPartitionLibNull.inf
  BootRecoverySmemLib|QcomPkg/Library/NullLibs/BootRecoverySmemLibNull/BootRecoverySmemLibNull.inf

  SaharaCommandHandlerLib|QcomPkg/XBLLoader/SaharaCommandHandler/SaharaCommandHandler.inf
  SaharaDispatchTableLib|QcomPkg/XBLLoader/SaharaDispatchTable/SaharaDispatchTable.inf

################################################################################
#
# Pcd Section - list of all EDK II PCD Entries defined by this Platform
#
################################################################################

[PcdsFeatureFlag.common]

[PcdsFixedAtBuild.common]

#
# Target Specific PCDs
#
  #################################
  ## PcdSmemBaseAddress is currently used by smem library
  #################################
  gQcomTokenSpaceGuid.PcdSmemBaseAddress|0x80900000  #64-bit smem addr
  gQcomTokenSpaceGuid.PcdSmemSize|0x00200000         # 2MB
  ## Generic SMEM information that SMEM lib might need
  ## LSB represents chip family, other bytes are unused for now.
  gQcomTokenSpaceGuid.PcdSmemInformation|0x00000005  # 5 = Nazgul

  # Timers
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|19200000
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|29
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|30
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x9BC0000
  gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0x65C0000
  gQcomTokenSpaceGuid.PcdQTimerAC_BasePhys|0x17C20000
  gQcomTokenSpaceGuid.PcdQTimerV1BasePhys|0x17C21000
  gQcomTokenSpaceGuid.PcdQTimerV2BasePhys|0x17C22000
  gQcomTokenSpaceGuid.PcdQTimerFrame|0
  gQcomTokenSpaceGuid.PcdQTimerEnabled|1

  #IPCC
  gQcomTokenSpaceGuid.PcdIPCCLibProtocol|0
  gQcomTokenSpaceGuid.PcdIPCCLibLocalClient|8
  gQcomTokenSpaceGuid.PcdIPCCLibTotalSignals|4

  # SDCC
  gQcomTokenSpaceGuid.SDCCExtSlotNumber|1
  gQcomTokenSpaceGuid.SDCCEmmcSlotNumber|0
  gQcomTokenSpaceGuid.SDCCRpmbKey|{0x20, 0xAA, 0x9C, 0xF4, 0x99, 0x4D, 0xD4, 0xFE, 0xA5, 0x85, 0xBE, 0x96, 0x6, 0x1, 0xD1, 0xA9, 0xC3, 0x3, 0x4F, 0x91, 0x62, 0x7C, 0x64, 0x53, 0x38, 0xC1, 0x1F, 0xF2, 0x76, 0x4D, 0x2E, 0xC4}
  gQcomTokenSpaceGuid.SDCCEventBasedSDDetectEnabled|FALSE
  gQcomTokenSpaceGuid.SDCCDmaEnabled|TRUE
  gQcomTokenSpaceGuid.SDCCEmmcHwResetEnabled|TRUE
  gQcomTokenSpaceGuid.SDCCMaxSlotNumber|2
  gQcomTokenSpaceGuid.SDCCSdhciEnable|TRUE
  ## SDCC eMMC speed mode - DDR50: 0, HS200: 1, HS400: 2 SDR: 3 ##
  gQcomTokenSpaceGuid.SDCCEmmcSpeedMode|1


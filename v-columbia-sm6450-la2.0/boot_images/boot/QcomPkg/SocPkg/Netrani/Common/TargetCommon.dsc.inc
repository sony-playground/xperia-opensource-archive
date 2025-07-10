#==============================================================================
# @file TargetCommon.dsc.inc
# Netrani Loader images common libraries.
#
# Copyright (c) 2017 - 2020 Qualcomm Technologies, Inc. All rights reserved.
# Portions Copyright (c) 2009 - 2010, Apple Inc. All rights reserved.
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#==============================================================================


!include QcomPkg/SocPkg/Common/Common.dsc.inc
!include QcomPkg/SocPkg/Netrani/$(VAR)/Variant.dsc.inc
[LibraryClasses.common]
  MemoryAllocationLib|QcomPkg/Library/LdrAllocPg/LdrAllocPg.inf
  UartSettingsLib|QcomPkg/SocPkg/Netrani/Settings/UART/UartSettingsLib.inf
  DALGenLibLoader|QcomPkg/SocPkg/Netrani/Settings/DALConfig/DALGenLibLoader_LA.inf
  DALConfigLoaderLib|QcomPkg/SocPkg/Netrani/Settings/DALConfig/DALConfigLoaderLib_LA.inf
  SpiNorCommonLib|QcomPkg/Library/NullLibs/SpiNorCommonLibNull/SpiNorCommonNullLib.inf
  UfsTargetBootLib|QcomPkg/SocPkg/Netrani/Library/UfsTargetLib/UfsTargetBootLib.inf
  UfsTargetJtagLib|QcomPkg/SocPkg/Netrani/Library/UfsTargetLib/UfsTargetJtagLib.inf
  IcbTargetLib|QcomPkg/SocPkg/Netrani/Library/ICBTargetLib/ICBTargetLib.inf
  IcbCfgLib|QcomPkg/Library/ICBLib/ICBLib.inf
  DTBExtnLib|QcomPkg/Library/DTBExtnLib/DTBExtnLib.inf
  ChipInfoTargetLib|QcomPkg/SocPkg/Netrani/Library/ChipInfoTargetLib/ChipInfoTargetLib.inf
  TLMMTargetLib|QcomPkg/SocPkg/Netrani/Library/TLMMTargetLib/TLMMTargetLib.inf
 #ClockTargetLib|QcomPkg/SocPkg/Lahaina/Library/ClockTargetLib/ClockTargetLib.inf
  ClockTargetLib|QcomPkg/SocPkg/Netrani/Library/ClockTargetLib/ClockTargetLib.inf
  BootPblSharedDataLib|QcomPkg/SocPkg/Library/BootPblSharedDataLib/boot_pbl_v1/BootPblSharedDataLib.inf
  SmemLib|QcomPkg/Library/SmemLib/build/SmemLibXBLLoaderCommon.inf

 QusbTargetLib|QcomPkg/SocPkg/Netrani/Library/QusbTargetLib/QusbTargetLib.inf
 #QusbTargetLib|QcomPkg/Library/NullLibs/QusbTargetLibNull/QusbTargetLibNull.inf
 QusbDciCommonLib|QcomPkg/SocPkg/Netrani/Library/QusbDciCommonLib/QusbDciCommonLib.inf
 #QusbDciCommonLib|QcomPkg/Library/NullLibs/QusbDciCommonLibNull/QusbDciCommonLibNull.inf

 UsbSharedLib|QcomPkg/SocPkg/Netrani/Library/UsbSharedLib/UsbSharedLibLoader.inf
 #UsbSharedLib|QcomPkg/Library/NullLibs/UsbSharedLibNull/UsbSharedLibLoaderNull.inf

 TsensTargetLib|QcomPkg/SocPkg/Netrani/Library/TsensTargetLib/TsensTargetLib.inf
 #TsensTargetLib|QcomPkg/Library/NullLibs/TsensTargetLibNull/TsensTargetLibNull.inf

  SdccTargetLib|QcomPkg/SocPkg/Netrani/Library/SdccTargetLib/SdccLoaderTargetLib.inf
  SdccClockLib|QcomPkg/SocPkg/Netrani/Library/SdccClockLib/SdccLoaderClockLib.inf
  
  SPMILib|QcomPkg/SocPkg/Netrani/Library/SPMILib/SPMILib.inf
  SPMILibDebugNull|QcomPkg/Library/NullLibs/SPMILibNull/SPMILibDebugNull.inf

 #CPRTargetLib|QcomPkg/Library/NullLibs/PowerLibNull/CprLibNull.inf
 CPRTargetLib|QcomPkg/SocPkg/Netrani/Library/CPRTargetLib/Loader/CPRTargetLib.inf

 #RailwayTargetLib|QcomPkg/Library/NullLibs/RailwayLibNull/RailwayLibNull.inf
  RailwayTargetLib|QcomPkg/SocPkg/Netrani/Library/RailwayTargetLib/RailwayTargetLib.inf

  #PrngLib|QcomPkg/SocPkg/Library/RNGLoaderLib/RNGLibHw.inf
  PrngLib|QcomPkg/Library/NullLibs/RNGLibNull/RNGLibSwNull.inf
  I2CFWImageLib|QcomPkg/SocPkg/Netrani/Settings/I2C/I2CFWImageLib.inf
  #I2CFWImageLib|QcomPkg/Library/NullLibs/I2CFWImageLibNull/I2CFWImageLib.inf
 SPIFWImageLib|QcomPkg/SocPkg/Netrani/Settings/SPI/SPIFWImageLib.inf
  #SPIFWImageLib|QcomPkg/Library/NullLibs/SPIFWImageLibNull/SPIFWImageLibNull.inf

  RMBLib|QcomPkg/SocPkg/Library/RMBLib/RMBLib.inf
  FdtLib|EmbeddedPkg/Library/FdtLib/FdtLib.inf
  
  MediaInitializationLib|QcomPkg/XBLLoader/MediaInitializationLib/MediaInitialization.inf

[BuildOptions.AARCH64]
  GCC:*_*_AARCH64_ARCHCC_FLAGS  == -mllvm -inline-threshold-multicaller-size=20 -mtune=cortex-a53 -DMDEPKG_NDEBUG -DQCOM_EDK2_PATCH -DFEATURE_SET_IMEM_SECURE_REG_RD_ONLY $(FEATURE_FLAGS) -I$(WORKSPACE)/QcomPkg/SocPkg/Include -I$(WORKSPACE)/QcomPkg/SocPkg/Netrani/Include -include $(WORKSPACE)/QcomPkg/SocPkg/Netrani/Include/Target_cust.h
  GCC:*_*_AARCH64_ARCHPP_FLAGS  == -DMDEPKG_NDEBUG -DQCOM_EDK2_PATCH -DFEATURE_SET_IMEM_SECURE_REG_RD_ONLY $(FEATURE_FLAGS) -I$(WORKSPACE)/QcomPkg/SocPkg/Include -I$(WORKSPACE)/QcomPkg/SocPkg/Netrani/Include -include $(WORKSPACE)/QcomPkg/SocPkg/Netrani/Include/Target_cust.h

!if $(PRODMODE) == "PRODMODE"
  GCC:*_*_*_CC_FLAGS = -DPRODMODE
!endif


[PcdsFeatureFlag.common]
[PcdsFixedAtBuild.common]
  gQcomTokenSpaceGuid.PcdQTimerAC_BasePhys|0x17420000      # APSS_QTMR0_QTMR_AC
  gQcomTokenSpaceGuid.PcdQTimerV1BasePhys|0x17421000       # APSS_QTMR0_F0V1_QTMR_V1
  gQcomTokenSpaceGuid.PcdQTimerV2BasePhys|0x17422000       # APSS_QTMR0_F0V2_QTMR_V2

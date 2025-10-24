#==============================================================================
# @file Core.dsc
# Kailua Core package.
#
# Copyright (c) 2019 Qualcomm Technologies, Inc. All rights reserved.
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

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = KailuaPkg
  PLATFORM_GUID                  = 74ED6F00-C570-4D61-8952-0EE3863CFE1B
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = QcomPkg/SocPkg/Kailua/LAA/Core.fdf

[Defines.ARM]
  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Kailua$(VAR)/Core_32

[Defines.AARCH64]
  OUTPUT_DIRECTORY               = $(BUILDROOT)/Build/Kailua$(VAR)/Core

[PcdsFeatureFlag.common]
  gQcomTokenSpaceGuid.PcdUefiEnhanced|0

!include QcomPkg/SocPkg/Kailua/Common/Core.dsc.inc

!ifdef FEATURE_XBOOT
#
# SOMC Modules need to be added here
#
[LibraryClasses]
  # XUtil Library
  XUtilLib|SomcPkg/Library/XUtilLib/XUtilUEFILib.inf
  # XDebug Library
  XDebugLib|SomcPkg/Library/XDebugLib/XDebugUEFILib.inf
  # XHwreset Library
  XHwresetLib|SomcPkg/Platform/SomcSm8550Pkg/Library/XHwresetLib/XHwresetLib.inf
  # XSDI Library
  XSDILib|SomcPkg/Platform/SomcQcomCmnPkg/Library/XSDILib/XSDILibNull.inf
  # Maze Library
  MazeLib|SomcPkg/Library/MazeLib/MazeLib.inf
  # XResetReasonApi Library
  XResetReasonApiLib|SomcPkg/Library/XResetReasonApiLib/XResetReasonApiLib.inf
  # XResetReason Library
  XResetReasonLib|SomcPkg/Platform/SomcQcomCmnPkg/Library/XResetReasonLib/XResetReasonLib.inf
  # TaLib Library
  TaLib|SomcPkg/Platform/SomcQcomCmnPkg/Library/TaLib/TaLib.inf
  # XRtcAlarm Library
  XRtcAlarmLib|SomcPkg/Platform/SomcQcomCmnPkg/Library/XRtcAlarmLib/XRtcAlarmLib.inf
  # XVibratorLib
  XVibratorLib|SomcPkg/Platform/SomcQcomCmnPkg/Library/XVibratorLib/XVibratorLibNull.inf
  # XHapticsLib
  XHapticsLib|SomcPkg/Platform/SomcSm8550Pkg/Library/XHapticsLib/XHapticsLib.inf
  # XBootPALLib Library
  XBootPALLib|SomcPkg/Platform/SomcSm8550Pkg/Library/XBootPALLib/XBootPALLib.inf
  # RTCPrintLib
  RTCPrintLib|SomcPkg/Platform/SomcQcomCmnPkg/Library/RTCPrintLib/RTCPrintLib.inf
  # ResetCfgLib
  ResetCfgLib|SomcPkg/Platform/SomcQcomCmnPkg/Library/ResetCfgLib/ResetCfgLib.inf
  # SetChargerLib
  SetChargerLib|SomcPkg/Platform/SomcQcomCmnPkg/Library/SetChargerLib/SetChargerLib.inf
  # XBootDisplayLib
  XBootDisplayLib|SomcPkg/Library/XBootDisplayLib/XBootDisplayLib.inf
  # XLcdIdApiLib Library
  XLcdIdApiLib|SomcPkg/Library/XLcdIdApiLib/XLcdIdApiLib.inf
  # XBootPanelLib Library
  XBootPanelLib|SomcPkg/Platform/SomcSm8550Pkg/Library/XBootPanelLib/XBootPanelLib.inf

[Components]
  # XHwresetDxe Driver
  SomcPkg/Platform/SomcQcomCmnPkg/Drivers/XHwresetDxe/XHwresetDxe.inf {
    <LibraryClasses>
      PmicCoreLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/core/la/PmicCoreLib.inf
      PmicLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/PmicLib.inf
  }
  # MazeDetDxe Driver
  SomcPkg/Drivers/MazeDetDxe/MazeDetDxe.inf
  # XResetReasonDxe Driver
  SomcPkg/Drivers/XResetReasonDxe/XResetReasonDxe.inf
  # TaDxe Driver
  SomcPkg/Drivers/TaDxe/TaDxe.inf
  # XBootPALDxe Driver
  SomcPkg/Drivers/XBootPALDxe/XBootPALDxe.inf
  # ResetCfgDxe Driver
  SomcPkg/Platform/SomcQcomCmnPkg/Drivers/ResetCfgDxe/ResetCfgDxe.inf {
    <LibraryClasses>
      PmicCoreLib|QcomPkg/SocPkg/Kailua/Library/PmicLib/core/la/PmicCoreLib.inf
      SPMILibDebugNull|QcomPkg/Library/NullLibs/SPMILibNull/SPMILibDebugNull.inf
  }
  # SoumenDxe Driver
  SomcPkg/Platform/SomcQcomCmnPkg/Drivers/SoumenDxe/SoumenDxe.inf

  # XGraphicImages (XGI)
  SomcPkg/Platform/SomcQcomCmnPkg/Drivers/XGraphicImagesDxe/XGraphicImagesDxe.inf

  # XGAdcDxe Driver
  SomcPkg/Platform/SomcQcomCmnPkg/Drivers/XGAdcDxe/XGAdcDxe.inf

### special XLogLib classes begin ###

# XLogCustLib.inf produces XLogLibCust class; for SEC and DXE
# This class is trick path for log.buf from SBL1 to UEFI env
[LibraryClasses.common.SEC.USES_FEATURE_XBOOT]
  XLogLibCust|SomcPkg/Platform/SomcQcomCmnPkg/Library/XLogLib/XLogCustLib.inf
[LibraryClasses.common.DXE_DRIVER.USES_FEATURE_XBOOT]
  XLogLibCust|SomcPkg/Platform/SomcQcomCmnPkg/Library/XLogLib/XLogCustLib.inf

# XLogOpenBufLib.inf produces XLogLibOpenBuf class; declared only in SEC;
# This class provides some cutomization for Cache.c
[LibraryClasses.common.SEC.USES_FEATURE_XBOOT]
  XLogLibOpenBuf|SomcPkg/Platform/SomcQcomCmnPkg/Library/XLogLib/XLogOpenBufLib.inf

# XLogHookLib.inf consumes SerialPortLib(SerialPortLib.inf for
# SerialPortShLibImpl.c, not SerialPortShLib.inf)
# XLogHookLib.inf produces XLogLibHook class; declared only in SEC;
# This class provides hook-point to capture serial-port-write
[LibraryClasses.common.SEC.USES_FEATURE_XBOOT]
  XLogLibHook|SomcPkg/Platform/SomcQcomCmnPkg/Library/XLogLib/XLogHookLib.inf

# XLogSaveLib.inf produces XLogLibSave class; for PlatformBDS-DXE
[LibraryClasses.common.DXE_DRIVER.USES_FEATURE_XBOOT]
  XLogLibSave|SomcPkg/Platform/SomcQcomCmnPkg/Library/XLogLib/XLogSaveLib.inf

### special XLogLib classes end ###
!endif # FEATURE_XBOOT

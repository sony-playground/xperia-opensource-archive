# @file Apriori.fdf.inc
# Apriori for LA Kailua
#
# Copyright (c) 2022 Qualcomm Technologies, Inc. All rights reserved.
# Portions Copyright (c) 2009, Apple Inc. All rights reserved.
# This program and the accompanying materials
# are licensed and made available under the terms and conditions of the BSD License
# which accompanies this distribution.  The full text of the license may be found at
# http://opensource.org/licenses/bsd-license.php
#
# THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
# WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#
#
#==============================================================================

########################### APRIORI Start ####################################################
## Load order for drivers ##
## NOTE: After the APRIORI End section is where drivers must be added in order for them to
##       be included in the FD. The APRIORI just dictates a load order regardless of whether
##       the drivers are actually included in the FD or not
#
#    Arch Protocols:
#    EfiSecurityArchProtocolGuid,
#    EfiCpuArchProtocolGuid,
#    EfiMetronomeArchProtocolGuid,
#    EfiTimerArchProtocolGuid,
#    EfiBdsArchProtocolGuid,
#    EfiWatchdogTimerArchProtocolGuid,
#    EfiRuntimeArchProtocolGuid,
#    EfiVariableArchProtocolGuid,
#    EfiVariableWriteArchProtocolGuid,
#    EfiCapsuleArchProtocolGuid,
#    EfiMonotonicCounterArchProtocolGuid,
#    EfiResetArchProtocolGuid,
#    EfiRealTimeClockArchProtocolGuid,


  APRIORI DXE {
        INF MdeModulePkg/Core/Dxe/DxeMain.inf
!ifdef FEATURE_XBOOT
        INF SomcPkg/Drivers/MazeDetDxe/MazeDetDxe.inf
!endif # FEATURE_XBOOT
        INF QcomPkg/Drivers/EnvDxe/EnvDxe.inf
        INF MdeModulePkg/Universal/ReportStatusCodeRouter/RuntimeDxe/RscRtDxe.inf
        INF MdeModulePkg/Universal/StatusCodeHandler/RuntimeDxe/SCHandlerRtDxe.inf
        INF MdeModulePkg/Core/RuntimeDxe/RuntimeDxe.inf
        INF ArmPkg/Drivers/CpuDxe/CpuDxe.inf
        INF ArmPkg/Drivers/ArmGic/ArmGicDxe.inf
        INF EmbeddedPkg/MetronomeDxe/MetronomeDxe.inf
        INF ArmPkg/Drivers/TimerDxe/TimerDxe.inf
        INF QcomPkg/Drivers/SmemDxe/SmemDxe.inf
#DEP: DAL depends on SMEM
        INF QcomPkg/Drivers/DALSYSDxe/DALSYSDxe.inf
        INF QcomPkg/Drivers/HWIODxe/HWIODxe.inf
        INF QcomPkg/Drivers/ChipInfoDxe/ChipInfoDxe.inf
        INF QcomPkg/Drivers/PlatformInfoDxe/PlatformInfoDxe.inf
        INF QcomPkg/Drivers/HALIOMMUDxe/HALIOMMUDxe.inf
        INF QcomPkg/Drivers/ULogDxe/ULogDxe.inf
        INF QcomPkg/Drivers/IPCCDxe/IPCCDxe.inf
        INF QcomPkg/Drivers/GLinkDxe/GLinkDxe.inf
        INF QcomPkg/Drivers/CmdDbDxe/CmdDbDxe.inf
        INF QcomPkg/Drivers/PwrUtilsDxe/PwrUtilsDxe.inf
        INF QcomPkg/Drivers/NpaDxe/NpaDxe.inf
         INF QcomPkg/Drivers/RpmhDxe/RpmhDxe.inf
        INF QcomPkg/Drivers/VcsDxe/VcsDxe.inf
#DEP: Clock Driver depends on Glink
        INF QcomPkg/Drivers/ClockDxe/ClockDxe.inf
#        INF QcomPkg/Drivers/NULLClockDxe/NULLClockDxe.inf
#        INF QcomPkg/Drivers/ClockDxe/ClockDriverTestInterface/ClockTestInterface.inf        
        INF QcomPkg/Drivers/ICBDxe/ICBDxe.inf
        INF QcomPkg/Drivers/ShmBridgeDxe/ShmBridgeDxeLA.inf
#        INF QcomPkg/Drivers/TzDxe/ScmDxeLA.inf
        INF QcomPkg/Drivers/TzDxe/ScmDxeLA_Kailua.inf
        INF QcomPkg/Drivers/TLMMDxe/TLMMDxe.inf
        INF QcomPkg/Drivers/I2CDxe/I2CDxe.inf
        INF QcomPkg/Drivers/SPMIDxe/SPMIDxe.inf
# --PRESIL--
# DEP: PMIC depends on I2C and TLMM
#       INF QcomPkg/Drivers/PmicDxe/NullLib/PmicDxeNull.inf
        INF QcomPkg/Drivers/ResetRuntimeDxe/ResetRuntimeDxe.inf
        INF QcomPkg/Drivers/PmicDxe/PmicDxeLa.inf
        INF MdeModulePkg/Universal/Disk/DiskIoDxe/DiskIoDxe.inf
        INF MdeModulePkg/Universal/Disk/PartitionDxe/PartitionDxe.inf
        INF MdeModulePkg/Universal/Disk/UnicodeCollation/EnglishDxe/EnglishDxe.inf
        INF MdeModulePkg/Universal/FvSimpleFileSystemDxe/FvSimpleFileSystemDxe.inf
        INF QcomPkg/Drivers/SdccDxe/SdccDxe.inf
        INF QcomPkg/Drivers/UFSDxe/UFSDxe.inf
        INF FatPkg/EnhancedFatDxe/Fat.inf
        INF QcomPkg/Drivers/TzDxe/TzDxeLA.inf
# --PRESIL--
#       INF QcomPkg/Drivers/VariableDxe/EmuRuntimeDxe/EmuVariableRuntimeDxe.inf
        INF QcomPkg/Drivers/VariableDxe/VariableDxe.inf
        INF QcomPkg/Drivers/QcomWDogDxe/QcomWDogDxe.inf
        INF QcomPkg/Drivers/DDRInfoDxe/DDRInfoDxe.inf
#DEP: DisplayDxe depends on storage, filesystem, variable services
        INF QcomPkg/Drivers/FeatureEnablerDxe/FeatureEnablerDxe.inf
!ifdef FEATURE_XBOOT
        # XGAdcDxe and PmicDxeLa(AdcDxe) are used in Display initialization. Need to load them before DisplayDxe
        INF SomcPkg/Platform/SomcQcomCmnPkg/Drivers/XGAdcDxe/XGAdcDxe.inf
!endif # FEATURE_XBOOT
        INF QcomPkg/Drivers/DisplayDxe/DisplayDxe.inf
        INF QcomPkg/Drivers/FvUtilsDxe/FvUtilsDxe.inf
        INF QcomPkg/Drivers/QRKSDxe/QRKSDxe.inf
#DEP: PIL depends on FvUtils
        INF QcomPkg/Drivers/PILProxyDxe/PILProxyDxe.inf
         INF QcomPkg/Drivers/PILDxe/PILDxe.inf
        INF QcomPkg/Drivers/SPSSDxe/SPSSDxe.inf
        INF MdeModulePkg/Universal/WatchdogTimerDxe/WatchdogTimer.inf
        INF MdeModulePkg/Universal/SecurityStubDxe/SecurityStubDxe.inf
        INF QcomPkg/Drivers/EmbeddedMonotonicCounter/EmbeddedMonotonicCounter.inf
        INF EmbeddedPkg/RealTimeClockRuntimeDxe/RealTimeClockRuntimeDxe.inf
        INF MdeModulePkg/Universal/PrintDxe/PrintDxe.inf
        INF MdeModulePkg/Universal/DevicePathDxe/DevicePathDxe.inf
        INF MdeModulePkg/Universal/CapsuleRuntimeDxe/CapsuleRuntimeDxe.inf
        INF MdeModulePkg/Universal/HiiDatabaseDxe/HiiDatabaseDxe.inf
        INF QcomPkg/Drivers/FontDxe/FontDxe.inf
#DEP: HIIdb and Fonts are BDS dependencies
        INF QcomPkg/Drivers/QcomBds/QcomBds.inf
        INF QcomPkg/Drivers/SPIDxe/SPIDxe.inf
        INF QcomPkg/Drivers/PmicGlinkDxe/PmicGlinkDxe.inf
#DEP: UsbPwrCtrl depends on I2C
        INF QcomPkg/Drivers/UsbPwrCtrlDxe/UsbPwrCtrlDxe.inf
        INF QcomPkg/Drivers/QcomChargerDxe/QcomChargerDxeLA.inf
# --PRESIL--
#        INF QcomPkg/Drivers/ChargerExDxe/NullLib/ChargerExDxeNull.inf
        INF QcomPkg/Drivers/ChargerExDxe/ChargerExDxe.inf
        INF QcomPkg/Drivers/UsbfnDwc3Dxe/UsbfnDwc3Dxe.inf
        INF QcomPkg/Drivers/XhciPciEmulationDxe/XhciPciEmulationDxe.inf
        INF QcomPkg/Drivers/XhciDxe/XhciDxe.inf
        INF QcomPkg/Drivers/UsbBusDxe/UsbBusDxe.inf
        INF QcomPkg/Drivers/UsbKbDxe/UsbKbDxe.inf
        INF QcomPkg/Drivers/UsbMassStorageDxe/UsbMassStorageDxe.inf
        INF QcomPkg/Drivers/UsbConfigDxe/UsbConfigDxe.inf
        INF QcomPkg/Drivers/ButtonsDxe/ButtonsDxe.inf
        INF QcomPkg/Drivers/TsensDxe/TsensDxe.inf
#DEP: Limits should run _before_ CPR
        INF QcomPkg/Drivers/LimitsDxe/LimitsDxe.inf
#DEP: CPR depends on CmdDb, Rpmh, Display
		 INF QcomPkg/Drivers/CPRDxe/CPRDxe.inf
        INF QcomPkg/Drivers/GpiDxe/GpiDxe.inf
        INF QcomPkg/Drivers/UCDxe/UCDxe.inf
        INF QcomPkg/Drivers/RNGDxe/RngDxe.inf
        INF QcomPkg/Drivers/SimpleTextInOutSerialDxe/SimpleTextInOutSerial.inf
        INF MdeModulePkg/Universal/Console/ConPlatformDxe/ConPlatformDxe.inf
        INF MdeModulePkg/Universal/Console/ConSplitterDxe/ConSplitterDxe.inf
        INF MdeModulePkg/Universal/Console/GraphicsConsoleDxe/GraphicsConsoleDxe.inf
        INF QcomPkg/Drivers/ASN1X509Dxe/ASN1X509Dxe.inf
        INF QcomPkg/Drivers/SecRSADxe/SecRSADxe.inf
# --PRESIL--
#        INF QcomPkg/Drivers/VerifiedBootNullDxe/VerifiedBootNullDxe.inf
        INF QcomPkg/Drivers/VerifiedBootDxe/VerifiedBootDxe.inf

#        INF QcomPkg/Drivers/AdcDxe/AdcDxe.inf
		INF QcomPkg/Drivers/RscDxe/RscDxe.inf
  }

#
########################### APRIORI End ####################################################
#


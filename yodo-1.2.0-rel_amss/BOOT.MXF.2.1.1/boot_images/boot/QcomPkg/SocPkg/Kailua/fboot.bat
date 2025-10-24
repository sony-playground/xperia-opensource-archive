:: @file fboot.bat
:: Batch file to easily flash necessary binaries to partitions
::
:: Copyright (c) 2016-2018 Qualcomm Technologies, Inc. All rights reserved.
::===========================================================================
:: when       who     what, where, why
:: --------   ---     -------------------------------------------------------
:: 05/24/18   vk      Add reboot option, fix binary path
:: 09/06/17   yps     Removed Pmic 
:: 05/05/16   bh      Initial revision
::
::===========================================================================
@ECHO off



if /I "%1"=="LAA" (
  set VARIANT=LAA
  set XBL_PART=xbl
  set XBLCFG_PART=xbl_config
  set SHRM_PART=shrm
  set XBL_RAMDUMP_PART=xbl_ramdump
  set UEFI_PART=uefi
) else if /I "%1"=="LAB" (
  set VARIANT=LAB
  set XBL_PART=xbl
  set XBLCFG_PART=xbl_config
  set SHRM_PART=shrm
) else (
  echo Usage: "fboot <variant> [test] [r]" where variant is LA or WP
  echo Options:
  echo               variant  Flash specified variant
  echo               test     Flash test or tools fv
  echo               r        Reboot device after flashing
  goto Exit
)

:: Default options
set REBOOT_AFTER_FLASH="FALSE"
set TOOLSFV_ELF=..\..\QcomToolsPkg\Bin\QcomTools\DEBUG\tools.fv
set CATEFV_ELF=..\..\QcomCatePkg\Bin\QcomCate\DEBUG\QcomCate.fv

:: Override default options from command line
if /I "%2"=="TEST" (
  set TOOLSFV_ELF=..\..\QcomTestPkg\Bin\QcomTest\DEBUG\tests.fv
) else if /I "%2"=="CORETEST" (
  set TOOLSFV_ELF=..\..\QcomSocPlatTestPkg\Bin\QcomSocPlatTest\DEBUG\soc_tests.fv
) else if /I "%2"=="R" (
  set REBOOT_AFTER_FLASH="TRUE"
)

if /I "%3"=="R" (
  set REBOOT_AFTER_FLASH="TRUE"
) 

echo Running fastboot tool ...
echo ---------------------
echo Variant: %VARIANT%

:: Check for device
fastboot.exe devices | find /I "fastboot"
if not errorlevel 1 (
  echo Device found ! 
) else (
  echo ERROR: No device connected ! Check cable !
  goto Exit
)

fastboot.exe flash %XBL_PART% Bin\%VARIANT%\DEBUG\xbl_s.melf
if ERRORLEVEL 1 (
set Failed_part=%XBL_PART%
goto Failure
)
echo ---------------------
echo Flashed XBL ...
echo ---------------------

fastboot.exe flash %XBLCFG_PART% Bin\%VARIANT%\DEBUG\xbl_config.elf
if ERRORLEVEL 1 (
set Failed_part=%XBLCFG_PART%
goto Failure
)

echo ---------------------
echo Flashed XBL CONFIG ...
echo ---------------------

fastboot.exe flash %SHRM_PART% Bin\%VARIANT%\DEBUG\shrm.elf
if ERRORLEVEL 1 (
set Failed_part=%SHRM_PART%
goto Failure
)

echo ---------------------
echo Flashed SHRM ...
echo ---------------------

fastboot.exe flash %XBL_RAMDUMP_PART% Bin\%VARIANT%\DEBUG\XblRamdump.elf
if ERRORLEVEL 1 (
set Failed_part=%XBL_RAMDUMP_PART%
goto Failure
)

echo ---------------------
echo Flashed XBL Ramdump ...
echo ---------------------

fastboot.exe flash %UEFI_PART% Bin\%VARIANT%\DEBUG\uefi.elf
if ERRORLEVEL 1 (
set Failed_part=%UEFI_PART%
goto Failure
)

echo ---------------------
echo Flashed UEFI ...
echo ---------------------


echo toolsfv FV image: %TOOLSFV_ELF%
fastboot.exe flash toolsfv %TOOLSFV_ELF%
if ERRORLEVEL 1 (
set Failed_part=toolsfv
goto Failure
)
echo ----------------------------------
echo Flashed "toolsfv" partition ...
echo ----------------------------------

fastboot.exe flash imagefv Bin\%VARIANT%\DEBUG\imagefv.elf
if ERRORLEVEL 1 (
set Failed_part=ImageFv
goto Failure
)
echo ----------------------------------
echo Flashed "ImageFv" partition ...
echo ----------------------------------

echo catefv FV image: %CATEFV_ELF%
fastboot.exe flash catefv %CATEFV_ELF%
if ERRORLEVEL 1 (
set Failed_part=catefv
goto Failure
)
echo ----------------------------------
echo Flashed "catefv" partition ...
echo ----------------------------------

echo SUCCESS
goto Exit

:Failure
echo ---------------------
echo Warning: Failed to flash %Failed_part% build
EXIT /B %ERRORLEVEL%

:Exit
if /I %REBOOT_AFTER_FLASH%=="TRUE" (
  echo Rebooting device ...
  fastboot.exe reboot
) else (
  echo No reboot ...
)

EXIT /B 0


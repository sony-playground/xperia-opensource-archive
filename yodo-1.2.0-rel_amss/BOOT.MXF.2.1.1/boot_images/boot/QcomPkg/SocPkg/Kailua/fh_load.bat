@echo off


if /I "%1"=="LAA" (
  set VARIANT=LAA
  set XBL_PART=xbl
  set XBLCFG_PART=xbl_config
  set RAMDUMP_PART=xbl_ramdump
) else if /I "%1"=="LAB" (
  set VARIANT=LAB
  set XBL_PART=XBL
  set XBLCFG_PART=XBL_CONFIG
  set RAMDUMP_PART=xbl_ramdump
) else if /I "%1"=="AU" (
  set VARIANT=AU
  set XBL_PART=xbl
  set XBLCFG_PART=xbl_config
  set RAMDUMP_PART=xbl_ramdump
) else (
  echo Usage: "fh_load <variant> [f]" where variant is LA or WP or AU
  echo Usage: "fh_load <variant> [t]" where variant is LA or WP or AU
  echo Options:
  echo               variant  Flash specified variant
  echo               f        Flash - do not query for builds, use from log files generated in previous run
  echo               t        Test  - Use device programmer from current build
  echo               l        Send  - Send device programmer lite, if d option send ddr
  echo               s        Send  - Send device programmer from current build and exit, no flashing
  goto Exit
)


set FLASH_MODE="FALSE"
set TEST_MODE="FALSE"
set SEND_MODE="FALSE"
set SEND_LITE="FALSE"
set boot_build_path=

:: Override default options from command line
if /I "%2"=="F" (
  set FLASH_MODE="TRUE"
)
   
if /I "%2"=="T" (
  set TEST_MODE="TRUE"
) 

if /I "%3"=="L" (
  set SEND_LITE="TRUE"
)

if /I "%3"=="D" (
  set SEND_LITE="FALSE"
)

if /I "%4"=="S" (
  set SEND_MODE="TRUE"
)
    
del /f /q %TEMP%\port.log

..\..\Tools\Storage\fh_loader\lsusb.exe | findstr "QDLoader 9008" > %TEMP%\port.log
:: type %TEMP%\port.log

for /f %%i in ("%TEMP%\port.log") do set size=%%~zi
if %size% equ 0 (
  echo ERROR: No device detected in EDL.
  goto ExitError
)

set /p port_string=<%TEMP%\port.log
set port_number=%port_string:~31,-1%
echo Detected  device in EDL on %port_number%
echo Variant is [%VARIANT%]

if /I %FLASH_MODE%=="TRUE" (
  for /f %%i in ("%TEMP%\boot_build.log") do set size=%%~zi
  if %size% equ 0 (
    echo ERROR: Unable to find boot build
    goto ExitError
  )

  set /p boot_build_path=<%TEMP%\boot_build.log
  goto SkipFindBuildBootCRM
)

if /I %TEST_MODE%=="FALSE" (
  echo Not test mode, using device programmer from latest approved CRM
  if /I "%VARIANT%"=="LAA" (
    echo Findbuild for LAA boot CRM 
    \\stone\aswcrm\smart\nt\bin\findbuild.exe -in=location -la -ap BOOT.MXF.2.1-?????-KAILUA-? > %TEMP%\boot_build.log
  ) else if /I "%VARIANT%"=="LAB" (  
    echo Findbuild for LAB boot CRM 
    \\stone\aswcrm\smart\nt\bin\findbuild.exe -in=location -la -ap BOOT.MXF.2.1-?????-KAILUA-? > %TEMP%\boot_build.log
  ) else (
    echo Variant not specified
    goto ExitError
  )
  
  for /f %%i in ("%TEMP%\boot_build.log") do set size=%%~zi
  if %size% equ 0 (
    echo ERROR: Unable to find boot build
    goto ExitError
  )

  set /p boot_build_path=<%TEMP%\boot_build.log
) else if /I %TEST_MODE%=="TRUE" (
  echo Test mode, using device programmer from current build
  set boot_build_path=%cd%\..\..\..\..\..\
)

:SkipFindBuildBootCRM
echo Boot build path: "%boot_build_path%"

echo SEND_LITE=%SEND_LITE%
echo SEND_MODE=%SEND_MODE%

if /I %SEND_LITE%=="TRUE" (
  echo Send device programmer lite ...
  %boot_build_path%\boot_images\boot_tools\QSaharaServer\QSaharaServer.exe -b %boot_build_path%\boot_images\boot\QcomPkg\SocPkg\Kailua\Bin\%VARIANT%\DEBUG\ -s 13:xbl_s_devprg_ns.melf -p \\.\%port_number%
) 

if /I %SEND_LITE%=="FALSE" (
  echo Send device programmer DDR ...
  %boot_build_path%\boot_images\boot_tools\QSaharaServer\QSaharaServer.exe -v 3 -b %boot_build_path%\boot_images\boot\QcomPkg\SocPkg\Kailua\Bin\%VARIANT%\DEBUG\ -s 13:xbl_s_devprg_ns.melf -p \\.\%port_number%
)

if errorlevel 1 (
  echo ERROR: Error running Qsaharaserver
  goto ExitError
)

if /I %SEND_MODE%=="TRUE" (
  echo Send Mode : %SEND_MODE%
  goto ExitOk
)

echo Find meta build ....
echo Flash Mode : %FLASH_MODE%
if /I %FLASH_MODE%=="FALSE" (
  if /I "%VARIANT%"=="LAA" (
    echo Findbuild meta for variant [%VARIANT%]
    \\stone\aswcrm\smart\nt\bin\findbuild.exe -in=location -la -ap Kailua.LA.1.0-?????-STD.INT-? > %TEMP%\meta_build.log
  ) else if /I "%VARIANT%"=="LAB" (
    echo Findbuild meta for variant [%VARIANT%]
    \\stone\aswcrm\smart\nt\bin\findbuild.exe -in=location -la -ap Kailua.LA.0.1-?????-STD.INT-? > %TEMP%\meta_build.log
  )
) else if /I %FLASH_MODE%=="TRUE" (
  echo Flash mode, using meta build from existing log file
)

type %TEMP%\meta_build.log

for /f %%i in ("%TEMP%\meta_build.log") do set size=%%~zi
if %size% equ 0 (
  echo ERROR: Unable to find meta build
  goto ExitError
)

set /p meta_build_path=<%TEMP%\meta_build.log


python %meta_build_path%\common\build\app\meta_cli.py get_partition_files flavor='asic' group=True storage='ufs' > %TEMP%\meta_cli.json
%boot_build_path%\boot_images\boot\QcomPkg\\Tools\Storage\fh_loader\fh_loader.exe --porttracename=%TEMP%\port_trace.txt --json_in=%TEMP%\meta_cli.json --search_path=%CD%\Bin\%VARIANT%\DEBUG --port=\\.\%port_number% --memoryname=ufs --files=shrm.elf,xbl_s.melf,xbl_config.elf,XblRamdump.elf > %TEMP%\fh_loader.log
if errorlevel 1 (
  echo ERROR: Error running fh_loader.exe
  goto ExitError
)

:ExitOk
echo ###############################
echo #           PASS              #
echo ###############################
exit /b


:ExitError
echo ###############################
echo #          FAILED             #
echo ###############################





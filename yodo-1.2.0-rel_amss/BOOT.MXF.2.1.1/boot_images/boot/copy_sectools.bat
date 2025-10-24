@if ""=="%1" (
  goto Usage
) else (
  set sectools_rel=%1
)

robocopy \\sundae\sectools\glue\%sectools_rel% c:\Temp\Sectools3 /z /e 
@if %ERRORLEVEL% LSS 8 (
  set ERRORLEVEL=0
) else ( 
  set ERRORLEVEL=1
)

dir c:\Temp\Sectools3 
@set SECTOOLS_DIR=c:\Temp\Sectools3
@exit /b

:Usage
@echo Usage: "copy_sectools <release version>" Get release version from \\sundae\sectools\glue\

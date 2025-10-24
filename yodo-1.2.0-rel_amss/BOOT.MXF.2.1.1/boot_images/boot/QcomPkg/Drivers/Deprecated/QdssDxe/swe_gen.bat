::===========================================================================
:: @file swe_gen.bat
:: Batch file to generate tracer sw event ids and table
:: Copyright (c) 2015, Qualcomm Technologies, Inc. All rights reserved.
::===========================================================================

echo off
set WORKSPACE=%~dp0\..\..\..
echo|set /p=[swe_gen.bat]  Generating QDSS SW Event Files...

SET QDSS_TRACER_EVENT_CFG=%WORKSPACE%\QcomPkg\Drivers\QdssDxe\tracer_event.cfg
SET QDSS_SWE_BUILDER_OUTPUT_DIR=%WORKSPACE%\QcomPkg\Include
SET QDSS_SWE_BUILDER_PY=%WORKSPACE%\QcomPkg\Drivers\QdssDxe\swe_builder_cfg.py

del %QDSS_SWE_BUILDER_OUTPUT_DIR%\tracer_event_ids.h 2>nul

echo python %QDSS_SWE_BUILDER_PY% %QDSS_SWE_BUILDER_OUTPUT_DIR%\ %QDSS_TRACER_EVENT_CFG% 
python %QDSS_SWE_BUILDER_PY% %QDSS_SWE_BUILDER_OUTPUT_DIR%\ %QDSS_TRACER_EVENT_CFG% >nul
if not %ERRORLEVEL%==0 (
  if %ERRORLEVEL%==1 (
    echo ERROR  Error: Open of Qdss SWE config file
  ) else if %ERRORLEVEL%==2 (
    echo ERROR  Error: SWE config file formatted
  ) else if %ERRORLEVEL%==3 (
    echo ERROR  Error: Open of output file
  ) else (
    echo ERROR  Error: Processing
  )
  EXIT /B 1
)

set created=true
if not exist %QDSS_SWE_BUILDER_OUT_DIR%\tracer_event_ids.h set created=false
if %created%=="false" (
  echo ERROR  QDSS SWE files not generated
  EXIT /B 1
)
echo Done
echo.
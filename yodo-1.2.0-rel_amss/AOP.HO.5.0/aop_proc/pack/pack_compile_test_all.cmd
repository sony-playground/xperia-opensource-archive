@echo off
rem ===============================================================================
rem 
rem  Pack Compile Test All
rem 
rem  GENERAL DESCRIPTION
rem     Call pack_compile_test_all.py
rem 
rem  Copyright (c) 2011-2012 by QUALCOMM, Incorporated.
rem  All Rights Reserved.
rem  QUALCOMM Proprietary/GTDR
rem 
rem -------------------------------------------------------------------------------
rem 
rem   $Header: //components/rel/aop.ho/5.0/aop_proc/pack/pack_compile_test_all.cmd#1 $
rem   $DateTime: 2021/10/26 22:03:12 $
rem   $Change: 33677139 $
rem 
rem ===============================================================================

python pack_compile_test_all.py %*
set BUILD_ERRORLEVEL=%ERRORLEVEL%
exit /B %BUILD_ERRORLEVEL%

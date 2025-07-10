@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2016 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_makenaau.bat#1 $

call build_makenaau_ivi.bat %*
call build_makenaau_adas.bat %*

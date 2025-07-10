@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2017,2019 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================

cd ./HY11_1/aop_proc/
python build\packrat_bfam.py %*


@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2016 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_netrani.bat#2 $

SET BUILD_ASIC=netrani
SET MSM_ID=netrani
SET HAL_PLATFORM=netrani
SET TARGET_FAMILY=netrani
SET CHIPSET=netrani
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=12.0.3
SET CLANG_VERSION=12.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*


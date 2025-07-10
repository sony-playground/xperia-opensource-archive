@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2016 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_Saipan.bat#1 $

SET BUILD_ASIC=Saipan
SET MSM_ID=Saipan
SET HAL_PLATFORM=Saipan
SET TARGET_FAMILY=Saipan
SET CHIPSET=Saipan
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=4.0.3
SET CLANG_VERSION=4.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*


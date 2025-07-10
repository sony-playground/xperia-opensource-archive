@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2016 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_makena.bat#1 $

SET BUILD_ASIC=makena
SET MSM_ID=makena
SET HAL_PLATFORM=makena
SET TARGET_FAMILY=makena
SET CHIPSET=makena
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=4.0.12
SET CLANG_VERSION=4.0.12
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*


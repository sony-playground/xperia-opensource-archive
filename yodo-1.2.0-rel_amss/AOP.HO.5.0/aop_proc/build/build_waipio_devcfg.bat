@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2020 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/rel/aop.ho/5.0/aop_proc/build/build_waipio_devcfg.bat#1 $

SET BUILD_ASIC=waipio
SET MSM_ID=waipio
SET HAL_PLATFORM=waipio
SET TARGET_FAMILY=waipio
SET CHIPSET=waipio
SET CHIPSET_PMIC=waipio
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET GENERATE_DEVCFG_MBN_ONLY=true

SET LLVM_VERSION=12.0.3
SET CLANG_VERSION=12.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*

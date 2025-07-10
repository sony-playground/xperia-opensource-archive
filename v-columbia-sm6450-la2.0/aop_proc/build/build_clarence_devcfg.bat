@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2020 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/dev/aop.ho/4.0/svaginep.aop.ho.4.0.aurora_ddr_mxc/aop_proc/build/build_aurora_devcfg.bat#1 $

SET BUILD_ASIC=clarence
SET MSM_ID=clarence
SET HAL_PLATFORM=clarence
SET TARGET_FAMILY=clarence
SET CHIPSET=clarence
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET GENERATE_DEVCFG_MBN_ONLY=true

SET LLVM_VERSION=12.0.3
SET CLANG_VERSION=12.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*

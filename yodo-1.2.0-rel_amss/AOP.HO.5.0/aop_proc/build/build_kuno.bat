@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2016 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/dev/aop.ho/5.0/pbamanal.aop.ho.5.0.kuno_Base_Build_01_31_2022/aop_proc/build/build_kuno.bat#1 $

SET BUILD_ASIC=kuno
SET MSM_ID=kuno
SET HAL_PLATFORM=kuno
SET TARGET_FAMILY=kuno
SET CHIPSET=kuno
SET CHIPSET_PMIC=kuno
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN USES_SEC_POLICY_INTEGRITY_CHECK

SET LLVM_VERSION=14.0.0
SET CLANG_VERSION=14.0.0
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*


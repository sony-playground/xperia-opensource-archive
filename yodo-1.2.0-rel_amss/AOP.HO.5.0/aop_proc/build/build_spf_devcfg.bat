@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2020 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_0degc/aop_proc/build/build_kailua_devcfg.bat#1 $

SET BUILD_ASIC=kailua
SET MSM_ID=kailua
SET HAL_PLATFORM=kailua
SET TARGET_FAMILY=kailua
SET CHIPSET=kailua
SET CHIPSET_PMIC=kailua
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET GENERATE_DEVCFG_MBN_ONLY=true

SET LLVM_VERSION=14.0.0
SET CLANG_VERSION=14.0.0
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*


rem ==========================================================================
SET BUILD_ASIC=kapiti
SET MSM_ID=kapiti
SET HAL_PLATFORM=kapiti
SET TARGET_FAMILY=kapiti
SET CHIPSET=kapiti
SET CHIPSET_PMIC=kapiti
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET GENERATE_DEVCFG_MBN_ONLY=true

SET LLVM_VERSION=14.0.0
SET CLANG_VERSION=14.0.0
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*

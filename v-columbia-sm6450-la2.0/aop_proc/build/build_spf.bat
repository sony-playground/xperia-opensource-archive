@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2020 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem QUALCOMM Proprietary/GTDR
rem ==========================================================================
rem $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_spf.bat#4 $

SET BUILD_ASIC=waipio
SET MSM_ID=waipio
SET HAL_PLATFORM=waipio
SET TARGET_FAMILY=waipio
SET CHIPSET=waipio
SET CHIPSET_PMIC=waipio
SET SPF=true
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=12.0.3
SET CLANG_VERSION=12.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*
rem ==========================================================================
SET BUILD_ASIC=waipio
SET MSM_ID=waipio
SET HAL_PLATFORM=waipio
SET TARGET_FAMILY=waipio
SET CHIPSET=waipio
SET CHIPSET_PMIC=palima
SET SPF=true
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

SET LLVM_VERSION=12.0.3
SET CLANG_VERSION=12.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*
rem ==========================================================================
SET BUILD_ASIC=fillmore
SET MSM_ID=fillmore
SET HAL_PLATFORM=fillmore
SET TARGET_FAMILY=fillmore
SET CHIPSET=fillmore
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET SPF=true

SET LLVM_VERSION=12.0.3
SET CLANG_VERSION=12.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*
rem ==========================================================================
SET BUILD_ASIC=netrani
SET MSM_ID=netrani
SET HAL_PLATFORM=netrani
SET TARGET_FAMILY=netrani
SET CHIPSET=netrani
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET SPF=true

SET LLVM_VERSION=12.0.3
SET CLANG_VERSION=12.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*
rem ==========================================================================
SET BUILD_ASIC=clarence
SET MSM_ID=clarence
SET HAL_PLATFORM=clarence
SET TARGET_FAMILY=clarence
SET CHIPSET=clarence
SET SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
SET SPF=true

SET LLVM_VERSION=12.0.3
SET CLANG_VERSION=12.0.3
SET SD_LLVM_ROOT=C:\Apps\LLVM\%LLVM_VERSION%
SET SD_LLVM_LIB=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\lib
SET SD_LLVM_LIBC=C:\Apps\LLVM\%LLVM_VERSION%\armv7m-none-eabi\libc
SET SD_LLVM_RTLIB=C:\Apps\LLVM\%LLVM_VERSION%\lib\clang\%CLANG_VERSION%\lib\baremetal

python build_common.py %*

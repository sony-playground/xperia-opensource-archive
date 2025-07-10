# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_spf.sh#5 $

export BUILD_ASIC=waipio
export MSM_ID=waipio
export HAL_PLATFORM=waipio
export TARGET_FAMILY=waipio
export CHIPSET=waipio
export CHIPSET_PMIC=waipio
export SPF=true
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'
python ./build_common.py $@
# ==========================================================================
export BUILD_ASIC=waipio
export MSM_ID=waipio
export HAL_PLATFORM=waipio
export TARGET_FAMILY=waipio
export CHIPSET=waipio
export CHIPSET_PMIC=palima
export SPF=true
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'
python ./build_common.py $@
# ==========================================================================
export BUILD_ASIC=fillmore
export MSM_ID=fillmore
export HAL_PLATFORM=fillmore
export TARGET_FAMILY=fillmore
export CHIPSET=fillmore
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export SPF=true

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'
python ./build_common.py $@
# ==========================================================================
export BUILD_ASIC=netrani
export MSM_ID=netrani
export HAL_PLATFORM=netrani
export TARGET_FAMILY=netrani
export CHIPSET=netrani
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export SPF=true

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@

# ==========================================================================
export BUILD_ASIC=clarence
export MSM_ID=clarence
export HAL_PLATFORM=clarence
export TARGET_FAMILY=clarence
export CHIPSET=clarence
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export SPF=true

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@

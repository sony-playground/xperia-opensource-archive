# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/pravsahu.aop.ho.5.0.kapiti_0525_spf_support/aop_proc/build/build_kailua.sh#1 $

export BUILD_ASIC=kailua
export MSM_ID=kailua
export HAL_PLATFORM=kailua
export TARGET_FAMILY=kailua
export CHIPSET=kailua
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export SPF=true
export LLVM_VERSION=14.0.0

CLANG=/pkg/qct/software/llvm/release/arm/14.0.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'
python ./build_common.py $@

########################################################################
export BUILD_ASIC=kapiti
export MSM_ID=kapiti
export HAL_PLATFORM=kapiti
export TARGET_FAMILY=kapiti
export CHIPSET=kapiti
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export SPF=true
export LLVM_VERSION=14.0.0

CLANG=/pkg/qct/software/llvm/release/arm/14.0.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'
python ./build_common.py $@



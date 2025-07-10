# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_fillmore_devcfg.sh#2 $

export BUILD_ASIC=fillmore
export MSM_ID=fillmore
export HAL_PLATFORM=fillmore
export TARGET_FAMILY=fillmore
export CHIPSET=fillmore
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export GENERATE_DEVCFG_MBN_ONLY=true

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


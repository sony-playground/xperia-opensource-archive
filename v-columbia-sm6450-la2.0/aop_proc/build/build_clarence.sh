# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/4.0/tmajumde.aop.ho.4.0.05202022_clarence_build_support/aop_proc/build/build_netrani.sh#1 $

export BUILD_ASIC=clarence
export MSM_ID=clarence
export HAL_PLATFORM=clarence
export TARGET_FAMILY=clarence
export CHIPSET=clarence
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


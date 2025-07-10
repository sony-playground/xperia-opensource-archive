# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_netrani.sh#4 $

export BUILD_ASIC=netrani
export MSM_ID=netrani
export HAL_PLATFORM=netrani
export TARGET_FAMILY=netrani
export CHIPSET=netrani
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


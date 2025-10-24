# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/vinodv.aop.ho.5.0.hamoa1/aop_proc/build/build_hamoa.sh#1 $

export BUILD_ASIC=hamoa
export MSM_ID=hamoa
export HAL_PLATFORM=hamoa
export TARGET_FAMILY=hamoa
export CHIPSET=hamoa
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=12.0.1

CLANG=/pkg/qct/software/llvm/release/arm/14.0.0/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


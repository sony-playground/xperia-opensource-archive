# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2021 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_lassen.sh#1 $

export BUILD_ASIC=lassen
export MSM_ID=lassen
export HAL_PLATFORM=lassen
export TARGET_FAMILY=lassen
export CHIPSET=lassen
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


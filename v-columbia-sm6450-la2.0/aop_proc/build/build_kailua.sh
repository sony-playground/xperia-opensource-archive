# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_kailua.sh#1 $

export BUILD_ASIC=kailua
export MSM_ID=kailua
export HAL_PLATFORM=kailua
export TARGET_FAMILY=kailua
export CHIPSET=kailua
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


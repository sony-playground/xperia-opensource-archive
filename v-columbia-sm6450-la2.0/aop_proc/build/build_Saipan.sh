# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_Saipan.sh#1 $

export BUILD_ASIC=Saipan
export MSM_ID=Saipan
export HAL_PLATFORM=Saipan
export TARGET_FAMILY=Saipan
export CHIPSET=Saipan
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

CLANG=/pkg/qct/software/llvm/release/arm/4.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2019 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_Chitwan.sh#1 $

export BUILD_ASIC=Chitwan
export MSM_ID=Chitwan
export HAL_PLATFORM=Chitwan
export TARGET_FAMILY=Chitwan
export CHIPSET=Chitwan
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

CLANG=/pkg/qct/software/llvm/release/arm/4.0.12/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


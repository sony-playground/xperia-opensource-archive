# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_kodiak_cedros_lahaina.sh#1 $

export BUILD_ASIC=kodiak
export MSM_ID=kodiak
export HAL_PLATFORM=kodiak
export TARGET_FAMILY=kodiak
export CHIPSET=kodiak
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

CLANG=/pkg/qct/software/llvm/release/arm/4.0.12/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@

export BUILD_ASIC=cedros
export MSM_ID=cedros
export HAL_PLATFORM=cedros
export TARGET_FAMILY=cedros
export CHIPSET=cedros
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

CLANG=/pkg/qct/software/llvm/release/arm/4.0.12/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@

export BUILD_ASIC=8350
export MSM_ID=8350
export HAL_PLATFORM=8350
export TARGET_FAMILY=8350
export CHIPSET=sm8350
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

CLANG=/pkg/qct/software/llvm/release/arm/4.0.12/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@
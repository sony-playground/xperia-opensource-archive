# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2021 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/5.0/aop_proc/build/build_lanai.sh#4 $

export BUILD_ASIC=lanai
export MSM_ID=lanai
export HAL_PLATFORM=lanai
export TARGET_FAMILY=lanai
export CHIPSET=lanai
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
#CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common_riscv.py $@


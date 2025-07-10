# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2021 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_halliday.sh#2 $

export BUILD_ASIC=halliday
export MSM_ID=halliday
export HAL_PLATFORM=halliday
export TARGET_FAMILY=halliday
export CHIPSET=halliday
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@

cd ../../

mkdir HY11_1

cp -rf aop_proc HY11_1/
./aop_proc/build/build_packed.sh halliday

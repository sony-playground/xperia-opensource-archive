# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2018 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_Olympic.sh#1 $

export BUILD_ASIC=Olympic
export MSM_ID=Olympic
export HAL_PLATFORM=Olympic
export TARGET_FAMILY=Olympic
export CHIPSET=Olympic
export SECPOLICY='USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN USES_SEC_POLICY_INTEGRITY_CHECK' 

CLANG=/pkg/qct/software/llvm/release/arm/4.0.12/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


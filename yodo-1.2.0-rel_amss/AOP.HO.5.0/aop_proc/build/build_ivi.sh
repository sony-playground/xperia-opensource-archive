# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/5.0/aop_proc/build/build_ivi.sh#1 $

export BUILD_ASIC=makenaau
export MSM_ID=makenaau
export HAL_PLATFORM=makenaau
export TARGET_FAMILY=makenaau
export CHIPSET=makenaau
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export VARIANT=IVI

CLANG=/pkg/qct/software/llvm/release/arm/4.0.12/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


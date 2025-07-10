# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/4.0/svaginep.aop.ho.4.0.aurora_ddr_mxc/aop_proc/build/build_aurora_devcfg.sh#1 $

export BUILD_ASIC=netrani
export MSM_ID=netrani
export HAL_PLATFORM=netrani
export TARGET_FAMILY=netrani
export CHIPSET=netrani
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export GENERATE_DEVCFG_MBN_ONLY=true

export LLVM_VERSION=12.0.3

if [ -z $SD_LLVM_ROOT ]; then
    CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
    export SD_LLVM_ROOT=`dirname $CLANG`/..
fi

if [ -z $USES_FEATURE_XBOOT ]; then
    cd './aop_proc/build/'
fi

python ./build_common.py $@


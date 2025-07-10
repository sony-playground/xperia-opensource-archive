# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/4.0/svaginep.aop.ho.4.0.aurora_ddr_mxc/aop_proc/build/build_aurora_devcfg.sh#1 $

export BUILD_ASIC=clarence
export MSM_ID=clarence
export HAL_PLATFORM=clarence
export TARGET_FAMILY=clarence
export CHIPSET=clarence
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export GENERATE_DEVCFG_MBN_ONLY=true

export LLVM_VERSION=12.0.3

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


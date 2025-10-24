# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2020 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/5.0/aop_proc/build/build_waipio_devcfg.sh#1 $

export BUILD_ASIC=waipio
export MSM_ID=waipio
export HAL_PLATFORM=waipio
export TARGET_FAMILY=waipio
export CHIPSET=waipio
export CHIPSET_PMIC=waipio
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export GENERATE_DEVCFG_MBN_ONLY=true

CLANG=/pkg/qct/software/llvm/release/arm/12.0.3/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common.py $@


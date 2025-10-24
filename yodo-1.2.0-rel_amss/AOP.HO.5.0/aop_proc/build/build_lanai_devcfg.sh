# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2022 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/dev/aop.ho/5.0/kparsha.aop.ho.5.0.aop50_0degc/aop_proc/build/build_lanai_devcfg.sh#1 $

export BUILD_ASIC=lanai
export MSM_ID=lanai
export HAL_PLATFORM=lanai
export TARGET_FAMILY=lanai
export CHIPSET=lanai
export CHIPSET_PMIC=lanai
export SECPOLICY=USES_SEC_POLICY_MULTIPLE_DEFAULT_SIGN
export GENERATE_DEVCFG_MBN_ONLY=true

export LLVM_VERSION=11.0.4

CLANG=/pkg/qct/software/llvm/release/riscv/11.0.4/ubuntu/bin/clang
export SD_LLVM_ROOT=`dirname $CLANG`/..

cd './aop_proc/build/'

python ./build_common_riscv.py $@

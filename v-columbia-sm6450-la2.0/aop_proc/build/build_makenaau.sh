# ==========================================================================
#
#  AOP build system launcher
#
# Copyright (c) 2016 by Qualcomm Technologies, Inc.
# All Rights Reserved.
# QUALCOMM Proprietary/GTDR
# ==========================================================================
# $Header: //components/rel/aop.ho/4.0/aop_proc/build/build_makenaau.sh#1 $

cd './aop_proc/build/'
./build_makenaau_ivi.sh $1
./build_makenaau_adas.sh $1


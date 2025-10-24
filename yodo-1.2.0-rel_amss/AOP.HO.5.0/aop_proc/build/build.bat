@echo off
rem ==========================================================================
rem
rem  AOP build system launcher
rem
rem Copyright (c) 2016,2019 Qualcomm Technologies, Inc.
rem All Rights Reserved.
rem Proprietary and Confidential - Qualcomm Technologies, Inc 
rem ==========================================================================
rem $Header: //components/rel/aop.ho/5.0/aop_proc/build/build.bat#1 $

SET BUILD_ASIC=SDM845
SET MSM_ID=845
SET HAL_PLATFORM=845
SET TARGET_FAMILY=845
SET CHIPSET=sdm845

python build_common.py %*

rem python mapread_bfam_splitmem.py ../.. > memory_%CHIPSET%.csv

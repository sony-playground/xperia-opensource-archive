## @file
# GNU/Linux makefile for 'GenSec' module build.
#
# Copyright (c) 2011,2013,2018, 2020 Qualcomm Technologies Inc. All rights reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
# Portions:
# Copyright (c) 2007 - 2018, Intel Corporation. All rights reserved.<BR>
# SPDX-License-Identifier: BSD-2-Clause-Patent
#
MAKEROOT ?= ..

APPNAME = GenSec

OBJECTS = GenSec.o

include $(MAKEROOT)/Makefiles/app.makefile

LIBS = -lCommon
#
#QCOM_EDK2_PATCH Start
#
#ifeq ($(CYGWIN), CYGWIN)
#  LIBS += -L/lib/e2fsprogs -luuid
#endif
#
#ifeq ($(LINUX), Linux)
#  LIBS += -luuid
#endif
#
#QCOM_EDK2_PATCH End
#

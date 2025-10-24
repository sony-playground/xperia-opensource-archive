## @file
# GNU/Linux makefile for 'minigzip' module build.
#
# Copyright (c) 2016, 2020 Qualcomm Technologies, Inc. All rights reserved.<BR> 
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#
ARCH ?= IA32
MAKEROOT ?= ..

include $(MAKEROOT)/Makefiles/app.makefile

all:
	cd zlib && ./configure
	cd zlib && $(MAKE) minigzip
	cp zlib/minigzip $(MAKEROOT)/bin/minigzip

cleanall:
	rm -f $(MAKEROOT)/bin/minigzip


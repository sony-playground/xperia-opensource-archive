## @file
# GNU/Linux makefile for 'minigzip' module build.
#
# Copyright (c) 2016, 2020, 2023 Qualcomm Technologies, Inc. All rights reserved.
# Confidential and Proprietary - Qualcomm Technologies, Inc.
#
ARCH ?= IA32
MAKEROOT ?= ..

include $(MAKEROOT)/Makefiles/app.makefile

OBJECTS = zlib/minigzip.o \
zlib/adler32.o \
zlib/crc32.o \
zlib/deflate.o \
zlib/infback.o \
zlib/inffast.o \
zlib/inflate.o \
zlib/inftrees.o \
zlib/trees.o \
zlib/zutil.o \
zlib/compress.o \
zlib/uncompr.o \
zlib/gzclose.o \
zlib/gzlib.o \
zlib/gzread.o \
zlib/gzwrite.o

all:
	cd zlib && ./configure
	cd zlib && $(MAKE) minigzip
	cp zlib/minigzip $(MAKEROOT)/bin/minigzip

cleanall:
	rm -f $(MAKEROOT)/bin/minigzip


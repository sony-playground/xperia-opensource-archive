#!/bin/bash
# *******************************************
# file: c2d.sh
# Script for creating deb package
# and then saving it to C2D
#
# Copyright (C) 2015 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.
#
# *******************************************

do_exit() {
  echo $1 >&2
  exit $2
}

do_print() {
  echo $1 >&2
}

TARGET_PLATFORM=$1

if [ "$TARGET_PLATFORM" == "" ]; then
  do_exit "No TARGET_PLATFORM defined. Exiting" 1
fi

if [ "$TARGET_PRODUCT" == "" ]; then
  do_exit "No TARGET_PRODUCT defined. Exiting" 1
fi

PACKAGE_TARGET_PLATFORM=`echo $TARGET_PLATFORM | sed s/_/-/g`
PACKAGE_TARGET_PRODUCT=`echo $TARGET_PRODUCT | sed s/_/-/g`
CREATEPACKAGE=${CREATEPACKAGE:-createpackage}

OUT_DIR=out/target/product/$TARGET_PRODUCT
DEB_DIR=$OUT_DIR/deb

while [ "$2" != "" ]; do
  if [ "$2" == "--repo" ]; then
    shift
    STATIC_MANIFEST=$2
  else
    RAMDUMP_DEB_VERSION=$2
  fi
  shift
done

if [ "$RAMDUMP_DEB_VERSION" == "" ]; then
  echo "No build id defined. Using \"ISO label\""
  DATE_TAG=`date -u +%Y%m%d-%H%M`
  COMMIT_TAG=`cd kernel/ramdump; git log -1 --pretty=%h`
  echo DATE_TAG   = $DATE_TAG
  echo COMMIT_TAG = $COMMIT_TAG
  RAMDUMP_DEB_VERSION=$PACKAGE_TARGET_PLATFORM-$DATE_TAG-$COMMIT_TAG
fi

RAMDUMP_DEB_VERSION=$(echo $RAMDUMP_DEB_VERSION | tr [:lower:] [:upper:])
RAMDUMP_DEB_NAME=fw-ramdump-raw-$PACKAGE_TARGET_PRODUCT
RAMDUMP_DEB_DEBUG=debug-ramdump-$PACKAGE_TARGET_PRODUCT

echo PACKAGE_TARGET_PLATFORM = $PACKAGE_TARGET_PLATFORM
echo PACKAGE_TARGET_PRODUCT = $PACKAGE_TARGET_PRODUCT
echo OUT_DIR = $OUT_DIR
echo RAMDUMP_DEB_NAME    = $RAMDUMP_DEB_NAME
echo RAMDUMP_DEB_VERSION = $RAMDUMP_DEB_VERSION

## Create the deb package
# First create an empty staging dir and then copy all files
STAGING_DIR=$DEB_DIR/img
STAGING_OBJ_DIR=$DEB_DIR/util/debug

rm -rf $STAGING_DIR
mkdir -p $STAGING_DIR
mkdir -p $STAGING_OBJ_DIR
cp $OUT_DIR/ramdump.img $STAGING_DIR > /dev/null 2>&1 || do_print "No ramdump image"
cp $OUT_DIR/obj/RD_KERNEL_OBJ/vmlinux $STAGING_OBJ_DIR  || do_print "No vmlinux file"
cp $OUT_DIR/obj/RD_KERNEL_OBJ/System.map $STAGING_OBJ_DIR || do_print "No System.map file"
cp -R $OUT_DIR/symbols $STAGING_OBJ_DIR || do_print "No Ramdump filesystem"
# include manifest file in deb for future rebuild
if [ "$STATIC_MANIFEST" != "" ]; then
    cp $STATIC_MANIFEST $STAGING_DIR || do_exit "No manifest.xml file. Exiting" 1
fi

# Do package
DEB_PACKAGE=`$CREATEPACKAGE $RAMDUMP_DEB_NAME $RAMDUMP_DEB_VERSION -df $STAGING_DIR -o $DEB_DIR` || do_exit "Could not create package. Exiting" 1
echo ramdump Package created = $DEB_PACKAGE

# Do debug package
DEB_DEBUG_PACKAGE=`$CREATEPACKAGE $RAMDUMP_DEB_DEBUG $RAMDUMP_DEB_VERSION -df $STAGING_OBJ_DIR -o $DEB_DIR` || do_exit "Could not create package. Exiting" 1
echo Debug package created = $DEB_DEBUG_PACKAGE

# To save the package to the C2D do:
# 'repository addpackage $DEB_PACKAGE'

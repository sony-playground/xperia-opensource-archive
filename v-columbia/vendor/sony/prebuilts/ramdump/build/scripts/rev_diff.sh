#!/bin/bash
# Script to get the differences log between two built revisions of the ramdumper
# the log can be used for commit comment for ramdump-packages
# Shall be launched from the ramdump/ directory
#
# Usage: rev_diff.sh <product> <from version> <to version>
# Example: ./rev_diff.sh nypon 1.0.B.0.11 1.0.B.0.12

PRODUCT=$1
FROM_VER=$2
TO_VER=$3

WORKING_DIR=./ramdump_diff

mkdir ${WORKING_DIR}
repository -s seld getpackage fw-ramdump-raw-${PRODUCT}-userdebug $FROM_VER --out=${WORKING_DIR}
dpkg-deb -x ${WORKING_DIR}/fw-ramdump-raw-${PRODUCT}-userdebug_${FROM_VER}_all.deb ${WORKING_DIR}/${PRODUCT}_${FROM_VER}
FROM_SH1=`grep semc\/ramdump ${WORKING_DIR}/${PRODUCT}_${FROM_VER}/img/static_manifest.xml | sed -r 's/.*revision=\"(.*)\".*/\1/'`

repository -s seld getpackage fw-ramdump-raw-${PRODUCT}-userdebug $TO_VER --out=${WORKING_DIR}
dpkg-deb -x ${WORKING_DIR}/fw-ramdump-raw-${PRODUCT}-userdebug_${TO_VER}_all.deb ${WORKING_DIR}/${PRODUCT}_${TO_VER}
TO_SH1=`grep semc\/ramdump ${WORKING_DIR}/${PRODUCT}_${TO_VER}/img/static_manifest.xml | sed -r 's/.*revision=\"(.*)\".*/\1/'`

echo "from SH1="$FROM_SH1
echo "to SH1="$TO_SH1

echo ""
echo "=== Changes between ${FROM_VER} and ${TO_VER} ==="
git log --oneline --no-merges ${FROM_SH1}..${TO_SH1}
echo ""

git log --no-merges ${FROM_SH1}..${TO_SH1} | grep FIX=

rm -r ${WORKING_DIR}

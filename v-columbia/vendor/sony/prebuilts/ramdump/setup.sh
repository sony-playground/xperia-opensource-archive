#!/bin/bash
# *******************************************
# file: setup.h
# Script for switching ramdump kernel
#
# Copyright (C) 2019 Sony Mobile Communications Inc.
# All rights, including trade secret rights, reserved.
#
# *******************************************

TOP=`pwd`
MANIFEST=$TOP/.repo/manifests/default.xml
KERNEL=`xmllint --xpath '//project/@name' $MANIFEST | grep -Po '"kernel/msm-.*?"' | tr -d \"`
DEVICETREE=`xmllint --xpath '//project/@name' $MANIFEST | grep -Po '"kernel/devicetree"' | tr -d \"`
DISPLAYDRIVER=`xmllint --xpath '//project/@name' $MANIFEST | grep -Po '"platform/vendor/opensource/display-drivers"' | tr -d \"`
RAMDUMP_BRANCH=r-sagami-bpf-ramdump
BPF_SW_LABEL=R-SAGAMI-BPF-210205-1713
STATIC_MANIFEST=

PROJECTS=(
'kernel/msm-5.4'
'kernel/devicetree'
'platform/vendor/opensource/display-drivers'
'platform/vendor/opensource/sched'
'platform/vendor/qcom-proprietary/camera-devicetree'
'platform/vendor/qcom-proprietary/display-devicetree'
)

GIT_PATHS=(
"${TOP}/kernel/ramdump"
"${TOP}/kernel/ramdump/arch/arm64/boot/dts/vendor"
"${TOP}/kernel/ramdump/techpack/display"
"${TOP}/kernel/ramdump/techpack/sched"
"${TOP}/kernel/ramdump/arch/arm64/boot/dts/vendor/qcom/camera/"
"${TOP}/kernel/ramdump/arch/arm64/boot/dts/vendor/qcom/display"
)

FIXED_SHA1=(
""
""
""
""
""
""
)

######### Read static manifest ###########
read_static_manifest()
{
    SW_LABEL=$1
    TMPDIR=`mktemp -d`
    repository getpackage build-metadata $SW_LABEL && mv *.deb $TMPDIR
    dpkg -x $TMPDIR/*.deb $TMPDIR
    STATIC_MANIFEST=$TMPDIR/manifest_static.xml
}

######### Clone projects from static manifest ###########
clone_projects()
{
    i=0
    while [ $i -lt ${#PROJECTS[*]} ]; do
        if [ ${PROJECTS[$i]} = $KERNEL ]; then
            git clone git://review.sonyericsson.net/${PROJECTS[$i]} ${GIT_PATHS[$i]} -b $RAMDUMP_BRANCH
        elif [ ${PROJECTS[$i]} = $DEVICETREE ]; then
            git clone git://review.sonyericsson.net/${PROJECTS[$i]} ${GIT_PATHS[$i]} -b $RAMDUMP_BRANCH
        elif [ ${PROJECTS[$i]} = $DISPLAYDRIVER ]; then
            git clone git://review.sonyericsson.net/${PROJECTS[$i]} ${GIT_PATHS[$i]} -b $RAMDUMP_BRANCH
        else
            echo "***************************************************"
            if [ -z "${FIXED_SHA1[$i]}" ]; then
                SHA1=`grep -rins ${PROJECTS[$i]} $STATIC_MANIFEST | grep -Po 'revision=\K"[0-9a-z]+"' | tr -d \"`
                echo "GIT sha1 is: $SHA1"
            else
                SHA1="${FIXED_SHA1[$i]}"
                echo "GIT fixed sha1 is: $SHA1"
            fi
            git clone git://review.sonyericsson.net/${PROJECTS[$i]} ${GIT_PATHS[$i]} && cd ${GIT_PATHS[$i]} && git reset --hard $SHA1
            if [ -d "${TOP}/kernel/ramdump/arch/arm64/boot/dts/vendor/qcom/display" ]; then
                ln -s ${TOP}/kernel/ramdump/arch/arm64/boot/dts/vendor/qcom/display/display/* ${TOP}/kernel/ramdump/arch/arm64/boot/dts/vendor/qcom/display/
            else
                echo "Devicetree Display directory not present"
            fi
            echo "***************************************************"
        fi

        i=$(($i + 1))
        cd $TOP
    done
}

read_static_manifest $BPF_SW_LABEL
clone_projects
rm -rf $TMPDIR
# soong/ninja filters environment variables, only Kati can see
# them. This is a workaround but incremental builds may be unsafe.
# See:
# http://opengrok.sonymobile.net/R/xref/r-edo/build/soong/ui/build/ninja.go#89
#
# Without this make parameter such as: BUILD_RAMDUMP=1 won't be visible in:
# kernel/ramdump/drivers/soc/qcom/last_logs/Kbuild
export ALLOW_NINJA_ENV=1

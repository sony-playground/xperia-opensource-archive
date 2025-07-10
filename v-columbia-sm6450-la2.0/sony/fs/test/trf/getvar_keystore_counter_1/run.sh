#!/bin/bash

source ../common.sh

# run loader
adb push fbcmd /
if [ $? -ne 0 ]; then
	echo "adb push fbcmd returned error"
	exit 1
fi

adb shell loader -s$STORAGE -g/fbcmd
if [ $? -ne 0 ]; then
	echo "adb shell loader returned error"
	exit 1
fi

adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
if [ $? -ne 0 ]; then
	echo "adb pull /fbcmd_out returned error"
	exit 1
fi

out=`cat $HOST_TMP_DIR/fbcmd_out`
if [ ${out:0:4} != "OKAY" ]; then
	echo "OKAY is missing"
	exit 1
fi

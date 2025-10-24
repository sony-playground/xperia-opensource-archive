#!/bin/bash

source ../common.sh

# run loader
adb push fbcmd /
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi
adb shell loader -sufs -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

out=`cat $HOST_TMP_DIR/fbcmd_out`
if [ ${out:0:4} != "FAIL" ]; then
	echo "OKAY is missing"
	exit 1
fi

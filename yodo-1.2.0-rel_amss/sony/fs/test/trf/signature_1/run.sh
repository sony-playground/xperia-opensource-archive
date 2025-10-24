#!/bin/bash

source ../common.sh

# push cms file
adb push dsp.cms /signature1
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# analyze and check result
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -eq 0 ]; then
	exit 0
else
	exit 1
fi

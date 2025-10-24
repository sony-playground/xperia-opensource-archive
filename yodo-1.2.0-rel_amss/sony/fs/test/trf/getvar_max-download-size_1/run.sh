#!/bin/bash

source ../common.sh

# run loader
adb push fbcmd /
if [ $? -ne 0 ]; then
		# adb returned error
		exit 1
fi
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -eq 0 ]; then
		exit 0
else
		exit 1
fi

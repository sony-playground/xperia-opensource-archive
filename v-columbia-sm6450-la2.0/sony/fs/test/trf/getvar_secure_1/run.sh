#!/bin/bash

source ../common.sh

adb push fbcmd /
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

out=`cat $HOST_TMP_DIR/fbcmd_out`
if [ ${out:0:4} != "OKAY" ]; then
	echo "OKAY is missing"
	exit 1
fi
if [ ${out:4:2} == "no" -o ${out:4:3} == "yes" ]; then
	exit 0
else
	echo "Unexpected response:"
	cat $HOST_TMP_DIR/fbcmd_out
	# Print newline
	echo ""
	exit 1
fi

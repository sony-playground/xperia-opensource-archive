#!/bin/bash

source ../common.sh

adb push fbcmd /
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -eq 0 ]; then
	exit 0
else
	echo "Unexpected response:"
	cat $HOST_TMP_DIR/fbcmd_out
	# Print newline
	echo ""
	exit 1
fi

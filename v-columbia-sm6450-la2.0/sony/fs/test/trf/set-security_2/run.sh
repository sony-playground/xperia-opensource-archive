#!/bin/bash

source ../common.sh

TAPART=/dev/block/bootdevice/by-name/TA

# Make backup of TA-partition
adb shell dd if=$TAPART of=/restore bs=4096 count=512
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# push data for testing
adb push secprop_dk /
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# push fbcmd and run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd

# Restore TA-partition
adb shell dd if=/restore of=$TAPART bs=4096 count=512
adb shell rm /restore

# Extract loader result and compare with reference
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -ne 0 ]; then
	echo "Unexpected response"
	exit 1
fi
exit 0

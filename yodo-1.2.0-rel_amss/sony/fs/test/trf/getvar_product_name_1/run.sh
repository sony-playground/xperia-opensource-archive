#!/bin/bash

source ../common.sh

prepare_ta_ref

# Backup TA
adb shell dd if=/dev/block/bootdevice/by-name/TA of=/TA_bak bs=512
if [ $? -ne 0 ]; then
		# adb returned error
		exit 1
fi
# Push reference TA to device
adb push $HOST_TMP_DIR/TA_ref /
if [ $? -ne 0 ]; then
		echo "Unable to push TA_ref to device"
		exit 1
fi
# Write reference TA
adb shell dd if=/TA_ref of=/dev/block/bootdevice/by-name/TA bs=512

# run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# Restore original TA
adb shell dd if=/TA_bak of=/dev/block/bootdevice/by-name/TA bs=512
# Remove TA_ref and TA_bak from device
adb shell rm /TA_ref
adb shell rm /TA_bak

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

#!/bin/bash

source ../common.sh
source ../authenticate.sh

RETVAL=0

stop () {
	adb shell "stop loader-trf"
	exit $RETVAL
}

# Authenticate
if ! authenticate; then
	echo "Authentication failed"
	RETVAL=1
	stop
fi

prepare_ta_ref

# Backup TA
adb shell dd if=/dev/block/bootdevice/by-name/TA of=/TA_bak bs=512
if [ $? -ne 0 ]; then
	echo "adb returned error"
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

# Push command file and prepare zerobyte of data to be written to TA66671
adb push fbcmd /
adb shell touch zerobyte

echo "Restart loader, returns when device is ready"
if ! restart_loader; then
	RETVAL=1
fi

echo "Device is ready"
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# Restore original TA
adb shell dd if=/TA_bak of=/dev/block/bootdevice/by-name/TA bs=512

# Remove TA_ref and TA_bak from device
adb shell rm /TA_ref
adb shell rm /TA_bak

diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -eq 0 ]; then
	stop
else
	echo "Unexpected response:"
	cat $HOST_TMP_DIR/fbcmd_out
	# Print newline
	echo ""
	RETVAL=1
fi

stop

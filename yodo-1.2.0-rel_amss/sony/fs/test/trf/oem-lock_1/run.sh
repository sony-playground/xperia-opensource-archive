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
adb pull /TA_bak $HOST_TMP_DIR/TA_bak
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

# Push fbcmd and cms
adb push fbcmd /
adb push oem_lock_cms_blob_00440245573320.bin /

# Restart loader
echo "Restart loader, returns when device is ready"
if ! restart_loader; then
	RETVAL=1
fi

# Restore original TA
adb push $HOST_TMP_DIR/TA_bak /TA_bak
adb shell dd if=/TA_bak of=/dev/block/bootdevice/by-name/TA bs=512

# Remove TA_ref, TA_bak and cms from device
adb shell rm /TA_bak
adb shell rm /TA_ref
adb shell rm /oem_lock_cms_blob_00440245573320.bin

# Extract result and compare with expected output reference
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -eq 0 ]; then
	stop
else
	echo "Unexpected response:"
	echo $fbcmd_out
	RETVAL=1
fi

stop

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
# Push reference TA to root of device (two steps are needed)
adb push $HOST_TMP_DIR/TA_ref /
if [ $? -ne 0 ]; then
	echo "Unable to push TA_ref to device"
	exit 1
fi
# Copy reference TA in device
adb shell dd if=/TA_ref of=/dev/block/bootdevice/by-name/TA bs=512

# Push command file
adb push fbcmd /

echo "Restart loader, returns when device is ready"
if ! restart_loader; then
	RETVAL=1
fi

echo "Device is ready"
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# Pull formatted TA
adb pull /dev/block/bootdevice/by-name/TA $HOST_TMP_DIR/TA_format3
# Restore original TA
adb shell dd if=/TA_bak of=/dev/block/bootdevice/by-name/TA bs=512
# Remove TA_ref and TA_bak from device
adb shell rm /TA_ref
adb shell rm /TA_bak
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -ne 0 ]; then
	echo "Format failed 1"
	RETVAL=1
	stop
fi
mkdir $HOST_TMP_DIR/TA_result
$SCRIPTS_DIR/ta_parser\
	-a$HOST_TMP_DIR/TA_result\
	$HOST_TMP_DIR/TA_format3 > /dev/null 2>&1
if [ $? -ne 0 ]; then
	echo "Format failed 2"
	rm -rf $HOST_TMP_DIR/TA_result > /dev/null 2>&1
	RETVAL=1
	stop
fi
ls $HOST_TMP_DIR/TA_result/1-* > /dev/null 2>&1
if [ $? -eq 0 ]; then
	echo "Format failed 3"
	rm -rf $HOST_TMP_DIR/TA_result > /dev/null 2>&1
	RETVAL=1
	stop
fi
ls $HOST_TMP_DIR/TA_result/2-* > /dev/null 2>&1
if [ $? -eq 0 ]; then
	echo "Format failed 4"
	rm -rf $HOST_TMP_DIR/TA_result > /dev/null 2>&1
	RETVAL=1
	stop
fi
rm -rf $HOST_TMP_DIR/TA_result > /dev/null 2>&1

stop

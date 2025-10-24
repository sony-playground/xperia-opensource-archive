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

# Push command file
adb push fbcmd /

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

rm -r $HOST_TMP_DIR/TA > /dev/null 2>&1
mkdir $HOST_TMP_DIR/TA
$SCRIPTS_DIR/ta_parser -a$HOST_TMP_DIR/TA $HOST_TMP_DIR/TA_ref > /dev/null
# Remove units from partition 2
rm -r $HOST_TMP_DIR/TA/2-* > /dev/null 2>&1

rm -r $HOST_TMP_DIR/TA_dump > /dev/null 2>&1
mkdir $HOST_TMP_DIR/TA_dump
python $COMMON_DIR/dump_all_ta_units.py\
	"1-" $HOST_TMP_DIR/fbcmd_out $HOST_TMP_DIR/TA_dump
if [ $? -ne 0 ]; then
	echo "Failed execution of dump_all_ta_units.pl"
	RETVAL=1
	stop
fi

diff -q $HOST_TMP_DIR/TA $HOST_TMP_DIR/TA_dump
if [ $? -ne 0 ]; then
	echo "Output does not match input"
	RETVAL=1
	stop
fi

stop

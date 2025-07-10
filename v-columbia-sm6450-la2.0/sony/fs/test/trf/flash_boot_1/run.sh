#!/bin/bash

source ../common.sh
source ../authenticate.sh

PART=/dev/block/bootdevice/by-name/boot
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

# Init test
adb shell dd if=$PART of=/restore bs=4096 count=1
if [ $? -ne 0 ]; then
	echo "adb returned error"
	RETVAL=1
	stop
fi
dd if=/dev/urandom of=$HOST_TMP_DIR/dump1 bs=4096 count=1
adb push $HOST_TMP_DIR/dump1 /

# Push command file
adb push fbcmd /

echo "Restart loader, returns when device is ready"
if ! restart_loader; then
	RETVAL=1
	stop
fi

echo "Device is ready"
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# Test final
adb shell dd if=$PART of=/dump2 bs=4096 count=1
adb shell dd if=/restore of=$PART bs=4096 count=1
adb pull dump2 $HOST_TMP_DIR/dump2
diff $HOST_TMP_DIR/dump1 $HOST_TMP_DIR/dump2
if [ $? -eq 0 ]; then
	echo "FLASH OK!"
	RETVAL=0
else
	echo "FLASH FAIL!"
	RETVAL=1
fi

adb shell rm /restore /dump1 /dump2
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -ne 0 ]; then
	RETVAL=1
fi

stop

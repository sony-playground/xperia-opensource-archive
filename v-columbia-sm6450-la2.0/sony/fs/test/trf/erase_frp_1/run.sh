#!/bin/bash

source ../common.sh
source ../authenticate.sh

PART=/dev/block/bootdevice/by-name/frp
RETVAL=0

stop () {
	# Restore frp if saved
	if [ -f $HOST_TMP_DIR/frp ]; then
		adb push $HOST_TMP_DIR/frp /frp
		adb shell dd if=/frp of=$PART
		adb shell rm /frp
	fi

	adb shell "stop loader-trf"
	exit $RETVAL
}

check_adb() {
	if [ $? -ne 0 ]; then
		echo "adb returned error"
		RETVAL=1
		stop
	fi
}

# Authenticate
if ! authenticate; then
	RETVAL=1
	stop
fi

# Save frp
adb pull $PART $HOST_TMP_DIR/frp
check_adb

# Push command file
adb push fbcmd /
check_adb

# Restart loader, returns when device is ready
if ! restart_loader; then
	RETVAL=1
	stop
fi

adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
check_adb

adb pull $PART $HOST_TMP_DIR/frp_z
check_adb
tmp=$(tr -dc '\000' <$HOST_TMP_DIR/frp_z | cmp - $HOST_TMP_DIR/frp_z)
if [[ $tmp = "-"* ]]; then
	echo "ERASE FAIL!"
	RETVAL=1
	stop
fi

diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -ne 0 ]; then
	echo "Output differs from reference"
	RETVAL=1
fi

stop

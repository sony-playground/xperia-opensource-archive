#!/bin/bash

source ../common.sh
source ../authenticate.sh

PART=/dev/block/bootdevice/by-name/frp
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

adb pull $PART $HOST_TMP_DIR/frp
if [ $? -ne 0 ]; then
	echo "adb returned error"
	RETVAL=1
	stop
fi

# Push command file
adb push fbcmd /

echo "Restart loader, returns when device is ready"
if ! restart_loader; then
	RETVAL=1
	stop
fi

echo "Device is ready"
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

cat fbcmd_out_ref1 $HOST_TMP_DIR/frp fbcmd_out_ref2 > \
		$HOST_TMP_DIR/fbcmd_out_ref
diff $HOST_TMP_DIR/fbcmd_out $HOST_TMP_DIR/fbcmd_out_ref
if [ $? -ne 0 ]; then
	RETVAL=1
fi

stop

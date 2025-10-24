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
	fi
	adb shell rm /frp /dump1

	adb shell "stop loader-trf"
	exit $RETVAL
}

adb pull $PART $HOST_TMP_DIR/frp
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

if ! authenticate; then
	RETVAL=1
	stop
fi

FSIZE=`stat -c%s $HOST_TMP_DIR/frp`
dd if=/dev/urandom of=$HOST_TMP_DIR/dump1 bs=$FSIZE count=1
adb push $HOST_TMP_DIR/dump1 /
adb shell dd if=dump1 of=$PART bs=$FSIZE count=1

# Push command file
adb push fbcmd /

# Restart loader, returns when device is ready
if ! restart_loader; then
	RETVAL=1
	stop
fi

adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

adb pull $PART $HOST_TMP_DIR/frp_z
tmp=$(tr -dc '\000' <$HOST_TMP_DIR/frp_z | cmp - $HOST_TMP_DIR/frp_z)
if [[ $tmp = "-"* ]] || [[ $tmp = "c"* ]]; then
	echo "ERASE FAIL!"
	RETVAL=1
fi

diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -ne 0 ]; then
	RETVAL=1
fi

stop

#!/bin/bash

source ../common.sh
source ../authenticate.sh

TAPART=/dev/block/bootdevice/by-name/TA
RETVAL=1

stop () {
	adb shell "stop loader-trf"
	exit $RETVAL
}

# Authenticate
if ! authenticate; then
	RETVAL=1
	stop
fi

# Make backup of TA-partition and extract it for analysis
adb shell dd if=$TAPART of=/restore bs=4096 count=512
adb pull /restore $HOST_TMP_DIR
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# push data for testing
adb push secprop_dk /
if ! check_adb; then
	return 1
fi

# push fbcmd
adb push fbcmd /
if ! check_adb; then
	return 1
fi

# Restart loader, returns when device is ready
if ! restart_loader; then
	RETVAL=1
	stop
fi

# Extract loader result and analyze
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
OUT=`cat $HOST_TMP_DIR/fbcmd_out`
if [ ${OUT:${#OUT}-4:4} != "OKAY" ]; then
	echo "OKAY is missing: "$OUT
	leave
	RETVAL=1
	stop
fi

# Copy whole TA-partition after running loader for analysis
adb shell dd if=$TAPART of=/result bs=4096 count=512
adb pull /result $HOST_TMP_DIR/
if ! check_adb; then
	return 1
fi

# Remove metadata and make hex for search and comparison
tail -c15 secprop_dk > $HOST_TMP_DIR/secprop_dk1
xxd -p $HOST_TMP_DIR/restore > $HOST_TMP_DIR/restorehex
xxd -p $HOST_TMP_DIR/result > $HOST_TMP_DIR/resulthex
xxd -p $HOST_TMP_DIR/secprop_dk1 > $HOST_TMP_DIR/secprop_dk1hex

# It should find a match since Set-security has set the Devicekey
if grep --quiet -c -f $HOST_TMP_DIR/secprop_dk1hex $HOST_TMP_DIR/resulthex; then
	RETVAL=0
fi
# And this is a search to make sure that the claimed change didn't exist
# If a match is found then we can't know if Set-security had made any change
if grep --quiet -c -f $HOST_TMP_DIR/secprop_dk1hex \
			$HOST_TMP_DIR/restorehex; then
	RETVAL=1
	echo "The new DK that is set from secprop_dk\
		is similar to the previous DK"
fi

# Restore TA-partition
adb shell dd if=/restore of=$TAPART bs=4096 count=512
adb shell rm /restore
adb shell rm /result
if ! check_adb; then
	return 1
fi

# stop loader-trf
leave
stop

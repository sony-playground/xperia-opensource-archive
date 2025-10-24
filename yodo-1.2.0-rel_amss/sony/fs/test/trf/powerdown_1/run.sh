#!/bin/bash

source ../common.sh

# Save current loader in case it is not the same as flashed
adb pull /system/bin/lilo_test $HOST_TMP_DIR/lilo_test
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# Push ta2002_1 to unit which holds 01 for TA unit factory flag
# This will make the unit to restart in service mode
adb push ta2002_1 ta2002
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# Run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd &
# Disregard output due to we can not reliably connect with adb after shutdown

i=0
out=`adb get-state`
while [ $out != "unknown" ]; do
	echo "Please disconnect and reconnect the USB cable"
	sleep 1
	out=`adb get-state`
	let "i += 1"
	if [ $i == 20 ]; then
		echo "TIMEOUT"
		exit 1
	fi
done

echo "Waiting for reboot, this might take some time..."
adb wait-for-device

# Restore the loader
adb push $HOST_TMP_DIR/lilo_test /system/bin/lilo_test

# Push ta2002_0 to unit which holds 00 for TA unit factory flag
adb push ta2002_0 /ta2002
if [ $? -ne 0 ]; then
	echo "adb returned error"
	exit 1
fi

# Run loader again to reset Factory Flag
adb push fbcmd2 /fbcmd
adb shell loader -s$STORAGE -g/fbcmd

adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
if [ $? -ne 0 ]; then
	echo "adb pull /fbcmd_out returned error"
	exit 1
fi

diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -ne 0 ]; then
	echo "Unexpected response:"
	cat $HOST_TMP_DIR/fbcmd_out
	exit 1
fi

exit 0

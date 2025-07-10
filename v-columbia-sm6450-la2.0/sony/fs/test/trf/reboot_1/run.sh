#!/bin/bash

source ../common.sh

# init test
adb pull /system/bin/lilo_test $HOST_TMP_DIR/lilo_test
if [ $? -ne 0 ]; then
		# adb returned error
		exit 1
fi

# run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd
# disregard output due to we can not reliably connect with adb after shutdown

echo "Waiting for powerdown..."
sleep 2
out=`adb get-state`
if [ $out != "unknown" ]; then
		echo "Device was not shut down"
		RETVAL=1
fi
echo "Waiting for reboot into Android, this might take some time..."
adb wait-for-device
adb root
adb wait-for-device
adb push fla_fla_set /data
adb shell "misctatest w 2002 < /data/fla_fla_set"
adb shell "rm /data/fla_fla_set"
adb shell "reboot -p"
echo "Waiting for reboot into loader, this might take some time..."
adb wait-for-device
adb push $HOST_TMP_DIR/lilo_test /system/bin/lilo_test
exit $RETVAL

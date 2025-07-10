#!/bin/bash

source ../common.sh

TAPART=/dev/block/bootdevice/by-name/TA

# Make backup of TA-partition
adb shell dd if=$TAPART of=/restore bs=4096 count=512
if [ $? -ne 0 ]; then
		# adb returned error
		exit 1
fi
# Create some random data for testing
dd if=/dev/urandom of=$HOST_TMP_DIR/tadata bs=4096 count=1
adb push $HOST_TMP_DIR/tadata /

# run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# Copy whole TA-partition
adb shell dd if=$TAPART of=/result bs=4096 count=512
adb pull /result $HOST_TMP_DIR/
# Restore TA-partition
adb shell dd if=/restore of=$TAPART bs=4096 count=512
adb shell rm /restore
adb shell rm /result
# Make hex-representation of binaries so that we can compare
xxd -p $HOST_TMP_DIR/result | tr -d '\n' > $HOST_TMP_DIR/resulthex
xxd -p $HOST_TMP_DIR/tadata| tr -d '\n' > $HOST_TMP_DIR/tadatahex
if grep --quiet -c -f $HOST_TMP_DIR/tadatahex $HOST_TMP_DIR/resulthex; then
		TAWRITE=0
else
		TAWRITE=1
		echo "TA-Write FAIL"
fi
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -eq 0 ] && [ $TAWRITE -eq 0 ]
then
		exit 0
else
		echo "Fastboot protocol fail"
		exit 1
fi

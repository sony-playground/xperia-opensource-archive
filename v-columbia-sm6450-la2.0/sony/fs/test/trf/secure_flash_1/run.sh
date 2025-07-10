#!/bin/bash

source ../common.sh

PART=/dev/block/bootdevice/by-name/dsp
RETVAL=0

unzip dsp.zip -d $HOST_TMP_DIR
FSZ=`wc -c < $HOST_TMP_DIR/dsp.000`

# init test
adb shell dd if=$PART of=/restore bs=$FSZ count=1
if [ $? -ne 0 ]; then
		# adb returned error
		exit 1
fi
adb push dsp.cms /signature1
adb push $HOST_TMP_DIR/dsp.000 /dump1

# run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

# test final
adb shell dd if=$PART of=/dump2 bs=$FSZ count=1
adb shell dd if=/restore of=$PART bs=$FSZ count=1
adb pull dump2 $HOST_TMP_DIR/dump2
diff $HOST_TMP_DIR/dsp.000 $HOST_TMP_DIR/dump2
if [ $? -eq 0 ]; then
		echo "FLASH OK!"
		RETVAL=0
else
		echo "FLASH FAIL!"
		RETVAL=1
fi
adb shell rm /restore /signature1 /dump1 /dump2
diff $HOST_TMP_DIR/fbcmd_out fbcmd_out_ref
if [ $? -eq 0 ]; then
		exit $RETVAL
else
		exit 1
fi

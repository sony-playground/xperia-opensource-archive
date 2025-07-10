#!/bin/bash

source ../common.sh

PART=/dev/block/bootdevice/by-name/frp

adb push fbcmd /
if [ $? -ne 0 ]; then
		# adb returned error
		exit 1
fi
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

adb pull $PART $HOST_TMP_DIR/frp
digest=`sha224sum $HOST_TMP_DIR/frp`
digest=`echo ${digest} | cut -f 1 -d " "`
digest=${digest^^}

out=`cat $HOST_TMP_DIR/fbcmd_out`
if [ ${out:0:4} != "OKAY" ]; then
		echo "OKAY is missing"
		exit 1
fi
if [ ${out:4} != ${digest} ]; then
		echo "incorrect hash"
		echo $out
		echo $digest
		exit 1
fi

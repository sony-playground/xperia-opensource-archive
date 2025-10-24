#!/bin/bash
. ../common.sh

PART=/dev/block/bootdevice/by-name/boot_a

exec_remote dd if=$PART of=$DEV_TMP_DIR/dump2 bs=4096 count=1
exec_remote dd if=$DEV_TMP_DIR/restore of=$PART bs=4096 count=1
pull_remote $DEV_TMP_DIR/dump2 $HOST_TMP_DIR/dump2
diff $HOST_TMP_DIR/dump1 $HOST_TMP_DIR/dump2
if [ $? -ne 0 ]; then
		echo "FLASH FAIL! Files differ"
		exit 1
fi

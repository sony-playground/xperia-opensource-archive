#!/bin/bash
. ../common.sh

PART=/dev/block/bootdevice/by-name/TA

push_remote $HOST_TMP_DIR/ta_backup $DEV_TMP_DIR/ta_backup
exec_remote dd if=$DEV_TMP_DIR/ta_backup of=$PART

exit 0

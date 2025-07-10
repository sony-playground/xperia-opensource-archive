#!/bin/bash
. ../common.sh

PART=/dev/block/bootdevice/by-name/boot

exec_remote dd if=$PART of=$DEV_TMP_DIR/restore bs=4096 count=1
dd if=/dev/urandom of=$HOST_TMP_DIR/dump1 bs=4096 count=1 2> /dev/null
push_remote $HOST_TMP_DIR/dump1 $DEV_TMP_DIR/

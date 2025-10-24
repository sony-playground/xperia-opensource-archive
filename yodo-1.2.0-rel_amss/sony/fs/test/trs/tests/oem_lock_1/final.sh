#!/bin/bash
. ../common.sh

sleep 1
echo "Rebooting, please wait..."
adb wait-for-device
exec_remote mkdir -p $DEV_TMP_DIR

#!/bin/bash

source ../common.sh

# run loader
adb push fbcmd /
if [ $? -ne 0 ]; then
    # adb returned error
    exit 1
fi
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

cat $HOST_TMP_DIR/fbcmd_out
echo ""

out=`cat $HOST_TMP_DIR/fbcmd_out`
if [ ${out:0:12} != "OKAYOKAYOKAY" ]; then
    echo "OKAY is missing"
    exit 1
fi
if [ ${out:(-4)} != "OKAY" ]; then
    echo "OKAY is missing"
    exit 1
fi

#!/bin/bash

source ../common.sh

# This is a negative test, it is supposed to fail

# Push the fake response to the phone
adb push response /response

if [ $? -ne 0 ]; then
		# adb returned error
		exit 1
fi

# Run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

out=`cat $HOST_TMP_DIR/fbcmd_out`

# The response should start with 'DATA' and end with
# 'OKAYFAILAuthentication failed'
if [ ${out:0:4} != "DATA" ]; then
		echo "DATA is missing"
		exit 1
fi

echo ${out:${#out}-25:25}

# Authentication is supposed to FAIL because the response is faked.
if [ ${out:${#out}-25:18} != "FAILAuthentication" ]; then
		echo "Authentication is supposed to fail"
		exit 1
fi


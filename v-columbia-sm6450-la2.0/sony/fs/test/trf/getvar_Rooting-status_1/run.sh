#!/bin/bash

source ../common.sh

# Run loader
adb push fbcmd /
adb shell loader -s$STORAGE -g/fbcmd
adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out

OUT=`cat $HOST_TMP_DIR/fbcmd_out`

if [ ${OUT:4:12} == "NOT_ROOTABLE" -o \
     ${OUT:4:8}  == "ROOTABLE" -o \
     ${OUT:4:6}  == "ROOTED" -o \
     ${OUT:4:11} == "SL_ROOTABLE" -o \
     ${OUT:4:15} == "SL_UNL_ROOTABLE" \
   ]; then
		exit 0
else
	echo "Unexpected response:"
	cat $HOST_TMP_DIR/fbcmd_out
	# Print newline
	echo ""
	exit 1
fi

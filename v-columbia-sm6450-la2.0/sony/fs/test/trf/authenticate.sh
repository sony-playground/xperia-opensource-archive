#!/bin/bash

source ../common.sh

MAX_WAIT_TIME=15
TIME=0
GO_HOST_FILE="go_host"
GO_DEVICE_FILE="go_device"
RESPONSE_FILE="response"

leave() {
	adb shell rm -f /$GO_HOST_FILE
	adb shell rm -f /$GO_DEVICE_FILE
}

wait_for_device() {
	echo "Wait for device"
	# For supporting authentication in the tests, more than one second delay
	# was introduced for the handshaking and tr_reopen from the loader side.
	# Thus, a 2 second delay here will fix the problem.
	sleep 2s
	TIME=0
	adb pull /$GO_HOST_FILE $HOST_TMP_DIR
	while [ $? -ne 0 -a $TIME -lt $MAX_WAIT_TIME ]; do
		sleep 1
		TIME=$((TIME+=1))
		adb pull /$GO_HOST_FILE $HOST_TMP_DIR
	done

	if [ "$TIME" -ge $MAX_WAIT_TIME ]; then
		echo "Timeout waiting for device"
		leave
		return 1
	fi
	return 0
}

check_adb() {
	if [ $? -ne 0 ]; then
		echo "adb returned error"
		leave
		return 1
	fi
	return 0
}

restart_loader () {
	# Remove any previous 'GO HOST' file
	adb shell rm -f /$GO_HOST_FILE

	# Push any file to device, as long as it is named GO_DEVICE_FILE
	echo "x" > $HOST_TMP_DIR/$GO_DEVICE_FILE

	adb push $HOST_TMP_DIR/$GO_DEVICE_FILE /$GO_DEVICE_FILE
	if ! check_adb; then
		return 1
	fi

	if ! wait_for_device; then
		return 1
	fi
	return 0
}


authenticate () {
	echo "Download command file"

	echo "c SAKE-Authenticate:challenge" > $HOST_TMP_DIR/fbcmd
	echo "w" >> $HOST_TMP_DIR/fbcmd

	adb push $HOST_TMP_DIR/fbcmd /
	if ! check_adb; then
		return 1
	fi
	adb shell rm -f /fbcmd_out
	if ! check_adb; then
		return 1
	fi
	adb shell rm -f /$RESPONSE_FILE
	if ! check_adb; then
		return 1
	fi
	adb shell rm -f /$GO_HOST_FILE
	if ! check_adb; then
		return 1
	fi
	adb shell rm -f /$GO_DEVICE_FILE
	if ! check_adb; then
		return 1
	fi

	echo "Run loader"
	adb shell "start loader-trf"
	if ! check_adb; then
		return 1
	fi

	if ! wait_for_device; then
		return 1
	fi

	adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
	if ! check_adb; then
		return 1
	fi
	adb shell rm -f /$GO_HOST_FILE
	if ! check_adb; then
		return 1
	fi

	OUT=`cat $HOST_TMP_DIR/fbcmd_out`

	if [ ${OUT:${#OUT}-4:4} != "OKAY" ]; then
		echo "OKAY is missing: "$OUT
		leave
		return 1
	fi

	# Extract the data size
	DATA_SIZE_HEX=${OUT:4:8}
	DATA_SIZE=$((16#${DATA_SIZE_HEX}))

	# Remove 'DATAxxxxxxxx' (12 bytes) in the beginning
	dd bs=12 skip=1 if=$HOST_TMP_DIR/fbcmd_out of=$HOST_TMP_DIR/chlg1

	# Use data_size bytes, that is removing OKAYOKAY at the end
	dd bs=1 count=${DATA_SIZE} if=$HOST_TMP_DIR/chlg1 of=$HOST_TMP_DIR/chlg

	echo "Send challenge to the SECS server"
	export LD_LIBRARY_PATH=`pwd`/../../auth/
	../../auth/secsauth $HOST_TMP_DIR/chlg $HOST_TMP_DIR/$RESPONSE_FILE

	echo "Send response to the device"

	# Create new command file with size of response in download command
	RESPONSE_SIZE=$(stat -c%s $HOST_TMP_DIR/$RESPONSE_FILE)

	if [ $RESPONSE_SIZE -eq 0 ];  then
		echo "Response file is empty"
		leave
		return 1
	fi

	printf -v RESPONSE_SIZE_HEX '%08x' $RESPONSE_SIZE
	echo "c download:"$RESPONSE_SIZE_HEX > $HOST_TMP_DIR/fbcmd
	echo "b "$RESPONSE_FILE >> $HOST_TMP_DIR/fbcmd
	echo "c SAKE-Authenticate:response" >> $HOST_TMP_DIR/fbcmd
	echo "w" >> $HOST_TMP_DIR/fbcmd

	echo "Push the response to the device and let the loader continue"
	adb push $HOST_TMP_DIR/$RESPONSE_FILE /
	if ! check_adb; then
		return 1
	fi
	# Push new commands
	adb push $HOST_TMP_DIR/fbcmd /fbcmd
	if ! check_adb; then
		return 1
	fi
	# Push any file to device, as long it is named GO_DEVICE_FILE
	adb push $HOST_TMP_DIR/fbcmd /$GO_DEVICE_FILE
	if ! check_adb; then
		return 1
	fi

	if ! wait_for_device; then
		return 1
	fi

	# Extract result and analyze
	adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
	if ! check_adb; then
		return 1
	fi

	OUT=`cat $HOST_TMP_DIR/fbcmd_out`

	if [ ${OUT:${#OUT}-4:4} != "OKAY" ]; then
		echo "OKAY is missing: "$OUT
		leave
		return 1
	fi

	leave
	return 0
}

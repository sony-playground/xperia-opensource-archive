#!/bin/bash
# Test if erase works correctly and read-partition does not return
# cached contents. First writes random values over FRP partition, then
# executes loader read-erase-read. The output fbcmd_out contains 2
# reads appended, first part is filled with random values and second
# part should contain 0. The first part of output binary is skipped and
# response is removed from the output file and a check is done if its
# zeroed out. Same test is done with adb pull from frp partition.

source ../common.sh
source ../authenticate.sh

PART=/dev/block/bootdevice/by-name/frp
RETVAL=0

stop () {
	# Restore frp
	adb shell dd if=restore of=$PART
	adb shell rm restore
	adb shell rm dump1

	adb shell "stop loader-trf"
	exit $RETVAL
}

check_adb() {
	if [ $? -ne 0 ]; then
		echo "adb returned error"
		RETVAL=1
		stop
	fi
}

# Authenticate
if ! authenticate; then
	echo "Authentication failed"
	RETVAL=1
	stop
fi

# Create backup of frp on device
adb shell dd if=$PART of=restore bs=4096 count=128
check_adb

# Write random data to frp to test read/erase/read cache
dd if=/dev/urandom of=$HOST_TMP_DIR/dump1 bs=4096 count=128
adb push $HOST_TMP_DIR/dump1 /
check_adb
adb shell dd if=/dump1 of=$PART bs=4096 count=128
check_adb
adb pull $PART $HOST_TMP_DIR/frp_1
check_adb

# Push commands
adb push fbcmd /
check_adb

# Restart loader, returns when device is ready
if ! restart_loader; then
	RETVAL=1
	stop
fi

adb pull /fbcmd_out $HOST_TMP_DIR/fbcmd_out
check_adb

# First test if loader read outs frp as 0
# Skip first 512kb + 32bytes (appended fb response) and trailing 4 bytes
dd bs=524320 skip=1 if=$HOST_TMP_DIR/fbcmd_out of=$HOST_TMP_DIR/frp_filter
truncate --size=-4 $HOST_TMP_DIR/frp_filter

tmp=$(tr -dc '\000' <$HOST_TMP_DIR/frp_filter | cmp - $HOST_TMP_DIR/frp_filter)
if [[ $tmp = "-"* ]]; then
	echo "ERASE FAIL! Loader read command binary is not erased"
	RETVAL=1
fi

# Second test if adb read of frp is 0
adb pull $PART $HOST_TMP_DIR/frp_z
check_adb
tmp=$(tr -dc '\000' <$HOST_TMP_DIR/frp_z | cmp - $HOST_TMP_DIR/frp_z)
if [[ $tmp = "-"* ]]; then
	echo "ERASE FAIL! Adb pull binary is not erased"
	RETVAL=1
fi


cat fbcmd_out_ref1 $HOST_TMP_DIR/frp_1 fbcmd_out_ref2 $HOST_TMP_DIR/frp_z \
		fbcmd_out_ref3 > $HOST_TMP_DIR/fbcmd_out_ref

diff $HOST_TMP_DIR/fbcmd_out $HOST_TMP_DIR/fbcmd_out_ref
if [ $? -ne 0 ]; then
	echo "Output differs from reference"
	RETVAL=1
fi

stop
